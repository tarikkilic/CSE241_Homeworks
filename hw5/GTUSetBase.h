/*
 * GTUSetBase.h
 *
 *  Created on: 14 Ara 2017
 *      Author: Tarık
 */
//Set sinifinin abstract classi.
//empty() : setin ici bos ise 0,dolu ise 1 dondurur.
//size() : setin boyutunu dondurur.
//max_size() : setin alabilecgi max boyutu dondurur.
//insert() : kendi tipinde bir eleman ekler.
//erase() : girilen elemani siler. eleman varsa 1,yoksa 0 döndürür.
//clear() : setin icini bosaltir.


//NOT: find,begin ve end fonk.larini buranin icinde tanimlayamadim cünkü
//iterator olmadigindan dolayi sikinti cikiyordu.
//Iterator ü de burada tanimlayinca yine bazi sikintilar cikti.
#ifndef GTUSETBASE_H_
#define GTUSETBASE_H_
#include <iostream>
#include <memory> // shared_ptr icin
using namespace std;

namespace my{

	template<typename T>
	class GTUSetBase
	{
	public:
		virtual bool empty() = 0;
		virtual int size() = 0;
		virtual int max_size() = 0;
		virtual void insert(const T& element) = 0;
		virtual int erase(const T& element) = 0;
		virtual void clear() = 0;
		virtual ~GTUSetBase(){ };
	protected:
		shared_ptr<T> _data;// _data.get()[0].first , _data.get()[0].second
		int used;
		int capacity;

	};
}



#endif /* GTUSETBASE_H_ */
