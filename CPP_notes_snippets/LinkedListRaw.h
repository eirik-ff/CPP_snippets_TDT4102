#pragma once
#include <string>
using namespace std;


class NodeRaw
{
private:
    string value;
    NodeRaw* next;

public:
    NodeRaw() : value(""), next(nullptr) {};
    NodeRaw(string value, NodeRaw* next=nullptr) : value(value), next(next) {};

    string getValue() const { return value; }
    NodeRaw*  getNext()  const { return next; }

    void setValue(string value) { this->value = value; }

    friend class LinkedListRaw;
};


class LinkedListRaw
{
private:
    NodeRaw* head;
    NodeRaw* const tail;
    int size;

public:
    LinkedListRaw() : head(new NodeRaw()), tail(head) {};
    ~LinkedListRaw();
    
    NodeRaw* begin() const { return head; }
    NodeRaw* end()   const { return tail; }

    int getSize() const { return size; }

    NodeRaw* insertBefore(NodeRaw* pos, const string& value);
    NodeRaw* insertAfter(NodeRaw* pos, const string& value);
    NodeRaw* remove(NodeRaw* pos);
    NodeRaw* remove(const string& value);
    NodeRaw* find(const string& value);
};