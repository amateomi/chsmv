/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "square.h"

#include "gtest/gtest.h"

using namespace chsmv;

TEST(SquareConstructorTest, constructorThrow) {
  EXPECT_THROW(Square square{""}, std::domain_error) << "Empty string";

  EXPECT_NO_THROW(Square square{"a1"}) << "First square on the board";
  EXPECT_NO_THROW(Square square{"e4"}) << "Middle square on the board";
  EXPECT_NO_THROW(Square square{"h8"}) << "Last square on the board";

  EXPECT_THROW(Square square{"j1"}, std::domain_error) << "j is invalid file (valid are a-h)";
  EXPECT_THROW(Square square{"a9"}, std::domain_error) << "9 is invalid rank (valid are 1-8)";
  EXPECT_THROW(Square square{"e0"}, std::domain_error) << "0 is invalid rank (valid are 1-8)";

  EXPECT_THROW(Square square{"  e4 "}, std::domain_error) << "Extra spaces";
  EXPECT_THROW(Square square{"a1e4"}, std::domain_error) << "Two squares";
}

class SquareTest : public ::testing::Test {
 public:
  SquareTest() = default;

 protected:
  Square a_1_{"a1"};
  Square d_1_{"d1"};
  Square a_3_{"a3"};
  Square e_4_{"e4"};
  Square h_8_{"h8"};
};

TEST_F(SquareTest, string_cast) {
  EXPECT_EQ(static_cast<std::string>(a_1_), "a1");
  EXPECT_EQ(static_cast<std::string>(d_1_), "d1");
  EXPECT_EQ(static_cast<std::string>(a_3_), "a3");
  EXPECT_EQ(static_cast<std::string>(e_4_), "e4");
  EXPECT_EQ(static_cast<std::string>(h_8_), "h8");
}
