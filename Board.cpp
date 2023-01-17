#include "Board.h"
#include <iostream>
#include <stdio.h>
#include "OrderedMoveList.h"

Board::Board() {
    initMailbox();

    side = WHITE;
    enPassantSquare = NO_SQ;
    fiftyMoveRule = 0;
    castlingPermission = WHITE_KINGSIDE_CASTLE |
                       WHITE_QUEENSIDE_CASTLE |
                       BLACK_KINGSIDE_CASTLE |
                       BLACK_QUEENSIDE_CASTLE;
    ply = 0;

    generateBitboards();
}

Board::Board(std::string fen) {
    initMailbox();

    // Spielfeld-Array und Figurlisten leeren
    for(int i = 0; i < 15; i++)
        pieceList[i].clear();
    
    for(int i = 0; i < 120; i++)
        pieces[i] = EMPTY;

    int file = FILE_A;
    int rank = RANK_8;
    int indexNextSection = fen.find(' ');

    // Figuren auslesen und einfügen
    std::string fenPieces = fen.substr(0, indexNextSection);
    for(char c : fenPieces) {
        if(c == '/') {
            file = FILE_A;
            rank--;
        }
        else if(c >= '1' && c <= '8') {
            file += c - '0';
        }
        else {
            int piece = EMPTY;
            switch(c) {
                case 'p': piece = BLACK_PAWN; break;
                case 'n': piece = BLACK_KNIGHT; break;
                case 'b': piece = BLACK_BISHOP; break;
                case 'r': piece = BLACK_ROOK; break;
                case 'q': piece = BLACK_QUEEN; break;
                case 'k': piece = BLACK_KING; break;
                case 'P': piece = WHITE_PAWN; break;
                case 'N': piece = WHITE_KNIGHT; break;
                case 'B': piece = WHITE_BISHOP; break;
                case 'R': piece = WHITE_ROOK; break;
                case 'Q': piece = WHITE_QUEEN; break;
                case 'K': piece = WHITE_KING; break;
            }
            int square = FR2SQ(file, rank);
            pieces[square] = piece;
            pieceList[piece].push_back(square);
            file++;
        }
    }
    
    fen = fen.substr(indexNextSection + 1);
    indexNextSection = fen.find(' ');

    // Zugfarbe auslesen
    side = fen[0] == 'w' ? WHITE : BLACK;
    fen = fen.substr(indexNextSection + 1);
    indexNextSection = fen.find(' ');

    // Noch mögliche Rochaden auslesen
    std::string fenCastling = fen.substr(0, indexNextSection);
    castlingPermission = 0;
    for(char c : fenCastling) {
        switch(c) {
            case 'K': castlingPermission |= WHITE_KINGSIDE_CASTLE; break;
            case 'Q': castlingPermission |= WHITE_QUEENSIDE_CASTLE; break;
            case 'k': castlingPermission |= BLACK_KINGSIDE_CASTLE; break;
            case 'q': castlingPermission |= BLACK_QUEENSIDE_CASTLE; break;
        }
    }
    fen = fen.substr(indexNextSection + 1);
    indexNextSection = fen.find(' ');

    // En Passant Feld auslesen
    std::string fenEnPassant = fen.substr(0, indexNextSection);
    if(fenEnPassant != "-") {
        int file = fenEnPassant[0] - 'a';
        int rank = fenEnPassant[1] - '1';
        enPassantSquare = FR2SQ(file, rank);
    }
    else {
        enPassantSquare = NO_SQ;
    }
    fen = fen.substr(indexNextSection + 1);
    indexNextSection = fen.find(' ');

    // Status der 50-Züge-Regel auslesen
    fiftyMoveRule = std::stoi(fen.substr(0, indexNextSection));
    fen = fen.substr(indexNextSection + 1);

    // Anzahl der bereits gespielten Halbzüge auslesen
    ply = std::stoi(fen) - 1;

    generateBitboards();
}

Board::~Board() {

}

void Board::initMailbox() {
    for(int i = 0; i < 120; i++)
        mailbox[i] = NO_SQ;
    
    int index = 0;
    for(int rank = RANK_1; rank <= RANK_8; rank++) {
        for(int file = FILE_A; file <= FILE_H; file++) {
            int square = FR2SQ(file, rank);
            mailbox[square] = index;
            mailbox64[index] = square;
            index++;
        }
    }    
}

