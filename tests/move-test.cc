/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "move.h"

#include "gtest/gtest.h"

TEST(MoveConstructorTest, constructorThrow) {
  EXPECT_THROW(chsmv::Move move{""}, std::domain_error) << "Empty string";

  EXPECT_NO_THROW(chsmv::Move move{"e2e4"}) << "Ordinary move";
  EXPECT_NO_THROW(chsmv::Move move{"g7a5"}) << "Invalid move for any standard piece, but still valid combination";
  EXPECT_NO_THROW(chsmv::Move move{"e1g1"}) << "White short castling";
  EXPECT_NO_THROW(chsmv::Move move{"e7e8q"}) << "White pawn promotion";
  EXPECT_NO_THROW(chsmv::Move move{"g3c1n"}) << "Invalid promotion for standard pawn, but still valid combination";

  EXPECT_THROW(chsmv::Move move{"j1"}, std::domain_error) << "End square not present";
  EXPECT_THROW(chsmv::Move move{"  a9"}, std::domain_error) << "Start square not present";
  EXPECT_THROW(chsmv::Move move{"e1f3k"}, std::domain_error) << "Unknown promotion target";
  EXPECT_THROW(chsmv::Move move{"e1f3qn"}, std::domain_error) << "Extra promotion targets";

  EXPECT_THROW(chsmv::Square square{"  e4e5 "}, std::domain_error) << "Extra spaces";
  EXPECT_THROW(chsmv::Square square{"h6a3b2q"}, std::domain_error) << "Three squares in move direction";
}

class MoveTest : public ::testing::Test {
 public:
  MoveTest() = default;

 protected:
  chsmv::Move queen_{"a1a1q"};
  chsmv::Move rook_{"b2b2r"};
  chsmv::Move bishop_{"c3c3b"};
  chsmv::Move knight_{"d4d4n"};
  chsmv::Move none_{"e5e5"};

  chsmv::Move e_2_e_4_{"e2e4"};
  chsmv::Move c_2_c_1_q_{"c2c1q"};

  chsmv::Move file_positive_{"f4e2"};
  chsmv::Move file_negative_{"a1h8"};

  chsmv::Move rank_positive_{"c2d8"};
  chsmv::Move rank_negative_{"f3b1"};
};

TEST_F(MoveTest, string_cast) {
  EXPECT_EQ(static_cast<std::string>(e_2_e_4_), "e2e4");
  EXPECT_EQ(static_cast<std::string>(c_2_c_1_q_), "c2c1q");
}

TEST_F(MoveTest, promotion) {
  EXPECT_EQ(queen_.promotion, chsmv::Promotion::TO_QUEEN);
  EXPECT_EQ(rook_.promotion, chsmv::Promotion::TO_ROOK);
  EXPECT_EQ(bishop_.promotion, chsmv::Promotion::TO_BISHOP);
  EXPECT_EQ(knight_.promotion, chsmv::Promotion::TO_KNIGHT);
  EXPECT_EQ(none_.promotion, chsmv::Promotion::NONE);
}

TEST_F(MoveTest, direction) {
  EXPECT_EQ(file_positive_.FileDirection(), 1);
  EXPECT_EQ(file_negative_.FileDirection(), -1);
  EXPECT_EQ(rank_positive_.RankDirection(), 1);
  EXPECT_EQ(rank_negative_.RankDirection(), -1);
}
