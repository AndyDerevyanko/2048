#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"

#include <climits>
#include <iostream>
using namespace std;

// Board class represents a 4x4 2048 game board
class board {
public:
    bool shouldPickRand =
        true;        // Flag to determine if a new random cell should be added
    int entry[4][4]; // The 4x4 board array

    // Check if a cell is empty (0)
    bool isempty(int x, int y) { return entry[x][y] == 0; }

    // Check if two cells have the same value
    bool issame(int x1, int y1, int x2, int y2) {
        return entry[x1][y1] == entry[x2][y2];
    }

    // Combine two cells (used when merging tiles)
    void combine(int x1, int y1, int x2, int y2) {
        entry[x2][y2] += entry[x1][y1]; // Merge value into target cell
        entry[x1][y1] = 0;              // Clear the source cell
    }

    // Shift a cell’s value to another location (used after merge)
    void shiftcell(int x1, int y1, int x2, int y2) {
        entry[x2][y2] = entry[x1][y1];
        entry[x1][y1] = 0;
    }

    // Shift the entire board in a given direction (w = up, a = left, s = down, d
    // = right)
    void shift(char direction) {
        switch (direction) {
        case 'w': // Shift up
            for (int x = 0; x < 4; x++) {
                for (int y = 3; y > 0; y--) {
                    if (!isempty(x, y) && isempty(x, y - 1)) {
                        entry[x][y - 1] = entry[x][y];
                        entry[x][y] = 0;
                    }
                }
            }
            break;

        case 'a': // Shift left
            for (int y = 0; y < 4; y++) {
                for (int x = 3; x > 0; x--) {
                    if (!isempty(x, y) && isempty(x - 1, y)) {
                        entry[x - 1][y] = entry[x][y];
                        entry[x][y] = 0;
                    }
                }
            }
            break;

        case 's': // Shift down
            for (int x = 0; x < 4; x++) {
                for (int y = 0; y < 3; y++) {
                    if (!isempty(x, y) && isempty(x, y + 1)) {
                        entry[x][y + 1] = entry[x][y];
                        entry[x][y] = 0;
                    }
                }
            }
            break;

        case 'd': // Shift right
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < 3; x++) {
                    if (!isempty(x, y) && isempty(x + 1, y)) {
                        entry[x + 1][y] = entry[x][y];
                        entry[x][y] = 0;
                    }
                }
            }
            break;