void Board::generateBitboards() {
    // weißer Bauer
    uint64_t res = 0ULL;
    for(int i : pieceList[WHITE_PAWN])
        res |= (1ULL << mailbox[i]);
    
    pieceBitboard[WHITE_PAWN] = Bitboard(res);

    // weißer Springer
    res = 0ULL;
    for(int i : pieceList[WHITE_KNIGHT])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[WHITE_KNIGHT] = Bitboard(res);

    // weißer Läufer
    res = 0ULL;
    for(int i : pieceList[WHITE_BISHOP])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[WHITE_BISHOP] = Bitboard(res);

    // weißer Turm
    res = 0ULL;
    for(int i : pieceList[WHITE_ROOK])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[WHITE_ROOK] = Bitboard(res);

    // weiße Dame
    res = 0ULL;
    for(int i : pieceList[WHITE_QUEEN])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[WHITE_QUEEN] = Bitboard(res);

    // weißer König
    res = 0ULL;
    for(int i : pieceList[WHITE_KING])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[WHITE_KING] = Bitboard(res);

    // schwarzer Bauer
    res = 0ULL;
    for(int i : pieceList[BLACK_PAWN])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[BLACK_PAWN] = Bitboard(res);

    // schwarzer Springer
    res = 0ULL;
    for(int i : pieceList[BLACK_KNIGHT])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[BLACK_KNIGHT] = Bitboard(res);

    // schwarzer Läufer
    res = 0ULL;
    for(int i : pieceList[BLACK_BISHOP])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[BLACK_BISHOP] = Bitboard(res);

    // schwarzer Turm
    res = 0ULL;
    for(int i : pieceList[BLACK_ROOK])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[BLACK_ROOK] = Bitboard(res);

    // schwarze Dame
    res = 0ULL;
    for(int i : pieceList[BLACK_QUEEN])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[BLACK_QUEEN] = Bitboard(res);

    // schwarzer König
    res = 0ULL;
    for(int i : pieceList[BLACK_KING])
        res |= (1ULL << mailbox[i]);

    pieceBitboard[BLACK_KING] = Bitboard(res);

    // alle weißen Figuren
    whitePiecesBitboard = pieceBitboard[WHITE_PAWN] |
                  pieceBitboard[WHITE_KNIGHT] |
                  pieceBitboard[WHITE_BISHOP] |
                  pieceBitboard[WHITE_ROOK] |
                  pieceBitboard[WHITE_QUEEN];

    // alle schwarzen Figuren
    blackPiecesBitboard = pieceBitboard[BLACK_PAWN] |
                  pieceBitboard[BLACK_KNIGHT] |
                  pieceBitboard[BLACK_BISHOP] |
                  pieceBitboard[BLACK_ROOK] |
                  pieceBitboard[BLACK_QUEEN];
    
    // alle Figuren
    allPiecesBitboard = whitePiecesBitboard | blackPiecesBitboard;
}

bool Board::isLegal(Move move) {
    int32_t ownSide = side;
    int32_t enemySide = side ^ COLOR_MASK;
    int32_t origin = move.getOrigin();
    int32_t destination = move.getDestination();
    int32_t pieceType = TYPEOF(pieces[origin]);

    Bitboard allPiecesPlusEnemyKing = allPiecesBitboard | pieceBitboard[enemySide | KING];

    // Spezialfall: En Passant
    if(move.isEnPassant()) {
        ASSERT(enPassantSquare != NO_SQ);

        // Das occupied-Bitboard muss so angepasst werden,
        // dass der En Passant geschlagene Bauer nicht mehr existiert
        int32_t capturedPawnSquare = enPassantSquare + (ownSide == WHITE ? SOUTH : NORTH);

        Bitboard modifiedBitboard = allPiecesPlusEnemyKing;
        modifiedBitboard.clearBit(mailbox[origin]);
        modifiedBitboard.clearBit(mailbox[capturedPawnSquare]);
        modifiedBitboard.setBit(mailbox[destination]);

        // Überprüfe, ob der König im Schach steht
        int32_t kingSquare = pieceList[ownSide | KING].front();
        return !squareAttacked(kingSquare, enemySide, modifiedBitboard);
    }

    int32_t kingSquare = pieceList[ownSide | KING].front();

    // Spezialfall: Rochade
    if(move.isCastle()) {
        // Der König, sein Ausgangsfeld und das Feld, dass er überspringt dürfen nicht im Schach stehen
        if(move.isKingsideCastle())
            return !squareAttacked(kingSquare, enemySide, allPiecesPlusEnemyKing) &&
                   !squareAttacked(kingSquare + 1, enemySide, allPiecesPlusEnemyKing) &&
                   !squareAttacked(kingSquare + 2, enemySide, allPiecesPlusEnemyKing);
        else
            return !squareAttacked(kingSquare, enemySide, allPiecesPlusEnemyKing) &&
                   !squareAttacked(kingSquare - 1, enemySide, allPiecesPlusEnemyKing) &&
                   !squareAttacked(kingSquare - 2, enemySide, allPiecesPlusEnemyKing);
    }

    // Spezialfall: Der König wird bewegt
    if(pieceType == KING) {
        // Der König darf sich nicht ins Schach bewegen
        return !squareAttacked(destination, enemySide, allPiecesPlusEnemyKing);
    }

    // Überprüfe, ob die bewegte Figur den König beschützt
    Bitboard modifiedBitboard = allPiecesBitboard;
    modifiedBitboard.clearBit(mailbox[origin]);
    modifiedBitboard.setBit(mailbox[destination]);

    return !squareAttacked(kingSquare, enemySide, allPiecesPlusEnemyKing);
}

