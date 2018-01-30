#include "Cell.h"
using namespace std;
namespace cfGame
{
  //0,0 '.' atar.
  Cell::Cell(){
      x = 0;
      y = 0;
      cellMember = '.';
  }

  //3 parametre alir koordinatlar ve icerik
  Cell::Cell(char newMember,int newX,int newY){
      x = newX;
      y = newY;
      cellMember = newMember;
  }

  //koordinatlari ve icerigini set eder.
  void Cell::setMember(char newMember){
      cellMember = newMember;
  }  
}
