#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "ConnectFour.h"
using namespace std;
int ConnectFour::livingCells = 0;

//0,0 '.' atar.
ConnectFour::Cell::Cell(){
    x = 0;
    y = 0;
    cellMember = '.';
}

//3 parametre alir koordinatlar ve icerik
ConnectFour::Cell::Cell(char newMember,int newX,int newY){
    x = newX;
    y = newY;
    cellMember = newMember;
}

//koordinatlari ve icerigini set eder.
void ConnectFour::Cell::setMember(char newMember){
    cellMember = newMember;
}

//5,5 otomatik board init eder.
ConnectFour::ConnectFour(){
    row = 5;
    column = 5;
    gameType = 'S';
    done = false;
    player1 = true;
    player2 = false;
    computer = false;
    flag = true;
    gameMode = 'S';
    turnCell = 0;
    initCells();
}

//row column girerek board init eder.
ConnectFour::ConnectFour(int newRow,int newColumn){
    row = newRow;
    column = newColumn;
    done = false;
    player1 = true;
    player2 = false;
    computer = false;
    flag = true;
    gameMode = 'S';
    turnCell = 0;
    initCells();
}

//board txt doyasindan okuyup init eder.
ConnectFour::ConnectFour(string filename){
    gameType = 'S';
    done = false;
    player1 = true;
    player2 = false;
    computer = false;
    flag = true;
    gameMode = 'S';
    turnCell = 0;
    row = 0;
    column = 0;
    _filename = filename;
    countRC(); //satir sutun sayisi bulur.
    initCells();//board icin hafizadan yer alir.


    char x; //txt den okuyacagimiz her karakteri tutar.
    ifstream file;
    file.open(filename);
    string line; //her bi satiri bu stringe tutulur.

    for(int i =0;i < row;i++){
        getline(file,line);
        for(int j =0 ;j < column;j++){//satirdikati her bir karakteri tek tek alir.
            x = line[j]; //satirdaki karakteri tek tek x'e attim.
            if(x == '*') //yildiz gördugunde x'i . yapar.Degilse bosluk atar.
                x = '.';
            Cell obje(x,i,j);//gecici obje olusturup bilgileri yazdim.
            gameCells[i][j] = obje;//gecici objeyi arraye atip orda tutuyoruz.
        }
    }
    file.close();
}

//board icin yer alir.
void ConnectFour::initCells(){
    gameCells = new Cell*[row+1];
    for(int i = 0;i < row;i++){
        gameCells[i] = new Cell[column+1];
    }


}

//satir sutun sayisi bulur.
void ConnectFour::countRC(){
    int tColumn = 0;
    ifstream file;
    file.open(_filename);
    string line;
    while (getline(file, line, '\n')){
        for(char c : line){
            tColumn++;
        }
        if(tColumn > column)
            column = tColumn;

        tColumn = 0;
        row++;
    }
    file.close();
}


//board bastirir.
void ConnectFour::printCells(){
    for(int i = 0; i < column; ++i) {
        cout << (char)('A' + i) << ' ';
    }
    cout << endl;
    for(int l = 0;l < row;l++){
        for(int k = 0;k < column; k++){
            if(gameCells[l][k].getMember() == '.'){
                cout << ". ";
            }
            else if(gameCells[l][k].getMember() == ' '){
                cout << "  ";
            }
            else if(gameCells[l][k].getMember() == 'X'){
                cout << "X ";
            }
            else if(gameCells[l][k].getMember() == 'O'){
                cout << "O ";
            }
            else if(gameCells[l][k].getMember() == 'x'){
                cout << "x ";
            }
            else if(gameCells[l][k].getMember() == 'o'){
                cout << "o ";
            }

        }
        cout << endl;
    }
}


//Oyun tipine göre fonksiyona girer.
void ConnectFour::playGame(){
    if(gameType == 'P'){
        PVP();
    }
    else if(gameType == 'C'){
        PVC();
    }
}


