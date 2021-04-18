#ifndef HELPER_HPP
#define HELPER_HPP

#include <string>
#include <ctime>

/**
 * Implementation of helper methods
 */
class Helper
{
private:
    Helper();
public:
    static std::string timespec_to_string(struct timespec value);
};

#endif // HELPER_HPP
