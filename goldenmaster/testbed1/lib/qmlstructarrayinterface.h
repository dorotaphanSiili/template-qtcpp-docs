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

#include "structarrayinterface.h"
#include <memory>

namespace testbed1 {

/**
* A QML wrapper of the StructArrayInterface implementation.
* Uses a StructArrayInterface backend provided by an ApiFactory.
* Use this class to easily bind to properties and signals provided by StructArrayInterface backend or
* invoke operations on it. Have in mind that singals provided by StructArrayInterface backend should be
* emitted only by StructArrayInterface backend, emitting it on qml will not reach the StructArrayInterface backend.
* See ApiFactory and factories that implement the ApiFactoryInterface for other features.
*/
class TESTBED1_LIB_EXPORT QmlStructArrayInterface : public AbstractStructArrayInterface
{
    Q_OBJECT

    /**
    * Exposes propBool property for qml.
    */
    Q_PROPERTY(QList<StructBool> propBool READ propBool WRITE setPropBool NOTIFY propBoolChanged)

    /**
    * Exposes propInt property for qml.
    */
    Q_PROPERTY(QList<StructInt> propInt READ propInt WRITE setPropInt NOTIFY propIntChanged)

    /**
    * Exposes propFloat property for qml.
    */
    Q_PROPERTY(QList<StructFloat> propFloat READ propFloat WRITE setPropFloat NOTIFY propFloatChanged)

    /**
    * Exposes propString property for qml.
    */
    Q_PROPERTY(QList<StructString> propString READ propString WRITE setPropString NOTIFY propStringChanged)
public:
    explicit QmlStructArrayInterface(QObject *parent = nullptr);
    ~QmlStructArrayInterface() override;
    /**
    * Getter for a propBool property
    * @return A value for propBool property provided by backend.
    */
    QList<StructBool> propBool() const override;
    /*
    * Setter for a propBool property, requests the backend to set the propBool property
    * @param const QList<StructBool>& propBool  Value to set for  propBool property.
    */
    void setPropBool(const QList<StructBool>& propBool) override;
    /**
    * Getter for a propInt property
    * @return A value for propInt property provided by backend.
    */
    QList<StructInt> propInt() const override;
    /*
    * Setter for a propInt property, requests the backend to set the propInt property
    * @param const QList<StructInt>& propInt  Value to set for  propInt property.
    */
    void setPropInt(const QList<StructInt>& propInt) override;
    /**
    * Getter for a propFloat property
    * @return A value for propFloat property provided by backend.
    */
    QList<StructFloat> propFloat() const override;
    /*
    * Setter for a propFloat property, requests the backend to set the propFloat property
    * @param const QList<StructFloat>& propFloat  Value to set for  propFloat property.
    */
    void setPropFloat(const QList<StructFloat>& propFloat) override;
    /**
    * Getter for a propString property
    * @return A value for propString property provided by backend.
    */
    QList<StructString> propString() const override;
    /*
    * Setter for a propString property, requests the backend to set the propString property
    * @param const QList<StructString>& propString  Value to set for  propString property.
    */
    void setPropString(const QList<StructString>& propString) override;

    /**
    * Exposes funcBool of backend implementation to a qml.
    *   
    */
    Q_INVOKABLE StructBool funcBool(const QList<StructBool>& paramBool) override;

    /**
    * Exposes funcInt of backend implementation to a qml.
    *   
    */
    Q_INVOKABLE StructBool funcInt(const QList<StructInt>& paramInt) override;

    /**
    * Exposes funcFloat of backend implementation to a qml.
    *   
    */
    Q_INVOKABLE StructBool funcFloat(const QList<StructFloat>& paramFloat) override;

    /**
    * Exposes funcString of backend implementation to a qml.
    *   
    */
    Q_INVOKABLE StructBool funcString(const QList<StructString>& paramString) override;

Q_SIGNALS:
    /** Re-define singals for property changed notification, to make them are available for qml property */
    void propBoolChanged(const QList<StructBool>& propBool);
    void propIntChanged(const QList<StructInt>& propInt);
    void propFloatChanged(const QList<StructFloat>& propFloat);
    void propStringChanged(const QList<StructString>& propString);
private:
    /**
    * Backend of AbstractStructArrayInterface type that provides properties on which methods will be invoked.
    * Produced by a ApiFactory factory. 
    */
	std::shared_ptr<AbstractStructArrayInterface> m_obj;
};

} //namespace testbed1
