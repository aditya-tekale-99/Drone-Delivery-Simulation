/**
 * @file strategy.h
 */
#ifndef STRATEGY_H
#define STRATEGY_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "entity/entity_base.h"
#include <queue>

using namespace std;

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Strategy class for different routes.
 */
class Strategy {
    public:
/**
 * @brief Strategy destructor 
 */
    ~Strategy() {}
/**
 * @brief virtual function that returns the fullpath from source to customer 
 * @param[in] IEntity drone, package, customer
 * 
 * @return vector of float vectors representeing a fullpath
 */
    virtual std::vector<vector<float>> getPath(IEntity* deliverer, IEntity* package, IEntity* customer) = 0;

};
}

#endif