

#include "multi_digit_addition.h"
using namespace std;

// copy constructor
Number::Number(const Number& other) : head(nullptr), tail(nullptr) {
    Digit* marker = other.head;
    while (nullptr != marker) {
        insertFront(marker->value);
        marker = marker->next;
    }
}

// destructor
Number::~Number() {
    // initialize auxiliary pointer
    Digit* marker = nullptr;

    // iterate through list
    while (nullptr != head) {
        // set pointer to head node
        marker = head;

        // move head node to next node
        head = head->next;

        // disconect current node from rest of linked list
        marker->next = nullptr;
        if (nullptr != head) {
            head->prev   = nullptr;
        }

        // deallocate pointer
        delete marker;
        marker = nullptr;
    }
}

// copy assignment operator
Number& Number::operator=(const Number& other) {
    throw std::runtime_error("do not use operator= function");
    if (this == &other) { return *this; }
    return *this;
}

// insert front
void Number::insertFront(int value) {
    // create new node
    Digit* digit = new Digit(value);

    // case: list is empty => set tail node
    if (nullptr == tail) {
        tail = digit;
    }

    // case: list is non-empty => link head to new node
    else {
        head->prev = digit;
    }

    // link node to head and update head
    digit->next = head;
    head = digit;
}

// insert back
void Number::insertBack(int value) {
    // create new node
    Digit* digit = new Digit(value);

    // case: list is empty => set head node
    if (nullptr == head) {
        head = digit;
    }

    // case: list is non-empty => link tail to new node
    else {
        tail->next = digit;
    }

    // link node to tail and update tail
    digit->prev = tail;
    tail = digit;
}

// insertion operator
ostream& operator<<(ostream& out, const Number& number) {
    Digit* marker = number.getHead();
    while (nullptr != marker) {
        out << marker->value;
        marker = marker->next;
    }
    return out;
}

// add function
Number Number::add(const Number& rhs) {
    // dont forget to use insert front and insert back functions
    // if sum of two nodes exceeds 9, add 1 to prev node. if prev node == nullptr, make a new node with value of 1
    // use this operator to indicate lhs
    Number newNumber;
    newNumber.tail = nullptr;
    newNumber.head = nullptr;
    int carry = 0;
    int sum = 0;

    Digit* cursor1 = this->tail; // begin from end
    Digit* cursor2 = rhs.tail;

    while (cursor1 != nullptr || cursor2 != nullptr){
        // perhaps the sum part should be left out of the conditionals
        if (cursor1->prev != nullptr && cursor2->prev != nullptr){ // more digits ahead of the current digit
            sum = cursor1->value + cursor2->value + carry; // sum of digits and carry value
            if (sum > 9){ //digit check if sum is greater than 9
                carry = 1; // set carry to 1
                sum = sum - 10; // ensure digit to add to newNumber is less than 9
            }else{
                carry = 0;
            }
            newNumber.insertFront(sum);
            // iterate both cursors
            cursor1 = cursor1->prev;
            cursor2 = cursor2->prev;
        }
        else if (cursor1->prev == nullptr && cursor2->prev != nullptr){ // no more further digits in lhs number
            sum = cursor1->value + cursor2->value + carry;
            if (sum > 9){
                carry = 1;
                sum = sum - 10;
            }else{
                carry = 0;
            }
            newNumber.insertFront(sum);
            // only iterate cursor 2
            cursor2 = cursor2->prev;
        }else if (cursor1->prev != nullptr && cursor2->prev == nullptr){ // nore more further digits in rhs number
            sum = cursor1->value + cursor2->value + carry;
            if (sum > 9){
                carry = 1;
                sum = sum - 10;
            }else{
                carry = 0;
            }
            newNumber.insertFront(sum);
            // only iterate cursor 1
            cursor1 = cursor1->prev;
        }else{ // if both prev point to nullptr
            sum = cursor1->value + cursor2->value + carry;
            if (sum > 9){
                carry = 1;
                sum = sum - 10;
            }else{
                carry = 0;
            }
            newNumber.insertFront(sum);
            // iterate both to make while conditional false and exit loop
            cursor1 = cursor1->prev;
            cursor2 = cursor2->prev;
        }
    }
    // exit loop
    // check carry
    if (carry == 1){
        newNumber.insertFront(carry);
    }

    return newNumber;


    
}   