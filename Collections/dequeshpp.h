/* File: dequeshpp.h
 * -----------------------------------------------------
 * This file exports a simple version of the Deque class
 * based on a linked list of array.
 */

#ifndef DEQUESHPP_H
#define DEQUESHPP_H

#include <iostream>
#include <stdlib.h>

/* Class: Deque<ValueType> deque;
 * ---------------------------------------------------
 * This class implements dque of a specified ValueType
 * elements
 */
template <typename ValueType>
class DequeSHPP {

    /* Public methods prototypes*/
public:

    /* Constructor: DequeSHPP
   * Usage: DequeSHPP<ValueType> deque;
   * -----------------------------------------------
   * Initializes a new empty deque
   */
    DequeSHPP();

    /* Destructor: ~DequeSHPP
   * ----------------------------------------------
   * Frees all allocated memory for the deque elements
   */
    virtual ~DequeSHPP();

    /* Method: pushBack
   * Usage: deque.pushBack(value);
   * -----------------------------------------------
   * Adds a new element to the end of the deque
   */
    void pushBack(ValueType value);

    /* Method: pushFront
   * Usage: deque.pushFront(value);
   * -----------------------------------------------
   * Adds a new element to the top of the deque
   */
    void pushFront(ValueType value);

    /* Method: popBack
   * Usage: value = deque.popBack();
   * ---------------------------------------------
   * Removes and returns the last element from the deque
   */
    ValueType popBack();

    /* Method: popFront
   * Usage: value = deque.popFront();
   * ---------------------------------------------
   * Removes and returns the top element from the deque
   */
    ValueType popFront();

    /* Method: front
   * Usage: value = deque.front();
   * ---------------------------------------------
   * Return top element of the deque without removing
   */
    ValueType front()const;

    /* Method: back
   * Usage: value = deque.back();
   * ---------------------------------------------
   * Return end element of the deque without removing
   */
    ValueType back()const;

    /* Method: empty
   * Usage: if(deque.empty())...
   * ---------------------------------------------
   * Return true if deque does not contain the elements
   */
    bool empty()const;

    /* Method: size
   * Usage: deque.size();
   * ---------------------------------------------
   * Returns the number of elements in the deque
   */
    int size()const;

    /* Method: clear
   * Usage: deque.clear();
   * ---------------------------------------------
   * Removes all elements of the deque
   */
    void clear();


    /* Private methods prototypes and instase variables*/
private:

    /* Structure for saving elements of the deque*/
    struct Section {
        ValueType* array;
        Section* left;
        Section* right;
        int count;
    };

    /* Method: createSection
   * Usage: Section* sec = createSection();
   * ---------------------------------------------
   * Create new section
   */
    Section* createSection();

    /* Method: moveArrayForward
   * Usage: moveArrayForward(Section* first)();
   * ---------------------------------------------
   * Shift array elements forward in order to
   * the new element was first
   */
    void moveArrayForward(Section* first);

    /* Method: moveArrayBack
   * Usage: moveArrayBack(Section* first)();
   * ---------------------------------------------
   * shifts the elements of the array back if
   * the first is absent
   */
    void moveArrayBack(Section* first);

    /* Current size of the elements in the deque*/
    int currentSize;

    /* References to the first section and the last, respectively*/
    Section* first;
    Section* last;

    /* Array size in one section*/
    const int ARRAY_SIZE = 10;

};

/* Implementation of all methods of DequeSHPP class*/
template <typename ValueType>
DequeSHPP<ValueType>::DequeSHPP() {
    currentSize = 0;
    first = 0;
    last = 0;
}

template <typename ValueType>
DequeSHPP<ValueType>::~DequeSHPP() {
    clear();
}

template <typename ValueType>
typename DequeSHPP<ValueType>::Section* DequeSHPP<ValueType>::createSection(){
    Section *newSection = new Section;
    newSection->array = new ValueType[ARRAY_SIZE];
    newSection->left = newSection->right = 0;
    newSection->count = 0;
    return newSection;
}

template <typename ValueType>
void DequeSHPP<ValueType>::moveArrayForward(Section* first){
    for(int i = first->count; i > 0; i--){
        first->array[i] = first->array[i-1];
    }
}

template <typename ValueType>
void DequeSHPP<ValueType>::moveArrayBack(Section* first){
    for(int i = 0; i < first->count; i++){
        first->array[i] = first->array[i+1];
    }
}

template <typename ValueType>
void DequeSHPP<ValueType>::pushBack(ValueType value){
    if(currentSize == 0){
        last = first = createSection();
    }
    if(last->count == ARRAY_SIZE){
        Section* list = new Section;
        list = last;
        last = createSection();
        last->left = list;
        list->right = last;
    }
    if(currentSize == ARRAY_SIZE){
        first->right = last;
    }
    last->count++;
    last->array[last->count - 1] = value;
    currentSize++;
}

template <typename ValueType>
void DequeSHPP<ValueType>::pushFront(ValueType value){
    if(currentSize == 0){
        last = first = createSection();
    }
    if(first->count == ARRAY_SIZE){
        Section* list = new Section;
        list = first;
        first = createSection();
        first->right = list;
        list->left = first;
    }
    if(currentSize == ARRAY_SIZE){
        last->left = first;
    }
    moveArrayForward(first);
    first->count++;
    first->array[0] = value;
    currentSize++;
}

template <typename ValueType>
ValueType DequeSHPP<ValueType>::popBack(){
    if(currentSize != 0){
        ValueType value = last->array[last->count - 1];
        last->count--;
        currentSize--;
        if(last->count == 0 && currentSize != 0){
            last = last->left;
            last->right = 0;
        }
        return value;
    } else {
        std::cout << "Error: Deque is empty" << std::endl;
        exit(1);
    }
}

template <typename ValueType>
ValueType DequeSHPP<ValueType>::popFront(){
    if(currentSize != 0){
        ValueType value = first->array[0];
        first->count--;
        currentSize--;
        moveArrayBack(first);
        if(first->count == 0){
            first = first->right;
            first->left = 0;
        }
        return value;
    } else {
        std::cout << "Error: Deque is empty" << std::endl;
        exit(1);
    }
}

template <typename ValueType>
ValueType DequeSHPP<ValueType>::front()const{
    if(currentSize != 0){
        return first->array[0];
    } else {
        std::cout << "Error: Deque is empty" << std::endl;
        exit(1);
    }
}

template <typename ValueType>
ValueType DequeSHPP<ValueType>::back()const{
    if(currentSize != 0){
        return last->array[last->count - 1];
    } else {
        std::cout << "Error: Deque is empty" << std::endl;
        exit(1);
    }
}

template <typename ValueType>
bool DequeSHPP<ValueType>::empty()const {
    return currentSize == 0;
}

template <typename ValueType>
int DequeSHPP<ValueType>::size()const {
    return currentSize;
}

template <typename ValueType>
void DequeSHPP<ValueType>::clear() {
    while (first->right != 0) {
        Section* tmp = new Section;
        tmp = first;
        first = first->right;
        delete tmp;
    }
    delete first;
    currentSize = 0;
}

#endif
