/**
 * @file customer_factory.h
 */
#ifndef CUSTOMER_FACTORY_H
#define CUSTOMER_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "entity/customer.h"

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Factory class that creates customer entities
 * 
 */

class CustomerFactory : public IEntityFactory {
    public: 
    /**
     * @brief Creates a customer if and only if the picojson object requests a customer
     */
    IEntity* CreateEntity(const picojson::object& val){
        if(JsonHelper::GetString(val, "type") == "customer") return new Customer(val);
        else return nullptr;
    };
};
}

#endif