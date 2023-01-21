#ifndef BOARD_EVALUATOR_H
#define BOARD_EVALUATOR_H

#include "Board.h"
#include "HashTable.h"
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

/**
 * @brief Die Klasse BoardEvaluator ist für die statische Bewertung eines Spielfeldes zuständig.
 * Parameter können in den Dateien "EvaluationDefinitions.h" und "EvaluationDefinitions.cpp" angepasst werden.
 */
class BoardEvaluator {

    private:
        // Die Bewertung von Bauernstrukturen ist sehr aufwendig,
        // weshalb berechnete Bewertungen von Bauernstrukturen in einer Hash-Tabelle gespeichert werden,
        // um sie bei der nächsten Bewertung(bei gleicher Bauernstruktur) wieder zu verwenden.
        // Weil Bauernstrukturen sich nicht zu häufig ändern, bekommt man hier eine hohe Trefferquote(Durchschnitt ca. 75%).
        HashTable<PawnBitboards, Score, 512, 4> pawnStructureTable;

        /**
         * @brief Die Methode findDoublePawns findet alle Bauern, die sich auf derselben Linie befinden.
         */
        inline Bitboard findDoublePawns(const Bitboard& ownPawns, int32_t side);

        /**
         * @brief Die Methode findIsolatedPawns findet alle isolierten Bauern.
         * Isolierte Bauern sind Bauern, die keine befreundeten Bauern auf der Linie links oder rechts von ihnen haben.
         */
        inline Bitboard findIsolatedPawns(const Bitboard& ownPawns, int32_t side);

        /**
         * @brief Die Methode findPassedPawns findet alle Bauern, die nicht von gegnerischen Bauern abgefangen werden können.
         */
        inline Bitboard findPassedPawns(const Bitboard& ownPawns, const Bitboard& otherPawns, int32_t side);

        /**
         * @brief Die Methode findPawnChains findet alle Bauernketten.
         * Bauernketten sind Bauern, die andere Bauern schützen.
         */
        inline Bitboard findPawnChains(const Bitboard& ownPawns, int32_t side);

        /**
         * @brief Die Methode findConnectedPawns findet alle verbundenen Bauern.
         * Verbundene Bauern sind Bauern, die sich nebeneinander auf demselben Rang befinden.
         */
        inline Bitboard findConnectedPawns(const Bitboard& ownPawns);

        /**
         * @brief Die Methode evalMaterial bewertet die Materialstärke der beiden Spieler.
         */
        int32_t evalMaterial(const Board& b);

        /**
         * @brief Die Methode evalMobility bewertet die Mobilität der beiden Spieler.
         * Mobilität ist die Anzahl der Felder, die ein Spieler angreift und/oder verteidigt.
         */
        int32_t evalMobility(const Board& b);

        /**
         * @brief Die Methode evalMG_PSQT bewertet die Figurenpositionen der beiden Spieler
         * mit dem Midgame-PSQT-Array.
         */
        inline int32_t evalMG_PSQT(Board& b);

        /**
         * @brief Die Methode evalEG_PSQT bewertet die Figurenpositionen der beiden Spieler
         * mit dem Endgame-PSQT-Array.
         */
        inline int32_t evalEG_PSQT(Board& b);

        /**
         * @brief Versucht die Bewertung einer Bauernstruktur aus der Hash-Tabelle zu laden.
         * 
         * @param b Das aktuelle Spielfeld.
         * @param score Hier wird die Bewertung der Bauernstruktur(falls gefunden) gespeichert.
         * @return true, wenn die Bewertung gefunden wurde.
         * @return false, wenn die Bewertung nicht gefunden wurde.
         */
        bool probePawnStructure(const Board& b, Score& score);

        /**
         * @brief Speichert die Bewertung einer Bauernstruktur in der Hash-Tabelle.
         * 
         * @param b Das aktuelle Spielfeld.
         * @param score Die Bewertung der Bauernstruktur.
         */
        void storePawnStructure(const Board& b, const Score& score);

