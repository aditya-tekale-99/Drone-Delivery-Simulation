/**
 * @file decorated_carrier.h
 */
#ifndef DECORATED_CARRIER_H
#define DECORATED_CARRIER_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity/decorator_interface.h"
#include "entity/package_carrier.h"
#include <iostream>

#include "json_helper.h"

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Drone decorator for adding color to drone. 
 */ 
class DecoratedCarrier : public csci3081::DecoratorInterface {
    public:
    /// this method has an instance from decorator interface
    DecoratedCarrier (csci3081::PackageCarrier* carrier) : DecoratorInterface(carrier->GetDetails()) {
        carrier_ = carrier;
        commitCarrierAttributes();
        color_ = "";
        count_ = 0;
        isIdle_ = true;
        updateColor();
    }
     ///update method for color of entity
    void update(float dt) {
        carrier_->update(dt);
        commitCarrierAttributes();
        updateColor();
        return;
    }

    protected:
    private:
    std::string color_; ///variable color_ of type string
    int count_; ///variable count_ of type int

    /**
     * @brief this method is used to update the color of the entity as it starts moving
     * and the battery starts to deplet (green is full battery whereas red is battery is about to die). 
     */ 
    void updateColor(){

        if(battery_.getCharge() >= 5000 && color_ != "0x00cc00"){
            updateColor("0x00cc00");
        } else if(battery_.getCharge() <= 5000 && battery_.getCharge() >= 2500 && color_ != "0xcccc00"){
            updateColor("0xcccc00");
        } else if(battery_.getCharge() <= 2500 && battery_.getCharge() >= 1000 && color_ != "0xffa500"){
            updateColor("0xffa500");
        }else if(battery_.getCharge() <= 1000 && battery_.getCharge() >= 1 && color_ != "0xcc0000"){
            updateColor("0xcc0000");
        } else if(battery_.getCharge() <= 1 && color_ != "0x000000"){
            updateColor("0x000000");
        }
    }
    /**
     * @brief this method is used to add the color to the
     * drone and robot and notifies in the simulation with relevant notifications
     * and also updates accordingly with changes happening as the entity starts to move. 
     */ 
    void updateColor(std::string color){
        color_ = color;
        details_["color"] = picojson::value(color);
        picojson::object notification;
        notification["type"] = picojson::value("notify");
        notification["value"] = picojson::value("updateDetails");
        notification["details"] = picojson::value(details_);
        ObserverSubject::notify(notification, this);
    }
};     
}

#endif
