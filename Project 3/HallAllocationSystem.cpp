#include "HallAllocationSystem.h"
#include "BST.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "Student.h"

// TODO: Task 5.1
HallAllocationSystem::HallAllocationSystem(int totalHallAvailable) {
    studentTable = new HashTable(193);
    studentQueue = new BST<int>;
    //studentPendingList = new LinkedList;
    this->totalHallAvailable = totalHallAvailable;
}

// TODO: Task 5.2
HallAllocationSystem::~HallAllocationSystem() {
    delete studentTable;
    delete studentQueue;
}

// TODO: Task 5.3
void HallAllocationSystem::allocateHall() {
    //cout << "5.3 is called" << endl;
    if (!studentPendingList.isEmpty()) {
        return;
    }

    else {
        LinkedList hehe;
        //cout << "studentQueue is " << studentQueue->isEmpty() << endl;
        //cout << "hall avail is " << totalHallAvailable << endl;

        while (totalHallAvailable != 0 && !studentQueue->isEmpty()) {
            //cout << "5.3 AA" << endl;
            
            LinkedList omg = studentQueue->kthLargest(1)->getValue();
            LLNode* temp = omg.getHead();
            hehe.add(omg);

            while (temp != nullptr) {
                //cout << "sub 5.3 AA" << endl;
                temp->getData()->setStatus(PENDING_ACTION);
                //cout << "sub 5.3 BB" << endl;                
                //hehe.add(temp->getData());
                //cout << "sub 5.3 CC" << endl;    
                temp = temp->getNext();
            }
            
            //cout << "5.3 CC" << endl;
            //cout << "hall pt is " << studentQueue->kthLargest(1)->getKey() <<endl;
            studentQueue->remove(studentQueue->kthLargest(1)->getKey());
            
            totalHallAvailable -= omg.getSize();
            if (totalHallAvailable < 0)
                totalHallAvailable = 0;
        }

        studentPendingList.add(hehe);
    }
}

// TODO: Task 5.4
void HallAllocationSystem::addStudent(Student* student) {
    if (student->getStatus() != QUEUEING) {
        //cout << "5.4 a Dont add" << endl;
        return;
    }

    else {
        if (studentPendingList.contains(student)) {
           // cout << "5.4 exist alr no add " << endl;
            return; 
        }
        else {
            //cout << "5.4 Add now " << endl;
            //cout << student->getName() << ": Student sid is " << student->getSid() << endl;
            studentTable->add(student);
            //cout << "student point is " << student->getTotalHallPoints() << endl;
            studentQueue->add(student->getTotalHallPoints(), student);            
        }
    }
}
// TODO: Task 5.5
void HallAllocationSystem::removeStudent(const Student* student) {
    studentTable->remove(student);
    //cout << "5.5 aa " << endl;

    //cout << student->getTotalHallPoints() << "Is total points" << endl;
    studentQueue->remove(student->getTotalHallPoints(), student);
    //cout << "5.5 bb " << endl;

    studentPendingList.remove(student);
    //cout << "5.5 cc " << endl;
}

// TODO: Task 5.6
bool HallAllocationSystem::predict(const Student* student) const {
    if (totalHallAvailable > 0) {
        //cout << "Student sid: " << student->getSid() << " with hall pt: " << student->getTotalHallPoints() << endl;
        //cout << "Kth largest: " << studentQueue->kthLargest(totalHallAvailable)->getValue().getHead()->getData()->getTotalHallPoints() << endl;
        if (!studentQueue->contains(student->getTotalHallPoints(), student)) {
            //cout << "Oops cant find u " << endl;
            return false;
        }
            
        if (student->getTotalHallPoints() >= studentQueue->kthLargest(totalHallAvailable)->getValue().getHead()->getData()->getTotalHallPoints())
        {
            return true;
        }

        else
            return false;
    }
    return false;
}

// TODO: Task 5.7
void HallAllocationSystem::acceptOffer(Student* student) {
    if (!studentPendingList.contains(student))
        return;
        
    else {
        studentPendingList.remove(student);
        student->setStatus(ACCEPTED);
        return;
    }
}

// TODO: Task 5.8
void HallAllocationSystem::rejectOffer(Student* student) {
    if (!studentPendingList.contains(student))
        return;
    else {
        student->setStatus(REJECTED);
        studentPendingList.remove(student);
        ++totalHallAvailable;
        return;
    }
}

// TODO: Task 5.9
void HallAllocationSystem::acceptAllOffers() {
    while (!studentPendingList.isEmpty()) {
        acceptOffer(studentPendingList.getHead()->getData());
    }
}

// TODO: Task 5.10
void HallAllocationSystem::rejectAllOffers() {
    while (!studentPendingList.isEmpty()) {
        rejectOffer(studentPendingList.getHead()->getData());
    }
}