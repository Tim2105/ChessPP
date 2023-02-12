#include "EvaluationDefinitions.h"

int16_t PIECE_VALUE[7] = {
        0, // Empty
        100, // Pawn
        400, // Knight
        400, // Bishop
        600, // Rook
        1200, // Queen
        0 // King
};

Bitboard neighboringFiles[8] = {
        0x101010101010101, // A
        0x505050505050505, // B
        0xA0A0A0A0A0A0A0A, // C
        0x1414141414141414, // D
        0x2828282828282828, // E
        0x5050505050505050, // F
        0xA0A0A0A0A0A0A0A0, // G
        0x4040404040404040 // H
};

Bitboard connectedPawnMasks[64] = {
        0x2,0x5,0xA,0x14,0x28,0x50,0xA0,0x40,
        0x200,0x500,0xA00,0x1400,0x2800,0x5000,0xA000,0x4000,
        0x20000,0x50000,0xA0000,0x140000,0x280000,0x500000,0xA00000,0x400000,
        0x2000000,0x5000000,0xA000000,0x14000000,0x28000000,0x50000000,0xA0000000,0x40000000,
        0x200000000,0x500000000,0xA00000000,0x1400000000,0x2800000000,0x5000000000,0xA000000000,0x4000000000,
        0x20000000000,0x50000000000,0xA0000000000,0x140000000000,0x280000000000,0x500000000000,0xA00000000000,0x400000000000,
        0x2000000000000,0x5000000000000,0xA000000000000,0x14000000000000,0x28000000000000,0x50000000000000,0xA0000000000000,0x40000000000000,
        0x200000000000000,0x500000000000000,0xA00000000000000,0x1400000000000000,0x2800000000000000,0x5000000000000000,0xA000000000000000,0x4000000000000000,
};

Bitboard pawnChainMasks[2][64] = {
        // White
        {
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                0x2,0x5,0xA,0x14,0x28,0x50,0xA0,0x40,
                0x200,0x500,0xA00,0x1400,0x2800,0x5000,0xA000,0x4000,
                0x20000,0x50000,0xA0000,0x140000,0x280000,0x500000,0xA00000,0x400000,
                0x2000000,0x5000000,0xA000000,0x14000000,0x28000000,0x50000000,0xA0000000,0x40000000,
                0x200000000,0x500000000,0xA00000000,0x1400000000,0x2800000000,0x5000000000,0xA000000000,0x4000000000,
                0x20000000000,0x50000000000,0xA0000000000,0x140000000000,0x280000000000,0x500000000000,0xA00000000000,0x400000000000,
                0x2000000000000,0x5000000000000,0xA000000000000,0x14000000000000,0x28000000000000,0x50000000000000,0xA0000000000000,0x40000000000000,
        },
        // Black
        {
                0x200,0x500,0xA00,0x1400,0x2800,0x5000,0xA000,0x4000,
                0x20000,0x50000,0xA0000,0x140000,0x280000,0x500000,0xA00000,0x400000,
                0x2000000,0x5000000,0xA000000,0x14000000,0x28000000,0x50000000,0xA0000000,0x40000000,
                0x200000000,0x500000000,0xA00000000,0x1400000000,0x2800000000,0x5000000000,0xA000000000,0x4000000000,
                0x20000000000,0x50000000000,0xA0000000000,0x140000000000,0x280000000000,0x500000000000,0xA00000000000,0x400000000000,
                0x2000000000000,0x5000000000000,0xA000000000000,0x14000000000000,0x28000000000000,0x50000000000000,0xA0000000000000,0x40000000000000,
                0x200000000000000,0x500000000000000,0xA00000000000000,0x1400000000000000,0x2800000000000000,0x5000000000000000,0xA000000000000000,0x4000000000000000,
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        }
};

