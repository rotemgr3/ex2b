#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

namespace mtm
{
    class Exception : public std::exception
    {
        public:
            Exception() = default;
            ~Exception() = default;
            virtual const char* what() const noexcept;
    };
    class IllegalArgument : Exception
    {
        public:
            IllegalArgument() = default;
            ~IllegalArgument() = default;
            const char* what() const noexcept override;
    };
    class IllegalCell : Exception   
    {
        public:
            IllegalCell() = default;
            ~IllegalCell() = default;
            const char* what() const noexcept override;
    };
    class CellEmpty : Exception
    {
        public:
            CellEmpty() = default;
            ~CellEmpty() = default;
            const char* what() const noexcept override;
    };
    class MoveTooFar : Exception
    {
        public:
            MoveTooFar() = default;
            ~MoveTooFar() = default;
            const char* what() const noexcept override;
    };
    class CellOccupied : Exception
    {
        public:
            CellOccupied() = default;
            ~CellOccupied() = default;
            const char* what() const noexcept override;
    };
    class OutOfRange : Exception
    {
        public:
            OutOfRange() = default;
            ~OutOfRange() = default;
            const char* what() const noexcept override;
    };
    class OutOfAmmo : Exception
    {
        public:
            OutOfAmmo() = default;
            ~OutOfAmmo() = default;
            const char* what() const noexcept override;
    };
    class IllegalTarget : Exception
    {
        public:
            IllegalTarget() = default;
            ~IllegalTarget() = default;
            const char* what() const noexcept override;
    };
}


#endif