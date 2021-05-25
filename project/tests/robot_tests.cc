#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <iostream>

#include "../include/entity/robot.h"
#include "../include/entity/customer.h"
#include "../include/entity/package.h"
#include "../include/factory/robot_factory.h"
#include "../include/factory/customer_factory.h"
#include "../include/factory/package_factory.h"

namespace csci3081 {

using entity_project::IEntity;

class RobotTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // Assign vars using a constructor
    picojson::object obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "robot");
    JsonHelper::AddStringToJsonObject(obj, "name", "robot");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
    JsonHelper::AddFloatToJsonObject(obj, "speed", 2);
    testRobot = dynamic_cast<Robot*>(robotFactory.CreateEntity(obj));
    JsonHelper::AddStringToJsonObject(obj, "type", "customer");
    sampleCustomer = dynamic_cast<Customer*>(customerFactory.CreateEntity(obj)); 
    JsonHelper::AddStringToJsonObject(obj, "type", "package");
    samplePackage = dynamic_cast<Package*>(packageFactory.CreateEntity(obj));
  }
  virtual void TearDown() {}
  Robot* testRobot;
  Customer* sampleCustomer;
  Package* samplePackage;

  RobotFactory robotFactory;
  CustomerFactory customerFactory;
  PackageFactory packageFactory;

  float speed = 2;

  std::vector<float> position_to_add = {498.292, 253.883, -228.53};
  std::vector<float> direction_to_add = {100, 200, 300};
};

//******************************************************************************
 //* Test Cases
//*****************************************************************************

TEST_F(RobotTest, RobotCreated) {
  ASSERT_EQ(testRobot->GetName(), "robot");
  ASSERT_EQ(testRobot->GetRadius(), 1);
  ASSERT_EQ(testRobot->GetVersion(), 1);

  ASSERT_FLOAT_EQ(testRobot->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(testRobot->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(testRobot->GetDirection()[2], direction_to_add[2]);

  ASSERT_FLOAT_EQ(testRobot->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(testRobot->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(testRobot->GetPosition()[2], position_to_add[2]);
  
  ASSERT_EQ(dynamic_cast<Robot*>(testRobot)->getCustomer(), nullptr);
  ASSERT_EQ(dynamic_cast<Robot*>(testRobot)->getSpeed(), 2);

  testRobot->setSmart(true);
  ASSERT_EQ(dynamic_cast<Robot*>(testRobot)->getSmart(), true);
}


}  // namespace csci3081