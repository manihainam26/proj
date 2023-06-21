#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

/*

Things to note

- Player 1 gets to place their ships first, so Player 2 gets to take a turn first
- In the odd case, both players end together, player 2 will win by proxy of having the first turn
- All of the constant variables can be changed to vary the game:
  - representing water, ship, hit or miss differently
  - changing the size of the board. Doesn't need to be square.
  - increase or decrease the number of ships
    - if you do so, you have to edit the function "the_ships" - you can also change names and lengths of ships here
- Since the boards are visible to the players during the game, if they attack a position again, their turn is wasted


*/

// Definitions
const char water = ' ';
const char ship = 'S';
const char hit = 'X';
const char miss = 'O';

// deciding number of ships
const int ship_num = 5;

// height(rows) and width(columns) of the board
const int h = 8;
const int w = 8;

// declaring an array for both players

struct player
{
    char board[h][w];

} plyr[3];

// all function declerations

void initial_board(int);
void print_board(int);
void the_ships();
void place(int, int, int, int, int);
void location_input(int, int);
void battleship_boards();
void print_board_final(int);
int ship_exists(int);
void firing();
int game_over(int);

//-------------------------------  GAME PHASE 1  -------------------------

//---------------------------- Setting up the boards ---------------------

// initializing the board with water

void initial_board(int p)
{

    for (int i = 0; i < h; i++)
    {

        for (int j = 0; j < w; j++)
        {
            plyr[p].board[i][j] = water;
        }
    }
}

// function to print the board with labelling and updated values

void print_board(int p)
{
    cout << "    ";

    for (int s = 0; s < w; s++)
    {
        cout << setw(2) << s + 1 << "  ";
    }
    cout << endl;

    for (int i = 0; i < h; i++)
    {
        cout << setw(2) << i + 1 << "   ";

        for (int j = 0; j < w; j++)
        {

            cout << plyr[p].board[i][j] << "   ";
        }
        cout << endl;
    }
}

// To Print the boards without the ships for gameplay

void print_board_final(int p)
{
    cout << "    ";

    for (int s = 0; s < w; s++)
    {
        cout << setw(2) << s + 1 << "  ";
    }
    cout << endl;

    for (int i = 0; i < h; i++)
    {
        cout << setw(2) << i + 1 << "   ";

        for (int j = 0; j < w; j++)
        {
            if (plyr[p].board[i][j] == ship)
            {
                cout << "    ";
            }
            else
            {
                cout << plyr[p].board[i][j] << "   ";
            }
        }
        cout << endl;
    }
}

// structure to determine size and number of ships

struct ship_plc
{
    string name;
    int size;

} ship_placer[ship_num];

// To make 4 named ships with specified length

void the_ships()
{
    ship_placer[0].name = "Destroyer";
    ship_placer[1].name = "Cruiser";
    ship_placer[2].name = "Submarine";
    ship_placer[3].name = "Battleship";
    ship_placer[4].name = "Carrier";

    ship_placer[0].size = 2;
    ship_placer[1].size = 3;
    ship_placer[2].size = 3;
    ship_placer[3].size = 4;
    ship_placer[4].size = 5;
}

// Takes in the coordinates for ship placement

void location_input(int len, int p)
{

    int orient;
    double x1 = 0;
    double y1 = 0;

    cout << endl
         << "Format:  Orientation (0:horizontal, 1:vertical), Column (1-" << w << "), row (1-" << h << ")" << endl
         << "Example - 0 2 4    Places a ship horizontally in column 2 starting at row 4" << endl
         << "Enter here: ";
    cin >> orient >> x1 >> y1;

    // To handle invalid inputs
    while (cin.fail() || (orient != 1 && orient != 0) || x1 < 1 || x1 > w || y1 < 1 || y1 > h || y1 != int(y1) || x1 != int(x1))
    {
        cin.clear();
        cin.ignore(100000, '\n');
        cout << endl
             << "Invalid input, Enter again" << endl;
        cout << "Enter here: ";
        cin >> orient >> x1 >> y1;
    }
    // x and y were declared as doubles to avoid taking decimal values as inputs
    // converted back to integer so it can be passed to the next function
    int x = int(x1);
    int y = int(y1);

    // Placing the ship on the baord

    place(orient, len, x, y, p);
}

// Places the ship on the board on the speicified coordinates

void place(int dir, int len, int x, int y, int p)
{
    int sy = y - 1;
    int ey = (y - 1) + (len - 1);
    int sx = x - 1;
    int ex = (x - 1) + (len - 1);

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
        {
            if (dir == 0 && i == sy && j >= sx && j <= ex)
            {

                if (plyr[p].board[i][j] != ship && ex < w)
                {
                    plyr[p].board[i][j] = ship;
                }
                else if (plyr[p].board[i][j] == ship || ex >= w)
                {
                    cout << endl
                         << endl;
                    cout << "Ship is already placed or out of bound, try again" << endl;
                    cout << endl;
                    location_input(len, p);
                    return;
                }
            }
            else if (dir == 1 && i >= sy && i <= ey && j == sx)
            {

                if (plyr[p].board[i][j] != ship && ey < h)
                {
                    plyr[p].board[i][j] = ship;
                }
                else if (plyr[p].board[i][j] == ship || ey >= h)
                {
                    cout << endl
                         << endl;
                    cout << "Ship is already placed or out of bound, try again" << endl;
                    cout << endl;
                    location_input(len, p);
                    return;
                }
            }
        }
    }
}

// -----------------------------MAIN PRE GAME FUNCTION------------------------------

