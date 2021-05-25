/**
 * @file battery.h
 */
#ifndef BATTERY_H
#define BATTERY_H 

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief This class is implements a battery for some of the carriers in the simulation
 */

class Battery{
    public: 
    /// @brief Constructor: Sets our battery variables to default values
    Battery();
    /// @brief Constructor: Takes in a capacity that's used to calculate the battery's charge
    Battery(double capacity);

    /// Returns whether or not the batter is currently charging
    bool getIsCharging() const;
    /// Sets the battery to be charging, or to be not charging
    void setIsCharging(bool isCharging);
    /// Returns the current charge of the battery
    float getCharge() const;
    /// Sets the current charge of the battery
    void setCharge(float charge);
    /// Checks if current charge is less than zero
    bool getIsDead() const;

    /**
     * Updates the charge of the battery given a timestep dt
     *
     * Still not fully sure how to do this. Current formula is distance moved 
     * is the amount of charge that gets subtracted
     *
     * Because chargers are not in place yet, this only subtracts. 
     */
    void update(float distance);

    private: 
    float charge_;       ///< float: Current charge for the battery
    float maxCharge_;    ///< float: A max charge for the battery    
    bool isCharging_;    ///< Boolean: True if the battery is charging
};
}

#endif