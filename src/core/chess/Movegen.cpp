#include "core/chess/Movegen.h"
#include "core/chess/MailboxDefinitions.h"

void Movegen::generatePseudoLegalWhitePawnMoves(Array<Move, 256>& moves, Board& b) {
    for(int& sq : b.pieceList[WHITE_PAWN]) {
        int32_t file = SQ2F(sq);
        int32_t rank = SQ2R(sq);

        int32_t destForw = FR2SQ(file, rank + 1);

        if(b.pieces[destForw] == EMPTY) {
            if(rank == RANK_7) {
                moves.push_back(Move(sq, destForw, MOVE_PROMOTION_KNIGHT));
                moves.push_back(Move(sq, destForw, MOVE_PROMOTION_BISHOP));
                moves.push_back(Move(sq, destForw, MOVE_PROMOTION_ROOK));
                moves.push_back(Move(sq, destForw, MOVE_PROMOTION_QUEEN));
            }
            else
                moves.push_back(Move(sq, destForw, MOVE_QUIET));
        }

        if(rank == RANK_2) {
            int32_t destForw2 = FR2SQ(file, rank + 2);
            if(b.pieces[destForw] == EMPTY && b.pieces[destForw2] == EMPTY)
                moves.push_back(Move(sq, destForw2, MOVE_DOUBLE_PAWN));
        }

        int32_t destLeft = FR2SQ(file - 1, rank + 1);
        if(Mailbox::mailbox[destLeft] != NO_SQ && b.pieces[destLeft] != EMPTY && (b.pieces[destLeft] & COLOR_MASK) == BLACK) {
            if(rank == RANK_7) {
                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
            }
            else
                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
        }

        int32_t destRight = FR2SQ(file + 1, rank + 1);
        if(Mailbox::mailbox[destRight] != NO_SQ && b.pieces[destRight] != EMPTY && (b.pieces[destRight] & COLOR_MASK) == BLACK) {
            if(rank == RANK_7) {
                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
            }
            else
                moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
        }

        if(b.enPassantSquare != NO_SQ) {
            if(b.enPassantSquare == destLeft)
                moves.push_back(Move(sq, destLeft, MOVE_EN_PASSANT));
            else if(b.enPassantSquare == destRight)
                moves.push_back(Move(sq, destRight, MOVE_EN_PASSANT));
        }
    }
}

void Movegen::generatePseudoLegalBlackPawnMoves(Array<Move, 256>& moves, Board& b) {
    for(int& sq : b.pieceList[BLACK_PAWN]) {
        int32_t file = SQ2F(sq);
        int32_t rank = SQ2R(sq);

        int32_t destForw = FR2SQ(file, rank - 1);

        if(b.pieces[destForw] == EMPTY) {
            if(rank == RANK_2) {
                moves.push_back(Move(sq, destForw, MOVE_PROMOTION_KNIGHT));
                moves.push_back(Move(sq, destForw, MOVE_PROMOTION_BISHOP));
                moves.push_back(Move(sq, destForw, MOVE_PROMOTION_ROOK));
                moves.push_back(Move(sq, destForw, MOVE_PROMOTION_QUEEN));
            }
            else
                moves.push_back(Move(sq, destForw, MOVE_QUIET));
        }

        if(rank == RANK_7) {
            int32_t destForw2 = FR2SQ(file, rank - 2);
            if(b.pieces[destForw] == EMPTY && b.pieces[destForw2] == EMPTY)
                moves.push_back(Move(sq, destForw2, MOVE_DOUBLE_PAWN));
        }

        int32_t destLeft = FR2SQ(file - 1, rank - 1);
        if(Mailbox::mailbox[destLeft] != NO_SQ && b.pieces[destLeft] != EMPTY && (b.pieces[destLeft] & COLOR_MASK) == WHITE) {
            if(rank == RANK_2) {
                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
            }
            else
                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
        }

        int32_t destRight = FR2SQ(file + 1, rank - 1);
        if(Mailbox::mailbox[destRight] != NO_SQ && b.pieces[destRight] != EMPTY && (b.pieces[destRight] & COLOR_MASK) == WHITE) {
            if(rank == RANK_2) {
                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
            }
            else
                moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
        }

        if(b.enPassantSquare != NO_SQ) {
            if(b.enPassantSquare == destLeft)
                moves.push_back(Move(sq, destLeft, MOVE_EN_PASSANT));
            else if(b.enPassantSquare == destRight)
                moves.push_back(Move(sq, destRight, MOVE_EN_PASSANT));
        }
    }
}

void Movegen::generatePseudoLegalWhiteKnightMoves(Array<Move, 256>& moves, Board& b) {
    for(int& sq : b.pieceList[WHITE_KNIGHT]) {
        for(int i = 0; i < 8; i++) {
            int n_sq = sq + KNIGHT_ATTACKS[i];
            if(Mailbox::mailbox[n_sq] != NO_SQ) {
                if(b.pieces[n_sq] == EMPTY)
                    moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                else if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                    moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
            }
        }
    }
}

void Movegen:: generatePseudoLegalBlackKnightMoves(Array<Move, 256>& moves, Board& b) {
    for(int& sq : b.pieceList[BLACK_KNIGHT]) {
        for(int i = 0; i < 8; i++) {
            int n_sq = sq + KNIGHT_ATTACKS[i];
            if(Mailbox::mailbox[n_sq] != NO_SQ) {
                if(b.pieces[n_sq] == EMPTY)
                    moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                else if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                    moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
            }
        }
    }
}

void Movegen::generatePseudoLegalWhiteRookMoves(Array<Move, 256>& moves, Board& b) {
    for(int& sq : b.pieceList[WHITE_BISHOP]) {
        for(int i = 0; i < 4; i++) {
            int n_sq = sq + DIAGONAL_ATTACKS[i];
            while(Mailbox::mailbox[n_sq] != NO_SQ) {
                if(b.pieces[n_sq] == EMPTY)
                    moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                    moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                    break;
                }
                else
                    break;

                n_sq += DIAGONAL_ATTACKS[i];
            }
        }
    }
}

void Movegen::generatePseudoLegalBlackRookMoves(Array<Move, 256>& moves, Board& b) {
    for(int& sq : b.pieceList[BLACK_BISHOP]) {
        for(int i = 0; i < 4; i++) {
            int n_sq = sq + DIAGONAL_ATTACKS[i];
            while(Mailbox::mailbox[n_sq] != NO_SQ) {
                if(b.pieces[n_sq] == EMPTY)
                    moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                    moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                    break;
                }
                else
                    break;

                n_sq += DIAGONAL_ATTACKS[i];
            }
        }
    }
}

void Movegen::generatePseudoLegalWhiteBishopMoves(Array<Move, 256>& moves, Board& b) {
    for(int& sq : b.pieceList[WHITE_ROOK]) {
        for(int i = 0; i < 4; i++) {
            int n_sq = sq + STRAIGHT_ATTACKS[i];
            while(Mailbox::mailbox[n_sq] != NO_SQ) {
                if(b.pieces[n_sq] == EMPTY)
                    moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                    moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                    break;
                }
                else
                    break;

                n_sq += STRAIGHT_ATTACKS[i];
            }
        }
    }
}

void Movegen::generatePseudoLegalBlackBishopMoves(Array<Move, 256>& moves, Board& b) {
    for(int& sq : b.pieceList[BLACK_ROOK]) {
        for(int i = 0; i < 4; i++) {
            int n_sq = sq + STRAIGHT_ATTACKS[i];
            while(Mailbox::mailbox[n_sq] != NO_SQ) {
                if(b.pieces[n_sq] == EMPTY)
                    moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                    moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                    break;
                }
                else
                    break;

                n_sq += STRAIGHT_ATTACKS[i];
            }
        }
    }
}

void Movegen::generatePseudoLegalWhiteQueenMoves(Array<Move, 256>& moves, Board& b) {
    int32_t QUEEN_ATTACKS[8] = {
        DIAGONAL_ATTACKS[0], DIAGONAL_ATTACKS[1], DIAGONAL_ATTACKS[2], DIAGONAL_ATTACKS[3],
        STRAIGHT_ATTACKS[0], STRAIGHT_ATTACKS[1], STRAIGHT_ATTACKS[2], STRAIGHT_ATTACKS[3]
    };

    for(int& sq : b.pieceList[WHITE_QUEEN]) {
        for(int i = 0; i < 8; i++) {
            int n_sq = sq + QUEEN_ATTACKS[i];
            while(Mailbox::mailbox[n_sq] != NO_SQ) {
                if(b.pieces[n_sq] == EMPTY)
                    moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                    moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                    break;
                }
                else
                    break;

                n_sq += QUEEN_ATTACKS[i];
            }
        }
    }
}

