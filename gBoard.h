const int V_BOARD_SIZE = 20;
const int H_BOARD_SIZE = 50;

const char WALL = 219;
const char CLSN = 177; // Temporary collision character
const char BLKSPC = 32;
const char PLAYER = 12;

const char M_SPIDER = 15;
const char M_GORGON = 225;
const char M_GRUELLER = 234;
const char M_SNAKE = 235;
const char M_DUPLED = 236;
const char M_DEOTAPHT = 228;
const char M_MACHEPOR = 233;
const char M_FRIPP = 237;
// Monsters, in order of descending difficulty

const char NPC = 2;
const char I_HEALTH = 3;
const char I_OTHER = 4;


void initGameBoard(char gameBoard[][H_BOARD_SIZE],   // The game board
                   int levelComplexity); // Compexity of the level (1-6)
// Fills the game board and randomizes the layout



void fillGBoard(char gameBoard[][H_BOARD_SIZE]);     // The game board
// Fills the game board with empty spaces



void borderGBoard(char gameBoard[][H_BOARD_SIZE]);   // The game board
// Makes a one-character border around the edge of the game board



void randomizeBoardLayout(char gameBoard[][H_BOARD_SIZE],   // The game board
                          int levelComplexity); // Compexity of the level (1-7)
// Randomizes the game board's layout


void setCollision(char gameBoard[][H_BOARD_SIZE]);     // The game board
// Sets a collision barrier adjacent to wall squares



bool testCurrentWall(char gameBoard[][H_BOARD_SIZE],   // The game board
                     int startVCoord, // The vertical starting coordinate
                     int startHCoord, // The horizontal starting coordinate
                     int endVCoord,   // The vertical end coordinate
                     int endHCoord,   // The horizontal end coordinate
                     bool firstWall); // Is it the first wall in the run?
// Tests the current wall to be placed for validity (0 - invalid, 1 - valid)

void insertCurrentWall(char gameBoard[][H_BOARD_SIZE], // The game board
                       int startVCoord, // The vertical starting coordinate
                       int startHCoord, // The horizontal starting coordinate
                       int endVCoord,   // The vertical end coordinate
                       int endHCoord);  // The horizontal end coordinate
// Inserts the current wall into the game board


void removeCollision(char gameBoard[][H_BOARD_SIZE]);  // The game board
// Removes the collision from the game board





void drawPlayer(char gameBoard[][H_BOARD_SIZE], // The game board
                int* playerCoords);             // The player's coordinates
// Draws the player to the game board


void drawMonster(char gameBoard[][H_BOARD_SIZE], // The game board
                 int* monsterCoords,             // The monster's coords
                 int monsterType);               // The type of monster
// Draws a monster to the game board


void drawNPC(char gameBoard[][H_BOARD_SIZE], // The game board
             int* npcCoords);                // The NPC's coordinates
// Draws a non-player character to the game board


void drawItem(char gameBoard[][H_BOARD_SIZE], // The game board
              int* itemCoords,                // The item's coordinates
              bool itemType);                 // 0-Health, 1-Other
// Draws an item to the game board


void removeObject(char gameBoard[][H_BOARD_SIZE], // The game board
                  int* remCoords); // Coordinates of the char to be removed
// Removes an object from the game board




void setColour(int colourType,   // The type of character that is being coloured
               int monsterType,  // Type:monster being coloured (if necessary)
               CHAR_INFO gBoardBuffer[], // The game board buffer
               int vCharCoord,  // The verti. coord of the char
               int hCharCoord); // The horiz. coord of the char
// Sets colour based upon character types


void printGameBoard(char gameBoard[][H_BOARD_SIZE]);   // The game board
// Prints the game board


void printBackground();
// Prints a background


void drawAllElements(char gameBoard[][H_BOARD_SIZE]);  // The game board
// Draws all elements on screen

void drawVolatileElements(char gameBoard[][H_BOARD_SIZE]);  // The game board
// Draws elements that change often on screen


/*
int main()
{
  char gameBoard[V_BOARD_SIZE][H_BOARD_SIZE];

  initGameBoard(gameBoard, 8);

  removeCollision(gameBoard);

  printGameBoard(gameBoard);

  system("PAUSE");
  return 0;
} // main
*/


void initGameBoard(char gameBoard[][H_BOARD_SIZE],
                   int levelComplexity) // The complexity of the level (1-6)
