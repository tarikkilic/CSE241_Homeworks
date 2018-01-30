/*
 * File:   main.cpp
 * Author: Tarik
 *
 * Created on 02 Kasim 2017 Persembe, 15:49
 */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "ConnectFour.h"
using namespace std;

int main()
{
    char Mode; // Multi veya Single tutar.
    bool check = true;//programin kapatilip kapatilmamasi icin.
    while(check){
        cout << "Oyun Modu Seciniz: M | S: ";
        cin >> Mode;
        //Single Mod
        if(Mode == 'S'){
            string f; //dosya ismi tutar
            cout << "Dosya ismi girin: ";
            cin >> f;
            ConnectFour obje1(f);
            obje1.setGameMode('S');
            cout << "P | C: ";
            obje1.inputGameType();
            obje1.playGame();
            check = false; 
        }
        //Multi Mod
        //5 obje icin tüm inputları tek tek aldim burda
        else if(Mode == 'M'){
            string f;
            cout << "Dosya ismi girin: ";
            cin >> f;
            ConnectFour obje1(f);
            obje1.setGameMode('M');
            cout << "obje1: " << endl;
            cout << "P | C: ";
            obje1.inputGameType();

            cout << "Dosya ismi girin: ";
            cin >> f;
            ConnectFour obje2(f);
            obje2.setGameMode('M');
            cout << "obje2: " << endl;
            cout << "P | C: ";
            obje2.inputGameType();

            cout << "Dosya ismi girin: ";
            cin >> f;
            ConnectFour obje3(f);
            obje3.setGameMode('M');
            cout << "obje3: " << endl;
            cout << "P | C: ";
            obje3.inputGameType();

            cout << "Dosya ismi girin: ";
            cin >> f;
            ConnectFour obje4(f);
            obje4.setGameMode('M');
            cout << "obje4: " << endl;
            cout << "P | C: ";
            obje4.inputGameType();

            cout << "Dosya ismi girin: ";
            cin >> f;
            ConnectFour obje5(f);
            obje5.setGameMode('M');
            cout << "obje5: " << endl;
            cout << "P | C: ";
            obje5.inputGameType();
            //tüm objeler bitince oyun biter.
            while(!(obje1.getDone()) || !(obje2.getDone()) || !(obje3.getDone()) || !(obje4.getDone()) || !(obje5.getDone())){
                cout << "Obje numarasi giriniz: ";
                int objeNumber;
                cin >> objeNumber;
                if(cin.fail()){
                    exit(1);
                }
                else if(objeNumber == 1){
                    obje1.playGame();
                }
                else if(objeNumber == 2){
                    obje2.playGame();

                }
                else if(objeNumber == 3){
                    obje3.playGame();
                }
                else if(objeNumber == 4){
                    obje4.playGame();
                }
                else if(objeNumber == 5){
                    obje5.playGame();
                }
                else{
                    cout << "Hatali Komut" << endl;
                }
                if(obje1 == obje2) //esittir operatörüyle sürekli karsilastirir.
                    cout << "ESIT" << endl;
                else if(obje1 != obje2)
                    cout << "ESIT DEGIL" << endl;
            }
            check = false;
        }
        else{
            cout << "Tekrar Giriniz" << endl;
        }
    }
    return 0;
}
