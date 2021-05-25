#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <iostream>

#include "../include/entity/customer.h"
#include "../include/factory/customer_factory.h"

namespace csci3081 {

using entity_project::IEntity;

class CustomerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // Assign vars using a constructor
    obj = JsonHelper::CreateJsonObject();
    JsonHelper::AddStringToJsonObject(obj, "type", "customer");
    JsonHelper::AddStringToJsonObject(obj, "name", "customer");
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
    JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);

    testCustomer = customerFactory.CreateEntity(obj);
  }
  virtual void TearDown() {
    delete testCustomer;
  }
  
  picojson::object obj = JsonHelper::CreateJsonObject();
  std::vector<float> position_to_add = {498.292, 253.883, -228.53};
  std::vector<float> direction_to_add = {100, 200, 300};
  IEntity* testCustomer;
  CustomerFactory customerFactory;

};

//******************************************************************************
 //* Test Cases
//*****************************************************************************

TEST_F(CustomerTest, CustomerWorking) {
  ASSERT_EQ(testCustomer->GetName(), "customer");
  ASSERT_EQ(testCustomer->GetRadius(), 1);
  ASSERT_EQ(testCustomer->GetVersion(), 1);

  ASSERT_FLOAT_EQ(testCustomer->GetDirection()[0], direction_to_add[0]);
  ASSERT_FLOAT_EQ(testCustomer->GetDirection()[1], direction_to_add[1]);
  ASSERT_FLOAT_EQ(testCustomer->GetDirection()[2], direction_to_add[2]);

  ASSERT_FLOAT_EQ(testCustomer->GetPosition()[0], position_to_add[0]);
  ASSERT_FLOAT_EQ(testCustomer->GetPosition()[1], position_to_add[1]);
  ASSERT_FLOAT_EQ(testCustomer->GetPosition()[2], position_to_add[2]);

}

}  // namespace csci3081