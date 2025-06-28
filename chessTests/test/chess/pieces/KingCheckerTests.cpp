#include "../../../../chess/src/chess/logic/Coordinate.h"
#include "../../../../chess/src/chess/pieces/King.h"
#include "../../../../chess/src/chess/pieces/KingChecker.h"
#include "../../../../chess/src/chess/pieces/Rook.h"
#include "../../../../chess/src/chess/pieces/logic/ePieceColor.h"
#include <boost/test/unit_test.hpp>

#include <memory>

BOOST_AUTO_TEST_SUITE(MoveCheckerTests)

BOOST_AUTO_TEST_CASE(FindPosibleKingMoves_Test)
{
    const auto blackRook  = std::make_shared<Chess::Rook>(Chess::ePieceColor::BLACK, 1);
    const auto whiteKing  = std::make_shared<Chess::King>(Chess::ePieceColor::WHITE);
    const auto whiteRook1 = std::make_shared<Chess::Rook>(Chess::ePieceColor::WHITE, 1);
    const auto whiteRook2 = std::make_shared<Chess::Rook>(Chess::ePieceColor::WHITE, 2);

    const std::vector<std::shared_ptr<Chess::Piece>> pieces      = { blackRook, whiteRook1, whiteRook2, whiteKing };
    const auto                                       kingChecker = std::make_shared<Chess::KingChecker>();

    BOOST_CHECK_EQUAL(kingChecker->GetMoves(whiteRook1, pieces).size(), 0);
    BOOST_CHECK_EQUAL(kingChecker->GetMoves(whiteKing, pieces).size(), 7);

    const auto whiteRook1Coordiante = whiteRook1->GetPosition();
    whiteRook1->Move(Chess::Coordinate('G', 2));
    BOOST_CHECK_EQUAL(kingChecker->GetMoves(whiteKing, pieces).size(), 6);

    whiteRook1->Move(whiteRook1Coordiante);
    BOOST_CHECK_EQUAL(kingChecker->GetMoves(whiteKing, pieces).size(), 6);

    const auto whiteKingCoordiante = whiteKing->GetPosition();
    whiteKing->Move(Chess::Coordinate('F', 2));
    BOOST_CHECK_EQUAL(kingChecker->GetMoves(whiteKing, pieces).size(), 8);

    whiteKing->Move(whiteKingCoordiante);
    BOOST_CHECK_EQUAL(kingChecker->GetMoves(whiteKing, pieces).size(), 5);
}

BOOST_AUTO_TEST_SUITE_END()