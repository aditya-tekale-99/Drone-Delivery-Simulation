/**
 * @file vector2D.h
 */
#ifndef VECTOR2D_H
#define VECTOR2D_H

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "vector/vec.h"

#include <vector>
#include <cmath>

namespace csci3081{
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief 2-Dimensional vector class
 */
class vector2D : public vec {
    public: 
    /// Destructor, does nothing 
    ~vector2D();

    /// Constructor. Sets x, y, and z coords
    vector2D(float x=0, float y=0, float z=0);
    /// Constructor. Takes a vec* as input, and copies vals
    vector2D(const vec* vec);
    /// Constructor. Sets x, y, and z coords
    vector2D(const std::vector<float>& v);

    void setVector(float x=0, float y=0, float z=0);
    void setVector(vec* vec);
    void setVector(std::vector<float> vec);
    void setX(float x);
    void setY(float y);
    void setZ(float z);
    float getX() const;
    float getY() const;
    float getZ() const;
    std::vector<float>& getPositionAsVector();

    /**
     * @brief Get the magnitude of the vector using only x and z coordinates. 
     */
    float magnitude();
    /**
     * @brief Dots the x and z coordinates to dotVec
     */
    float dot(vec* dotVec);
    /**
     * @brief Gets distance from distVec using only x and z coordinates
     */
    float distance(const vec* distVec) const;

    /**
     * @brief Scales the vector by magnitude
     */
    vec* scale(float magnitude);

    /**
     * @brief Descales the vector by magnitude
     */
    vec* shrink(float magnitude);

    /**
     * @brief Normalize the vector to be of length 1
     */
    vec* normalize();
    /**
     * @brief Adds to the vector, only using the x and z coordinates
     */
    vec* add(vec* addVec);
    /**
     * @brief Subtracts from the vector, only using the x and z coordinates
     */
    vec* subtract(vec* addVec);
    /**
     * @brief Tests if two vectors are equal by checking their distance is less than a threshold. 
     */
    bool equal(vec* cmp) const;
};

}

#endif