/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"

#include "engine.h"

#include "gtest/gtest.h"

TEST(LegalMovesTest, KingLegalMove) {
  // White
  {
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
  // Black
  {
    chsmv::Board board{"8/4PqpB/1K5p/2P5/PP3p2/P7/1br2k2/n5N1 b - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 1, 1, 1, 0,
      0, 0, 0, 0, 1, 0, 1, 0,
      0, 0, 0, 0, 1, 1, 1, 0,
        // clang-format on
    };
    EXPECT_EQ(chsmv::Engine::GetAllLegalMoves(board, chsmv::Square{"f2"}), expect);
  }
}

TEST(LegalMovesTest, QueenLegalMove) {
  // White
  {
    chsmv::Board board{"2n3QR/4P2n/1p3p2/1p2p3/P7/pK2b3/P3P3/4k3 w - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      0, 0, 1, 1, 1, 1, 0, 0,
      0, 0, 0, 0, 0, 1, 1, 1,
      0, 0, 0, 0, 1, 0, 1, 0,
      0, 0, 0, 1, 0, 0, 1, 0,
      0, 0, 1, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 1, 0,
        // clang-format on
    };
    EXPECT_EQ(chsmv::Engine::GetAllLegalMoves(board, chsmv::Square{"g8"}), expect);
  }
  // Black
  {
    chsmv::Board board{"2k5/5b1p/1K6/2r3np/3P3B/N2p2P1/P3q2P/7Q b - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 1, 0, 1, 0,
      0, 0, 0, 0, 1, 1, 0, 0,
      1, 1, 1, 1, 0, 1, 1, 1,
      0, 0, 0, 1, 1, 1, 0, 0,
        // clang-format on
    };
    EXPECT_EQ(chsmv::Engine::GetAllLegalMoves(board, chsmv::Square{"e2"}), expect);
  }
}

TEST(LegalMovesTest, RookLegalMove) {
  // White
  {
    chsmv::Board board{"K2n1r2/4p2R/N7/3P2p1/PB6/4nP2/3Pb3/2k4r w - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 1, 1, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 1,
        // clang-format on
    };
    EXPECT_EQ(chsmv::Engine::GetAllLegalMoves(board, chsmv::Square{"h7"}), expect);
  }
  // Black
  {
    chsmv::Board board{"3R4/P3NB2/n3pK2/br1p1n2/P7/7k/1Brp4/8 b - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0,
      0, 1, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0,
        // clang-format on
    };
    EXPECT_EQ(chsmv::Engine::GetAllLegalMoves(board, chsmv::Square{"c2"}), expect);
  }
}

TEST(LegalMovesTest, BishopLegalMove) {
  // White
  {
    chsmv::Board board{"8/2P4p/2p5/b3B3/2K1pPbP/4k3/1P2P1pr/n7 w - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      0, 0, 0, 0, 0, 0, 0, 1,
      0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 1, 0, 1, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
        // clang-format on
    };
    EXPECT_EQ(chsmv::Engine::GetAllLegalMoves(board, chsmv::Square{"e5"}), expect);
  }
  // Black
  {
    chsmv::Board board{"1N4nN/P6P/1p4P1/2k3pK/2p5/2P1r1P1/2b5/5Q2 b - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 1, 0, 0,
      1, 0, 0, 0, 1, 0, 0, 0,
      0, 1, 0, 1, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 1, 0, 1, 0, 0, 0, 0,
        // clang-format on
    };
    EXPECT_EQ(chsmv::Engine::GetAllLegalMoves(board, chsmv::Square{"c2"}), expect);
  }
}

TEST(LegalMovesTest, PawnLegalMove) {
  // White
  {
    chsmv::Board board{"3r2B1/P7/1P4Rp/1Q6/pp5k/1r5P/2P5/1n2R1K1 w - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 1, 0, 0, 0, 0, 0,
      0, 1, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
        // clang-format on
    };
    EXPECT_EQ(chsmv::Engine::GetAllLegalMoves(board, chsmv::Square{"c2"}), expect);
  }
  // Black
  {
    chsmv::Board board{"3B4/r6p/pK1pP1PP/5bp1/7b/3n4/qPkP4/3r4 b - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 1, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
        // clang-format on
    };
    EXPECT_EQ(chsmv::Engine::GetAllLegalMoves(board, chsmv::Square{"h7"}), expect);
  }
}

#pragma clang diagnostic pop
