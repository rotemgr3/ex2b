#include "Exceptions.h"

namespace mtm
{   
    const std::string new_line = "\n";
    const char* Exception::what() const noexcept
    {
        return (error_message + error_type + new_line).c_str() ;
    }
}