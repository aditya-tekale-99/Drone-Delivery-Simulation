/**
 * @file composite_factory.h
 */
#ifndef COMPOSITE_FACTORY_H
#define COMPOSITE_FACTORY_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_factory.h>
#include "entity/entity_base.h"

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Composite Factory class used by our simulation. Takes factories, and uses 
 * them to create entities. Implements the abstract factory pattern
 */

class CompositeFactory : public IEntityFactory {
    public: 
    ~CompositeFactory();
    /**
     * @brief Creates an entity. Does so by iterating over the factories
     * that have been added to our abstract factory pattern
     */
    IEntity* CreateEntity(const picojson::object& val);
    /// Adds a factory to our set of factories 
    void addFactory(IEntityFactory* factory);

    private:
    vector<IEntityFactory*> factories_; ///< Set of factories currently added to the composite factory
};
}

#endif