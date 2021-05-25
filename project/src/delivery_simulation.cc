#include "delivery_simulation.h"

#include "iostream"

namespace csci3081 {

DeliverySimulation::DeliverySimulation() : scheduler_( (this->entities_) ) {
	IEntityFactory* append;
	append = new DroneFactory();
	this->AddFactory(append);
	append = new RobotFactory();
	this->AddFactory(append);
	append = new CustomerFactory();
	this->AddFactory(append);
	append = new PackageFactory();
	this->AddFactory(append);
}

DeliverySimulation::~DeliverySimulation() {
	for(auto entity : entities_) delete entity;
}

IEntity* DeliverySimulation::CreateEntity(const picojson::object& val) {
  //TODO for lab10: replace the ?????'s with the appropriate values,
  //  then uncomment the section of code
  IEntity* res = compositefactory_.CreateEntity(val);
  JsonHelper::Print(val);
  return res;
  
}

void DeliverySimulation::AddFactory(IEntityFactory* factory) {
	compositefactory_.addFactory(factory);
}

void DeliverySimulation::AddEntity(IEntity* entity) { 
  //TODO for lab10: One line of code
  if(entity != nullptr) {
	entities_.push_back(entity);

	for(auto observer : entityObservers_) dynamic_cast<EntityBase*>(entity)->addObserver(observer);
  }
}

void DeliverySimulation::SetGraph(const IGraph* graph) {
	scheduler_.setGraph(graph);
}

void DeliverySimulation::ScheduleDelivery(IEntity* package, IEntity* dest) {
	if(package == nullptr || dest == nullptr){
		std::cout << "error null scheduled\n";
	} else{
		scheduler_.ScheduleDelivery(package, dest);	
	}
}

void DeliverySimulation::AddObserver(IEntityObserver* observer) {
	entityObservers_.push_back(observer);
}

void DeliverySimulation::RemoveObserver(IEntityObserver* observer) {
	entityObservers_.erase(std::find(entityObservers_.begin(),entityObservers_.end(),observer));

	for(auto entity : entities_) dynamic_cast<EntityBase*>(entity)->removeObserver(observer);
}

const std::vector<IEntity*>& DeliverySimulation::GetEntities() const { return entities_; }

void DeliverySimulation::Update(float dt) {
	// Update position of my entities
	scheduler_.scheduleDeliveries();

	for(auto entity_stub : entities_){
  		const picojson::object& details = entity_stub->GetDetails();
		std::string type = JsonHelper::GetString(details, "type");
		dynamic_cast<EntityBase*>(entity_stub)->update(dt);
	}
	
	//scheduler_.scheduleDeliveries();
}


// DO NOT MODIFY THE FOLLOWING UNLESS YOU REALLY KNOW WHAT YOU ARE DOING
void DeliverySimulation::RunScript(const picojson::array& script, IEntitySystem* system) const {
  JsonHelper::PrintArray(script);
  IDeliverySystem* deliverySystem = dynamic_cast<IDeliverySystem*>(system);
	if (deliverySystem) {
	    // To store the unadded entities_
	    std::vector<IEntity*> created_entities;

		for (unsigned int i=0; i < script.size(); i++) {
			const picojson::object& object = script[i].get<picojson::object>();
			const std::string cmd = object.find("command")->second.get<std::string>();
			const picojson::object& params = object.find("params")->second.get<picojson::object>();
			// May want to replace the next few if-statements with an enum
			if (cmd == "createEntity") {
				IEntity* entity = NULL;
				entity = deliverySystem->CreateEntity(params);
				if (entity) {
					created_entities.push_back(entity);
				} else {
					std::cout << "Null entity" << std::endl;
				}
			}
			else if (cmd == "addEntity") {
				int ent_index = static_cast<int>(params.find("index")->second.get<double>());
				if (ent_index >= 0 && ent_index < created_entities.size()) {
					deliverySystem->AddEntity(created_entities[ent_index]);
				}
			}
			else if (cmd == "scheduleDelivery" ) {
				int pkg_index = static_cast<int>(params.find("pkg_index")->second.get<double>());
				int dest_index = static_cast<int>(params.find("dest_index")->second.get<double>());
				if (pkg_index >= 0 && pkg_index < system->GetEntities().size()) {
					IEntity* pkg = deliverySystem->GetEntities()[pkg_index];
					if (dest_index >= 0 && pkg_index < system->GetEntities().size()) {
						IEntity* cst = system->GetEntities()[dest_index];
						if (pkg && cst) {
							deliverySystem->ScheduleDelivery(pkg, cst);
						}
					}
				}
				else {
					std::cout << "Failed to schedule delivery: invalid indexes" << std::endl;
				}
			}
		}
	}
}

}
