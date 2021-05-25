/**
 * @file smart_strategy.h
 */
#ifndef SMART_STRATEGY_H
#define SMART_STRATEGY_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "strategy/strategy.h"
#include <queue>
using namespace std;

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Strategy class for smart route.
 */
class SmartStrategy : public csci3081::Strategy {
    public:
/**
 * @brief returns the fullpath from source to customer 
 * @param[in] IEntity drone, package, customer
 * 
 * @return vector of float vectors representeing a fullpath
 */
    std::vector<vector<float>> getPath(IEntity* deliverer, IEntity* package, IEntity* customer);
/**
  * @brief sets graph for smart path
  * @param[in] IGraph graph
  *
  */    
    void SetGraph (const IGraph* graph);
/**
 * @brief SmartStrategy destructor 
 */
    ~SmartStrategy();

    protected:
    const IGraph* graph_; ///< The graph of our city

};
}

#endif