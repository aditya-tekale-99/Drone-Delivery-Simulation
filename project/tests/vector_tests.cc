#include "gtest/gtest.h"
#include <EntityProject/project_settings.h>
#include <EntityProject/entity.h>
#include "json_helper.h"
#include <iostream>
#include <cmath>
#include <vector>

#include "../include/vector/vec.h"
#include "../include/vector/vector2D.h"
#include "../include/vector/vector3D.h"

namespace csci3081 {

using entity_project::IEntity;

class vecTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // Assign vars using a constructor
    zeroVec = new vector3D();
    iUnitVec = new vector3D(1);
    jUnitVec = new vector3D(0, 1); 
    kUnitVec = new vector3D(0, 0, 1);
    kUnitVecCopy = new vector3D(kUnit);
    kUnitVecVector = new vector3D(kUnitVec);
    kUnitVecTimes10 = new vector3D(0, 0, 10);
    finalAdditionVec = new vector3D(1, 0, 10);
    massiveVec = new vector3D(12345, 54321, 100);
    massiveVecCopy = new vector3D(massiveVec);
    negVec = new vector3D(-2, -2, -2);
  }
  virtual void TearDown() {}

  vec* zeroVec;
  vec* iUnitVec;
  vec* jUnitVec;
  vec* kUnitVec;
  vec* kUnitVecCopy;
  vec* kUnitVecVector;
  vec* kUnitVecTimes10;
  vec* massiveVec;
  vec* massiveVecCopy;
  vec* massiveVecCopy2D;
  vec* finalAdditionVec;
  vec* fiveVec;
  vec* negVec;
  std::vector<float> kUnit = {0, 0, 1};
};

class vec2DTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    // Assign vars using a constructor
    zeroVec = new vector2D();
    iUnitVec = new vector2D(1);
    jUnitVec = new vector2D(0, 1); 
    kUnitVec = new vector2D(0, 0, 1);
    kUnitVecCopy = new vector2D(kUnit);
    kUnitVecVector = new vector2D(kUnitVec);
    kUnitVecTimes10 = new vector2D(0, 0, 10);
    finalAdditionVec = new vector2D(1, 0, 10);
    massiveVec = new vector2D(12345, 54321, 100);
    massiveVecCopy = new vector2D(massiveVec);
    negVec = new vector2D(-2, -2, -2);

    threeDimVec = new vector3D(2, 2, 2);
  }
  virtual void TearDown() {}

  vec* zeroVec;
  vec* iUnitVec;
  vec* jUnitVec;
  vec* kUnitVec;
  vec* kUnitVecCopy;
  vec* kUnitVecVector;
  vec* kUnitVecTimes10;
  vec* massiveVec;
  vec* massiveVecCopy;
  vec* massiveVecCopy2D;
  vec* finalAdditionVec;
  vec* fiveVec;
  vec* negVec;
  vec* threeDimVec;
  std::vector<float> kUnit = {0, 0, 1};
};



/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(vecTest, vector3DTests){
  // test magnitude
  ASSERT_FLOAT_EQ(zeroVec->magnitude(), 0);
  ASSERT_FLOAT_EQ(iUnitVec->magnitude(), 1);
  ASSERT_FLOAT_EQ(jUnitVec->magnitude(), kUnitVec->magnitude());
  ASSERT_FLOAT_EQ(negVec->magnitude(), std::sqrt(12));


  // test dot product
  ASSERT_FLOAT_EQ(massiveVec->dot(negVec), -133532);
  ASSERT_FLOAT_EQ(negVec->dot(massiveVec), -133532);
  ASSERT_FLOAT_EQ(negVec->dot(negVec), negVec->magnitude() * negVec->magnitude());

  // test distance between two vectors
  ASSERT_FLOAT_EQ(iUnitVec->distance(jUnitVec), std::sqrt(2));
  ASSERT_FLOAT_EQ(iUnitVec->distance(negVec), std::sqrt(17));
  // test + operator

  ASSERT_FLOAT_EQ(kUnitVec->distance(kUnitVecCopy), 0);
  ASSERT_FLOAT_EQ(kUnitVec->distance(kUnitVecVector), 0);
  ASSERT_FLOAT_EQ(kUnitVec->distance(kUnitVecTimes10), 9);
  kUnitVec->scale(10);
  ASSERT_FLOAT_EQ(kUnitVec->distance(kUnitVecTimes10), 0);
  kUnitVec->add(iUnitVec);
  ASSERT_FLOAT_EQ(kUnitVec->distance(finalAdditionVec), 0);
  kUnitVec->subtract(iUnitVec);
  ASSERT_FLOAT_EQ(kUnitVec->distance(kUnitVecTimes10), 0);
  ASSERT_EQ(kUnitVec->equal(kUnitVecTimes10), true);
  kUnitVecTimes10->shrink(10);
  vec* kUnitVec_shrink = new vector3D(0, 0, 1);
  ASSERT_FLOAT_EQ(kUnitVec_shrink->distance(kUnitVecTimes10), 0);
  


  //test normalize
  vec* zeroVec_norm = new vector3D();
  vec* iUnitVec_norm = new vector3D(1);
  vec* jUnitVec_norm = new vector3D(0, 1); 
  vec* kUnitVec_norm = new vector3D(0, 0, 1);
  vec* negVec_norm = new vector3D(-2, -2, -2);
  ASSERT_EQ(zeroVec_norm->normalize()->getX(), 0);
  ASSERT_EQ(zeroVec_norm->normalize()->getY(), 0);
  ASSERT_EQ(zeroVec_norm->normalize()->getZ(), 0);

  ASSERT_EQ(iUnitVec_norm->normalize()->getX(), 1);
  ASSERT_EQ(iUnitVec_norm->normalize()->getY(), 0);
  ASSERT_EQ(iUnitVec_norm->normalize()->getZ(), 0);

  ASSERT_EQ(jUnitVec_norm->normalize()->getX(), 0);
  ASSERT_EQ(jUnitVec_norm->normalize()->getY(), 1);
  ASSERT_EQ(jUnitVec_norm->normalize()->getZ(), 0);

  ASSERT_EQ(kUnitVec_norm->normalize()->getX(), 0);
  ASSERT_EQ(kUnitVec_norm->normalize()->getY(), 0);
  ASSERT_EQ(kUnitVec_norm->normalize()->getZ(), 1);

  ASSERT_FLOAT_EQ(negVec_norm->normalize()->getX(), -2/std::sqrt(12));
  ASSERT_FLOAT_EQ(negVec_norm->normalize()->getY(), -2/std::sqrt(12));
  ASSERT_FLOAT_EQ(negVec_norm->normalize()->getZ(), -2/std::sqrt(12));

}

