/**
NO TITLE
Copyright (C) 2020 ApiGear UG

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#pragma once

#include <QtCore>

#include "tb_same1/api/api.h"

#if defined(TB_SAME1_LIB_LIBRARY)
#  define TB_SAME1_LIB_EXPORT Q_DECL_EXPORT
#else
#  define TB_SAME1_LIB_EXPORT Q_DECL_IMPORT
#endif

namespace tb_same1 {

/**
* The SameEnum2Interface implementation.
*/
class TB_SAME1_LIB_EXPORT SameEnum2Interface : public AbstractSameEnum2Interface
{
    Q_OBJECT
public:
    explicit SameEnum2Interface(QObject *parent = nullptr);
    virtual ~SameEnum2Interface() override;


    /** @return value of the property prop1 */
    Enum1::Enum1Enum prop1() const override;
    /** Use to change a property value.
    * if the property is changed, a signal {.Name}}Changed is emitted.
    * @param value to set for the property prop1 
    */
    void setProp1(Enum1::Enum1Enum prop1) override;
    /** @return value of the property prop2 */
    Enum2::Enum2Enum prop2() const override;
    /** Use to change a property value.
    * if the property is changed, a signal {.Name}}Changed is emitted.
    * @param value to set for the property prop2 
    */
    void setProp2(Enum2::Enum2Enum prop2) override;
    Enum1::Enum1Enum func1(Enum1::Enum1Enum param1) override;
    Enum1::Enum1Enum func2(Enum1::Enum1Enum param1, Enum2::Enum2Enum param2) override;

private:
    /** prop1 property */
    Enum1::Enum1Enum m_prop1;
    /** prop2 property */
    Enum2::Enum2Enum m_prop2;
};
} //namespace tb_same1