void Board::makeMove(Move m) {
    int32_t origin = m.getOrigin();
    int32_t destination = m.getDestination();
    int32_t origin64 = mailbox[origin];
    int32_t destination64 = mailbox[destination];
    int32_t pieceType = pieces[origin];
    int32_t capturedPieceType = pieces[destination];
    int32_t enPassantCaptureSq = enPassantSquare + (side == WHITE ? SOUTH : NORTH);

    if(m.isEnPassant())
        capturedPieceType = pieces[enPassantCaptureSq];

    // Speichere den Zustand des Spielfeldes, um den Zug später wieder rückgängig machen zu können
    MoveHistoryEntry entry(m);
    entry.capturedPiece = capturedPieceType;
    entry.castlingPermission = castlingPermission;
    entry.enPassantSquare = enPassantSquare;
    entry.fiftyMoveRule = fiftyMoveRule;
    entry.hashValue = hashValue;

    moveHistory.push_back(entry);

    // Zug ausführen
    ASSERT(pieceType != EMPTY);
    ASSERT((pieceType & COLOR_MASK) == side);
    if(capturedPieceType != EMPTY)
        ASSERT((capturedPieceType & COLOR_MASK) != side);

    // Spezialfall: En Passant
    if(m.isEnPassant()) {
        ASSERT(enPassantSquare != NO_SQ);

        // Entferne den geschlagenen Bauern
        int32_t other = side ^ COLOR_MASK;
        ASSERT(capturedPieceType == (other | PAWN));

        int32_t enPassantSquare64 = mailbox[enPassantCaptureSq];
        pieces[enPassantCaptureSq] = EMPTY;
        pieceList[capturedPieceType].remove(enPassantCaptureSq);
        pieceBitboard[capturedPieceType].clearBit(enPassantSquare64);
        allPiecesBitboard.clearBit(enPassantSquare64);
        if(side == WHITE)
            blackPiecesBitboard.clearBit(enPassantSquare64);
        else
            whitePiecesBitboard.clearBit(enPassantSquare64);
    }

    // Spezialfall: Rochade
    if(m.isCastle()) {
        if(m.isKingsideCastle()) {
            // Turm auf Königsseite bewegen
            ASSERT(TYPEOF(pieces[origin + 3]) == ROOK);
            pieces[origin + 3] = EMPTY;
            pieces[origin + 1] = side | ROOK;
            pieceList[side | ROOK].remove(origin + 3);
            pieceList[side | ROOK].push_back(origin + 1);
            pieceBitboard[side | ROOK].clearBit(origin64 + 3);
            pieceBitboard[side | ROOK].setBit(origin64 + 1);
            allPiecesBitboard.clearBit(origin64 + 3);
            allPiecesBitboard.setBit(origin64 + 1);
            if(side == WHITE) {
                whitePiecesBitboard.clearBit(origin64 + 3);
                whitePiecesBitboard.setBit(origin64 + 1);
            }
            else {
                blackPiecesBitboard.clearBit(origin64 + 3);
                blackPiecesBitboard.setBit(origin64 + 1);
            }
        } else {
            // Turm auf Damenseite bewegen
            ASSERT(TYPEOF(pieces[origin - 4]) == ROOK);
            pieces[origin - 4] = EMPTY;
            pieces[origin - 1] = side | ROOK;
            pieceList[side | ROOK].remove(origin - 4);
            pieceList[side | ROOK].push_back(origin - 1);
            pieceBitboard[side | ROOK].clearBit(origin64 - 4);
            pieceBitboard[side | ROOK].setBit(origin64 - 1);
            allPiecesBitboard.clearBit(origin64 - 4);
            allPiecesBitboard.setBit(origin64 - 1);
            if(side == WHITE) {
                whitePiecesBitboard.clearBit(origin64 - 4);
                whitePiecesBitboard.setBit(origin64 - 1);
            }
            else {
                blackPiecesBitboard.clearBit(origin64 - 4);
                blackPiecesBitboard.setBit(origin64 - 1);
            }
        }
    }

    // Bewege die Figur
    pieces[origin] = EMPTY;
    pieces[destination] = pieceType;
    pieceList[pieceType].remove(origin);
    pieceList[pieceType].push_back(destination);
    pieceBitboard[pieceType].clearBit(origin64);
    pieceBitboard[pieceType].setBit(destination64);
    allPiecesBitboard.clearBit(origin64);
    allPiecesBitboard.setBit(destination64);
    if(side == WHITE) {
        whitePiecesBitboard.clearBit(origin64);
        whitePiecesBitboard.setBit(destination64);
    }
    else {
        blackPiecesBitboard.clearBit(origin64);
        blackPiecesBitboard.setBit(destination64);
    }

    // Spezialfall: Schlagen
    if(capturedPieceType != EMPTY && !m.isEnPassant()) {
        pieceList[capturedPieceType].remove(destination);
        pieceBitboard[capturedPieceType].clearBit(destination64);
        if(side == WHITE)
            blackPiecesBitboard.clearBit(destination64);
        else
            whitePiecesBitboard.clearBit(destination64);
    }

    // Spezialfall: Bauernumwandlung
    if(m.isPromotion()) {
        int32_t promotedPieceType = EMPTY;
        if(m.isPromotionQueen())
            promotedPieceType = QUEEN;
        else if(m.isPromotionRook())
            promotedPieceType = ROOK;
        else if(m.isPromotionBishop())
            promotedPieceType = BISHOP;
        else if(m.isPromotionKnight())
            promotedPieceType = KNIGHT;
        else
            ASSERT(false);

        // Entferne den Bauern, die allgemeinen Bitboards müssen nicht angepasst werden
        pieceList[side | PAWN].remove(destination);
        pieceBitboard[side | PAWN].clearBit(destination64);

        // Füge die neue Figur hinzu
        pieces[destination] = side | promotedPieceType;
        pieceList[side | promotedPieceType].push_back(destination);
        pieceBitboard[side | promotedPieceType].setBit(destination64);
    }

    // Aktualisiere Rochandenrechte und En Passant
    enPassantSquare = NO_SQ;

    if(TYPEOF(pieceType) == KING || TYPEOF(pieceType) == ROOK) {
        if(pieceType == WHITE_KING)
            castlingPermission &= ~(WHITE_KINGSIDE_CASTLE | WHITE_QUEENSIDE_CASTLE);
        else if(pieceType == BLACK_KING)
            castlingPermission &= ~(BLACK_KINGSIDE_CASTLE | BLACK_QUEENSIDE_CASTLE);
        else if(pieceType == WHITE_ROOK && origin == A1)
            castlingPermission &= ~WHITE_QUEENSIDE_CASTLE;
        else if(pieceType == WHITE_ROOK && origin == H1)
            castlingPermission &= ~WHITE_KINGSIDE_CASTLE;
        else if(pieceType == BLACK_ROOK && origin == A8)
            castlingPermission &= ~BLACK_QUEENSIDE_CASTLE;
        else if(pieceType == BLACK_ROOK && origin == H8)
            castlingPermission &= ~BLACK_KINGSIDE_CASTLE;
    }

    if(TYPEOF(capturedPieceType) == ROOK) {
        if(capturedPieceType == WHITE_ROOK && destination == A1)
            castlingPermission &= ~WHITE_QUEENSIDE_CASTLE;
        else if(capturedPieceType == WHITE_ROOK && destination == H1)
            castlingPermission &= ~WHITE_KINGSIDE_CASTLE;
        else if(capturedPieceType == BLACK_ROOK && destination == A8)
            castlingPermission &= ~BLACK_QUEENSIDE_CASTLE;
        else if(capturedPieceType == BLACK_ROOK && destination == H8)
            castlingPermission &= ~BLACK_KINGSIDE_CASTLE;
    }

    if(m.isDoublePawn()) {
        if(side == WHITE)
            enPassantSquare = destination + SOUTH;
        else
            enPassantSquare = destination + NORTH;
    }

    // Aktualisiere den Spielzustand
    if(capturedPieceType != EMPTY || TYPEOF(pieceType) == PAWN)
        fiftyMoveRule = 0;
    else
        fiftyMoveRule++;

    side = side ^ COLOR_MASK;
    ply++;
}

