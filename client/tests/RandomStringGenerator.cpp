#include "RandomStringGenerator.h"

using namespace std;

RandomStringGenerator::RandomStringGenerator() {
    srand(time(NULL));  // Seed the random number generator with the current time
}

/**
 * @brief Returns a random printable character
 * @returns a random printable character
 */
char RandomStringGenerator::randomChar() {
    const char max = '~';   // Upper end of printable character range (excluding backspace)
    const char min = ' ';   // Lower end of printable character range
    char rand_char = min + (rand() % static_cast<int>(max - min + 1));  // Pick random char within range
    return rand_char;
}

/**
 * @brief Returns a random printable string of random length
 * @returns a random string
 */
string RandomStringGenerator::randomString() {
    string rand_str = "";
    for(int i = 0; i < rand(); i++)        // For a random string length,
        rand_str.append(1,this->randomChar());    // Append a random character
    return rand_str;
}