
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

// Define the maximum number of players per team
#define MAX_PLAYERS 10

// Define your teams
struct {
    string myteam;
} myStructure;


// Assign values to members of myTeam
myStructure.myTeam = Patriots;
myStructure.myString = "Please enter your team: ";

// Print members of myStructure
cout << myStructure.myTeam << "\n";
cout << myStructure.myString << "\n";

// Define a structure for a player
typedef struct {
    char name[100];
    int number;
} Player;

// Define a structure for a team
typedef struct {
    char name[100];
    Player players[MAX_PLAYERS];
    int numPlayers;
} Team;

// Define a function to take user input for a player
void addPlayer(Player* player)
{
    printf("Enter player name: ");
    fgets(player->name, sizeof(player->name), stdin);
    player->name[strcspn(player->name, "\n")] = '\0'; // Remove newline character from input

    printf("Enter player number (1-10): ");
    scanf("%d", &player->number);
    while (getchar() != '\n'); // Clear input buffer
}

// Define a function to take user input for a team
void addTeam(Team* team)
{
    printf("Enter team name: ");
    fgets(team->name, sizeof(team->name), stdin);
    team->name[strcspn(team->name, "\n")] = '\0'; // Remove newline character from input

    printf("Enter number of players (1-%d): ", MAX_PLAYERS);
    scanf("%d", &team->numPlayers);
    while (getchar() != '\n'); // Clear input buffer

    int i;
    for (i = 0; i < team->numPlayers; i++) {
        printf("Enter player %d information:\n", i + 1);
        addPlayer(&team->players[i]);
    }
}

int main()
{
    // Seed the random number generator
    srand(time(NULL));

    // Initialize the teams
    Team team1, team2;
    printf("Enter team 1 information:\n");
    addTeam(&team1);
    printf("\nEnter team 2 information:\n");
    addTeam(&team2);

    // Pick a random number for each player to determine who goes first
    int i;
    int maxNumber = -1;
    Player* firstPlayer = NULL;
    for (i = 0; i < team1.numPlayers; i++) {
        int number = rand() % 10 + 1; // Generate a random number between 1 and 10
        team1.players[i].number = number;
        printf("%s's number is %d\n", team1.players[i].name, number);
        if (number > maxNumber) {
            maxNumber = number;
            firstPlayer = &team1.players[i];
        }
    }
    for (i = 0; i < team2.numPlayers; i++) {
        int number = rand() % 10 + 1; // Generate a random number between 1 and 10
        team2.players[i].number = number;
        printf("%s's number is %d\n", team2.players[i].name, number);
        if (number > maxNumber) {
            maxNumber = number;
            firstPlayer = &team2.players[i];
        }
    }

    // Print the first player
    printf("%s from %s goes first!\n", firstPlayer->name, firstPlayer >= team2.players ? team2.name : team1.name);

    return 0;
}