Bitboard doubledPawnMasks[2][64] = {
        // White
        {
                0x101010101010100,0x202020202020200,0x404040404040400,0x808080808080800,0x1010101010101000,0x2020202020202000,0x4040404040404000,0x8080808080808000,
                0x101010101010000,0x202020202020000,0x404040404040000,0x808080808080000,0x1010101010100000,0x2020202020200000,0x4040404040400000,0x8080808080800000,
                0x101010101000000,0x202020202000000,0x404040404000000,0x808080808000000,0x1010101010000000,0x2020202020000000,0x4040404040000000,0x8080808080000000,
                0x101010100000000,0x202020200000000,0x404040400000000,0x808080800000000,0x1010101000000000,0x2020202000000000,0x4040404000000000,0x8080808000000000,
                0x101010000000000,0x202020000000000,0x404040000000000,0x808080000000000,0x1010100000000000,0x2020200000000000,0x4040400000000000,0x8080800000000000,
                0x101000000000000,0x202000000000000,0x404000000000000,0x808000000000000,0x1010000000000000,0x2020000000000000,0x4040000000000000,0x8080000000000000,
                0x100000000000000,0x200000000000000,0x400000000000000,0x800000000000000,0x1000000000000000,0x2000000000000000,0x4000000000000000,0x8000000000000000,
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        },
        // Black
        {
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,
                0x101,0x202,0x404,0x808,0x1010,0x2020,0x4040,0x8080,
                0x10101,0x20202,0x40404,0x80808,0x101010,0x202020,0x404040,0x808080,
                0x1010101,0x2020202,0x4040404,0x8080808,0x10101010,0x20202020,0x40404040,0x80808080,
                0x101010101,0x202020202,0x404040404,0x808080808,0x1010101010,0x2020202020,0x4040404040,0x8080808080,
                0x10101010101,0x20202020202,0x40404040404,0x80808080808,0x101010101010,0x202020202020,0x404040404040,0x808080808080,
                0x1010101010101,0x2020202020202,0x4040404040404,0x8080808080808,0x10101010101010,0x20202020202020,0x40404040404040,0x80808080808080,
        }
};

Bitboard sentryMasks[2][64] = {
        // White
        {
                0x303030303030300,0x707070707070700,0xE0E0E0E0E0E0E00,0x1C1C1C1C1C1C1C00,0x3838383838383800,0x7070707070707000,0xE0E0E0E0E0E0E000,0xC0C0C0C0C0C0C000,
                0x303030303030000,0x707070707070000,0xE0E0E0E0E0E0000,0x1C1C1C1C1C1C0000,0x3838383838380000,0x7070707070700000,0xE0E0E0E0E0E00000,0xC0C0C0C0C0C00000,
                0x303030303000000,0x707070707000000,0xE0E0E0E0E000000,0x1C1C1C1C1C000000,0x3838383838000000,0x7070707070000000,0xE0E0E0E0E0000000,0xC0C0C0C0C0000000,
                0x303030300000000,0x707070700000000,0xE0E0E0E00000000,0x1C1C1C1C00000000,0x3838383800000000,0x7070707000000000,0xE0E0E0E000000000,0xC0C0C0C000000000,
                0x303030000000000,0x707070000000000,0xE0E0E0000000000,0x1C1C1C0000000000,0x3838380000000000,0x7070700000000000,0xE0E0E00000000000,0xC0C0C00000000000,
                0x303000000000000,0x707000000000000,0xE0E000000000000,0x1C1C000000000000,0x3838000000000000,0x7070000000000000,0xE0E0000000000000,0xC0C0000000000000,
                0x300000000000000,0x700000000000000,0xE00000000000000,0x1C00000000000000,0x3800000000000000,0x7000000000000000,0xE000000000000000,0xC000000000000000,
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        },
        // Black
        {
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                0x3,0x7,0xE,0x1C,0x38,0x70,0xE0,0xC0,
                0x303,0x707,0xE0E,0x1C1C,0x3838,0x7070,0xE0E0,0xC0C0,
                0x30303,0x70707,0xE0E0E,0x1C1C1C,0x383838,0x707070,0xE0E0E0,0xC0C0C0,
                0x3030303,0x7070707,0xE0E0E0E,0x1C1C1C1C,0x38383838,0x70707070,0xE0E0E0E0,0xC0C0C0C0,
                0x303030303,0x707070707,0xE0E0E0E0E,0x1C1C1C1C1C,0x3838383838,0x7070707070,0xE0E0E0E0E0,0xC0C0C0C0C0,
                0x30303030303,0x70707070707,0xE0E0E0E0E0E,0x1C1C1C1C1C1C,0x383838383838,0x707070707070,0xE0E0E0E0E0E0,0xC0C0C0C0C0C0,
                0x3030303030303,0x7070707070707,0xE0E0E0E0E0E0E,0x1C1C1C1C1C1C1C,0x38383838383838,0x70707070707070,0xE0E0E0E0E0E0E0,0xC0C0C0C0C0C0C0,
        }
};

