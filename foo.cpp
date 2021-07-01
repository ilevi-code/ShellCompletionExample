#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

/**
 * @brief Check if the program should perform shell-argument completion.
 * 
 * @return Wether completion should be performed.
 */
bool shouldPerformCompletion();

/**
 * @brief Performs argument conversion and invokes completion functions.
 * 
 * @param argc The amount of argmuent in \p argv.
 * @param argv An array of strings which are the program's arguments.
 */
void complete(int argc, const char *argv[]) __attribute__((noreturn));

/**
 * @brief Completes the argument in \p completingWordIndex.
 * 
 * @param args The program's arguments.
 * @param completingWordIndex The index of the word the program should complete.
 */
void complete(std::vector<std::string> args, std::size_t completingWordIndex);

int main(int argc, const char *argv[])
{
    if (shouldPerformCompletion())
    {
        complete(argc, argv);
    }

    std::cout << "hello" << std::endl;
}

bool shouldPerformCompletion()
{
    const char *completionEnvValue = getenv("_FOO_COMPLETE");
    if (completionEnvValue == nullptr)
    {
        return false;
    }

    return std::string("complete") == completionEnvValue;
}

void complete(int argc, const char *argv[])
{
    std::vector<std::string> args = {argv, argv + argc};
    std::size_t completingWordIndex;

    const char *rawCompletingWordIndex = getenv("COMP_CWORD");
    if (rawCompletingWordIndex == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    std::stringstream rawIndex(rawCompletingWordIndex);
    rawIndex >> completingWordIndex;
    if (rawIndex.fail())
    {
        exit(EXIT_FAILURE);
    }

    complete(args, completingWordIndex);

    exit(EXIT_SUCCESS);
}

void complete(std::vector<std::string> args, std::size_t completingWordIndex)
{
    // TODO perform completion
}