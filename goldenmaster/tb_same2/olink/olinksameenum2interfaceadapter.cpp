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



#include "olinksameenum2interfaceadapter.h"

#include <nlohmann/json.hpp>
#include "tb_same2/api/json.adapter.h"

#include "olink/remoteregistry.h"
#include "olink/iremotenode.h"

#include <QtCore>

using namespace ApiGear::ObjectLink;

using json = nlohmann::json;

namespace tb_same2 {

OLinkSameEnum2InterfaceAdapter::OLinkSameEnum2InterfaceAdapter(RemoteRegistry& registry, AbstractSameEnum2Interface* impl, QObject *parent)
    : QObject(parent)
    , m_impl(impl)
    , m_registry(registry)
{
    connect(m_impl, &AbstractSameEnum2Interface::prop1Changed, this,
        [=](Enum1::Enum1Enum prop1) {
        const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
        for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(propertyId))) {
            auto lockedNode = node.lock();
            if(lockedNode) {
                lockedNode->notifyPropertyChange(propertyId, prop1);
            }
        }
    });
    connect(m_impl, &AbstractSameEnum2Interface::prop2Changed, this,
        [=](Enum2::Enum2Enum prop2) {
        const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop2");
        for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(propertyId))) {
            auto lockedNode = node.lock();
            if(lockedNode) {
                lockedNode->notifyPropertyChange(propertyId, prop2);
            }
        }
    });
        connect(m_impl, &AbstractSameEnum2Interface::sig1, this,
            [=](Enum1::Enum1Enum param1) {
                const nlohmann::json& args = { param1 };
                const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sig1");
                for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(signalId))) {
                    auto lockedNode = node.lock();
                    if(lockedNode) {
                        lockedNode->notifySignal(signalId, args);
                    }
                }
    });
        connect(m_impl, &AbstractSameEnum2Interface::sig2, this,
            [=](Enum1::Enum1Enum param1, Enum2::Enum2Enum param2) {
                const nlohmann::json& args = { param1, param2 };
                const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sig2");
                for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(signalId))) {
                    auto lockedNode = node.lock();
                    if(lockedNode) {
                        lockedNode->notifySignal(signalId, args);
                    }
                }
    });
}

json OLinkSameEnum2InterfaceAdapter::captureState()
{
    return json::object({
        { "prop1", m_impl->prop1() },
        { "prop2", m_impl->prop2() }
    });
}

void OLinkSameEnum2InterfaceAdapter::applyState(const json& state)
{
    if(state.contains("prop1")) {
        m_impl->setProp1(state["prop1"]);
    }
    if(state.contains("prop2")) {
        m_impl->setProp2(state["prop2"]);
    }
}


std::string OLinkSameEnum2InterfaceAdapter::olinkObjectName() {
    return "tb.same2.SameEnum2Interface";
}

json OLinkSameEnum2InterfaceAdapter::olinkInvoke(const std::string& methodId, const nlohmann::json& args){
    qDebug() << Q_FUNC_INFO << QString::fromStdString(methodId);
    std::string path = Name::getMemberName(methodId);
    if(path == "func1") {
        const Enum1::Enum1Enum& param1 = args.at(0);
        Enum1::Enum1Enum result = m_impl->func1(param1);
        return result;
    }
    if(path == "func2") {
        const Enum1::Enum1Enum& param1 = args.at(0);
        const Enum2::Enum2Enum& param2 = args.at(1);
        Enum1::Enum1Enum result = m_impl->func2(param1, param2);
        return result;
    }
    return json();
}

void OLinkSameEnum2InterfaceAdapter::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value){
    qDebug() << Q_FUNC_INFO << QString::fromStdString(propertyId);
    std::string path = Name::getMemberName(propertyId);
    if(path == "prop1") {
        Enum1::Enum1Enum prop1 = value.get<Enum1::Enum1Enum>();
        m_impl->setProp1(prop1);
    }
    if(path == "prop2") {
        Enum2::Enum2Enum prop2 = value.get<Enum2::Enum2Enum>();
        m_impl->setProp2(prop2);
    }    
}

void OLinkSameEnum2InterfaceAdapter::olinkLinked(const std::string& objectId, IRemoteNode *node) {
    qDebug() << Q_FUNC_INFO << QString::fromStdString(objectId);
}

void OLinkSameEnum2InterfaceAdapter::olinkUnlinked(const std::string& objectId)
{
    qDebug() << Q_FUNC_INFO << QString::fromStdString(objectId);
}

json OLinkSameEnum2InterfaceAdapter::olinkCollectProperties()
{
    return captureState();
}

} // namespace tb_same2
