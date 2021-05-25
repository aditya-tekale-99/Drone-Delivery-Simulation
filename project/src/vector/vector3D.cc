#include "vector/vector3D.h"

namespace csci3081{

vector3D::~vector3D() {}

vector3D::vector3D(float x, float y, float z){
    x_ = x;
    y_ = y;
    z_ = z;
}

vector3D::vector3D(const vec* vec){
    x_ = vec->getX();
    y_ = vec->getY();
    z_ = vec->getZ();
}

vector3D::vector3D(const std::vector<float>& v){
    x_ = y_ = z_ = 0;
    if(v.size() > 0) x_ = v[0];
    if(v.size() > 1) y_ = v[1];
    if(v.size() > 2) z_ = v[2];
}

void vector3D::setVector(float x, float y, float z){
    x_ = x;
    y_ = y;
    z_ = z;
}

void vector3D::setVector(vec* vec){
    x_ = vec->getX();
    y_ = vec->getY();
    z_ = vec->getZ();
}

void vector3D::setVector(std::vector<float> vec){
    x_ = y_ = z_ = 0;
    if(vec.size() > 0) x_ = vec[0];
    if(vec.size() > 1) y_ = vec[1];
    if(vec.size() > 2) z_ = vec[2];
}


void vector3D::setX(float x){
    x_ = x;
}

void vector3D::setY(float y){
    y_ = y;
}

void vector3D::setZ(float z){
    z_ = z;
}

float vector3D::getX() const{
    return x_;
}

float vector3D::getY() const{
    return y_;
}

float vector3D::getZ() const{   
    return z_;
}

std::vector<float>& vector3D::getPositionAsVector(){
    position_ = {x_, y_, z_};
}

float vector3D::magnitude(){
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_);
}

float vector3D::dot(vec* dotVec){
    return x_ * dotVec->getX() + y_ * dotVec->getY() + z_ * dotVec->getZ();
}

float vector3D::distance(const vec* distVec) const{
    float diffX = x_ - distVec->getX();
    float diffY = y_ - distVec->getY();
    float diffZ = z_ - distVec->getZ();
    float res = std::sqrt(diffX * diffX + diffY * diffY + diffZ * diffZ);
    return res;
}

vec* vector3D::scale(float magnitude){
    x_ *= magnitude;
    y_ *= magnitude;
    z_ *= magnitude;
    return this;
}

vec* vector3D::shrink(float magnitude){
    x_ /= magnitude;
    y_ /= magnitude;
    z_ /= magnitude;
    return this;
}

vec* vector3D::normalize(){
    float mag = magnitude();
    if(mag != 0){
        x_ /= mag;
        y_ /= mag;
        z_ /= mag;
    }
    return this;
}

vec* vector3D::add(vec* addVec){
    x_ += addVec->getX();
    y_ += addVec->getY();
    z_ += addVec->getZ();
    return this;
}

vec* vector3D::subtract(vec* addVec){
    x_ -= addVec->getX();
    y_ -= addVec->getY();
    z_ -= addVec->getZ();
    return this;
}

bool vector3D::equal(vec* cmp) const{
    return distance(cmp) < 1e-6;
}

}