void Board::undoMove() {
    MoveHistoryEntry moveEntry = moveHistory.back();
    Move move = moveEntry.move;
    moveHistory.pop_back();

    int32_t origin = move.getOrigin();
    int32_t destination = move.getDestination();
    int32_t origin64 = mailbox[origin];
    int32_t destination64 = mailbox[destination];
    int32_t pieceType = pieces[destination];
    int32_t capturedPieceType = moveEntry.capturedPiece;

    // Mache den Spielzustand rückgängig
    ply--;
    side = side ^ COLOR_MASK;
    fiftyMoveRule = moveEntry.fiftyMoveRule;
    enPassantSquare = moveEntry.enPassantSquare;
    castlingPermission = moveEntry.castlingPermission;

    int32_t enPassantCaptureSq = enPassantSquare + (side == WHITE ? SOUTH : NORTH);

    // Spezialfall: Bauernumwandlung
    if(move.isPromotion()) {
        int32_t promotedPieceType = EMPTY;
        if(move.isPromotionQueen())
            promotedPieceType = QUEEN;
        else if(move.isPromotionRook())
            promotedPieceType = ROOK;
        else if(move.isPromotionBishop())
            promotedPieceType = BISHOP;
        else if(move.isPromotionKnight())
            promotedPieceType = KNIGHT;
        else
            ASSERT(false);
        
        pieceType = side | PAWN;

        // Entferne die neue Figur, die allgemeinen Bitboards müssen nicht angepasst werden
        pieceList[side | promotedPieceType].remove(destination);
        pieceBitboard[side | promotedPieceType].clearBit(destination64);

        // Füge den Bauern hinzu
        pieces[destination] = side | PAWN;
        pieceList[side | PAWN].push_back(destination);
        pieceBitboard[side | PAWN].setBit(destination64);
    }

    // Mache den Zug rückgängig
    pieces[origin] = pieceType;
    pieces[destination] = EMPTY;
    pieceList[pieceType].remove(destination);
    pieceList[pieceType].push_back(origin);
    pieceBitboard[pieceType].clearBit(destination64);
    pieceBitboard[pieceType].setBit(origin64);
    allPiecesBitboard.clearBit(destination64);
    allPiecesBitboard.setBit(origin64);
    if(side == WHITE) {
        whitePiecesBitboard.clearBit(destination64);
        whitePiecesBitboard.setBit(origin64);
    } else {
        blackPiecesBitboard.clearBit(destination64);
        blackPiecesBitboard.setBit(origin64);
    }

    // Spezialfall: Schlagen
    if(capturedPieceType != EMPTY && !move.isEnPassant()) {
        pieces[destination] = capturedPieceType;
        pieceList[capturedPieceType].push_back(destination);
        pieceBitboard[capturedPieceType].setBit(destination64);
        allPiecesBitboard.setBit(destination64);
        if(side == WHITE)
            blackPiecesBitboard.setBit(destination64);
        else
            whitePiecesBitboard.setBit(destination64);
    }

    // Spezialfall: Rochade
    if(move.isCastle()) {
        if(move.isKingsideCastle()) {
            // Rochade auf Königsseite
            ASSERT(TYPEOF(pieces[origin + 1]) == ROOK);
            ASSERT(pieces[origin + 3] == EMPTY);
            pieces[origin + 3] = side | ROOK;
            pieces[origin + 1] = EMPTY;
            pieceList[side | ROOK].remove(origin + 1);
            pieceList[side | ROOK].push_back(origin + 3);
            pieceBitboard[side | ROOK].clearBit(origin64 + 1);
            pieceBitboard[side | ROOK].setBit(origin64 + 3);
            allPiecesBitboard.clearBit(origin64 + 1);
            allPiecesBitboard.setBit(origin64 + 3);
            if(side == WHITE) {
                whitePiecesBitboard.clearBit(origin64 + 1);
                whitePiecesBitboard.setBit(origin64 + 3);
            } else {
                blackPiecesBitboard.clearBit(origin64 + 1);
                blackPiecesBitboard.setBit(origin64 + 3);
            }
        } else {
            // Rochade auf Damenseite
            ASSERT(TYPEOF(pieces[origin - 1]) == ROOK);
            ASSERT(pieces[origin - 4] == EMPTY);
            pieces[origin - 4] = side | ROOK;
            pieces[origin - 1] = EMPTY;
            pieceList[side | ROOK].remove(origin - 1);
            pieceList[side | ROOK].push_back(origin - 4);
            pieceBitboard[side | ROOK].clearBit(origin64 - 1);
            pieceBitboard[side | ROOK].setBit(origin64 - 4);
            allPiecesBitboard.clearBit(origin64 - 1);
            allPiecesBitboard.setBit(origin64 - 4);
            if(side == WHITE) {
                whitePiecesBitboard.clearBit(origin64 - 1);
                whitePiecesBitboard.setBit(origin64 - 4);
            } else {
                blackPiecesBitboard.clearBit(origin64 - 1);
                blackPiecesBitboard.setBit(origin64 - 4);
            }
        }
    }

    // Spezialfall: En Passant
    if(move.isEnPassant()) {
        ASSERT(enPassantSquare != NO_SQ);
        ASSERT(pieces[enPassantCaptureSq] == EMPTY);
        ASSERT(TYPEOF(capturedPieceType) == PAWN);

        int32_t enPassantSquare64 = mailbox[enPassantCaptureSq];
        pieces[enPassantCaptureSq] = capturedPieceType;
        pieceList[capturedPieceType].push_back(enPassantCaptureSq);
        pieceBitboard[capturedPieceType].setBit(enPassantSquare64);
        allPiecesBitboard.setBit(enPassantSquare64);
        if(side == WHITE)
            blackPiecesBitboard.setBit(enPassantSquare64);
        else
            whitePiecesBitboard.setBit(enPassantSquare64);
    }
}

