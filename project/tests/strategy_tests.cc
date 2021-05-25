#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <iostream>

#include "strategy/beeline_strategy.h"
#include "strategy/parabolic_strategy.h"
#include "strategy/smart_strategy.h"

#include "../include/entity/drone.h"
#include "../include/entity/customer.h"
#include "../include/entity/package.h"
#include "../include/factory/drone_factory.h"
#include "../include/factory/customer_factory.h"
#include "../include/factory/package_factory.h"

namespace csci3081 {
    using entity_project::IEntity;

        class StrategyTest : public ::testing::Test {
        protected:
            virtual void SetUp() {
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

        ParabolicStrategy parabolicRoute;
        SmartStrategy smartRoute; 
        BeelineStrategy beelineRoute;

        float speed = 2;

        std::vector<float> position_to_add = {498.292, 253.883, -228.53};
        std::vector<float> direction_to_add = {100, 200, 300};
    };

    TEST_F(StrategyTest, StrategiesCreated) {

        std::vector<std::vector<float>> path;

        path = beelineRoute.getPath(testDrone, samplePackage, sampleCustomer);
        ASSERT_EQ(path[1][1], 500);
        ASSERT_EQ(path[2][1], 500);
        ASSERT_EQ(path[4][1], 500);
        ASSERT_EQ(path[5][1], 500);

        // path = smartRoute.getPath(testDrone, samplePackage, sampleCustomer);
        // ASSERT_GT(path.size(), 0);
        // smart path
        // parabolic path
        
    }
}