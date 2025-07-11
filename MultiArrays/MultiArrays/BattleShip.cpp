// Battleship.cpp -- Implements Battleship game reading a board from file and processing user shots
// CSIS 111-<B03> 
// Sources: None

// Include statements
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Global declarations: Constants and type definitions only -- no variables
const int SIZE = 25;
char ocean[SIZE][SIZE];

// Function prototypes
bool ReadBoard(const string& filename);
void Fire(int x, int y);
bool FleetSunk();
void PrintBoard();

int main()
{
    // In cout statement below SUBSTITUTE your name and lab number
    cout << "Ezekiel Clifton -- Lab #7" << endl << endl;

    // Program logic
    if (!ReadBoard("board.txt")) {
        return 1;
    }

    cout << "Welcome to Battleship!\n";
    cout << "Enter coordinates to fire in range 1 to 25 for both X and Y.\n";

    while (!FleetSunk()) {
        int x, y;
        cout << "Enter coordinates to fire (X Y): ";
        cin >> x >> y;

        // Convert from 1-based input to 0-based array indices
        x = x - 1;
        y = y - 1;

        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
            cout << "Invalid coordinates. Please enter values between 1 and 25." << endl;
            continue;
        }

        Fire(x, y);
        PrintBoard();  // Optionally print board after each shot
    }

    cout << "The fleet was destroyed!" << endl;
    PrintBoard();

    // Closing program statements
    system("pause");
    return 0;
}

// Function definitions

bool ReadBoard(const string& filename) {
    ifstream fin(filename);
    if (!fin) {
        cerr << "Error opening file: " << filename << endl;
        return false;
    }

    string line;
    for (int i = 0; i < SIZE; i++) {
        if (!getline(fin, line) || line.length() < SIZE) {
            cerr << "Invalid board file format at line " << i + 1 << endl;
            return false;
        }
        for (int j = 0; j < SIZE; j++) {
            char c = line[j];
            if (c == '~' || c == '#' || c == 'H' || c == 'M') {
                ocean[i][j] = c;
            }
            else {
                cerr << "Invalid character '" << c << "' in board at line " << i + 1 << ", column " << j + 1 << endl;
                return false;
            }
        }
    }
    return true;
}

void Fire(int x, int y) {
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) {
        cout << "Coordinates out of bounds!" << endl;
        return;
    }

    char& pos = ocean[y][x]; // Note: y is row, x is column

    if (pos == '#') {
        pos = 'H';
        cout << "HIT" << endl;
    }
    else if (pos == 'H') {
        cout << "HIT AGAIN" << endl;
    }
    else if (pos == '~') {
        pos = 'M';  // Mark miss
        cout << "MISS" << endl;
    }
    else if (pos == 'M') {
        cout << "MISS AGAIN" << endl;
    }
}

bool FleetSunk() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (ocean[i][j] == '#') {
                return false;  // Ship parts remain
            }
        }
    }
    return true;
}

void PrintBoard() {
    // Print column headers (1 to 25)
    cout << "   ";
    for (int j = 0; j < SIZE; j++) {
        cout << (j + 1 < 10 ? " " : "") << j + 1 << " ";
    }
    cout << "\n";

    for (int i = 0; i < SIZE; i++) {
        // Print row header (1 to 25)
        cout << (i + 1 < 10 ? " " : "") << i + 1 << " ";

        for (int j = 0; j < SIZE; j++) {
            char c = ocean[i][j];
            if (c == '#') {
                // Hide ships that are not hit by printing water
                cout << " ~ ";
            }
            else {
                // Show water (~), hits (H), misses (M), normally
                cout << " " << c << " ";
            }
        }
        cout << endl;
    }
}