void Movegen::generatePseudoLegalBlackQueenMoves(Array<Move, 256>& moves, Board& b) {
    int32_t QUEEN_ATTACKS[8] = {
        DIAGONAL_ATTACKS[0], DIAGONAL_ATTACKS[1], DIAGONAL_ATTACKS[2], DIAGONAL_ATTACKS[3],
        STRAIGHT_ATTACKS[0], STRAIGHT_ATTACKS[1], STRAIGHT_ATTACKS[2], STRAIGHT_ATTACKS[3]
    };

    for(int& sq : b.pieceList[BLACK_QUEEN]) {
        for(int i = 0; i < 8; i++) {
            int n_sq = sq + QUEEN_ATTACKS[i];
            while(Mailbox::mailbox[n_sq] != NO_SQ) {
                if(b.pieces[n_sq] == EMPTY)
                    moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                    moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                    break;
                }
                else
                    break;

                n_sq += QUEEN_ATTACKS[i];
            }
        }
    }
}

void Movegen::generatePseudoLegalWhiteKingMoves(Array<Move, 256>& moves, Board& b) {
    int32_t KING_ATTACKS[8] = {
        DIAGONAL_ATTACKS[0], DIAGONAL_ATTACKS[1], DIAGONAL_ATTACKS[2], DIAGONAL_ATTACKS[3],
        STRAIGHT_ATTACKS[0], STRAIGHT_ATTACKS[1], STRAIGHT_ATTACKS[2], STRAIGHT_ATTACKS[3]
    };

    int sq = b.pieceList[WHITE_KING].front();
    for(int i = 0; i < 8; i++) {
        int n_sq = sq + KING_ATTACKS[i];
        if(Mailbox::mailbox[n_sq] != NO_SQ) {
            if(b.pieces[n_sq] == EMPTY)
                moves.push_back(Move(sq, n_sq, MOVE_QUIET));
            else if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
        }
    }

    if(b.castlingPermission & WHITE_KINGSIDE_CASTLE) {
        if(b.pieces[F1] == EMPTY && b.pieces[G1] == EMPTY) {
            moves.push_back(Move(E1, G1, MOVE_KINGSIDE_CASTLE));
        }
    }

    if(b.castlingPermission & WHITE_QUEENSIDE_CASTLE) {
        if(b.pieces[D1] == EMPTY && b.pieces[C1] == EMPTY && b.pieces[B1] == EMPTY) {
            moves.push_back(Move(E1, C1, MOVE_QUEENSIDE_CASTLE));
        }
    }
}

void Movegen::generatePseudoLegalBlackKingMoves(Array<Move, 256>& moves, Board& b) {
    int32_t KING_ATTACKS[8] = {
        DIAGONAL_ATTACKS[0], DIAGONAL_ATTACKS[1], DIAGONAL_ATTACKS[2], DIAGONAL_ATTACKS[3],
        STRAIGHT_ATTACKS[0], STRAIGHT_ATTACKS[1], STRAIGHT_ATTACKS[2], STRAIGHT_ATTACKS[3]
    };

    int sq = b.pieceList[BLACK_KING].front();
    for(int i = 0; i < 8; i++) {
        int n_sq = sq + KING_ATTACKS[i];
        if(Mailbox::mailbox[n_sq] != NO_SQ) {
            if(b.pieces[n_sq] == EMPTY)
                moves.push_back(Move(sq, n_sq, MOVE_QUIET));
            else if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
        }
    }

    if(b.castlingPermission & BLACK_KINGSIDE_CASTLE) {
        if(b.pieces[F8] == EMPTY && b.pieces[G8] == EMPTY) {
            moves.push_back(Move(E8, G8, MOVE_KINGSIDE_CASTLE));
        }
    }

    if(b.castlingPermission & BLACK_QUEENSIDE_CASTLE) {
        if(b.pieces[D8] == EMPTY && b.pieces[C8] == EMPTY && b.pieces[B8] == EMPTY) {
            moves.push_back(Move(E8, C8, MOVE_QUEENSIDE_CASTLE));
        }
    }
}

void Movegen::generateWhitePawnMoves(Array<Move, 256>& moves, Board& b,
                                     int32_t numAttackers, Bitboard attackingRays,
                                     Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Bauernzug kann legal sein
    if(numAttackers > 1)
        return;

    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Bauer den Angreifer schlagen oder den K??nig sch??tzen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[WHITE_PAWN]) {
            int32_t rank = SQ2R(sq);

            int32_t destForw = sq + NORTH;
            int32_t destForw2 = sq + 2 * NORTH;
            int32_t destLeft = sq + NORTH_WEST;
            int32_t destRight = sq + NORTH_EAST;

            bool pinned = pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]);

            // Wenn der Bauer gefesselt ist, kann er sich nicht bewegen
            if(pinned)
                continue;

            // En-Passant Z??ge befreien den K??nig nur aus dem Schach, wenn der geschlagene Bauer der Angreifer ist
            if(b.enPassantSquare != NO_SQ) {
                int32_t captureSquare = b.enPassantSquare + SOUTH;

                if(b.enPassantSquare == destLeft) {
                    if(attackingRays.getBit(Mailbox::mailbox[captureSquare]))
                        moves.push_back(Move(sq, destLeft, MOVE_EN_PASSANT));
                } else if(b.enPassantSquare == destRight) {
                    if(attackingRays.getBit(Mailbox::mailbox[captureSquare]))
                        moves.push_back(Move(sq, destRight, MOVE_EN_PASSANT));
                }
            }
            
            // Wenn der Bauer den Angreifer blockiert, ist der Zug legal
            // Ein blockierende Zug kann kein normaler Schlagzug sein, weil der Bauer sonst nicht gefesselt w??re
            if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[destForw]) && b.pieces[destForw] == EMPTY) {
                // Promotion
                if(rank == RANK_7) {
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destForw, MOVE_QUIET));
            } else if(rank == RANK_2 && attackingRays & Bitboard(1ULL << Mailbox::mailbox[destForw2]) && b.pieces[destForw2] == EMPTY && b.pieces[destForw] == EMPTY)
                moves.push_back(Move(sq, destForw2, MOVE_DOUBLE_PAWN));
            
            // Wenn der Bauer den Angreifer schlagen kann, ist der Zug legal
            if(b.pieces[destLeft] != EMPTY && attackingRays & Bitboard(1ULL << Mailbox::mailbox[destLeft]) && (b.pieces[destLeft] & COLOR_MASK) == BLACK) {
                // Promotion
                if(rank == RANK_7) {
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
            } else if(b.pieces[destRight] != EMPTY && attackingRays & Bitboard(1ULL << Mailbox::mailbox[destRight]) && (b.pieces[destRight] & COLOR_MASK) == BLACK) {
                // Promotion
                if(rank == RANK_7) {
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
            }
        }
    } else {
        for(int& sq : b.pieceList[WHITE_PAWN]) {
            int32_t rank = SQ2R(sq);

            int32_t destForw = sq + NORTH;
            int32_t destForw2 = sq + 2 * NORTH;
            int32_t destLeft = sq + NORTH_WEST;
            int32_t destRight = sq + NORTH_EAST;

            bool pinned = pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]);

            // En-Passant Z??ge entfernen 2 Figuren aus einer Reihe, daher muss immer ??berpr??ft werden, ob der K??nig nach dem Zug im Schach st??nde
            // -> Ein En-Passant Zug mit einem ungefesselten Bauer kann illegal sein
            if(b.enPassantSquare != NO_SQ) {
                int32_t captureSquare = b.enPassantSquare + SOUTH;
                int32_t kingSquare = b.pieceList[WHITE_KING].front();

                if(b.enPassantSquare == destLeft) {
                    Bitboard allPiecesAfterMove = b.allPiecesBitboard | b.pieceBitboard[BLACK_KING];
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[sq]);
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[captureSquare]);
                    allPiecesAfterMove.setBit(Mailbox::mailbox[destLeft]);

                    if(!b.squareAttacked(kingSquare, BLACK, allPiecesAfterMove))
                        moves.push_back(Move(sq, destLeft, MOVE_EN_PASSANT));

                } else if(b.enPassantSquare == destRight) {
                    Bitboard allPiecesAfterMove = b.allPiecesBitboard | b.pieceBitboard[BLACK_KING];
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[sq]);
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[captureSquare]);
                    allPiecesAfterMove.setBit(Mailbox::mailbox[destRight]);

                    if(!b.squareAttacked(kingSquare, BLACK, allPiecesAfterMove))
                        moves.push_back(Move(sq, destRight, MOVE_EN_PASSANT));
                }
            }

            // ??berpr??fe, ob der Bauer horizontal oder diagonal gefesselt ist
            // Wenn ja, kann er sich nur bewegen, wenn er den Angreifer schl??gt(diagonal)
            if(pinned) {
                int32_t pinDir = pinDirections[Mailbox::mailbox[sq]];
                if(pinDir == SOUTH_EAST || pinDir == NORTH_WEST) {
                    if(b.pieces[destLeft] != EMPTY && (b.pieces[destLeft] & COLOR_MASK) == BLACK) {
                        // Promotion
                        if(rank == RANK_7) {
                                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                        } else
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
                    }
                } else if(pinDir == SOUTH_WEST || pinDir == NORTH_EAST) {
                    if(b.pieces[destRight] != EMPTY && (b.pieces[destRight] & COLOR_MASK) == BLACK) {
                        // Promotion
                        if(rank == RANK_7) {
                                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                        } else
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
                    }
                }
                
                if(!(pinDir == NORTH || pinDir == SOUTH))
                    continue;
            }
            
            // Wenn der Bauer nicht horizontal oder diagonal gefesselt ist, kann er sich nach vorne bewegen
            if(b.pieces[destForw] == EMPTY) {
                // Promotion
                if(rank == RANK_7) {
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destForw, MOVE_QUIET));
            }

            if(rank == RANK_2 && b.pieces[destForw2] == EMPTY && b.pieces[destForw] == EMPTY)
                moves.push_back(Move(sq, destForw2, MOVE_DOUBLE_PAWN));
            
            // Schlagz??ge
            // sind nur m??glich, wenn der Bauer nicht gefesselt ist
            int32_t nwPiece = b.pieces[destLeft];

            if(nwPiece != EMPTY && (nwPiece & COLOR_MASK) == BLACK && !pinned) {
                // Promotion
                if(rank == RANK_7) {
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
            }

            int32_t nePiece = b.pieces[destRight];

            if(nePiece != EMPTY && (nePiece & COLOR_MASK) == BLACK && !pinned) {
                // Promotion
                if(rank == RANK_7) {
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
            }
        }
    }
}

