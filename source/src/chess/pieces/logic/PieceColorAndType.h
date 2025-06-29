#pragma once

#include "ePieceColor.h"
#include "ePieceType.h"

namespace Chess
{
    struct PieceColorAndType
    {
        ePieceColor m_color;
        ePieceType  m_type;

    public:
        PieceColorAndType();
        PieceColorAndType(ePieceColor color, ePieceType type);

        ePieceColor GetColor() const;
        ePieceType  GetType() const;

        PieceColorAndType& operator=(const PieceColorAndType& other);
        bool               operator==(const PieceColorAndType& other) const;
    };
} // namespace Chess
