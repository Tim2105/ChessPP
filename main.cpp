#include <iostream>
#include "Board.h"
#include <chrono>
#include "SearchTree.h"
#include <iomanip>
#include "EvaluationDefinitions.h"


void perft(Board& board, int depth, int& count) {
    if(depth == 1) {
        count += board.generateLegalMoves().size();
        return;
    }

    for(Move m : board.generateLegalMoves()) {
        board.makeMove(m);
        perft(board, depth - 1, count);
        board.undoMove();
    }
}

Move getUserMove(Board& board) {
    while(true) {
        std::string move;
        std::cout << "Enter move: ";
        std::cin >> move;

        for(Move m : board.generateLegalMoves()) {
            if(move == m.toString()) {
                return m;
            }
        }

        std::cout << "Invalid move" << std::endl;
    }
}

int main() {

    Board board("rnbq1rk1/2p2ppp/p2bpn2/1p1p4/3P1BQN/3BP3/PPP2PPP/RN3RK1 w - - 0 1");
    SearchTree st(board);
    BoardEvaluator evaluator(board);

    // while(board.generateLegalMoves().size() != 0 && !evaluator.isDraw()) {  
    //     board.makeMove(getUserMove(board));

    //     if(board.generateLegalMoves().size() == 0)
    //         break;

    //     int16_t score = st.search(4000);
    //     Move m = st.getPrincipalVariation()[0];
    //     std::cout << "Playing " << m << " Eval " << score << std::endl;
    //     board.makeMove(m);
    // }

    st.search(50000);

    return 0;
}