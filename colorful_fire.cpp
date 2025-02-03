
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

#define WIDTH 50
#define HEIGHT 20

// Function to generate a random color
std::string getRandomColor() {
    int color = rand() % 6 + 31;  // Random color codes between 31 (Red) and 36 (Cyan)
    return "\033[1;" + std::to_string(color) + "m";
}

// Function to generate fire effect
void generateFireEffect() {
    char fire[HEIGHT][WIDTH];
    
    // Initialize the fire with random characters
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            fire[i][j] = ' ';
        }
    }

    while (true) {
        // Generate the fire pattern from bottom to top
        for (int i = HEIGHT - 1; i > 0; --i) {
            for (int j = 0; j < WIDTH; ++j) {
                if (fire[i - 1][j] != ' ') {
                    fire[i][j] = fire[i - 1][j];
                } else {
                    fire[i][j] = ' ';
                }
            }
        }

        // Add a new layer of fire at the top
        for (int j = 0; j < WIDTH; ++j) {
            if (rand() % 100 < 30) { // 30% chance to have fire on the top
                fire[0][j] = '*';
            }
        }

        // Display the fire in colorful effect
        for (int i = 0; i < HEIGHT; ++i) {
            for (int j = 0; j < WIDTH; ++j) {
                std::string color = getRandomColor();
                if (fire[i][j] != ' ') {
                    std::cout << color << fire[i][j];
                } else {
                    std::cout << "\033[0m "; // Reset color for empty space
                }
            }
            std::cout << "\033[0m" << std::endl;  // Reset color at the end of the row
        }

        usleep(100000); // Delay for the effect (100 ms)
        std::cout << "\033[H"; // Move cursor to top left
    }
}

int main() {
    srand(time(0)); // Seed the random number generator
    generateFireEffect();
    return 0;
}
