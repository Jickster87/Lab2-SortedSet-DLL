#include "SortedSet.h"
#include "SortedSetIterator.h"

SortedSet::SortedSet(Relation r) {
    head = nullptr;
    tail = nullptr;
    nrElems = 0;
    rel = r; // ???
}


bool SortedSet::add(TComp elem) {
    // Is Set empty
    Node *newNode = new Node(elem);
    
    if (head == nullptr) {
        //Node *newNode = new Node(elem);
        head = tail = newNode;
        nrElems++;
        return true;
    }
    
    Node *current = head;
    
    if (elem == current->elem) {
        return false;
    }
    //if elem is smaller than 1st elem(head)
    if (rel(elem, current->elem)) {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
        nrElems++;
        return true;
    }
    // Move with a temp node to elem position + rel
    while (current != nullptr && rel(current->elem, elem)) {
        // If element exists, exit because Set reasons
        if (current->elem == elem) {
            delete newNode; // suggested cleanup by gpt ???
            return false;
        }
        current = current->next;
    }
    
    // is it tail (larger than all elems ?)
    if (current == nullptr) {
        newNode->prev = tail;
        tail->next = newNode;
        tail = newNode;
        nrElems++;
        return true;
    }
    //in between list
    newNode->next = current;
    newNode->prev = current->prev;
    current->prev->next = newNode;
    current->prev = newNode;

    
    nrElems++;
    return true;
}

bool SortedSet::remove(TComp elem) {
	//what cases?
    //if head = tail = ? 1 element in the list ->set to head and tail to nullptr ?
    if (head == tail) {
        return false;
    }
    
    Node * current = head;
    while (current != nullptr && current->elem != elem) {
        current = current->next;
    }
    //if not found
    if (current == nullptr) {
        return false;
    }
    //one elem in the list
    if (head == tail && current == head) {
        delete current;
        head = tail = nullptr;
        nrElems--;
        return true;
    }
    
    // Case 4: Removing head
    if (current == head) {
        head = head->next;
        head->prev = nullptr;
        delete current;
        nrElems--;
        return true;
    }

    // Case 5: Removing tail
    if (current == tail) {
        tail = tail->prev;
        tail->next = nullptr;
        delete current;
        nrElems--;
        return true;
    }

    // Case 6: Removing from the middle
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    nrElems--;
    return true;
}


bool SortedSet::search(TComp elem) const {
    Node * current = head;
    while (current != nullptr) {
        if (current->elem == elem) {
            return true;
        }
        current = current->next;
    }
	return false;
}


int SortedSet::size() const {
	return nrElems;
}


bool SortedSet::isEmpty() const {
	return nrElems == 0;
}

SortedSetIterator SortedSet::iterator() const {
	return SortedSetIterator(*this);
}


SortedSet::~SortedSet() {
    while (head != nullptr) {
        Node * temp = head;
        head = head->next;
        delete temp;
    }
}


