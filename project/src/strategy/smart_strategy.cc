#include "strategy/smart_strategy.h"

namespace csci3081{
    //destructor for smart path
    SmartStrategy::~SmartStrategy(){
        cout << "No more smart strategy" << endl;
    }
    //setting graph for smart path
    void SmartStrategy::SetGraph(const IGraph* graph) {
        graph_ = graph;
    }
    //overwriting strategy funtion
    std::vector<vector<float>> SmartStrategy::getPath(IEntity* deliverer, IEntity* package, IEntity* customer){
        auto path1 = graph_->GetPath(deliverer->GetPosition(), package->GetPosition());
        auto path2 = graph_->GetPath(package->GetPosition(), customer->GetPosition());
        std::vector<std::vector<float>> fullPath(path1); //new path set
        fullPath.insert(fullPath.end(), path2.begin(), path2.end());
        std::reverse(fullPath.begin(), fullPath.end()); //reverse path
        return fullPath; //return full path from source to customer
    }
}