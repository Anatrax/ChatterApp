#ifndef RANDOM_STRING_GENERATOR
#define RANDOM_STRING_GENERATOR

#include <ctime>
#include <random>
#include <string>

class RandomStringGenerator {
public:

    /**
     * @brief Random string generator constructor
     */
    RandomStringGenerator();

    /**
     * @brief Returns a random printable string of random length
     * @returns a random string
     */
    std::string randomString();

private:

    /**
     * @brief Returns a random printable character
     * @returns a random printable character
     */
    char randomChar();
};

#endif  // RANDOM_STRING_GENERATOR