void Movegen::generateBlackPawnMoves(Array<Move, 256>& moves, Board& b,
                                     int32_t numAttackers, Bitboard attackingRays,
                                     Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Bauerzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Bauer den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[BLACK_PAWN]) {
            int32_t rank = SQ2R(sq);

            int32_t destForw = sq + SOUTH;
            int32_t destForw2 = sq + 2 * SOUTH;
            int32_t destLeft = sq + SOUTH_WEST;
            int32_t destRight = sq + SOUTH_EAST;

            bool pinned = pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]);

            // Wenn der Bauer gefesselt ist, kann er sich nicht bewegen
            if(pinned)
                continue;
            
            // En-Passant Z??ge befreien den K??nig nur aus dem Schach, wenn der geschlagene Bauer der Angreifer ist
            if(b.enPassantSquare != NO_SQ) {
                int32_t captureSquare = b.enPassantSquare + NORTH;

                if(b.enPassantSquare == destLeft) {
                    if(attackingRays.getBit(Mailbox::mailbox[captureSquare]))
                        moves.push_back(Move(sq, destLeft, MOVE_EN_PASSANT));
                } else if(b.enPassantSquare == destRight) {
                    if(attackingRays.getBit(Mailbox::mailbox[captureSquare]))
                        moves.push_back(Move(sq, destRight, MOVE_EN_PASSANT));
                }
            }
            
            // Wenn der Bauer den Angreifer blockiert, ist der Zug legal
            // Ein blockierende Zug kann kein normaler Schlagzug sein, weil der Bauer sonst nicht gefesselt w??re
            if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[destForw]) && b.pieces[destForw] == EMPTY) {
                // Promotion
                if(rank == RANK_2) {
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destForw, MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destForw, MOVE_QUIET));
            } else if(rank == RANK_7 && attackingRays & Bitboard(1ULL << Mailbox::mailbox[destForw2]) && b.pieces[destForw2] == EMPTY && b.pieces[destForw] == EMPTY)
                moves.push_back(Move(sq, destForw2, MOVE_DOUBLE_PAWN));
            
            // Wenn der Bauer den Angreifer schlagen kann, ist der Zug legal
            if(b.pieces[destLeft] != EMPTY && attackingRays & Bitboard(1ULL << Mailbox::mailbox[destLeft]) && (b.pieces[destLeft] & COLOR_MASK) == WHITE) {
                // Promotion
                if(rank == RANK_2) {
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
            } else if(b.pieces[destRight] != EMPTY && attackingRays & Bitboard(1ULL << Mailbox::mailbox[destRight]) && (b.pieces[destRight] & COLOR_MASK) == WHITE) {
                // Promotion
                if(rank == RANK_2) {
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
            }
        }
    } else {
        for(int& sq : b.pieceList[BLACK_PAWN]) {
            int32_t rank = SQ2R(sq);

            int32_t destForw = sq + SOUTH;
            int32_t destForw2 = sq + 2 * SOUTH;
            int32_t destLeft = sq + SOUTH_WEST;
            int32_t destRight = sq + SOUTH_EAST;

            bool pinned = pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]);

            // En-Passant Z??ge entfernen 2 Figuren aus einer Reihe, daher muss immer ??berpr??ft werden, ob der K??nig nach dem Zug im Schach st??nde
            // -> Ein En-Passant Zug mit einem ungefesselten Bauer kann illegal sein
            if(b.enPassantSquare != NO_SQ) {
                int32_t captureSquare = b.enPassantSquare + NORTH;
                int32_t kingSquare = b.pieceList[BLACK_KING].front();

                if(b.enPassantSquare == destLeft) {
                    Bitboard allPiecesAfterMove = b.allPiecesBitboard | b.pieceBitboard[WHITE_KING];
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[sq]);
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[captureSquare]);
                    allPiecesAfterMove.setBit(Mailbox::mailbox[destLeft]);

                    if(!b.squareAttacked(kingSquare, WHITE, allPiecesAfterMove))
                        moves.push_back(Move(sq, destLeft, MOVE_EN_PASSANT));

                } else if(b.enPassantSquare == destRight) {
                    Bitboard allPiecesAfterMove = b.allPiecesBitboard | b.pieceBitboard[WHITE_KING];
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[sq]);
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[captureSquare]);
                    allPiecesAfterMove.setBit(Mailbox::mailbox[destRight]);

                    if(!b.squareAttacked(kingSquare, WHITE, allPiecesAfterMove))
                        moves.push_back(Move(sq, destRight, MOVE_EN_PASSANT));
                }
            }

            // ??berpr??fe, ob der Bauer horizontal oder diagonal gefesselt ist
            // Wenn ja, kann er sich nur bewegen, wenn er den Angreifer schl??gt(diagonal)
            if(pinned) {
                int32_t pinDir = pinDirections[Mailbox::mailbox[sq]];
                
                if(pinDir == NORTH_EAST || pinDir == SOUTH_WEST) {
                    if(b.pieces[destLeft] != EMPTY && (b.pieces[destLeft] & COLOR_MASK) == WHITE) {
                        // Promotion
                        if(rank == RANK_2) {
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                        } else
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
                    }
                } else if(pinDir == NORTH_WEST || pinDir == SOUTH_EAST) {
                    if(b.pieces[destRight] != EMPTY && (b.pieces[destRight] & COLOR_MASK) == WHITE) {
                        // Promotion
                        if(rank == RANK_2) {
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                        } else
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
                    }
                }
                
                if(!(pinDir == NORTH || pinDir == SOUTH))
                    continue;
            }

            // Wenn der Bauer nicht horizontal oder diagonal gefesselt ist, kann er sich nach vorne bewegen
            if(b.pieces[destForw] == EMPTY) {
                // Promotion
                if(rank == RANK_2) {
                    moves.push_back(Move(sq, destForw, MOVE_PROMOTION_QUEEN));
                    moves.push_back(Move(sq, destForw, MOVE_PROMOTION_ROOK));
                    moves.push_back(Move(sq, destForw, MOVE_PROMOTION_BISHOP));
                    moves.push_back(Move(sq, destForw, MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destForw, MOVE_QUIET));
            }

            if(rank == RANK_7 && b.pieces[destForw2] == EMPTY && b.pieces[destForw] == EMPTY)
                moves.push_back(Move(sq, destForw2, MOVE_DOUBLE_PAWN));
            
            // Schlagz??ge
            // sind nur m??glich, wenn der Bauer nicht gefesselt ist
            int32_t swPiece = b.pieces[destLeft];

            if(swPiece != EMPTY && (swPiece & COLOR_MASK) == WHITE && !pinned) {
                // Promotion
                if(rank == RANK_2) {
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
            }

            int32_t sePiece = b.pieces[destRight];

            if(sePiece != EMPTY && (sePiece & COLOR_MASK) == WHITE && !pinned) {
                // Promotion
                if(rank == RANK_2) {
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
            }
        }
    }
}

