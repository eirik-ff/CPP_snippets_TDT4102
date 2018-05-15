#include "LinkedListRaw.h"

LinkedListRaw::~LinkedListRaw()
{
    NodeRaw* current = begin();
    while (current != end()) {
        NodeRaw* n = current->next;
        delete current;
        current = n;
    }
}

NodeRaw * LinkedListRaw::insertBefore(NodeRaw * pos, const string & value)
{
    if (pos == begin()) {
        head = new NodeRaw(value, head);
        ++size;
        return begin();
    }

    NodeRaw* current = begin();
    while (current->getNext() != pos) {
        current = current->getNext();
    }
    // current is now the node BEFORE pos
    current->next = new NodeRaw(value, pos);
    ++size;
    return current->next;
}

NodeRaw * LinkedListRaw::insertAfter(NodeRaw * pos, const string & value)
{
    if (begin() == end()) {  // empty list
        head->next = new NodeRaw(value, end());
        ++size;
        return begin();
    }

    pos->next = new NodeRaw(value, pos->next);
    ++size;
    return pos->next;
}

NodeRaw * LinkedListRaw::remove(NodeRaw * pos)
{
    if (pos == begin()) {
        head = head->next;
        delete pos;
        --size;
        return begin();
    }

    NodeRaw* current = begin();
    while (current->next != pos) {
        current = current->getNext();
    }
    // current is node BEFORE pos
    current->next = pos->next;
    delete pos;
    --size;

    return current;
}

NodeRaw * LinkedListRaw::remove(const string & value)
{
    NodeRaw* pos = find(value);
    if (pos != end()) {
        return remove(pos);
    }
    return end();
}

NodeRaw * LinkedListRaw::find(const string & value)
{
    NodeRaw* current = begin();
    while (current->getValue() != value && current != end()) {
        current = current->getNext();
    }

    return current;
}