//Playerin hamlesini gerceklestiren fonksiyon
void ConnectFour::play(string newPosition){
    string dosyaismi;
    bool status = true;//Hata mesajini verebilmek icin.
    if(newPosition == "SAVE"){
        cin >> dosyaismi;
        saveGame(dosyaismi);
        status = false;
        cout << "OYUN KAYDEDILDI" << endl;
    }
    else if(newPosition == "LOAD"){
        cin >> dosyaismi;
        loadGame(dosyaismi);
        cout << "OYUN YUKLENDI." << endl;
        printCells();
        status = false;
    }
    else{
        for (int i = 0; i < column; ++i) {
            if (newPosition[0] == 'A' + i) {
                for (int j = 0; j < row; ++j) {
                    if (gameCells[row - j - 1][i].getMember() == '.') {
                        if(status)
                        {
                            if(player1){
                                gameCells[row - j - 1][i].setMember('X');
                                //Hamle siralarini degistiriyorum.
                                player1 = false;
                                player2 = true;
                                computer = true;
                                livingCells++;
                                turnCell++;
                            }
                            else if(player2){
                                //Hamle siralarini degistiriyorum.
                                gameCells[row - j - 1][i].setMember('O');
                                player1 = true;
                                player2 = false;
                                livingCells++;
                                turnCell++;
                            }
                            status = false;
                        }
                    }
                }
            }
        }
    }

    if(status){
        cerr << "YANLIS KOMUT" << endl;
    }
}


//Bilgisayar hamlesi
void ConnectFour::play(){
    computerAI();
    livingCells++;
    turnCell++;
    computer = false;
    player1 = true;
}

void ConnectFour::PVP(){
        string position;//sütun inputunu aldigimiz degisken.
        printCells();
        while(!(done) && flag){
            if(player1){
                if(gameType == 'P'){
                    cout << "P1 sutun giriniz: ";
                    inputPos(position);
                    play(position);
                    printCells();
                    cout << "Living Cell: " << getLiving() << endl;
                    gameFinishPvP();
                }
                if(gameType == 'C'){//pvp de pvc cagirirsa
                    PVC();
                    flag = false;
                }
            }
            else if(player2){
                if(gameType == 'P'){
                    cout << "P2 sutun giriniz: ";
                    inputPos(position);
                    play(position);
                    printCells();
                    cout << "Living Cell: " << getLiving() << endl;
                    gameFinishPvP();
                }
                if(gameType == 'C'){//pvp de pvc cagirirsa
                    PVC();
                    flag = false;
                }
                if(gameMode == 'M' && position != "SAVE" && position != "LOAD")
                    flag = false;
            }
        }
        flag = true;
}
void ConnectFour::PVC(){
        string position;//sütun inputunu aldigimiz degisken.
        printCells();
        while(!(done) && flag){
            if(player1){
                if(gameType == 'C'){
                    cout << "P1 sutun giriniz: ";
                    inputPos(position);
                    play(position);
                    printCells();
                    cout << "Living Cell: " << getLiving() << endl;
                    gameFinishPvP();
                }
                if(gameType == 'P'){//pvc icinde pvp cagirirsa
                    PVP();
                    flag = false;
                }
            }
            else if(computer){
                printCells();
                play();
                printCells();
                gameFinishPvC();
                if(gameMode == 'M' && position != "SAVE" && position != "LOAD")
                    flag = false;
            }
        }
        flag = true;
}

void ConnectFour::gameFinishPvC(){

        if (isFinishedO() || crossFinishedO()) {
            done = true;
            cout << "BILGISAYAR KAZANDI" << endl;;
            printCells();
        }
        else if (isFinishedX() || crossFinishedX()) {
            done = true;
            cout << "KAZANDINIZ" << endl;;
            printCells();
        }
        else if (isFilled()) {
            done = true;
            cout << "BERABERE" << endl;
            printCells();
        }
}



void ConnectFour::gameFinishPvP(){

        if (isFinishedO() || crossFinishedO()) {
            done = true;
            cout << "PLAYER2 KAZANDI" << endl;;
            printCells();
        }
        else if (isFinishedX() || crossFinishedX()) {
            done = true;
            cout << "PLAYER1 KAZANDI" << endl;;
            printCells();
        }
        else if (isFilled()) {
            done = true;
            cout << "BERABERE" << endl;
            printCells();
        }
}

