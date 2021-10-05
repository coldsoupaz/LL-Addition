#include <iostream>

struct Digit {
    int value   = 0;
    Digit* prev = nullptr;
    Digit* next = nullptr;    
    Digit(int value)
        : value(value), prev(nullptr), next(nullptr) {
        if (value < 0 || 9 < value) {
            throw std::invalid_argument("invalid digit");
        }
    }
};

class Number {
    Digit* head;
    Digit* tail;
  public:
    Number() : head(nullptr), tail(nullptr) { };
    Digit* getHead() const { return head; }
    Digit* getTail() const { return tail; }

    Number(const Number& other);
    ~Number();
    Number& operator=(const Number& other);

    void insertFront(int value);
    void insertBack(int value);
    
    Number add(const Number& rhs);
};

std::ostream& operator<<(std::ostream& out, const Number& number);