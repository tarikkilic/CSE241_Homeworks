#include <iostream>
#include <fstream>
#include "ConnectFourUndo.h"
using namespace std;

namespace cfGame
{
  //constructor
  ConnectFourUndo::ConnectFourUndo()
  {
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
  ConnectFourUndo::ConnectFourUndo(int newColumn,int newRow)
  {
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
  ConnectFourUndo::ConnectFourUndo(int newColumn,int newRow,char newGameType)
  {
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


  void ConnectFourUndo::initUndo()
  {
      undo = new char[row*column]; //cell sayisi kadar yer alinir.
      sizeUndo = row*column;
      ctUndo = 0;
  }



  void ConnectFourUndo::play(string newPosition)
  {
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
      //undo arrayinde en son indexinde en son oynanan sutun harfi tutulur.
      //yukardan bakar ilk nokta olmayan yeri nokta yapar.
      else if(newPosition == "UNDO")
      {

          for (int i = 0; i < column; ++i) {
              if (undo[ctUndo - 1] == 'A' + i) {
                  for (int j = 0; j < row; ++j) {
                      if (gameCells[j][i].getMember() != '.') {
                          if(status)
                          {
                              if(player1){

                                  gameCells[j][i].setMember('.');
                                  //Hamle siralarini degistiriyorum.
                                  player1 = false;
                                  player2 = true;
                                  computer = true;
                                  ctUndo--;
                              }
                              else if(player2){
                                  //Hamle siralarini degistiriyorum.
                                  gameCells[j][i].setMember('.');
                                  player1 = true;
                                  player2 = false;
                                  ctUndo--;
                              }
                              status = false;
                          }
                      }
                  }
              }
          }
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
                                  undo[ctUndo] = newPosition[0];
                                  ctUndo++;
                              }
                              else if(player2){
                                  //Hamle siralarini degistiriyorum.
                                  gameCells[row - j - 1][i].setMember('O');
                                  player1 = true;
                                  player2 = false;
                                  undo[ctUndo] = newPosition[0];
                                  ctUndo++;
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




  void ConnectFourUndo::saveGame(string filename)const{
      ofstream save;

      save.open(filename.c_str());

      save << sizeUndo << endl;
      save << ctUndo << endl;
      save << gameType << endl;
      save << row << endl;
      save << column << endl;
      save << player1 << endl;
      if(gameType == 'P')
          save << player2 << endl;
      else{
          save << computer << endl;
      }
      for(int k = 0; k < sizeUndo;k++){
        save << undo[k] << endl;
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

  void ConnectFourUndo::loadGame(string filename){
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
          delete[] undo;
          load >> sizeUndo;
          load >> ctUndo;
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
          initUndo();
          for(int k = 0; k < sizeUndo; k++){
            load >> undo[k];

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
  void ConnectFourUndo::playGame(){
      inputColumn();
      inputRow();
      initCells();
      initUndo();
      cout << "P | C: ";
      inputGameType();
      if(gameType == 'P'){
          PVP();
      }
      else if(gameType == 'C'){
          PVC();
      }
  }

  void ConnectFourUndo::PVP(){
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

  void ConnectFourUndo::PVC(){
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

  //Bilgisayar hamlesi
  void ConnectFourUndo::play(){
      computerAI();
      computer = false;
      player1 = true;
  }
}
