/*
 * GTUSet.h
 *
 *  Created on: 14 Ara 2017
 *      Author: Tarık
 */

//sort() : her eleman eklendiginde diziyi siralar.
#ifndef GTUSET_H_
#define GTUSET_H_
#include "GTUSetBase.h"

namespace my
{
	template<typename T>
	class GTUSet : public GTUSetBase<T>
	{
	public:
		class GTUIterator
		{
		public:
			GTUIterator();
			GTUIterator(T* p);
			GTUIterator(const GTUIterator& other);
			virtual GTUIterator& operator=(const GTUIterator& other) ;
			virtual GTUIterator& operator++();
			virtual GTUIterator& operator--();
			virtual bool operator==(const GTUIterator& other);
			virtual bool operator!=(const GTUIterator& other);
			virtual T& operator*()const;
			virtual T* operator->();
		protected:
			T* ptr;

		};
		GTUSet();
		virtual GTUIterator find(const T& element);
		virtual GTUIterator begin();
		virtual GTUIterator end();
		virtual bool empty();
		virtual int size();
		virtual int max_size();
		virtual void insert(const T& element);
		virtual int erase(const T& element);
		virtual int count(const T& element);
		virtual void clear();
		virtual void sort();
		virtual ~GTUSet() {}
	};
}

#endif /* GTUSET_H_ */
