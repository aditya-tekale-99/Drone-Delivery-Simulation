#include "strategy/parabolic_strategy.h"

namespace csci3081{
    
    //destructor for parabolic path
    ParabolicStrategy::~ParabolicStrategy(){
        cout << "No more parabolic strategy" << endl;
    }

    //overwriting strategy funtion
    std::vector<vector<float>> ParabolicStrategy::getPath(IEntity* deliverer, IEntity* package, IEntity* customer) {
        float default_max_height = 700; //default max height set
        float initial_height = 25;

        int totalSteps = 40; //total steps on parabola
        std::vector<std::vector<float>> fullPath; //fullpath to return

        vec* v0 = new vector3D(deliverer->GetPosition()); //source position of drone
        vec* v_inter_dest = new vector3D(package->GetPosition()); //intermeiate position of package

        for (int i = 0; i <= totalSteps; i++) { //loop through steps
            float t = i * (1/(float)totalSteps);
            //calculate new coordinates
            float x = (v0->getX()) + ((v_inter_dest->getX() - v0->getX()) * t);
            float y = (((-4 * default_max_height) + (2 * v0->getY()) + (2 * v_inter_dest->getY())) * pow(t,2)) + (((4 * default_max_height) - (3 * v0->getY()) - (v_inter_dest->getY())) * t) + v0->getY();
            float z = (v0->getZ()) + ((v_inter_dest->getZ() - v0->getZ()) * t);

            vec* v1 = new vector3D(x, y, z); //set new vector with coordinates
            fullPath.push_back(v1->getPositionAsVector()); //new path set
        }

        vec* v_final_dest = new vector3D(customer->GetPosition()); //final position of customer

        for (int i = 0; i <= totalSteps; i++) { //loop through steps
            float t = i * (1/(float)totalSteps);
            //calculate new coordinates
            float x = (v_inter_dest->getX()) + ((v_final_dest->getX() - v_inter_dest->getX()) * t);
            float y = (((-4 * default_max_height) + (2 * v_inter_dest->getY()) + (2 * v_final_dest->getY())) * pow(t,2)) + (((4 * default_max_height) - (3 * v_inter_dest->getY()) - (v_final_dest->getY())) * t) + v0->getY();
            float z = (v_inter_dest->getZ()) + ((v_final_dest->getZ() - v_inter_dest->getZ()) * t);
            
            vec* v1 = new vector3D(x, y, z); //set new vector with coordinates
            fullPath.push_back(v1->getPositionAsVector()); //new path set
        }
        
        std::reverse(fullPath.begin(), fullPath.end()); //reverse path
        return fullPath; //return full path from source to customer

    }


}