// Fills the game board and randomizes the layout
{
  fillGBoard(gameBoard);                   // The game board
  // Fills the game board with empty spaces

  borderGBoard(gameBoard);                 // The game board
  // Creates a one-character collision barrier around the walls to ensure that
  // no one wall collides with another

  randomizeBoardLayout(gameBoard,          // The game board
                       levelComplexity);   // The complexity of the level (1-6)
  // Randomizes the board layout

  removeCollision(gameBoard);              // The game board
  // Removes the one-character collision barrier around the walls
} // initGameBoard



void fillGBoard(char gameBoard[][H_BOARD_SIZE])
// Fills the game board with empty spaces
{
  for (int vCount = 0; vCount < V_BOARD_SIZE; vCount++)
  {
    for (int hCount = 0; hCount < H_BOARD_SIZE; hCount++)
    {
      gameBoard[vCount][hCount] = BLKSPC;
    } // for
  } // for
} // fillGBoard



void borderGBoard(char gameBoard[][H_BOARD_SIZE])
// Makes a one-character border around the edge of the game board
{
  for (int vCount = 0; vCount < V_BOARD_SIZE; vCount++)
  {
    gameBoard[vCount][0] = WALL;                      // Makes the left...
    gameBoard[vCount][H_BOARD_SIZE - 1] = WALL;       // ... and right borders
  } // for

  for (int hCount = 0; hCount < H_BOARD_SIZE; hCount++)
  {
    gameBoard[0][hCount] = WALL;                      // Makes the top...
    gameBoard[V_BOARD_SIZE - 1][hCount] = WALL;       // ... and bottom borders
  } // for

  setCollision(gameBoard);
} // borderGBoard



void setCollision(char gameBoard[][H_BOARD_SIZE])
// Sets a collision barrier adjacent to wall squares
{
  for (int vCount = 0; vCount < V_BOARD_SIZE; vCount++)
  {
    for (int hCount = 0; hCount < H_BOARD_SIZE; hCount++)
    {
      if (gameBoard[vCount][hCount] == WALL)
      // If the current char is a wall char
      {
        for (int offset = -1; offset <= 1; offset++)
        {
          if (!(vCount + offset < 0 || vCount + offset >= V_BOARD_SIZE))
          // If the current vertical character plus the offset doesn't exceed
          // the board size and isn't below zero
          {
            if (gameBoard[vCount + offset][hCount] != WALL)
              gameBoard[vCount + offset][hCount] = CLSN;
          } // if

          if (!(hCount + offset < 0 || hCount + offset >= H_BOARD_SIZE))
          // If the current horizontal character plus the offset doesn't exceed
          // the board size and isn't below zero
          {
            if (gameBoard[vCount][hCount + offset] != WALL)
              gameBoard[vCount][hCount + offset] = CLSN;
          } // if

          if ((!(hCount + offset < 0 || hCount + offset >= H_BOARD_SIZE)) &&
             (!(vCount + offset < 0 || vCount + offset >= V_BOARD_SIZE)))
          // If the current horizontal character plus the offset doesn't exceed
          // the board size and isn't below zero and the current vertical
          // character plus the offset doesn't exceed the board size and isn't
          // below zero
          {
            if (gameBoard[vCount + offset][hCount + offset] != WALL)
              gameBoard[vCount + offset][hCount + offset] = CLSN;
          }

          if ((!(hCount - offset < 0 || hCount - offset >= H_BOARD_SIZE)) &&
             (!(vCount + offset < 0 || vCount + offset >= V_BOARD_SIZE)))
          // If the current horizontal character plus the offset doesn't exceed
          // the board size and isn't below zero and the current vertical
          // character plus the offset doesn't exceed the board size and isn't
          // below zero
          {
            if (gameBoard[vCount + offset][hCount - offset] != WALL)
              gameBoard[vCount + offset][hCount - offset] = CLSN;
          }

          if ((!(hCount + offset < 0 || hCount + offset >= H_BOARD_SIZE)) &&
             (!(vCount - offset < 0 || vCount - offset >= V_BOARD_SIZE)))
          // If the current horizontal character plus the offset doesn't exceed
          // the board size and isn't below zero and the current vertical
          // character plus the offset doesn't exceed the board size and isn't
          // below zero
          {
            if (gameBoard[vCount - offset][hCount + offset] != WALL)
              gameBoard[vCount - offset][hCount + offset] = CLSN;
          }

        } // for
      } // if
    } // for
  } // for
} // setCollision




