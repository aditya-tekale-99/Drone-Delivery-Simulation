#include "strategy/beeline_strategy.h"

namespace csci3081{
    //destructor for beeline path
    BeelineStrategy::~BeelineStrategy(){
        cout << "No more beeline strategy" << endl;
    }
    //overwriting strategy funtion
    std::vector<vector<float>> BeelineStrategy::getPath(IEntity* deliverer, IEntity* package, IEntity* customer) {
        std::vector<std::vector<float>> fullPath(7); //fullpath to return
        fullPath[0] = deliverer->GetPosition(); //source position of drone
        fullPath[1] = deliverer->GetPosition();
        fullPath[2] = package->GetPosition(); //intermeiate position of package
        fullPath[3] = package->GetPosition();
        fullPath[4] = package->GetPosition();
        fullPath[5] = customer->GetPosition();//final position of customer
        fullPath[6] = customer->GetPosition();

        fullPath[1][1] = 500;
        fullPath[2][1] = 500;
        fullPath[4][1] = 500;
        fullPath[5][1] = 500;

        std::reverse(fullPath.begin(), fullPath.end()); //reverse path
        return fullPath; //return full path from source to customer
    }
}