bool Board::squareAttacked(int32_t sq120, int32_t ownSide, Bitboard occupied) {
    int32_t sq64 = mailbox[sq120];
    int32_t otherSide = (ownSide == WHITE) ? BLACK : WHITE;

    // Diagonale Angriffe
    if(diagonalAttackBitboard(sq64, occupied) & (pieceBitboard[ownSide | BISHOP] | pieceBitboard[ownSide | QUEEN]))
        return true;

    // Waaagerechte Angriffe
    if(straightAttackBitboard(sq64, occupied) & (pieceBitboard[ownSide | ROOK] | pieceBitboard[ownSide | QUEEN]))
        return true;

    // Springer Angriffe
    if(knightAttackBitboard(sq64) & pieceBitboard[ownSide | KNIGHT])
        return true;
    
    // Bauer Angriffe
    if(pawnAttackBitboard(sq64, otherSide) & pieceBitboard[ownSide | PAWN])
        return true;
    
    // König Angriffe
    if(kingAttackBitboard(sq64) & pieceBitboard[ownSide | KING])
        return true;
    
    return false;
}

bool Board::squareAttacked(int32_t sq120, int32_t ownSide, Bitboard occupied, Bitboard& attackerRays) {
    return numSquareAttackers(sq120, ownSide, occupied, attackerRays) > 0;
}