        default:
            throw invalid_argument{ "Invalid direction. Use 'w', 'a', 's', or 'd'." };
        }
    }

    // Move board up (shift + merge)
    void up() {
        shift('w');
        for (int x = 0; x < 4; x++) {
            for (int y = 0; y < 3; y++) {
                if (!isempty(x, y + 1)) {
                    if (!isempty(x, y) && issame(x, y + 1, x, y)) {
                        combine(x, y + 1, x, y);
                    }
                    else if (isempty(x, y)) {
                        shiftcell(x, y + 1, x, y);
                    }
                }
            }
            shift('w'); // Ensure all tiles are shifted fully after merging
        }
    }

    // Move board down
    void down() {
        shift('s');
        for (int x = 0; x < 4; x++) {
            for (int y = 3; y > 0; y--) {
                if (!isempty(x, y - 1)) {
                    if (!isempty(x, y) && issame(x, y - 1, x, y)) {
                        combine(x, y - 1, x, y);
                    }
                    else if (isempty(x, y)) {
                        shiftcell(x, y - 1, x, y);
                    }
                }
            }
            shift('s');
        }
    }

    // Move board left
    void left() {
        shift('a');
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 3; x++) {
                if (!isempty(x + 1, y)) {
                    if (!isempty(x, y) && issame(x + 1, y, x, y)) {
                        combine(x + 1, y, x, y);
                    }
                    else if (isempty(x, y)) {
                        shiftcell(x + 1, y, x, y);
                    }
                }
            }
            shift('a');
        }
    }

    // Move board right
    void right() {
        shift('d');
        for (int y = 0; y < 4; y++) {
            for (int x = 3; x > 0; x--) {
                if (!isempty(x - 1, y)) {
                    if (!isempty(x, y) && issame(x - 1, y, x, y)) {
                        combine(x - 1, y, x, y);
                    }
                    else if (isempty(x, y)) {
                        shiftcell(x - 1, y, x, y);
                    }
                }
            }
            shift('d');
        }
    }

    // Check if any moves are possible in any direction
    bool movetest() {
        board b;
        int values_same = 0;
        for (int m = 0; m < 4; m++) {
            for (int n = 0; n < 4; n++) {
                if (entry[m][n] == 0)
                    return false;              // Empty cell = move available
                b.entry[m][n] = entry[m][n]; // Copy board
            }
        }
        b.up();
        b.down();
        b.left();
        b.right();

        // Check if the board changed after any move
        for (int m = 0; m < 4; m++) {
            for (int n = 0; n < 4; n++) {
                if (b.entry[m][n] == entry[m][n])
                    values_same++;
            }
        }
        return values_same != 16; // If all same, no moves
    }

    // Check if a move is possible in a specific direction
    bool movetestdir(char direction) {
        board b;
        int values_same = 0;
        for (int m = 0; m < 4; m++) {
            for (int n = 0; n < 4; n++) {
                b.entry[m][n] = entry[m][n]; // Copy board
            }
        }

        switch (direction) {
        case 'w':
            b.up();
            break;
        case 's':
            b.down();
            break;
        case 'a':
            b.left();
            break;
        case 'd':
            b.right();
            break;
        default:
            throw invalid_argument{ "Invalid direction. Use 'w','a','s','d'." };
        }

        for (int m = 0; m < 4; m++) {
            for (int n = 0; n < 4; n++) {
                if (b.entry[m][n] == entry[m][n])
                    values_same++;
            }
        }

        return values_same == 16; // True if move does nothing
    }

    // Copy one board to another
    void moveboardxtoy(board& x, board& y) {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                y.entry[i][j] = x.entry[i][j];
    }

    // Check if the board is empty
    bool zerochecker() {
        int m = 0;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (entry[i][j] == 0)
                    m++;
        return m == 16;
    }

    // Find the maximum tile on the board
    int findmax() {
        int max = INT_MIN;
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                if (max < entry[i][j])
                    max = entry[i][j];
        return max;
    }
};

// Namespace with game functions
namespace test {

    // Game modes and input modes
    enum Emode { contest, game, onebyone, series, quit };
    int gamemode = game;
    int inputmode = onebyone;

    // Handles input one move at a time
    int takeinputonebyone(board& a) {
        std::string input;
        char registered_input;

        std::cin >> input;
        cin.ignore();
        if (input.length() > 1) {
            std::cout << "Bad Input. Enter 'w','a','s','d', '!' to quit, or 'i' to "
                "toggle input modes.\n";
            return 1;
        }
        registered_input = std::tolower(input[0]);

        switch (registered_input) {
        case 'd':
            if (a.movetestdir('d')) {
                std::cout << "Move unavailable.\n";
                return 1;
            }
            a.right();
            break;
        case 'a':
            if (a.movetestdir('a')) {
                std::cout << "Move unavailable.\n";
                return 1;
            }
            a.left();
            break;
        case 'w':
            if (a.movetestdir('w')) {
                std::cout << "Move unavailable.\n";
                return 1;
            }
            a.up();
            break;
        case 's':
            if (a.movetestdir('s')) {
                std::cout << "Move unavailable.\n";
                return 1;
            }
            a.down();
            break;
        case '!':
            return 2; // Quit
        case 'i':   // Toggle input mode
            inputmode = (inputmode == series) ? onebyone : series;
            std::cout << (inputmode == onebyone ? "Input mode switched to One-by-One\n"
                : "Input mode switched to Series\n");
            a.shouldPickRand = false;
            break;
        default:
            std::cout << "Invalid Input!\n";
            return 1;
        }
        return 0;
    }

