#include "ConnectFourDiag.h"
#include <iostream>

using namespace std;

namespace cfGame
{

  //constructor
  ConnectFourDiag::ConnectFourDiag()
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
  ConnectFourDiag::ConnectFourDiag(int newColumn,int newRow)
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
  ConnectFourDiag::ConnectFourDiag(int newColumn,int newRow,char newGameType)
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


  void ConnectFourDiag::gameFinishPvC(){

          if (crossFinishedO()) {
              done = true;
              cout << "BILGISAYAR KAZANDI" << endl;
              printCells();
          }
          else if (crossFinishedX()) {
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



  void ConnectFourDiag::gameFinishPvP(){

          if (crossFinishedO()) {
              done = true;
              cout << "PLAYER2 KAZANDI" << endl;
              printCells();
          }
          else if (crossFinishedX()) {
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

  int ConnectFourDiag::crossFinishedO(){
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

  int ConnectFourDiag::crossFinishedX(){
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

}
