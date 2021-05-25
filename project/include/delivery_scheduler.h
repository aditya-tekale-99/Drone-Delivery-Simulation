/**
 * @file delivery_scheduler.h
 */
#ifndef DELIVERY_SCHEDULER_H
#define DELIVERY_SCHEDULER_H

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include "entity/drone.h"
#include "entity/customer.h"
#include "entity/package.h"
#include "entity/robot.h"
#include "strategy/strategy.h"
#include "strategy/parabolic_strategy.h"
#include "strategy/smart_strategy.h"
#include "strategy/beeline_strategy.h"

#include <queue>

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class has functions that make the drone/robot carry out its delivery process
 */

class DeliveryScheduler {
    public: 
    /// constructor for the scheduler with a reference to a set of entities
    DeliveryScheduler(const vector<IEntity*>& entities) : entities_(entities) {}
    /// this function is used to schedule the deliveres for the drone/robot to carry out
    void scheduleDeliveries();
    /// Sets the graph of the UML so that smart paths can be generated
    void setGraph(const IGraph* graph) { graph_ = graph; smartRoute.SetGraph(graph);}
    /// Sets the graph of the UML so that smart paths can be generated
    void ScheduleDelivery(IEntity* package, IEntity* dest) {
	    auto delivery = std::make_pair(package, dest);
	    	schedule_.push(delivery);
    }
    protected:
    const IGraph* graph_; ///< The graph of our city
    const vector<IEntity*>& entities_; ///< the entities used in this project
    std::queue<std::pair<IEntity*, IEntity*>> schedule_; ///< queue of customer, package pairs to be delivered
    /// Vector of deliveries. Iterated over in unscheduleDeliveres
    std::vector<DeliveryInstance*> deliveries_; 
    /// Strategy object used to generate parabolic paths
    ParabolicStrategy parabolicRoute; 
    /// Strategy object used to generate smart paths
    SmartStrategy smartRoute; 
    /// Strategy object used to generate beeline paths
    BeelineStrategy beelineRoute; 

    //std::vector<vector<float>> getSmartPath(IEntity* deliverer, IEntity* package, IEntity* customer);

    //std::vector<vector<float>> getDumbPath(IEntity* deliverer, IEntity* package, IEntity* customer);
    
    private:
    /// gets either the drone or robot based on which one is closest to the package
    IEntity* getClosestPackageCarrier(IEntity* package);
    /// Unschedules deliveries which have dead carriers, or deliveries where the package is delivered
    void unscheduleDeliveries();
};    
}

#endif