int32_t Board::numSquareAttackers(int32_t sq120, int32_t ownSide, Bitboard occupied) {
    int32_t sq64 = mailbox[sq120];
    int32_t otherSide = (ownSide == WHITE) ? BLACK : WHITE;
    int32_t numAttackers = 0;

    // Diagonale Angriffe
    Bitboard diagonalAttackers = diagonalAttackBitboard(sq64, occupied) & (pieceBitboard[ownSide | BISHOP] | pieceBitboard[ownSide | QUEEN]);
    numAttackers += diagonalAttackers.getNumberOfSetBits();

    // Waaagerechte Angriffe
    Bitboard straightAttackers = straightAttackBitboard(sq64, occupied) & (pieceBitboard[ownSide | ROOK] | pieceBitboard[ownSide | QUEEN]);
    numAttackers += straightAttackers.getNumberOfSetBits();

    // Springer Angriffe
    Bitboard knightAttackers = knightAttackBitboard(sq64) & pieceBitboard[ownSide | KNIGHT];
    numAttackers += knightAttackers.getNumberOfSetBits();

    // Bauer Angriffe
    Bitboard pawnAttackers = pawnAttackBitboard(sq64, otherSide) & pieceBitboard[ownSide | PAWN];
    numAttackers += pawnAttackers.getNumberOfSetBits();

    // König Angriffe
    Bitboard kingAttackers = kingAttackBitboard(sq64) & pieceBitboard[ownSide | KING];
    numAttackers += kingAttackers.getNumberOfSetBits();

    return numAttackers;
}

