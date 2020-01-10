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
#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include <pybind11/detail/init.h>

#include <SofaPython3/PythonFactory.h>
#include "Binding_VisualParams.h"
#include "Binding_VisualParams_doc.h"

namespace sofapython3
{

VisualContext::VisualContext()
{
    m_currentParams = nullptr;
}

VisualContext::~VisualContext(){
}

template<typename T, typename D>
std::vector<D>& copyToVector(std::vector<D>& dest, py::array_t<T, py::array::c_style> src)
{
    auto r = src.unchecked();
    for (ssize_t i = 0; i < r.shape(0); i++)
    {
        D tmp;
        for(size_t j=0;j<r.shape(1);j++)
            tmp[j] = typename D::value_type(r(i,j));
        dest.push_back(tmp);
    }
    return dest;
}


template<class D>
std::vector<D>& fromPython(std::vector<D>& dest, py::list list)
{
    for(auto item :  list)
    {
        D destitem;
        py::list listitem = py::cast<py::list>(item);
        for(size_t i=0;i<listitem.size()&&i<destitem.size();i++)
        {
            destitem[i] = py::cast<double>(listitem[i]);
        }
        dest.push_back(destitem);
    }
    return dest;
}

template<class D>
std::vector<D>& fromPython(std::vector<D>& dest, py::array src)
{
    py::buffer_info srcinfo = src.request();
    if(srcinfo.format=="d")
        return copyToVector<double>(dest, src);
    else if(srcinfo.format=="f")
        return copyToVector<float>(dest, src);
    return dest;
}

template<class D>
D& fromPython(D& dest, py::list src)
{
    for(size_t i=0;i<src.size()&&i<dest.size();i++)
    {
        dest[i] = py::cast<typename D::value_type>(src[i]);
    }
    return dest;
}


template<class D>
std::vector<D>& fromPython(std::vector<D>& dest, py::object src)
{
    if(py::isinstance<py::array>(src))
        return fromPython(dest, py::cast<py::array>(src));

    if(py::isinstance<py::list>(src))
        return fromPython(dest, py::cast<py::list>(src));

    return dest;
}

void moduleAddVisualParams(py::module &m)
{
    py::class_<VisualContext,
            std::shared_ptr<VisualContext>> c(m, "VisualContext");
    c.def("drawPoints", [](VisualContext& vc, py::object points, py::object pysize, py::list pycolor)
    {
        if(vc.m_currentParams==nullptr)
            throw std::runtime_error("Invalid rendering context.");

        if(vc.m_currentParams->drawTool()==nullptr)
            throw std::runtime_error("Missing drawTools in the current visual context");

        auto dt = vc.m_currentParams->drawTool();

        std::vector<sofa::defaulttype::Vec3d> tmp ;
        sofa::helper::types::RGBAColor color {sofa::helper::types::RGBAColor::white()};

        fromPython(color, pycolor);
        fromPython(tmp, points);

        dt->drawPoints(tmp, py::cast<float>(pysize), color);
    });
}

} /// namespace sofapython3
