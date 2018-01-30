#include <iostream>
#include <fstream>//load save
#include <string>//load save
#include <cstdlib>//exit
#include "ConnectFourAbstract.h"
using namespace std;
namespace cfGame
{
    ConnectFourAbstract::ConnectFourAbstract(){
        row = 5;
        column = 5;
        gameType = 'P';
        done = false;
        player1 = true;
        player2 = false;
        computer = false;
        flag = true;
        initCells();
    }

    //row column girerek board init eder.
    ConnectFourAbstract::ConnectFourAbstract(int newRow,int newColumn){
        row = newRow;
        column = newColumn;
        gameType = 'P';
        done = false;
        player1 = true;
        player2 = false;
        computer = false;
        flag = true;
        initCells();
    }

    ConnectFourAbstract::ConnectFourAbstract(int newColumn,int newRow,char newGameType){
        initCells();
        column = newColumn;
        row = newRow;
        gameType = newGameType;
        done = false;
        player1 = true;
        player2 = false;
        flag = true;
        computer = false;
    }
    ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& obje){
        row = obje.row;
        column = obje.column;
        player1 = obje.player1;
        player2 = obje.player2;
        computer = obje.computer;
        done = obje.done;
        gameType = obje.gameType;
        flag = obje.flag;
        initCells();
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                gameCells[i][j] = obje.gameCells[i][j];
            }
        }

    }
    ConnectFourAbstract& ConnectFourAbstract::operator=(const ConnectFourAbstract& obje)
    {
       for(int i = 0;i < row;i++){
            delete gameCells[i];
        }
        delete[] gameCells;
        row = obje.row;
        column = obje.column;
        player1 = obje.player1;
        player2 = obje.player2;
        computer = obje.computer;
        done = obje.done;
        gameType = obje.gameType;
        flag = obje.flag;
        initCells();
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < column; ++j)
            {
                gameCells[i][j] = obje.gameCells[i][j];
            }
        }
        return *this;
    }

    void ConnectFourAbstract::initCells(){
        gameCells = new Cell*[row+1];
        for(int i = 0;i < row;i++){
            gameCells[i] = new Cell[column+1];
        }
    }

    //board bastirir.
    void ConnectFourAbstract::printCells(){
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

    //Oyun tipine g�re fonksiyona girer.
    void ConnectFourAbstract::playGame(){
        inputColumn();
        inputRow();
        initCells();
        cout << "P | C: ";
        inputGameType();
        if(gameType == 'P'){
            PVP();
        }
        else if(gameType == 'C'){
            PVC();
        }
    }

    //Playerin hamlesini gerceklestiren fonksiyon
    void ConnectFourAbstract::play(string newPosition){
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
                                }
                                else if(player2){
                                    //Hamle siralarini degistiriyorum.
                                    gameCells[row - j - 1][i].setMember('O');
                                    player1 = true;
                                    player2 = false;
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
    void ConnectFourAbstract::play(){
        computerAI();
        computer = false;
        player1 = true;
    }

    void ConnectFourAbstract::PVP(){
            string position;//s�tun inputunu aldigimiz degisken.
            printCells();
            while(!(done) && flag){
                if(player1){
                    if(gameType == 'P'){
                        cout << "P1 sutun giriniz: ";
                        inputPos(position);
                        play(position);
                        printCells();
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
                        gameFinishPvP();
                    }
                    if(gameType == 'C'){//pvp de pvc cagirirsa
                        PVC();
                        flag = false;
                    }
                }
            }
            flag = true;
    }

    void ConnectFourAbstract::PVC(){
            string position;//s�tun inputunu aldigimiz degisken.
            printCells();
            while(!(done) && flag){
                if(player1){
                    if(gameType == 'C'){
                        cout << "P1 sutun giriniz: ";
                        inputPos(position);
                        play(position);
                        printCells();
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
                }
            }
            flag = true;
    }

  
    void ConnectFourAbstract::toLower(int x,int y){
        if(gameCells[x][y].getMember() == 'X')
            gameCells[x][y].setMember('x');
        else if(gameCells[x][y].getMember() == 'O')
            gameCells[x][y].setMember('o');
    }
    int ConnectFourAbstract::isLegal(int newX,int newY)const{
        int status = 0;
        if(newX >= 0 && newY >= 0 && newX < row && newY < column)
            status = 1;

        return status;

    }
    int ConnectFourAbstract::isFilled()const{
        int status = 1;

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < column; ++j) {
                if(gameCells[i][j].getMember() == '.')
                    status = 0;
            }
        }
        return status;
    }

    int ConnectFourAbstract::computer3Right(){
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

    int ConnectFourAbstract::computer3RightO(){
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

    int ConnectFourAbstract::computer3Left(){
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

    int ConnectFourAbstract::computer3LeftO(){
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

    int ConnectFourAbstract::computer2Left(){
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

    int ConnectFourAbstract::computer2LeftO(){
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

    int ConnectFourAbstract::computer2Right(){
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

    int ConnectFourAbstract::computer2RightO(){
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

    int ConnectFourAbstract::computer3Up(){
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

    int ConnectFourAbstract::computer3UpO(){
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

    int ConnectFourAbstract::computer2Up(){
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

    int ConnectFourAbstract::computer2UpO(){
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

    int ConnectFourAbstract::computerUp(){
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

    int ConnectFourAbstract::computerUpO(){
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

    int ConnectFourAbstract::computerRight(){
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

    int ConnectFourAbstract::computerRightO(){
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

    int ConnectFourAbstract::computerLeft(){
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

    int ConnectFourAbstract::computerLeftO(){
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

    int ConnectFourAbstract::computerMid(){
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

    int ConnectFourAbstract::computerAI(){
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
    void ConnectFourAbstract::inputGameType(){
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

    void ConnectFourAbstract::saveGame(string filename)const{
        ofstream save;

        save.open(filename.c_str());


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
                save << ' ';
            }
    	save << endl;
        }
        save.close();
    }

    void ConnectFourAbstract::loadGame(string filename){
        char tmp;
        ifstream load;
        load.open(filename.c_str());
        if(load.fail())
            cerr << "DOSYA ACILMADI" << endl;
        else{
            //�nceki boardi siliyorum.
           for(int i = 0;i < row;i++){
                delete gameCells[i];
            }
            delete[] gameCells;
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
            //yeni satir sutuna g�re yer aliyorum.
            gameCells = new Cell*[row];
            for(int i = 0;i < row;i++){
                gameCells[i] = new Cell[column];
            }

            for(int i = 0; i < row; i++){
                for(int j = 0; j < column; j++){
                    load >> tmp;
                    Cell c(tmp,i,j);
                    gameCells[i][j] = c;
                }
            }
            load.close();
        }
    }

    //hamle yerini girdi aliyor.
    void ConnectFourAbstract::inputPos(string& pos){
        cin >> pos;
        if(cin.fail())
            exit(1);
    }

    //Destructor
    ConnectFourAbstract::~ConnectFourAbstract(){
      for(int i = 0;i < row;i++){
           delete gameCells[i];
       }
       delete[] gameCells;

    }

    void ConnectFourAbstract::inputRow(){
        cout << "Boy giriniz: ";
        cin >> row;

    }
    void ConnectFourAbstract::inputColumn(){
        cout << "En giriniz: ";
        cin >> column;

    }
}
