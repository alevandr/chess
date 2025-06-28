#include "../../../../chess/src/chess/logic/Coordinate.h"
#include "../../../../chess/src/chess/pieces/Bishop.h"
#include "../../../../chess/src/chess/pieces/Rook.h"
#include "../../../../chess/src/chess/pieces/RookChecker.h"
#include "../../../../chess/src/chess/pieces/logic/ePieceColor.h"
#include <boost/test/unit_test.hpp>

#include <memory>

BOOST_AUTO_TEST_SUITE(MoveCheckerTests)

BOOST_AUTO_TEST_CASE(FindPosibleRookMoves_Test)
{
    const auto blackRook   = std::make_shared<Chess::Rook>(Chess::ePieceColor::BLACK, 1);
    const auto whiteBishop = std::make_shared<Chess::Bishop>(Chess::ePieceColor::WHITE, 1);
    const auto whiteRook   = std::make_shared<Chess::Rook>(Chess::ePieceColor::WHITE, 1);

    const std::vector<std::shared_ptr<Chess::Piece>> pieces      = { blackRook, whiteBishop, whiteRook };
    const auto                                       rookChecker = std::make_shared<Chess::RookChecker>();

    BOOST_CHECK_EQUAL(rookChecker->GetMoves(whiteBishop, pieces).size(), 0);

    blackRook->Move(Chess::Coordinate('A', 7));
    BOOST_CHECK_EQUAL(rookChecker->GetMoves(whiteRook, pieces).size(), 7);
}

BOOST_AUTO_TEST_SUITE_END()