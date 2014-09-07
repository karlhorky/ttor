#include <iostream.h>
#include <stdlib.h>

class item
{
  protected:
    int type;        // The type of item
    int coords[2];   // The coordinates of the item
    bool dropped;    // If the item is carried by someone or not

  public:
    int getType() {return type;}
    // Gets the type of item
    void setType(int inType) {type = inType;}
    // Sets the type of item
    void getCoords(int outCoords[2]);
    // Gets the coordinates of the item
    void setInitCoords(int inCoords[2]);
    // Sets the initial coordinates of the item
    bool getDropped() {return dropped;}
    // Gets if an item is carried or on the ground
    void setDropped(bool inDropped) {dropped = inDropped;}
    // Sets if an item is carried or on the ground
};


void item::getCoords(int outCoords[2])
// Gets the coordinates of the item
{
  for (int assignCount = 0; assignCount <= 1; assignCount++)
    outCoords[assignCount] = coords[assignCount];
} // item::getCoords

void item::setInitCoords(int inCoords[2])
// Sets the initial coordinates of the item
{
  for (int assignCount = 0; assignCount <= 1; assignCount++)
    coords[assignCount] = inCoords[assignCount];
} // item::setInitCoords



class weapon : public item
{
  private:
    char* name;
    int level;
    int strength;

  public:
    weapon() {setType(3);}
    // Default constructor
    char* getName() {return name;}
    // Returns the weapon's name
    int getLevel() {return level;}
    // Returns the weapon's level
    int getStrength() {return strength;}
    // Returns the weapon's strength
    void setWeapon(int weaponType, int weaponLevel);
    // Sets all attributes of a weapon
    void setType(int weaponType);
    // Sets the type and name of weapon
    void setLevel(int weaponLevel) {level = weaponLevel;}
    // Sets the level of weapon
    void setStrength(int weaponType);
    // Sets the strength of the weapon
};

void weapon::setWeapon(int weaponType, int weaponLevel)
// Sets all attributes of a weapon
{
  setType(weaponType);
  setLevel(weaponLevel);
  setStrength(weaponType);
} // weapon::setWeapon

void weapon::setType(int weaponType)
// Sets the type and name of weapon
{
  switch(weaponType)
  {
    case 1:
      name = "club";
      break;

    case 2:
      name = "dagger";
      break;

    case 3:
      name = "staff";
      break;

    case 4:
      name = "throwing Stars";
      break;

    case 5:
      name = "nunchuks";
      break;

    case 6:
      name = "throwing Knives";
      break;

    case 7:
      name = "mace";
      break;

    case 8:
      name = "bow and arrow";
      break;

    case 9:
      name = "longsword";
      break;

    case 10:
      name = "double-handed broadsword";
      break;

  } // switch
} // weapon::setType

void weapon::setStrength(int weaponType)
// Sets the strength of the weapon
{
strength = weaponType * 3 + int(level / 2);
} // weapon::setStrength






class baseCharacter
// Character with common attributes and methods
{
  protected:
    char* name;                       // The name of the character
    int health;                       // The health of the character
    int potentialHealth;              // The potential health at full
    int armour;                       // The armour of the character
    int potentialArmour;              // The potential armour at full
    int gold;                         // The amount of gold carried
    weapon currentWeapon;             // The current weapon held
    float accuracy;                   // Accuracy with a weapon

    int coords[2];                    // Coordinates of the character


  public:
    baseCharacter() {}
    // Default constructor

    char* getName() {return name;}
    // Gets the character's name
    void setName(char* inName) {name = inName;}
    // Sets the character's name

    int getHealth() {return health;}
    // Gets the character's health
    int getArmour() {return armour;}
    // Gets the character's armour
    int getPotHealth() {return potentialHealth;}
    // Gets the character's potential health at full
    int getPotArmour() {return potentialArmour;}
    // Gets the character's potential armour at full
    void setInitHealth(int inHealth);
    // Sets initial health and potential health
    void setInitArmour(int inArmour);
    // Sets initial armour and potential armour
    void setPotHealth(int inHealth) {potentialHealth = inHealth;}
    // Sets the character's potential health at full
    void setPotArmour(int inArmour) {potentialArmour = inArmour;}
    // Sets the character's potential armour at full
    void offsetHealth(int inHealth) {health += inHealth;}
    // Offsets current health by inHealth
    void offsetArmour(int inArmour) {armour += inArmour;}
    // Offsets current armour by inArmour

    int getGold() {return gold;}
    // Gets the gold carried
    void setInitGold(int inGold) {gold = inGold;}
    // Set the initial gold carried
    void offsetGold(int inGold) {gold += inGold;}
    // Offsets the gold carried

    weapon getCurrentWeapon() {return currentWeapon;}
    // Gets the current weapon
    void setInitWeapon(int weaponType, int weaponLevel);
    // Sets the initial weapon
    void chgWeapon(weapon inWeapon) {currentWeapon = inWeapon;}
    // Changes the weapon to the one put in

    float getAccuracy() {return accuracy;}
    // Returns the accuracy with a weapon of the character
    void setInitAccuracy(float inAccuracy) {accuracy = inAccuracy;}
    // Sets the initial accuracy with a weapon of a character
    void offsetAccuracy(float inAccuracy) {accuracy += inAccuracy;}
    // Offsets the accuracy with a weapon of a character



    void getCoords(int outCoords[2]);
    // Gets the coordinates of the character
    void setInitCoords(int inCoords[2]);
    // Sets the initial coordinates of a baseCharacter
    void offsetCoords(int direction);
    // Offsets the coordinates by one in the direction specified


}; // baseCharacter


