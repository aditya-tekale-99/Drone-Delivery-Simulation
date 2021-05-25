/**
 * @file delivery_instance.h
 */
#ifndef DELIVERY_INSTANCE_H
#define DELIVERY_INSTANCE_H
/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <vector>
#include "entity/entity_base.h"

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class is the delivery instance
 */

class DeliveryInstance{
    public:
    /// @brief Constructor: Takes in a package carrier, a package, a customer, and a path and assigns them to the respective member variables
    DeliveryInstance(EntityBase& carrier, EntityBase& package, EntityBase& customer, std::vector<std::vector<float>> path);
    /// gets the package function 
    EntityBase& getPackage();
    /// gets the customer function
    EntityBase& getCustomer();
    /// gets the path that the entity will take
    std::vector<std::vector<float>>& getPath();
    /// gets the carrier function
    EntityBase* getCarrier();
    /// bool: gets the IsPickedUp function
    bool getIsPickedUp();
    /// bool: sets the IsPickedUp value
    bool setIsPickedUp();
    /// bool: gets the value of isValid based on the state of the drone
    bool getisValid();
    /// bool: sets the value of the drone/robot based on the isValid value when its called
    bool setisValid();
    /// bool: gets is delivered status
    bool getisDelivered();
    /// bool: sets is delivered status based on weather the package is delivered or not
    bool setisDelivered(bool status);

    protected:
    EntityBase& package_; ///< Package from the entitybase
    EntityBase& customer_; ///< customer from the entity base
    EntityBase* carrier_; ///< carrier that could be either drone or robot 
    std::vector<std::vector<float>> path_; ///< path that the entity could take
    bool isPickedUp_; ///< bool: used for picking up the package
    bool isValid_; ///< bool: gets the value as either true or false based on the status of drone/robot
    bool isDelivered_; ///< bool: returns true when package is delivered
};

}

#endif
