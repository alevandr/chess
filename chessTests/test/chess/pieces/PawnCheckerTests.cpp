#include "../../../../chess/src/chess/logic/Coordinate.h"
#include "../../../../chess/src/chess/logic/Sizes.h"
#include "../../../../chess/src/chess/pieces/King.h"
#include "../../../../chess/src/chess/pieces/Pawn.h"
#include "../../../../chess/src/chess/pieces/PawnChecker.h"
#include "../../../../chess/src/chess/pieces/Queen.h"
#include "../../../../chess/src/chess/pieces/logic/ePieceColor.h"
#include <boost/test/unit_test.hpp>

#include <memory>

BOOST_AUTO_TEST_SUITE(MoveCheckerTests)

BOOST_AUTO_TEST_CASE(FindPosiblePawnMoves_Test)
{
    const auto blackKing  = std::make_shared<Chess::King>(Chess::ePieceColor::BLACK);
    const auto blackPawn  = std::make_shared<Chess::Pawn>(Chess::ePieceColor::BLACK, 'D');
    const auto whitePawn  = std::make_shared<Chess::Pawn>(Chess::ePieceColor::WHITE, 'B');
    const auto whiteQueen = std::make_shared<Chess::Queen>(Chess::ePieceColor::WHITE);

    const std::vector<std::shared_ptr<Chess::Piece>> pieces      = { blackKing, blackPawn, whitePawn, whiteQueen };
    const auto                                       pawnChecker = std::make_shared<Chess::PawnChecker>();

    BOOST_CHECK_EQUAL(pawnChecker->GetMoves(blackKing, pieces).size(), 0);
    BOOST_CHECK_EQUAL(pawnChecker->GetMoves(whitePawn, pieces).size(), 2);

    blackKing->Move(Chess::Coordinate('B', 3));
    BOOST_CHECK_EQUAL(pawnChecker->GetMoves(whitePawn, pieces).size(), 0);

    blackKing->Move(Chess::Coordinate('C', 3));
    whiteQueen->Move(Chess::Coordinate('A', 3));
    BOOST_CHECK_EQUAL(pawnChecker->GetMoves(whitePawn, pieces).size(), 3);

    whitePawn->Move(Chess::Coordinate('B', Chess::CHESSBOARD_SIZE - 1));
    BOOST_CHECK_EQUAL(pawnChecker->GetMoves(whitePawn, pieces).size(), 1);

    whitePawn->Move(Chess::Coordinate('B', Chess::CHESSBOARD_SIZE));
    BOOST_CHECK_EQUAL(pawnChecker->GetMoves(whitePawn, pieces).size(), 0);

    blackKing->Move(Chess::Coordinate('B', Chess::CHESSBOARD_SIZE - 3));
    whitePawn->Move(Chess::Coordinate('C', Chess::CHESSBOARD_SIZE - 3));
    blackPawn->Move(Chess::Coordinate('D', Chess::CHESSBOARD_SIZE - 3));
    BOOST_CHECK_EQUAL(pawnChecker->GetMoves(whitePawn, pieces).size(), 2);
}

BOOST_AUTO_TEST_SUITE_END()