void Movegen::generateWhiteKnightMoves(Array<Move, 256>& moves, Board& b,
                                       int32_t numAttackers, Bitboard attackingRays,
                                       Bitboard pinnedPieces) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Springerzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Springer den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[WHITE_KNIGHT]) {
            // Wenn der Springer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPieces & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 8; i++) {
                int n_sq = sq + KNIGHT_ATTACKS[i];

                if(Mailbox::mailbox[n_sq] == NO_SQ)
                    continue;
                
                // Wenn der Springer den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                    if(b.pieces[n_sq] == EMPTY)
                        moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                    else
                        moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[WHITE_KNIGHT]) {
            // Wenn der Springer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPieces & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            // Ansonsten darf er sich frei bewegen
            for(int i = 0; i < 8; i++) {
                int n_sq = sq + KNIGHT_ATTACKS[i];
                if(Mailbox::mailbox[n_sq] != NO_SQ) {
                    if(b.pieces[n_sq] == EMPTY)
                        moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                    else if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                        moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                }
            }
        }
    }
}

void Movegen::generateBlackKnightMoves(Array<Move, 256>& moves, Board& b,
                                       int32_t numAttackers, Bitboard attackingRays,
                                       Bitboard pinnedPieces) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Springerzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Springer den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[BLACK_KNIGHT]) {
            // Wenn der Springer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPieces & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 8; i++) {
                int n_sq = sq + KNIGHT_ATTACKS[i];

                if(Mailbox::mailbox[n_sq] == NO_SQ)
                    continue;
                
                // Wenn der Springer den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                    if(b.pieces[n_sq] == EMPTY)
                        moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                    else
                        moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[BLACK_KNIGHT]) {
            // Wenn der Springer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPieces & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            // Ansonsten darf er sich frei bewegen
            for(int i = 0; i < 8; i++) {
                int n_sq = sq + KNIGHT_ATTACKS[i];
                if(Mailbox::mailbox[n_sq] != NO_SQ) {
                    if(b.pieces[n_sq] == EMPTY)
                        moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                    else if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                        moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                }
            }
        }
    }
}

