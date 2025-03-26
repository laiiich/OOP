#ifndef __BST_IMPLEMENTATION_H__
#define __BST_IMPLEMENTATION_H__

#include "BST.h"
#include "BSTNode.h"
#include "LinkedList.h"

// TODO: Task 3.1
template <typename K>
const BST<K>* BST<K>::find(K key) const {
    //cout << "3.1 is called for key " << key << " and root key is " << root->key << endl;

    if (root->key == key) {
        return this;
    }

    else if (root == nullptr) {
        //cout << "3.1 NULLPTRRRRR" << endl;
        return nullptr;
    }

    else {
        //cout << "3.1 else " << endl;
        if (key > root->key) {
            //cout << "3.1 go right " << endl;
            if (!root->right.isEmpty())
                return root->right.find(key);
            return nullptr;
        }
        else {
            //cout << "3.1 go left " << endl;
            if (!root->left.isEmpty())
                return root->left.find(key);
            return nullptr;
        }
    }
    //cout << "3.1 enddddd null" << endl;
    return nullptr;
}

// TODO: Task 3.2
template <typename K>
bool BST<K>::contains(K key, const Student* student) const {
    if (root == nullptr) {
        //cout << "3.2 empty false" << endl;
        return false;
    }
    if (find(key) == nullptr) {
        //cout << "3.2 false " << endl;
        return false;
    }

    else {
        //const BST<K>* temp = find(key);
        //cout << "3.2 depends on 2.1" << endl;
        return (find(key)->root->value).contains(student);
        //return temp->getValue().contains(student);
    }
    //cout << "3.2 at last false" << endl;
    return false;
}

// TODO: Task 3.3
template <typename K>
int BST<K>::size() const {
    if (root == nullptr){
        //cout << "3.3 Base case" << endl;
        return 0;
    }
    int hehe = root->value.getSize();
    hehe += root->right.size();
    hehe += root->left.size();

    return hehe;
}

// TODO: Task 3.4
template <typename K>
void BST<K>::add(K key, Student* student) {
    //cout << "3.4 is called " << endl;
    if (isEmpty()) {
        //cout << "Create new node! with key " << key << endl;
        root = new BSTNode<K>(key, student);
        //cout << "3.4 Empty and return " << endl;
        return;
    }

    if (find(key) == nullptr) { //does not exist, create new node
        //cout << "3.4 Not exist and need to create!" << endl;
        if (key == root->key) {
            //cout << "3.4 Add now " << endl;
            root->add(student);
        }
        if (key > root->key) {
            //cout << "3.4 Right turn" << endl; 
            root->right.add(key, student);
        }
            
        else {
            //cout << "Left turn" << endl;
            root->left.add(key, student);
        }
    }

    else { //exist, add student to linked list
        //cout << "almost end!" << endl;
        find(key)->root->value.add(student);
        //cout << "Added! leave now " << endl;
    }
    //cout << "3.4 ends ! " << endl;
}

// TODO: Task 3.5
template <typename K>
LinkedList BST<K>::getAllValues() const {
    LinkedList hehe;
        if (root != nullptr) {      //reverse in order required
            if (!root->right.isEmpty()) {
                //cout << "3.5 go right " << endl;
                hehe.add(root->right.getAllValues());
            }
            
            hehe.add(root->value);
            
            if (!root->left.isEmpty()) {
                //cout << "3.5 go left " << endl;
                hehe.add(root->left.getAllValues());
            }
    }
    //cout << "3.5 returns" << endl;
    return hehe;
}

// TODO: Task 3.6
template <typename K>
const BST<K>* BST<K>::kthLargest(int k) const {
    //cout << "3.6 is called " << endl;

    LinkedList temp = getAllValues();
    //cout << "how does it work" << endl;
    LLNode* current = temp.getHead();
    int arrsize = temp.getSize(), curlargest;
    int arr[arrsize];
    for (int k = 0; k < arrsize; k++) 
        arr[k] = 0;
    int cnt = 1;
    for (int i = 0; i < arrsize; i++) {
        arr[i] = current->getData()->getTotalHallPoints();
        //cout << "in i " << i << " and points is " << arr[i] << endl;
        if (i != arrsize - 1)
            current = current->getNext();
    }

    while (arrsize >= cnt) {
       //cout << "3.6 inside while loop " << endl;
        curlargest = 0;
        int location = 0;
        for (int j = 0; j < arrsize; j++) {
            //cout << "haha for loop j is " << j << "and element " << arr[j] << endl;
            if (arr[j] > curlargest) {
                //cout << "Candidate is here! at j = " << j << ", " << arr[j] << endl;
                curlargest = arr[j];
                location = j;
            }
        //cout << "NED oF LOOP Location is " << location << endl;
        }
        arr[location] = 0;
        if (cnt == k) {
            //cout << "K is found! The largest is " << curlargest << endl;
            return find(curlargest);
        }
        ++cnt;
        
    }
    return nullptr;
}

// TODO: Task 3.7
template <typename K>
void BST<K>::remove(K key) {
    //cout << "3.7 is called for " << key << endl;
    if (find(key) == nullptr) {
        return;
    }

    if (key < root->key) {
        root->left.remove(key);
    }
    
    else if (key > root->key) {
        root->right.remove(key);
    }
    
    else if (!root->left.isEmpty() && !root->right.isEmpty()) { //2 children
        //cout << "3.7CCC" << endl;
        BSTNode<K>* temp = root->left.root;
        while (!temp->right.isEmpty()) {
            temp = temp->right.root;
        }
            
        //temp->right = root->right;
        if (temp != root->left.root)
            temp = root->left.root;
        
        root->value = temp->value;
        root->key = temp->key;
        root->left.remove(root->key);
        //delete temp;
        
    }

    else {
        //cout << "3.7DDD" << endl;
        BSTNode<K>* hehe = root;
        if (root->left.isEmpty())
            root = root->right.root;
        else
            root = root->left.root;
        hehe->left.root = nullptr;
        hehe->right.root = nullptr;
        delete hehe;
    }
    //cout << "end of remove " << endl;
}

// TODO: Task 3.8
template <typename K>
void BST<K>::remove(K key, const Student* student) {
    //cout << "3.8 is called!" << endl;
    //cout << find(key) << endl;
    if (find(key) == nullptr) {
        //cout << "3.8 nth for " << key << endl;
        return;
    }
    
    else {
        //cout << "3.8 else " << endl;
        find(key)->root->value.remove(student);
        //cout << find(key)->root->value.isEmpty() << endl;    
        if (find(key)->root->value.isEmpty()) {
            remove(key);
        }
    }
    return;
}
#endif