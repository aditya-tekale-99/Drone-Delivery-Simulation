/**
 *@file observer_subject.h
 */
#ifndef OBSERVER_SUBJECT_H
#define OBSERVER_SUBJECT_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <EntityProject/entity_console_logger.h>
#include "entity/entity_base.h"
#include <iostream>
#include <set>

#include "json_helper.h"


namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Observer subject to events when they occur
 */

class ObserverSubject : public entity_project::EntityConsoleLogger {
    protected:
    /// Adds the observer 
    /// Adds an observer to our set of observers
    void AddObserver(const IEntityObserver& add);
    /// Removes an observer from our set of observers
    void RemoveObserver(const IEntityObserver& remove);
    /**
     * @brief Notifies Observers of an event
     *
     * Does so by having the subject pass details built with a description
     * as well as a pointer to itself.  
     *
     * Possible notifications so far include for carriers idle, moving 
     *
     * Possible notifications so far include for packages en route, picked up, delivered
     */
    void notify(picojson::object& details, IEntity* entity);
    /**
     * @brief Helper function that builds a picojson for a notification
     *
     * Return a json object with values {type: notify, value: notifcationType}
     */

    picojson::object buildNotification(std::string notificationType);

    /**
     * @brief Helper function builds a picojson for a notification in the event of 
     * a delivery being scheduled. 
     *
     * Package Carriers pass their notificationType of moving, along with a path to the 
     * function. 
     *
     * Return a json boject with values {type: notify, value: notificationType, path: [path]}
     */
    picojson::object buildNotification(std::string notificationType, std::vector<std::vector<float>>& path);

    private: 
    std::set<IEntityObserver*> observers_; // Private set of observers for the subject

    friend class DecoratorInterface;
};

}

#endif
