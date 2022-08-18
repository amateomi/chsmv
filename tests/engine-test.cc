/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"

#include "engine.h"

#include "gtest/gtest.h"

TEST(LegalMovesTest, King) {
  chsmv::Board board{"3N4/1p3K2/1Bp2P2/P2p4/2P5/4RpP1/kn1p1b2/8 w - - 0 1"};
  std::vector<bool> expect{
      // clang-format off
      0, 0, 0, 0, 1, 1, 1, 0,
      0, 0, 0, 0, 1, 0, 1, 0,
      0, 0, 0, 0, 1, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      // clang-format on
  };
  EXPECT_EQ(chsmv::Engine::GetAllLegalMoves(board, chsmv::Square{"f7"}), expect);
}

#pragma clang diagnostic pop
