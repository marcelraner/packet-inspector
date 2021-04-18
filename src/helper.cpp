#include "helper.hpp"

/**
 * Converts struct timespec to a string 
 */
std::string Helper::timespec_to_string(struct timespec value)
{
    struct tm tm;
    char buf[20];
    gmtime_r(&value.tv_sec, &tm);
    strftime(buf, 20, "%Y-%m-%d %H:%M:%S", &tm);
    return std::string(buf) + "." + std::to_string(value.tv_nsec);
}
