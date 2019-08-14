#include "Binding_Visitor.h"

#include "Binding_Node.h"

#include <sofa/simulation/PropagateEventVisitor.h>

#include <SofaPython3/DataHelper.h>
#include <SofaPython3/PythonFactory.h>

#include <pybind11/pybind11.h>
#include <pybind11/detail/init.h>

PYBIND11_DECLARE_HOLDER_TYPE(Visitor,
                             sofapython3::py_non_intrusive_ptr<Visitor>, true)


namespace sofapython3
{
    namespace py { using namespace pybind11; }
    using namespace pybind11::literals;
    using sofa::simulation::Visitor;


    class Visitor_Trampoline : public Visitor, public PythonNonIntrusiveTrampoline
    {
    public:
        Visitor_Trampoline(sofa::core::ExecParams* params = sofa::core::ExecParams::defaultInstance())
            : Visitor(params)
        {
            // @damienmarchal: Why don't we need this in every other trampoline? Why did I miss?
            setInstance(py::cast(dynamic_cast<PythonNonIntrusiveTrampoline*>(this)));
        }

        ~Visitor_Trampoline() override = default; // impossible to destroy pyobject as it's a circular dependency..

        sofa::simulation::Visitor::Result processNodeTopDown(sofa::simulation::Node* node) override
        {
            PYBIND11_OVERLOAD_PURE(Visitor::Result, Visitor, processNodeBottomUp, node);
        }

        void processNodeBottomUp(sofa::simulation::Node* node) override
        {
            try {
                PYBIND11_OVERLOAD_PURE(void, Visitor, processNodeBottomUp, node);
            } catch (std::exception & /*e*/) {
                return;
            }
        }

        const char* getClassName() const override
        {
            return pyobject->ob_type->tp_name;
        }
        const char* getCategoryName() const override
        {
            try {
                PYBIND11_OVERLOAD_PURE(const char*, Visitor, getCategoryName);
            } catch (std::exception& /*e*/) {
                return Visitor::getCategoryName();
            }
        }
        bool isThreadSafe() const override {
            try {
                PYBIND11_OVERLOAD_PURE(bool, Visitor, isThreadSafe);
            } catch (std::exception& /*e*/) {
                return Visitor::isThreadSafe();
            }
        }
    };

    class ExecuteFunctionVisitor: public Visitor
    {
    public:
        ExecuteFunctionVisitor(py::object function)
            : Visitor(sofa::core::ExecParams::defaultInstance())
            , m_func(function)
        {

        }

        virtual Result processNodeTopDown(sofa::simulation::Node* node) override
        {
            py::object pyr = m_func(node);
            if (pyr.is_none())
                throw py::value_error("ExecuteFunctionVisitor's signature must be (arg0: Sofa.Core.Node) -> bool");

            if (py::cast<bool>(pyr))
                return RESULT_CONTINUE;
            return RESULT_PRUNE;
        }

        const char* getClassName() const override
        {
            return "ExecuteFunctionVisitor";
        }
        const char* getCategoryName() const override
        {
            return "Default";
        }
        bool isThreadSafe() const override
        {
            return false;
        }
    private:
        py::object m_func;
    };

    void moduleAddVisitor(py::module &m)
    {

        py::class_<Visitor, Visitor_Trampoline,
                py_non_intrusive_ptr<Visitor>> v(m, "Visitor",
                                                 py::dynamic_attr(),
                                                 py::multiple_inheritance());

        v.def(py::init([]()
        {
            return new Visitor_Trampoline(sofa::core::ExecParams::defaultInstance());
        }));

        py::enum_<Visitor::TreeTraversalRepetition>(v, "TreeTraversalRepetition", py::arithmetic(), "")
                .value("NO_REPETITION", Visitor::NO_REPETITION, "")
                .value("REPEAT_ALL", Visitor::REPEAT_ALL, "")
                .value("REPEAT_ONCE", Visitor::REPEAT_ONCE, "")
                .export_values();

        py::enum_<Visitor::Result>(v, "Result", py::arithmetic(), "")
                .value("RESULT_CONTINUE", Visitor::RESULT_CONTINUE, "")
                .value("RESULT_PRUNE", Visitor::RESULT_PRUNE, "")
                .export_values();

        v.def("execute", [](Visitor& self, Node& node, bool precomputedOrder = false){ self.execute(node.toBaseContext(), precomputedOrder); });
        v.def("processNodeTopDown", [](Visitor& self, Node* node) { self.processNodeTopDown(node); }, "node"_a);
        v.def("processNodeBottomUp", [](Visitor& self, Node* node) { self.processNodeBottomUp(node); }, "node"_a);
        v.def("childOrderReversed", &Visitor::childOrderReversed, "node"_a);
        v.def("isThreadSafe", &Visitor::isThreadSafe);
        v.def("getCategoryName", &Visitor::getCategoryName);
        v.def("getClassName", &Visitor::getClassName);
        v.def("getInfos", &Visitor::getInfos);
        v.def("treeTraversal", &Visitor::treeTraversal, "repeat"_a);
        v.def("execParams", &Visitor::execParams);

        py::class_<ExecuteFunctionVisitor, Visitor, std::shared_ptr<ExecuteFunctionVisitor>> efv(m, "ExecuteFunctionVisitor");
        efv.def(py::init([](py::args& args){
            return ExecuteFunctionVisitor(args[0]);
        }));

        m.def("_test_getCategoryName_test_", [](Visitor& v){ return v.getCategoryName(); });
    }

}  // namespace sofapython3
