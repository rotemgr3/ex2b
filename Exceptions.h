#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <typeinfo>
#include <string>

namespace mtm
{   
    const std::string illegal_argument = "IllegalArgument";
    const std::string illegal_cell = "IllegalCell";
    const std::string cell_empty = "CellEmpty";
    const std::string move_too_far = "MoveTooFar";
    const std::string cell_occupied = "CellOccupied";
    const std::string out_of_range = "OutOfRange";
    const std::string out_of_ammo = "OutOfAmmo";
    const std::string illegal_target = "IllegalTarget";

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
            IllegalArgument() : Exception(illegal_argument) {};
            ~IllegalArgument() = default;
    };
    class IllegalCell : public Exception   
    {
        public:
            IllegalCell() : Exception(illegal_cell) {};
            ~IllegalCell() = default;
    };
    class CellEmpty : public Exception
    {
        public:
            CellEmpty() : Exception(cell_empty) {};
            ~CellEmpty() = default;
    };
    class MoveTooFar : public Exception
    {
        public:
            MoveTooFar() : Exception(move_too_far) {};
            ~MoveTooFar() = default;
    };
    class CellOccupied : public Exception
    {
        public:
            CellOccupied() : Exception(cell_occupied) {};
            ~CellOccupied() = default;
    };
    class OutOfRange : public Exception
    {
        public:
            OutOfRange() : Exception(out_of_range) {};
            ~OutOfRange() = default;
    };
    class OutOfAmmo : public Exception
    {
        public:
            OutOfAmmo() : Exception(out_of_ammo) {};
            ~OutOfAmmo() = default;
    };
    class IllegalTarget : public Exception
    {
        public:
            IllegalTarget() : Exception(illegal_target) {};
            ~IllegalTarget() = default;
    };
}

#endif /*EXCEPTIONS_H*/