void battleship_boards()
{
    cout << endl
         << "WELCOME TO BATTLESHIP!" << endl
         << endl
         << endl
         << "HOW TO PLAY: " << endl
         << endl
         << "1. Both players place " << ship_num << " ships on separate boards, hidden from the other" << endl
         << "2. After all the ships have been placed, it is time to start the game!" << endl
         << "3. Guess where a ship might be on the enemy board and ATTACK!" << endl
         << "4. If you hit a ship, a '" << hit << "' will appear on that position. If you miss, a '" << miss << "' will appear" << endl
         << "5. Whoever hits all the other player's ships first, WINS!" << endl
         << endl

         << endl;

    cout << endl
         << "LET'S PLAY!!!" << endl
         << endl;

    system("pause");

    the_ships();

    // loop to draw boards for both players (only index 1 and 2 needed)
    for (int p = 1; p < 3; p++)
    {
        initial_board(p);

        cout << endl
             << "Player " << p << " , you will now be placing your ships!" << endl
             << endl;

        // loop to go through every ship type

        for (int spl = 0; spl < ship_num; spl++) // spl - ship being placed
        {
            system("cls");
            cout << endl
                 << "Player " << p << "'s Board" << endl
                 << endl;
            print_board(p);

            cout << endl
                 << "You are placing " << ship_placer[spl].name << " of length " << ship_placer[spl].size << endl;

            // Inputting ship coordinates for placing ships

            location_input(ship_placer[spl].size, p);
        }
        system("cls");
    }
} // Ships have now been placed, proceeding to gameplay

//-------------------------------  GAME PHASE 2  -------------------------------

//-------------------------------  The Gameplay  -------------------------------

int main()
{
    // placing ships - main function for game phase 1
    battleship_boards();

    for (int p = 1; p < 3; p++)
    {
        cout << endl
             << "Player " << p << "'s board :" << endl
             << endl;
        // printing the empty boards first to indicate the game has started
        print_board_final(p);
    }

    cout << endl;
    cout << "LET'S BEGIN THE GAME!" << endl
         << endl
         << "FIRE!!!" << endl
         << endl;

    // gameplay - main function for game phase 2

    firing();

    for (int p = 1; p < 3; p++)
    {
        cout << endl;
        cout << "Player " << p << "'s final board :" << endl;
        print_board(p);
    }

    return 0;
}

// ---------------------------MAIN GAMEPLAY FUNCTION----------------------------

void firing()
{
    int plr = 0; // determining turn
    int p;       // idenifying enemy player
    // int p=1;

    // the loop is to conduct the actual attack
    // runs till all ship values on one board turn into hit values

    for (p = 1; ship_exists(p) == 1; p++)
    {

        if (p == 1)
        {
            plr = 2;
        }
        else if (p == 2)
        {
            plr = 1;
        }
        double xi, yi;

        cout << endl
             << "Player " << plr << "'s turn" << endl
             << endl;

        cout << endl
             << "Format: Column (1-" << w << ") , row (1-" << h << ")" << endl
             << "Example: 2 4 " << endl
             << "Enter here: ";
        cin >> xi >> yi;

        // handling inputs that exceed the board's size

        while (cin.fail() || xi > w || xi < 1 || yi > h || yi < 1 || yi != int(yi) || xi != int(xi))
        {
            cin.clear();
            cin.ignore(1000000, '\n');
            cout << endl
                 << "Invalid input, enter again" << endl;
            cout << "Enter here: ";
            cin >> xi >> yi;
        }

        int xx = int(xi);
        int yy = int(yi);

        // for array indexing

        xx -= 1;
        yy -= 1;

        if (plyr[p].board[yy][xx] == ship)
        {
            plyr[p].board[yy][xx] = hit;
            // remove comment below if you want to clear the terminal during the gameplay
            // system ("cls");
            cout << endl
                 << endl
                 << "It's a Hit!" << endl
                 << endl;
        }

        else if (plyr[p].board[yy][xx] == water)
        {
            plyr[p].board[yy][xx] = miss;
            // remove comment below if you want to clear the terminal during the gameplay
            // system ("cls")
            cout << endl
                 << endl
                 << "It's a Miss :(" << endl
                 << endl;
            
        }
        else if (plyr[p].board[yy][xx] == miss || plyr[p].board[yy][xx] == hit)
        {
            // remove comment below if you want to clear the terminal during the gameplay
            // system ("cls")
            cout << endl
                 << "You have already fired at this position and wasted your turn" << endl;
        }

        if (p == 1)
        {
            cout << endl
                 << "Player " << p + 1 << "'s board: " << endl
                 << endl;
            print_board_final(p + 1);
        }
        if (p == 2)
        {
            cout << endl
                 << "Player " << p - 1 << "'s board: " << endl
                 << endl;
            print_board_final(p - 1);
            p = p - 2;
        }
    }

    // determining the winner after the loop ends

    int winner = 0;

    if (plr == 1)
    {
        winner = 2;
    }
    if (plr == 2)
    {
        winner = 1;
    }

    system("cls");

    cout << endl
         << endl
         << endl
         << "  CONGRATULATIONS !!! " << endl
         << endl
         << " ***** PLAYER " << winner << " HAS WON THE GAME! ***** "
         << endl
         << endl;
}

// Checking whether the ships have already sunk

int ship_exists(int p)
{
    int check = 0;

    for (int i = 0; i < h; i++)
    {

        for (int j = 0; j < w; j++)
        {
            if (plyr[p].board[i][j] == ship)
            {
                check += 1;
            }
        }
    }
    if (check > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
