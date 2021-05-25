/**
 * @file package.h
 */
#ifndef PACKAGE_H
#define PACKAGE_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity/entity_base.h"
#include "entity/observer_subject.h"
#include "json_helper.h"
#include "delivery_instance.h"

#include <vector>
#include <string>

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Package entity for our simulation.
 */

class Package : public csci3081::EntityBase, public csci3081::ObserverSubject{
  // TODO: Add documentation to these functions
  public:
  /// Package destructor. Does nothing currently
  ~Package() {};
  
  /** 
   * Package constructor. 
   * 
   * Calls default constructor, as well as setting customer and carrier to be null. Sets weigth to 1
   */
  Package(const picojson::object& details);

  /// Gets position vector for this package. 
  vec* getPosition() {return position_;}

  /// Gets the customer for this package.
  EntityBase* getCustomer();

  /// Gets the carrier for this package.
  EntityBase* getCarrier();

  /// Gets package weight
  float getWeight();

  /// Sets package weight
  void setWeight(float w);

  /**
   * @brief Updates the position of the package. 
   *
   * Moves to the same position as the carrier if and only if the carrier is not a null pointer. 
   */
  void update(float dt);

  /**
   * @brief Assigns the delivery_ variable to have value delivery
   */
  void scheduleDelivery(DeliveryInstance* delivery);

  /**
   * @brief Sets our package as having been completely delivered
   */
  void setDelivered();

  /**
   * @brief Notifies the simulation that our package has been scheduled for delivery
   */
  void notifyScheduled();

  /**
   * @brief Notifies the simulation that our package has been picked up
   */
  void notifyPickedUp();

  /**
   * @brief Notifies the simulation that our package has been successfully delivered
   */
  void notifyDelivered();

   /**
   * @brief Function allowing the package carrier to be observed. 
   *
   * Necessary so that this can be called polymorphically for the packageCarrier class
   * within delivery_simulation.cc
   */
  void addObserver(IEntityObserver* observer);
  /**
  * @brief simulates the package being dropped when a package carrier that's carrying it goes idle
  */
  void fall(float dt){ vector3D pos = getPosition(); setPosition(pos.getX(), pos.getY() - dt * 25, pos.getZ());}
    /**
  * @brief returns whether a package has fallen
  */
  bool getFalling(){ return falling_;}
  private: 

  DeliveryInstance* delivery_; // Delivery that our package is scheduled to be a member of
  float weight_;        /// Package weight with a default of 1. 
  bool falling_;

  /// Sets position vector for this package.
  void setPosition(vec* pos);

  /// Sets position vector using three integers
  void setPosition(int x, int y, int z);

  /// Sets position vector using three integers
  void setPosition(std::vector<float> vec);
};

}

#endif
