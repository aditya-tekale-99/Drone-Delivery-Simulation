#include "entity/battery.h"

namespace csci3081{
    
Battery::Battery(){
    maxCharge_ = 10000.0;
    isCharging_ = false;
}
//battery capacity is set to a 10000.0
Battery::Battery(double capacity){
    maxCharge_ = 10000.0;
    charge_ = std::min(10000.0, std::max(capacity, 0.0)); 
    isCharging_ = false;
}

bool Battery::getIsCharging() const{
    return isCharging_;
}

void Battery::setIsCharging(bool isCharging){
    isCharging_ = isCharging;
}

float Battery::getCharge() const{
    return charge_;
}

void Battery::setCharge(float charge){
    charge_ = charge;
}

bool Battery::getIsDead() const{
    return charge_ <= 0.1;
}
//updates the battery life by subtracting the charge with the distance 
void Battery::update(float distance){
    charge_ = std::max((float)0.0, charge_-distance);
}

}
