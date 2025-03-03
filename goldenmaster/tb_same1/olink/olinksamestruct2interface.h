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
#include <QtPromise>

#include "tb_same1/api/api.h"
#include "olink/iobjectsink.h"

#include <nlohmann/json.hpp>

namespace ApiGear {
namespace ObjectLink {
class IClientNode;
}}


using namespace ApiGear;
using namespace ApiGear::ObjectLink;

namespace tb_same1 {

/**
* Adapts the general OLink Client handler to a SameStruct2Interface in a way it provides access 
* to remote specific for SameStruct2Interface services (properties, signals, methods). 
* Sends and receives data over the network with ObjectLink protocol, through the communication node. 
* see https://objectlinkprotocol.net for ObjectLink details.
* see https://github.com/apigear-io/objectlink-core-cpp.git for olink client node - abstraction over the network.
* see Apigear::ObjectLink::OlinkClient for general Olink Client Handler implementation.
*     It provides a network implementation and tools to connect OLinkSameStruct2Interface to it.
* Use on client side to request changes of the SameStruct2Interface on the server side 
* and to subscribe for the SameStruct2Interface changes.
*/
class OLinkSameStruct2Interface : public AbstractSameStruct2Interface, public IObjectSink
{
    Q_OBJECT
public:
    /** ctor */
    explicit OLinkSameStruct2Interface(QObject *parent = nullptr);
    /** dtor */
    ~OLinkSameStruct2Interface() override = default;
    /**
    * Property getter
    * @return Locally stored recent value for Prop1.
    */
    Struct2 prop1() const override;
    /**
    * Request setting a property on the SameStruct2Interface service.
    * @param The value to which set request is send for the Prop1.
    */
    void setProp1(const Struct2& prop1) override;
    /**
    * Property getter
    * @return Locally stored recent value for Prop2.
    */
    Struct2 prop2() const override;
    /**
    * Request setting a property on the SameStruct2Interface service.
    * @param The value to which set request is send for the Prop2.
    */
    void setProp2(const Struct2& prop2) override;
    /**
    * Remote call of ISameStruct2Interface::func1 on the SameStruct2Interface service.
    * Uses func1Async
    */
    Struct1 func1(const Struct1& param1) override;
    /**
    * Remote call of ISameStruct2Interface::func1 on the SameStruct2Interface service.
    */
    QtPromise::QPromise<Struct1> func1Async(const Struct1& param1);
    /**
    * Remote call of ISameStruct2Interface::func2 on the SameStruct2Interface service.
    * Uses func2Async
    */
    Struct1 func2(const Struct1& param1, const Struct2& param2) override;
    /**
    * Remote call of ISameStruct2Interface::func2 on the SameStruct2Interface service.
    */
    QtPromise::QPromise<Struct1> func2Async(const Struct1& param1, const Struct2& param2);

signals:

    /**
    * Informs if the OLinkSameStruct2Interface is ready to send and receive messages.
    */
    void isReady();
public:

    /**
    * The name of the object for which this sink is created, object on server side has to have the same name.
    * It serves as an identifier for the client registry, it has to be unique for the pair sink object - client node.
    * Passed in the olink messages as an object identifier.
    */
    std::string olinkObjectName() override;

    /**
    * Information about signal emission on a server side to all subscribers.
    * @param signalId Unique identifier for the signal emitted from object.
    * @param args The arguments for the signal.
    */
    void olinkOnSignal(const std::string& signalId, const nlohmann::json& args) override;

    /**
    * Applies the information about the property changed on server side.
    * @param propertyId Unique identifier of a changed property in object .
    * @param value The value of the property.
    */
    void olinkOnPropertyChanged(const std::string& propertyId, const nlohmann::json& value) override;

    /** Informs this object sink that connection was is established.
    * @param interfaceId The name of the object for which link was established.
    * @param props Initial values obtained from the SameStruct2Interface service
    * @param the initialized link endpoint for this sink.
    */
    void olinkOnInit(const std::string& objectId, const nlohmann::json& props, ::ApiGear::ObjectLink::IClientNode *node) override;
    /**
    * Informs this object sink that the link was disconnected and cannot be used anymore.
    */
    void olinkOnRelease() override;
private:
    /**
    * Applies received data to local state and publishes changes to subscribers.
    * @param the data received from SameStruct2Interface service.
    */
    void applyState(const nlohmann::json& fields);
    /**  Updates local value for Prop1 and informs subscriber about the change with emit property changed signal. */
    void setProp1Local(const Struct2& prop1);
    /** A local value for prop1 */
    Struct2 m_prop1;
    /**  Updates local value for Prop2 and informs subscriber about the change with emit property changed signal. */
    void setProp2Local(const Struct2& prop2);
    /** A local value for prop2 */
    Struct2 m_prop2;
    /** An indicator if the object is linked with the service. */
    bool m_isReady;
    /** 
    * An abstraction layer over the connection with service for the OLinkSameStruct2Interface.
    * Handles incoming and outgoing messages.
    * Is given when object is linked with the service.
    */
    IClientNode *m_node;
};

} //namespace tb_same1
