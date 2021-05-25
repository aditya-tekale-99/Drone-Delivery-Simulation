#include "entity/package.h"

namespace csci3081{

Package::Package(const picojson::object& details) : EntityBase(details) {
  weight_ = 1;
  delivery_ = nullptr;
  falling_ = false;
}

void Package::setPosition(vec* pos){
  JsonHelper::AddStdFloatVectorToJsonObject(details_, "position", pos->getPositionAsVector());
  position_->setVector(pos);
  return;
}

void Package::setPosition(int x, int y, int z){
  position_->setVector(x, y, z);
  return;
}

void Package::setPosition(std::vector<float> pos){
  position_->setVector(pos);
  return;
}

EntityBase* Package::getCustomer(){ 
  if(delivery_ != nullptr) return &delivery_->getCustomer();
  else return nullptr;
}

EntityBase* Package::getCarrier() { 
  if(delivery_ != nullptr) return delivery_->getCarrier();
  else return nullptr;
}

float Package::getWeight() {return weight_;};

void Package::setWeight(float weight){ weight_ = weight;}

void Package::update(float dt){
  if(delivery_ != nullptr){
    EntityBase* carrier = delivery_->getCarrier();
    EntityBase* customer = &delivery_->getCustomer();
    if(delivery_->getIsPickedUp()){
      setPosition(carrier->GetPosition());
    } else {
      if(IsColliding(carrier)){ delivery_->setIsPickedUp(); notifyPickedUp();}
    }

    if(IsColliding(customer)){
      notifyDelivered();
      delivery_->setisDelivered(true);
      setDelivered();
    }
  } else if(position_->getY() > 258){
    falling_ = true;
    fall(dt);
  } else{
    falling_ = false;
  }
}

void Package::scheduleDelivery(DeliveryInstance* delivery){
  if(delivery != nullptr) notifyScheduled();
  else falling_ = true;
  delivery_ = delivery;
} 

void Package::setDelivered(){
  vector3D res(-9999, -9999, -9999);
  delivery_->setisDelivered(true);
  setPosition(&res);
}

void Package::notifyScheduled() {
  picojson::object obj = buildNotification("scheduled");
  notify(obj, this);
}

void Package::notifyPickedUp() {
  picojson::object obj = buildNotification("en route");
  notify(obj, this);
}

void Package::notifyDelivered() {
  picojson::object obj = buildNotification("delivered");
  notify(obj, this);
}

void Package::addObserver(IEntityObserver* observer){
  if(observer != nullptr) AddObserver(*observer); 
}
}