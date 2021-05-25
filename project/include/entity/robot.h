/**
 * @file robot.h
 */
#ifndef ROBOT_H
#define ROBOT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity/package_carrier.h"
#include "entity/battery.h"

#include "json_helper.h"
#include "delivery_instance.h"

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
 * @brief Robot entity for our simulation. Robots transport packages to customers
 */
class Robot : public csci3081::PackageCarrier {
 public:
  /// Destructor that does nothing currently
  ~Robot();
  /**
   * Constructor extending parent constructor. 
   *
   * Calls entity base constructor. Initializes all of our regular values. 
   * Sets carrier and payload to be null, smart to be false 
   */
  Robot(const picojson::object& details);

  /// Gets whether or not our robot is smart
  bool getSmart();

  /// Sets whether or not our robot is smart
  void setSmart(bool smart);

  /**
   * @brief Updates the position of the robot for our simulation. Only moves
   * if a package has been set for the robot. 
   *
   * The path variable is a set of positions that we must travel to to complete the 
   * delivery. Upon reaching each position, we update package state, and update 
   * delivery state. 
   *
   * Upon completion of the delivery, we set payload and customer to be nullptr. 
   */
  void update(float dt);



 private:
  bool smart_;          ///< Bool determining if our robot takes the smart path
};

}

#endif
