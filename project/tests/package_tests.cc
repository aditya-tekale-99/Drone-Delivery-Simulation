#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <iostream>

#include "../include/entity/customer.h"
#include "../include/factory/customer_factory.h"
#include "../include/entity/package.h"
#include "../include/factory/package_factory.h"
#include "../include/entity/drone.h"
#include "../include/factory/drone_factory.h"
#include "../include/vector/vector3D.h"

namespace csci3081 {

using entity_project::IEntity;

class PackageTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // Assign vars using a constructor
    obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "package");
    JsonHelper::AddStringToJsonObject(obj, "name", "package");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);

    testPackage = dynamic_cast<Package*>(packageFactory.CreateEntity(obj));
    testCustomer = customerFactory.CreateEntity(obj);

    JsonHelper::AddFloatToJsonObject(obj, "speed", 2);
    testCarrier = droneFactory.CreateEntity(obj);
    
    newPos = new vector3D(100, 100, 100);
  }
  virtual void TearDown() {
    delete testCustomer;
    delete testCarrier;
    delete testPackage;
    delete newPos;
  }
  
  picojson::object obj = JsonHelper::CreateJsonObject();
  std::vector<float> position_to_add = {498.292, 253.883, -228.53};
  std::vector<float> direction_to_add = {100, 200, 300};

  vec* newPos;
  Package* testPackage;
  IEntity* testCustomer;
  IEntity* testCarrier;
  CustomerFactory customerFactory;
  DroneFactory droneFactory;
  PackageFactory packageFactory;
};

//******************************************************************************
 //* Test Cases
//*****************************************************************************

TEST_F(PackageTest, PackageWorking) {
  ASSERT_EQ(testPackage->GetName(), "package");
  ASSERT_EQ(testPackage->GetRadius(), 1);
  ASSERT_EQ(testPackage->GetVersion(), 1);
  ASSERT_FLOAT_EQ(testPackage->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(testPackage->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(testPackage->GetDirection()[2], direction_to_add[2]);

  ASSERT_FLOAT_EQ(testPackage->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(testPackage->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(testPackage->GetPosition()[2], position_to_add[2]);

  ASSERT_EQ(testPackage->getCustomer(), nullptr);
  ASSERT_EQ(testPackage->getCarrier(), nullptr);
  
  ASSERT_EQ(testPackage->getCarrier(), testCarrier);
  ASSERT_EQ(testPackage->getCustomer(), testCustomer);

  testPackage->setWeight(100);
  ASSERT_FLOAT_EQ(testPackage->getWeight(), 100);

  

}

}  // namespace csci3081