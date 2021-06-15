#include "Exceptions.h"

namespace mtm
{   
    const char* Exception::what() const noexcept
    {
        return (error_message + error_type).c_str() ;
    }
}