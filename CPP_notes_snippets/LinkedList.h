#pragma once
#include <memory>
#include <string>
using namespace std;


class Node
{
private:
    string value;
    unique_ptr<Node> next;

public:
    Node() : value(""), next(nullptr) {};
    Node(string value, unique_ptr<Node> next=nullptr) : value(value), next(move(next)) {};

    string getValue() const { return value; }
    Node*  getNext()  const { return next.get(); }

    void setValue(string value) { this->value = value; }
    void setNext(unique_ptr<Node> next) { this->next = move(next); }
    
    friend class LinkedList;
};


class LinkedList
{
private:
    unique_ptr<Node> head;
    Node* const tail;
    int size = 0;

public:
    LinkedList() : head(make_unique<Node>("----")), tail(head.get()) {};

    Node* begin() const { return head.get(); }
    Node* end()   const { return tail; }

    int getSize() const { return size; }

    Node* insertBefore(Node* pos, const string& value);
    Node* insertAfter(Node* pos, const string& value);
    Node* find(const string& value);
    Node* remove(Node* pos);
    Node* remove(const string& value);
};