#ifndef CONNECTFOUR_UNDO_H
#define CONNECTFOUR_UNDO_H
#include "ConnectFourPlus.h"

namespace cfGame
{
  class ConnectFourUndo : public ConnectFourPlus
  {
  public:
      //constructor
      ConnectFourUndo();
      ConnectFourUndo(int newColumn,int newRow);
      ConnectFourUndo(int newColumn,int newRow,char newGameType);
      void playGame();
  protected:
      //Load ve Save yapan Fonksiyonlar
      void loadGame(string filename);
      void saveGame(string filename)const;
      void play(string newPosition);
      void initUndo();
      void PVP();
      void PVC();
      void play();
      char* undo; //gecmis hamleleri tutulan yer.
      int sizeUndo; //undonun botuyu
      int ctUndo; //o ana kadar oynanmis hamle saiysi
  };
}



#endif // CONNECTFOUR_UNDO_H
