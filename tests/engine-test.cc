/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "modernize-use-bool-literals"

#include "engine.h"

#include "gtest/gtest.h"

using namespace chsmv;

TEST(LegalMovesTest, KingLegalMove) {
  // White
  {
    Board board{"3N4/1p3K2/1Bp2P2/P2p4/2P5/4RpP1/kn1p1b2/8 w - - 0 1"};
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
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"f7"}), expect);
  }
  // Black
  {
    Board board{"8/4PqpB/1K5p/2P5/PP3p2/P7/1br2k2/n5N1 b - - 0 1"};
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
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"f2"}), expect);
  }
}

TEST(LegalMovesTest, QueenLegalMove) {
  // White
  {
    Board board{"2n3QR/4P2n/1p3p2/1p2p3/P7/pK2b3/P3P3/4k3 w - - 0 1"};
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
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"g8"}), expect);
  }
  // Black
  {
    Board board{"2k5/5b1p/1K6/2r3np/3P3B/N2p2P1/P3q2P/7Q b - - 0 1"};
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
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"e2"}), expect);
  }
}

TEST(LegalMovesTest, RookLegalMove) {
  // White
  {
    Board board{"K2n1r2/4p2R/N7/3P2p1/PB6/4nP2/3Pb3/2k4r w - - 0 1"};
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
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"h7"}), expect);
  }
  // Black
  {
    Board board{"3R4/P3NB2/n3pK2/br1p1n2/P7/7k/1Brp4/8 b - - 0 1"};
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
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"c2"}), expect);
  }
}

TEST(LegalMovesTest, BishopLegalMove) {
  // White
  {
    Board board{"8/2P4p/2p5/b3B3/2K1pPbP/4k3/1P2P1pr/n7 w - - 0 1"};
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
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"e5"}), expect);
  }
  // Black
  {
    Board board{"1N4nN/P6P/1p4P1/2k3pK/2p5/2P1r1P1/2b5/5Q2 b - - 0 1"};
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
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"c2"}), expect);
  }
}

TEST(LegalMoveTest, KnightLegalMove) {
  // White
  {
    Board board{"5b2/P1pp1p2/1N5P/1PpR4/2p3p1/1P2k3/6n1/2K5 w - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      1, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 1, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      1, 0, 1, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
        // clang-format on
    };
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"b6"}), expect);
  }
  // Black
  {
    Board board{"1q2N3/3pR1n1/1R3P2/K1kP3N/5Q2/7B/p2p3P/8 b - - 0 1"};
    std::vector<bool> expect{
        // clang-format off
      0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 1, 0, 0, 0,
      0, 0, 0, 0, 0, 1, 0, 1,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
      0, 0, 0, 0, 0, 0, 0, 0,
        // clang-format on
    };
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"g7"}), expect);
  }
}

TEST(LegalMovesTest, PawnLegalMove) {
  // White
  {
    Board board{"3r2B1/P7/1P4Rp/1Q6/pp5k/1r5P/2P5/1n2R1K1 w - - 0 1"};
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
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"c2"}), expect);
  }
  // Black
  {
    Board board{"3B4/r6p/pK1pP1PP/5bp1/7b/3n4/qPkP4/3r4 b - - 0 1"};
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
    EXPECT_EQ(Engine::GetAllLegalMoves(board, Square{"h7"}), expect);
  }
}

TEST(LegalMovesTest, PawnPromotion) {
  EXPECT_EQ(Engine::IsLegalMove(Board{"Qr5k/K1P1R2B/6p1/p7/p1P4p/P1q2p2/5B2/8 w - - 0 1"}, Move{"c7b8"}),
            MoveDescription::PAWN_PROMOTION_NOT_SPECIFIED);
  EXPECT_EQ(Engine::IsLegalMove(Board{"b1B5/3P4/PRN2P2/4Nk2/n4p2/5p2/3K1p1p/r7 b - - 0 1"}, Move{"h2h1"}),
            MoveDescription::PAWN_PROMOTION_NOT_SPECIFIED);
}

TEST(ProcessMoveTest, ProcessSimpleMoves) {
  EXPECT_EQ(static_cast<std::string>(
                Engine::ProcessMove(Board{"8/P5n1/2P5/Kn5k/p3PB2/8/3R1pbp/2Nqb3 w - - 0 1"}, Move{"f4h2"})),
            "8/P5n1/2P5/Kn5k/p3P3/8/3R1pbB/2Nqb3 b - - 0 1");
  EXPECT_EQ(static_cast<std::string>(
                Engine::ProcessMove(Board{"8/5PPp/Pk2B1p1/5nP1/1K3b2/1b1N1r2/p2p4/8 w - - 0 1"}, Move{"b4b3"})),
            "8/5PPp/Pk2B1p1/5nP1/5b2/1K1N1r2/p2p4/8 b - - 0 1");
  EXPECT_EQ(static_cast<std::string>(
                Engine::ProcessMove(Board{"6n1/Bp1Pp1r1/6P1/k2p4/P7/1R6/P1P5/K1b2n2 b - - 0 1"}, Move{"b7b5"})),
            "6n1/B2Pp1r1/6P1/kp1p4/P7/1R6/P1P5/K1b2n2 w - b6 0 2");
  EXPECT_EQ(static_cast<std::string>(
                Engine::ProcessMove(Board{"8/P2n1p2/qp4B1/p7/3pN2K/8/p1kP4/BR2r3 b - - 0 1"}, Move{"d7c5"})),
            "8/P4p2/qp4B1/p1n5/3pN2K/8/p1kP4/BR2r3 w - - 1 2");
}

#pragma clang diagnostic pop
