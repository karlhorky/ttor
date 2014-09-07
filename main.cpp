////////////////////////////////////////////////////////////////////////////////
// Name : Karl Horky and Lisa Mooney                                          //
// Module : main.cpp                                                          //
// Module Purpose : Program Initiation and Central Collaborator               //
// Program Name : The Tide of Reckoning                                       //
// Program Purpose : Entertainment                                            //
////////////////////////////////////////////////////////////////////////////////

#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <vector.h>
#include "gBoard.h"     // Creating random game boards and placing objects
#include "classes.h"    // Definition of classes

#define VK_ENTER   13

#define MBOX_WIDTH   34
#define MBOX_HEIGHT  7

#define SBOX_WIDTH   70
#define SBOX_HEIGHT  20



const int MAX_LEVELS = 35;           // Maximum difficulty levels in game
const char* SEQ_NEWWORD = "|";
const char* SEQ_SPC = " ";
const char SEQ_TAB[] = {"|                                   |"};



void intro();                           // Introduction text

void getPlayerName(char playerName[]);  // Gets the name of the player

bool getPAlignment();                   // Gets the alignment of the player



bool mainGameLoop(player &userPlayer,               // The player
                 game &currGame);                   // The current game
// The main game loop



int mQuant(game &currGame);           // The current game
// Randomize a monster quantity and return it

int iQuant(game &currGame);           // The current game
// Randomize an item quantity and return it





void initLevel(game &currGame,                     // The current game
               player &userPlayer,                 // The player of the game
               vector<monster> &m,                // The monsters in the level
               int monsterQuantity,               // The quantity of monsters
               vector<item> &i,                   // The items in the level
               int itemQuantity,                  // The quantity of items
               npc &objNPC,                        // Objective NPC
               npc &goalChar,                      // Objective-based character
               item &goalItem,                     // Objective-based item
               monster &goalMonster,               // Objective-based monster
               char gameBoard[][H_BOARD_SIZE]);   // The game board
// Initialize every aspect of the level except for the game board


void initMonsters(game &currGame,                   // The current game
                  vector<monster> &m,              // The monsters in the level
                  int monsterQuantity,             // The quantity of monsters
                  char gameBoard[][H_BOARD_SIZE]); // The game board
// Initializes random monsters for the current level

void initItems(game &currGame,                  // The current game
               vector<item> &i,                // The items in the level
               int itemQuantity,               // Quantity of items in level
               player &userPlayer,              // The player of the game
               char gameBoard[][H_BOARD_SIZE]);// The game board
// Initializes random items for the current level

void initObjective(game &currGame,                  // The current game
                   npc &objNPC,                     // Objective NPC
                   npc &goalChar,                   // Objective-based character
                   item &goalItem,                  // Objective-based item
                   monster &goalMonster,            // Objective-based monster
                   player &userPlayer,              // The player
                   char gameBoard[][H_BOARD_SIZE]);// The game board
// Initializes a random objective for the current level

void initNPC(game &currGame,                        // The current game
             npc &objNPC,                           // Objective NPC
             char* speech,                         // The NPC's speech
             char gameBoard[][H_BOARD_SIZE]);      // The game board
// Initializes the Non-Player Character for the objective in the current level

void initGoalCharacter(game &currGame,              // The current game
                       npc &goalChar,               // Objective-based character
                       char* speech,               // The character's speech
                       char gameBoard[][H_BOARD_SIZE]); // The game board
// Initializes the objective-based character in the current level (if necessary)

void initGoalItem(game &currGame,                   // The current game
                  item &goalItem,                   // Objective-based item
                  char gameBoard[][H_BOARD_SIZE]); // The game board
// Initializes the objective-based item in the current level (if necessary)

void initGoalMonster(game &currGame,                // The current game
                     monster &goalMonster,          // Objective-based monster
                     char gameBoard[][H_BOARD_SIZE]); // The game board
// Initializes the objective-based monster in the current level (if necessary)





void randomizePlacement(int inCoords[],   // General coords used to randomize
                        int outCoords[],  // Specific randomized coords
                        char gameBoard[][H_BOARD_SIZE]); // The game board
// Randomizes placement of monsters




void playerMove(char gameBoard[][H_BOARD_SIZE],  // The game board
                player &userPlayer,               // The player class
                vector<monster> &m,              // Monsters in level
                int monsterQuantity,             // Quantity of monsters
                vector<item> &i,                 // Items in level
                int itemQuantity,                // Quantity of items
                npc &objNPC,                      // Objective NPC
                npc &goalChar,                    // Objective-based character
                item &goalItem,                   // Objective-based item
                monster &goalMonster,             // Objective-based monster
                game &currGame,                   // The current game
                int &quitting);                  // If the player is quitting
// Allows the player to move



bool testMoveClsn(player &userPlayer,               // The player
                  char gameBoard[][H_BOARD_SIZE],  // The game board
                  vector<monster> &m,              // Monsters in level
                  int monsterQuantity,             // Quantity of monsters
                  vector<item> &i,                 // Items in level
                  int itemQuantity,                // Quantity of items
                  npc &objNPC,                      // Objective NPC
                  npc &goalChar,                    // Objective-based character
                  item &goalItem,                   // Objective-based item
                  monster &goalMonster,             // Objective-based monster
                  int dir);                        // Direction to move
// Test the move's collision with other objects


bool monsterEncroach(char gameBoard[][H_BOARD_SIZE],  // The game board
                     int moveCoords[],           // The potential move coords
                     player &userPlayer,          // The player
                     vector<monster> &m,         // Monsters in level
                     int monsterQuantity,        // Quantity of monsters
                     npc &objNPC,                 // Objective NPC
                     npc &goalChar,               // Objective-based character
                     monster goalMonster);       // Objective-based monster
// If the player's move encroaches apon a monster



void attackSequence(int moveCoords[],           // The potential move coords
                    player &userPlayer,          // The player
                    vector<monster> &m,         // Monsters in level
                    int monsterQuantity,        // Quantity of monsters
                    npc &objNPC,                 // Objective NPC
                    npc &goalChar,               // Objective-based character
                    monster &goalMonster);       // Objective-based monster
// Finds the correct character to attack and starts a battle


void playerTurn(monster &aMonster,     // The defending monster
                player &userPlayer,    // The player
                char turnResult[40]);  // The result of the turn
// An attack turn for the player


void monsterTurn(monster &aMonster,     // The attacking monster
                 player &userPlayer,    // The player
                 char turnResult[40],   // The result of the turn
                 bool pBlocking);       // If the player is blocking
// An attack turn for the monster



void msgBox(char question[],             // The question to be asked
            int type,                    // 0-Boolean, 1-Info, 2-Options
            char responseDesc[],         // Response description
            char iOptions[],             // Input options
            int &response);              // The response to the message box
// Create a message box and display it


void initMsgBox(char outputArray[][MBOX_WIDTH],  // The output array
                int type,                        // 0-Boolean, 1-Info, 2-Options
                char question[],                 // The question to be asked
                char responseDesc[],             // Response description
                int rSpcSt[2]);                  // Start coord:response space
// Initiate question and response options

bool getMsgBoxResponse(int &response,    // The response
                       int type,         // 0-Boolean, 1-Info, 2-Options
                       char iOptions[]); // Options for input
// Get the response to the message box from the user



void seqBox(char sequenceMsg[],           // The sequence box's message
            int type,                     // 0-Boolean, 1-Info, 2-Options
            char responseDesc[],          // Response description
            char iOptions[],              // Input options
            int &response);               // The response to the seq box
// Create a sequence box and display it

void initSeqBox(char outputArray[][SBOX_WIDTH], // The output array
                int type,                       // 0-Boolean, 1-Info, 2-Options
                char sequenceMsg[],             // The sequence message
                char responseDesc[],            // Response description
                int rSpcSt[2]);                 // Start coords:response space
// Initiate question and response options

bool getSeqBoxResponse(int &response,      // The response
                       int type,           // 0-Boolean, 1-Info, 2-Options
                       char iOptions[]);   // Options for input
// Get the response to the sequence box from the user



void setCursorOff();
// Sets the cursor to invisible

void setCursorOn();
// Sets the cursor to visible






int main()
{
  bool quit;

  do
  {
    char playerName[20];
    // The name of the player

    system("CLS");

    intro();
    // Introduction text

    getPlayerName(playerName);
    // Get the player's name
    bool playerAlignment = getPAlignment();
    // Get the player's alignment
    player userPlayer(playerName,           // The player's name
                      playerAlignment);     // The player's alignment
    // Initiate a player with the name and alignment put in

    system("CLS");
    // Clear the screen of cout to allow for WriteConsoleOutput

    game currGame;
    // The current game

    quit = mainGameLoop(userPlayer,
                        currGame);
  } while (!quit);
  return 0;
} // main



