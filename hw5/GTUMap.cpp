/*
 * GTUMap.cpp
 *
 *  Created on: 14 Ara 2017
 *      Author: Tarık
 */

#include "GTUMap.h"

namespace my
{
	template<typename K,typename V>
	V& GTUMap<K,V>::operator[](const K& key)
	{
		for(int i = 0; i < this->used;i++)
		{
			if(this->_data.get()[i].first == key) // key i bulursa degeri döndürüyor.
				return this->_data.get()[i].second;
		}

		throw invalid_argument("OYLE BIR ELEMAN YOK");
	}

}


