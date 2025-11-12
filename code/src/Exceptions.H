#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

class DequeException : public std::exception {
    std::string mMsg;
public:
    DequeException(const std::string &msg): mMsg(msg) {}
    const char* what() const noexcept override { return mMsg.c_str(); }
};

class EmployeeException : public std::exception {
    std::string mMsg;
public:
    EmployeeException(const std::string &msg): mMsg(msg) {}
    const char* what() const noexcept override { return mMsg.c_str(); }
};

#endif // EXCEPTIONS_H
