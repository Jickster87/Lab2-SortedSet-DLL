#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
    currentElem = multime.head;
}


void SortedSetIterator::first() {
    currentElem = multime.head;
}


void SortedSetIterator::next() {
    if (!valid()) {
        throw exception();
    }
    currentElem = currentElem->next;
}


TElem SortedSetIterator::getCurrent()
{
    if (!valid()) {
        throw exception();
    }
    return currentElem->elem;
}

bool SortedSetIterator::valid() const {
	return currentElem != nullptr;
}