void intro()
// Introduction text
{
  cout << "\t\t\tThe Tides of Reckoning\n\nIn the age of the fifth king after t"
          "he death of Calmeritus, the great wizard of\nthe East, turmoil was a"
          "stir. The division between good and evil had become so\ndefined that"
          " there was no longer any gray area. There was, however, gray area\ni"
          "n the rewards offered by each. The reward for returning stolen goods"
          " was\noften the same as the gold they produced when sold.\n\n";
} // intro

void getPlayerName(char playerName[])
// Gets the name of the player
{
  cout << "Please enter your name: ";
  cin.getline(playerName, 20);
} // getPlayerName

bool getPAlignment()
// Gets the player alignment
{
  char inputString[80];        // The string of input
  char truncChar;              // The truncated string
  bool alignment;              // 0 - Good, 1 - Evil

  cout << "Type G to enter as a good player and E to enter as evil: " ;
  cin >> inputString;

  truncChar = tolower(inputString[0]);
  // Truncate the input to one character and change to lowercase

  while(truncChar != 'g' && truncChar != 'e')
  {
    cout << "That's not a G or an E. ";
    cin >> inputString;

    truncChar = inputString[0];
    tolower(truncChar);
  } // while

  if (truncChar == 'g')   // If you choose to be good...
    alignment = 0;        // ...alignment is set at 0
  if (truncChar == 'e')   // If you choose to be evil...
    alignment = 1;        // ...alignment is set at 1

  return alignment;
} // getPAlignment




bool mainGameLoop(player &userPlayer,               // The player
                  game &currGame)                   // The current game
// The main game loop
{
  int quitting = 0;
  // If the player is quitting

  do
  {
    int currentCoords[2];
    // The current coordinates of the player


    int monsterQuantity = mQuant(currGame);
    vector <monster> m(monsterQuantity);
    // Create a vector of monsters for level

    int itemQuantity = iQuant(currGame);
    vector <item> i(itemQuantity);
    // Create a vector of items for level

    npc objNPC;           // The NPC that gives you the objective
    npc goalChar;         // The objective-based character (if necessary)
    item goalItem;        // The objective-based item (if necessary)
    monster goalMonster;  // The objective-based monster (if necessary)

    char gameBoard[V_BOARD_SIZE][H_BOARD_SIZE];
    // The array of chars that is the game board

    int boardComplexity = int((currGame.getLevel() + 1) / 5);
    // Seven levels of game board complexity based upon the level of the game
    if (boardComplexity < 1)  // If the division by five rendered 0...
      boardComplexity++;      // ...make sure that boardComplexity is at least 1

    initGameBoard(gameBoard,             // The game board
                  boardComplexity);      // The complexity
    // Initialize a random game board


    initLevel(currGame,                          // The current game
              userPlayer,                        // The player of the game
              m,                                 // The monster in the level
              monsterQuantity,                   // The quantity of monsters
              i,                                 // The items in the level
              itemQuantity,                      // The quantity of items
              objNPC,                            // Objective NPC
              goalChar,                          // Objective-based character
              goalItem,                          // Objective-based item
              goalMonster,                       // Objective-based monster
              gameBoard);                        // The game board
    // Initialize every aspect of the level except for the game board

    userPlayer.setInitPos();
    // Sets the player's position at 1, 1
    userPlayer.getCoords(currentCoords);
    // Gets the player's current position

    drawPlayer(gameBoard,                // The game board
               currentCoords);           // The coordinates of the player
    // Draw the player on the game board

    drawAllElements(gameBoard);             // The game board
    // Draws all elements on screen

    // envDescription();


    playerMove(gameBoard,                 // The game board
               userPlayer,                // The player class
               m,                         // Monsters in level
               monsterQuantity,           // The quantity of monsters
               i,                         // Items in level
               itemQuantity,              // The quantity of items
               objNPC,                    // Objective NPC
               goalChar,                  // Objective-based character
               goalItem,                  // Objective-based item
               goalMonster,               // Objective-based monster
               currGame,                  // The current game
               quitting);                 // If the player is quitting
    // Allow the player to move

  } while (currGame.currentObjective.getCompleted() // Current obj complete
           && userPlayer.getHealth() > 0);          // Player's health above 0

  if (userPlayer.getHealth() <= 0)
  {
    int playAgain;    // If the user wants to play again

    msgBox("You| have| died.| Do| you| want| to| play| again?| ",
           0,
           "(Y   /   N)",
           "ny",
           playAgain);
    // Ask the user if he wants to play again

    if (playAgain)
      return 0;
    else
      return 1;
  } // else if
  else if (quitting)
    return 1;
} // mainGameLoop



int mQuant(game &currGame)            // The current game
// Randomize a monster quantity and return it
{
  srand(GetTickCount());         // Seed randomize for time

  int randQuantMult = rand()%3 + 10;  // Random quantity multiplyer
  int monsterQuantity = (currGame.getLevel() + 1)*(randQuantMult / 10)+5;

  return monsterQuantity;
} // mQuant


int iQuant(game &currGame)            // The current game
// Randomize an item quantity and return it
{
  srand(GetTickCount());         // Seed randomize from tick count

  int randQuantMult = rand()%2 + 3;
  int itemQuantity = ((currGame.getLevel() + 1) / 10 + 1) * randQuantMult + 5;

  return itemQuantity;
} // iQuant




void initLevel(game &currGame,                     // The current game
               player &userPlayer,                 // The player of the game
               vector<monster> &m,                // The monsters in the level
               int monsterQuantity,               // The quantity of monsters
               vector<item> &i,                   // The items in the level
               int itemQuantity,                  // The quantity of items
               npc &objNPC,                        // Objective NPC
               npc &goalChar,                      // Objective-based character
               item &goalItem,                     // Objective-based item
               monster &goalMonster,               // Objective-based monster
               char gameBoard[][H_BOARD_SIZE])    // The game board
// Initialize every aspect of the level except for the game board
{
  currGame.incLevel();          // Increments the level by one

  initMonsters(currGame,        // The current game
               m,               // The monsters in the level
               monsterQuantity, // The quantity of monsters
               gameBoard);      // The game board
  // Initializes random monsters for the current level

  initItems(currGame,           // The current game
            i,                  // The items in the level
            itemQuantity,       // The quantity of items
            userPlayer,         // The player of the game
            gameBoard);         // The game board
  // Initializes random items for the current level

  initObjective(currGame,       // The current game
                objNPC,         // Objective NPC
                goalChar,       // Objective-based character
                goalItem,       // Objective-based item
                goalMonster,    // Objective-based monster
                userPlayer,     // The player's alignment
                gameBoard);     // The game board
  // Initializes a random objective for the current level
} // initLevel


void initMonsters(game &currGame,                   // The current game
                  vector<monster> &m,              // The monsters in the level
                  int monsterQuantity,             // The quantity of monsters
                  char gameBoard[][H_BOARD_SIZE])  // The game board
// Initializes random monsters for the current level
{
  srand(GetTickCount());         // Seed randomize for time

  for (int mPlcCount = 0; mPlcCount < monsterQuantity; mPlcCount++)
  {
    int randHlthMult = rand()%4+2;        // Random health multiplyer

    int randGold = rand()%currGame.getLevel() + int(currGame.getLevel()*1.5);

    int randWeapLimiter = currGame.getLevel()/4;
    int randWeapType = rand()%2 + (randWeapLimiter + 1);
    int randWeapLvl = rand()%10 - int(randWeapType - currGame.getLevel()/3.5)
                             + 1;

    int randTypeLimiter = currGame.getLevel()/7;
    // So that there aren't monsters that are too easy
    int randTypeSpec = 8 - int((MAX_LEVELS - currGame.getLevel())/5)
                       - randTypeLimiter;
    int randType = rand()%randTypeSpec+(randTypeLimiter+1);
    // Random types of monster

    int inCoords[] = {0, 0};
    int randomCoords[2];

    randomizePlacement(inCoords,      // General coords used to randomize
                       randomCoords,  // Specific randomized coords
                       gameBoard);    // The game board
    m[mPlcCount].setInitCoords(randomCoords);
    // Sets random coords

    m[mPlcCount].setInitHealth(randType * randHlthMult
                               * (currGame.getLevel() / 7) + 6);
    // Sets the initial health of the monster

    int initArmour = (currGame.getLevel() - 1) * 3 - 35 / randHlthMult;
    if (initArmour < 0)
      initArmour = 0;
    m[mPlcCount].setInitArmour(initArmour);

    m[mPlcCount].setInitGold(randGold);

    m[mPlcCount].setInitWeapon(randWeapType, randWeapLvl);
    // Set a random weapon

    m[mPlcCount].setInitAccuracy((currGame.getLevel() * 1.5 + 40) / 100);
    // Set the initial accuracy of the monster

    switch (randType)
    // Set monsters' names via monster type
    {
      case 1:
        m[mPlcCount].setName("Spider");
        break;
      case 2:
        m[mPlcCount].setName("Gorgon");
        break;
      case 3:
        m[mPlcCount].setName("Grueller");
        break;
      case 4:
        m[mPlcCount].setName("Snake");
        break;
      case 5:
        m[mPlcCount].setName("Dupled");
        break;
      case 6:
        m[mPlcCount].setName("Deotapht");
        break;
      case 7:
        m[mPlcCount].setName("Machepor");
        break;
      case 8:
        m[mPlcCount].setName("Fripp");
        break;
    } // switch

    drawMonster(gameBoard,                // The game board
                randomCoords,             // The random coordinates
                randType);                // The random type of monster
  } // for

} // initMonsters



