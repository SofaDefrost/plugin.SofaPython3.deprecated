#include "Binding_Simulation.h"

#include <sofa/simulation/Simulation.h>
#include "Simulation_doc.h"
using sofa::simulation::Simulation;
using sofa::simulation::Node;
using namespace pybind11::literals;

namespace sofapython3
{

void moduleAddSimulation(py::module &m)
{
  ///////////////////////////// Simulation binding //////////////////////////////
  py::class_<Simulation, Simulation::SPtr> s(m, "Simulation", __doc_sofa_simulation_Simulation);
  s.def("print", &Simulation::print, "node"_a,__doc_sofa_simulation_Simulation_print);
  s.def("init", &Simulation::init, "node"_a, __doc_sofa_simulation_Simulation_init);
  s.def("animate", &Simulation::animate, "node"_a, "dt"_a = 0.0, __doc_sofa_simulation_Simulation_animate);
  s.def("reset", &Simulation::reset, "node"_a, __doc_sofa_simulation_Simulation_reset);
  s.def("load", &Simulation::load, "filename"_a, "reload"_a = false, __doc_sofa_simulation_Simulation_load);
  s.def("unload", &Simulation::unload, "node"_a, __doc_sofa_simulation_Simulation_unload);
}

void moduleAddRuntime(py::module &m)
{
  py::module singleRuntime = m.def_submodule("SingleSimulation", __doc_sofa_simulation_Simulation);
  singleRuntime.def("setSimulation", [](Simulation *s){ sofa::simulation::setSimulation(s); }, "Simulation"_a, __doc_sofa_simulation_setSimulation);
  singleRuntime.def("getSimulation", [](){ return sofa::simulation::getSimulation(); }, __doc_sofa_simulation_getSimulation);
  singleRuntime.def("print", [](Node* n){ sofa::simulation::getSimulation()->print(n); }, "node"_a, __doc_sofa_simulation_Simulation_print);
  singleRuntime.def("animate", [](Node* n, SReal dt=0.0){ sofa::simulation::getSimulation()->animate(n, dt); }, "node"_a, "dt"_a = 0.0, __doc_sofa_simulation_Simulation_animate);
  singleRuntime.def("init", [](Node* n){ sofa::simulation::getSimulation()->init(n); }, "node"_a, __doc_sofa_simulation_Simulation_init);
  singleRuntime.def("reset", [](Node* n){ sofa::simulation::getSimulation()->reset(n); }, "node"_a, __doc_sofa_simulation_Simulation_reset);
  singleRuntime.def("load", [](const std::string name){ return sofa::simulation::getSimulation()->load(name.c_str());}, "filename"_a, __doc_sofa_simulation_Simulation_load);
  singleRuntime.def("unload", [](Node* n){ sofa::simulation::getSimulation()->unload(n); }, "node"_a, __doc_sofa_simulation_Simulation_unload);
}


} /// namespace sofapython3
