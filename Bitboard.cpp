#include "Bitboard.h"
#include "Definitions.h"

Bitboard::Bitboard() {
    bitboard = 0ULL;
}

Bitboard::Bitboard(uint64_t bitboard) {
    this->bitboard = bitboard;
}

Bitboard::Bitboard(const Bitboard& bitboard) {
    this->bitboard = bitboard.bitboard;
}

std::ostream& operator<<(std::ostream& os, const Bitboard& bitboard) {
    for(int r = RANK_8; r >= RANK_1; r--) {
        for(int f = FILE_A; f <= FILE_H; f++) {
            if(bitboard.getBit(r * 8 + f))
                os << "1";
            else
                os << "0";
        }
        os << std::endl;
    }

    return os;
}

uint64_t Bitboard::getBitboard() const {
    return bitboard;
}

void Bitboard::setBitboard(uint64_t bitboard) {
    this->bitboard = bitboard;
}

void Bitboard::setBit(int32_t index) {
    bitboard |= (1ULL << index);
}

void Bitboard::clearBit(int32_t index) {
    bitboard &= ~(1ULL << index);
}

bool Bitboard::getBit(int32_t index) const {
    return (bitboard & (1ULL << index)) != 0;
}

int32_t Bitboard::getFirstSetBit() const {
    return __builtin_ctzll(bitboard);
}

int32_t Bitboard::getLastSetBit() const {
    return 63 - __builtin_clzll(bitboard);
}

int32_t Bitboard::getNumberOfSetBits() const {
    return __builtin_popcountll(bitboard);
}

Bitboard::operator bool() const {
    return bitboard != 0ULL;
}

Bitboard::operator uint64_t() const {
    return bitboard;
}

Bitboard Bitboard::operator&(const Bitboard& bitboard) const {
    return Bitboard(this->bitboard & bitboard.bitboard);
}

Bitboard Bitboard::operator|(const Bitboard& bitboard) const {
    return Bitboard(this->bitboard | bitboard.bitboard);
}

Bitboard Bitboard::operator|=(const Bitboard& bitboard) {
    this->bitboard |= bitboard.bitboard;
    return *this;
}

Bitboard Bitboard::operator^(const Bitboard& bitboard) const {
    return Bitboard(this->bitboard ^ bitboard.bitboard);
}

Bitboard Bitboard::operator~() const {
    return Bitboard(~bitboard);
}

Bitboard Bitboard::operator<<(int32_t shift) const {
    return Bitboard(bitboard << shift);
}

Bitboard Bitboard::operator>>(int32_t shift) const {
    return Bitboard(bitboard >> shift);
}

bool Bitboard::operator==(const Bitboard& bitboard) const {
    return this->bitboard == bitboard.bitboard;
}

bool Bitboard::operator!=(const Bitboard& bitboard) const {
    return this->bitboard != bitboard.bitboard;
}

Bitboard Bitboard::operator=(const Bitboard& bitboard) {
    this->bitboard = bitboard.bitboard;
    return *this;
}

Bitboard diagonalAttackBitboard(int32_t sq, const Bitboard& occupied) {
    Bitboard attackBitboard;

    // Diagonale nach oben rechts
    for(int32_t i = sq + 9; i < 64 && i % 8 != 0; i += 9) {
        attackBitboard.setBit(i);

        if(occupied.getBit(i))
            break;
    }

    // Diagonale nach unten links
    for(int32_t i = sq - 9; i >= 0 && i % 8 != 7; i -= 9) {
        attackBitboard.setBit(i);

        if(occupied.getBit(i))
            break;
    }

    // Diagonale nach unten rechts
    for(int32_t i = sq + 7; i < 64 && i % 8 != 7; i += 7) {
        attackBitboard.setBit(i);

        if(occupied.getBit(i))
            break;
    }

    // Diagonale nach oben links
    for(int32_t i = sq - 7; i >= 0 && i % 8 != 0; i -= 7) {
        attackBitboard.setBit(i);

        if(occupied.getBit(i))
            break;
    }

    return attackBitboard;
}

Bitboard straightAttackBitboard(int32_t sq, const Bitboard& occupied) {
    Bitboard attackBitboard;

    // Vertikal nach oben
    for(int32_t i = sq + 8; i < 64; i += 8) {
        attackBitboard.setBit(i);

        if(occupied.getBit(i))
            break;
    }

    // Vertikal nach unten
    for(int32_t i = sq - 8; i >= 0; i -= 8) {
        attackBitboard.setBit(i);

        if(occupied.getBit(i))
            break;
    }

    // Horizontal nach rechts
    for(int32_t i = sq + 1; i < 64 && i % 8 != 0; i += 1) {
        attackBitboard.setBit(i);

        if(occupied.getBit(i))
            break;
    }

    // Horizontal nach links
    for(int32_t i = sq - 1; i >= 0 && i % 8 != 7; i -= 1) {
        attackBitboard.setBit(i);

        if(occupied.getBit(i))
            break;
    }

    return attackBitboard;
}

Bitboard knightAttackBitboard(int32_t sq) {
    int32_t knightMoves[8] = { -17, -15, -10, -6, 6, 10, 15, 17 };
    Bitboard attackBitboard;

    for(int32_t i = 0; i < 8; i++) {
        int32_t target = sq + knightMoves[i];

        if(target >= 0 && target < 64 && abs((target % 8) - (sq % 8)) <= 2)
            attackBitboard.setBit(target);
    }
    return attackBitboard;
}

Bitboard pawnAttackBitboard(int32_t sq, int32_t side) {
    int32_t sideAsSign = side == WHITE ? 1 : -1;

    int32_t pawnMoves[2] = { 7, 9 };
    Bitboard attackBitboard;

    for(int32_t i = 0; i < 2; i++) {
        int32_t target = sq + pawnMoves[i] * sideAsSign;

        if(target >= 0 && target < 64 && abs((target % 8) - (sq % 8)) == 1)
            attackBitboard.setBit(target);
    }
    return attackBitboard;
}

Bitboard kingAttackBitboard(int32_t sq) {
    int32_t kingMoves[8] = { -9, -8, -7, -1, 1, 7, 8, 9 };
    Bitboard attackBitboard;

    for(int32_t i = 0; i < 8; i++) {
        int32_t target = sq + kingMoves[i];

        if(target >= 0 && target < 64 && abs((target % 8) - (sq % 8)) <= 1)
            attackBitboard.setBit(target);
    }
    return attackBitboard;
}