#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <iostream>

#include "entity/decorated_carrier.h"
#include "entity/decorator_interface.h"
#include "entity/package_carrier.h"
#include "../include/entity/drone.h"
#include "../include/entity/robot.h"
#include "../include/factory/drone_factory.h"
#include "../include/factory/customer_factory.h"
#include "../include/factory/package_factory.h"
#include "../include/factory/robot_factory.h"




namespace csci3081 {
    using entity_project::IEntity;

    class DecoratedCarrierTest : public ::testing::Test {
        protected:
            virtual void SetUp() {
                picojson::object obj = JsonHelper::CreateJsonObject();
                JsonHelper::AddStringToJsonObject(obj, "type", "drone");
                JsonHelper::AddStringToJsonObject(obj, "name", "drone");
                JsonHelper::AddStdFloatVectorToJsonObject(obj, "position", position_to_add);
                JsonHelper::AddStdFloatVectorToJsonObject(obj, "direction", direction_to_add);
                JsonHelper::AddFloatToJsonObject(obj, "speed", 2);
                testDrone = dynamic_cast<Drone*>(droneFactory.CreateEntity(obj));
                // JsonHelper::AddStringToJsonObject(obj, "type", "customer");
                // sampleCustomer = dynamic_cast<Customer*>(customerFactory.CreateEntity(obj)); 
                // JsonHelper::AddStringToJsonObject(obj, "type", "package");
                // samplePackage = dynamic_cast<Package*>(packageFactory.CreateEntity(obj));

                JsonHelper::AddStringToJsonObject(obj, "type", "robot");
                JsonHelper::AddStringToJsonObject(obj, "name", "robot");
                testRobot = dynamic_cast<Robot*>(robotFactory.CreateEntity(obj));
                testDecoratedCarrierDrone = new DecoratedCarrier(testDrone);
                testDecoratedCarrierRobot = new DecoratedCarrier(testRobot);
            
            }
            virtual void TearDown() {}
        Drone* testDrone;
        Robot* testRobot;
        // Customer* sampleCustomer;
        // Package* samplePackage;
        DecoratedCarrier* testDecoratedCarrierDrone;
        DecoratedCarrier* testDecoratedCarrierRobot;

        DroneFactory droneFactory;
        RobotFactory robotFactory;
        CustomerFactory customerFactory;
        PackageFactory packageFactory;

        float speed = 2;

        std::vector<float> position_to_add = {498.292, 253.883, -228.53};
        std::vector<float> direction_to_add = {100, 200, 300};
    };

    TEST_F(DecoratedCarrierTest, DecoratedCarrierCreated) {
        // update function test

    }
}