    // Handle multiple moves in a row (series input)
    std::string takeinputseries() {
        std::string input, output;
        getline(std::cin >> std::ws, input);

        for (int i = 0; i < input.length(); i++) {
            switch (input[i]) {
            case 'd':
            case 'a':
            case 'w':
            case 's':
            case '!':
            case 'i':
                output.push_back(input[i]);
                break;
            default:
                break;
            }
        }
        return output;
    }

    // Display the board
    void drawboard(board& a) {
        std::cout << "\n**********************************\n";
        for (int k = 0; k < 4; k++) {
            std::cout << a.entry[0][k] << ' ' << a.entry[1][k] << ' ' << a.entry[2][k]
                << ' ' << a.entry[3][k] << '\n';
        }
        std::cout << "**********************************\n";
    }

    // Clear the board
    void emptyboard(board& a) {
        for (int k = 0; k < 4; k++) {
            a.entry[0][k] = a.entry[1][k] = a.entry[2][k] = a.entry[3][k] = 0;
        }
    }

    // Pick a random cell (2 or 4) for new tile
    void pickrandcell(board& b) {
        int x, y, thechance, values_nonzero;
        while (true) {
            values_nonzero = 0;
            for (int q = 0; q < 4; q++)
                for (int r = 0; r < 4; r++)
                    if (b.entry[q][r] != 0)
                        values_nonzero++;
            if (values_nonzero == 16)
                break; // Board full

            x = rand() % 4;
            y = rand() % 4;

            if (b.entry[x][y] == 0) {
                thechance = rand() % 10;
                b.entry[x][y] = (thechance == 7) ? 4 : 2;
                break;
            }
        }
    }

    // Read board input from user
    bool readtoboard(board& a) {
        string input;
        cin.clear();
        emptyboard(a);

        // Repeated code for each column
        for (int col = 0; col < 4; col++) {
            for (bool isSatisfied = false; !isSatisfied;) {
                isSatisfied = true;
                getline(cin, input);
                for (short spacecount = 0, i = 0; spacecount < 4 && i < input.length();
                    i++) {
                    if (isdigit(input[i])) {
                        a.entry[spacecount][col] =
                            a.entry[spacecount][col] * 10 + (input[i] - '0');
                    }
                    else if (input[i] == ' ') {
                        spacecount++;
                    }
                    else if (input[i] == '!') {
                        return false;
                    }
                    else {
                        std::cout << "Invalid Input! Please re-enter.\n";
                        isSatisfied = false;
                    }
                }
            }
        }
        a.shouldPickRand = false;
        return true;
    }

    // Play interactive game
    int playgame() {
        srand(time(NULL));
        board a;
        bool thething = true;
        std::string input;

        std::cout << "Enter existing dataset? (y/n)\n";
        for (bool isSatisfied = false; !isSatisfied;) {
            getline(cin >> ws, input);
            switch (tolower(input[0])) {
            case 'y':
                readtoboard(a);
                thething = false;
                isSatisfied = true;
                break;
            case 'n':
                emptyboard(a);
                goto begin;
                break;
            default:
                std::cout << "Invalid input!\n";
                break;
            }
        }

    begin:
        if (!thething)
            pickrandcell(a);

        while (true) {
            if (a.shouldPickRand)
                pickrandcell(a);
            else
                a.shouldPickRand = true;

            drawboard(a);
            if (a.movetest())
                break;

            if (inputmode == series) {
                std::string input_series = takeinputseries();
                for (int j = 0; j < input_series.size() && j < 64; j++) {
                    switch (input_series[j]) {
                    case 'd':
                        if (!a.movetestdir('d'))
                            a.right();
                        pickrandcell(a);
                        break;
                    case 'a':
                        if (!a.movetestdir('a'))
                            a.left();
                        pickrandcell(a);
                        break;
                    case 'w':
                        if (!a.movetestdir('w'))
                            a.up();
                        pickrandcell(a);
                        break;
                    case 's':
                        if (!a.movetestdir('s'))
                            a.down();
                        pickrandcell(a);
                        break;
                    case '!':
                        return 1;
                    case 'i':
                        inputmode = (inputmode == series) ? onebyone : series;
                        break;
                    default:
                        break;
                    }
                    a.shouldPickRand = false;
                }
            }
            else {
                switch (takeinputonebyone(a)) {
                case 0:
                    break;
                case 1:
                    continue;
                case 2:
                    return 1;
                }
            }
        }

        std::cout << "GAME OVER\n";
        return 0;
    }

