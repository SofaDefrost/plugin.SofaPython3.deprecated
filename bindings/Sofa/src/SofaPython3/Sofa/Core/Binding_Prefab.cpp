/*********************************************************************
Copyright 2019, CNRS, University of Lille, INRIA

This file is part of sofaPython3

sofaPython3 is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

sofaPython3 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with sofaqtquick. If not, see <http://www.gnu.org/licenses/>.
*********************************************************************/
/********************************************************************
 Contributors:
    - damien.marchal@univ-lille.fr
    - bruno.josue.marques@inria.fr
    - eve.le-guillou@centrale.centralelille.fr
    - jean-nicolas.brunet@inria.fr
    - thierry.gaugry@inria.fr
********************************************************************/

#include <pybind11/pybind11.h>
#include <pybind11/eval.h>

#include "Binding_Prefab.h"
#include "Binding_Prefab_doc.h"

#include <SofaPython3/DataHelper.h>
#include <SofaPython3/PythonFactory.h>
#include <SofaPython3/PythonEnvironment.h>

#include <SofaPython3/Sofa/Core/Binding_Base.h>
#include <sofa/core/objectmodel/DataCallback.h>
using sofa::core::objectmodel::DataCallback;

#include <sofa/simulation/DeleteVisitor.h>
#include <sofa/helper/system/FileMonitor.h>
using sofa::helper::system::FileMonitor;
using sofa::helper::system::FileEventListener;

PYBIND11_DECLARE_HOLDER_TYPE(Prefab,
                             sofapython3::py_shared_ptr<Prefab>, true)

#include <sofa/simulation/VisualVisitor.h>
using sofa::simulation::VisualInitVisitor;

#include <sofa/simulation/Simulation.h>
using sofa::simulation::Simulation;
using sofa::simulation::Node;

#include <sofa/simulation/MutationListener.h>
using sofa::simulation::MutationListener;

namespace sofapython3
{
using sofa::core::objectmodel::Event;

void forwardEvent(Node *parent, Node *child, const std::string& evtName)
{
    PythonEnvironment::gil acquire;

    py::object self = py::cast(parent);
    /// Is there a method with this name in the class ?
    if( py::hasattr(self, evtName.c_str()) )
    {
        py::object fct = self.attr(evtName.c_str());
        /// Call the matching event in the funcVector & pass it the given event
        fct(PythonFactory::toPython(parent), PythonFactory::toPython(child));
    }
}

void forwardEvent(Node *parent, BaseObject *child, const std::string& evtName){
    PythonEnvironment::gil acquire;

    py::object self = py::cast(parent);
    /// Is there a method with this name in the class ?
    if( py::hasattr(self, evtName.c_str()) )
    {
        py::object fct = self.attr(evtName.c_str());
        /// Call the matching event in the funcVector & pass it the given event
        fct(PythonFactory::toPython(parent), PythonFactory::toPython(child));
    }
}


void PrefabMutationListener::onEndAddChild(Node *parent, Node *child)
{   forwardEvent(parent, child, "onEndAddChild"); }

void PrefabMutationListener::onEndRemoveChild(Node *parent, Node *child)
{   forwardEvent(parent, child, "onEndRemoveChild"); }

void PrefabMutationListener::onEndAddObject(Node *parent, BaseObject *object)
{   forwardEvent(parent, object, "onEndAddObject"); }

void PrefabMutationListener::onEndRemoveObject(Node *parent, BaseObject *object)
{   forwardEvent(parent, object, "onEndRemoveObject"); }

void Prefab::init()
{
    reinit();
    Inherit1::init(sofa::core::ExecParams::defaultInstance());
}

void PrefabFileEventListener::fileHasChanged(const std::string &filename)
{
    PythonEnvironment::gil acquire ;
    //std::string file=filepath;
    //SP_CALL_FILEFUNC(const_cast<char*>("onReimpAFile"),
    //                 const_cast<char*>("s"),
    //                 const_cast<char*>(file.data()));

    py::dict local;
    local["filename"] = filename;
    py::eval("onReimpAFile(filename)", py::globals(), local);

    m_prefab->clearLoggedMessages();
    m_prefab->init();
}

void Prefab::reinit()
{
    clearLoggedMessages();

    /// remove everything in the node.
    execute<sofa::simulation::DeleteVisitor>(sofa::core::ExecParams::defaultInstance());
    doReInit();

    /// Beurk beurk beurk
    sofa::simulation::getSimulation()->initNode(this);
    execute<VisualInitVisitor>(nullptr);

    m_componentstate = sofa::core::objectmodel::ComponentState::Valid;
}

void Prefab::doReInit()
{
}

Prefab::Prefab()
{
    /// The file listener is used to detect when the file is canged
    m_filelistener.m_prefab = this;

    /// In case of change we call reinit
    m_datacallback.addCallback( std::bind(&Prefab::reinit, this) );

    /// The mutation listener is there to detect when nodes are added/remove
    //addListener(&m_mutationListener);
}


Prefab::~Prefab()
{
    FileMonitor::removeListener(&m_filelistener);
}


void Prefab::addPrefabParameter(const std::string& name, py::object value, const std::string& help, std::string type)
{
    BaseData* data = findData(name);
    if(data == nullptr)
    {
        BaseData* data = BindingBase::addData(py::cast(this), name, value, py::object(), help, "Prefab's properties", type);
        m_datacallback.addInputs({data});
        return;
    }
    //PythonFactory::fromPython(data, value);
}

void Prefab::setSourceTracking(const std::string& filename)
{
    std::cout << "Activating source tracking to " << filename << std::endl;
    FileMonitor::addFile(filename, &m_filelistener);
}


class Prefab_Trampoline : public Prefab, public PythonTrampoline
{
public:
    Prefab_Trampoline() = default;