void ConnectFour::toLower(int x,int y){
    if(gameCells[x][y].getMember() == 'X')
        gameCells[x][y].setMember('x');
    else if(gameCells[x][y].getMember() == 'O')
        gameCells[x][y].setMember('o');
}
int ConnectFour::isLegal(int newX,int newY)const{
    int status = 0;
    if(newX >= 0 && newY >= 0 && newX < row && newY < column)
        status = 1;

    return status;

}
int ConnectFour::isFilled()const{
    int status = 1;

    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if(gameCells[i][j].getMember() == '.')
                status = 0;
        }
    }
    return status;
}
int ConnectFour::isFinishedO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i + 1, j) && isLegal(i + 2, j) && isLegal(i + 3, j)) {
                if (gameCells[i][j].getMember() == 'O' && gameCells[i + 1][j].getMember() == 'O' && gameCells[i + 2][j].getMember() == 'O' && gameCells[i + 3][j].getMember() == 'O') {
                    toLower(i, j);
                    toLower(i + 1, j);
                    toLower(i + 2, j);
                    toLower(i + 3, j);
                    status = 1;
                }
            }
            if (isLegal(i, j + 1) && isLegal(i, j + 2) && isLegal(i, j + 3)) {
                if (gameCells[i][j].getMember() == 'O' && gameCells[i][j+1].getMember() == 'O' && gameCells[i][j + 2].getMember() == 'O' && gameCells[i][j + 3].getMember() == 'O') {
                    toLower(i, j);
                    toLower(i, j + 1);
                    toLower(i, j + 2);
                    toLower(i, j + 3);
                    status = 1;
                }
            }

        }
    }
    return  status;
}

int ConnectFour::isFinishedX(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i + 1, j) && isLegal(i + 2, j) && isLegal(i + 3, j)) {
                if (gameCells[i][j].getMember() == 'X' && gameCells[i + 1][j].getMember() == 'X' && gameCells[i + 2][j].getMember() == 'X' && gameCells[i + 3][j].getMember() == 'X') {
                    toLower(i, j);
                    toLower(i + 1, j);
                    toLower(i + 2, j);
                    toLower(i + 3, j);
                    status = 1;
                }
            }
            if (isLegal(i, j + 1) && isLegal(i, j + 2) && isLegal(i, j + 3)) {
                if (gameCells[i][j].getMember() == 'X' && gameCells[i][j+1].getMember() == 'X' && gameCells[i][j + 2].getMember() == 'X' && gameCells[i][j + 3].getMember() == 'X') {
                    toLower(i, j);
                    toLower(i, j + 1);
                    toLower(i, j + 2);
                    toLower(i, j + 3);
                    status = 1;
                }
            }

        }
    }
    return  status;
}

int ConnectFour::crossFinishedO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if(isLegal(i+1,j+1) && isLegal(i+2,j+2) && isLegal(i+3,j+3)){
                if(gameCells[i][j].getMember() == 'O' && gameCells[i+1][j+1].getMember() == 'O' && gameCells[i+2][j+2].getMember() == 'O' && gameCells[i+3][j+3].getMember() == 'O') {
                    toLower(i,j);
                    toLower(i+1,j+1);
                    toLower(i+2,j+2);
                    toLower(i+3,j+3);
                    status = 1;
                }
            }
            if(isLegal(i-1,j+1) && isLegal(i-2,j+2) && isLegal(i-3,j+3)){
                 if(gameCells[i][j].getMember() == 'O' && gameCells[i-1][j+1].getMember() == 'O' && gameCells[i-2][j+2].getMember() == 'O' && gameCells[i-3][j+3].getMember() == 'O') {
                     toLower(i,j);
                     toLower(i-1,j+1);
                     toLower(i-2,j+2);
                     toLower(i-3,j+3);
                     status = 1;
                 }
            }
            if(isLegal(i+1,j-1) && isLegal(i+2,j-2) && isLegal(i+3,j-3)){
                 if(gameCells[i][j].getMember() == 'O' && gameCells[i+1][j-1].getMember() == 'O' && gameCells[i+2][j-2].getMember() == 'O' && gameCells[i+3][j-3].getMember() == 'O') {
                     toLower(i,j);
                     toLower(i+1,j-1);
                     toLower(i+2,j-2);
                     toLower(i+3,j-3);
                     status = 1;
                 }
            }
            if(isLegal(i-1,j-1) && isLegal(i-2,j-2) && isLegal(i-3,j-3)) {
                if (gameCells[i][j].getMember() == 'O' && gameCells[i-1][j-1].getMember() == 'O' && gameCells[i-2][j-2].getMember() == 'O' &&
                    gameCells[i-3][j-3].getMember() == 'O') {
                    toLower(i,j);
                    toLower(i-1,j-1);
                    toLower(i-2,j-2);
                    toLower(i-3,j-3);
                    status = 1;
                }
            }
        }
    }
    return status;
}