        /**
         * @brief Die Methode evalPawnStructure bewertet die Bauernstruktur der beiden Spieler.
         */
        Score evalPawnStructure(const Board& b, int32_t side);

        Score evalPawnStructure(Bitboard doublePawns, Bitboard isolatedPawns, Bitboard passedPawns, Bitboard pawnChains, Bitboard connectedPawns, int32_t side);
        inline Score evalDoublePawns(Bitboard doublePawns, int32_t side);
        inline Score evalIsolatedPawns(Bitboard isolatedPawns, int32_t side);
        inline Score evalPassedPawns(Bitboard passedPawns, int32_t side);
        inline Score evalPawnChains(Bitboard pawnChains, int32_t side);
        inline Score evalConnectedPawns(Bitboard connectedPawns, int32_t side);
        
        /**
         * @brief Die Methode evalMGKingSafety bewertet die Sicherheit des Königs der beiden Spieler im Midgame.
         */
        int32_t evalMGKingSafety(const Board& b);
        inline int32_t evalMGPawnShield(int32_t kingSquare, const Bitboard& ownPawns, const Bitboard& otherPawns, int32_t side);
        inline int32_t evalMGPawnStorm(int32_t otherKingSquare, const Bitboard& ownPawns, const Bitboard& otherPawns, int32_t side);
        inline int32_t evalMGKingMobility(const Board& b, int32_t side);

        /**
         * @brief Die Methode evalEGKingSafety bewertet die Sicherheit des Königs der beiden Spieler im Endgame.
         */
        int32_t evalEGKingSafety(const Board& b);
        inline int32_t evalEGKingMobility(const Board& b, int32_t side);

        /**
         * @brief Überprüft, ob das Spiel zwangsläufig ein Unentschieden ist.
         * Ein Spiel ist zwangsläufig ein Unentschieden, wenn kein Spieler Schachmatt gesetzt werden kann,
         * auch wenn beide Spieler kooperieren würden.
         * Andere Möglichkeiten für ein Unentschieden sind z.B. 50 Züge ohne Bauern- oder Schlagzug
         * oder dreimal dieselbe Stellung.
         */
        bool isDraw(Board& b);

    public:
        /**
         * @brief Führt eine statische Bewertung für das Midgame der
         * Spielpositon aus der Sicht des Spielers der am Zug ist durch.
         * 
         * @param b Das aktuelle Spielfeld.
         * @return Die Bewertung der Spielposition.
         * Je größer der Wert, desto besser ist die Spielposition für den Spieler der am Zug ist.
         * Je kleiner der Wert, desto besser ist die Spielposition für den Gegner des Spielers der am Zug ist.
         * Eine Bewertung von 0 bedeutet ein ausgeglichenes Spiel.
         */
        int32_t middlegameEvaluation(Board& b);

        /**
         * @brief Führt eine statische Bewertung für das Endgame der
         * Spielpositon aus der Sicht des Spielers der am Zug ist durch.
         * 
         * @param b Das aktuelle Spielfeld.
         * @return Die Bewertung der Spielposition.
         * Je größer der Wert, desto besser ist die Spielposition für den Spieler der am Zug ist.
         * Je kleiner der Wert, desto besser ist die Spielposition für den Gegner des Spielers der am Zug ist.
         * Eine Bewertung von 0 bedeutet ein ausgeglichenes Spiel.
         */
        int32_t endgameEvaluation(Board& b);

        /**
         * @brief Führt eine statische Bewertung der
         * Spielpositon aus der Sicht des Spielers der am Zug ist durch.
         * Die Bewertung ist eine Interpolation zwischen der Midgame- und der Endgame-Bewertung.
         * 
         * @param b Das aktuelle Spielfeld.
         * @return Die Bewertung der Spielposition.
         * Je größer der Wert, desto besser ist die Spielposition für den Spieler der am Zug ist.
         * Je kleiner der Wert, desto besser ist die Spielposition für den Gegner des Spielers der am Zug ist.
         * Eine Bewertung von 0 bedeutet ein ausgeglichenes Spiel.
         */
        int32_t evaluate(Board& b);
};

#endif