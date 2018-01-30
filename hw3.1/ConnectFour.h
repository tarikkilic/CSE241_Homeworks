/*
 * File:   ConnectFour.h
 * Author: Tarık
 *
 * Created on 02 Kasım 2017 Perşembe, 15:49
 */

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

#include <iostream>
#include <string>
using namespace std;

class ConnectFour{
public:
    //Constructors
    ConnectFour(); //5,5 otomatik board init eder.
    ConnectFour(int newRow,int newColumn);//row column girerek board init eder.
    ConnectFour(string filename);//board txt doyasindan okuyup init eder.
    ConnectFour(const ConnectFour& obje);//copy constructor
    ~ConnectFour();//Destructor


    bool getDone()const{return done;}
    //Oyun döngüsü iceren fonksiyon
    void playGame();
    //Load ve Save yapan Fonksiyonlar
    void loadGame(string filename);
    void saveGame(string filename)const;
    //board icin yer alir
    void initCells();
    //row column sayisi olcer
    void countRC();
    //gameCells i ekrana bastirir
    void printCells();
    //oyun modunu set eder
    void setGameMode(char newGameMod){gameMode = newGameMod;}
    //oyun tipini kullanicidan alir
    void inputGameType();
    //dosya ismini set eder.
    void setFile(string filename){_filename = filename;}

    //iki CF objesini karsilastirir.
    bool operator==(const ConnectFour& other)const;
    bool operator!=(const ConnectFour& other)const;
    //CF objelerini atama yapar.
    ConnectFour& operator=(const ConnectFour& rightSide);

private:
    //Board ile ilgili veri tutan class
    class Cell{
    public:
        Cell();//Here yeri nokta olarak tutar
        //3 tane parametre alir koordinatlar ve ne icerdigi.
        Cell(char newMember,int newX,int newY);
        //koordinatlari ve icerigini return eder.
        char getMember()const{return cellMember;}
        int getX()const{return x;}
        int getY()const{return y;}

        //koordinatlari ve icerigini set eder.
        void setMember(char newMember);
        void setX(int newX);
        void setY(int newY);

        //empty den user1 e, user1 den user2 ye, user2 den computera cevirir.
        Cell operator++(int);
        Cell& operator++();
        Cell operator--(int);
        Cell& operator--();
        //iki cell objesini karsilastirir.
        bool operator==(const Cell& other)const;
        bool operator!=(const Cell& other)const;
        //boardin bir hücresini ekrana bastirir ve girdi ister.
        friend istream& operator>>(istream& is,Cell& board){
             is >> board.cellMember;
            return is;
        }
        friend ostream& operator<<(ostream& os,const Cell& board){
            os << board.cellMember;
            return os;
        }
    private:
        //boardin icerigini tutar.
        char cellMember; 
        //koordinatlari tutar.
        int x;
        int y;
    };
    //private fonksiyonlar
    //parametreli olan user inputu alir,parametresiz computer hamlesi.
    void play(string newPosition);
    void play();
    //atacagi yeri kullanicidan ister
    void inputPos(string& pos);
    //Oyun modlarini ayristirdim.
    void PVP();
    void PVC();
    //bilgisayarin hamlenin nasil yapilcagina karar verir.
    int computerAI();
    //Bilgisayar en uygun atilacak yeri kontrol eder
    int computer3Right();
    int computer3Left();
    int computer3Up();
    int computer2Left();
    int computer2Right();
    int computer2Up();
    int computerUp();
    int computerRight();
    int computerLeft();
    int computer3RightO();
    int computer3LeftO();
    int computer3UpO();
    int computer2LeftO();
    int computer2RightO();
    int computer2UpO();
    int computerUpO();
    int computerRightO();
    int computerLeftO();
    //arada bosluk varsa ve tehlikeliyse oraya atar.
    int computerMid();
    //hamle sayisi return eder.
    static int getLiving(){return livingCells;}
    //koordinatin legal olup olmadigini kontrol eder.
    int isLegal(int newX,int newY)const;
    //Ana bitis fonk.lari
    void gameFinishPvP();
    void gameFinishPvC();
    //board doldugunu kontrol eder
    int isFilled()const ;
    //harfleri kucultur.
    void toLower(int x,int y);
    //Oyunun bitislerini kontrol eden fonklar
    int isFinishedO();
    int isFinishedX();
    int crossFinishedO();
    int crossFinishedX();
    //----------------------------------------
    //datalar
    //dinamik olarak tuttugum 2d dinamik array
    Cell** gameCells;
    //Boardın en ve yüksekligi
    int row;
    int column;
    //Oyun tipi
    char gameType;
    //Oyun bitisini kontrol eder
    bool done;
    //hamle sirasini tutan degiskenler
    bool player1;
    bool player2;
    bool computer;
    //load save ederken livingcelli dogru tutabilmek icin anlik hamle sayisini
    int turnCell;
    //PVP deyken PVC load edilirse ve ya tam tersinde hatalari engellemek icin.
    bool flag;
    char gameMode;
    static int livingCells;
    string _filename;

};



#endif /* CONNECTFOUR_H */