void initItems(game &currGame,                  // The current game
               vector<item> &i,                // The items in the level
               int itemQuantity,               // Quantity of items in level
               player &userPlayer,              // The player of the game
               char gameBoard[][H_BOARD_SIZE]) // The game board
// Initializes random items for the current level
{
  srand(GetTickCount());         // Seed randomize from tick count

  for (int iPlcCount = 0; iPlcCount < itemQuantity; iPlcCount++)
  {
    int itemType = rand()%4+1;
    int itemShift = rand()%3;

    int inCoords[] = {0, 0};
    int randomCoords[2];

    randomizePlacement(inCoords,      // General coords used to randomize
                       randomCoords,  // Specific randomized coords
                       gameBoard);    // The game board

    i[iPlcCount].setInitCoords(randomCoords);
    // Sets random coords

  } // for
} // initItems



void initObjective(game &currGame,                  // The current game
                   npc &objNPC,                     // Objective NPC
                   npc &goalChar,                   // Objective-based character
                   item &goalItem,                  // Objective-based item
                   monster &goalMonster,            // Objective-based monster
                   player &userPlayer,              // The player
                   char gameBoard[][H_BOARD_SIZE]) // The game board
// Initializes a random objective for the current level
{
  char* speech;

  initNPC(currGame,           // The current game
          objNPC,             // Objective NPC
          speech,             // The NPC's speech
          gameBoard);         // The game board
  // Initializes the NPC for the objective

  srand(GetTickCount());
  bool objectiveChoose = rand()%2;

  if (!userPlayer.getAlignment())
  {
    if (!objectiveChoose)
    {
      // function to randomly choose between several objective briefings
      //objective currentObjective(type 0, text taken from above func);
      //initGoalItem(currGame);   // item type? (from objective briefing?)
    } // if
    else
    {
      // function to randomly choose between several objective briefings
      //objective currentObjective(type 1, text taken from above func);
      //initGoalCharacter(currGame); // monster type? (from objective briefing?)
    } // else
  } // if
  else
  {
    if (!objectiveChoose)
    {
      // function to randomly choose between several objective briefings
      //objective currentObjective(type 2, text taken from above func);
      //initGoalItem(currGame);   // item type? (from objective briefing?)
    } // if
    else
    {
      // function to randomly choose between several objective briefings
      //objective currentObjective(type 3, text taken from above func);
      //initGoalCharacter(currGame); // monster type? (from objective briefing?)
    } // else
  } // else
} // initObjective



void initNPC(game &currGame,                        // The current game
             npc &objNPC,                           // Objective NPC
             char* speech,                         // The NPC's speech
             char gameBoard[][H_BOARD_SIZE])       // The game board
// Initializes the Non-Player Character for the objective in the current level
{

} // initNPC


void initGoalCharacter(game &currGame,              // The current game
                       npc &goalChar,               // Objective-based character
                       char* speech,               // The character's speech
                       char gameBoard[][H_BOARD_SIZE]) // The game board
// Initializes the objective-based character in the current level (if necessary)
{
  // npc goalChar;
} // initGoalCharacter


void initGoalItem(game &currGame,                   // The current game
                  item &goalItem,                   // Objective-based item
                  char gameBoard[][H_BOARD_SIZE])  // The game board
// Initializes the objective-based item in the current level (if necessary)
{
  // item goalItem;
} // initGoalItem

void initGoalMonster(game &currGame,                // The current game
                     monster &goalMonster,          // Objective-based monster
                     char gameBoard[][H_BOARD_SIZE]) // The game board
// Initializes the objective-based monster in the current level (if necessary)
{
  // monster goalMonster;
} // initGoalMonster





void randomizePlacement(int inCoords[],   // General coords used to randomize
                        int outCoords[],  // Specific randomized coords
                        char gameBoard[][H_BOARD_SIZE]) // The game board
// Randomizes placement of monsters
{
  int randVPlcmt, randHPlcmt;           // Random coordinates
  int vBound, hBound;                   // Bounds for the randomizer
  int vOffset, hOffset;                 // Offsets for the bounds

  if (inCoords[0] == 0 && inCoords[1] == 0)
  // If no general bounds specified
  {
    vBound = V_BOARD_SIZE - 2;
    vOffset = 1;
    hBound = H_BOARD_SIZE - 2;
    hOffset = 1;
  } // if
  else
  // If general bounds are specified
  {
    for (int boundAssign = 0; boundAssign <= 1; boundAssign++)
    {
      switch (inCoords[boundAssign])
      {
        case 1:
          if (!boundAssign)
          {
            vBound = 4;
            vOffset = 1;
          } // if
          else
          {
            vBound = 10;
            vOffset = 1;
          } // else
          break;

        case 2:
          if (!boundAssign)
          {
            vBound = 4;
            vOffset = 5;
          } // if
          else
          {
            vBound = 10;
            vOffset = 11;
          } // else
          break;

        case 3:
          if (!boundAssign)
          {
            vBound = 4;
            vOffset = 9;
          } // if
          else
          {
            vBound = 10;
            vOffset = 21;
          } // else
          break;

        case 4:
          if (!boundAssign)
          {
            vBound = 4;
            vOffset = 13;
          } // if
          else
          {
            vBound = 10;
            vOffset = 31;
          } // else
          break;

        case 5:
          if (!boundAssign)
          {
            vBound = 3;
            vOffset = 17;
          } // if
          else
          {
            vBound = 9;
            vOffset = 41;
          } // else
          break;
      } // switch
    } // for
  } // else

  do
  {
    randVPlcmt = rand()%vBound + vOffset;    // Random verti. plcmt
    randHPlcmt = rand()%hBound + hOffset;    // Random horiz. plcmt
  } while (gameBoard[randVPlcmt][randHPlcmt] != BLKSPC);

  outCoords[0] = randVPlcmt;
  outCoords[1] = randHPlcmt;
} // randomizePlacement






void playerMove(char gameBoard[][H_BOARD_SIZE],  // The game board
                player &userPlayer,               // The player class
                vector<monster> &m,              // Monsters in level
                int monsterQuantity,             // Quantity of monsters
                vector<item> &i,                 // Items in level
                int itemQuantity,                // Quantity of items
                npc &objNPC,                      // Objective NPC
                npc &goalChar,                    // Objective-based character
                item &goalItem,                   // Objective-based item
                monster &goalMonster,             // Objective-based monster
                game &currGame,                   // The current game
                int &quitting)                   // If the player is quitting
