/*
 * GTUMap.h
 *
 *  Created on: 14 Ara 2017
 *      Author: Tarık
 */

#ifndef GTUMAP_H_
#define GTUMAP_H_

#include "GTUSet.h"
#include <utility>

namespace my
{
	template<typename K,typename V>
	class GTUMap : public GTUSet<pair<K,V>>
	{
	public:
		GTUMap() { GTUSet<pair<K,V>>(); }
		V& operator[](const K& key); //İcindekiler direk index op. ulasmak icin.
	};
}



#endif /* GTUMAP_H_ */
