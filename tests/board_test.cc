/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "clion-misra-cpp2008-11-0-1"
#pragma ide diagnostic ignored "clion-misra-cpp2008-6-4-5"
#pragma ide diagnostic ignored "clion-misra-cpp2008-6-4-1"
#pragma ide diagnostic ignored "clion-misra-cpp2008-6-3-1"
#pragma ide diagnostic ignored "clion-misra-cpp2008-8-0-1"
#pragma ide diagnostic ignored "clion-misra-cpp2008-5-0-4"
#pragma ide diagnostic ignored "clion-misra-cpp2008-18-4-1"

#include "board.h"

#include "gtest/gtest.h"

TEST(BoardConstructorTest, constructorThrow) {
  EXPECT_THROW(chsmv::Board board{""}, std::domain_error) << "Empty string";

  EXPECT_NO_THROW(chsmv::Board board) << "Start board";

  EXPECT_NO_THROW(chsmv::Board board{"rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"});
  EXPECT_NO_THROW(chsmv::Board board{"rnbqkbnr/pppppppp/8/8/4P3/8/PPPP1PPP/RNBQKBNR b KQkq e3 0 1"});
  EXPECT_NO_THROW(chsmv::Board board{"rnbqkbnr/pp1ppppp/8/2p5/4P3/8/PPPP1PPP/RNBQKBNR w KQkq c6 0 2"});
  EXPECT_NO_THROW(chsmv::Board board{"rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2"});
  EXPECT_NO_THROW(chsmv::Board board{"8/4b3/4P3/1k4P1/8/ppK5/8/4R3 b - - 1 45"});
  EXPECT_NO_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3 w - - 5 39"});
  EXPECT_NO_THROW(chsmv::Board board{"r2q1rk1/pp2ppbp/2p2np1/6B1/3PP1b1/Q1P2N2/P4PPP/3RKB1R b K - 0 13"});

  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 w - - 5 39"}, std::domain_error) << "9 ranks";
  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/9/8/4P3/4K3 w - - 5 39"}, std::domain_error) << "Too long rank";
  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8nK/8/4P3/4K3 w - - 5 39"}, std::domain_error) << "Too long rank";

  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 - - 5 39"}, std::domain_error) << "No move side";

  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 b - 5 39"}, std::domain_error) << "No castling info";
  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 b kK - 5 39"}, std::domain_error)
      << "Castling info is in wrong order";
  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 b zxc - 5 39"}, std::domain_error)
      << "Invalid castling info";

  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 w - 5 39"}, std::domain_error) << "No en passant info";
  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 w - c6h3 5 39"}, std::domain_error) << "Invalid en passant data";
  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 w - a1 5 39"}, std::domain_error) << "Invalid en passant square";

  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 w - -"}, std::domain_error) << "No clocks";
  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 w - - 51 39"}, std::domain_error) << "halfmove clock is overloaded";
  EXPECT_THROW(chsmv::Board board{"4k3/8/8/8/8/8/4P3/4K3/8 w - - 13"}, std::domain_error) << "No fullmove clock";
}

#pragma clang diagnostic pop
