#ifndef BOARD_H
#define BOARD_H

#include <stdint.h>
#include <vector>
#include <list>
#include "Move.h"
#include "Definitions.h"
#include <stdio.h>
#include <string>
#include "Bitboard.h"
#include "Movegen.h"

/**
 * @brief Enthält alle notwendigen Informationen um einen Zug rückgängig zu machen.
 */
class MoveHistoryEntry {
    friend class Board;

    private:
        /**
         * @brief Der Zug der rückgängig gemacht werden soll.
         */
        Move move;

        /**
         * @brief Speichert den Typ der geschlagenen Figur.
         */
        int32_t capturedPiece;

        /**
         * @brief Speichert alle möglichen Rochaden vor diesem Zug.
         */
        int32_t castlingPermission;

        /**
         * @brief Speichert die Position eines möglichen En Passant Zuges vor diesem Zug(wenn möglich).
         */
        int32_t enPassantSquare;

        /**
         * @brief Der 50-Zug Counter vor diesem Zug.
         */
        int32_t fiftyMoveRule;

        /**
         * @brief Speichert den Hashwert vor diesem Zug.
         */
        uint64_t hashValue;
    
    public:
        /**
         * @brief Erstellt einen neuen MoveHistoryEntry.
         * @param move Der Zug der rückgängig gemacht werden soll.
         * @param capturedPiece Speichert den Typ der geschlagenen Figur.
         * @param castlePermission Speichert alle möglichen Rochaden vor diesem Zug.
         * @param enPassantSquare Speichert die Position eines möglichen En Passant Zuges vor diesem Zug(wenn möglich).
         * @param fiftyMoveRule Der 50-Zug Counter vor diesem Zug.
         * @param hashValue Speichert den Hashwert vor diesem Zug.
         */
        MoveHistoryEntry(Move move, int32_t capturedPiece, int32_t castlePermission, int32_t enPassantSquare, int32_t fiftyMoveRule, uint64_t hashValue) {
            this->move = move;
            this->capturedPiece = capturedPiece;
            this->castlingPermission = castlePermission;
            this->enPassantSquare = enPassantSquare;
            this->fiftyMoveRule = fiftyMoveRule;
            this->hashValue = hashValue;
        }

        /**
         * @brief Erstellt einen neuen MoveHistoryEntry.
         * @param move Der Zug der rückgängig gemacht werden soll.
         */
        MoveHistoryEntry(Move move) {
            this->move = move;
            this->capturedPiece = EMPTY;
            this->castlingPermission = 0;
            this->enPassantSquare = 0;
            this->fiftyMoveRule = 0;
            this->hashValue = 0;
        }
};

/**
 * @brief Stellt ein Schachbrett dar.
 * Die Klasse Board stellt ein Schachbrett dar und enthält Methoden zur Zuggeneration.
 * Dieser Teil des Programms ist sehr Performancekritisch und folgt daher nicht strikt den Regeln der Objektorientierten Programmierung.
 */
class Board {
    friend class Movegen;

    private:
         /**
          * @brief Stellt das Schachbrett in 10x12 Notation dar.
          * https://www.chessprogramming.org/10x12_Board
          */
        int32_t pieces[120] = {
            EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,      EMPTY, EMPTY,
            EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,      EMPTY, EMPTY,
            EMPTY, WHITE_ROOK, WHITE_KNIGHT, WHITE_BISHOP, WHITE_QUEEN, WHITE_KING, WHITE_BISHOP, WHITE_KNIGHT, WHITE_ROOK, EMPTY,
            EMPTY, WHITE_PAWN,   WHITE_PAWN,   WHITE_PAWN,  WHITE_PAWN, WHITE_PAWN,   WHITE_PAWN,   WHITE_PAWN, WHITE_PAWN, EMPTY,
            EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,      EMPTY, EMPTY,
            EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,      EMPTY, EMPTY,
            EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,      EMPTY, EMPTY,
            EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,      EMPTY, EMPTY,
            EMPTY, BLACK_PAWN,   BLACK_PAWN,   BLACK_PAWN,  BLACK_PAWN, BLACK_PAWN,   BLACK_PAWN,   BLACK_PAWN, BLACK_PAWN, EMPTY,
            EMPTY, BLACK_ROOK, BLACK_KNIGHT, BLACK_BISHOP, BLACK_QUEEN, BLACK_KING, BLACK_BISHOP, BLACK_KNIGHT, BLACK_ROOK, EMPTY,
            EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,      EMPTY, EMPTY,
            EMPTY,      EMPTY,        EMPTY,        EMPTY,       EMPTY,      EMPTY,        EMPTY,        EMPTY,      EMPTY, EMPTY
        };

        /**
         * @brief Enthält eine Liste aller Figuren für jeden Figurentyp auf dem Schachbrett.
         * Speichert den Index der Position.
         */
        std::list<int32_t> pieceList[15] = {
            {},
            {A2, B2, C2, D2, E2, F2, G2, H2},
            {B1, G1},
            {C1, F1},
            {A1, H1},
            {D1},
            {E1},
            {},
            {},
            {A7, B7, C7, D7, E7, F7, G7, H7},
            {B8, G8}, 
            {C8, F8},
            {A8, H8},
            {D8},
            {E8}
        };

        /**
         * @brief Speichert die Farbe, die am Zug ist.
         */
        int32_t side;

        /**
         * @brief Speichert den Index des Feldes, auf dem ein Bauer En Passant geschlagen werden kann(wenn vorhanden).
         */
        int32_t enPassantSquare;

