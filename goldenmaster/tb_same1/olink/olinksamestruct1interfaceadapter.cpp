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



#include "olinksamestruct1interfaceadapter.h"

#include <nlohmann/json.hpp>
#include "tb_same1/api/json.adapter.h"

#include "olink/remoteregistry.h"
#include "olink/iremotenode.h"

#include <QtCore>

using namespace ApiGear::ObjectLink;

using json = nlohmann::json;

namespace tb_same1 {

OLinkSameStruct1InterfaceAdapter::OLinkSameStruct1InterfaceAdapter(RemoteRegistry& registry, AbstractSameStruct1Interface* impl, QObject *parent)
    : QObject(parent)
    , m_impl(impl)
    , m_registry(registry)
{
    connect(m_impl, &AbstractSameStruct1Interface::prop1Changed, this,
        [=](const Struct1& prop1) {
        const auto& propertyId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "prop1");
        for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(propertyId))) {
            auto lockedNode = node.lock();
            if(lockedNode) {
                lockedNode->notifyPropertyChange(propertyId, prop1);
            }
        }
    });
        connect(m_impl, &AbstractSameStruct1Interface::sig1, this,
            [=](const Struct1& param1) {
                const nlohmann::json& args = { param1 };
                const auto& signalId = ApiGear::ObjectLink::Name::createMemberId(olinkObjectName(), "sig1");
                for(auto node: m_registry.getNodes(ApiGear::ObjectLink::Name::getObjectId(signalId))) {
                    auto lockedNode = node.lock();
                    if(lockedNode) {
                        lockedNode->notifySignal(signalId, args);
                    }
                }
    });
}

json OLinkSameStruct1InterfaceAdapter::captureState()
{
    return json::object({
        { "prop1", m_impl->prop1() }
    });
}

void OLinkSameStruct1InterfaceAdapter::applyState(const json& state)
{
    if(state.contains("prop1")) {
        m_impl->setProp1(state["prop1"]);
    }
}


std::string OLinkSameStruct1InterfaceAdapter::olinkObjectName() {
    return "tb.same1.SameStruct1Interface";
}

json OLinkSameStruct1InterfaceAdapter::olinkInvoke(const std::string& methodId, const nlohmann::json& args){
    qDebug() << Q_FUNC_INFO << QString::fromStdString(methodId);
    std::string path = Name::getMemberName(methodId);
    if(path == "func1") {
        const Struct1& param1 = args.at(0);
        Struct1 result = m_impl->func1(param1);
        return result;
    }
    return json();
}

void OLinkSameStruct1InterfaceAdapter::olinkSetProperty(const std::string& propertyId, const nlohmann::json& value){
    qDebug() << Q_FUNC_INFO << QString::fromStdString(propertyId);
    std::string path = Name::getMemberName(propertyId);
    if(path == "prop1") {
        Struct1 prop1 = value.get<Struct1>();
        m_impl->setProp1(prop1);
    }    
}

void OLinkSameStruct1InterfaceAdapter::olinkLinked(const std::string& objectId, IRemoteNode *node) {
    qDebug() << Q_FUNC_INFO << QString::fromStdString(objectId);
}

void OLinkSameStruct1InterfaceAdapter::olinkUnlinked(const std::string& objectId)
{
    qDebug() << Q_FUNC_INFO << QString::fromStdString(objectId);
}

json OLinkSameStruct1InterfaceAdapter::olinkCollectProperties()
{
    return captureState();
}

} // namespace tb_same1
