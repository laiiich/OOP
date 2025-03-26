#include <climits>
#include "HashTable.h"
#include "Student.h"

using namespace std;

// TODO: Task 4.1
HashTable::HashTable(int size) {
    this->size = size;
    table = new LinkedList[size];
}

// TODO: Task 4.2
HashTable::~HashTable() {
    for (int i = 0; i < table->getSize(); i++)
    {
        table[i].clear();
    }
    delete [] table;
}

// TODO: Task 4.3
int HashTable::hash(int sid) {
    unsigned long long hehe = static_cast<unsigned long long>(sid);
    return static_cast<int>((sid * sid) % INT_MAX);
}

// TODO: Task 4.4
void HashTable::add(Student* student) {
    //cout << "4.4 is called for " << student->getName() << endl;
    table[hash(student->getSid()) % size].add(student);
    //cout << "4.4 done!" << endl;
    /*for (int i = 0; i < size; i++) {
        if (table[i].getNode(student)->getData()->getSid() == student->getSid()) {
            table[i].getNode(student)
        }
    }*/
}

// TODO: Task 4.5
Student* HashTable::get(int sid) const {
    //cout << "4.5 is called " << endl;
    for (int i = 0; i < size; i++) {
        if (!table[i].isEmpty()) {
            if (table[i].getHead()->getData()->getSid() == sid)
                return table[i].getHead()->getData();
        }
    }
    
    return nullptr;
    /*int hehe = hash(sid) % size;
    /while (table[hehe].getHead() != nullptr) {
        if (table[hehe].getHead()->getData()->getSid() == sid) {
            return table[hehe].getHead()->getData();
        }
        table[hehe] = table[hehe].getHead()->getNext();
    }*/
}

// TODO: Task 4.6
void HashTable::remove(const Student* student) {
    //cout << "4.6 is called " << endl;
    for (int i = 0; i < size; i++) {
        if (table[i].contains(student)) {
            //cout << "4.6 if statement go" << endl;
            //cout << "he is " << table[i].getHead()->getData()->getName() << endl;
            table[i].remove(student);
        }
    }
}

// GIVEN: DO NOT EDIT
void HashTable::printTable() const {
    for (int i = 0; i < size; i++) {
        cout << "table[" << i << "] = " << table[i] << endl;
    }
}