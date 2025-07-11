#pragma once

#include <boost/signals2.hpp>

#include <memory>

namespace Chess
{
    class Chessboard;
    struct Coordinate;

    class Controller
    {
    private:
        std::shared_ptr<Chessboard> m_chessboard;

        boost::signals2::signal<void()> m_signalMove;

    public:
        explicit Controller(const std::shared_ptr<Chessboard>& chessboard);

        bool TryInitPiece(const Coordinate& from) const;
        bool TryMovePiece(const Coordinate& to) const;

        boost::signals2::connection ConnectMove(const boost::signals2::signal<void()>::slot_type& subscriber);
    };
} // namespace Chess
