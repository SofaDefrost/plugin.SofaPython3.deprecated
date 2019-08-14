#pragma once

#include <sofa/simulation/Visitor.h>
#include <SofaPython3/config.h>

#include <pybind11/pybind11.h>

template class pybind11::class_<sofa::simulation::Visitor,
                                std::shared_ptr<sofa::simulation::Visitor>>;

namespace sofapython3
{

namespace py { using namespace pybind11; }

void moduleAddVisitor(py::module &m);

} /// namespace sofapython3