void randomizeBoardLayout(char gameBoard[][H_BOARD_SIZE],
                          int levelComplexity) // Complexity of the level (1-6)
// Randomizes the game board's layout
{
  srand(GetTickCount());         // Seed randomize from tick count
  int totalWRuns = rand()%5+(levelComplexity*10);
  // How many times to place sets of walls

  for (int wallRunCount = 0; wallRunCount < totalWRuns; wallRunCount++)
  {
    bool origDir = rand()%2;    // First wall's direction
    bool currWallValid = 0;     // 0 - invalid, 1 - valid
    bool overtested = 0;        // If an iteration is tested more than 100 times
    int runWalls = rand()%3+1;  // How many walls to place in the current run
    int randomVCoord, randomHCoord;  // Random verti. and horiz. coords
    int endVCoord, endHCoord;        // Verti. and horiz. ending coordinates
    int testCount = 0;               // Number of times an iteration is tested

    for (int wallCount = 0; wallCount < runWalls; wallCount++)
    {
        do
        // Until a valid wall is found, keep randomizing
        {
          do
          // Picks a random spot on an existing wall to start a new wall with
          {
            randomVCoord = rand()%V_BOARD_SIZE;
            randomHCoord = rand()%H_BOARD_SIZE;
          } while (gameBoard[randomVCoord][randomHCoord] != WALL);

          if (origDir)
          // If the wall to be placed is vertical
          {
            int currWallLength = rand()%(H_BOARD_SIZE-5)+2;

            endHCoord = randomHCoord + currWallLength;
            if (!(endHCoord >= 2 && endHCoord <=(H_BOARD_SIZE-3)))
            // Make sure that the wall isn't going the wrong way
              endHCoord = randomHCoord - currWallLength;


            currWallValid = testCurrentWall(gameBoard,     // The game board
                                            randomVCoord,  // Start v. coord
                                            randomHCoord,  // Start h. coord
                                            randomVCoord,  // End v. coord
                                            endHCoord,     // End h. coord
                                            bool(!wallCount)); // First wall?
          } // if
          else
          // If the wall to be placed is horizontal
          {
            int currWallLength = rand()%(V_BOARD_SIZE-5)+2;

            endVCoord = randomVCoord + currWallLength;
            if (!(endVCoord >= 2 && endVCoord <=(V_BOARD_SIZE-3)))
            // Make sure that the wall isn't going the wrong way
              endVCoord = randomVCoord - currWallLength;

            currWallValid = testCurrentWall(gameBoard,     // The game board
                                            randomVCoord,  // Start v. coord
                                            randomHCoord,  // Start h. coord
                                            endVCoord,     // End v. coord
                                            randomHCoord,  // End h. coord
                                            bool(!wallCount)); // First wall?
          } // else

        if (!currWallValid)
          testCount++;
        if (testCount == 100)
          overtested = true;

        } while (!currWallValid && !overtested);

        if (!overtested)  // If the iteration hasn't been tested over 100 times
        {
          if (origDir)
            insertCurrentWall(gameBoard,     // The game board
                              randomVCoord,  // Start v. coord
                              randomHCoord,  // Start h. coord
                              randomVCoord,  // End v. coord
                              endHCoord);    // End h. coord
          else
            insertCurrentWall(gameBoard,     // The game board
                              randomVCoord,  // Start v. coord
                              randomHCoord,  // Start h. coord
                              endVCoord,     // End v. coord
                              randomHCoord); // End h. coord
        } // if
      currWallValid = 0;
      setCollision(gameBoard);
    } // for


  } // for
} // randomizeBoardLayout




bool testCurrentWall(char gameBoard[][H_BOARD_SIZE],
                     int startVCoord, // The vertical starting coordinate
                     int startHCoord, // The horizontal starting coordinate
                     int endVCoord,   // The vertical end coordinate
                     int endHCoord,   // The horizontal end coordinate
                     bool firstWall)  // Is it the first wall in the run?
