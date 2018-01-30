//============================================================================
// Name        : 1.cpp

//============================================================================

#include <iostream>
#include <string>
#include "GTUMap.cpp"
#include "GTUSet.cpp"
using namespace my;




int main() {
	cout << "SET CLASSI ELEMAN EKLEME , EKRANA YAZDIRMA(ITERATOR), EXCEPTION TEST , SIRALAMA TEST" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << endl;
	GTUSet<string> s1;

	string ad = "Tarik",soyad = "Kilic", ders = "C++", status = "FAIL";
	try{
		s1.insert(ad);
		s1.insert(soyad);
		s1.insert(ders);
		s1.insert(status);
		s1.insert(ad);
	}
	catch(invalid_argument)
	{
		cerr << "HATA" << endl;
	}

	GTUSet<string>::GTUIterator ita;
	for(ita = s1.begin(); ita != s1.end(); ++ita)
		cout << *ita << " " << endl;

	cout << "SET CLASSI BOYUT" << endl;
	cout << s1.size() << endl;
	cout << "SET CLASSI ELEMAN KONTROL" << endl;
	if(s1.count("Tarik"))
		cout << "Tarik Var" << endl;
	if(!(s1.count("Ahmet")))
		cout << "Ahmet Yok" << endl;

	cout << "ELEMAN SILME" << endl;
	s1.erase("Tarik");
	if(!(s1.count("Tarik")))
		cout << "Tarik Yok" << endl;

	cout << "CLEAR FONK. VE SONRA BOYUT KONTROLU" << endl;
	s1.clear();
	cout << s1.size() << endl;

	cout << "MAP CLASSI ELEMAN EKLEME ve EKRANA YAZDIRMA(ITERATOR) ve SIRALAMA TEST" << endl;
	cout << "----------------------------------------------------------------------" << endl;
	cout << endl;
	GTUMap<string,int> m1;
	m1.insert(make_pair("Tarik",23));
	m1.insert(make_pair("Ramazan",10));
	m1.insert(make_pair("Celal", 15));
	m1.insert(make_pair("Alperen",2));
	m1.insert(make_pair("Yusuf",99));
	m1.insert(make_pair("Yasir",98));


	GTUMap<string,int>::GTUIterator it;
	for(it = m1.begin(); it != m1.end(); ++it)
		cout << it->first << " : " << it->second << endl;

	cout << "MAP CLASSI BOYUT" << endl;
	cout << m1.size() << endl;
	cout << "MAP CLASSI ELEMAN KONTROL" << endl;
	if(m1.count(make_pair("Celal", 15)))
		cout << "Celal Var" << endl;
	if(!(m1.count(make_pair("Ahmet", 17))))
		cout << "Ahmet Yok" << endl;

	cout << "ELEMAN SILME" << endl;
	m1.erase(make_pair("Celal", 15));
	cout << "SILDIKTEN SONRA TEKRAR EKRANA BASMA" << endl;
	for(it = m1.begin(); it != m1.end(); ++it)
		cout << it->first << " : " << it->second << endl;

	cout << "INDEX OPERATORU ILE EKRANA BASMA" << endl;
	cout << m1["Tarik"] << endl;

	cout << "CLEAR FONK. VE SONRA BOYUT KONTROLU" << endl;
	m1.clear();
	cout << m1.size() << endl;



	return 0;
}