Bitboard kingAttackZoneMask[2][64] = {
        // White
        {
                0x3030302,0x7070705,0xE0E0E0A,0x1C1C1C14,0x38383828,0x70707050,0xE0E0E0A0,0xC0C0C040,
                0x303030200,0x707070500,0xE0E0E0A00,0x1C1C1C1400,0x3838382800,0x7070705000,0xE0E0E0A000,0xC0C0C04000,
                0x30303020000,0x70707050000,0xE0E0E0A0000,0x1C1C1C140000,0x383838280000,0x707070500000,0xE0E0E0A00000,0xC0C0C0400000,
                0x3030302000000,0x7070705000000,0xE0E0E0A000000,0x1C1C1C14000000,0x38383828000000,0x70707050000000,0xE0E0E0A0000000,0xC0C0C040000000,
                0x303030200000000,0x707070500000000,0xE0E0E0A00000000,0x1C1C1C1400000000,0x3838382800000000,0x7070705000000000,0xE0E0E0A000000000,0xC0C0C04000000000,
                0x303020000000003,0x707050000000007,0xE0E0A000000000E,0x1C1C14000000001C,0x3838280000000038,0x7070500000000070,0xE0E0A000000000E0,0xC0C04000000000C0,
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        },
        // Black
        {
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                0x300000000020303,0x700000000050707,0xE000000000A0E0E,0x1C00000000141C1C,0x3800000000283838,0x7000000000507070,0xE000000000A0E0E0,0xC00000000040C0C0,
                0x2030303,0x5070707,0xA0E0E0E,0x141C1C1C,0x28383838,0x50707070,0xA0E0E0E0,0x40C0C0C0,
                0x203030300,0x507070700,0xA0E0E0E00,0x141C1C1C00,0x2838383800,0x5070707000,0xA0E0E0E000,0x40C0C0C000,
                0x20303030000,0x50707070000,0xA0E0E0E0000,0x141C1C1C0000,0x283838380000,0x507070700000,0xA0E0E0E00000,0x40C0C0C00000,
                0x2030303000000,0x5070707000000,0xA0E0E0E000000,0x141C1C1C000000,0x28383838000000,0x50707070000000,0xA0E0E0E0000000,0x40C0C0C0000000,
                0x203030300000000,0x507070700000000,0xA0E0E0E00000000,0x141C1C1C00000000,0x2838383800000000,0x5070707000000000,0xA0E0E0E000000000,0x40C0C0C000000000,
        }
};

int32_t kingSafetyTable[100] = {
        0,  0,   1,   2,   3,   5,   7,   9,  12,  15,
        18,  22,  26,  30,  35,  39,  44,  50,  56,  62,
        68,  75,  82,  85,  89,  97, 105, 113, 122, 131,
        140, 150, 169, 180, 191, 202, 213, 225, 237, 248,
        260, 272, 283, 295, 307, 319, 330, 342, 354, 366,
        377, 389, 401, 412, 424, 436, 448, 459, 471, 483,
        494, 500, 500, 500, 500, 500, 500, 500, 500, 500,
        500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
        500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
        500, 500, 500, 500, 500, 500, 500, 500, 500, 500
};

