/**
 * @file package_carrier.h
 */
#ifndef PACKAGE_CARRIER_H
#define PACKAGE_CARRIER_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity/entity_base.h"
#include "entity/observer_subject.h"
#include "delivery_instance.h"
//#include "strategy/strategy.h"

#include "json_helper.h"
#include "battery.h"

#include <vector>
#include <string>

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Drone entity for our simulation. Drones transport packages to customers
 */
class PackageCarrier : public csci3081::EntityBase, public csci3081::ObserverSubject {
 public:
  /// Destructor that does nothing currently
  ~PackageCarrier();
  /**
   * Constructor extending parent constructor. 
   *
   * Calls entity base constructor. Initializes all of our regular values. 
   * Sets carrier and payload to be null, smart to be false 
   */
  PackageCarrier(const picojson::object& details);

  /// Get the customer Customer* of our drone
  EntityBase* getCustomer();

  /// Get the speed of our drone;
  float getSpeed() const;

  /// Get the associated Battery for the package carrier
  Battery getBattery() { return battery_;}

  /// Get the associated DeliveryInstance for the package carrier
  DeliveryInstance* getDelivery() {return delivery_;}

  /**
   * @brief Returns the position vec pointer for this drone
   */
  vec* getPositionVec();

  /**
   * @brief Updates the position of the drone for our simulation. Only moves
   * if a package has been set for the drone. 
   *
   * The path variable is a set of positions that we must travel to to complete the 
   * delivery. Upon reaching each position, we update package state, and update 
   * delivery state. 
   *
   * Upon completion of the delivery, we set payload and customer to be nullptr. 
   */
  virtual void update(float dt) = 0;

   /**
   * @brief Schedules a delivery. 
   *
   * Does so by setting the package variable, the customer variable, and the path variable. 
   */
  void scheduleDelivery(DeliveryInstance* delivery);

  /**
   * @brief Function allowing the package carrier to be observed. 
   *
   * Necessary so that this can be called polymorphically for the packageCarrier class
   * within delivery_simulation.cc
   */
  void addObserver(IEntityObserver* observer);

  /**
   * @brief Sets state of delivery to be invalid. This is used by scheduler to unschedule if carrier is dead
   */  
  void setDeliveryInvalid();

  /**
   * @brief Sets the drone to be idle
  */
  void setIsIdle();  

  /**
   * @brief gets the idle status of the drone
   */
  bool getIsIdle();

  /// Sends a notification to observers to indicate carrier is idle
  void notifyIdle();
  /**
   * @brief Sets the drone to be idle
  */
  void pickUpPackage();
  /// Returns true if package was picked up
  bool getPackagePickedUp(){ return packagePickedUp_; }

 protected:
  float speed_;         ///< speed of our drone
  Battery battery_;     ///< Our Drones battery
  DeliveryInstance* delivery_; ///< Delivery variable helping our drone keep track of current delivery
   /// Variable telling us if the carrier is out of battery
  bool isIdle_;
  /// Variable telling us if the package has been picked up
  bool packagePickedUp_; 
  /// Temp variable used to store path from drone to package
  std::vector<std::vector<float>> startPath_; 
  /// Temp variable used to store path from package to customer
  std::vector<std::vector<float>> endPath_; 

    /**
   * @brief Adds to the vector position pointer for this vector
   */
  void addPositionVec(vec* position);

  /**
   * @brief Sets the directions vector pointer for this drone
   */
  void setDirection(vec* direction);
  
private:
  
  /// Get the payload Package* of our drone
  EntityBase* getPayload();
  
  /**
   * @brief Takes in the total path, uses it to assign a startPath_ and an endPath_ variable used in notifications
   *
   * required to fix bug whereby large notifications were breaking the simulation
  */
  void cutPathInHalf(std::vector<std::vector<float>> path, EntityBase* package);
    
  void notifyMoving(std::vector<vector<float>>& path);

  /**
   * @brief Sets the vector direction pointer for this drone
   */
  void setPositionVec(vec* position);

};

}

#endif
