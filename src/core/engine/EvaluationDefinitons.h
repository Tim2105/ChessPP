#ifndef EVALUATION_DEFINITIONS_H
#define EVALUATION_DEFINITIONS_H

#include "core/utils/Bitboard.h"
#include <stdint.h>
#include <functional>

struct Score {
    int32_t mg;
    int32_t eg;

    Score operator+(const Score& other) const {
        return Score{mg + other.mg, eg + other.eg};
    }

    Score operator-(const Score& other) const {
        return Score{mg - other.mg, eg - other.eg};
    }

    Score& operator+=(const Score& other) {
        mg += other.mg;
        eg += other.eg;
        return *this;
    }

    Score& operator-=(const Score& other) {
        mg -= other.mg;
        eg -= other.eg;
        return *this;
    }

    Score operator*(const int32_t& scalar) const {
        return Score{mg * scalar, eg * scalar};
    }

    Score& operator*=(const int32_t& scalar) {
        mg *= scalar;
        eg *= scalar;
        return *this;
    }

    Score operator/(const int32_t& scalar) const {
        return Score{mg / scalar, eg / scalar};
    }

    Score& operator/=(const int32_t& scalar) {
        mg /= scalar;
        eg /= scalar;
        return *this;
    }

    bool operator==(const Score& other) const {
        return mg == other.mg && eg == other.eg;
    }

    bool operator!=(const Score& other) const {
        return !(*this == other);
    }
};

struct PawnBitboards {
    Bitboard whitePawns;
    Bitboard blackPawns;

    bool operator==(const PawnBitboards& other) const {
        return whitePawns == other.whitePawns && blackPawns == other.blackPawns;
    }

    bool operator!=(const PawnBitboards& other) const {
        return !(*this == other);
    }
};

template <>
struct std::hash<PawnBitboards> {
    std::size_t operator()(const PawnBitboards& pwns) const {
        return std::hash<Bitboard>()(pwns.whitePawns) ^ std::hash<Bitboard>()(pwns.blackPawns);
    }
};

#endif // EVALUATION_DEFINITIONS_H