/**
 * @file robot_factory.h
 */
#ifndef ROBOT_FACTORY_H
#define ROBOT_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "entity/robot.h"
#include "entity/decorated_carrier.h"

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Factory class for creating robots.
 */
class RobotFactory : public IEntityFactory {
    public: 
    /**
     * @brief Creates a robot if and only if the picojson object requests a robot
     */
    IEntity* CreateEntity(const picojson::object& val){
        if(JsonHelper::GetString(val, "type") == "robot"){
            PackageCarrier* res = new Robot(val);
            if(JsonHelper::ContainsKey(val, "colored") && JsonHelper::GetString(val, "colored") == "true") res = new DecoratedCarrier(res);
            return res;
        } 
        else return nullptr;
    };
};
}

#endif
