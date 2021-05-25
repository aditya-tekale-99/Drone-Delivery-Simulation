/**
 * @file parabolic_strategy.h
 */
#ifndef PARABOLIC_STRATEGY_H
#define PARABOLIC_STRATEGY_H
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
 * @brief Strategy class for parabolic route.
 */
class ParabolicStrategy : public csci3081::Strategy {
    public:
/**
 * @brief returns the fullpath from source to customer 
 * @param[in] IEntity drone, package, customer
 * 
 * @return vector of float vectors representeing a fullpath
 */
    std::vector<vector<float>> getPath(IEntity* deliverer, IEntity* package, IEntity* customer);
/**
 * @brief ParabolicStrategy destructor 
 */
    ~ParabolicStrategy();

};
}

#endif