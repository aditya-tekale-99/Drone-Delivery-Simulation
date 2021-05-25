#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include "../include/delivery_simulation.h"
#include <EntityProject/entity.h>
#include "json_helper.h"
#include "../include/factory/composite_factory.h"
#include "../include/factory/customer_factory.h"
#include "../include/factory/package_factory.h"
#include "../include/factory/drone_factory.h"


#include <iostream>

namespace csci3081 {

using entity_project::IEntity;

class FactoryTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    system = dynamic_cast<IDeliverySystem*>(GetEntitySystem("default"));
  }
  virtual void TearDown() {}

  IDeliverySystem* system;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(FactoryTest, FactoryCreated) {
  picojson::object obj = JsonHelper::CreateJsonObject();
  JsonHelper::AddStringToJsonObject(obj, "name", "king");
  JsonHelper::AddStringToJsonObject(obj, "type", "drone");

  std::vector<float> position_to_add {323.12, 232.1, -232.34};
  std::vector<float> direction_to_add {1, 0, 0};

  JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
  JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
  JsonHelper::AddFloatToJsonObject(obj, "speed", 2.1);


  	IEntityFactory* droneFactory = new DroneFactory();
    IEntityFactory* customerFactory = new CustomerFactory();
    IEntityFactory* packageFactory = new PackageFactory();
    IEntityFactory* robotFactory = new RobotFactory();

    CompositeFactory compositeFactory;

    EXPECT_TRUE(compositeFactory.CreateEntity(obj) == nullptr);

    compositeFactory.addFactory(droneFactory);
    compositeFactory.addFactory(customerFactory);
    compositeFactory.addFactory(packageFactory);
    compositeFactory.addFactory(robotFactory);


  IEntity* entity1 = compositeFactory.CreateEntity(obj);
  ASSERT_NE(entity1, nullptr) << "The entity created";
  system->AddEntity(entity1);
  ASSERT_EQ(1, system->GetEntities().size()) << "Entity not inserting into the system properly";
  ASSERT_FLOAT_EQ(entity1->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity1->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity1->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity1->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity1->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity1->GetDirection()[2], direction_to_add[2]);
  ASSERT_EQ(picojson::value(system->GetEntities()[0]->GetDetails()).serialize(), picojson::value(obj).serialize());


  JsonHelper::AddStringToJsonObject(obj, "type", "customer");
  IEntity* entity2 = customerFactory->CreateEntity(obj);
  ASSERT_NE(entity2, nullptr) << "The entity created";
  system->AddEntity(entity2);
  ASSERT_EQ(2, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity2->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity2->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity2->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity2->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity2->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity2->GetDirection()[2], direction_to_add[2]);

  JsonHelper::AddStringToJsonObject(obj, "type", "package");
  IEntity* entity3 = packageFactory->CreateEntity(obj);
  ASSERT_NE(entity3, nullptr) << "The entity3 created";
  system->AddEntity(entity3);
  ASSERT_EQ(3, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity3->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity3->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity3->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity3->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity3->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity3->GetDirection()[2], direction_to_add[2]);

    JsonHelper::AddStringToJsonObject(obj, "type", "robot");
  IEntity* entity4 = robotFactory->CreateEntity(obj);
  ASSERT_NE(entity4, nullptr) << "The entity4 created";
  system->AddEntity(entity4);
  ASSERT_EQ(4, system->GetEntities().size());
  ASSERT_FLOAT_EQ(entity4->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(entity4->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(entity4->GetPosition()[2], position_to_add[2]);
  ASSERT_FLOAT_EQ(entity4->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(entity4->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(entity4->GetDirection()[2], direction_to_add[2]);


}
}  // namespace csci3081
