#include "delivery_scheduler.h"
#include "strategy/strategy.h"
#include <limits>
#include <utility>
#include <queue>
#include <vector>

namespace csci3081{

void DeliveryScheduler::scheduleDeliveries(){
	// For each entity, if the entity is a carrier then we check 2 things. 
	// 1: customer == nullptr which implies that the carrier is free
	// 2: !schedule_.empty() which implies that there is a package to deliver
	
	unscheduleDeliveries();
	while(!schedule_.empty()){
		auto toSchedule = schedule_.front();
		Package* package = dynamic_cast<Package*>(toSchedule.first);
		Customer* customer = dynamic_cast<Customer*>(toSchedule.second);
		PackageCarrier* carrier = dynamic_cast<PackageCarrier*>(getClosestPackageCarrier(package));
		if(carrier == nullptr || package->getFalling()){
			break;
		} else{
			schedule_.pop();
			std::vector<std::vector<float>> path;
			//path = getSmartPath(carrier, package, customer);
			if (JsonHelper::ContainsKey(carrier->GetDetails(),"path")){ //check if path key exists in json
				if (JsonHelper::GetString(carrier->GetDetails(), "path") == "parabolic") { //check if path keys value is parabolic
					//JsonHelper::Print(carrier->GetDetails());
					path = parabolicRoute.getPath(carrier, package, customer); //return parabolic route
				} else if (JsonHelper::GetString(carrier->GetDetails(), "path") == "smart") { //check if path keys value is smart
					path = smartRoute.getPath(carrier, package, customer); //return smart route
				} else {
					path = beelineRoute.getPath(carrier, package, customer); //else return beeline route
				}
			} else {
				path = smartRoute.getPath(carrier, package, customer); //if path key doesn't exist make deliverer take smart route
			}
			//if(drone -> getSmart()) path = getSmartPath(drone, package, customer);
			//else path = getDumbPath(drone, package, customer);

			DeliveryInstance* delivery = new DeliveryInstance(*carrier, *package, *customer, path);
			package->scheduleDelivery(delivery);
			carrier->scheduleDelivery(delivery);
			
			deliveries_.push_back(delivery);
		}
	}
}

void DeliveryScheduler::unscheduleDeliveries(){
	for(auto deliveryIt = deliveries_.begin(); deliveryIt < deliveries_.end(); deliveryIt++){
		// if is delivered delete
		DeliveryInstance* delivery = *deliveryIt;

		EntityBase* customer, *package, *drone;
		customer = &delivery->getCustomer();
		package = &delivery->getPackage();
		drone = delivery->getCarrier();

		if(delivery->getisDelivered()){
			deliveryIt = deliveries_.erase(deliveryIt);
			package->scheduleDelivery(nullptr);
			drone->scheduleDelivery(nullptr);
		}
		// if not valid then set up new delivery
		else if(! delivery->getisValid()){
			// step 1: set the values for each variable
			package->scheduleDelivery(nullptr);
			drone->scheduleDelivery(nullptr);

			// step 2: push onto deliveries
			auto pair = std::make_pair(dynamic_cast<IEntity*>(package), dynamic_cast<IEntity*>(customer));
			schedule_.push(pair);

			// step 3: delete current delivery
			deliveryIt = deliveries_.erase(deliveryIt);
		}

	}
}


IEntity* DeliveryScheduler::getClosestPackageCarrier(IEntity* package){
	IEntity* closestCarrier = nullptr;
	vector3D packagePos(package->GetPosition());
	float maxDistance = std::numeric_limits<float>::max();

	for(IEntity* entity: entities_){
		if(JsonHelper::GetString(entity->GetDetails(), "type") == "drone" ||
		   JsonHelper::GetString(entity->GetDetails(), "type") == "robot"){
			PackageCarrier* carrier = dynamic_cast<PackageCarrier*>(entity);	
			if(carrier -> getCustomer() == nullptr && 
				carrier -> getIsIdle() == false
				){
				vector3D carrierPos(carrier->GetPosition());
				float distance = packagePos.distance(&carrierPos);
				if(distance < maxDistance){
					closestCarrier = entity;
					maxDistance = distance;
				}
			}
		}
	}

	return closestCarrier;
}

}