int ConnectFour::crossFinishedX(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if(isLegal(i+1,j+1) && isLegal(i+2,j+2) && isLegal(i+3,j+3)){
                if(gameCells[i][j].getMember() == 'X' && gameCells[i+1][j+1].getMember() == 'X' && gameCells[i+2][j+2].getMember() == 'X' && gameCells[i+3][j+3].getMember() == 'X') {
                    toLower(i,j);
                    toLower(i+1,j+1);
                    toLower(i+2,j+2);
                    toLower(i+3,j+3);
                    status = 1;
                }
            }
            if(isLegal(i-1,j+1) && isLegal(i-2,j+2) && isLegal(i-3,j+3)){
                 if(gameCells[i][j].getMember() == 'X' && gameCells[i-1][j+1].getMember() == 'X' && gameCells[i-2][j+2].getMember() == 'X' && gameCells[i-3][j+3].getMember() == 'X') {
                     toLower(i,j);
                     toLower(i-1,j+1);
                     toLower(i-2,j+2);
                     toLower(i-3,j+3);
                     status = 1;
                 }
            }
            if(isLegal(i+1,j-1) && isLegal(i+2,j-2) && isLegal(i+3,j-3)){
                 if(gameCells[i][j].getMember() == 'X' && gameCells[i+1][j-1].getMember() == 'X' && gameCells[i+2][j-2].getMember()== 'X' && gameCells[i+3][j-3].getMember() == 'X') {
                     toLower(i,j);
                     toLower(i+1,j-1);
                     toLower(i+2,j-2);
                     toLower(i+3,j-3);
                     status = 1;
                 }
            }
            if(isLegal(i-1,j-1) && isLegal(i-2,j-2) && isLegal(i-3,j-3)) {
                if (gameCells[i][j].getMember() == 'X' && gameCells[i-1][j-1].getMember() == 'X' && gameCells[i-2][j-2].getMember() == 'X' &&
                    gameCells[i-3][j-3].getMember() == 'X') {
                    toLower(i,j);
                    toLower(i-1,j-1);
                    toLower(i-2,j-2);
                    toLower(i-3,j-3);
                    status = 1;
                }
            }
        }
    }
    return status;
}


