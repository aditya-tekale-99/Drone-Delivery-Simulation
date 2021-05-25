/**
 *@file entity_base.h
 */
#ifndef ENTITY_BASE_H_
#define ENTITY_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "vector/vector2D.h"
#include "vector/vector3D.h"

#include "json_helper.h"
#include <EntityProject/facade/delivery_system.h>

namespace csci3081 {
static int EntityBaseID = 0;
class DeliveryInstance;
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The base class for creating entities.
 *
 * This class can be used as the base for all entities in the delivery system.
 * The overall design is up to you (the student), but all entities must implement
 * the IEntity interface.
 *
 * See the documentation for IEntity for more information
 */

class EntityBase : public IEntity {
 public:
  /// Virtual destructor to allow child class destructors to be called
  virtual ~EntityBase() {}

  /** 
    * Constructor
    * 
    * details_: set to be the input parameter
    * id_: set by a static int starting at 0. 
    * name_: set by getting the "name" key from details
    * position_: set by getting "postiong" key from details
    * direction_: set by getting "direciton" key from details
    * radius_: default set to 1
    * version_: default set to 1
    * dynamic_: default set to true
    */
  EntityBase(const picojson::object& details) {
    details_ = details;
    id_ = EntityBaseID++;
    name_ = JsonHelper::GetString(details, "name"); 
    position_ = new vector3D(JsonHelper::GetStdFloatVector(details, "position"));
    direction_ = new vector3D(JsonHelper::GetStdFloatVector(details, "direction"));
    radius_ = 1;
    version_ = 1;
    dynamic_ = true;
  }
 
  /// Returns id
  int GetId() const {return id_;}

  /// Returns name
  const std::string& GetName() { return name_;}

  /// Returns the position as a std::vector<float>
  const std::vector<float>& GetPosition() const { return position_->getPositionAsVector(); }

  /// Returns the direction as a std::vector<float>
  const std::vector<float>& GetDirection() const { return direction_->getPositionAsVector(); }

  /// Returns the radius of the entity
  float GetRadius() const { return radius_; }

  /// Returns the details of the entity
  const picojson::object& GetDetails() { return details_; }

  /// Returns the version of the entity
  int GetVersion() const { return version_; }

  /// Returns whether or not the entity is dynamic
  bool IsDynamic() const { return dynamic_; }


  virtual void scheduleDelivery(DeliveryInstance* delivery){}

  /**
   * Pure virtual update method to be overriden by all entities
   */
  virtual void update(float dt) = 0;

  virtual void addObserver(IEntityObserver* observer) {};
  virtual void removeObserver(IEntityObserver* observer) {};

  /// Returns the position as a csci3081::vec*
  vec* GetPositionVec() const { return position_; }

  /// Returns the direction as a csci3081::vec*
  vec* GetDirectionVec() const { return direction_; }
 protected:

    /** Checks if two entities are colliding. 
   *
   * If the sum of their radii is greater than their distance,
   * then they are said to be colliding. Since the robot is on the 2D plane, we correct for the fact that it can't get
      get close enough to the packages by subtracting 3 from the calculated distance.
   */
  bool IsColliding(EntityBase* cmp) const { 
    vec* p1 = new vector3D(GetPosition());
    vec* p2 = new vector3D(cmp->GetPosition());

    float dist = std::max(p1->distance(p2), p2->distance(p1));
    if(JsonHelper::GetString(cmp->GetDetails(), "type") == "robot") {
      return (dist - 3) < (GetRadius() + cmp -> GetRadius());

    } else {
    return dist < (GetRadius() + cmp -> GetRadius());
    }
  }

  int id_;            ///< id of entity
  std::string name_;  ///< name of entity
  vec* position_;     ///< position of entity
  vec* direction_;    ///< direction of entity
  float radius_;      ///< radius of entity
  picojson::object details_;  ///< entity details
  int version_;       ///< entity version
  bool dynamic_;      ///< entity dynamicity


};

}  // namespace csci3081


#endif  // ENTITY_BASE_H_
