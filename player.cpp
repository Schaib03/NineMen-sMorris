#include "player.h"
#include <QDebug>

Move HumanPlayer::getNextMove(Game g)
{
    // Take the user's input based on the current state
    short n;
    Move move;
    std::cout << "\nTarget i : ";
    std::cin >> n;
    std::cout << "You chose :" << n << "\n";
    move.set_dest_i((short)n);
    std::cout << "\nTarget j : ";
    std::cin >> n;
    std::cout << "You chose :" << n << "\n";
    move.set_dest_j((short)n);
    std::cout << "\nSource i (3 if not applicable): ";
    std::cin >> n;
    std::cout << "You chose :" << n << "\n";
    move.set_source_i((short)n);
    std::cout << "\nSource j (3 if not applicable): ";
    std::cin >> n;
    std::cout << "You chose :" << n << "\n";
    move.set_source_j((short)n);
    std::cout << "\nRemove i (3 if not applicable): ";
    std::cin >> n;
    std::cout << "You chose :" << n << "\n";
    move.set_remove_i((short)n);
    std::cout << "\nRemove j (3 if not applicable): ";
    std::cin >> n;
    std::cout << "You chose :" << n << "\n";
    move.set_remove_j((short)n);
    move.setColor(g.getCurrentState().getTurn());
    return move;
}

AIPlayer::AIPlayer(int d)
{
    diff = d;
}

Move AIPlayer::getNextMove(Game g)
{
    State current = g.getCurrentState();
    qDebug() << diff;
    if (diff == 3)
    {
        qDebug() << "diff is 3";
    };
    State next = current.alphaBeta(diff, current.getTurn());
    next.display();
    return current.getMove(next);
}

void AIPlayer::setDifficulty(int d)
{
    diff = d;
}