Bitboard pawnShieldMask[2][64] = {
        // White
        {
                0x30300,0x70700,0xE0E00,0x1C1C00,0x383800,0x707000,0xE0E000,0xC0C000,
                0x3030000,0x7070000,0xE0E0000,0x1C1C0000,0x38380000,0x70700000,0xE0E00000,0xC0C00000,
                0x303000000,0x707000000,0xE0E000000,0x1C1C000000,0x3838000000,0x7070000000,0xE0E0000000,0xC0C0000000,
                0x30300000000,0x70700000000,0xE0E00000000,0x1C1C00000000,0x383800000000,0x707000000000,0xE0E000000000,0xC0C000000000,
                0x3030000000000,0x7070000000000,0xE0E0000000000,0x1C1C0000000000,0x38380000000000,0x70700000000000,0xE0E00000000000,0xC0C00000000000,
                0x303000000000000,0x707000000000000,0xE0E000000000000,0x1C1C000000000000,0x3838000000000000,0x7070000000000000,0xE0E0000000000000,0xC0C0000000000000,
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        },
        // Black
        {
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                0x303,0x707,0xE0E,0x1C1C,0x3838,0x7070,0xE0E0,0xC0C0,
                0x30300,0x70700,0xE0E00,0x1C1C00,0x383800,0x707000,0xE0E000,0xC0C000,
                0x3030000,0x7070000,0xE0E0000,0x1C1C0000,0x38380000,0x70700000,0xE0E00000,0xC0C00000,
                0x303000000,0x707000000,0xE0E000000,0x1C1C000000,0x3838000000,0x7070000000,0xE0E0000000,0xC0C0000000,
                0x30300000000,0x70700000000,0xE0E00000000,0x1C1C00000000,0x383800000000,0x707000000000,0xE0E000000000,0xC0C000000000,
                0x3030000000000,0x7070000000000,0xE0E0000000000,0x1C1C0000000000,0x38380000000000,0x70700000000000,0xE0E00000000000,0xC0C00000000000,
        }
};

Bitboard pawnStormMask[2][64] = {
        // White
        {
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
                0x3,0x7,0xE,0x1C,0x38,0x70,0xE0,0xC0,
                0x303,0x707,0xE0E,0x1C1C,0x3838,0x7070,0xE0E0,0xC0C0,
                0x30303,0x70707,0xE0E0E,0x1C1C1C,0x383838,0x707070,0xE0E0E0,0xC0C0C0,
                0x3030303,0x7070707,0xE0E0E0E,0x1C1C1C1C,0x38383838,0x70707070,0xE0E0E0E0,0xC0C0C0C0,
                0x303030303,0x707070707,0xE0E0E0E0E,0x1C1C1C1C1C,0x3838383838,0x7070707070,0xE0E0E0E0E0,0xC0C0C0C0C0,
                0x30303030303,0x70707070707,0xE0E0E0E0E0E,0x1C1C1C1C1C1C,0x383838383838,0x707070707070,0xE0E0E0E0E0E0,0xC0C0C0C0C0C0,
                0x3030303030303,0x7070707070707,0xE0E0E0E0E0E0E,0x1C1C1C1C1C1C1C,0x38383838383838,0x70707070707070,0xE0E0E0E0E0E0E0,0xC0C0C0C0C0C0C0,
        },
        // Black
        {
                0x303030303030300,0x707070707070700,0xE0E0E0E0E0E0E00,0x1C1C1C1C1C1C1C00,0x3838383838383800,0x7070707070707000,0xE0E0E0E0E0E0E000,0xC0C0C0C0C0C0C000,
                0x303030303030000,0x707070707070000,0xE0E0E0E0E0E0000,0x1C1C1C1C1C1C0000,0x3838383838380000,0x7070707070700000,0xE0E0E0E0E0E00000,0xC0C0C0C0C0C00000,
                0x303030303000000,0x707070707000000,0xE0E0E0E0E000000,0x1C1C1C1C1C000000,0x3838383838000000,0x7070707070000000,0xE0E0E0E0E0000000,0xC0C0C0C0C0000000,
                0x303030300000000,0x707070700000000,0xE0E0E0E00000000,0x1C1C1C1C00000000,0x3838383800000000,0x7070707000000000,0xE0E0E0E000000000,0xC0C0C0C000000000,
                0x303030000000000,0x707070000000000,0xE0E0E0000000000,0x1C1C1C0000000000,0x3838380000000000,0x7070700000000000,0xE0E0E00000000000,0xC0C0C00000000000,
                0x303000000000000,0x707000000000000,0xE0E000000000000,0x1C1C000000000000,0x3838000000000000,0x7070000000000000,0xE0E0000000000000,0xC0C0000000000000,
                0x300000000000000,0x700000000000000,0xE00000000000000,0x1C00000000000000,0x3800000000000000,0x7000000000000000,0xE000000000000000,0xC000000000000000,
                0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
        }
};

