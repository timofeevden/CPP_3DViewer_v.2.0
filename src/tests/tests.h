#ifndef CPP4_3DVIEWER_V2_0_1_SRC_TEST_TEST_H_
#define CPP4_3DVIEWER_V2_0_1_SRC_TEST_TEST_H_

#include <gtest/gtest.h>

#include <array>
#include <vector>

#include "../model/model.h"

constexpr float epsilon = 1e-6;

#define EXPECT_EQUAL_VERTEX(result, expected)   \
  {                                             \
    EXPECT_NEAR(result.x, expected.x, epsilon); \
    EXPECT_NEAR(result.y, expected.y, epsilon); \
    EXPECT_NEAR(result.z, expected.z, epsilon); \
  }

#define EXPECT_EQUAL_POLYGONS(result, expected) \
  {                                             \
    EXPECT_EQ(result.pol[0], expected.pol[0]);  \
    EXPECT_EQ(result.pol[1], expected.pol[1]);  \
  }

#endif  // CPP4_3DVIEWER_V2_0_1_SRC_TEST_TEST_H_
