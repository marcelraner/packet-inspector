#ifndef LOGGING_HPP
#define LOGGING_HPP

#include <iostream>

/**
 * TRACE macro for logging
 */ 
#define TRACE(message) std::cout << __FILE__ << ":" << __LINE__ << ": " << message << std::endl;

#endif // LOGGING_HPP
