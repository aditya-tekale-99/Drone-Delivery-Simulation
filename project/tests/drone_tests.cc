#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <iostream>

#include "../include/entity/drone.h"
#include "../include/entity/customer.h"
#include "../include/entity/package.h"
#include "../include/factory/drone_factory.h"
#include "../include/factory/customer_factory.h"
#include "../include/factory/package_factory.h"

namespace csci3081 {

using entity_project::IEntity;

class DroneTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // Assign vars using a constructor
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "drone");
    JsonHelper::AddStringToJsonObject(obj, "name", "drone");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "speed", 2);
    testDrone = dynamic_cast<Drone*>(droneFactory.CreateEntity(obj));
    JsonHelper::AddStringToJsonObject(obj, "type", "customer");
    sampleCustomer = dynamic_cast<Customer*>(customerFactory.CreateEntity(obj)); 
    JsonHelper::AddStringToJsonObject(obj, "type", "package");
    samplePackage = dynamic_cast<Package*>(packageFactory.CreateEntity(obj));
  }
  virtual void TearDown() {}
  Drone* testDrone;
  Customer* sampleCustomer;
  Package* samplePackage;

  DroneFactory droneFactory;
  CustomerFactory customerFactory;
  PackageFactory packageFactory;

  float speed = 2;

  std::vector<float> position_to_add = {498.292, 253.883, -228.53};
  std::vector<float> direction_to_add = {100, 200, 300};
};

//******************************************************************************
 //* Test Cases
//*****************************************************************************

TEST_F(DroneTest, DroneCreated) {
  ASSERT_EQ(testDrone->GetName(), "drone");
  ASSERT_EQ(testDrone->GetRadius(), 1);
  ASSERT_EQ(testDrone->GetVersion(), 1);

  ASSERT_FLOAT_EQ(testDrone->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(testDrone->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(testDrone->GetDirection()[2], direction_to_add[2]);

  ASSERT_FLOAT_EQ(testDrone->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(testDrone->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(testDrone->GetPosition()[2], position_to_add[2]);
  
  ASSERT_EQ(dynamic_cast<Drone*>(testDrone)->getCustomer(), nullptr);
  ASSERT_EQ(dynamic_cast<Drone*>(testDrone)->getSpeed(), 2);

  testDrone->setSmart(true);
  ASSERT_EQ(dynamic_cast<Drone*>(testDrone)->getSmart(), true);

  testDrone->setIsIdle();
  ASSERT_EQ(dynamic_cast<Drone*>(testDrone)->getIsIdle(), true);

}

}  // namespace csci3081