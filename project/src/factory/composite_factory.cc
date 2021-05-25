#include "factory/composite_factory.h"

namespace csci3081{

CompositeFactory::~CompositeFactory(){
    for(auto factory: factories_) delete factory;
}

IEntity* CompositeFactory::CreateEntity(const picojson::object& val){
    IEntity* res;
    for(auto factory : factories_){
        res = factory->CreateEntity(val);
        if (res != nullptr)  return res;
    }
    return nullptr;
}

void CompositeFactory::addFactory(IEntityFactory* factory){
    factories_.push_back(factory);
}

}