void Movegen::generateWhiteBishopMoves(Array<Move, 256>& moves, Board& b,
                                       int32_t numAttackers, Bitboard attackingRays,
                                       Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein L??uferzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der L??ufer den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[WHITE_BISHOP]) {
            // Wenn der L??ufer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + DIAGONAL_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn der L??ufer den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                    } else if(b.pieces[n_sq] != EMPTY)
                        break;
                        
                    n_sq += DIAGONAL_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[WHITE_BISHOP]) {
            // Wenn der L??ufer gefesselt ist, muss er sich in oder gegen die Richtung bewegen, in die er gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                // Diagonale von links unten nach rechts oben
                if(pinDirection == NORTH_EAST || pinDirection == SOUTH_WEST) {
                    int n_sq = sq + NORTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH_EAST;
                    }
                    n_sq = sq + SOUTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH_WEST;
                    }
                } else if(pinDirection == NORTH_WEST || pinDirection == SOUTH_EAST) {
                    // Diagonale von rechts unten nach links oben
                    int n_sq = sq + NORTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH_WEST;
                    }
                    n_sq = sq + SOUTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH_EAST;
                    }
                }
            } else {
                // Ansonsten darf er sich frei bewegen
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + DIAGONAL_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;

                        n_sq += DIAGONAL_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateBlackBishopMoves(Array<Move, 256>& moves, Board& b,
                                       int32_t numAttackers, Bitboard attackingRays,
                                       Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein L??uferzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der L??ufer den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[BLACK_BISHOP]) {
            // Wenn der L??ufer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + DIAGONAL_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn der L??ufer den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                    } else if(b.pieces[n_sq] != EMPTY)
                        break;
                        
                    n_sq += DIAGONAL_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[BLACK_BISHOP]) {
            // Wenn der L??ufer gefesselt ist, muss er sich in oder gegen die Richtung bewegen, in die er gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                // Diagonale von links unten nach rechts oben
                if(pinDirection == NORTH_EAST || pinDirection == SOUTH_WEST) {
                    int n_sq = sq + NORTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH_EAST;
                    }
                    n_sq = sq + SOUTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH_WEST;
                    }
                } else if(pinDirection == NORTH_WEST || pinDirection == SOUTH_EAST) {
                    // Diagonale von rechts unten nach links oben
                    int n_sq = sq + NORTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH_WEST;
                    }
                    n_sq = sq + SOUTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH_EAST;
                    }
                }
            } else {
                // Ansonsten darf er sich frei bewegen
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + DIAGONAL_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;

                        n_sq += DIAGONAL_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateWhiteRookMoves(Array<Move, 256>& moves, Board& b,
                                     int32_t numAttackers, Bitboard attackingRays,
                                     Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Turmzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Turm den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[WHITE_ROOK]) {
            // Wenn der Turm gefesselt ist, kann er sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + STRAIGHT_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn der Turm den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                    } else if(b.pieces[n_sq] != EMPTY)
                        break;
                        
                    n_sq += STRAIGHT_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[WHITE_ROOK]) {
            // Wenn der Turm gefesselt ist, muss er sich in oder gegen die Richtung bewegen, in die er gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                // Gerade von oben nach unten
                if(pinDirection == NORTH || pinDirection == SOUTH) {
                    int n_sq = sq + NORTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH;
                    }
                    n_sq = sq + SOUTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH;
                    }
                } else if(pinDirection == EAST || pinDirection == WEST) {
                    // Gerade von links nach rechts
                    int n_sq = sq + EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += EAST;
                    }
                    n_sq = sq + WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += WEST;
                    }
                }
            } else {
                // Ansonsten darf er sich frei bewegen
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + STRAIGHT_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;

                        n_sq += STRAIGHT_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateBlackRookMoves(Array<Move, 256>& moves, Board& b,
                                     int32_t numAttackers, Bitboard attackingRays,
                                     Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Turmzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Turm den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[BLACK_ROOK]) {
            // Wenn der Turm gefesselt ist, kann er sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + STRAIGHT_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn der Turm den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                    } else if(b.pieces[n_sq] != EMPTY)
                        break;
                        
                    n_sq += STRAIGHT_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[BLACK_ROOK]) {
            // Wenn der Turm gefesselt ist, muss er sich in oder gegen die Richtung bewegen, in die er gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                // Gerade von oben nach unten
                if(pinDirection == NORTH || pinDirection == SOUTH) {
                    int n_sq = sq + NORTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH;
                    }
                    n_sq = sq + SOUTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH;
                    }
                } else if(pinDirection == EAST || pinDirection == WEST) {
                    // Gerade von links nach rechts
                    int n_sq = sq + EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += EAST;
                    }
                    n_sq = sq + WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += WEST;
                    }
                }
            } else {
                // Ansonsten darf er sich frei bewegen
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + STRAIGHT_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;

                        n_sq += STRAIGHT_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateWhiteQueenMoves(Array<Move, 256>& moves, Board& b,
                                      int32_t numAttackers, Bitboard attackingRays,
                                      Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Damenzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann die Dame den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[WHITE_QUEEN]) {
            // Wenn die Dame gefesselt ist, kann sie sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            // Diagonal
            for(int i = 0; i < 4; i++) {
                int n_sq = sq + DIAGONAL_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn die Dame den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                    } else if(b.pieces[n_sq] != EMPTY)
                        break;
                        
                    n_sq +=  DIAGONAL_ATTACKS[i];
                }
            }

            // Gerade
            for(int i = 0; i < 4; i++) {
                int n_sq = sq + STRAIGHT_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn die Dame den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                    } else if(b.pieces[n_sq] != EMPTY)
                        break;
                        
                    n_sq += STRAIGHT_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[WHITE_QUEEN]) {
            // Wenn die Dame gefesselt ist, muss sie sich in oder gegen die Richtung bewegen, in die sie gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                // Diagonal von links oben nach rechts unten
                if(pinDirection == NORTH_WEST || pinDirection == SOUTH_EAST) {
                    int n_sq = sq + NORTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH_WEST;
                    }
                    n_sq = sq + SOUTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH_EAST;
                    }
                } else if(pinDirection == NORTH_EAST || pinDirection == SOUTH_WEST) {
                    // Diagonal von rechts oben nach links unten
                    int n_sq = sq + NORTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH_EAST;
                    }
                    n_sq = sq + SOUTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH_WEST;
                    }
                } else if(pinDirection == NORTH || pinDirection == SOUTH) {
                    // Gerade von oben nach unten
                    int n_sq = sq + NORTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH;
                    }
                    n_sq = sq + SOUTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH;
                    }
                } else if(pinDirection == EAST || pinDirection == WEST) {
                    // Gerade von links nach rechts
                    int n_sq = sq + EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += EAST;
                    }
                    n_sq = sq + WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += WEST;
                    }
                }
            } else {
                // Ansonsten darf sie sich frei bewegen

                // Diagonal
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + DIAGONAL_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;

                        n_sq += DIAGONAL_ATTACKS[i];
                    }
                }

                // Gerade
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + STRAIGHT_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;

                        n_sq += STRAIGHT_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateBlackQueenMoves(Array<Move, 256>& moves, Board& b,
                                      int32_t numAttackers, Bitboard attackingRays,
                                      Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Damenzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann die Dame den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[BLACK_QUEEN]) {
            // Wenn die Dame gefesselt ist, kann sie sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            // Diagonal
            for(int i = 0; i < 4; i++) {
                int n_sq = sq + DIAGONAL_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn die Dame den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                    } else if(b.pieces[n_sq] != EMPTY)
                        break;
                        
                    n_sq +=  DIAGONAL_ATTACKS[i];
                }
            }

            // Gerade
            for(int i = 0; i < 4; i++) {
                int n_sq = sq + STRAIGHT_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn die Dame den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                    } else if(b.pieces[n_sq] != EMPTY)
                        break;

                    n_sq += STRAIGHT_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[BLACK_QUEEN]) {
            // Wenn die Dame gefesselt ist, muss sie sich in oder gegen die Richtung bewegen, in die sie gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                // Diagonal von links oben nach rechts unten
                if(pinDirection == NORTH_WEST || pinDirection == SOUTH_EAST) {
                    int n_sq = sq + NORTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH_WEST;
                    }
                    n_sq = sq + SOUTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH_EAST;
                    }
                } else if(pinDirection == NORTH_EAST || pinDirection == SOUTH_WEST) {
                    // Diagonal von rechts oben nach links unten
                    int n_sq = sq + NORTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH_EAST;
                    }
                    n_sq = sq + SOUTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH_WEST;
                    }
                } else if(pinDirection == NORTH || pinDirection == SOUTH) {
                    // Gerade von oben nach unten
                    int n_sq = sq + NORTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += NORTH;
                    }
                    n_sq = sq + SOUTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += SOUTH;
                    }
                } else if(pinDirection == EAST || pinDirection == WEST) {
                    // Gerade von links nach rechts
                    int n_sq = sq + EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += EAST;
                    }
                    n_sq = sq + WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;
                        n_sq += WEST;
                    }
                }
            } else {
                // Ansonsten darf sie sich frei bewegen

                // Diagonal
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + DIAGONAL_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;

                        n_sq += DIAGONAL_ATTACKS[i];
                    }
                }

                // Gerade
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + STRAIGHT_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] == EMPTY)
                            moves.push_back(Move(sq, n_sq, MOVE_QUIET));
                        else if((b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        else
                            break;

                        n_sq += STRAIGHT_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateWhiteKingMoves(Array<Move, 256>& moves, Board& b,
                                     Bitboard attackedSquares) {
    int32_t KING_ATTACKS[8] = {
        DIAGONAL_ATTACKS[0], DIAGONAL_ATTACKS[1], DIAGONAL_ATTACKS[2], DIAGONAL_ATTACKS[3],
        STRAIGHT_ATTACKS[0], STRAIGHT_ATTACKS[1], STRAIGHT_ATTACKS[2], STRAIGHT_ATTACKS[3]
    };

    int sq = b.pieceList[WHITE_KING].front();
    for(int i = 0; i < 8; i++) {
        int n_sq = sq + KING_ATTACKS[i];
        if(Mailbox::mailbox[n_sq] != NO_SQ) {
            if(b.pieces[n_sq] == EMPTY && !attackedSquares.getBit(Mailbox::mailbox[n_sq]))
                moves.push_back(Move(sq, n_sq, MOVE_QUIET));
            else if((b.pieces[n_sq] & COLOR_MASK) == BLACK && !attackedSquares.getBit(Mailbox::mailbox[n_sq]))
                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
        }
    }

    if(!attackedSquares.getBit(Mailbox::mailbox[E1])) {
        if(b.castlingPermission & WHITE_KINGSIDE_CASTLE) {
            if(b.pieces[F1] == EMPTY && b.pieces[G1] == EMPTY &&
                !attackedSquares.getBit(Mailbox::mailbox[F1]) && !attackedSquares.getBit(Mailbox::mailbox[G1])) {
                moves.push_back(Move(E1, G1, MOVE_KINGSIDE_CASTLE));
            }
        }

        if(b.castlingPermission & WHITE_QUEENSIDE_CASTLE) {
            if(b.pieces[D1] == EMPTY && b.pieces[C1] == EMPTY && b.pieces[B1] == EMPTY &&
                !attackedSquares.getBit(Mailbox::mailbox[D1]) && !attackedSquares.getBit(Mailbox::mailbox[C1])) {
                moves.push_back(Move(E1, C1, MOVE_QUEENSIDE_CASTLE));
            }
        }
    }
}

void Movegen::generateBlackKingMoves(Array<Move, 256>& moves, Board& b,
                                     Bitboard attackedSquares) {
    int32_t KING_ATTACKS[8] = {
        DIAGONAL_ATTACKS[0], DIAGONAL_ATTACKS[1], DIAGONAL_ATTACKS[2], DIAGONAL_ATTACKS[3],
        STRAIGHT_ATTACKS[0], STRAIGHT_ATTACKS[1], STRAIGHT_ATTACKS[2], STRAIGHT_ATTACKS[3]
    };

    int sq = b.pieceList[BLACK_KING].front();
    for(int i = 0; i < 8; i++) {
        int n_sq = sq + KING_ATTACKS[i];
        if(Mailbox::mailbox[n_sq] != NO_SQ) {
            if(b.pieces[n_sq] == EMPTY && !attackedSquares.getBit(Mailbox::mailbox[n_sq]))
                moves.push_back(Move(sq, n_sq, MOVE_QUIET));
            else if((b.pieces[n_sq] & COLOR_MASK) == WHITE && !attackedSquares.getBit(Mailbox::mailbox[n_sq]))
                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
        }
    }

    if(!attackedSquares.getBit(Mailbox::mailbox[E8])) {
        if(b.castlingPermission & BLACK_KINGSIDE_CASTLE) {
            if(b.pieces[F8] == EMPTY && b.pieces[G8] == EMPTY &&
                !attackedSquares.getBit(Mailbox::mailbox[F8]) && !attackedSquares.getBit(Mailbox::mailbox[G8])) {
                moves.push_back(Move(E8, G8, MOVE_KINGSIDE_CASTLE));
            }
        }

        if(b.castlingPermission & BLACK_QUEENSIDE_CASTLE) {
            if(b.pieces[D8] == EMPTY && b.pieces[C8] == EMPTY && b.pieces[B8] == EMPTY &&
                !attackedSquares.getBit(Mailbox::mailbox[D8]) && !attackedSquares.getBit(Mailbox::mailbox[C8])) {
                moves.push_back(Move(E8, C8, MOVE_QUEENSIDE_CASTLE));
            }
        }
    }
}

void Movegen::generateWhitePawnCaptures(Array<Move, 256>& moves, Board& b,
                                     int32_t numAttackers, Bitboard attackingRays,
                                     Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Bauernzug kann legal sein
    if(numAttackers > 1)
        return;

    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Bauer den Angreifer schlagen oder den K??nig sch??tzen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[WHITE_PAWN]) {
            int32_t rank = SQ2R(sq);

            int32_t destLeft = sq + NORTH_WEST;
            int32_t destRight = sq + NORTH_EAST;

            bool pinned = pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]);

            // Wenn der Bauer gefesselt ist, kann er sich nicht bewegen
            if(pinned)
                continue;

            // En-Passant Z??ge befreien den K??nig nur aus dem Schach, wenn der geschlagene Bauer der Angreifer ist
            if(b.enPassantSquare != NO_SQ) {
                int32_t captureSquare = b.enPassantSquare + SOUTH;

                if(b.enPassantSquare == destLeft) {
                    if(attackingRays.getBit(Mailbox::mailbox[captureSquare]))
                        moves.push_back(Move(sq, destLeft, MOVE_EN_PASSANT));
                } else if(b.enPassantSquare == destRight) {
                    if(attackingRays.getBit(Mailbox::mailbox[captureSquare]))
                        moves.push_back(Move(sq, destRight, MOVE_EN_PASSANT));
                }
            }
            
            // Wenn der Bauer den Angreifer schlagen kann, ist der Zug legal
            if(b.pieces[destLeft] != EMPTY && attackingRays & Bitboard(1ULL << Mailbox::mailbox[destLeft]) && (b.pieces[destLeft] & COLOR_MASK) == BLACK) {
                // Promotion
                if(rank == RANK_7) {
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
            } else if(b.pieces[destRight] != EMPTY && attackingRays & Bitboard(1ULL << Mailbox::mailbox[destRight]) && (b.pieces[destRight] & COLOR_MASK) == BLACK) {
                // Promotion
                if(rank == RANK_7) {
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
            }
        }
    } else {
        for(int& sq : b.pieceList[WHITE_PAWN]) {
            int32_t rank = SQ2R(sq);

            int32_t destLeft = sq + NORTH_WEST;
            int32_t destRight = sq + NORTH_EAST;

            bool pinned = pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]);

            // En-Passant Z??ge entfernen 2 Figuren aus einer Reihe, daher muss immer ??berpr??ft werden, ob der K??nig nach dem Zug im Schach st??nde
            // -> Ein En-Passant Zug mit einem ungefesselten Bauer kann illegal sein
            if(b.enPassantSquare != NO_SQ) {
                int32_t captureSquare = b.enPassantSquare + SOUTH;
                int32_t kingSquare = b.pieceList[WHITE_KING].front();

                if(b.enPassantSquare == destLeft) {
                    Bitboard allPiecesAfterMove = b.allPiecesBitboard | b.pieceBitboard[BLACK_KING];
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[sq]);
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[captureSquare]);
                    allPiecesAfterMove.setBit(Mailbox::mailbox[destLeft]);

                    if(!b.squareAttacked(kingSquare, BLACK, allPiecesAfterMove))
                        moves.push_back(Move(sq, destLeft, MOVE_EN_PASSANT));

                } else if(b.enPassantSquare == destRight) {
                    Bitboard allPiecesAfterMove = b.allPiecesBitboard | b.pieceBitboard[BLACK_KING];
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[sq]);
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[captureSquare]);
                    allPiecesAfterMove.setBit(Mailbox::mailbox[destRight]);

                    if(!b.squareAttacked(kingSquare, BLACK, allPiecesAfterMove))
                        moves.push_back(Move(sq, destRight, MOVE_EN_PASSANT));
                }
            }

            // ??berpr??fe, ob der Bauer horizontal oder diagonal gefesselt ist
            // Wenn ja, kann er sich nur bewegen, wenn er den Angreifer schl??gt(diagonal)
            if(pinned) {
                int32_t pinDir = pinDirections[Mailbox::mailbox[sq]];
                if(pinDir == SOUTH_EAST || pinDir == NORTH_WEST) {
                    if(b.pieces[destLeft] != EMPTY && (b.pieces[destLeft] & COLOR_MASK) == BLACK) {
                        // Promotion
                        if(rank == RANK_7) {
                                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                                moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                        } else
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
                    }
                } else if(pinDir == SOUTH_WEST || pinDir == NORTH_EAST) {
                    if(b.pieces[destRight] != EMPTY && (b.pieces[destRight] & COLOR_MASK) == BLACK) {
                        // Promotion
                        if(rank == RANK_7) {
                                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                                moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                        } else
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
                    }
                }
                
                if(!(pinDir == NORTH || pinDir == SOUTH))
                    continue;
            }
            
            // Schlagz??ge
            // sind nur m??glich, wenn der Bauer nicht gefesselt ist
            int32_t nwPiece = b.pieces[destLeft];

            if(nwPiece != EMPTY && (nwPiece & COLOR_MASK) == BLACK && !pinned) {
                // Promotion
                if(rank == RANK_7) {
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
            }

            int32_t nePiece = b.pieces[destRight];

            if(nePiece != EMPTY && (nePiece & COLOR_MASK) == BLACK && !pinned) {
                // Promotion
                if(rank == RANK_7) {
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
            }
        }
    }
}

