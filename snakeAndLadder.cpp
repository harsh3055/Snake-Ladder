#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <unordered_map>

using namespace std;

class Player {
public:
    string name;
    int position;

    Player(const string& playerName) : name(playerName), position(0) {}
};
// function to roll diceddd
int rollDice()
{
    return (rand() % 6) + 1;
}

void playGame()
{
    vector<Player> players; // Stores the players
    bool gameOver = false;
    int currentPlayer = 0;
    int numPlayers;

    cout << "Enter the number of players: ";
    cin >> numPlayers;

    cin.ignore(); // Ignore the newline character

    // Initialize players
    for (int i = 0; i < numPlayers; ++i) {
        string playerName;
        cout << "Enter the name of player " << i + 1 << ": ";
        getline(cin, playerName);
        players.push_back(Player(playerName));
    }

    // Define the snakes and ladders using an unordered map
    unordered_map<int, int> snakesAndLadders;
    snakesAndLadders[17] = 7;
    snakesAndLadders[54] = 34;
    snakesAndLadders[62] = 19;
    snakesAndLadders[64] = 60;
    snakesAndLadders[87] = 36;
    snakesAndLadders[93] = 73;
    snakesAndLadders[95] = 75;
    snakesAndLadders[98] = 79;

    while (!gameOver)
    {
        cout << endl;
        cout << "Player " << players[currentPlayer].name << " (" << players[currentPlayer].position << ") turn. Press enter to roll the dice...";
        cin.ignore(); // Wait for user input

        int diceRoll = rollDice();
        cout << "Player " << players[currentPlayer].name << " rolled a " << diceRoll << endl;
        players[currentPlayer].position += diceRoll;

        if (players[currentPlayer].position == 100)
        {
            cout << "Player " << players[currentPlayer].name << " wins!" << endl;
            gameOver = true;
        }
        else if (players[currentPlayer].position > 100)
        {
            cout << "Player " << players[currentPlayer].name << " exceeded the board size. Try again." << endl;
            players[currentPlayer].position -= diceRoll;
        }
        else
        {
            cout << "Player " << players[currentPlayer].name << " is now at position " << players[currentPlayer].position << endl;

            // Check if the current position has a snake or ladder
            if (snakesAndLadders.find(players[currentPlayer].position) != snakesAndLadders.end()) {
                int newPosition = snakesAndLadders[players[currentPlayer].position];
                players[currentPlayer].position = newPosition;
                cout << "Player " << players[currentPlayer].name << " got bitten by a snake! Moved to position " << newPosition << endl;
            }
        }

        if (!gameOver)
            currentPlayer = (currentPlayer + 1) % numPlayers;
    }
}

int main()
{
    srand(time(0)); // Seed the random number generator with current time

    cout << "Snake and Ladder Game" << endl;
    cout << "---------------------" << endl;
    cout << endl;

    playGame();

    return 0;
}
