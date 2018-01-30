#include "ConnectFourPlus.h"
#include <iostream>
using namespace std;

namespace cfGame
{

  //constructor
  ConnectFourPlus::ConnectFourPlus()
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
  ConnectFourPlus::ConnectFourPlus(int newColumn,int newRow)
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
  ConnectFourPlus::ConnectFourPlus(int newColumn,int newRow,char newGameType)
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


  int ConnectFourPlus::isFinishedO(){
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

  int ConnectFourPlus::isFinishedX(){
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

  void ConnectFourPlus::gameFinishPvC(){

          if (isFinishedO()) {
              done = true;
              cout << "BILGISAYAR KAZANDI" << endl;
              printCells();
          }
          else if (isFinishedX()) {
              done = true;
              cout << "KAZANDINIZ" << endl;
              printCells();
          }
          else if (isFilled()) {
              done = true;
              cout << "BERABERE" << endl;
              printCells();
          }
  }



  void ConnectFourPlus::gameFinishPvP(){

          if (isFinishedO()) {
              done = true;
              cout << "PLAYER2 KAZANDI" << endl;
              printCells();
          }
          else if (isFinishedX()) {
              done = true;
              cout << "PLAYER1 KAZANDI" << endl;
              printCells();
          }
          else if (isFilled()) {
              done = true;
              cout << "BERABERE" << endl;
              printCells();
          }
  }

}
