/**
 * @file package_factory.h
 */
#ifndef PACKAGE_FACTORY_H
#define PACKAGE_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "entity/package.h"

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Factory for creating packages. 
 */
class PackageFactory : public IEntityFactory{
    public: 
    /**
     * @brief Creates a package if and only if the picojson object requests a package
     */
    IEntity* CreateEntity(const picojson::object& val){
        if(JsonHelper::GetString(val, "type") == "package") return new Package(val);
        else return nullptr;
    };
};
}

#endif