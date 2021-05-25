/**
 * @file drone.h
 */
#ifndef DRONE_H
#define DRONE_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity/entity_base.h"
#include "entity/package_carrier.h"
#include "entity/battery.h"
//#include "strategy/strategy.h"

#include "json_helper.h"
#include "delivery_instance.h"
#include "delivery_scheduler.h"

#include <vector>
#include <string>

namespace csci3081 {
class DeliveryInstance;
class Package;
class Customer;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Drone entity for our simulation. Drones transport packages to customers
 */
class Drone : public csci3081::PackageCarrier {
 public:
  /// Destructor that does nothing currently
  ~Drone();
  /**
   * Constructor extending parent constructor. 
   *
   * Calls entity base constructor. Initializes all of our regular values. 
   * Sets carrier and payload to be null, smart to be false 
   */
  Drone(const picojson::object& details);

  /// Gets whether or not our drone is smart
  bool getSmart();

  /// Sets whether or not our drone is smart
  void setSmart(bool smart);

  /**
   * @brief Updates the position of the drone for our simulation. Only moves
   * if a package has been set for the drone. 
   *
   * The path variable is a set of positions that we must travel to complete the 
   * delivery. Upon reaching each position, we update package state, and update 
   * delivery state. 
   *
   * Upon completion of the delivery, we set payload and customer to be nullptr. 
   */
  void update(float dt);
  /**
  * @brief Updates the position and direction of drone to make it fall to the ground. 
  * This is used when a drone runs out of battery and becomes idle. 
  */


  


 private:
   bool smart_;          ///< Bool determining if our drone takes the smart path
   //Strategy* routeStrategy;
   ///< declaring fall method that will be used to make the package drop when entity dies
   void fall(float dt){ 
     vector3D sub(0,-dt * 10,0); 
     addPositionVec(&sub);
     
     vector3D dir(1, 0, 0);
     setDirection(&dir);
   }
 
};

}

#endif