// Tests the current wall to be placed for validity (0 - invalid, 1 - valid)
{
  int credit = 1;
  // How many collision spaces can be overwritten by the wall to be placed

  if (firstWall)
  // If it's the first wall to be placed, allow one more collision space to be
  // overwritten
    credit++;

  if (endVCoord >= startVCoord)
  // If the verti. ending coordinate is higher than the starting coordinate
  {
    for (int vTest = startVCoord; vTest <= endVCoord; vTest++)
    {
      if (endHCoord >= startHCoord)
      // If the horiz. ending coord is higher than the starting coord
      {
        for (int hTest = startHCoord; hTest <= endHCoord; hTest++)
        {
          if (gameBoard[vTest][hTest] == CLSN ||
              gameBoard[vTest][hTest] == WALL)
          // If current character is either a collision character or a wall
          // character
          {
            if (credit)    // If there's any credit left...
              credit--;    // ... subtract from that credit
            else           // If there isn't...
              return 0;    // ... proclaim the invalidity of the wall
          } // if
        } // for
      } // if
      else //if (endHCoord < startHCoord)
      // If the horiz. ending coord is lower than the starting coord
      {
        for (int hTest = startHCoord; hTest >= endHCoord; hTest--)
        {
          if (gameBoard[vTest][hTest] == CLSN ||
              gameBoard[vTest][hTest] == WALL)
          // If current character is either a collision character or a wall
          // character
          {
            if (credit)    // If there's any credit left...
              credit--;    // ... subtract from that credit
            else           // If there isn't...
              return 0;    // ... proclaim the invalidity of the wall
          } // if
        } // for
      } // else
    } // for
  } // if
  else //if (endVCoord < startVCoord)
  // If the verti. ending coordinate is lower than the starting coordinate
  {
    for (int vTest = startVCoord; vTest >= endVCoord; vTest--)
    {
      if (endHCoord >= startHCoord)
      // If the horiz. ending coord is higher than the starting coord
      {
        for (int hTest = startHCoord; hTest <= endHCoord; hTest++)
        {
          if (gameBoard[vTest][hTest] == CLSN ||
              gameBoard[vTest][hTest] == WALL)
          // If current character is either a collision character or a wall
          // character
          {
            if (credit)    // If there's any credit left...
              credit--;    // ... subtract from that credit
            else           // If there isn't...
              return 0;    // ... proclaim the invalidity of the wall
          } // if
        } // for
      } // if
      else //if (endHCoord < startHCoord)
      // If the horiz. ending coord is lower than the starting coord
      {
        for (int hTest = startHCoord; hTest >= endHCoord; hTest--)
        {
          if (gameBoard[vTest][hTest] == CLSN ||
              gameBoard[vTest][hTest] == WALL)
          // If current character is either a collision character or a wall
          // character
          {
            if (credit)    // If there's any credit left...
              credit--;    // ... subtract from that credit
            else           // If there isn't...
              return 0;    // ... proclaim the invalidity of the wall
          } // if
        } // for
      } // else
    } // for
  } // else

  return 1;    // If there are no errors, proclaim the validity of the wall
} // testCurrentWall





void insertCurrentWall(char gameBoard[][H_BOARD_SIZE],
                       int startVCoord, // The vertical starting coordinate
                       int startHCoord, // The horizontal starting coordinate
                       int endVCoord,   // The vertical end coordinate
                       int endHCoord)   // The horizontal end coordinate
// Inserts the current wall into the game board
{
  if (endVCoord >= startVCoord)
  // If the verti. ending coordinate is higher than the starting coordinate
  {
    for (int vCharPlc = startVCoord; vCharPlc <= endVCoord; vCharPlc++)
    {
      if (endHCoord >= startHCoord)
      // If the horiz. ending coord is higher than the starting coord
      {
        for (int hCharPlc = startHCoord; hCharPlc <= endHCoord; hCharPlc++)
          gameBoard[vCharPlc][hCharPlc] = WALL; // Make the current char a wall
      } // if

      else
      // If the horiz. ending coord is lower than the starting coord
      {
        for (int hCharPlc = startHCoord; hCharPlc >= endHCoord; hCharPlc--)
          gameBoard[vCharPlc][hCharPlc] = WALL; // Make the current char a wall
      } // else
    } // for
  } // if

  else
  // If the verti. ending coordinate is lower than the starting coordinate
  {
    for (int vCharPlc = startVCoord; vCharPlc >= endVCoord; vCharPlc--)
    {
      if (endHCoord >= startHCoord)
      // If the horiz. ending coord is higher than the starting coord
      {
        for (int hCharPlc = startHCoord; hCharPlc <= endHCoord; hCharPlc++)
          gameBoard[vCharPlc][hCharPlc] = WALL; // Make the current char a wall
      } // if
      else //if (endHCoord < startHCoord)
      // If the horiz. ending coord is lower than the starting coord
      {
        for (int hCharPlc = startHCoord; hCharPlc >= endHCoord; hCharPlc--)
          gameBoard[vCharPlc][hCharPlc] = WALL; // Make the current char a wall
      } // else
    } // for
  } // else

} // insertCurrentWall



