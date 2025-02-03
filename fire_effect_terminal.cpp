#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#define WIDTH 40
#define HEIGHT 20
#define MAX_HEAT 10

using namespace std;

vector<vector<int>> fire(HEIGHT, vector<int>(WIDTH, 0));

void initializeFire() {
    for (int x = 0; x < WIDTH; x++) {
        fire[HEIGHT - 1][x] = MAX_HEAT;
    }
}

void updateFire() {
    for (int y = 0; y < HEIGHT - 1; y++) {
        for (int x = 1; x < WIDTH - 1; x++) {
            int decay = rand() % 3;
            fire[y][x] = (fire[y + 1][x] - decay) > 0 ? (fire[y + 1][x] - decay) : 0;
        }
    }
}

void renderFire() {
    const char *palette = " .:-=+*#%@";
    cout << "\033[H"; // Move cursor to top-left
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            cout << palette[fire[y][x]] << " ";
        }
        cout << "\n";
    }
}

int main() {
    srand(time(0));
    initializeFire();
    cout << "\033[2J"; // Clear screen
    while (true) {
        updateFire();
        renderFire();
        usleep(50000); // Delay for smooth animation
    }
    return 0;
}
