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
#include <QtCore/QtGlobal>

#include <memory>

#if defined(TESTBED1_API_LIBRARY)
#  define TESTBED1_API_EXPORT Q_DECL_EXPORT
#else
#  define TESTBED1_API_EXPORT Q_DECL_IMPORT
#endif

namespace testbed1 {
    class AbstractStructInterface;
    class AbstractStructArrayInterface;

/**
* An interface for a Factory of interfaces in testbed1
* May be used to provide different implementations of your interfaces.
* Check the usage of IApiFactory in Qml versions of interface implementation.
* See also the ApiFactory, where you can set this factory as an IApiFactory implementation.
*/
class TESTBED1_API_EXPORT IApiFactory
{
public:
    /** 
    * Create an instance of StructInterface
    * @return The implementation of a AbstractStructInterface.
    */
    virtual std::shared_ptr<AbstractStructInterface> createStructInterface(QObject *parent = nullptr) = 0;
    /** 
    * Create an instance of StructArrayInterface
    * @return The implementation of a AbstractStructArrayInterface.
    */
    virtual std::shared_ptr<AbstractStructArrayInterface> createStructArrayInterface(QObject *parent = nullptr) = 0;
};

} //namespace testbed1