void removeCollision(char gameBoard[][H_BOARD_SIZE])
// Removes the collision from the game board
{
  for (int vCount = 0; vCount < V_BOARD_SIZE; vCount++)
  {
    for (int hCount = 0; hCount < H_BOARD_SIZE; hCount++)
    {
      if (gameBoard[vCount][hCount] == CLSN)   // If there's a collision space
        gameBoard[vCount][hCount] = BLKSPC;    // Set it to a black space
    } // for
  } // for
} // removeCollision






void drawPlayer(char gameBoard[][H_BOARD_SIZE], // The game board
                int playerCoords[])    // The coordinates of the player
// Draws the player to the game board
{
  gameBoard[playerCoords[0]][playerCoords[1]] = PLAYER;
  // Draw the player to his position
} // drawPlayer



void drawMonster(char gameBoard[][H_BOARD_SIZE], // The game board
                 int monsterCoords[],            // The monster's coords
                 int monsterType)                // The type of monster
// Draws a monster to the game board
{
  switch (monsterType)
  {
    case 1:
      gameBoard[monsterCoords[0]][monsterCoords[1]] = M_SPIDER;
      break;
    case 2:
      gameBoard[monsterCoords[0]][monsterCoords[1]] = M_GORGON;
      break;
    case 3:
      gameBoard[monsterCoords[0]][monsterCoords[1]] = M_GRUELLER;
      break;
    case 4:
      gameBoard[monsterCoords[0]][monsterCoords[1]] = M_SNAKE;
      break;
    case 5:
      gameBoard[monsterCoords[0]][monsterCoords[1]] = M_DUPLED;
      break;
    case 6:
      gameBoard[monsterCoords[0]][monsterCoords[1]] = M_DEOTAPHT;
      break;
    case 7:
      gameBoard[monsterCoords[0]][monsterCoords[1]] = M_MACHEPOR;
      break;
    case 8:
      gameBoard[monsterCoords[0]][monsterCoords[1]] = M_FRIPP;
      break;
  } // switch

  // Draw a monster to its position
} // drawMonster



void drawNPC(char gameBoard[][H_BOARD_SIZE], // The game board
             int npcCoords[])                // The npc's coords
// Draws a non-player character to the game board
{
  gameBoard[npcCoords[0]][npcCoords[1]] = NPC;
  // Draw a non-player character to his position
} // drawNPC



void drawItem(char gameBoard[][H_BOARD_SIZE], // The game board
              int itemCoords[],               // The item's coords
              bool itemType)                  // 0-Health, 1-Other
// Draws an item to the game board
{
  if (!itemType)
    gameBoard[itemCoords[0]][itemCoords[1]] = I_HEALTH;
  else
    gameBoard[itemCoords[0]][itemCoords[1]] = I_OTHER;
  // Draw an item to its position
} // drawItem



void removeObject(char gameBoard[][H_BOARD_SIZE], // The game board
                  int remCoords[]) // Coordinates of the char to be removed
// Removes an object from the game board
{
  gameBoard[remCoords[0]][remCoords[1]] = BLKSPC;
  // Draw an empty space where the object was before
} // removeObject






void setColour(int colourType,  // The type of character that is being coloured
               int monsterType, // Type of monster being coloured (if necessary)
               CHAR_INFO gBoardBuffer[], // The game board buffer
               int vCharCoord,  // The verti. coord of the char
               int hCharCoord)  // The horiz. coord of the char
// Sets colour based upon character types
{
  switch (colourType)
  {
    case 1:         // Player
      gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
        FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED |
        FOREGROUND_INTENSITY;
      break;
    case 2:         // Monster
      switch (monsterType)
      {
        case 1:     // Spider
          gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
            FOREGROUND_BLUE | FOREGROUND_RED;
          break;
        case 2:     // Gorgon
          gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
            FOREGROUND_GREEN | FOREGROUND_INTENSITY;
          break;
        case 3:     // Grueller
          gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
            FOREGROUND_RED;
          break;
        case 4:     // Snake
          gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
            FOREGROUND_GREEN;
          break;
        case 5:     // Dupled
          gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
          break;
        case 6:     // Deotapht
          gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
            FOREGROUND_BLUE | FOREGROUND_GREEN;
          break;
        case 7:     // Machepor
          gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
            FOREGROUND_GREEN | FOREGROUND_RED;
          break;
        case 8:     // Fripp
          gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
            FOREGROUND_BLUE | FOREGROUND_INTENSITY;
          break;
      } // switch
      break;
    case 3:         // Item
      gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
        FOREGROUND_BLUE;
      break;
    case 4:         // NPC
      gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
      break;
    case 5:         // Wall
      gBoardBuffer[hCharCoord + vCharCoord * H_BOARD_SIZE].Attributes =
        FOREGROUND_GREEN | FOREGROUND_RED;
      break;
  } // switch
} // setColour




