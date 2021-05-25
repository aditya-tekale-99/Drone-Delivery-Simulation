#include "delivery_instance.h"

namespace csci3081{
DeliveryInstance::DeliveryInstance(EntityBase& carrier, EntityBase& package, EntityBase& customer, std::vector<std::vector<float>> path) : 
    carrier_(&carrier), package_(package), customer_(customer) {
    path_ = path;
    isPickedUp_ = false;
    isValid_ = true;
    isDelivered_ = false;
}
EntityBase& DeliveryInstance::getPackage() { return package_;}
EntityBase& DeliveryInstance::getCustomer() { return customer_; }
std::vector<std::vector<float>>& DeliveryInstance::getPath() {return path_; }
EntityBase* DeliveryInstance::getCarrier() { return carrier_; }
bool DeliveryInstance::getIsPickedUp() { return isPickedUp_; }
bool DeliveryInstance::setIsPickedUp() { isPickedUp_ = true; }
bool DeliveryInstance::getisValid() { return isValid_; }
bool DeliveryInstance::setisValid() { isValid_ = false; }

bool DeliveryInstance::getisDelivered() {return isDelivered_; }
bool DeliveryInstance::setisDelivered(bool status){ isDelivered_ = status;}

}

