#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <typeinfo>
#include <string>

namespace mtm
{   
    const std::string illegal_argument_error = "A game related error has occurred: IllegalArgument";
    const std::string illegal_cell_error = "A game related error has occurred: IllegalCell";
    const std::string cell_empty_error = "A game related error has occurred: CellEmpty";
    const std::string move_too_far_error = "A game related error has occurred: MoveTooFar";
    const std::string cell_occupied_error = "A game related error has occurred: CellOccupied";
    const std::string out_of_range_error = "A game related error has occurred: OutOfRange";
    const std::string out_of_ammo_error = "A game related error has occurred: OutOfAmmo";
    const std::string illegal_target_error = "A game related error has occurred: IllegalTarget";

    class Exception : public std::exception
    {
        private:
            const char* error_message;
        public:
            Exception(const std::string error_message) :
                    error_message(error_message.c_str()) {};
            Exception() {};
            ~Exception() {};
            virtual const char* what() const noexcept override;
    };
    class IllegalArgument : public Exception
    {
        public:
            IllegalArgument() : Exception(illegal_argument_error) {};
            ~IllegalArgument() = default;
    };
    class IllegalCell : public Exception   
    {
        public:
            IllegalCell() : Exception(illegal_cell_error) {};
            ~IllegalCell() = default;
    };
    class CellEmpty : public Exception
    {
        public:
            CellEmpty() : Exception(cell_empty_error) {};
            ~CellEmpty() = default;
    };
    class MoveTooFar : public Exception
    {
        public:
            MoveTooFar() : Exception(move_too_far_error) {};
            ~MoveTooFar() = default;
    };
    class CellOccupied : public Exception
    {
        public:
            CellOccupied() : Exception(cell_occupied_error) {};
            ~CellOccupied() = default;
    };
    class OutOfRange : public Exception
    {
        public:
            OutOfRange() : Exception(out_of_range_error) {};
            ~OutOfRange() = default;
    };
    class OutOfAmmo : public Exception
    {
        public:
            OutOfAmmo() : Exception(out_of_ammo_error) {};
            ~OutOfAmmo() = default;
    };
    class IllegalTarget : public Exception
    {
        public:
            IllegalTarget() : Exception(illegal_target_error) {};
            ~IllegalTarget() = default;
    };
}

#endif /*EXCEPTIONS_H*/