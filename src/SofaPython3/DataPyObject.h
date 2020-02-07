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

#include <iostream>
#include <pybind11/pybind11.h>

#include <SofaPython3/config.h>
#include <SofaPython3/PythonEnvironment.h>
#include <sofa/core/objectmodel/Data.h>

////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sofa::core::objectmodel
{

class TSPyObject
{
public:
    pybind11::object m_object {sofapython3::py::none()};
    TSPyObject(){}
    TSPyObject(pybind11::object object){ m_object = object; }

    bool is_none() const
    {
        return m_object.is_none();
    }
};

typedef Data<TSPyObject> DataPyObject;

/// Specialization for reading pybind::object...
template<> bool TData<TSPyObject>::read( const std::string& str );
template<> void TData<TSPyObject>::printValue( std::ostream& out) const;
template<> std::string TData<TSPyObject>::getValueString() const ;

}


