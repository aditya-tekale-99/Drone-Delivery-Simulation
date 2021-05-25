/**
 * @file vector3D.h
 */
#ifndef VECTOR3D_H
#define VECTOR3D_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "vector/vec.h"

#include <vector>
#include <cmath>

namespace csci3081 {
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief 3-Dimensional Vector class
 */
class vector3D : public vec {
    public:
    /// Default destructor. Does nothing
    ~vector3D();

    /// Constructor setting member x, y, and z given argument x,y,z
    vector3D(float x=0, float y=0, float z=0);

    /// Constructor copying vals from another vec
    vector3D(const vec* vec);

    /// Cosntructor taking values from a std::vector<float>
    vector3D(const std::vector<float>& v);

    /// Sets vector using three float parameters
    void setVector(float x=0, float y=0, float z=0);

    /// Sets vector using a pointer to other vec
    void setVector(vec* vec);

    /// Sets vector using a pointer to other vec
    void setVector(std::vector<float> vec);

    /// Sets x variable
    void setX(float x);

    /// Sets y variable
    void setY(float y);

    /// Sets z variable
    void setZ(float z);

    /// Gets x variable
    float getX() const;

    /// Gets y variable
    float getY() const;

    /// Gets z variable
    float getZ() const;

    /// Returns position as a vector. Useful in entity_base, where this is necessary
    std::vector<float>& getPositionAsVector();

    /// Gets magnitude using all of x, y, z
    float magnitude();

    /// Dots using all of x, y, z
    float dot(vec* dotVec);

    /// Gets distance using all of x, y, z
    float distance(const vec* distVec) const;

    /// Scales our vector by a magnitude
    vec* scale(float magnitude);

    /// Scales down ur vector by a magnitude
    vec* shrink(float magnitude);

    /// Normalizes our vector
    vec* normalize();

    /// Adds another vector to our vector
    vec* add(vec* addVec);

    /// Subtract another vector from our vector
    vec* subtract(vec* addVec);

    /// Checks if our vector is equal to another vector, by checking if distance less than 1e-6
    bool equal(vec* cmp) const;
};
}

#endif