int16_t MG_PSQT[7][64] = {
        // Empty
        {},
        // Pawn
        {
                0, 0, 0, 0, 0, 0, 0, 0,
                8, 16, 16, -31, -31, 16, 16, 8,
                8, -8, -16, 0, 0, -16, -8, 8,
                0, 0, 0, 31, 31, 0, 0, 0,
                8, 8, 16, 31, 31, 16, 8, 8,
                16, 16, 31, 23, 23, 31, 16, 16,
                75, 75, 75, 75, 75, 75, 75, 75,
                0, 0, 0, 0, 0, 0, 0, 0
        },
        // Knight
        {
                -46, -31, -15, -15, -15, -15, -31, -46,
                -46, -15, 0, 8, 8, 0, -15, -46,
                -31, 8, 23, 31, 31, 23, 8, -31,
                -31, 0, 31, 38, 38, 31, 0, -31,
                -31, 8, 31, 38, 38, 31, 8, -31,
                -31, 0, 23, 31, 31, 23, 0, -31,
                -46, -15, 0, 0, 0, 0, -15, -46,
                -46, -31, -15, -15, -15, -15, -31, -46
        },
        // Bishop
        {
                -31, -15, -15, -15, -15, -15, -15, -31,
                -15, 8, 0, 0, 0, 0, 8, -15,
                -15, 23, 23, 23, 23, 23, 23, -15,
                -15, 0, 23, 23, 23, 23, 0, -15,
                -15, 8, 8, 23, 23, 8, 8, -15,
                -15, 0, 8, 23, 23, 8, 0, -15,
                -15, 0, 0, 0, 0, 0, 0, -15,
                -31, -15, -15, -15, -15, -15, -15, -31
        },
        // Rook
        {
                0, 0, 0, 8, 8, 0, 0, 0,
                8, 16, 16, 16, 16, 16, 16, 8,
                -8, 0, 0, 0, 0, 0, 0, -8,
                -8, 0, 0, 0, 0, 0, 0, -8,
                -8, 0, 0, 0, 0, 0, 0, -8,
                -8, 0, 0, 0, 0, 0, 0, -8,
                46, 46, 46, 46, 46, 46, 46, 46,
                0, 0, 0, 0, 0, 0, 0, 0
        },
        // Queen
        {
                -30, -15, -15, -7, -7, -15, -15, -30,
                -15, 0, 7, 3, 3, 7, 0, -15,
                -15, 7, 15, 10, 10, 15, 7, -15,
                -7, 3, 10, 15, 15, 10, 3, -7,
                0, 3, 10, 15, 15, 10, 3, -7,
                -15, 7, 10, 10, 10, 10, 7, -15,
                -15, 0, 0, 0, 0, 0, 0, -15,
                -30, -15, -15, -7, -7, -15, -15, -30
        },
        // King
        {
                30, 45, 5, 0, 0, 5, 45, 30,
                15, 30, 0, -15, -15, 0, 30, 15,
                -15, -30, -30, -30, -30, -30, -30, -15,
                -30, -45, -45, -60, -60, -45, -45, -30,
                -45, -60, -60, -75, -75, -60, -60, -45,
                -45, -60, -60, -75, -75, -60, -60, -45,
                -45, -60, -60, -75, -75, -60, -60, -45,
                -45, -60, -60, -75, -75, -60, -60, -45
        }
};

