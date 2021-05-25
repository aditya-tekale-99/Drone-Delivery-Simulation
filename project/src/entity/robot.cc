#include "entity/robot.h"
#include "../include/entity/battery.h"

#include <iostream>
namespace csci3081 {

Robot::~Robot(){}

Robot::Robot(const picojson::object& details) : PackageCarrier(details) {
  smart_ = true;
}

bool Robot::getSmart() {
  return smart_;
}

void Robot::setSmart(bool smart){
  this->smart_ = smart;
}

void Robot::update(float dt){
	if(delivery_ != nullptr && battery_.getIsDead() && !getIsIdle() ){
	        setIsIdle();
          notifyIdle();
          setDeliveryInvalid();
	  return;
    }
  else if(delivery_ != nullptr){
    const EntityBase& customer = delivery_->getCustomer();
    const EntityBase& package = delivery_->getPackage(); 
    vector<vector<float>>& path_ = delivery_->getPath();
    //if payload exists, then we have a path we can follow

    vector2D position(position_);
    vector2D destination(path_.back());
    pickUpPackage();

    // Begin to update our destination. If we are on destination
    // then we move to the next node. If we are out of nodes, 
    // or the package can sense that it is delivered, then we
    // can exit. 
    while( ( position.distance(&destination) ) < radius_){
      path_.pop_back();
      float res = position.distance(&destination);
      destination.setVector(path_.back()[0], path_.back()[1], path_.back()[2]);
    }

    // updates direction using vector subtraction, and scaling
    destination.subtract(this->position_);
    float distFrom = destination.magnitude();

    this->direction_->setVector(&destination);
    this->direction_->normalize(); 

    // updates position using direction, scaled by dt and speed_
    vector2D addVec(this->direction_);
    addVec.scale(std::min(dt*speed_, distFrom));
    addPositionVec(&addVec);
    battery_.update(addVec.magnitude());
  } else if(delivery_ == nullptr && isIdle_ == false && battery_.getIsDead()){
    setIsIdle();
  }
  return;
}


}
