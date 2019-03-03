#include<iostream>
#ifndef Deque_DEFINE
#define Deque_DEFINE(t) \
	struct Deque_##t##_Iterator;											\
	struct Deque_##t {												\
		t * data;												\
		int iSize;												\
		int iCap;												\
		size_t (*size) (Deque_##t * deq);									\
		bool (*empty) (Deque_##t * deq);									\
		Deque_##t##_Iterator (*begin) (Deque_##t * deq);							\
		Deque_##t##_Iterator (*end) (Deque_##t * deq);								\
		t& (*at) (Deque_##t * deq, size_t st);									\
		void (*clear) (Deque_##t * deq);									\
		void (*push_back) (Deque_##t * deq, const t& var);							\
		void (*push_front) (Deque_##t * deq, const t& var);							\
		t& (*front) (Deque_##t * deq);										\
		t& (*back) (Deque_##t * deq);										\
		void (*pop_front) (Deque_##t * deq);									\
		void (*pop_back) (Deque_##t * deq);									\
	};														\
	struct Deque_##t##_Iterator {											\
		int index;												\
		Deque_##t * deq;											\
	};														\
	size_t Deque_##t##_size(Deque_##t * deq) {									\
		return deq->iSize;											\
	}														\
	bool Deque_##t##_size(Deque_##t * deq) {									\
		return (0 == deq->iSize);										\
	}														\
	void Deque_##t##_ctor(Deque_##t * deq) {									\
		deq->iSize = 0;												\
		deq->iCap = 10;												\
		deq->data = (t *) malloc (deq->iCap * sizeof(t));							\
		deq->size = &Deque_##t##_size;										\
		deq->empty = &Deque_##t##_empty;									\
		deq->dtor = &Deque_##t##_dtor;										\
		deq->push_back = &Deque_##t##_push_back;                                               			\
		deq->push_front = &Deque_##t##_push_front;                                             			\
		deq->front = &Deque_##t##_front;                                                       			\
		deq->back = &Deque_##t##_back;                                                         			\
		deq->pop_front = &Deque_##t##_pop_front;                                               			\
		deq->pop_back = &Deque_##t##_pop_back;                                                 			\
		deq->begin = &Deque_##t##_begin;                                                       			\
		deq->end = &Deque_##t##_end;                                                           			\
		deq->at = &Deque_##t##_at;                                                              		\
		deq->clear = &Deque_##t##_clear;                                                        		\
	}														\
	void Deque_##t##_dtor(Deque_##t * deq) {									\
		free(deq->data);											\
	}														\
	void Deque_##t##_Iterator_ctor(Deque_##t##_Iterator * it, int idx, Deque_##t * dequ) {				\
		it->index = idx;                                                                       			\
		it->deq = dequ;                        						    			\
		it->inc = &Deque_##t##_Iterator_inc;                				    			\
		it->deref = &Deque_##t##_Iterator_deref;               				    			\
		it->dec = &Deque_##t##_Iterator_dec;                                                			\
	} 											    			\
	Deque_##t##_Iterator Deque_##t##_begin(Deque_##t * deq) {                                     			\
		Deque_##t##_Iterator it;                                                                		\
		Deque_##t##_Iterator_ctor(&it, ((deq->capacity)+(deq->insertFront)+1), deq);				\
		return it;                                                                              		\
	}														\
	Deque_##t##_Iterator Deque_##t##_end(Deque_##t * deq) { 							\
		Deque_##t##_Iterator it;                                                                		\
		Deque_##t##_Iterator_ctor(&it, deq->insertBack, deq);                                 			\
		return it;                                                                              		\
	}														\
	void Deque_##t##_clear(Deque_##t * deq) { 					          			\
		deq->size = 0;												\
		deq->curSize = 0;                                                                       		\
		deq->insertFront = -1;                                                                  		\
		deq->insertBack = 0;											\
	}														\
	void Deque_##t##_push_back(Deque_##t * deq, const t& var) {							\
		if(deq->curSize == deq->capacity)                                                       		\
		{                                                                                       		\
			Deque_##t##_increaseCapacity(deq);                                                  		\
		}                                                                                       		\
		deq->data[deq->insertBack] = var;                                                            		\
		deq->insertBack++;                                                                           		\
		deq->curSize++;                                                                              		\
	}                                                                                           			\
	void Deque_##t##_push_front(Deque_##t * deq, const t& var) {                           				\
		if(deq->curSize == deq->capacity)                                                       		\
		{                                                                                       		\
			Deque_##t##_increaseCapacity(deq);                                                  		\
		}                                                                                       		\
		deq->data[deq->capacity + deq->insertFront] = var;                                              	\
		deq->insertFront--;                                                                             	\
		deq->curSize++;                                                                              		\
	}														\
	void Deque_##t##_pop_front(Deque_##t * deq) {									\
		if(deq->curSize != 0)											\
		{													\
			deq->insertFront++;										\
			deq->curSize--;											\
		}													\
	}                                                                                           			\
	void Deque_##t##_pop_back(Deque_##t * deq) { 									\
		if(deq->curSize !=0)											\
		{													\
			deq->insertBack--;										\
			deq->curSize--;											\
		}													\
	}                                                                                           			\
	t& Deque_##t##_front(Deque_##t * deq) {                                                       			\
		return deq->data[deq->capacity + deq->insertFront + 1];							\
	}                                                                                           			\
	t& Deque_##t##_back(Deque_##t * deq) {                                                        			\
		return deq->data[deq->insertBack-1];                                                       		\
	}                                                                                              			\
	t& Deque_##t##_at(Deque_##t * deq, size_t st) { 								\
		return deq->data[ ( (deq->insertFront + deq->capacity + 1) + st ) %deq->capacity];                      \
	}
#endif
