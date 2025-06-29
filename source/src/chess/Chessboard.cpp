#include "Chessboard.h"

#include "Player.h"
#include "logic/Coordinate.h"
#include "logic/MoveValidator.h"
#include "logic/PieceDirector.h"
#include "logic/PieceSignalDirector.h"
#include "pieces/Piece.h"
#include "pieces/logic/ePieceColor.h"

Chess::Chessboard::Chessboard(const std::vector<std::shared_ptr<Piece>>& piecesOnBoard, std::shared_ptr<PieceSignalDirector> signalDirector)
{
    m_piecesOnBoard = piecesOnBoard;
    m_director      = std::make_shared<PieceDirector>(m_piecesOnBoard, signalDirector);
    m_validator     = std::make_shared<MoveValidator>(m_piecesOnBoard, std::make_shared<Player>(ePieceColor::WHITE, signalDirector));
}

Chess::Coordinate Chess::Chessboard::GetFrom() const
{
    return m_from;
}

const std::shared_ptr<Chess::MoveValidator>& Chess::Chessboard::GetMoveValidator() const
{
    return m_validator;
}

const std::shared_ptr<Chess::PieceDirector>& Chess::Chessboard::GetPieceDirector() const
{
    return m_director;
}

Chess::Coordinate Chess::Chessboard::GetTo() const
{
    return m_to;
}

bool Chess::Chessboard::TryInitPiece(const Coordinate& from)
{
    m_from = from;
    m_to   = Coordinate(0, 0);
    m_director->InitCurrentPiece(from);

    if (!m_director->GetCurrentPiece())
    {
        return false;
    }

    m_validator->CalculatePossibleMoves(m_director->GetCurrentPiece());

    if (m_validator->GetPossibleMoves().size() < 1)
    {
        return false;
    }

    m_signalChessboardUndated();

    return true;
}

bool Chess::Chessboard::TryMovePiece(const Coordinate& to)
{
    m_to = to;

    if (!m_validator->IsValidMove(m_director->GetCurrentPiece(), to))
    {
        return false;
    }

    m_validator->ClearPossibleMoves();
    m_validator->ClearPiecesCanMove();
    m_director->MovePiece(to, m_signalChessboardUndated);
    m_validator->CalculatePiecesCanMove();

    m_signalChessboardUndated();

    return true;
}

boost::signals2::connection Chess::Chessboard::ConnectChessboardUpdated(const boost::signals2::signal<void()>::slot_type& subscriber)
{
    return m_signalChessboardUndated.connect(subscriber);
}
