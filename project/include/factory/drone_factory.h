/**
 * @file drone_factory.h
 */
#ifndef DRONE_FACTORY_H
#define DRONE_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "entity/drone.h"
#include "entity/decorated_carrier.h"

//#include "entity/package_carrier.h"

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Factory class for creating drones.
 */
class DroneFactory : public IEntityFactory {
    public: 
    /**
     * @brief Creates a drone if and only if the picojson object requests a drone
     */
    IEntity* CreateEntity(const picojson::object& val){
        if(JsonHelper::GetString(val, "type") == "drone"){
            PackageCarrier* res = new Drone(val);
            if(JsonHelper::ContainsKey(val, "colored") && JsonHelper::GetString(val, "colored") == "true") res = new DecoratedCarrier(res);
            return res;
        }         
        else return nullptr;
    }
};
}

#endif