void Movegen::generateBlackPawnCaptures(Array<Move, 256>& moves, Board& b,
                                     int32_t numAttackers, Bitboard attackingRays,
                                     Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Bauerzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Bauer den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[BLACK_PAWN]) {
            int32_t rank = SQ2R(sq);

            int32_t destLeft = sq + SOUTH_WEST;
            int32_t destRight = sq + SOUTH_EAST;

            bool pinned = pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]);

            // Wenn der Bauer gefesselt ist, kann er sich nicht bewegen
            if(pinned)
                continue;
            
            // En-Passant Z??ge befreien den K??nig nur aus dem Schach, wenn der geschlagene Bauer der Angreifer ist
            if(b.enPassantSquare != NO_SQ) {
                int32_t captureSquare = b.enPassantSquare + NORTH;

                if(b.enPassantSquare == destLeft) {
                    if(attackingRays.getBit(Mailbox::mailbox[captureSquare]))
                        moves.push_back(Move(sq, destLeft, MOVE_EN_PASSANT));
                } else if(b.enPassantSquare == destRight) {
                    if(attackingRays.getBit(Mailbox::mailbox[captureSquare]))
                        moves.push_back(Move(sq, destRight, MOVE_EN_PASSANT));
                }
            }
            
            // Wenn der Bauer den Angreifer schlagen kann, ist der Zug legal
            if(b.pieces[destLeft] != EMPTY && attackingRays & Bitboard(1ULL << Mailbox::mailbox[destLeft]) && (b.pieces[destLeft] & COLOR_MASK) == WHITE) {
                // Promotion
                if(rank == RANK_2) {
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
            } else if(b.pieces[destRight] != EMPTY && attackingRays & Bitboard(1ULL << Mailbox::mailbox[destRight]) && (b.pieces[destRight] & COLOR_MASK) == WHITE) {
                // Promotion
                if(rank == RANK_2) {
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                        moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
            }
        }
    } else {
        for(int& sq : b.pieceList[BLACK_PAWN]) {
            int32_t rank = SQ2R(sq);

            int32_t destLeft = sq + SOUTH_WEST;
            int32_t destRight = sq + SOUTH_EAST;

            bool pinned = pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]);

            // En-Passant Z??ge entfernen 2 Figuren aus einer Reihe, daher muss immer ??berpr??ft werden, ob der K??nig nach dem Zug im Schach st??nde
            // -> Ein En-Passant Zug mit einem ungefesselten Bauer kann illegal sein
            if(b.enPassantSquare != NO_SQ) {
                int32_t captureSquare = b.enPassantSquare + NORTH;
                int32_t kingSquare = b.pieceList[BLACK_KING].front();

                if(b.enPassantSquare == destLeft) {
                    Bitboard allPiecesAfterMove = b.allPiecesBitboard | b.pieceBitboard[WHITE_KING];
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[sq]);
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[captureSquare]);
                    allPiecesAfterMove.setBit(Mailbox::mailbox[destLeft]);

                    if(!b.squareAttacked(kingSquare, WHITE, allPiecesAfterMove))
                        moves.push_back(Move(sq, destLeft, MOVE_EN_PASSANT));

                } else if(b.enPassantSquare == destRight) {
                    Bitboard allPiecesAfterMove = b.allPiecesBitboard | b.pieceBitboard[WHITE_KING];
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[sq]);
                    allPiecesAfterMove.clearBit(Mailbox::mailbox[captureSquare]);
                    allPiecesAfterMove.setBit(Mailbox::mailbox[destRight]);

                    if(!b.squareAttacked(kingSquare, WHITE, allPiecesAfterMove))
                        moves.push_back(Move(sq, destRight, MOVE_EN_PASSANT));
                }
            }

            // ??berpr??fe, ob der Bauer horizontal oder diagonal gefesselt ist
            // Wenn ja, kann er sich nur bewegen, wenn er den Angreifer schl??gt(diagonal)
            if(pinned) {
                int32_t pinDir = pinDirections[Mailbox::mailbox[sq]];
                
                if(pinDir == NORTH_EAST || pinDir == SOUTH_WEST) {
                    if(b.pieces[destLeft] != EMPTY && (b.pieces[destLeft] & COLOR_MASK) == WHITE) {
                        // Promotion
                        if(rank == RANK_2) {
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                        } else
                            moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
                    }
                } else if(pinDir == NORTH_WEST || pinDir == SOUTH_EAST) {
                    if(b.pieces[destRight] != EMPTY && (b.pieces[destRight] & COLOR_MASK) == WHITE) {
                        // Promotion
                        if(rank == RANK_2) {
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                        } else
                            moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
                    }
                }
                
                if(!(pinDir == NORTH || pinDir == SOUTH))
                    continue;
            }
            
            // Schlagz??ge
            // sind nur m??glich, wenn der Bauer nicht gefesselt ist
            int32_t swPiece = b.pieces[destLeft];

            if(swPiece != EMPTY && (swPiece & COLOR_MASK) == WHITE && !pinned) {
                // Promotion
                if(rank == RANK_2) {
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destLeft, MOVE_CAPTURE));
            }

            int32_t sePiece = b.pieces[destRight];

            if(sePiece != EMPTY && (sePiece & COLOR_MASK) == WHITE && !pinned) {
                // Promotion
                if(rank == RANK_2) {
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_QUEEN));
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_ROOK));
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_BISHOP));
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE | MOVE_PROMOTION_KNIGHT));
                } else
                    moves.push_back(Move(sq, destRight, MOVE_CAPTURE));
            }
        }
    }
}

