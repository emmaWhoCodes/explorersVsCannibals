#include <iostream>
#include <vector>
#include <list>

using namespace std;

// Pre: Takes in a reference list of vectors that are of type int, "printMoves", that has
//      all of the moves stored in it.
//
// Post: Prints out the possible moves to the console. The moves are printed to where we see
//       the movement of the boat going from the left to the right hand side. The cannibals and
//       explorers are denoted as "C" or "E" respectively.
void printLine(list<vector<int> > &printMoves) {
    vector<int> printHelper;
    std::list<vector<int> >::iterator current;
    int level = 0;
    cout << endl;
    bool boat = false;
    for (current = printMoves.begin(); current != printMoves.end(); current++) {
        printHelper = *current;
        if (boat) {
            cout << '\t' << '\t' << '\t' << "\\";
            for (int i = 0; i < printHelper[0]; i++) {
                cout << "E";
            }
            for (int i = 0; i < printHelper[1]; i++) {
                cout << "C";
            }
            cout << "/" ;
        } else {
            for (int i = 0; i < printHelper[0]; i++) {
                cout << "E";
            }
            for (int i = 0; i < printHelper[1]; i++) {
                cout << "C";
            }
            for (int i = 0; i < 6 - (printHelper[0] + printHelper[1]); i++) {
                cout << "-";
            }
            if (level % 2 == 0) {
                cout << " \\__/" << '\t' << '\t' << '\t' << "  ";
            } else {
                cout << '\t' << '\t' << '\t' << " \\__/ " ;
            }
            level++;
            for (int i = 0; i < 3 - printHelper[0]; i++) {
                cout << "E";
            }
            for (int i = 0; i < 3 - printHelper[1]; i++) {
                cout << "C";
            }
            for (int i = 0; i < printHelper[0] + printHelper[1]; i++) {
                cout << "-";
            }
        }
        cout << endl;
        boat = !boat;
    }
}


// Parameters:
    // currentState - current state of the cannibals and explorers
    // explorersOnBoat - possibility of explorers
    // cannibalsOnBoat - possibilites of cannibals
bool safeTrip(vector<int> currentState, int explorersOnBoat, int cannibalsOnBoat) {

   // Can only handle 2 cannibals or explorers per trip. Also boat cannot be empty
    if (explorersOnBoat + cannibalsOnBoat > 2 || explorersOnBoat + cannibalsOnBoat == 0 ) {
        return false;
    }
    
    int explorersOnLeft, cannibalsOnLeft;
    int explorersOnRight, cannibalsOnRight;

    if (currentState[2] == 1) { // leaving the left side

        explorersOnLeft = currentState[0] - explorersOnBoat; // - boat because they left this side
        cannibalsOnLeft = currentState[1] - cannibalsOnBoat;
        explorersOnRight = 3 - currentState[0] + explorersOnBoat;  // + boat because it came over
        cannibalsOnRight = 3 - currentState[1] + cannibalsOnBoat;

        // check if left side has enough cannibals and explorers for boat
        if (explorersOnLeft < 0 || cannibalsOnLeft < 0) {
            return false;
        }

    } else { // Leaving right side.

        explorersOnLeft = currentState[0] + explorersOnBoat; // + boat because it is coming to this side
        cannibalsOnLeft = currentState[1] + cannibalsOnBoat;
        explorersOnRight = 3 - currentState[0] - explorersOnBoat; // - boat because it left this side
        cannibalsOnRight = 3 - currentState[1] - cannibalsOnBoat;

        // check if right side has enough cannibals and explorers for boat.
        if (explorersOnRight < 0 || cannibalsOnRight < 0) {
            return false;
        }
    }

    // if cannibals outnumber explorers on left.
    if (explorersOnLeft < cannibalsOnLeft) {
        if (explorersOnLeft != 0) {
            return false;
        }
    }
    
    // if cannibals outnumber explorers on right
    if (explorersOnRight < cannibalsOnRight) {
        if (explorersOnRight != 0) {
            return false;
        }
    }

    // it is a valid move
    return true;
}


// Parameters:
    // Previous move made. Starts at (3, 3, 1). The 2nd index, 1 indicates boat is on left side.
    // it will be 0 for the right side.
void findWays(vector<int> prevMove, vector<int> parent, list<vector<int> > printMoves) {
    if (prevMove[0] == 0 && prevMove[1] == 0 && prevMove[2] == 0) {
        printLine(printMoves);
        cout << endl << endl << endl << endl;
    } else {
        vector<int> nextMove;
        vector<int> boat;
        
        for (int explorersOnBoat = 0; explorersOnBoat <= 2; explorersOnBoat++) {
            for (int cannibalsOnBoat = 0; cannibalsOnBoat <= 2; cannibalsOnBoat++) {
                if (safeTrip(prevMove, explorersOnBoat, cannibalsOnBoat)) {
                    if (prevMove[2] == 1) {
                        nextMove = {prevMove[0] - explorersOnBoat, prevMove[1] - cannibalsOnBoat, 0};
                    } else {
                        nextMove = {prevMove[0] + explorersOnBoat, prevMove[1] + cannibalsOnBoat, 1};
                    }
                    boat = {explorersOnBoat, cannibalsOnBoat};

                    // Prevents the game from starting all over again at <3,3,1> position
                    if (nextMove[0] != 3 || nextMove[1] != 3 || nextMove[2] != 1) {

                        // prevents from making a move that will cause it to be the same as before.
                        if (nextMove[0] != parent[0] || nextMove[1] != parent[1]) {
                            printMoves.push_back(boat);
                            printMoves.push_back(nextMove);
                            findWays(nextMove, prevMove, printMoves);
                            printMoves.pop_back();
                            printMoves.pop_back();
                        }
                    }
                }
            }
        }
    }
}



int main() {
    list<vector<int> > recordMoves;
    vector<int> start = {3, 3, 1};
    recordMoves.push_back(start);
    findWays(start, start, recordMoves);
    return 0;
}