void baseCharacter::setInitHealth(int inHealth)
// Sets initial health and potential health
{
  health = inHealth;       // Set initial health
  setPotHealth(inHealth);  // Set potential health
} // baseCharacter::setInitHealth


void baseCharacter::setInitArmour(int inArmour)
// Sets initial armour and potential armour
{
  armour = inArmour;       // Set initial armour
  setPotArmour(inArmour);  // Set potential armour
} // baseCharacter::setInitArmour

void baseCharacter::setInitWeapon(int weaponType, int weaponLevel)
// Sets the initial weapon held by a character
{
  currentWeapon.setWeapon(weaponType, weaponLevel);
} // baseCharacter::setInitWeapon


void baseCharacter::getCoords(int outCoords[2])
// Gets the coordinates of the character
{
  for (int assignCount = 0; assignCount <= 1; assignCount++)
    outCoords[assignCount] = coords[assignCount];
} // baseCharacter::getCoords

void baseCharacter::setInitCoords(int inCoords[2])
// Sets the initial coordinates of a baseCharacter
{
  for (int assignCount = 0; assignCount <= 1; assignCount++)
    coords[assignCount] = inCoords[assignCount];
} // baseCharacter::setInitCoords

void baseCharacter::offsetCoords(int direction)
// Offsets the coordinates by one in the direction specified
{
  switch (direction)
  {
    case 0:    // Up
      coords[0]--;
      break;
    case 1:    // Left
      coords[1]--;
      break;
    case 2:    // Down
      coords[0]++;
      break;
    case 3:    // Right
      coords[1]++;
  }
} // baseCharacter::offsetCoords




class player : public baseCharacter
{
  private:
    bool alignment;                // The player's alignment
  public:
    player(char* playerName,       // The player's name
           bool playerAlignment);  // The player's alignment
    // Constructor

    void setInitPos();
    // Sets the initial position of a player in the level

    void offsetGold(int inGold) {gold += inGold;}
    // Offsets the current gold by inGold

    bool getAlignment() {return alignment;}
    // Returns alignment
};

player::player(char* playerName, bool playerAlignment)
// Constructor
{
  setName(playerName);
  // Set name to that passed in

  alignment = playerAlignment;
  // Set alignment to that passed in

  if (alignment)
  // If player chooses good, balance accordingly
  {
    setInitHealth(120);
    setInitAccuracy(0.35);
  } // if
  else
  // If player chooses evil, give 100 health instead of 120
  {
    setInitHealth(100);
    setInitAccuracy(0.45);
  } // else

  setInitGold(0);         // Set inital gold to zero
  setInitArmour(0);       // Set initial armour to zero
  setPotArmour(100);      // Set potential armour to 100

  setInitWeapon(1, 1);
}; // player::player



void player::setInitPos()
// Sets the initial position of a player in the level
{
  int initPos[2] = {1, 1};
  setInitCoords(initPos);     // Set initial position at the top left
} // player::setInitPos




class monster : public baseCharacter
{
  public:
    monster() {}
    // Default monster constructor
};





class npc : public baseCharacter
// Non-Player Character class
{
  private:
    char* speech;        // The speech uttered by the NPC
    bool speechComplete; // Has the speech been spoken?

  public:
    npc() {health = 10; armour = 0;}
    // Default constructor
    bool getSComplete() {return speechComplete;}
    // Returns if the NPC has spoken his speech yet
    void setSComplete(bool inSComplete) {speechComplete = inSComplete;}
    // Sets if the NPC has spoken his speech yet
    char* getSpeech() {return speech;}
    // Returns the speech of the NPC
    void setSpeech(char* inSpeech) {speech = inSpeech;}
    // Sets the speech of the NPC
}; // npc : public baseCharacter




class objective
{
  private:
    bool type;
    // The type of objective (0 - Item based, 1 - Character based)
    bool objectiveAlignment;
    // The alignment of objective (0 - Good, 1 - Evil)
    //npc objectiveNPC(;
    // The name of the Non-Player Character that gives you the objective
    char* objectiveItem;
    // The item related to the objective (if applicable)
    char* objectiveCharacter;
    // The character related to the objective
    char* objExplain;
    // The text explaining about the objective
    char* completedText;
    // The text printed at completion of an objective
    bool completed;
    // Is the objective completed

  public:
    objective() {completed = false;}                // Default obj constructor
    bool getType() {return type;}                   // Returns the obj. type
    void setType(bool inType) {type = inType;}      // Sets the obj. type
    bool getCompleted() {return completed;}         // Returns completed var.
    void toggleCompleted();                         // Toggle completed

    char* getExplain() {return objExplain;}
    // Return an explanation
    void setExplain(char* inExplain) {objExplain = inExplain;}
    // Set an explanation
    char* getCText() {return completedText;}
    // Return the completion text
    void setCText(char* inCText) {completedText = inCText;}
    // Set the completion text
};

void objective::toggleCompleted()
// Toggles the state of the boolean completed
{
  if (!completed)
    completed = true;
  else
    completed = false;
} // objective::toggleCompleted



class game
// Game class (to hold the difficulty level and current objective)
{
  private:
    int level;                     // Which level the player's currently on
  public:
    game() {level = 0;}            // Default game constructor
    objective currentObjective;    // The current objective for the level
    int getLevel() {return level;} // Returns the difficulty level
    void incLevel() {level++;}     // Increments the current level by one
}; // game class


