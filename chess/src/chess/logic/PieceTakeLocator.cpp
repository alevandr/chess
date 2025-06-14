#include "PieceTakeLocator.h"

#include "Coordinate.h"
#include "../pieces/Piece.h"
#include "../pieces/logic/PieceColorAndType.h"
#include "../pieces/logic/PieceFinder.h"
#include "../pieces/Pawn.h"

#include <memory>

Chess::Coordinate Chess::PieceTakeLocator::Find(std::shared_ptr<Piece> const& piece, std::vector<std::shared_ptr<Piece>> const& piecesOnBoard, Coordinate to)
{
	auto pawnOnPassCoordinate = Coordinate(to.GetFile(), piece->GetPosition().GetRank());
	auto finder = std::make_shared<PieceFinder>(piecesOnBoard);
	auto currentPawn = std::dynamic_pointer_cast<Pawn>(piece);
	auto opponentPawn = std::dynamic_pointer_cast<Pawn>(finder->Find(pawnOnPassCoordinate));

	if (currentPawn && opponentPawn
		&& opponentPawn->GetCanEnPassant()
		&& opponentPawn->GetColorAndType().GetColor() != currentPawn->GetColorAndType().GetColor())
	{
		return pawnOnPassCoordinate;
	}
	else
	{
		return to;
	}
}
