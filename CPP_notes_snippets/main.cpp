#include <iostream>
#include <string>
#include "LinkedList.h"
#include "LinkedListRaw.h"

using namespace std;

void printList(const LinkedListRaw& ll) {
    NodeRaw* current = ll.begin();
    while (current != ll.end()) {
        cout << current->getValue() << ", ";
        current = current->getNext();
    }
    cout << endl;
}


//int main() {
//    LinkedListRaw ll;
//    NodeRaw* current = ll.begin();
//
//    for (int i = 0; i < 10; ++i) {
//        current = ll.insertBefore(current, to_string(i));
//    }
//
//    printList(ll);
//    cout << endl;
//
//    for (int i = 100; i < 200; ++i) {
//        current = ll.insertAfter(current, to_string(i));
//    }
//
//    printList(ll);
//    cout << endl;
//
//    for (int i = 150; i < 300; ++i) {
//        current = ll.remove(to_string(i));
//        if (current != ll.end()) {
//            cout << "Deleted " << i << " ";
//        }
//    }
//
//    printList(ll);
//    system("pause");
//
//    return 0;
//}