int32_t Board::numSquareAttackers(int32_t sq120, int32_t ownSide, Bitboard occupied, Bitboard& attackerRays) {
    int32_t sq64 = mailbox[sq120];
    int32_t otherSide = (ownSide == WHITE) ? BLACK : WHITE;
    int32_t numAttackers = 0;

    // Diagonale Angriffe
    Bitboard diagonalAttackers = diagonalAttackBitboard(sq64, occupied) & (pieceBitboard[ownSide | BISHOP] | pieceBitboard[ownSide | QUEEN]);
    numAttackers += diagonalAttackers.getNumberOfSetBits();
    attackerRays |= diagonalAttackUntilBlocked(sq64, pieceBitboard[ownSide | BISHOP] | pieceBitboard[ownSide | QUEEN], occupied);

    // Waaagerechte Angriffe
    Bitboard straightAttackers = straightAttackBitboard(sq64, occupied) & (pieceBitboard[ownSide | ROOK] | pieceBitboard[ownSide | QUEEN]);
    numAttackers += straightAttackers.getNumberOfSetBits();
    attackerRays |= straightAttackUntilBlocked(sq64, pieceBitboard[ownSide | ROOK] | pieceBitboard[ownSide | QUEEN], occupied);

    // Springer Angriffe
    Bitboard knightAttackers = knightAttackBitboard(sq64) & pieceBitboard[ownSide | KNIGHT];
    numAttackers += knightAttackers.getNumberOfSetBits();
    attackerRays |= knightAttackers;

    // Bauer Angriffe
    Bitboard pawnAttackers = pawnAttackBitboard(sq64, otherSide) & pieceBitboard[ownSide | PAWN];
    numAttackers += pawnAttackers.getNumberOfSetBits();
    attackerRays |= pawnAttackers;

    // König Angriffe
    Bitboard kingAttackers = kingAttackBitboard(sq64) & pieceBitboard[ownSide | KING];
    numAttackers += kingAttackers.getNumberOfSetBits();
    attackerRays |= kingAttackers;

    return numAttackers;
}

Bitboard Board::generateAttackBitboard(int32_t side) {
    Bitboard attackBitboard;
    Bitboard piecesPlusOwnKing = allPiecesBitboard | pieceBitboard[side | KING];
    
    // Diagonale Angriffe
    for(int sq : pieceList[side | BISHOP]) {
        int sq64 = mailbox[sq];
        attackBitboard |= diagonalAttackBitboard(sq64, piecesPlusOwnKing);
    }

    for(int sq : pieceList[side | QUEEN]) {
        int sq64 = mailbox[sq];
        attackBitboard |= diagonalAttackBitboard(sq64, piecesPlusOwnKing);
    }

    // Waagerechte Angriffe
    for(int sq : pieceList[side | ROOK]) {
        int sq64 = mailbox[sq];
        attackBitboard |= straightAttackBitboard(sq64, piecesPlusOwnKing);
    }

    for(int sq : pieceList[side | QUEEN]) {
        int sq64 = mailbox[sq];
        attackBitboard |= straightAttackBitboard(sq64, piecesPlusOwnKing);
    }

    // Springer Angriffe
    for(int sq : pieceList[side | KNIGHT]) {
        int sq64 = mailbox[sq];
        attackBitboard |= knightAttackBitboard(sq64);
    }

    // Bauer Angriffe
    for(int sq : pieceList[side | PAWN]) {
        int sq64 = mailbox[sq];
        attackBitboard |= pawnAttackBitboard(sq64, side);
    }

    // König Angriffe
    for(int sq : pieceList[side | KING]) {
        int sq64 = mailbox[sq];
        attackBitboard |= kingAttackBitboard(sq64);
    }

    return attackBitboard;
}

void Board::generatePinnedPiecesBitboards(int32_t side, Bitboard& pinnedPiecesBitboard,
                                          int32_t* pinnedPiecesDirection) {

    int32_t kingSquare = pieceList[side | KING].front();
    int32_t kingSquare64 = mailbox[kingSquare];
    int32_t otherSide = side ^ COLOR_MASK;
    Bitboard enemyPiecesPlusKing;
    if(side == WHITE)
        enemyPiecesPlusKing = blackPiecesBitboard | pieceBitboard[BLACK | KING];
    else
        enemyPiecesPlusKing = whitePiecesBitboard | pieceBitboard[WHITE | KING];

    Bitboard ownPieces = side == WHITE ? whitePiecesBitboard : blackPiecesBitboard;

    // Diagonale Angriffe
    int diagonalPins[4];
    int diagonalPinDirections[4];

    int32_t numDiagonalPins = getDiagonallyPinnedToSquare(kingSquare64,
                                ownPieces,
                                pieceBitboard[otherSide | QUEEN] | pieceBitboard[otherSide | BISHOP],
                                enemyPiecesPlusKing,
                                diagonalPins,
                                diagonalPinDirections);
    
    // Waaagerechte Angriffe
    int straightPins[4];
    int straightPinDirections[4];

    int32_t numStraightPins = getStraightPinnedToSquare(kingSquare64,
                              ownPieces,
                              pieceBitboard[otherSide | QUEEN] | pieceBitboard[otherSide | ROOK],
                              enemyPiecesPlusKing,
                              straightPins,
                              straightPinDirections);
    
    // Pins zusammenfassen
    for(int i = 0; i < numDiagonalPins; i++) {
        pinnedPiecesBitboard.setBit(diagonalPins[i]);
        pinnedPiecesDirection[diagonalPins[i]] = diagonalPinDirections[i];
    }

    for(int i = 0; i < numStraightPins; i++) {
        pinnedPiecesBitboard.setBit(straightPins[i]);
        pinnedPiecesDirection[straightPins[i]] = straightPinDirections[i];
    }
}

