#include <iostream>
#include <conio.h>

using namespace std;

int headX, headY;
int targetX, targetY;
int width, height;
int score = 0;

int tailX[100], tailY[100];
int numTail = 0;


void makeTail() {
    // Make a tail
    int prevX = headX;
    int prevY = headY;
    int prev2X, prev2Y;

    for (int j = 0; j < numTail; j++) {
        prev2X = tailX[j];
        prev2Y = tailY[j];
        tailX[j] = prevX;
        tailY[j] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
}

void draw(int width, int height) {

    system("cls");
    for (int i = 0; i < width+2; i++) {
        cout << '#';
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        cout << '#';
        for (int j = 0; j < width; j++) {

            // Check head to be in the field 
            if (headY <= 0) {
                headY = 0;
            }
            if (headY > height-1) {
                headY = height - 1;
            }
            if (headX > width - 1) {
                headX = width - 1;
            }
            if (headX <= 0) {
                headX = 0;
            }

            // Check weather the target has been reached
            if (headY == targetY && headX == targetX) {

                score++;
                numTail++;
                // Generate new coordinates for target
                srand((unsigned)time(0));
                int h = rand() % height;
                int w = rand() % width;

                targetY = h;
                targetX = w;

            }

            // Print the snake
            if (i == headY && j == headX) {
                cout << 'O';
            }
            else if (i == targetY && j == targetX) {
                cout << 'T';
            }

            else {
                
                // Print the tail
                bool printed = false;
                for (int k = 0; k < numTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << '*';
                        printed = true;
                    }
                }

                if (!printed) {
                    cout << " ";
                }

            }

        }
        cout << '#' << endl;
    }
    for (int i = 0; i < width+2; i++) {
        cout << '#';
    }
    cout << "\n\nYour score is " << score << endl;
}

void input() {

    while (true) {

        // Get input
        if (_kbhit() != 0) {
            char input = _getch();

            if (input == 's' || input == 'S') {
                headY += 1;
            }
            else if (input == 'w' || input == 'W') {
                headY -= 1;
            }
            else if (input == 'a' || input == 'A') {
                headX -= 1;
            }
            else if (input == 'd' || input == 'D') {
                headX += 1;
            }
            else {
                continue;
            }

            // Redraw
            system("cls");
            draw(width, height);
            makeTail();
            
        }
    }
}


int main()
{
    // Initialize tail arrays
    for (int i = 0; i < 100; i++) {
        tailX[i] = -1;  
        tailY[i] = -1;  
    }

    srand((unsigned)time(0));
    width = rand() % 15 + 10;
    height = rand() % 15 + 10;

    headX = rand() % width;
    headY = rand() % height;

    targetX = rand() % width;
    targetY = rand() % height;

    // Prevent (targetX, targetY) == (headX, headY)

    if (targetX == headX && targetY == headY) {

        if(targetX == 0)
            targetX++;
        if (targetY == 0)
            targetY++;
        else
            targetX--;
    }

    draw(width, height);
    input();
}
