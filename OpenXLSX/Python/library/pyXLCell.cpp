/*

   ____                               ____      ___ ____       ____  ____      ___
  6MMMMb                              `MM(      )M' `MM'      6MMMMb\`MM(      )M'
 8P    Y8                              `MM.     d'   MM      6M'    ` `MM.     d'
6M      Mb __ ____     ____  ___  __    `MM.   d'    MM      MM        `MM.   d'
MM      MM `M6MMMMb   6MMMMb `MM 6MMb    `MM. d'     MM      YM.        `MM. d'
MM      MM  MM'  `Mb 6M'  `Mb MMM9 `Mb    `MMd       MM       YMMMMb     `MMd
MM      MM  MM    MM MM    MM MM'   MM     dMM.      MM           `Mb     dMM.
MM      MM  MM    MM MMMMMMMM MM    MM    d'`MM.     MM            MM    d'`MM.
YM      M9  MM    MM MM       MM    MM   d'  `MM.    MM            MM   d'  `MM.
 8b    d8   MM.  ,M9 YM    d9 MM    MM  d'    `MM.   MM    / L    ,M9  d'    `MM.
  YMMMM9    MMYMMM9   YMMMM9 _MM_  _MM_M(_    _)MM_ _MMMMMMM MYMMMM9 _M(_    _)MM_
            MM
            MM
           _MM_

  Copyright (c) 2020, Kenneth Troldal Balslev

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  - Neither the name of the author nor the
    names of any contributors may be used to endorse or promote products
    derived from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
  DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

 */

#include <pybind11/pybind11.h>
#include <XLCell.hpp>

namespace py = pybind11;
using namespace OpenXLSX;

void init_XLCell(py::module &m) {
    py::class_<XLCell>(m, "XLCell")
        .def_property("integerValue", &XLCell::getValue<int64_t>, &XLCell::setValue<int64_t>, "Get or set the cell getValue as an integer.")
        .def_property("floatValue",
                      &XLCell::getValue<double>,
                      &XLCell::setValue<double>,
                      "Get or set the cell value as a floating point getValue.")
        .def_property("booleanValue", &XLCell::getValue<bool>, &XLCell::setValue<bool>, "Get or set the cell getValue as a boolean.")
        .def_property("stringValue",
                      &XLCell::getValue<const std::string>,
                      &XLCell::setValue<const std::string>,
                      "Get or set the cell getValue as a string.")
        .def_property("getValue", &XLCell::getValue, &XLCell::operator=<XLCellValue>, "Get or set the cell getValue object.")
        //        .def("value", &XLCell::value, "Get the getValue object for the cell.")
        .def("valueType", &XLCell::valueType, "Get the getValue type for the cell.")
        .def("cellReference", &XLCell::cellReference, "Get the reference object for the cell")
        .def("offset",
             py::overload_cast<uint32_t, uint16_t>(&XLCell::offset), 
             "Get the reference to the offset value of the current one", 
             py::arg("rowOffset"),
             py::arg("columnOffset"))
        .def("hasFormula", &XLCell::hasFormula, "Boolean for determining if the cell has a formula or not.")
        .def("formula", &XLCell::formula, "Get the formula object for the cell")
        .def("setFormula", &XLCell::setFormula, "Set the formula string for the cell", py::arg("formula"));
}

