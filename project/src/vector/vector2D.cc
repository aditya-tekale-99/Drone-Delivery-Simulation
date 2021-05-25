#include "vector/vector2D.h"

namespace csci3081{

vector2D::~vector2D() {}

vector2D::vector2D(float x, float y, float z){
    x_ = x;
    y_ = 0;
    z_ = z;
}

vector2D::vector2D(const vec* vec){
    x_ = vec->getX();
    y_ = 300;
    z_ = vec->getZ();
}

vector2D::vector2D(const std::vector<float>& v){
    x_ = y_ = z_ = 0;
    if(v.size() > 0) x_ = v[0];
    if(v.size() > 1) y_ = 0;
    if(v.size() > 2) z_ = v[2];
}

void vector2D::setVector(float x, float y, float z){
    x_ = x;
    y_ = 0;
    z_ = z;
}

void vector2D::setVector(vec* vec){
    x_ = vec->getX();
    y_ = 0;
    z_ = vec->getZ();
}

void vector2D::setVector(std::vector<float> vec){
    x_ = y_ = z_ = 0;
    if(vec.size() > 0) x_ = vec[0];
    if(vec.size() > 1) y_ = 0;
    if(vec.size() > 2) z_ = vec[2];
}

void vector2D::setX(float x){
    x_ = x;
}

void vector2D::setY(float y){
    y_ = 0;
}

void vector2D::setZ(float z){
    z_ = z;
}

float vector2D::getX() const{
    return x_;
}

float vector2D::getY() const{
    return 0;
}

float vector2D::getZ() const{   
    return z_;
}

std::vector<float>& vector2D::getPositionAsVector(){
    position_ = {x_, 0, z_};
    return position_;
}

float vector2D::magnitude(){
    return std::sqrt(x_ * x_ + z_ * z_);
}

float vector2D::dot(vec* dotVec){
    return x_ * dotVec->getX() + z_ * dotVec->getZ();
}

float vector2D::distance(const vec* distVec) const{
    float diffX = x_ - distVec->getX();
    float diffY = y_ - distVec->getY();
    float diffZ = z_ - distVec->getZ();
    return std::sqrt(diffX * diffX + diffZ * diffZ);
}

vec* vector2D::scale(float magnitude){
    x_ *= magnitude;
    z_ *= magnitude;
    return this;
}

vec* vector2D::shrink(float magnitude){
    x_ /= magnitude;
    z_ /= magnitude;
    return this;
}

vec* vector2D::normalize(){
    float mag = magnitude();
    if(mag != 0){
        x_ /= mag;
        z_ /= mag;
    }
    return this; 
}

vec* vector2D::add(vec* addVec){
    x_ += addVec->getX();
    y_ = 0;
    z_ += addVec->getZ();
    return this;
}

vec* vector2D::subtract(vec* addVec){
    x_ -= addVec->getX();
    y_ = 0;
    z_ -= addVec->getZ();
    return this;
}

bool vector2D::equal(vec* cmp) const{
    return distance(cmp) < 1e-6;
}

}