void printGameBoard(char gameBoard[][H_BOARD_SIZE])
// Prints the game board
{
  CHAR_INFO gBoardBuffer[H_BOARD_SIZE * V_BOARD_SIZE] = {0};
  SMALL_RECT drawRect = {2, 1, H_BOARD_SIZE + 1, V_BOARD_SIZE};
  COORD bufferSize = {H_BOARD_SIZE, V_BOARD_SIZE}; // Size of the buffer
  COORD drawCoords = {0, 0}; // Coordinates to be drawn to

  HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  for (int vCount = 0; vCount < V_BOARD_SIZE; vCount++)
  {
    for (int hCount = 0; hCount < H_BOARD_SIZE; hCount++)
    {
      char currentChar = gameBoard[vCount][hCount];
      gBoardBuffer[hCount + vCount * H_BOARD_SIZE].Char.AsciiChar = currentChar;

      if (currentChar != BLKSPC)
      {
        switch (currentChar)
        {
          case PLAYER:
            setColour(1,            // The type of character being coloured
                      0,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case M_SPIDER:
            setColour(2,            // The type of character being coloured
                      1,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case M_GORGON:
            setColour(2,            // The type of character being coloured
                      2,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case M_GRUELLER:
            setColour(2,            // The type of character being coloured
                      3,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case M_SNAKE:
            setColour(2,            // The type of character being coloured
                      4,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case M_DUPLED:
            setColour(2,            // The type of character being coloured
                      5,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case M_DEOTAPHT:
            setColour(2,            // The type of character being coloured
                      6,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case M_MACHEPOR:
            setColour(2,            // The type of character being coloured
                      7,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case M_FRIPP:
            setColour(2,            // The type of character being coloured
                      8,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case I_HEALTH:
            setColour(3,            // The type of character being coloured
                      0,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case I_OTHER:
            setColour(3,            // The type of character being coloured
                      0,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case NPC:
            setColour(4,            // The type of character being coloured
                      0,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
          case WALL:
            setColour(5,            // The type of character being coloured
                      0,            // The type of monster being coloured
                      gBoardBuffer, // The game board buffer
                      vCount,       // The verti. coord of the char
                      hCount);      // The horiz. coord of the char
            // Set the colour for the current character
            break;
        } // switch
      } // if
    } // for
  } // for

  WriteConsoleOutput(outputHandle, gBoardBuffer, bufferSize, drawCoords,
                     &drawRect);

} // printGameBoard

void printBackground()
// Prints a background
{
  int bgWidth = 80;
  int bgHeight = 25;
  CHAR_INFO bgBuffer[bgWidth * bgHeight];
  SMALL_RECT drawRect = {0, 0, bgWidth - 1, bgHeight - 1};
  COORD bufferSize = {bgWidth, bgHeight}; // Size of the buffer
  COORD drawCoords = {0, 0}; // Coordinates to be drawn to

  HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  for (int hCount = 0; hCount < bgHeight; hCount++)
  {
    for (int wCount = 0; wCount < bgWidth; wCount++)
    {
      bgBuffer[wCount + hCount * bgWidth].Char.AsciiChar = 176;
      bgBuffer[wCount + hCount * bgWidth].Attributes =
        FOREGROUND_GREEN | FOREGROUND_RED;
    } // for
  } // for

  WriteConsoleOutput(outputHandle, bgBuffer, bufferSize, drawCoords,
                     &drawRect);
} // printBackground


void drawAllElements(char gameBoard[][H_BOARD_SIZE])  // The game board
// Draws all elements on screen
{
  printBackground();
  printGameBoard(gameBoard);
} // drawElements

void drawVolatileElements(char gameBoard[][H_BOARD_SIZE])  // The game board
// Draws elements that change often on screen
{
  printGameBoard(gameBoard);
} // drawElements


