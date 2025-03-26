#include <iostream>
#include "LinkedList.h"
#include "Student.h"

// TODO: Task 2.2
LinkedList::LinkedList(const LinkedList& ll) : head(nullptr), tail(nullptr){
    *this = ll;
}

// TODO: Task 2.1
bool LinkedList::contains(const Student* data) const {
    //cout << "2.1 is called " << endl;
    LLNode* temp = head;

    while (temp != nullptr)
    {
        if (temp->data == data) {
            return true;
        }
        temp = temp->next;
    }

    return false;
}

// TODO: Task 2.3
LinkedList& LinkedList::operator=(const LinkedList& ll) {
    if (this != &ll){
        clear();
        add(ll);
    }
    return *this;
}
