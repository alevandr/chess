#include "Pawn.h"

#include "logic/PieceColorAndType.h"
#include "../logic/Coordinate.h"
#include "../logic/eError.h"
#include "../logic/ErrorConverter.h"
#include "../logic/PieceSignalDirector.h"
#include "../logic/Sizes.h"


#include <stdexcept>

Chess::Pawn::Pawn(ePieceColor color, char file)
{
	if (file < 'A' || file > 'A' + CHESSBOARD_SIZE - 1)
	{
		throw std::out_of_range(ErrorConverter::ToString(Chess::eError::OUT_OF_CHESSBOARD));
	}

	m_colorAndType = PieceColorAndType(color, ePieceType::PAWN);

	switch (color)
	{
	case Chess::ePieceColor::BLACK:
		m_position = Coordinate(file, CHESSBOARD_SIZE - 1);
		break;
	case Chess::ePieceColor::WHITE:
		m_position = Coordinate(file, 2);
		break;
	default:
		throw std::out_of_range(ErrorConverter::ToString(Chess::eError::OUT_OF_CHESSBOARD));
	}
}

Chess::Pawn::Pawn(ePieceColor color, char file, std::shared_ptr<PieceSignalDirector> const& signalDirector) : Pawn(color, file)
{
	MakeTracking(signalDirector);
}

Chess::Pawn::Pawn(ePieceColor color, Coordinate const& coordinate)
	: Piece(PieceColorAndType(color, ePieceType::PAWN), coordinate) { }

Chess::Pawn::Pawn(ePieceColor color, Coordinate const& coordinate, std::shared_ptr<PieceSignalDirector> const& signalDirector) : Pawn(color, coordinate)
{
	MakeTracking(signalDirector);
}

void Chess::Pawn::LostEnPassant()
{
	m_canEnPassant = false;
}

void Chess::Pawn::MakeTracking(std::shared_ptr<Chess::PieceSignalDirector> const& signalDirector)
{
	if (!signalDirector)
	{
		return;
	}

	signalDirector->ConnectMove([this]()
		{
			if (!m_isOnPawnFirstMove)
			{
				LostEnPassant();
			}

			m_isOnPawnFirstMove = false;
		});
}

bool Chess::Pawn::GetCanEnPassant() const
{
	return m_canEnPassant;
}

bool Chess::Pawn::GetIsNotMoved() const
{
	return m_isNotMoved;
}

void Chess::Pawn::Move(Coordinate to, bool isRealMove)
{
	if(isRealMove)
	{
		if (abs(to.GetRank() - GetPosition().GetRank()) == 2)
		{
			m_canEnPassant = m_isNotMoved;
		}
		else
		{
			LostEnPassant();
		}

		m_isOnPawnFirstMove = m_isNotMoved;
		m_isNotMoved = false;
	}

	Piece::Move(to);
}
