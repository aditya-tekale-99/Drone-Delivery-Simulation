/**
 * @file customer.h
 */
#ifndef CUSTOMER_H
#define CUSTOMER_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity/entity_base.h"
#include "json_helper.h"

#include <vector>
#include <string>

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Customer entity from our simulation. 
 */ 

class Customer : public csci3081::EntityBase {
 public:
  /// Destructor method. Deletes position and direction.
  ~Customer() {delete position_; delete direction_;};
  /// Constructs a customer by calling the entity base default constructor
  Customer(const picojson::object& details);
  /// Customers do not move, so does nothing. 
  void update(float dt) {}
};

}

#endif