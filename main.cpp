#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

bool isWall(int x, int y, int width, int height, bool maze[20][20]) {
return (x == 0 || x == width - 1 || y == 0 || y == height - 1 || maze[y][x]);
}

void addWalls(int width, int height, int difficulty, bool maze[20][20]) {
srand(time(0)); 

int numWalls = 0;
if (difficulty == 1) {
numWalls = (width * height) / 10; 
} else if (difficulty == 2) {
numWalls = (width * height) / 5; 
} else if (difficulty == 3) {
numWalls = (width * height) / 3; 
}

while (numWalls > 0) {
int x = rand() % (width - 2) + 1; 
int y = rand() % (height - 2) + 1;

if (!maze[y][x]) { 
maze[y][x] = true;
numWalls--;
}
}
}

void placeExit(int width, int height, bool maze[20][20], int &exitX, int &exitY) {
while (true) {
exitX = rand() % (width - 2) + 1; 
exitY = rand() % (height - 2) + 1;

if (maze[exitY][exitX] == false) {
break;
}
}
}

int main() {
int width, height;

cout << "Enter maze width (minimum 3): ";
cin >> width;
while (width < 3) {
cout << "Width must be at least 3. Please enter a valid width: ";
cin >> width;
}

cout << "Enter maze height (minimum 3): ";
cin >> height;
while (height < 3) {
cout << "Height must be at least 3. Please enter a valid height: ";
cin >> height;
}

int difficulty;
cout << "Select difficulty level (1 = Easy, 2 = Medium, 3 = Hard): ";
cin >> difficulty;

while (difficulty < 1 || difficulty > 3) {
cout << "Invalid difficulty. Please select (1 = Easy, 2 = Medium, 3 = Hard): ";
cin >> difficulty;
}

bool maze[20][20] = {false}; 

int playerX = 1, playerY = 1;
int exitX, exitY;

addWalls(width, height, difficulty, maze);
placeExit(width, height, maze, exitX, exitY);

char input;

while (true) {
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif

for (int y = 0; y < height; y++) {
for (int x = 0; x < width; x++) {
if (x == playerX && y == playerY) {
cout << "P"; 
} else if (x == exitX && y == exitY) {
cout << "E"; 
} else if (isWall(x, y, width, height, maze)) {
cout << "#"; 
} else {
cout << " "; 
}
}
cout << endl;
}

if (playerX == exitX && playerY == exitY) {
cout << "Congratulations, you've escaped the maze!" << endl;
break;
}

cin >> input;
int newX = playerX, newY = playerY;

if (input == 'w' || input == 'W') newY--;
if (input == 's' || input == 'S') newY++;
if (input == 'a' || input == 'A') newX--;
if (input == 'd' || input == 'D') newX++;

if (input == 'q' || input == 'Q') break;

if (!isWall(newX, newY, width, height, maze)) {
playerX = newX;
playerY = newY;
}
}

return 0;
}