std::vector<Move> Board::generatePseudoLegalMoves() {
    std::vector<Move> moves;
    moves.reserve(256);

    if(side == WHITE) {
        Movegen::generatePseudoLegalWhitePawnMoves(moves, *this);
        Movegen::generatePseudoLegalWhiteKnightMoves(moves, *this);
        Movegen::generatePseudoLegalWhiteBishopMoves(moves, *this);
        Movegen::generatePseudoLegalWhiteRookMoves(moves, *this);
        Movegen::generatePseudoLegalWhiteQueenMoves(moves, *this);
        Movegen::generatePseudoLegalWhiteKingMoves(moves, *this);
    } else {
        Movegen::generatePseudoLegalBlackPawnMoves(moves, *this);
        Movegen::generatePseudoLegalBlackKnightMoves(moves, *this);
        Movegen::generatePseudoLegalBlackBishopMoves(moves, *this);
        Movegen::generatePseudoLegalBlackRookMoves(moves, *this);
        Movegen::generatePseudoLegalBlackQueenMoves(moves, *this);
        Movegen::generatePseudoLegalBlackKingMoves(moves, *this);
    }

    return moves;
}

std::vector<Move> Board::generateLegalMoves() {
    std::vector<Move> legalMoves;
    legalMoves.reserve(256);

    if(side == WHITE) {
        Bitboard attackedSquares = generateAttackBitboard(BLACK);

        Bitboard attackingRays;
        int32_t numAttackers = numSquareAttackers(pieceList[WHITE_KING].front(), BLACK, allPiecesBitboard | pieceBitboard[BLACK_KING], attackingRays);

        Bitboard pinnedPieces;
        int pinnedDirections[64];

        generatePinnedPiecesBitboards(WHITE, pinnedPieces, pinnedDirections);

        Movegen::generateWhitePawnMoves(legalMoves, *this, numAttackers, attackingRays, pinnedPieces, pinnedDirections);
        Movegen::generateWhiteKnightMoves(legalMoves, *this, numAttackers, attackingRays, pinnedPieces);
        Movegen::generateWhiteBishopMoves(legalMoves, *this, numAttackers, attackingRays, pinnedPieces, pinnedDirections);
        Movegen::generateWhiteRookMoves(legalMoves, *this, numAttackers, attackingRays, pinnedPieces, pinnedDirections);
        Movegen::generateWhiteQueenMoves(legalMoves, *this, numAttackers, attackingRays, pinnedPieces, pinnedDirections);
        Movegen::generateWhiteKingMoves(legalMoves, *this, attackedSquares);
    } else {
        Bitboard attackedSquares = generateAttackBitboard(WHITE);

        Bitboard attackingRays;
        int32_t numAttackers = numSquareAttackers(pieceList[BLACK_KING].front(), WHITE, allPiecesBitboard | pieceBitboard[WHITE_KING], attackingRays);

        Bitboard pinnedPieces;
        int pinnedDirections[64];

        generatePinnedPiecesBitboards(BLACK, pinnedPieces, pinnedDirections);

        Movegen::generateBlackPawnMoves(legalMoves, *this, numAttackers, attackingRays, pinnedPieces, pinnedDirections);
        Movegen::generateBlackKnightMoves(legalMoves, *this, numAttackers, attackingRays, pinnedPieces);
        Movegen::generateBlackBishopMoves(legalMoves, *this, numAttackers, attackingRays, pinnedPieces, pinnedDirections);
        Movegen::generateBlackRookMoves(legalMoves, *this, numAttackers, attackingRays, pinnedPieces, pinnedDirections);
        Movegen::generateBlackQueenMoves(legalMoves, *this, numAttackers, attackingRays, pinnedPieces, pinnedDirections);
        Movegen::generateBlackKingMoves(legalMoves, *this, attackedSquares);
    }

    return legalMoves;
}