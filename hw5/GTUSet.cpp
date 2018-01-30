/*
 * GTUSet.cpp
 *
 *  Created on: 14 Ara 2017
 *      Author: Tarık
 */

#include "GTUSet.h"
#include <climits> //INT_MAX icin
namespace my
{

	template<typename T>
	GTUSet<T>::GTUSet()
	{
		this->capacity = 10;
		shared_ptr<T> temp(new T[this->capacity],default_delete<T[]>());//shared_ptr<T> == T*
		this->_data = temp;
		this->used = 0;
	}

	template<typename T>
	bool GTUSet<T>::empty()
	{
		return this->used == 0;
	}

	template<typename T>
	int GTUSet<T>::size()
	{
		return this->used;
	}

	template<typename T>
	int GTUSet<T>::max_size()
	{
		return INT_MAX;
	}

	template<typename T>
	void GTUSet<T>::clear()
	{
		this->_data.reset();
		this->capacity = 10;
		shared_ptr<T> temp(new T[this->capacity],default_delete<T[]>());
		this->_data = temp;
		this->used = 0;
	}

	template<typename T>
	int GTUSet<T>::count(const T& element)
	{
		for(int i = 0; i < this->used;i++)
		{
			if(this->_data.get()[i] == element) // var mi yok mu kontrol ediyor.
				return 1;
		}
		return 0;
	}

	template<typename T>
	void GTUSet<T>::insert(const T& element)
	{
		bool flag = true;
		for(int i = 0;i < this->used;i++)
		{
			if(this->_data.get()[i] == element) //ilk önce eleman sette var mi yok mu kontrol ediyor.
			{
				flag = false;					//varsa flagi 0 yapip fonk. hicbir sey yapmiyor.
			}
		}
		if(this->used >= this->capacity && flag){     //eger kapasite dolmus ise kendini yedege alip
			shared_ptr<T> temp(new T[this->capacity],default_delete<T[]>()); //kendisi siliyor.Sonra 2 katı kapasiteli yer
			for(int i = 0;i < this->used;i++)          //alip,yedeginden eski verilerini aliyor.
				temp.get()[i] = this->_data.get()[i];
			this->_data.reset();
			this->capacity*=2;
			shared_ptr<T> temp2(new T[this->capacity],default_delete<T[]>());
			this->_data = temp2;
			for(int i = 0;i < this->used;i++)
				this->_data.get()[i] = temp.get()[i];
			this->_data.get()[this->used] = element;
			this->used++;
		}
		else if(flag)
		{
			this->_data.get()[this->used] = element;
			this->used++;
		}
		sort();
		if(!flag)
			throw invalid_argument("HATA");

	}



	//bubble sort algoritmasi
	template<typename T>
	void GTUSet<T>::sort()
	{
		for(int i = 0; i < this->used -1;i++)
		{
			for(int j = 0; j < this->used - i - 1;j++)
			{
				if(this->_data.get()[j] > this->_data.get()[j+1])
				{
					T temp;
					temp = this->_data.get()[j];
					this->_data.get()[j] = this->_data.get()[j+1];
					this->_data.get()[j + 1] = temp;
				}
			}
		}
	}


	template<typename T>
	int GTUSet<T>::erase(const T& element)
	{
		int index,flag = 0;
		for(int i = 0;i < this->used;i++){
			if(this->_data.get()[i] == element) //silecegi elemani ariyor varsa indexi tutuyor.s
			{
				index = i;
				this->used--;
				flag = 1;   //eleman varsa flag 1 ,yoksa 0
				break;
			}
		}
		if(flag)
		{
			for(int j = index; j < (this->used);j++){
				this->_data.get()[j] = this->_data.get()[j+1]; //silenecek indexe kadar sondan kaydiriliyor.
			}
			shared_ptr<T> temp(new T[this->capacity],default_delete<T[]>());
			for(int i = 0;i < this->used;i++)
				temp.get()[i] = this->_data.get()[i];
			this->_data.reset();
			this->_data = temp;
			return 1;
		}
		
		return 0;
	}

	template<typename T>
	typename GTUSet<T>::GTUIterator GTUSet<T>::find(const T& element)
	{
		int index;
		for(int i = 0; i < this->used;i++)
		{
			if(this->_data.get()[i] == element)
			{
				index = i;
				break;
			}
		}
		return GTUIterator(this->_data.get() + index);
	}

	template<typename T>
	typename GTUSet<T>::GTUIterator GTUSet<T>::begin()
	{
		return GTUIterator(this->_data.get());
	}

	template<typename T>
	typename GTUSet<T>::GTUIterator GTUSet<T>::end()
	{
		return GTUIterator(this->_data.get() + this->used);
	}

	template<typename T>
	GTUSet<T>::GTUIterator::GTUIterator() : ptr(nullptr)
	{
		//empty
	}

	template<typename T>
	GTUSet<T>::GTUIterator::GTUIterator(T* p) : ptr(p)
	{
		//empty
	}

	template<typename T>
	GTUSet<T>::GTUIterator::GTUIterator(const GTUIterator& other)
	{
		this->ptr = other.ptr;
	}

	template<typename T>
	typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator=(const GTUIterator& other)
	{
		this->ptr = other.ptr;
		return *this;
	}

	template<typename T>
	typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator++()
	{
		this->ptr++;
		return *this;
	}

	template<typename T>
	typename GTUSet<T>::GTUIterator& GTUSet<T>::GTUIterator::operator--()
	{
		this->ptr--;
		return *this;
	}

	template<typename T>
	bool GTUSet<T>::GTUIterator::operator==(const GTUIterator& other)
	{
		return this->ptr == other.ptr;
	}

	template<typename T>
	bool GTUSet<T>::GTUIterator::operator!=(const GTUIterator& other)
	{
		return this->ptr != other.ptr;
	}

	template<typename T>
	T& GTUSet<T>::GTUIterator::operator*()const
	{
		return *ptr;
	}

	template<typename T>
	T* GTUSet<T>::GTUIterator::operator->()
	{
		return ptr;
	}


}