int16_t EG_PSQT[7][64] = {
        //Empty
        {},
        // Pawn
        {
                0, 0, 0, 0, 0, 0, 0, 0,
                -30, -30, -30, -30, -30, -30, -30, -30,
                -15, -15, -15, -15, -15, -15, -15, -15,
                0, 0, 0, 0, 0, 0, 0, 0,
                22, 22, 22, 22, 22, 22, 22, 22,
                52, 52, 52, 52, 52, 52, 52, 52,
                75, 75, 75, 75, 75, 75, 75, 75,
                0, 0, 0, 0, 0, 0, 0, 0
        },
        // Knight
        {
                -37, -30, -22, -22, -22, -22, -30, -37,
                -30, -15, 0, 3, 3, 0, -15, -30,
                -22, 3, 7, 10, 10, 7, 3, -22,
                -22, 0, 10, 15, 15, 10, 0, -22,
                -22, 3, 10, 15, 15, 10, 3, -22,
                -22, 0, 7, 10, 10, 7, 0, -22,
                -30, -15, 0, 3, 3, 0, -15, -30,
                -37, -30, -22, -22, -22, -22, -30, -37
        },
        // Bishop
        {
                -15, -7, -7, -7, -7, -7, -7, -15,
                -7, 3, 0, 0, 0, 0, 3, -7,
                -7, 7, 7, 7, 7, 7, 7, -7,
                -7, 0, 7, 7, 7, 7, 0, -7,
                -7, 3, 3, 7, 7, 3, 3, -7,
                -7, 0, 3, 7, 7, 3, 0, -7,
                -7, 0, 0, 0, 0, 0, 0, -7,
                -15, -7, -7, -7, -7, -7, -7, -15
        },
        // Rook
        {
                -15, -7, -3, 0, 0, -3, -7, -15,
                -7, -3, 0, 3, 3, 0, -3, -7,
                -3, 0, 3, 7, 7, 3, 0, -3,
                0, 3, 7, 15, 15, 7, 3, 0,
                0, 3, 7, 15, 15, 7, 3, 0,
                -3, 0, 3, 7, 7, 3, 0, -3,
                -7, -3, 0, 3, 3, 0, -3, -7,
                -15, -7, -3, 0, 0, -3, -7, -15
        },
        // Queen
        {
                -15, -7, -5, 0, 0, -5, -7, -15,
                -7, 0, 2, 5, 5, 2, 0, -7,
                -5, 2, 5, 7, 7, 5, 2, -5,
                0, 5, 7, 10, 10, 7, 5, 0,
                0, 5, 7, 10, 10, 7, 5, 0,
                -5, 2, 5, 7, 7, 5, 2, -5,
                -7, 0, 2, 5, 5, 2, 0, -7,
                -15, -7, -5, 0, 0, -5, -7, -15
        },
        // King
        {
                -75, -45, -45, -30, -30, -45, -45, -75,
                -45, -15, -15, 0, 0, -15, -15, -45,
                -45, -15, 20, 30, 30, 20, -15, -45,
                -30, 0, 30, 40, 40, 30, 0, -30,
                -30, 0, 30, 40, 40, 30, 0, -30,
                -45, -15, 20, 30, 30, 20, -15, -45,
                -45, -15, -15, 0, 0, -15, -15, -45,
                -75, -45, -45, -30, -30, -45, -45, -75
        }
};

Bitboard centerSquares = 0x0000001818000000;