TEST_F(vec2DTest, 2DVectorTests){
  ASSERT_FLOAT_EQ(zeroVec->magnitude(), 0);
  ASSERT_FLOAT_EQ(iUnitVec->magnitude(), 1);
  ASSERT_FLOAT_EQ(jUnitVec->magnitude(), 0);
  ASSERT_FLOAT_EQ(negVec->magnitude(), std::sqrt(8));

  // test dot product
  ASSERT_FLOAT_EQ(massiveVec->dot(negVec), -24890);
  ASSERT_FLOAT_EQ(negVec->dot(massiveVec), -24890);
  ASSERT_FLOAT_EQ(negVec->dot(negVec), negVec->magnitude() * negVec->magnitude());
  ASSERT_FLOAT_EQ(negVec->dot(negVec), 8);
  ASSERT_FLOAT_EQ(negVec->dot(threeDimVec), -8);

  // test distance between two vectors
  ASSERT_FLOAT_EQ(iUnitVec->distance(jUnitVec), 1);
  ASSERT_FLOAT_EQ(iUnitVec->distance(kUnitVec), std::sqrt(2));
  ASSERT_FLOAT_EQ(iUnitVec->distance(negVec), std::sqrt(13));
  ASSERT_FLOAT_EQ(negVec->distance(threeDimVec), std::sqrt(32));
  // test + operator

  ASSERT_FLOAT_EQ(kUnitVec->distance(kUnitVecCopy), 0);
  ASSERT_FLOAT_EQ(kUnitVec->distance(kUnitVecVector), 0);
  ASSERT_FLOAT_EQ(kUnitVec->distance(kUnitVecTimes10), 9);
  kUnitVec->scale(10);
  ASSERT_FLOAT_EQ(kUnitVec->distance(kUnitVecTimes10), 0);
  kUnitVec->add(iUnitVec);
  ASSERT_FLOAT_EQ(kUnitVec->distance(finalAdditionVec), 0);
  kUnitVec->add(jUnitVec);
  ASSERT_FLOAT_EQ(kUnitVec->distance(finalAdditionVec), 0);
  kUnitVec->subtract(iUnitVec);
  ASSERT_FLOAT_EQ(kUnitVec->distance(kUnitVecTimes10), 0);
  ASSERT_EQ(kUnitVec->equal(kUnitVecTimes10), true);

  //test normalize
  vec* zeroVec_norm = new vector2D();
  vec* iUnitVec_norm = new vector2D(1);
  vec* jUnitVec_norm = new vector2D(0, 1); 
  vec* kUnitVec_norm = new vector2D(0, 0, 1);
  vec* negVec_norm = new vector2D(-2, -2, -2);
  ASSERT_EQ(zeroVec_norm->normalize()->getX(), 0);
  ASSERT_EQ(zeroVec_norm->normalize()->getY(), 0);
  ASSERT_EQ(zeroVec_norm->normalize()->getZ(), 0);

  ASSERT_EQ(iUnitVec_norm->normalize()->getX(), 1);
  ASSERT_EQ(iUnitVec_norm->normalize()->getY(), 0);
  ASSERT_EQ(iUnitVec_norm->normalize()->getZ(), 0);

  ASSERT_EQ(jUnitVec_norm->normalize()->getX(), 0);
  ASSERT_EQ(jUnitVec_norm->normalize()->getY(), 0);
  ASSERT_EQ(jUnitVec_norm->normalize()->getZ(), 0);

  ASSERT_EQ(kUnitVec_norm->normalize()->getX(), 0);
  ASSERT_EQ(kUnitVec_norm->normalize()->getY(), 0);
  ASSERT_EQ(kUnitVec_norm->normalize()->getZ(), 1);

  ASSERT_FLOAT_EQ(negVec_norm->normalize()->getX(), -2/std::sqrt(8));
  ASSERT_FLOAT_EQ(negVec_norm->normalize()->getY(), 0);
  ASSERT_FLOAT_EQ(negVec_norm->normalize()->getZ(), -2/std::sqrt(8));
  
}


}  // namespace csci3081