        /**
         * @brief Speichert die Anzahl der Halbzüge, die seit dem letzten Bauer- oder Schlagzug vergangen sind.
         */
        int32_t fiftyMoveRule;

        /**
         * @brief Speichert alle noch offenen Rochaden.
         */
        int32_t castlingPermission;

        /**
         * @brief Speichert die Anzahl der Halbzüge, die seit dem Anfang des Spiels vergangen sind.
         */
        int32_t ply;

        /**
         * @brief Der Zobristhash des Schachbretts.
         * https://www.chessprogramming.org/Zobrist_Hashing
         */
        uint64_t hashValue;

        /**
         * @brief Speichert alle von Figuren(nicht Könige) belegten Felder.
         */
        Bitboard allPiecesBitboard;

        /**
         * @brief Speichert alle Felder, auf denen sich weiße Figuren(außer König) befinden.
         */
        Bitboard whitePiecesBitboard;

        /**
         * @brief Speichert alle Felder, auf denen sich schwarze Figuren(außer König) befinden.
         */
        Bitboard blackPiecesBitboard;

        /**
         * @brief Speichert alle Felder, auf denen sich Figuren befinden.
         */
        Bitboard pieceBitboard[15];

        /**
         * @brief Speichert alle gespielten Züge und notwendige Informationen um diesen effizient rückgängig zu machen.
         */
        std::vector<MoveHistoryEntry> moveHistory;

        /**
         * @brief Array zur Konvertierung der 10x12 Notation in 8x8 Notation.
         * Invalide Felder werden als NO_SQ markiert.
         */
        int32_t mailbox[120];

        /**
         * @brief Array zur Konvertierung der 8x8 Notation in 10x12 Notation.
         */
        int32_t mailbox64[64];

        /**
         * @brief Initialisiert die Mailbox-Arrays
         */
        void initMailbox();

        /**
         * @brief Generiert ein Bitboard, das alle besetzten Felder enthält(König ausgeschlossen).
         */
        void generateBitboards();

        /**
         * @brief Generiert ein Bitboard, das alle Felder enthält, auf denen sich gefesselte Figuren befinden.
         * Außerdem wird die Richtung, aus der die Figuren gefesselt sind, in einem 64 int großen Array gespeichert(in 120er Notation).
         * 
         * @param side Die Seite, für die gefesselte Figuren gefunden werden sollen.
         * @param pinnedPiecesBitboard Das Bitboard, das alle gefesselten Figuren enthält.
         * @param pinnedPiecesDirection Das Array, in dem die Richtung, aus der die Figuren gefesselt sind, gespeichert wird(muss mind. 8 groß sein).
         */
        void generatePinnedPiecesBitboards(int32_t side, Bitboard& pinnedPiecesBitboard, int32_t* pinnedPiecesDirection);

        /**
         * @brief Überprüft, ob ein Zug legal ist.
         */
        bool isLegal(Move move);

    public:
        /**
         * @brief Erstellt ein neues Schachbrett.
         */
        Board();

        /**
         * @brief Erstellt ausgehend von einem FEN-String ein neues Schachbrett.
         * @param fen Die FEN-Notation des Schachbretts.
         */
        Board(std::string fen);

        virtual ~Board();

        /**
         * @brief Generiert alle Pseudo-Legalen Züge.
         * Pseudo-Legale Züge sind Züge, die auf dem Schachbrett möglich sind, aber eventuell den eigenen König im Schach lassen.
         */
        std::vector<Move> generatePseudoLegalMoves();

        /**
         * @brief Generiert alle Legalen Züge und gibt sie nach ihrer Stärke bewertet zurück.
         * Legale Züge sind Züge, die auf dem Schachbrett möglich sind und den eigenen König nicht im Schach lassen.
         */
        std::vector<Move> generateLegalMoves();

        /**
         * @brief Führt einen Zug aus.
         */
        void makeMove(Move move);

        /**
         * @brief Macht den letzten gespielten Zug rückgängig.
         */
        void undoMove();

        /**
         * @brief Überprüft bei einem anzugebenden Belegbitboard, ob ein Feld von einer bestimmten Seite angegriffen wird.
         * 
         * @param square Das Feld, das überprüft werden soll(in 120er Notation).
         */
        bool squareAttacked(int32_t square, int32_t side, Bitboard occupied);

        /**
         * @brief Überprüft bei einem anzugebenden Belegbitboard, ob ein Feld von einer bestimmten Seite angegriffen wird.
         * 
         * @param square Das Feld, das überprüft werden soll(in 120er Notation).
         * @param attackingRays Gibt dein Bitboard mit allen Angreifern zurück. Bei laufenden Figuren sind außerdem sind außerdem die Verbindungsfelder mit enthalten.
         */
        bool squareAttacked(int32_t square, int32_t side, Bitboard occupied, Bitboard& attackingRays);

        /**
         * @brief Gibt die Anzahl der angreifenden Figuren eines Feldes zurück.
         * 
         * @param square Das Feld, das überprüft werden soll(in 120er Notation).
         */
        int32_t numSquareAttackers(int32_t square, int32_t side, Bitboard occupied);

        /**
         * @brief Gibt die Anzahl der angreifenden Figuren eines Feldes zurück.
         * 
         * @param square Das Feld, das überprüft werden soll(in 120er Notation).
         * @param attackingRays Gibt dein Bitboard mit allen Angreifern zurück. Bei laufenden Figuren sind außerdem sind außerdem die Verbindungsfelder mit enthalten.
         */
        int32_t numSquareAttackers(int32_t square, int32_t side, Bitboard occupied, Bitboard& attackingRays);
};

#endif