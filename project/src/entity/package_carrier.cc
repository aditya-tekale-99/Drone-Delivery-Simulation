#include "entity/package_carrier.h"

#include <utility>


namespace csci3081 {

PackageCarrier::~PackageCarrier(){}

PackageCarrier::PackageCarrier(const picojson::object& details) : EntityBase(details) {
  speed_ = JsonHelper::GetDouble(details, "speed");
  delivery_ = nullptr;
  packagePickedUp_ = false;
  isIdle_ = false;

  double batteryCapacity;
  if(JsonHelper::ContainsKey(details, "battery_capacity")) batteryCapacity = JsonHelper::GetDouble(details, "battery_capacity");
  else batteryCapacity = 10000.0;
  battery_.setCharge(batteryCapacity);

}

EntityBase* PackageCarrier::getPayload(){
  if(delivery_ == nullptr) return nullptr;
  else return &delivery_->getPackage();
}

EntityBase* PackageCarrier::getCustomer(){
  if(delivery_ == nullptr) return nullptr;
  else return &delivery_->getCustomer();
}

vec* PackageCarrier::getPositionVec(){
  return this->position_;
}

void PackageCarrier::setPositionVec(vec* position){
  position_->setVector(position);
  return;
}

void PackageCarrier::addPositionVec(vec* position){
  this->position_->add(position);
  this->setPositionVec(position_);
  return;
}

void PackageCarrier::setDirection(vec* direction){
  direction_->setVector(direction);
  return;
}

float PackageCarrier::getSpeed() const{
  return speed_;
}

void PackageCarrier::addObserver(IEntityObserver* observer){
    if(observer != nullptr) AddObserver(*observer); 
  }

void PackageCarrier::notifyMoving(std::vector<vector<float>>& path) {
  picojson::object obj = buildNotification("moving", path);
  notify(obj, this);
}

void PackageCarrier::notifyIdle() {
  picojson::object obj = buildNotification("idle");
  notify(obj, this);
}

void PackageCarrier::setDeliveryInvalid() {
  delivery_ -> setisValid();
}

bool PackageCarrier::getIsIdle(){
	return isIdle_;
}

void PackageCarrier::setIsIdle(){
	this->isIdle_ = true;
}

void PackageCarrier::cutPathInHalf(std::vector<std::vector<float>> path, EntityBase* package) {
  std::vector<std::vector<float>> v1, v2;
  vector3D vec = package->GetPositionVec();
  for(auto it = path.begin(); it != path.end(); it++){
    vector3D pos(*it);
    if(pos.distance(&vec) < 0.01){
      startPath_.assign(path.begin(), it);
      endPath_.assign(it, path.end());
    }
  }
}

void PackageCarrier::scheduleDelivery(DeliveryInstance* delivery){
  delivery_ = delivery;
  if (delivery != nullptr){
    cutPathInHalf(delivery->getPath(), &delivery->getPackage());
    notifyMoving(startPath_);
    isIdle_ = false;
  } 
}

void PackageCarrier::pickUpPackage(){
  if(IsColliding(getPayload()) && !packagePickedUp_) {
    notifyMoving(endPath_);
    packagePickedUp_ = true;
  }
}

}
