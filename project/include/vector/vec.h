/**
 * @file vec.h
 */
#ifndef VECTOR_H
#define VECTOR_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Vector interface that our vector2D and vector3D implement
 *
 * Any function I want to add to vector2D or vector3D I ADD HERE FIRST. 
 * no ifs ands or buts, as I want to keep things clean and easy to expand.
 */
class vec {
    public:
    /// Vector setter using 3 floats
    virtual void setVector(float x=0, float y=0, float z=0) = 0;

    /// Vector setter using another vec*
    virtual void setVector(vec* vec) = 0;

    /// Vector setter using another vec*
    virtual void setVector(std::vector<float> vec) = 0;

    /// Setter for the x parameter of the vector
    virtual void setX(float x) = 0;

    /// Setter for the x parameter of the vector
    virtual void setY(float y) = 0;

    /// Setter for the x parameter of the vector
    virtual void setZ(float z) = 0;

    /// Setter for the x parameter of the vector
    virtual float getX() const = 0;

    /// Setter for the x parameter of the vector
    virtual float getY() const = 0;

    /// Setter for the x parameter of the vector
    virtual float getZ() const = 0;

    /// Setter for the x parameter of the vector
    virtual std::vector<float>& getPositionAsVector() = 0;

    /// Vectors should have a magnitude
    virtual float magnitude() = 0;

    /// Vectors should form an inner product
    virtual float dot(vec* dotVec) = 0;
    
    /// Vectors should have distance
    virtual float distance(const vec* distVec) const = 0;

    /// Vectors can be scaled
    virtual vec* scale(float magnitude) = 0;

    /// Vectors can be scaled down
    virtual vec* shrink(float magnitude) = 0;

    /// Vectors can be normalized
    virtual vec* normalize() = 0;

    /// We can add vectors
    virtual vec* add(vec* addVec) = 0;

    /// We can subtract vectors
    virtual vec* subtract(vec* addVec) = 0;

    /// We can check for equality of two vectors
    virtual bool equal(vec* cmp) const = 0;

    protected:
    float x_;    ///< x coord of the vector
    float y_;    ///< y coord of the vector
    float z_;    ///< z coord of the vector
    std::vector<float> position_; ///< vector<float> of our vector for which the memory location can be returned
};
}

#endif