/**
 * @file beeline_strategy.h
 */
#ifndef BEELINE_STRATEGY_H
#define BEELINE_STRATEGY_H
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
 * @brief Strategy class for beeline route.
 */
class BeelineStrategy : public csci3081::Strategy {
    public:
/**
 * @brief returns the fullpath from source to customer 
 * @param[in] IEntity drone, package, customer
 * 
 * @return vector of float vectors representeing a fullpath
 */
    std::vector<vector<float>> getPath(IEntity* deliverer, IEntity* package, IEntity* customer);
 /**
 * @brief BeelineStrategy destructor 
 */   
    ~BeelineStrategy();

};
}

#endif