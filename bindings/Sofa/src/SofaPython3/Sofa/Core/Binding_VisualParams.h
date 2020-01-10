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

#pragma once

#include <pybind11/pybind11.h>
#include <sofa/core/visual/VisualParams.h>


namespace sofapython3
{
namespace py { using namespace pybind11; }

using sofa::core::visual::VisualParams;
using sofa::defaulttype::Vec3d;

class VisualContext
{
public:
    VisualContext();
    virtual ~VisualContext();
    const sofa::core::visual::VisualParams* m_currentParams;

    void enter(){}
    void exit(){ m_currentParams = nullptr; }
};

template<class T>
class ContextManager
{
public:
    T m_context;
    ContextManager(T context)
    {
        m_context = context;
        m_context->enter();
    }

    ~ContextManager()
    {
        m_context->exit();
    }
};

void moduleAddVisualParams(py::module &m);

} /// namespace sofapython3

template class pybind11::class_<sofapython3::VisualContext, std::shared_ptr<sofapython3::VisualContext>>;

