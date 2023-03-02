#ifndef __PROJ5_PRIORITY_QUEUE_HPP
#define __PROJ5_PRIORITY_QUEUE_HPP

#include "runtimeexcept.hpp"
#include <vector>
#include <iostream>

class PriorityQueueEmptyException : public RuntimeException 
{
public:
	PriorityQueueEmptyException(const std::string & err) : RuntimeException(err) {}
};




template<typename Object>
class MyPriorityQueue
{
private:
	// fill in private member data here
    std::vector<Object> minHeap;
    
public:

	// You also need a constructor and a destructor.
	MyPriorityQueue();
	~MyPriorityQueue();

 	size_t size() const noexcept;
	bool isEmpty() const noexcept;

	void insert(const Object & elem);


	// Note:  no non-const version of this one.  This is on purpose because
	// the interior contents should not be able to be modified due to the
	// heap property.  This isn't true of all priority queues but 
	// for this project, we will do this.
	// min and extractMin should throw PriorityQueueEmptyException if the queue is empty.
	const Object & min() const; 

	void extractMin(); 

    
};

template<typename Object>
MyPriorityQueue<Object>::MyPriorityQueue()
{

}

template<typename Object>
MyPriorityQueue<Object>::~MyPriorityQueue()
{

}

template<typename Object>
size_t MyPriorityQueue<Object>::size() const noexcept
{
    return minHeap.size();
}

template<typename Object>
bool MyPriorityQueue<Object>::isEmpty() const noexcept
{
    return minHeap.empty();
}

template<typename Object>
void MyPriorityQueue<Object>::insert(const Object & elem) 
{
    minHeap.push_back(elem);
	if(minHeap.size() != 1) {
        unsigned index = minHeap.size();
        while(minHeap[index / 2 - 1] > minHeap[index - 1]) {
			std::swap(minHeap[index / 2 - 1], minHeap[index - 1]);
            index = index / 2;
            if (index == 1) {
				break;
			}
        }
    }
}

template<typename Object>
const Object & MyPriorityQueue<Object>::min() const
{
	if (isEmpty()) {
		throw PriorityQueueEmptyException("Error: Empty queue");
	}
	return minHeap[0];
}


template<typename Object>
void MyPriorityQueue<Object>::extractMin() 
{
    
    if (minHeap.empty()) {
        throw PriorityQueueEmptyException("Error: Empty queue");
    }
    if (minHeap.size() == 1){
        minHeap.pop_back();
    }
    
    else {
        std::swap(minHeap[0], minHeap.back());
        minHeap.pop_back();
        unsigned index = 1;
        
        while (!(index * 2 > minHeap.size())) {
            if ((index * 2 + 1  > minHeap.size())) {
                if (minHeap[index - 1] > minHeap[index * 2 - 1 ]) {
					std::swap(minHeap[index - 1], minHeap[index * 2 - 1]);
                    index *= 2;
                } else {
                    break;
                }
            }
            else {
                if (minHeap[index * 2 - 1] < minHeap[index * 2]) {
                    if (minHeap[index - 1] > minHeap[index * 2 - 1]) {
                        std::swap(minHeap[index - 1], minHeap[index * 2 - 1]);
                        index *= 2;
                    } else {
                    break;
                    }
                } else {
                    if(minHeap[index - 1] > minHeap[(index * 2) ]) {
                        std::swap(minHeap[index - 1], minHeap[index * 2]);
                        index = index * 2 + 1;
                    } else {
                    break;
                    }
                }
            }
        }
    }
}

#endif