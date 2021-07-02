#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <sstream>
#include <functional>

#define STRING_START_INDEX (0)

/**
 * @brief Check if the program should perform shell-argument completion.
 * 
 * @return Wether completion should be performed.
 */
bool shouldPerformCompletion();

/**
 * @brief Performs argument conversion and invokes completion functions.
 * 
 * @param argc The amount of argument in \p argv.
 * @param argv An array of strings which are the program's arguments.
 */
void complete(int argc, const char *argv[]) __attribute__((noreturn));

/**
 * @brief Completes the argument in \p completingWordIndex.
 * 
 * @param args The program's arguments.
 * @param completingWordIndex The index of the word the program should complete.
 */
void complete(const std::vector<std::string> &args, std::size_t completingWordIndex);

/**
 * @brief Find completion matches for \p incomplete in given set of \p options.
 * 
 * @param options The options set to search for matches.
 * @param incomplete The incomplete argument.
 * @return A list of matches.
 */
std::list<std::string> findMatch(const std::set<std::string> &options, const std::string &incomplete);

/**
 * @brief Suggests a single completion match.
 * 
 * @param match The match to suggest.
 */
void suggestSingle(const std::string &match);

/**
 * @brief Suggests a multiple completion matches.
 * 
 * @param match The matches to suggest.
 */
void suggestMultiple(const std::list<std::string> &matches);

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
    std::vector<std::string> args(argv, argv + argc);
    std::size_t completingWordIndex;

    const char *rawCompletingWordIndex = getenv("COMP_CWORD");
    if (rawCompletingWordIndex == nullptr)
    {
        exit(EXIT_FAILURE);
    }

    std::stringstream rawIndex(rawCompletingWordIndex);
    rawIndex >> completingWordIndex;
    if (rawIndex.fail() || completingWordIndex > args.size())
    {
        exit(EXIT_FAILURE);
    }

    complete(args, completingWordIndex);

    exit(EXIT_SUCCESS);
}

void complete(const std::vector<std::string> &args, std::size_t completingWordIndex)
{
    std::set<std::string> animals = {"cat", "camel", "dog", "donkey", "lion", "lizard", "lobster"};
    std::string incomplete = "";

    if (completingWordIndex < args.size())
    {
        incomplete = args[completingWordIndex];
    }
    auto matches = findMatch(animals, incomplete);

    switch (matches.size())
    {
    case 0:
        break;
    case 1:
        suggestSingle(matches.front());
        break;
    default:
        suggestMultiple(matches);
        break;
    }
}

std::list<std::string> findMatch(const std::set<std::string> &options, const std::string &incomplete)
{
    std::list<std::string> matches;

    for (const auto &option : options)
    {
        if (incomplete.size() == 0 || option.rfind(incomplete, STRING_START_INDEX) == STRING_START_INDEX)
        {
            matches.push_back(option);
        }
    }

    return matches;
}

void suggestSingle(const std::string &match)
{
    std::cout << match;
}

void suggestMultiple(const std::list<std::string> &matches)
{
    for (const auto &match : matches)
    {
        std::cout << match << std::endl;
    }
}