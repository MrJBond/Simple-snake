#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <termios.h>

using namespace std;

int headX, headY;
int targetX, targetY;
int width, height;
int score = 0;

int tailX[100], tailY[100];
int numTail = 0;

void makeTail() {
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
    system("clear");
    for (int i = 0; i < width + 2; i++) {
        cout << '#';
    }
    cout << endl;

    for (int i = 0; i < height; i++) {
        cout << '#';
        for (int j = 0; j < width; j++) {

            if (headY <= 0) {
                headY = 0;
            }
            if (headY > height - 1) {
                headY = height - 1;
            }
            if (headX > width - 1) {
                headX = width - 1;
            }
            if (headX <= 0) {
                headX = 0;
            }

            if (headY == targetY && headX == targetX) {
                score++;
                numTail++;
                srand((unsigned)time(0));
                int h = rand() % height;
                int w = rand() % width;
                targetY = h;
                targetX = w;
            }

            if (i == headY && j == headX) {
                cout << 'O';
            } else if (i == targetY && j == targetX) {
                cout << 'T';
            } else {
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
    for (int i = 0; i < width + 2; i++) {
        cout << '#';
    }
    cout << "\n\nYour score is " << score << endl;
}

char my_getch() {
    char buf = 0;
    struct termios old = {0};

// Save the current terminal attributes
    if (tcgetattr(STDIN_FILENO, &old) < 0)
        perror("tcsetattr()");

// Disable canonical mode and echo
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;

// Apply the modified attributes
    if (tcsetattr(STDIN_FILENO, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");

    // Read a single character
    if (read(STDIN_FILENO, &buf, 1) < 0)
        perror("read()");

// Restore original terminal attributes (reenable canonical mode and echo)
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;

    if (tcsetattr(STDIN_FILENO, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");

    // Return the read character
    return buf;
}

void input() {
    while (true) {
        char input = my_getch();

        if (input == 's' || input == 'S') {
            headY += 1;
        } else if (input == 'w' || input == 'W') {
            headY -= 1;
        } else if (input == 'a' || input == 'A') {
            headX -= 1;
        } else if (input == 'd' || input == 'D') {
            headX += 1;
        } else {
            continue;
        }

        system("clear");
        draw(width, height);
        makeTail();
    }
}

int main() {
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

    if (targetX == headX && targetY == headY) {
        if (targetX == 0)
            targetX++;
        if (targetY == 0)
            targetY++;
        else
            targetX--;
    }

    draw(width, height);
    input();

    return 0;
}



