#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <iostream>
#include <cmath>

#include "../include/entity/battery.h"

namespace csci3081 {

using entity_project::IEntity;

class batteryTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
      battery = new Battery(10000.0);
      battery_default = new Battery();
  }
  virtual void TearDown() {}

    Battery* battery; 
    Battery* battery_default;
    float charge = 10000;
    float update = 123.4321;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(batteryTest, generalBatteryTests){
    ASSERT_FLOAT_EQ(battery->getCharge(), 10000.0);
    battery->setIsCharging(false);
    battery->update(update);
    ASSERT_FLOAT_EQ(battery->getCharge(), charge - update);
    battery->update(update * 3);
    ASSERT_FLOAT_EQ(battery->getCharge(), charge - 4 * update);
    battery->update(update);
    ASSERT_FLOAT_EQ(battery->getCharge(), charge - 5 * update);
    battery->setIsCharging(true);
    battery->update(update * 100);
    ASSERT_FLOAT_EQ(battery->getCharge(), 0);
    ASSERT_EQ(battery->getIsCharging(), true);

    ASSERT_FLOAT_EQ(battery_default->getCharge(), 0);
    battery_default->setCharge(10000);
    ASSERT_FLOAT_EQ(battery_default->getCharge(), 10000);



    
}

}