    ~Prefab_Trampoline() override = default;

    std::string getClassName() const override
    {
        return "Prefab"; /// pyobject->ob_type->tp_name;
    }

    void doReInit() override ;
};

void Prefab_Trampoline::doReInit()
{
    try{
        PYBIND11_OVERLOAD(void, Prefab, doReInit, );
    } catch (std::exception& e)
    {
        msg_error(this) << e.what();
    }
}

void moduleAddPrefab(py::module &m) {
    py::class_<sofa::core::objectmodel::BasePrefab,
            sofa::simulation::Node,
            sofa::core::objectmodel::BasePrefab::SPtr>(m, "BasePrefab");

    py::class_<Prefab,
            Prefab_Trampoline,
            BasePrefab,
            py_shared_ptr<Prefab>> f(m, "RawPrefab",
                                     py::dynamic_attr(),
                                     py::multiple_inheritance(),
                                     sofapython3::doc::prefab::Prefab);

    f.def(py::init([](py::args& /*args*/, py::kwargs& kwargs){
              auto c = new Prefab_Trampoline();

              for(auto kv : kwargs)
              {

                  std::string key = py::cast<std::string>(kv.first);
                  py::object value = py::reinterpret_borrow<py::object>(kv.second);

                  std::cout << "PREFAB ARE BROKEN " << key << std::endl;

                  if( key == "name")
                  c->setName(py::cast<std::string>(kv.second));
                  try {
                      BindingBase::SetAttr(*c, key, value);
                  } catch (py::attribute_error& /*e*/) {
                      /// kwargs are used to set datafields to their initial values,
                      /// but they can also be used as simple python attributes, unrelated to SOFA.
                      /// thus we catch & ignore the py::attribute_error thrown by SetAttr
                  }
              }
              return c;

          }
          ));

    f.def("setSourceTracking", &Prefab::setSourceTracking);
    f.def("addPrefabParameter", &Prefab::addPrefabParameter,
          "name"_a, "value"_a, "help"_a, "type"_a);
    f.def("init", &Prefab::init);
    f.def("reinit", &Prefab::reinit);
}


}
