/**
 * @file decorator_interface.h
 */
#ifndef DECORATOR_INTERFACE_H
#define DECORATOR_INTERFACE_H
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "entity/package_carrier.h"

#include "json_helper.h"

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief decorator interface for adding color to entities. 
 */ 
class DecoratorInterface : public csci3081::PackageCarrier{
    public:
    /// this method has an instance of package carrier
    DecoratorInterface (const picojson::object& details) : PackageCarrier(details) {}
    /// update function
    virtual void update(float dt) = 0;
    protected:
    ///carrier_ object created
    PackageCarrier* carrier_;
    /// this method had attributes that point the carrier to specific attribute using this ->
    void commitCarrierAttributes(){
        this->id_ = carrier_->GetId(); 
        this->name_ = carrier_->GetName(); 
        this->position_ = carrier_->GetPositionVec();
        this->direction_ = carrier_->GetDirectionVec(); 
        this->radius_ = carrier_->GetRadius(); 
        this->version_ = carrier_->GetVersion();
        this->dynamic_ = carrier_->IsDynamic(); 

        this->speed_ = carrier_->getSpeed(); 
        this->battery_ = carrier_->getBattery();
        this->delivery_ = carrier_->getDelivery();
        this->isIdle_ = carrier_->getIsIdle(); 
        this->packagePickedUp_ = carrier_->getPackagePickedUp(); 
        //this->details_ = carrier_->GetDetails();

        carrier_->observers_ = this->observers_; 
    }
    /**
     * @brief schedule delivery function that is used to schedule a delivery for
     * drone or robot based on the carrier attributes.
     */ 
    void scheduleDelivery(DeliveryInstance* delivery){
        carrier_->scheduleDelivery(delivery);
        commitCarrierAttributes();
    }
    private:
};     
}

#endif
