#include "LinkedList.h"

Node * LinkedList::insertBefore(Node * pos, const string & value)
{
    if (pos == begin()) {
        head = make_unique<Node>(value, move(head));
        ++size;
        return begin();
    }

    Node* current = begin();
    while (current->getNext() != pos) {
        current = current->getNext();
    }
    current->setNext(make_unique<Node>(value, move(current->next)));
    ++size;
    return current->getNext();
}

Node * LinkedList::insertAfter(Node * pos, const string & value)
{
    if (pos == end()) {
        head->setNext(make_unique<Node>(value, move(head->next)));
    }
    
    Node* current = begin();
    while (current != pos) {
        current = current->getNext();
    }
    current->setNext(make_unique<Node>(value, move(current->next)));
    ++size;
    return current->getNext();
}

Node * LinkedList::find(const string & value)
{
    Node* current = begin();
    while (current != end()) {
        if (current->getValue() == value) {
            return current;
        }
        current = current->getNext();
    }

    return current;  // is end()
}

Node * LinkedList::remove(Node * pos)
{
    if (pos == nullptr) {
        return nullptr;  // invalid
    }

    if (pos == begin()) {
        head = move(pos->next);
        return begin();
    }

    Node* current = begin();
    while (current->getNext() != pos && current != end()) {
        current = current->getNext();
    }
    if (current != end()) {  // actually deletes
        current->setNext(move(pos->next));
        --size;

        return current;
    }
    else {
        return end();
    }

}

Node * LinkedList::remove(const string & value)
{
    Node* node = find(value);
    if (node != end()) {  // it exists
        return remove(node);
    }
    return end();
}