    // Solver function to find max tile from board
    int checker(board xprime) {
        int max = INT_MIN;
        board x = xprime;
        board tester;
        int permutationArray[] = { 1, 2, 3, 4 };

        for (int count = 0; count < 24; count++) {
            emptyboard(tester);
            // Apply permutations of moves to try maximizing tiles
            for (int i = 0; !x.movetest();) {
                if (permutationArray[i] == 1 && !x.movetestdir('w'))
                    x.up();
                if (permutationArray[i] == 2 && !x.movetestdir('a'))
                    x.left();
                if (permutationArray[i] == 3 && !x.movetestdir('s'))
                    x.down();
                if (permutationArray[i] == 4 && !x.movetestdir('d'))
                    x.right();

                if (i == 3)
                    i = 0;
                else
                    i++;

                // Stop if board stops changing
                int copycount = 0;
                for (int k = 0; k < 4; k++)
                    for (int l = 0; l < 4; l++)
                        if (x.entry[k][l] == tester.entry[k][l])
                            copycount++;
                if (copycount == 16)
                    break;

                if (x.zerochecker())
                    return 0;
                drawboard(x);
            }

            if (max < x.findmax())
                max = x.findmax();
            x = xprime;

            // Generate next permutation
        startcount:
            if (permutationArray[3] == 4) {
                permutationArray[3] = 1;
                if (permutationArray[2] == 4) {
                    permutationArray[2] = 1;
                    if (permutationArray[1] == 4) {
                        permutationArray[1] = 1;
                        permutationArray[0]++;
                    }
                    else {
                        permutationArray[1]++;
                    }
                }
                else {
                    permutationArray[2]++;
                }
            }
            else {
                permutationArray[3]++;
            }

            // Avoid duplicate numbers in permutation
            if (permutationArray[0] == permutationArray[1] ||
                permutationArray[0] == permutationArray[2] ||
                permutationArray[0] == permutationArray[3] ||
                permutationArray[1] == permutationArray[2] ||
                permutationArray[1] == permutationArray[3] ||
                permutationArray[2] == permutationArray[3])
                goto startcount;
        }
        return max;
    }

    // Solve 5 pre-set boards
    void problemsolve() {
        std::cout << endl
            << "Enter boards line by line with one space in between" << endl;
        std::cout << "EXAMPLE:" << endl;
        std::cout << "2 0 0 2" << endl;
        std::cout << "0 2 4 0" << endl;
        std::cout << "0 0 0 0" << endl;
        std::cout << "2 0 0 2" << endl;
        std::cout << "-------" << endl << endl;

        board a, b, c, d, e;
        readtoboard(a);
        readtoboard(b);
        readtoboard(c);
        readtoboard(d);
        readtoboard(e);

        std::cout << "Started solving...\n";
        std::cout << checker(a) << '\n';
        std::cout << checker(b) << '\n';
        std::cout << checker(c) << '\n';
        std::cout << checker(d) << '\n';
        std::cout << checker(e) << '\n';
    }

} // namespace test

int main() {
    bool gamemode;

    cout << "--- 2048 Game & Solver ---" << endl;
    cout << "Select a mode:" << endl;
    cout << " [1] Play Interactive Game" << endl;
    cout << " [0] Problem Solve Mode (Check 5 Pre-set Boards)" << endl;
    cout << "Enter your choice: ";

    // Validate input
    if (!(cin >> gamemode)) {
        cout << "Invalid input. Please enter 1 or 0." << endl;
        return 1;
    }

    if (gamemode) {
        if (test::playgame() == 0)
            return 0;
        else {
            std::cout << "\nGame Quit by User\n";
            return 0;
        }
    }
    else {
        test::problemsolve();
        std::cout << "Finished\n";
    }
}
