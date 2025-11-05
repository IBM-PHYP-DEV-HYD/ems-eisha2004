#ifndef EDLL_H
#define EDLL_H

#include <iostream>
#include "Exceptions.H"

template<typename T>
class EDLL {
private:
    struct Node {
        T mData;
        Node* mPrev;
        Node* mNext;
        Node(const T& dataParm): mData(dataParm), mPrev(nullptr), mNext(nullptr) {}
    };

    Node* mFront;
    Node* mRear;
    int mSize;

    Node* pGetNodeAt(int index) const {
        if (index < 0 || index >= mSize) return nullptr;
        Node* cur;
        if (index <= mSize/2) {
            cur = mFront;
            for (int i=0;i<index;++i) cur = cur->mNext;
        } else {
            cur = mRear;
            for (int i=mSize-1;i>index;--i) cur = cur->mPrev;
        }
        return cur;
    }

public:
    EDLL(): mFront(nullptr), mRear(nullptr), mSize(0) {}
    ~EDLL() { clear(); }

    bool empty() const { return mSize==0; }
    int size() const { return mSize; }

    void pushFront(const T& value) {
        Node* n = new Node(value);
        if (empty()) { mFront = mRear = n; }
        else {
            n->mNext = mFront;
            mFront->mPrev = n;
            mFront = n;
        }
        ++mSize;
    }

    void pushBack(const T& value) {
        Node* n = new Node(value);
        if (empty()) { mFront = mRear = n; }
        else {
            mRear->mNext = n;
            n->mPrev = mRear;
            mRear = n;
        }
        ++mSize;
    }

    void popFront() {
        if (empty()) return;
        Node* t = mFront;
        if (mSize==1) { mFront = mRear = nullptr; }
        else {
            mFront = mFront->mNext;
            mFront->mPrev = nullptr;
        }
        delete t;
        --mSize;
    }

    void popBack() {
        if (empty()) return;
        Node* t = mRear;
        if (mSize==1) { mFront = mRear = nullptr; }
        else {
            mRear = mRear->mPrev;
            mRear->mNext = nullptr;
        }
        delete t;
        --mSize;
    }

    T& front() const {
        if (empty()) throw DequeException("EDLL: empty front");
        return mFront->mData;
    }
    T& back() const {
        if (empty()) throw DequeException("EDLL: empty back");
        return mRear->mData;
    }

    void clear() {
        Node* cur = mFront;
        while (cur) {
            Node* tmp = cur;
            cur = cur->mNext;
            delete tmp;
        }
        mFront = mRear = nullptr;
        mSize = 0;
    }

    // insert at index: 0..mSize
    void insertAt(int index, const T& value) {
        if (index < 0 || index > mSize) throw DequeException("insertAt: index out of range");
        if (index==0) { pushFront(value); return; }
        if (index==mSize) { pushBack(value); return; }
        Node* nextNode = pGetNodeAt(index);
        if (!nextNode) throw DequeException("insertAt: internal error");
        Node* prevNode = nextNode->mPrev;
        Node* n = new Node(value);
        n->mPrev = prevNode;
        n->mNext = nextNode;
        prevNode->mNext = n;
        nextNode->mPrev = n;
        ++mSize;
    }

    // remove at index 0..mSize-1
    void removeAt(int index) {
        if (index < 0 || index >= mSize) throw DequeException("removeAt: index out of range");
        if (index==0) { popFront(); return; }
        if (index==mSize-1) { popBack(); return; }
        Node* curr = pGetNodeAt(index);
        if (!curr) throw DequeException("removeAt: internal error");
        Node* p = curr->mPrev;
        Node* n = curr->mNext;
        p->mNext = n;
        n->mPrev = p;
        delete curr;
        --mSize;
    }

    // returns index of first match (using pointer equality or compare function externally)
    // Provide iteration helpers:
    class Iterator {
        Node* mNode;
    public:
        Iterator(Node* n): mNode(n) {}
        bool hasNext() const { return mNode != nullptr; }
        T& value() const { return mNode->mData; }
        void next() { if (mNode) mNode = mNode->mNext; }
    };
    Iterator getIterator() const { return Iterator(mFront); }
};

#endif // EDLL_H