void Movegen::generateWhiteKnightCaptures(Array<Move, 256>& moves, Board& b,
                                       int32_t numAttackers, Bitboard attackingRays,
                                       Bitboard pinnedPieces) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Springerzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Springer den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[WHITE_KNIGHT]) {
            // Wenn der Springer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPieces & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 8; i++) {
                int n_sq = sq + KNIGHT_ATTACKS[i];

                if(Mailbox::mailbox[n_sq] == NO_SQ)
                    continue;
                
                // Wenn der Springer den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq]))
                    if(b.pieces[n_sq] != EMPTY)
                        moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
            }
        }
    } else {
        for(int& sq : b.pieceList[WHITE_KNIGHT]) {
            // Wenn der Springer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPieces & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            // Ansonsten darf er sich frei bewegen
            for(int i = 0; i < 8; i++) {
                int n_sq = sq + KNIGHT_ATTACKS[i];
                if(Mailbox::mailbox[n_sq] != NO_SQ) {
                    if(b.pieces[n_sq] != EMPTY && (b.pieces[n_sq] & COLOR_MASK) == BLACK)
                        moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                }
            }
        }
    }
}

void Movegen::generateBlackKnightCaptures(Array<Move, 256>& moves, Board& b,
                                       int32_t numAttackers, Bitboard attackingRays,
                                       Bitboard pinnedPieces) {

    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Springerzug kann legal sein
    if(numAttackers > 1)
        return;

    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Springer den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[BLACK_KNIGHT]) {
            // Wenn der Springer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPieces & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 8; i++) {
                int n_sq = sq + KNIGHT_ATTACKS[i];

                if(Mailbox::mailbox[n_sq] == NO_SQ)
                    continue;
                
                // Wenn der Springer den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq]))
                    if(b.pieces[n_sq] != EMPTY)
                        moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
            }
        }
    } else {
        for(int& sq : b.pieceList[BLACK_KNIGHT]) {
            // Wenn der Springer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPieces & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            // Ansonsten darf er sich frei bewegen
            for(int i = 0; i < 8; i++) {
                int n_sq = sq + KNIGHT_ATTACKS[i];
                if(Mailbox::mailbox[n_sq] != NO_SQ) {
                    if(b.pieces[n_sq] != EMPTY && (b.pieces[n_sq] & COLOR_MASK) == WHITE)
                        moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                }
            }
        }
    }
}

void Movegen::generateWhiteBishopCaptures(Array<Move, 256>& moves, Board& b,
                                       int32_t numAttackers, Bitboard attackingRays,
                                       Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein L??uferzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der L??ufer den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[WHITE_BISHOP]) {
            // Wenn der L??ufer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + DIAGONAL_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn der L??ufer den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] != EMPTY && (b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                    } else
                        break;
                        
                    n_sq += DIAGONAL_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[WHITE_BISHOP]) {
            // Wenn der L??ufer gefesselt ist, muss er sich in oder gegen die Richtung bewegen, in die er gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                // Diagonale von links unten nach rechts oben
                if(pinDirection == NORTH_EAST || pinDirection == SOUTH_WEST) {
                    int n_sq = sq + NORTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH_EAST;
                    }
                    n_sq = sq + SOUTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH_WEST;
                    }
                } else if(pinDirection == NORTH_WEST || pinDirection == SOUTH_EAST) {
                    // Diagonale von rechts unten nach links oben
                    int n_sq = sq + NORTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH_WEST;
                    }
                    n_sq = sq + SOUTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH_EAST;
                    }
                }
            } else {
                // Ansonsten darf er sich frei bewegen
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + DIAGONAL_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += DIAGONAL_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateBlackBishopCaptures(Array<Move, 256>& moves, Board& b,
                                       int32_t numAttackers, Bitboard attackingRays,
                                       Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein L??uferzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der L??ufer den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[BLACK_BISHOP]) {
            // Wenn der L??ufer gefesselt ist, kann er sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + DIAGONAL_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn der L??ufer den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] != EMPTY && (b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                    } else
                        break;
                        
                    n_sq += DIAGONAL_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[BLACK_BISHOP]) {
            // Wenn der L??ufer gefesselt ist, muss er sich in oder gegen die Richtung bewegen, in die er gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                // Diagonale von links unten nach rechts oben
                if(pinDirection == NORTH_EAST || pinDirection == SOUTH_WEST) {
                    int n_sq = sq + NORTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH_EAST;
                    }
                    n_sq = sq + SOUTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH_WEST;
                    }
                } else if(pinDirection == NORTH_WEST || pinDirection == SOUTH_EAST) {
                    // Diagonale von rechts unten nach links oben
                    int n_sq = sq + NORTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH_WEST;
                    }
                    n_sq = sq + SOUTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH_EAST;
                    }
                }
            } else {
                // Ansonsten darf er sich frei bewegen
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + DIAGONAL_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += DIAGONAL_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateWhiteRookCaptures(Array<Move, 256>& moves, Board& b,
                                     int32_t numAttackers, Bitboard attackingRays,
                                     Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Turmzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Turm den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[WHITE_ROOK]) {
            // Wenn der Turm gefesselt ist, kann er sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + STRAIGHT_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn der Turm den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] != EMPTY && (b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                    } else
                        break;
                    n_sq += STRAIGHT_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[WHITE_ROOK]) {
            // Wenn der Turm gefesselt ist, muss er sich in oder gegen die Richtung bewegen, in die er gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                if(pinDirection == NORTH || pinDirection == SOUTH) {
                    // Gerade von oben nach unten
                    int n_sq = sq + NORTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH;
                    }
                    n_sq = sq + SOUTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH;
                    }
                } else if(pinDirection == EAST || pinDirection == WEST) {
                    // Gerade von rechts nach links
                    int n_sq = sq + EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += EAST;
                    }
                    n_sq = sq + WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += WEST;
                    }
                }
            } else {
                // Ansonsten darf er sich frei bewegen
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + STRAIGHT_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }

                        n_sq += STRAIGHT_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateBlackRookCaptures(Array<Move, 256>& moves, Board& b,
                                     int32_t numAttackers, Bitboard attackingRays,
                                     Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein Turmzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann der Turm den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[BLACK_ROOK]) {
            // Wenn der Turm gefesselt ist, kann er sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + STRAIGHT_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn der Turm den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] != EMPTY && (b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                    } else
                        break;
                    n_sq += STRAIGHT_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[BLACK_ROOK]) {
            // Wenn der Turm gefesselt ist, muss er sich in oder gegen die Richtung bewegen, in die er gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                if(pinDirection == NORTH || pinDirection == SOUTH) {
                    // Gerade von oben nach unten
                    int n_sq = sq + NORTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH;
                    }
                    n_sq = sq + SOUTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH;
                    }
                } else if(pinDirection == EAST || pinDirection == WEST) {
                    // Gerade von rechts nach links
                    int n_sq = sq + EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += EAST;
                    }
                    n_sq = sq + WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += WEST;
                    }
                }
            } else {
                // Ansonsten darf er sich frei bewegen
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + STRAIGHT_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }

                        n_sq += STRAIGHT_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateWhiteQueenCaptures(Array<Move, 256>& moves, Board& b,
                                     int32_t numAttackers, Bitboard attackingRays,
                                     Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein L??uferzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann die Dame den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[WHITE_QUEEN]) {
            // Wenn die Dame gefesselt ist, kann sie sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + DIAGONAL_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn die Dame den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] != EMPTY && (b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                    } else
                        break;
                    n_sq += DIAGONAL_ATTACKS[i];
                }
            }
            
            for(int i = 0; i < 4; i++) {
                int n_sq = sq + STRAIGHT_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn die Dame den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] != EMPTY && (b.pieces[n_sq] & COLOR_MASK) == BLACK) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                    } else
                        break;
                    n_sq += STRAIGHT_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[WHITE_QUEEN]) {
            // Wenn die Dame gefesselt ist, muss sie sich in oder gegen die Richtung bewegen, in die sie gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                if(pinDirection == NORTH_EAST || pinDirection == SOUTH_WEST) {
                    // Diagonale von oben links nach unten rechts
                    int n_sq = sq + NORTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH_EAST;
                    }
                    n_sq = sq + SOUTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH_WEST;
                    }
                } else if(pinDirection == NORTH_WEST || pinDirection == SOUTH_EAST) {
                    // Diagonale von oben rechts nach unten links
                    int n_sq = sq + NORTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH_WEST;
                    }
                    n_sq = sq + SOUTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH_EAST;
                    }
                } else if(pinDirection == NORTH || pinDirection == SOUTH) {
                    // Gerade von oben nach unten
                    int n_sq = sq + NORTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH;
                    }
                    n_sq = sq + SOUTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH;
                    }
                } else if(pinDirection == WEST || pinDirection == EAST) {
                    // Gerade von links nach rechts
                    int n_sq = sq + WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += WEST;
                    }
                    n_sq = sq + EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += EAST;
                    }
                }
            } else {
                // Wenn die Dame nicht gefesselt ist, kann sie sich in jede Richtung bewegen
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + DIAGONAL_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += DIAGONAL_ATTACKS[i];
                    }
                }
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + STRAIGHT_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == BLACK)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += STRAIGHT_ATTACKS[i];
                    }
                }
            }
        }
    }
}