// Allows the player to move
{
  int playerCoords[2];
  int prevCoords[2];
  userPlayer.getCoords(playerCoords);
  userPlayer.getCoords(prevCoords);

  bool moveValid = 0;    // If the move is valid or not

  INPUT_RECORD inputRecord;
  HANDLE inputHandle = GetStdHandle(STD_INPUT_HANDLE);
  DWORD events = 0;

  HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  setCursorOff();          // Turns the cursor off

  while (!currGame.currentObjective.getCompleted()  // Current obj incomplete
         && userPlayer.getHealth() > 0     // and player's health is above 0
         && !quitting)                     // and the player's not quitting
  {
    do
    {
      ReadConsoleInput(inputHandle, &inputRecord, 1, &events);
      // Gets a keystroke

      if(inputRecord.EventType == KEY_EVENT
         && inputRecord.Event.KeyEvent.bKeyDown == 0)
    	// If the user (presses and) releases a key
	    {

        if (inputRecord.Event.KeyEvent.wVirtualKeyCode == VK_UP)
        // If up arrow is pressed
        {
          if (!(playerCoords[0] - 1 < 0))
          {
            moveValid = testMoveClsn(userPlayer,   // The player
                                     gameBoard,    // The game board
                                     m,            // Monsters in level
                                     monsterQuantity, // Quantity of monsters
                                     i,            // Items in level
                                     itemQuantity, // Quantity of items
                                     objNPC,       // Objective NPC
                                     goalChar,     // Objective-based character
                                     goalItem,     // Objective-based item
                                     goalMonster,  // Objective-based monster
                                     0);           // Direction to move
            // Test the move's collision with other objects

            if (moveValid)
            {
              playerCoords[0]--; // Change the verti. coord for game board
              userPlayer.offsetCoords(0);  // Change the actual player's coords
            } // if
          } // if
        } // if
        else if (inputRecord.Event.KeyEvent.wVirtualKeyCode == VK_LEFT)
        // If left arrow is pressed
        {
          if (!(playerCoords[1] - 1 < 0))
          {
            moveValid = testMoveClsn(userPlayer,   // The player
                                     gameBoard,    // The game board
                                     m,            // Monsters in level
                                     monsterQuantity, // Quantity of monsters
                                     i,            // Items in level
                                     itemQuantity, // Quantity of items
                                     objNPC,       // Objective NPC
                                     goalChar,     // Objective-based character
                                     goalItem,     // Objective-based item
                                     goalMonster,  // Objective-based monster
                                     1);           // Direction to move
            // Test the move's collision with other objects

            if (moveValid)
            {
              playerCoords[1]--;   // Change the horizontal coordinate
              userPlayer.offsetCoords(1);  // Change the actual player's coords
            } // if
          } // if
        } // else if
        else if (inputRecord.Event.KeyEvent.wVirtualKeyCode == VK_DOWN)
        // If down arrow is pressed
        {
          if (!(playerCoords[0] + 1 > V_BOARD_SIZE))
          {
            moveValid = testMoveClsn(userPlayer,   // The player
                                     gameBoard,    // The game board
                                     m,            // Monsters in level
                                     monsterQuantity, // Quantity of monsters
                                     i,            // Items in level
                                     itemQuantity, // Quantity of items
                                     objNPC,       // Objective NPC
                                     goalChar,     // Objective-based character
                                     goalItem,     // Objective-based item
                                     goalMonster,  // Objective-based monster
                                     2);           // Direction to move
            // Test the move's collision with other objects

            if (moveValid)
            {
              moveValid = true;    // The move is valid
              playerCoords[0]++;   // Change the vertical coordinate
              userPlayer.offsetCoords(2);  // Change the actual player's coords
            } // if
          } // if
        } // else if
        else if (inputRecord.Event.KeyEvent.wVirtualKeyCode == VK_RIGHT)
        // If right arrow is pressed
        {
          if (!(playerCoords[1] + 1 > H_BOARD_SIZE))
          {
            moveValid = testMoveClsn(userPlayer,   // The player
                                     gameBoard,    // The game board
                                     m,            // Monsters in level
                                     monsterQuantity, // Quantity of monsters
                                     i,            // Items in level
                                     itemQuantity, // Quantity of items
                                     objNPC,       // Objective NPC
                                     goalChar,     // Objective-based character
                                     goalItem,     // Objective-based item
                                     goalMonster,  // Objective-based monster
                                     3);           // Direction to move
            // Test the move's collision with other objects

            if (moveValid)
            {
              moveValid = true;    // The move is valid
              playerCoords[1]++;   // Change the vertical coordinate
              userPlayer.offsetCoords(3);  // Change the actual player's coords
            } // if
          } // if
        } // else if
        else if (inputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
        // If escape is pressed
        {
          msgBox("Are| you| sure| you| want| to| quit?| ",
                 0,
                 "(Y   /   N)",
                 "ny",
                 quitting);     // Response
            // Message box asking whether you want to quit or not
          if (!quitting)
            drawAllElements(gameBoard);
        } // else if
      } // if
      FlushConsoleInputBuffer(inputHandle);  // Clear input buffer
    } while (!moveValid && !quitting);



    if (!quitting)
    {
      removeObject(gameBoard,       // The game board
                   prevCoords);     // The previous coordinates of the player
      // Remove the previous iteration of the player from the game board

      drawPlayer(gameBoard,         // The game board
                 playerCoords);     // The new coordinates of the player
      // Draw a new iteration of the player to the game board

      for (int resetCount = 0; resetCount <= 1; resetCount++)
        // Resets the previous coordinate variable
        prevCoords[resetCount] = playerCoords[resetCount];

      drawVolatileElements(gameBoard);
    } // if

  } // while
} // playerMove


bool testMoveClsn(player &userPlayer,              // The player
                  char gameBoard[][H_BOARD_SIZE],  // The game board
                  vector<monster> &m,              // Monsters in level
                  int monsterQuantity,             // Quantity of monsters
                  vector<item> &i,                 // Items in level
                  int itemQuantity,                // Quantity of items
                  npc &objNPC,                     // Objective NPC
                  npc &goalChar,                   // Objective-based character
                  item &goalItem,                  // Objective-based item
                  monster &goalMonster,            // Objective-based monster
                  int dir)                         // Direction to move
// Test the move's collision with other objects
{
  char testChar;  // Character to be tested

  int playerCoords[2];
  int moveCoords[2];
  userPlayer.getCoords(playerCoords);      // Set the player's coordinates
  userPlayer.getCoords(moveCoords);        // Set potential move coordinates

  switch (dir)
  // Based upon direction, set the character to be tested accordingly
  {
    case 0:   // Up
      testChar = gameBoard[playerCoords[0] - 1][playerCoords[1]];
      moveCoords[0]--;
      break;
    case 1:   // Left
      testChar = gameBoard[playerCoords[0]][playerCoords[1] - 1];
      moveCoords[1]--;
      break;
    case 2:   // Down
      testChar = gameBoard[playerCoords[0] + 1][playerCoords[1]];
      moveCoords[0]++;
      break;
    case 3:   // Right
      testChar = gameBoard[playerCoords[0]][playerCoords[1] + 1];
      moveCoords[1]++;
  } // switch

  if (testChar != BLKSPC)
  {
    switch (testChar)
    // Test the character
    {
      case WALL:
        return 0;
        break;
      case M_SPIDER:
        monsterEncroach(gameBoard,       // The game board
                        moveCoords,      // Potential move coordinates
                        userPlayer,      // The player
                        m,               // Monsters in the level
                        monsterQuantity, // Quantity of monsters
                        objNPC,          // Objective NPC
                        goalChar,        // Objective-based character
                        goalMonster);    // Objective-based monster
        // If the player's move encroaches apon a monster
        return 0;
        break;
      case M_GORGON:
        monsterEncroach(gameBoard,       // The game board
                        moveCoords,      // Potential move coordinates
                        userPlayer,      // The player
                        m,               // Monsters in the level 
                        monsterQuantity, // Quantity of monsters
                        objNPC,          // Objective NPC
                        goalChar,        // Objective-based character
                        goalMonster);    // Objective-based monster
        // If the player's move encroaches apon a monster
        return 0;
        break;
      case M_GRUELLER:
        monsterEncroach(gameBoard,       // The game board
                        moveCoords,      // Potential move coordinates
                        userPlayer,      // The player
                        m,               // Monsters in the level 
                        monsterQuantity, // Quantity of monsters
                        objNPC,          // Objective NPC
                        goalChar,        // Objective-based character
                        goalMonster);    // Objective-based monster
        // If the player's move encroaches apon a monster
        return 0;
        break;
      case M_SNAKE:
        monsterEncroach(gameBoard,       // The game board
                        moveCoords,      // Potential move coordinates
                        userPlayer,      // The player
                        m,               // Monsters in the level  
                        monsterQuantity, // Quantity of monsters
                        objNPC,          // Objective NPC
                        goalChar,        // Objective-based character
                        goalMonster);    // Objective-based monster
        // If the player's move encroaches apon a monster
        return 0;
        break;
      case M_DUPLED:
        monsterEncroach(gameBoard,       // The game board
                        moveCoords,      // Potential move coordinates
                        userPlayer,      // The player
                        m,               // Monsters in the level 
                        monsterQuantity, // Quantity of monsters
                        objNPC,          // Objective NPC
                        goalChar,        // Objective-based character
                        goalMonster);    // Objective-based monster
        // If the player's move encroaches apon a monster
        return 0;
        break;
      case M_DEOTAPHT:
        monsterEncroach(gameBoard,       // The game board
                        moveCoords,      // Potential move coordinates
                        userPlayer,      // The player
                        m,               // Monsters in the level  
                        monsterQuantity, // Quantity of monsters
                        objNPC,          // Objective NPC
                        goalChar,        // Objective-based character
                        goalMonster);    // Objective-based monster
        // If the player's move encroaches apon a monster
        return 0;
        break;
      case M_MACHEPOR:
        monsterEncroach(gameBoard,       // The game board
                        moveCoords,      // Potential move coordinates
                        userPlayer,      // The player
                        m,               // Monsters in the level 
                        monsterQuantity, // Quantity of monsters
                        objNPC,          // Objective NPC
                        goalChar,        // Objective-based character
                        goalMonster);    // Objective-based monster
        // If the player's move encroaches apon a monster
        return 0;
        break;
      case M_FRIPP:
        monsterEncroach(gameBoard,       // The game board
                        moveCoords,      // Potential move coordinates
                        userPlayer,      // The player
                        m,               // Monsters in the level 
                        monsterQuantity, // Quantity of monsters
                        objNPC,          // Objective NPC
                        goalChar,        // Objective-based character
                        goalMonster);    // Objective-based monster
        // If the player's move encroaches apon a monster
        return 0;
        break;
    } // switch
  } // if
  else
  // If it is an open space, let the player move
    return 1;
} // testMoveClsn

bool monsterEncroach(char gameBoard[][H_BOARD_SIZE],  // The game board
                     int moveCoords[],           // The potential move coords
                     player &userPlayer,          // The player
                     vector<monster> &m,         // Monsters in level
                     int monsterQuantity,        // Quantity of monsters
                     npc &objNPC,                 // Objective NPC
                     npc &goalChar,               // Objective-based character
                     monster goalMonster)        // Objective-based monster
// If the player's move encroaches apon a monster
{
  int attackResponse;

  msgBox("Options",
         0,
         "(A)ttack  /  (C)ancel",
         "ca",
         attackResponse);
  if (attackResponse)
  // If player wants to attack, go to attackSequence
  {
    drawAllElements(gameBoard);   // The game board
    // Clear the screen
    attackSequence(moveCoords,      // Potential move coordinates
                   userPlayer,      // The player
                   m,               // Monsters in the level
                   monsterQuantity, // Quantity of monsters
                   objNPC,          // Objective NPC
                   goalChar,        // Objective-based character
                   goalMonster);    // Objective-based monster
    // Finds the correct character to attack and starts a battle
    drawAllElements(gameBoard);   // The game board
    // Clear the screen
    return 1;
  } // if
  else
  {
    drawAllElements(gameBoard);   // The game board
    // Draw all elements to the screen
    return 0;
  } // else
} // monsterEncroach




void attackSequence(int moveCoords[],           // The potential move coords
                    player &userPlayer,          // The player
                    vector<monster> &m,         // Monsters in level
                    int monsterQuantity,        // Quantity of monsters
                    npc &objNPC,                // Objective NPC
                    npc &goalChar,              // Objective-based character
                    monster &goalMonster)       // Objective-based monster
// Finds the correct character to attack and starts a battle
{
  bool genMonsterMatch = false;
  int genMonsterNum;

  bool objNPCMatch = false;
  bool goalCharMatch = false;
  bool goalMonsterMatch = false;

  int charCoords[2];    // The current tested character's coordinates
  char seqMsg[800];     // The sequence box message
  char mTurnResult[40]; // The result of a monster's turn
  char pTurnResult[40]; // The result of a player's turn
  char killNotify[40];  // Notify the player of victory or defeat
  char seqBuffer[20];   // The sequence buffer, used for converting ints
  char aHealth[11];     // The attacked char's health
  char pHealth[11];     // The player's health
  char aArmour[11];     // The attacked char's armour
  char pArmour[11];     // The player's armour
  int seqResponse;      // The response to the sequence
  int noResponse;       // When no response is required but an int is
  bool fleeing;         // If the player is fleeing from battle
  int spaceNum;         // The number of spaces between elements in a seq box
  monster aMonster;     // The attacked monster
  npc aNPC;             // The attacked NPC

  for (int mCount = 0; mCount < monsterQuantity; mCount++)
  {
    m[mCount].getCoords(charCoords);

    if (charCoords[0] == moveCoords[0] && charCoords[1] == moveCoords[1])
    {
      genMonsterMatch = true;
      genMonsterNum = mCount;
      aMonster = m[genMonsterNum];
    } // if
  } // for

  if (!genMonsterMatch)
  // If the coordinates didn't match a general monster, test the objective NPC
  {
    objNPC.getCoords(charCoords);

    if (charCoords[0] == moveCoords[0] && charCoords[1] == moveCoords[1])
    {
      objNPCMatch = true;
      aNPC = objNPC;
    } // if

    if (!objNPCMatch)
    // If the coordinates didn't match the objective NPC, test the
    // objective-based character
    {
      goalChar.getCoords(charCoords);

      if (charCoords[0] == moveCoords[0] && charCoords[1] == moveCoords[1])
        goalCharMatch = true;

      if (!goalCharMatch)
      // If the coordinates didn't match the objective-based character, test the
      // objective-based monster
      {
        goalMonster.getCoords(charCoords);

        if (charCoords[0] == moveCoords[0] && charCoords[1] == moveCoords[1])
          goalMonsterMatch = true;
      } // if
    } // if
  } // if

  strcpy(pTurnResult, "");
  strcpy(mTurnResult, "");

  if (genMonsterMatch)
  {
    do
    {
      strcpy(aHealth, "(");
      itoa(aMonster.getHealth(), seqBuffer, 10);
      strcat(aHealth, seqBuffer);
      strcat(aHealth, " / ");
      itoa(aMonster.getPotHealth(), seqBuffer, 10);
      strcat(aHealth, seqBuffer);
      strcat(aHealth, ")");


      strcpy(pHealth, "(");
      itoa(userPlayer.getHealth(), seqBuffer, 10);
      strcat(pHealth, seqBuffer);
      strcat(pHealth, " / ");
      itoa(userPlayer.getPotHealth(), seqBuffer, 10);
      strcat(pHealth, seqBuffer);
      strcat(pHealth, ")");


      strcpy(aArmour, "(");
      itoa(aMonster.getArmour(), seqBuffer, 10);
      strcat(aArmour, seqBuffer);
      strcat(aArmour, " / ");
      itoa(aMonster.getPotArmour(), seqBuffer, 10);
      strcat(aArmour, seqBuffer);
      strcat(aArmour, ")");


      strcpy(pArmour, "(");
      itoa(userPlayer.getArmour(), seqBuffer, 10);
      strcat(pArmour, seqBuffer);
      strcat(pArmour, " / ");
      itoa(userPlayer.getPotArmour(), seqBuffer, 10);
      strcat(pArmour, seqBuffer);
      strcat(pArmour, ")");



      strcpy(seqMsg, "Battle| ");

      spaceNum = 65;
      for (int spcCount = 0; spcCount < spaceNum; spcCount++)
        strcat(seqMsg, SEQ_SPC);
      strcat(seqMsg, SEQ_NEWWORD);

      strcat(seqMsg, aMonster.getName());
      strcat(seqMsg, SEQ_NEWWORD);
      // Names
      spaceNum = 66 - strlen(aMonster.getName()) - strlen(userPlayer.getName());
      for (int spcCount = 0; spcCount < spaceNum; spcCount++)
        strcat(seqMsg, SEQ_SPC);
  
      strcat(seqMsg, userPlayer.getName());
      strcat(seqMsg, SEQ_NEWWORD);
  


      spaceNum = 65;
      for (int spcCount = 0; spcCount < spaceNum; spcCount++)
        strcat(seqMsg, SEQ_SPC);
      strcat(seqMsg, SEQ_NEWWORD);
  
  
        
      strcat(seqMsg, aHealth);
      strcat(seqMsg, SEQ_NEWWORD);
      // Healths
      spaceNum = 66 - strlen(aHealth) - strlen(pHealth);
      for (int spcCount = 0; spcCount < spaceNum; spcCount++)
        strcat(seqMsg, SEQ_SPC);

      strcat(seqMsg, pHealth);
      strcat(seqMsg, SEQ_NEWWORD);




      strcat(seqMsg, aArmour);
      strcat(seqMsg, SEQ_NEWWORD);
      // Armours
      spaceNum = 66 - strlen(aArmour) - strlen(pArmour);
      for (int spcCount = 0; spcCount < spaceNum; spcCount++)
        strcat(seqMsg, SEQ_SPC);

      strcat(seqMsg, pArmour);
      strcat(seqMsg, SEQ_NEWWORD);



      strcat(seqMsg, aMonster.getCurrentWeapon().getName());
      // Weapons
      spaceNum = 66 - strlen(aMonster.getCurrentWeapon().getName())
                    - strlen(userPlayer.getCurrentWeapon().getName());
      for (int spcCount = 0; spcCount < spaceNum; spcCount++)
        strcat(seqMsg, SEQ_SPC);

      strcat(seqMsg, userPlayer.getCurrentWeapon().getName());
      strcat(seqMsg, SEQ_NEWWORD);

      spaceNum = 66;
      for (int spcCount = 0; spcCount < spaceNum; spcCount++)
        strcat(seqMsg, SEQ_SPC);
      strcat(seqMsg, SEQ_NEWWORD);

      spaceNum = 66;
      for (int spcCount = 0; spcCount < spaceNum; spcCount++)
        strcat(seqMsg, SEQ_SPC);
      strcat(seqMsg, SEQ_NEWWORD);

      if (strlen(pTurnResult) > 0)
      // Results of a player's turn
      {
        strcat(seqMsg, pTurnResult);
        strcpy(pTurnResult, "");

        spaceNum = 66;
        for (int spcCount = 0; spcCount < spaceNum; spcCount++)
          strcat(seqMsg, SEQ_SPC);
        strcat(seqMsg, SEQ_NEWWORD);
      } // if



      if (strlen(mTurnResult) > 0)
      // Results of a monster's turn
      {          
        strcat(seqMsg, mTurnResult);
        strcpy(mTurnResult, "");
      } // if

      seqBox(seqMsg,
             2,
             "(A)ttack  /  (B)lock  /  (F)lee",
             "fba",
             seqResponse);

      if (seqResponse == 0)
      // If player decides to flee
      {
        fleeing = true;
        monsterTurn(aMonster,     // The attacking monster
                    userPlayer,   // The player
                    mTurnResult,  // The result of the turn
                    false);       // The player isn't blocking
        // Give the monster a turn
        seqBox(mTurnResult,     // The result of the monster's turn
               1,               // Info box
               "",              // None
               "",              // None
               noResponse);     // No response required
        // Lets the player know that the monster has tried to hit him
      } // if
      else if (seqResponse == 1)
      // If player decides to block
        monsterTurn(aMonster,     // The attacking monster
                    userPlayer,   // The player
                    mTurnResult,  // The result of the turn
                    true);        // The player is blocking
        // Give the monster a turn
      else if (seqResponse == 2)
      // If the player decides to attack
      {
        playerTurn(aMonster,     // The defending monster
                   userPlayer,   // The player
                   pTurnResult); // The result of the turn
        // Give the player a turn

        monsterTurn(aMonster,     // The attacking monster
                    userPlayer,   // The player
                    mTurnResult,  // The result of the turn
                    false);       // The player isn't blocking
        // Give the monster a turn
        if (aMonster.getHealth() <= 0)
        {
          strcpy(killNotify, "You| have| killed| the| ");
          strcat(killNotify, aMonster.getName());
          strcat(killNotify, "!| ");

          spaceNum = 66;
          for (int spcCount = 0; spcCount < spaceNum; spcCount++)
            strcat(killNotify, SEQ_SPC);
          strcat(killNotify, SEQ_NEWWORD);

          spaceNum = 66;
          for (int spcCount = 0; spcCount < spaceNum; spcCount++)
            strcat(killNotify, SEQ_SPC);
          strcat(killNotify, SEQ_NEWWORD);

          spaceNum = 66;
          for (int spcCount = 0; spcCount < spaceNum; spcCount++)
            strcat(killNotify, SEQ_SPC);
          strcat(killNotify, SEQ_NEWWORD);


          strcat(killNotify, "The| ");
          strcat(killNotify, aMonster.getName());
          strcat(killNotify, "| has| dropped| ");
          itoa(aMonster.getGold(), seqBuffer, 10);
          strcat(killNotify, seqBuffer);
          strcat(killNotify, "| gold| pieces.");

          seqBox(killNotify,   // The notification text
                 1,            // Info box
                 "",           // None
                 "",           // None
                 noResponse);  // No response necessary
          // The sequence box notifying you of victory
        } // if
        else if (userPlayer.getHealth() <= 0)
        {
          strcpy(killNotify, "You have been killed by the ");
          strcat(killNotify, aMonster.getName());
          strcat(killNotify, "!");
          seqBox(killNotify,   // The notification text
                 1,            // Info box
                 "",           // None
                 "",           // None
                 noResponse);  // No response necessary
          // The sequence box notifying you of defeat
        } // else if
      } // else if
    } while (aMonster.getHealth() > 0 && userPlayer.getHealth() > 0
             && !fleeing);
  } // if
  else if (objNPCMatch)
  {
  } // else if
  else if (goalCharMatch)
  {
  } // else if
  else if (goalMonsterMatch)
  {
  } // else if
} // attackSequence



void playerTurn(monster &aMonster,     // The defending monster
                player &userPlayer,    // The player
                char turnResult[40])   // The result of the turn
// An attack turn for the player
{
  srand(GetTickCount());         // Seed randomize for time

  int randOffset = rand()%100+20;
  for (int rCount = 0; rCount < randOffset; rCount++)
  // Offset the random numbers
    randOffset = rand()%100+30;

  float randHit = rand()%100+1;
  char dmgAmountStr[20];           // Amount of damage in string form
  int dmgAmount;                   // Amount of damage in integer form

  strcpy(turnResult, userPlayer.getName());
  strcat(turnResult, "| (");
  strcat(turnResult, userPlayer.getCurrentWeapon().getName());
  strcat(turnResult, ")| ");

  if (randHit <= userPlayer.getAccuracy()*100)
  // If the attack hit
  {
    itoa(userPlayer.getCurrentWeapon().getStrength(), dmgAmountStr, 10);
    dmgAmount = userPlayer.getCurrentWeapon().getStrength();

    strcat(turnResult, "hits| ");
    strcat(turnResult, aMonster.getName());
    strcat(turnResult, ",| damaging| him| -");
    strcat(turnResult, dmgAmountStr);
    strcat(turnResult, "!| ");

    if (aMonster.getArmour() > 0)
    // If the monster has armour
    {
      if (aMonster.getArmour() >= dmgAmount/2)
      // If the monster has enough armour, divide equally between
      {
        aMonster.offsetArmour(-dmgAmount/2);
        aMonster.offsetHealth(-dmgAmount/2);
      }
      else
      // If the monster doesn't have enough armour
      {
        int remainderDmg = dmgAmount/2 - aMonster.getArmour();
        aMonster.offsetArmour(-aMonster.getArmour());
        // Set the armour at zero
        aMonster.offsetHealth(-remainderDmg);
      } // else
    }
    else
    // If the monster has no armour
      aMonster.offsetHealth(-dmgAmount);
  } // if
  else
    strcat(turnResult, "misses!| ");
} // playerTurn



void monsterTurn(monster &aMonster,     // The attacking monster
                 player &userPlayer,    // The player
                 char turnResult[40],   // The result of the turn
                 bool pBlocking)        // If the player is blocking
// An attack turn for the monster
{
  srand(GetTickCount());         // Seed randomize for time

  int randOffset = rand()%20+60;
  for (int rCount = 0; rCount < randOffset; rCount++)
  // Offset the random numbers
    randOffset = rand()%40+90;

  float randHit = rand()%100+1;
  char dmgAmountStr[20];        // Amount of damage in string form
  int dmgAmount;                // Amount of damage in integer form

  strcpy(turnResult, aMonster.getName());
  strcat(turnResult, "| (");
  strcat(turnResult, aMonster.getCurrentWeapon().getName());
  strcat(turnResult, ")| ");

  if (randHit <= aMonster.getAccuracy()*100)
  // If the attack hit
  {
    itoa(aMonster.getCurrentWeapon().getStrength(), dmgAmountStr, 10);
    dmgAmount = aMonster.getCurrentWeapon().getStrength();

    if (pBlocking)
    // If the player's blocking, adjust damage amount accordingly
      dmgAmount -= int(userPlayer.getCurrentWeapon().getStrength() * 0.65);

    strcat(turnResult, "hits| ");
    strcat(turnResult, userPlayer.getName());
    strcat(turnResult, ",| damaging| him| -");
    strcat(turnResult, dmgAmountStr);
    strcat(turnResult, "!");

    if (userPlayer.getArmour() > 0)
    // If the player has armour
    {
      if (userPlayer.getArmour() >= dmgAmount/2)
      // If the player has enough armour, divide equally between
      {
        userPlayer.offsetArmour(-dmgAmount/2);
        userPlayer.offsetHealth(-dmgAmount/2);
      }
      else
      // If the player doesn't have enough armour
      {
        int remainderDmg = dmgAmount/2 - userPlayer.getArmour();
        userPlayer.offsetArmour(-userPlayer.getArmour());
        // Set the armour at zero
        userPlayer.offsetHealth(-remainderDmg);
      } // else
    }
    else
    // If the player has no armour
      userPlayer.offsetHealth(-dmgAmount);
  } // if
  else
    strcat(turnResult, "misses!");
} // monsterTurn






void msgBox(char question[],             // The question to be asked
            int type,                    // 0-Boolean, 1-Info, 2-Options
            char responseDesc[],         // Response description
            char iOptions[],             // Input options
            int &response)               // The response to the message box
// Create a message box and display it
{
  CHAR_INFO mBoxBuffer[MBOX_WIDTH * MBOX_HEIGHT] = {0};
  SMALL_RECT drawRect = {25, 7, MBOX_WIDTH + 24, MBOX_HEIGHT + 6};
  COORD bufferSize = {MBOX_WIDTH, MBOX_HEIGHT}; // Size of the buffer
  COORD drawCoords = {0, 0}; // Coordinates to be drawn to
  COORD initCursorPos = {0, 0};



  HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  char outputArray[MBOX_HEIGHT][MBOX_WIDTH];   // Preliminary output array
  bool responded = false;
  char responseSpc = 177;
  int rSpcSt[2];                // The start coordinate of the response space

  initMsgBox(outputArray,   // The output array
             type,          // 0-Boolean, 1-Info, 2-Options
             question,      // The question to be asked
             responseDesc,  // Response description
             rSpcSt);       // The start coordinate of the response space
  // Initiate question and response options


  COORD cursorPos = {rSpcSt[0]+25, rSpcSt[1]+7};

  do
  {
    for (int aRowAssign = 0; aRowAssign < MBOX_HEIGHT; aRowAssign++)
    {
      for (int aColAssign = 0; aColAssign < MBOX_WIDTH; aColAssign++)
      {
        mBoxBuffer[aColAssign + aRowAssign * MBOX_WIDTH].Char.AsciiChar =
          outputArray[aRowAssign][aColAssign];
        // Set the current character

        if (outputArray[aRowAssign][aColAssign] != responseSpc)
        // If it's not the response box
          mBoxBuffer[aColAssign + aRowAssign * MBOX_WIDTH].Attributes =
            FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED |
            FOREGROUND_INTENSITY;
          // Set the current colour
        else
        // If it is the response box
          mBoxBuffer[aColAssign + aRowAssign * MBOX_WIDTH].Attributes =
            BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED |
            BACKGROUND_INTENSITY;
        // Set the current colour
      }
    } // for

    WriteConsoleOutput(outputHandle, mBoxBuffer, bufferSize, drawCoords,
                       &drawRect);

    SetConsoleCursorPosition(outputHandle, cursorPos);

    if (type != 1)
      setCursorOn();          // Turns the cursor on


    responded = getMsgBoxResponse(response,    // The response
                                  type,        // 0-Boolean, 1-Info, 2-Options
                                  iOptions);   // Options for input
    // Get the response to the message box from the user
  } while (!responded);

  SetConsoleCursorPosition(outputHandle, initCursorPos);
  setCursorOff();          // Turns the cursor off
} // msgBox



void initMsgBox(char outputArray[][MBOX_WIDTH],  // The output array
                int type,                        // 0-Boolean, 1-Info, 2-Options
                char question[],                 // The question to be asked
                char responseDesc[],             // Response description
                int rSpcSt[2])                   // Start coord:response space
// Initiate question and response options
{
  char message[60];               // Original message container
  char oldMessage[60];            // First part of tokenized message
  bool messageWritten = false;    // Has the message been put out yet?
  int msgStartPoint;              // The starting point on a line of a message
  int msgEndPoint;                // The ending point on a line of a message
  int descStartPoint;             // Starting point of a description
  int descEndPoint;               // Ending point of a description

  char blank = 32;           // Blank char
  char border = 219;         // Border char for the message box
  char responseSpc = 177;      // The space set out for the response

  strcpy(message, question);

  for (int aRowAssign = 0; aRowAssign < MBOX_HEIGHT; aRowAssign++)
  {
    for (int aColAssign = 0; aColAssign < MBOX_WIDTH; aColAssign++)
      outputArray[aRowAssign][aColAssign] = blank;
  } // for

  for (int aRowAssign = 0; aRowAssign < MBOX_HEIGHT; aRowAssign++)
  {
    if (aRowAssign == 0 || aRowAssign == MBOX_HEIGHT - 1)
    {
      for (int aColAssign = 0; aColAssign < MBOX_WIDTH; aColAssign++)
        outputArray[aRowAssign][aColAssign] = border;
    } // if
    else
    {
      outputArray[aRowAssign][0] = border;
      if ((aRowAssign == 2 || aRowAssign == 3) && !messageWritten)
      // If the current row is row 3 or 4 and the message hasn't been written
      {
        if (strlen(message) > MBOX_WIDTH - 4)
        // If the message will be two lines long
        {
          if (aRowAssign == 2)
          // If it's still the first line of the message
          {
            strcpy(oldMessage, message);

            strcpy(oldMessage, strtok(oldMessage, "|"));
            // Set first word of first line

            while (strlen(oldMessage) <= strlen(message)/2)
            // Set the rest of the first line
              strcat(oldMessage, strtok(NULL, "|"));
              // Set the next word in the line


            strcpy(message, strtok(NULL, "|"));
            // Set first word of second line
            char* addition = strtok(NULL, "|");
            while (addition != NULL)
            // Set the rest of the second line
            {
              strcat(message, addition);
              addition = strtok(NULL, "|");
            } // while

            msgStartPoint = MBOX_WIDTH / 2 - strlen(oldMessage) / 2;
            // End point of first line of message
            msgEndPoint = MBOX_WIDTH / 2 + strlen(oldMessage) / 2 + 1;
            // End point of first line of message

            int msgCounter = 0;  // To keep in sync with assChar
            for (int assChar = msgStartPoint; assChar < msgEndPoint; assChar++)
            {
              outputArray[aRowAssign][assChar] = oldMessage[msgCounter];
              msgCounter++;
            } // for
          } // if
          else
          // If it's the second line of the message
          {
            msgStartPoint = MBOX_WIDTH / 2 - strlen(message) / 2;
            // End point of second line of message
            msgEndPoint = MBOX_WIDTH / 2 + strlen(message) / 2;
            // End point of second line of message

            int msgCounter = 0;  // To keep in sync with assChar
            for (int assChar = msgStartPoint; assChar <= msgEndPoint; assChar++)
            {
              outputArray[aRowAssign][assChar] = message[msgCounter];
              msgCounter++;
            } // for
            messageWritten = true;
          } // else
        } // if
        else
        // If the message is only one line long
        {
          msgStartPoint = MBOX_WIDTH / 2 - strlen(message) / 2;
          // End point of line of message
          msgEndPoint = MBOX_WIDTH / 2 + strlen(message) / 2;
          // End point of line of message

          int msgCounter = 0;  // To keep in sync with assChar
          for (int assChar = msgStartPoint; assChar <= msgEndPoint; assChar++)
          {
            outputArray[aRowAssign][assChar] = message[msgCounter];
            msgCounter++;
          } // for
          messageWritten = true;
        } // else
      } // if
      else if (aRowAssign == 4)
      // If the current row describes the response required
      {
        descStartPoint = MBOX_WIDTH / 2 - strlen(responseDesc) / 2;
        // End point of line of description
        descEndPoint = MBOX_WIDTH / 2 + strlen(responseDesc) / 2;
        // End point of line of description

        int descCounter = 0;  // To keep in sync with assChar
        for (int assChar = descStartPoint; assChar <= descEndPoint; assChar++)
        {
          outputArray[aRowAssign][assChar] = responseDesc[descCounter];
          if (type != 1)
          // If it's not an information box, make a response space and
          // set cursor position via that
          {
            outputArray[aRowAssign + 1][assChar] = responseSpc;
            rSpcSt[0] = descStartPoint;
            rSpcSt[1] = aRowAssign + 1;
          }
          descCounter++;
        } // for
      } // else if
      else if (aRowAssign == 5 && type == 1)
      // If the current row is the response row and it's an info box
      {
        char okay[] = {"OK"};
        int okCounter = 0;

        for (int aColAssign = 12; aColAssign <= 20; aColAssign++)
        {
          if (aColAssign != 15 && aColAssign != 16)
            outputArray[aRowAssign][aColAssign] = responseSpc;
          else
          {
            outputArray[aRowAssign][aColAssign] = okay[okCounter];
            okCounter++;
          } // else
        } // for

        rSpcSt[0] = -22;
        rSpcSt[1] = 14;
      } // else if
      outputArray[aRowAssign][MBOX_WIDTH-1] = border;
    } // else
  } // for
} // initMsgBox


bool getMsgBoxResponse(int &response,    // The response
                       int type,         // 0-Boolean, 1-Info, 2-Options
                       char iOptions[])  // Options for input
// Get the response to the message box from the user
{
  char inputString[80];        // The string of input
  char truncChar;              // The truncated string

  if (type != 1)
    cin >> inputString;
  else
    system("PAUSE");

  truncChar = tolower(inputString[0]);
  // Truncate the input to one character and change to lowercase

  if (type == 0)
  // If the message box is boolean
  {
    if (truncChar == iOptions[0] || truncChar == iOptions[1])
    {
      if (truncChar == iOptions[1])
        response = true;
      else
        response = false;
      return true;
    } // if
  } // if
  else if (type == 1)
  // If the message box is an info box
    return true;
  else if (type == 2)
  // If the message box contains different options
  {
    bool bOptionPicked = false;
    int optionPicked;
    int numOpts = strlen(iOptions);

    for (int optCount = 0; optCount < numOpts; optCount++)
    {
      if (truncChar == iOptions[optCount])
      {
        bOptionPicked = true;
        optionPicked = optCount;
      } // if
    } // for

    if (bOptionPicked)
    {
      response = optionPicked;
      return true;
    } // if
  } // else if

  return false;
} // getMsgboxResponse






void seqBox(char sequenceMsg[],           // The sequence box's message
            int type,                     // 0-Boolean, 1-Info, 2-Options
            char responseDesc[],          // Response description
            char iOptions[],              // Input options
            int &response)               // The response to the seq box
// Create a sequence box and display it
{
  CHAR_INFO sBoxBuffer[SBOX_WIDTH * SBOX_HEIGHT] = {0};
  SMALL_RECT drawRect = {1, 1, SBOX_WIDTH, SBOX_HEIGHT};
  COORD bufferSize = {SBOX_WIDTH, SBOX_HEIGHT}; // Size of the buffer
  COORD drawCoords = {0, 0}; // Coordinates to be drawn to
  COORD initCursorPos = {0, 0};
  

  HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  char outputArray[SBOX_HEIGHT][SBOX_WIDTH];   // Preliminary output array
  bool responded = false;
  char responseSpc = 177;
  int rSpcSt[2];           // Start coords for the response space

  initSeqBox(outputArray,   // The output array
             type,          // 0-Boolean, 1-Info, 2-Options
             sequenceMsg,   // The question to be asked
             responseDesc,  // Response description
             rSpcSt);       // Start coords for response space
  // Initiate question and response options


  COORD cursorPos = {rSpcSt[0]+1, rSpcSt[1]+1};
  
  do
  {
    for (int aRowAssign = 0; aRowAssign < SBOX_HEIGHT; aRowAssign++)
    {
      for (int aColAssign = 0; aColAssign < SBOX_WIDTH; aColAssign++)
      {
        sBoxBuffer[aColAssign + aRowAssign * SBOX_WIDTH].Char.AsciiChar =
          outputArray[aRowAssign][aColAssign];
        // Set the current character

        if (outputArray[aRowAssign][aColAssign] != responseSpc)
        // If it's not the response box
          sBoxBuffer[aColAssign + aRowAssign * SBOX_WIDTH].Attributes =
            FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED |
            FOREGROUND_INTENSITY;
          // Set the current colour
        else
        // If it is the response box
          sBoxBuffer[aColAssign + aRowAssign * SBOX_WIDTH].Attributes =
            BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED |
            BACKGROUND_INTENSITY;
        // Set the current colour
      }
    } // for

    WriteConsoleOutput(outputHandle, sBoxBuffer, bufferSize, drawCoords,
                       &drawRect);

    SetConsoleCursorPosition(outputHandle, cursorPos);

    if (type != 1)
      setCursorOn();          // Turns the cursor on

    responded = getSeqBoxResponse(response,     // The response
                                  type,         // 0-Boolean, 1-Info, 2-Options
                                  iOptions);    // Options for input
    // Get the response to the sequence box from the user
  } while (!responded);

  setCursorOff();          // Turns the cursor off
  SetConsoleCursorPosition(outputHandle, initCursorPos);
} // seqBox



void initSeqBox(char outputArray[][SBOX_WIDTH], // The output array
                int type,                       // 0-Boolean, 1-Info, 2-Options
                char sequenceMsg[],             // The sequence message
                char responseDesc[],            // Response description
                int rSpcSt[2])                  // Start coords:response space
// Initiate question and response options
{
  char currMessage[800];          // Current line of tokenized message
  bool messageWritten = false;    // Has the message been put out yet?
  int msgLineNum = 0;             // The line number of the message
  int msgStartPoint;              // The starting point on a line of a message
  int msgEndPoint;                // The ending point on a line of a message
  int descStartPoint;             // Starting point of a description
  int descEndPoint;               // Ending point of a description

  char blank = 32;           // Blank char
  char border = 219;         // Border char for the message box
  char responseSpc = 177;      // The space set out for the response

  for (int aRowAssign = 0; aRowAssign < SBOX_HEIGHT; aRowAssign++)
  {
    for (int aColAssign = 0; aColAssign < SBOX_WIDTH; aColAssign++)
      outputArray[aRowAssign][aColAssign] = blank;
  } // for

  for (int aRowAssign = 0; aRowAssign < SBOX_HEIGHT; aRowAssign++)
  {
    if (aRowAssign == 0 || aRowAssign == SBOX_HEIGHT - 1)
    {
      for (int aColAssign = 0; aColAssign < SBOX_WIDTH; aColAssign++)
        outputArray[aRowAssign][aColAssign] = border;
    } // if
    else
    {
      outputArray[aRowAssign][0] = border;
      if (aRowAssign == 2 && !messageWritten)
      // If the current row is a message row and the message hasn't been written
      {
        strcpy(currMessage, sequenceMsg);

        char* addition = strtok(currMessage, "|");

        do
        {
          strcpy(currMessage, addition);
          // Set first word of current line

          addition = strtok(NULL, "|");

          while (addition != NULL &&
                 strlen(currMessage) + strlen(addition) <= SBOX_WIDTH - 4)
          // Set the rest of the current line
          {
            strcat(currMessage, addition);
            // Set the next word in the line
            addition = strtok(NULL, "|");
          } // while


          msgStartPoint = SBOX_WIDTH / 2 - strlen(currMessage) / 2;
          // End point of first line of message
          msgEndPoint = SBOX_WIDTH / 2 + strlen(currMessage) / 2 + 1;
          // End point of first line of message

          int msgCounter = 0;  // To keep in sync with assChar
          for (int assChar = msgStartPoint; assChar < msgEndPoint; assChar++)
          {
            outputArray[aRowAssign + msgLineNum][assChar]
            = currMessage[msgCounter];
            msgCounter++;
          } // for

          msgLineNum++;

          strcpy(currMessage, "");

        } while (addition != NULL);

        messageWritten = true;
      } // if
      else if (aRowAssign == 15)
      // If the current row describes the response required
      {
        descStartPoint = SBOX_WIDTH / 2 - strlen(responseDesc) / 2;
        // End point of line of description
        descEndPoint = SBOX_WIDTH / 2 + strlen(responseDesc) / 2;
        // End point of line of description

        int descCounter = 0;  // To keep in sync with assChar
        for (int assChar = descStartPoint; assChar <= descEndPoint; assChar++)
        {
          outputArray[aRowAssign][assChar] = responseDesc[descCounter];

          if (type != 1)
          // If it's not an information box, make a response space and
          // set cursor position via that
          {
            outputArray[aRowAssign + 1][assChar] = responseSpc;
            rSpcSt[0] = descStartPoint;
            rSpcSt[1] = aRowAssign + 1;
          } // if
          descCounter++;
        } // for
      } // else if
      else if (aRowAssign == 17 && type == 1)
      // If the current row is the response row (Y / N)
      {
        char okay[] = {"OK"};
        int okCounter = 0;

        for (int aColAssign = 31; aColAssign <= 39; aColAssign++)
        {
          if (aColAssign != 34 && aColAssign != 35)
            outputArray[aRowAssign][aColAssign] = responseSpc;
          else
          {
            outputArray[aRowAssign][aColAssign] = okay[okCounter];
            okCounter++;
          } // else
        } // for

        rSpcSt[0] = 1;
        rSpcSt[1] = aRowAssign + 1;
      } // else if
      outputArray[aRowAssign][SBOX_WIDTH-1] = border;
    } // else
  } // for
} // initSeqBox


bool getSeqBoxResponse(int &response,      // The response
                       int type,           // 0-Boolean, 1-Info, 2-Options
                       char iOptions[])    // Options for input
// Get the response to the sequence box from the user
{
  char inputString[80];        // The string of input
  char truncChar;              // The truncated string

  if (type != 1)
    cin >> inputString;
  else
    system("PAUSE");

  truncChar = tolower(inputString[0]);
  // Truncate the input to one character and change to lowercase

  if (type == 0)
  // If the sequence box is boolean
  {
    if (truncChar == iOptions[0] || truncChar == iOptions[1])
    {
      if (truncChar == iOptions[1])
        response = true;
      else
        response = false;
      return true;
    } // if
  } // if
  else if (type == 1)
  // If the sequence box is an info box
    return true;
  else if (type == 2)
  // If the sequence box contains different options
  {
    bool bOptionPicked = false;
    int optionPicked;
    int numOpts = strlen(iOptions);

    for (int optCount = 0; optCount < numOpts; optCount++)
    {
      if (truncChar == iOptions[optCount])
      {
        bOptionPicked = true;
        optionPicked = optCount;
      } // if
    } // for

    if (bOptionPicked)
    {
      response = optionPicked;
      return true;
    } // if
  } // else if

  return false;
} // getSeqBoxResponse





void setCursorOff()
// Sets the cursor to invisible
{
  HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;

  GetConsoleCursorInfo(outputHandle, &cursorInfo);

  if (cursorInfo.bVisible)
    cursorInfo.bVisible = false;
  SetConsoleCursorInfo (outputHandle, &cursorInfo);
} // setCursorOff


void setCursorOn()
// Sets the cursor to visible
{
  HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;

  GetConsoleCursorInfo(outputHandle, &cursorInfo);

  if (!cursorInfo.bVisible)
    cursorInfo.bVisible = true;
  SetConsoleCursorInfo (outputHandle, &cursorInfo);
} // setCursorOn
