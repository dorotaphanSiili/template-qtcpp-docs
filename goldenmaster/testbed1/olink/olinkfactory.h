#pragma once

#include <QtCore>

#include "testbed1/api/apifactory.h"
#include "olink/clientnode.h"

class OLinkFactory : public QObject, public ApiFactoryInterface
{
public:
    OLinkFactory(ApiGear::ObjectLink::ClientRegistry& registry, QObject *parent = nullptr);
    AbstractStructInterface* createStructInterface(QObject *parent) override;
    AbstractStructArrayInterface* createStructArrayInterface(QObject *parent) override;
private:
ApiGear::ObjectLink::ClientRegistry& m_registry;
};
