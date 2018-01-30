#ifndef CELL_H
#define CELL_H

namespace cfGame
{
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

  protected:
      //boardin icerigini tutar.
      char cellMember;
      //koordinatlari tutar.
      int x;
      int y;
  };
}

#endif // CELL_H