int ConnectFour::computer3Right(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j+1) && isLegal(i , j+2) && isLegal(i, j+3)) {
                if (gameCells[i][j].getMember() == 'X' && gameCells[i][j + 1].getMember() == 'X' && gameCells[i][j + 2].getMember() == 'X' && gameCells[i][j+3].getMember() == '.') {
                    if(!(isLegal(i+1,j+3)) || gameCells[i+1][j + 3].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 3].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer3RightO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j+1) && isLegal(i , j+2) && isLegal(i, j+3)) {
                if (gameCells[i][j].getMember() == 'O' && gameCells[i][j + 1].getMember() == 'O' && gameCells[i][j + 2].getMember() == 'O' && gameCells[i][j+3].getMember() == '.') {
                    if(!(isLegal(i+1,j+3)) || gameCells[i+1][j + 3].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 3].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer3Left(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j-1) && isLegal(i , j-2) && isLegal(i, j-3)) {
                if (gameCells[i][j].getMember() == 'X' && gameCells[i][j - 1].getMember() == 'X' && gameCells[i][j - 2].getMember() == 'X' && gameCells[i][j-3].getMember() == '.') {
                    if(!(isLegal(i+1,j-3)) || gameCells[i+1][j - 3].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j - 3].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer3LeftO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j-1) && isLegal(i , j-2) && isLegal(i, j-3)) {
                if (gameCells[i][j].getMember() == 'O' && gameCells[i][j - 1].getMember() == 'O' && gameCells[i][j - 2].getMember() == 'O' && gameCells[i][j-3].getMember() == '.') {
                    if(!(isLegal(i+1,j-3)) || gameCells[i+1][j - 3].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j - 3].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer2Left(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j-1) && isLegal(i , j-2)) {
                if (gameCells[i][j].getMember() == 'X' && gameCells[i][j - 1].getMember() == 'X' && gameCells[i][j - 2].getMember() == '.') {
                    if(!(isLegal(i+1,j-2)) || gameCells[i+1][j - 2].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j - 2].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer2LeftO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j-1) && isLegal(i , j-2)) {
                if (gameCells[i][j].getMember() == 'O' && gameCells[i][j - 1].getMember() == 'O' && gameCells[i][j - 2].getMember() == '.') {
                    if(!(isLegal(i+1,j-2)) || gameCells[i+1][j - 2].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j - 2].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer2Right(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j+1) && isLegal(i , j+2)) {
                if (gameCells[i][j].getMember() == 'X' && gameCells[i][j + 1].getMember() == 'X' && gameCells[i][j + 2].getMember() == '.') {
                    if(!(isLegal(i+1,j+2)) || gameCells[i+1][j + 2].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 2].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer2RightO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j+1) && isLegal(i , j+2)) {
                if (gameCells[i][j].getMember() == 'O' && gameCells[i][j + 1].getMember() == 'O' && gameCells[i][j + 2].getMember() == '.') {
                    if(!(isLegal(i+1,j+2)) || gameCells[i+1][j + 2].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 2].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer3Up(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i - 1, j) && isLegal(i-2 , j) && isLegal(i-3, j)) {
                if (gameCells[i][j].getMember() == 'X' && gameCells[i-1][j].getMember() == 'X' && gameCells[i-2][j].getMember() == 'X' && gameCells[i-3][j].getMember() == '.') {
                    if(gameCells[i-3][j].getMember() == '.') {
                        if(status == 0) {
                            gameCells[i - 3][j].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer3UpO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i - 1, j) && isLegal(i-2 , j) && isLegal(i-3, j)) {
                if (gameCells[i][j].getMember() == 'O' && gameCells[i-1][j].getMember() == 'O' && gameCells[i-2][j].getMember() == 'O' && gameCells[i-3][j].getMember() == '.') {
                    if(gameCells[i-3][j].getMember() == '.') {
                        if(status == 0) {
                            gameCells[i - 3][j].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer2Up(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i - 1, j) && isLegal(i-2 , j)) {
                if (gameCells[i][j].getMember() == 'X' && gameCells[i-1][j].getMember() == 'X' &&  gameCells[i-2][j].getMember() == '.') {
                    if(gameCells[i-2][j].getMember() == '.') {
                        if(status == 0) {
                            gameCells[i - 2][j].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computer2UpO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i - 1, j) && isLegal(i-2 , j)) {
                if (gameCells[i][j].getMember() == 'O' && gameCells[i-1][j].getMember() == 'O' &&  gameCells[i-2][j].getMember() == '.') {
                    if(gameCells[i-2][j].getMember() == '.') {
                        if(status == 0) {
                            gameCells[i - 2][j].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computerUp(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i - 1, j) && isLegal(i-2 , j)) {
                if (gameCells[i][j].getMember() == 'X' &&  gameCells[i-1][j].getMember() == '.') {
                    if(gameCells[i-1][j].getMember() == '.') {
                        if(status == 0) {
                            gameCells[i - 1][j].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computerUpO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i - 1, j) && isLegal(i-2 , j)) {
                if (gameCells[i][j].getMember() == 'O' &&  gameCells[i-1][j].getMember() == '.') {
                    if(gameCells[i-1][j].getMember() == '.') {
                        if(status == 0) {
                            gameCells[i - 1][j].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computerRight(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j+1) && isLegal(i , j+2)) {
                if (gameCells[i][j].getMember() == 'X' && gameCells[i][j + 1].getMember() == '.') {
                    if(!(isLegal(i+1,j+1)) || gameCells[i+1][j + 1].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 1].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computerRightO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j+1) && isLegal(i , j+2)) {
                if (gameCells[i][j].getMember() == 'O' && gameCells[i][j + 1].getMember() == '.') {
                    if(!(isLegal(i+1,j+1)) || gameCells[i+1][j + 1].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 1].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computerLeft(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j-1) && isLegal(i , j-2)) {
                if (gameCells[i][j].getMember() == 'X' &&  gameCells[i][j - 1].getMember() == '.') {
                    if(!(isLegal(i+1,j-1)) || gameCells[i+1][j - 1].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j - 1].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computerLeftO(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j-1) && isLegal(i , j-2)) {
                if (gameCells[i][j].getMember() == 'O' &&  gameCells[i][j - 1].getMember() == '.') {
                    if(!(isLegal(i+1,j-1)) || gameCells[i+1][j - 1].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j - 1].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computerMid(){
    int status = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < column; ++j) {
            if (isLegal(i, j+1) && isLegal(i , j-1)) {
                if (gameCells[i][j-1].getMember() == 'X'  && gameCells[i][j + 1].getMember() == 'X' && gameCells[i][j].getMember() == '.') {
                    if(!(isLegal(i+1,j)) || gameCells[i+1][j].getMember() != '.') {
                        if(status == 0) {
                            gameCells[i][j].setMember('O');
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int ConnectFour::computerAI(){
    if(computer3RightO()){
        return 0;
    }
    else if(computer3LeftO()){
        return 0;
    }
    else if(computer3UpO()){
        return 0;
    }
    else if(computer3Up()){
        return 0;
    }
    else if(computer3Left()){
        return 0;
    }
    else if(computer3Right()){
        return 0;
    }
    else if(computerMid()){
        return 0;
    }
    else if(computer2Right()){
        return 0;
    }
    else if(computer2Up()){
        return 0;
    }
    else if(computer2Left()){
        return 0;
    }
    else if(computer2UpO()){
        return 0;
    }
    else if(computer2LeftO()){
        return 0;
    }
    else if(computer2RightO()){
        return 0;
    }
    else if(computerUp()){
        return 0;
    }
    else if(computerRight()){
        return 0;
    }
    else if(computerLeft()){
        return 0;
    }
    else if(computerUpO()){
        return 0;
    }
    else if(computerRightO()){
        return 0;
    }
    else if(computerLeftO()){
        return 0;
    }

    return 0;
}


//PVP icin P,PVC icin C inputu alir.
void ConnectFour::inputGameType(){
    string type;
    bool flag2 = true;
    while(flag2){
        cout << "PVP or PVC: ";
        cin >> type;

        if(type[0] == 'P'){
            gameType = 'P';
            flag2 = false;
        }
        else if(type[0] == 'C'){
            gameType = 'C';
            flag2 = false;
        }
        else if(type.length() == 0){
            exit(1);
        }
        else
            cout << "Tekrar deneyiniz" << endl;
    }
}

void ConnectFour::saveGame(string filename)const{
    ofstream save;

    save.open(filename);

    save << turnCell << endl;
    save << gameType << endl;
    save << row << endl;
    save << column << endl;
    save << player1 << endl;
    if(gameType == 'P')
        save << player2 << endl;
    else{
        save << computer << endl;
    }

    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++ )
        {
            save << gameCells[i][j].getMember();
        }
	save << endl;
    }
    save.close();
}

void ConnectFour::loadGame(string filename){
    char tmp;
    ifstream load;
    load.open(filename);
    if(load.fail())
        cerr << "DOSYA ACILMADI" << endl;
    else{
        //Önceki boardi siliyorum.
       for(int i = 0;i < row;i++){
            delete gameCells[i];
        }
        delete[] gameCells;
        //livingCelli dogru bulmak icin
        livingCells -=turnCell;
        load >> turnCell;
        livingCells +=turnCell;
        load >> gameType;
        load >> row;
        load >> column;
        load >> player1;
        if(gameType == 'P'){
            load >> player2;
        }
        else if(gameType == 'C'){
            load >> computer;
        }
        //yeni satir sutuna göre yer aliyorum.
        gameCells = new Cell*[row];
        for(int i = 0;i < row;i++){
            gameCells[i] = new Cell[column];
        }      

        string line;
        getline(load,line); 
        char x;

        //txt ten board i okuyorum
        for(int k =0;k < row;k++){
            getline(load,line);
            for(int l =0 ;l < column;l++){
                x = line[l];
                Cell obje(x,k,l);
                gameCells[k][l] = obje;
            }
        }
            load.close();
    }
}

//hamle yerini girdi aliyor.
void ConnectFour::inputPos(string& pos){
    cin >> pos;
    if(cin.fail())
        exit(1);
}


//empty den user1 e, user1 den user2 ye, user2 den computera cevirir.
ConnectFour::Cell ConnectFour::Cell::operator++(int){
    char tempMember = cellMember;
    if(cellMember == '.')
        cellMember == 'X';
    else if(cellMember == 'X')
        cellMember == 'O';
    else if(cellMember == 'O'){
        cellMember == '.';
    }

    return Cell(tempMember,x,y);
}
//empty den user1 e, user1 den user2 ye, user2 den computera cevirir.
ConnectFour::Cell& ConnectFour::Cell::operator++(){
    if(cellMember == '.')
        cellMember == 'X';
    else if(cellMember == 'X')
        cellMember == 'O';
    else if(cellMember == 'O'){
        cellMember == '.';
    }
    return *this;
}



ConnectFour::Cell& ConnectFour::Cell::operator--(){
    if(cellMember == 'X')
        cellMember == '.';
    else if(cellMember == 'O')
        cellMember == 'X';
    else if(cellMember == '.'){
        cellMember == 'O';
    }
    return *this;
}

ConnectFour::Cell ConnectFour::Cell::operator--(int){
    char tempMember = cellMember;
    if(cellMember == 'X')
        cellMember == '.';
    else if(cellMember == 'O')
        cellMember == 'X';
    else if(cellMember == '.'){
        cellMember == 'O';
    }

    return Cell(tempMember,x,y);    
}



bool ConnectFour::Cell::operator==(const Cell& other)const{
    return (x == other.x && y == other.y && cellMember == other.cellMember);
}

bool ConnectFour::Cell::operator!=(const Cell& other)const{
    return !(*this == other);
}



bool ConnectFour::operator==(const ConnectFour& other)const{
    if(row != other.row && column != other.column && gameType != other.gameType && player1 != other.player1)
        return false;

    for (int i = 0; i < row; ++i)
        for (int j = 0; j < column; ++j)
        {
            if(gameCells[i][j] != other.gameCells[i][j])
                return false;
        }
    return true;
    
}
bool ConnectFour::operator!=(const ConnectFour& other)const{
    return !(*this == other);
}
//Destructor
ConnectFour::~ConnectFour(){
   for(int i = 0;i < row;i++){
        delete gameCells[i];
    }
    delete[] gameCells;
}

ConnectFour::ConnectFour(const ConnectFour& obje){
    row = obje.row;
    column =obje.column;
    gameType = obje.gameType;
    done = obje.done;
    player1 = obje.player1;
    player2 = obje.player2;
    computer = obje.player2;
    turnCell = obje.turnCell;
    flag = obje.flag;
    gameMode = obje.gameMode;
    _filename = obje._filename;

    gameCells = new Cell*[row];
    for(int i = 0;i < row;i++){
        gameCells[i] = new Cell[column];
    }

    for(int k = 0;k < row;k++){
        for(int j = 0;j < column;j++){
            gameCells[k][j] = obje.gameCells[k][j];
        }
    }
}

ConnectFour& ConnectFour::operator=(const ConnectFour& rightSide){
    if(this == &rightSide){
        return *this;
    }
   for(int i = 0;i < row;i++){
        delete gameCells[i];
    }
    delete[] gameCells;

    row = rightSide.row;
    column =rightSide.column;
    gameType = rightSide.gameType;
    done = rightSide.done;
    player1 = rightSide.player1;
    player2 = rightSide.player2;
    computer = rightSide.player2;
    turnCell = rightSide.turnCell;
    flag = rightSide.flag;
    gameMode = rightSide.gameMode;
    _filename = rightSide._filename;

    gameCells = new Cell*[row];
    for(int i = 0;i < row;i++){
        gameCells[i] = new Cell[column];
    }

    for(int k = 0;k < row;k++){
        for(int j = 0;j < column;j++){
            gameCells[k][j] = rightSide.gameCells[k][j];
        }
    }

    return *this;
}