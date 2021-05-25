#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <iostream>

#include "strategy/strategy.h"
#include "strategy/parabolic_strategy.h"
#include "strategy/smart_strategy.h"
#include "strategy/beeline_strategy.h"
#include "../include/entity/drone.h"
#include "../include/entity/customer.h"
#include "../include/entity/package.h"
#include "../include/factory/drone_factory.h"
#include "../include/factory/customer_factory.h"
#include "../include/factory/package_factory.h"


namespace csci3081 {
    using entity_project::IEntity;

    class DeliveryInstanceTest : public ::testing::Test {
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
        DeliveryInstance* testDelivery;

        DroneFactory droneFactory;
        CustomerFactory customerFactory;
        PackageFactory packageFactory;

        BeelineStrategy smartRoute;

        float speed = 2;

        std::vector<float> position_to_add = {498.292, 253.883, -228.53};
        std::vector<float> direction_to_add = {100, 200, 300};
    };

    TEST_F(DeliveryInstanceTest, DeliveryInstanceCreated) {
        std::vector<std::vector<float>> path = smartRoute.getPath(testDrone, samplePackage, sampleCustomer);

        testDelivery = new DeliveryInstance(*testDrone, *samplePackage, *sampleCustomer, path);

        ASSERT_EQ(testDelivery->getIsPickedUp(), false);
        
        testDelivery->setIsPickedUp();
        ASSERT_EQ(testDelivery->getIsPickedUp(), true);

        ASSERT_EQ(testDelivery->getisValid(), true);

        testDelivery->setisValid();
        ASSERT_EQ(testDelivery->getisValid(), false);

        ASSERT_EQ(testDelivery->getisDelivered(), false);

        testDelivery->setisDelivered(true);
        ASSERT_EQ(testDelivery->getisDelivered(), true);

    }
}