#pragma once

#include "../src/global_var.hpp"
#include <gtest/gtest.h>

TEST(GlobalVarTest, GravityTest) {
  GlobalVar &instance = GlobalVar::getInstance();
  instance.setGravity(12.3);
  EXPECT_DOUBLE_EQ(12.3, instance.getGravity());
}

TEST(GlobalVarTest, FieldSizeTest) {
  GlobalVar &instance = GlobalVar::getInstance();
  instance.setFieldSizeX_Y(800, 600);
  EXPECT_EQ(800, instance.getFieldSizeX());
  EXPECT_EQ(600, instance.getFieldSizeY());
}

TEST(GlobalVarTest, ParticleSizeTest) {
  GlobalVar &instance = GlobalVar::getInstance();
  instance.setParticleSize(0.25);
  EXPECT_DOUBLE_EQ(0.25, instance.getMaxPartSize());
}
// GlobalVar &gv = GlobalVar::getInstance();//TODO0 does gv is the same for
// every file?
TEST(GlobalVarTest, GlobalVarInstance) {
  GlobalVar &instance = GlobalVar::getInstance();
  instance.setGravity(12.66);
  GlobalVar &instance2 = GlobalVar::getInstance();
  EXPECT_EQ(&instance, &instance2);
}