void Movegen::generateBlackQueenCaptures(Array<Move, 256>& moves, Board& b,
                                     int32_t numAttackers, Bitboard attackingRays,
                                     Bitboard pinnedPiecesBitboard, int32_t* pinDirections) {
    // Wenn der eigene K??nig von mehr als einer Figur angegriffen wird, muss er sich bewegen
    // -> Kein L??uferzug kann legal sein
    if(numAttackers > 1)
        return;
    
    // Wenn der eigene K??nig von genau einer Figur angegriffen wird, kann die Dame den Angreifer schlagen oder sich dazwischen stellen
    if(numAttackers == 1) {
        for(int& sq : b.pieceList[BLACK_QUEEN]) {
            // Wenn die Dame gefesselt ist, kann sie sich nicht bewegen
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq]))
                continue;

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + DIAGONAL_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn die Dame den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] != EMPTY && (b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                    } else
                        break;
                    n_sq += DIAGONAL_ATTACKS[i];
                }
            }

            for(int i = 0; i < 4; i++) {
                int n_sq = sq + STRAIGHT_ATTACKS[i];
                while(Mailbox::mailbox[n_sq] != NO_SQ) {
                    // Wenn die Dame den Angreifer schlagen oder sich dazwischen stellen kann, ist der Zug legal
                    if(attackingRays & Bitboard(1ULL << Mailbox::mailbox[n_sq])) {
                        if(b.pieces[n_sq] != EMPTY && (b.pieces[n_sq] & COLOR_MASK) == WHITE) {
                            moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                    } else
                        break;
                    n_sq += STRAIGHT_ATTACKS[i];
                }
            }
        }
    } else {
        for(int& sq : b.pieceList[BLACK_QUEEN]) {
            // Wenn die Dame gefesselt ist, muss sie sich in oder gegen die Richtung bewegen, in die sie gefesselt ist
            if(pinnedPiecesBitboard & Bitboard(1ULL << Mailbox::mailbox[sq])) {
                int32_t pinDirection = pinDirections[Mailbox::mailbox[sq]];

                if(pinDirection == NORTH_EAST || pinDirection == SOUTH_WEST) {
                    // Diagonale von oben links nach unten rechts
                    int n_sq = sq + NORTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH_EAST;
                    }
                    n_sq = sq + SOUTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH_WEST;
                    }
                } else if(pinDirection == NORTH_WEST || pinDirection == SOUTH_EAST) {
                    // Diagonale von oben rechts nach unten links
                    int n_sq = sq + NORTH_WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH_WEST;
                    }
                    n_sq = sq + SOUTH_EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH_EAST;
                    }
                } else if(pinDirection == NORTH || pinDirection == SOUTH) {
                    // Gerade von oben nach unten
                    int n_sq = sq + NORTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += NORTH;
                    }
                    n_sq = sq + SOUTH;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += SOUTH;
                    }
                } else if(pinDirection == WEST || pinDirection == EAST) {
                    // Gerade von links nach rechts
                    int n_sq = sq + WEST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += WEST;
                    }
                    n_sq = sq + EAST;
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += EAST;
                    }
                }
            } else {
                // Wenn die Dame nicht gefesselt ist, kann sie sich in jede Richtung bewegen
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + DIAGONAL_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += DIAGONAL_ATTACKS[i];
                    }
                }
                for(int i = 0; i < 4; i++) {
                    int n_sq = sq + STRAIGHT_ATTACKS[i];
                    while(Mailbox::mailbox[n_sq] != NO_SQ) {
                        if(b.pieces[n_sq] != EMPTY) {
                            if((b.pieces[n_sq] & COLOR_MASK) == WHITE)
                                moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                            break;
                        }
                        n_sq += STRAIGHT_ATTACKS[i];
                    }
                }
            }
        }
    }
}
    

void Movegen::generateWhiteKingCaptures(Array<Move, 256>& moves, Board& b,
                                        Bitboard attackedSquares) {
    int32_t KING_ATTACKS[8] = {
        DIAGONAL_ATTACKS[0], DIAGONAL_ATTACKS[1], DIAGONAL_ATTACKS[2], DIAGONAL_ATTACKS[3],
        STRAIGHT_ATTACKS[0], STRAIGHT_ATTACKS[1], STRAIGHT_ATTACKS[2], STRAIGHT_ATTACKS[3]
    };

    int sq = b.pieceList[WHITE_KING].front();
    for(int i = 0; i < 8; i++) {
        int n_sq = sq + KING_ATTACKS[i];
        if(Mailbox::mailbox[n_sq] != NO_SQ) {
            if(b.pieces[n_sq] != EMPTY) {
                if((b.pieces[n_sq] & COLOR_MASK) == BLACK && !attackedSquares.getBit(Mailbox::mailbox[n_sq]))
                    moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                
                break;
            }
        }
    }
}

void Movegen::generateBlackKingCaptures(Array<Move, 256>& moves, Board& b,
                                        Bitboard attackedSquares) {
    int32_t KING_ATTACKS[8] = {
        DIAGONAL_ATTACKS[0], DIAGONAL_ATTACKS[1], DIAGONAL_ATTACKS[2], DIAGONAL_ATTACKS[3],
        STRAIGHT_ATTACKS[0], STRAIGHT_ATTACKS[1], STRAIGHT_ATTACKS[2], STRAIGHT_ATTACKS[3]
    };

    int sq = b.pieceList[BLACK_KING].front();
    for(int i = 0; i < 8; i++) {
        int n_sq = sq + KING_ATTACKS[i];
        if(Mailbox::mailbox[n_sq] != NO_SQ) {
            if(b.pieces[n_sq] != EMPTY) {
                if((b.pieces[n_sq] & COLOR_MASK) == WHITE && !attackedSquares.getBit(Mailbox::mailbox[n_sq]))
                    moves.push_back(Move(sq, n_sq, MOVE_CAPTURE));
                
                break;
            }
        }
    }
}