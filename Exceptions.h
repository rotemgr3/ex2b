#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <typeinfo>
#include <string>

namespace mtm
{
    class Exception : public std::exception
    {
        private:
            const std::string error_message = "A game related error has occurred: ";
            const std::string error_type;
        public:
            Exception(const std::string error_name) : error_type(error_name) {};
            Exception() {};
            ~Exception() {};
            virtual const char* what() const noexcept override;
    };
    class IllegalArgument : public Exception
    {
        public:
            IllegalArgument() : Exception("IllegalArgument") {};
            ~IllegalArgument() = default;
    };
    class IllegalCell : public Exception   
    {
        public:
            IllegalCell() : Exception("IllegalCell") {};
            ~IllegalCell() = default;
    };
    class CellEmpty : public Exception
    {
        public:
            CellEmpty() : Exception("CellEmpty") {};
            ~CellEmpty() = default;
    };
    class MoveTooFar : public Exception
    {
        public:
            MoveTooFar() : Exception("MoveTooFar") {};
            ~MoveTooFar() = default;
    };
    class CellOccupied : public Exception
    {
        public:
            CellOccupied() : Exception("CellOccupied") {};
            ~CellOccupied() = default;
    };
    class OutOfRange : public Exception
    {
        public:
            OutOfRange() : Exception("OutOfRange") {};
            ~OutOfRange() = default;
    };
    class OutOfAmmo : public Exception
    {
        public:
            OutOfAmmo() : Exception("OutOfAmmo") {};
            ~OutOfAmmo() = default;
    };
    class IllegalTarget : public Exception
    {
        public:
            IllegalTarget() : Exception("IllegalTarget") {};
            ~IllegalTarget() = default;
    };
}

#endif /*EXCEPTIONS_H*/