#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

int get_int(int min); // Tip kontrolü icin global fonk. fonksiyonu internetten buldum.
inline void inputClear(){cin.clear();cin.ignore(1000,'\n');};//input alirken sikinti olmamasi icin

class ConnectFour{
public:
    //construct
    ConnectFour();
    ConnectFour(int newColumn,int newRow);
    ConnectFour(int newColumn,int newRow,char gameType);
    //Vektorü init ediyor.
    void initCells();
    //Oyunu oynayan ana fonksiyon.
    void playGame();
    //vektoru print eder
    void print()const;
    //satir ve sutun degerlerini verir
    const int getRow()const;
    const int getColumn()const;
    //oyunun döngüsünü kontrol eden degiskeni return eder.
    const bool getDone()const;
    //satir sutunu kullanicadan ister.
    void inputRow();
    void inputColumn();
    //Oyun tipini kullanicidan ister
    void inputGameType();
    //Oyun modunu set eder.
    void setGameMode(char newGameMod);
    //iki objenin hangisinin daha iyi durumda oldugunu karsilastirir
    bool compare( const ConnectFour& newObje) const;

private:
    //private inner class
    class Cell{
    public:
        //construct
        Cell(char other,int newColumn,int newRow);
        Cell(char other){CellMember = other;}
        //setter
        void setA(char newA){ CellMember = newA; }
        //bu setterlari hic kullanmadim
        void setX(int newX){ x = newX;}
        void setY(int newY){ y = newY;}
        //getter
        //En basta getA diye koydum denemek icin.Cok fazla kullanlip unutunca ismi böyle kaldi.
        char getA() const {return CellMember;}
        //bu getterlari hic kullanmadim.Koordlari return ediyor.
        int getX()const{return x;}
        int getY()const{return y;}

    private:
        char CellMember; //board icindeki gösterimler
        //asagidaki ikisi degiskeni kullanmadim hic.Koord. tutuyor.
        int x;
        int y;
    };
    //ConnectFour Function
    //Sadece class fonksiyonlarındayken ulaşılabilmesi icin private.Parametrelerde degisiklik yaptigi icin.
    //Dosya okuyan ve kaydeden fonk.lar
    void loadGame(string filename);
    void saveGame(string filename)const;
    //parametreli PVP hamlesi,parametresi bilgisayar hamlesi
    void play(string newPosition);
    void play();
    //Oyun modlarini ayristirdim.
    void PVP();
    void PVC();
    //bilgisayarin hamlenin nasýl yapilcagina karar verir.
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

//--------------------------------------------------------------------------------------

    //ConnectFour MEMBER
    vector< vector<Cell> > gameCells;
    static int livingCells;
    int row;
    int column;
    char gameType;
    //hamle sirasini tutan degiskenler
    bool player1;
    bool player2;
    bool computer;
    //oyunun bitip bitmedigini tutan degisken
    bool done;
    char gameMode;
    //load save ederken livingcelli dogru tutabilmek icin anlik hamle sayisini tuTan dgsnk.
    int turnCell;
    //flag Multi modda karsilikli oynandiktan sonra diger objeye gecmesi icin tuttum.
    bool flag;
};
int ConnectFour::livingCells = 0;

int main(){
    char Mode;
    bool check = true;//programin kapatilip kapatilmamasi icin.
    while(check){
        cout << "Oyun Modu Seciniz: M | S: ";
        cin >> Mode;
        //Single Mod
        if(Mode == 'S'){
            ConnectFour obje1;
            obje1.setGameMode('S');
            obje1.inputColumn();
            obje1.inputRow();
            obje1.initCells();
            cout << "P | C: ";
            obje1.inputGameType();
            obje1.playGame();
            check = false;
        }
        //Multi Mod
        else if(Mode == 'M'){
            ConnectFour obje1,obje2,obje3,obje4,obje5;
            int objeNumber;
            obje1.setGameMode('M');
            cout << "obje1: " << endl;
            obje1.inputColumn();
            obje1.inputRow();
            obje1.initCells();
            cout << "P | C: ";
            obje1.inputGameType();

            obje2.setGameMode('M');
            cout << "obje2: " << endl;
            obje2.inputColumn();
            obje2.inputRow();
            obje2.initCells();
            cout << "P | C: ";
            obje2.inputGameType();

            obje3.setGameMode('M');
            cout << "obje3: " << endl;
            obje3.inputColumn();
            obje3.inputRow();
            obje3.initCells();
            cout << "P | C: ";
            obje3.inputGameType();

            obje4.setGameMode('M');
            cout << "obje4: " << endl;
            obje4.inputColumn();
            obje4.inputRow();
            obje4.initCells();
            cout << "P | C: ";
            obje4.inputGameType();

            obje5.setGameMode('M');
            cout << "obje5: " << endl;
            obje5.inputColumn();
            obje5.inputRow();
            obje5.initCells();
            cout << "P | C: ";
            obje5.inputGameType();
            //tüm objeler bitince oyun biter.
            while(!(obje1.getDone()) || !(obje2.getDone()) || !(obje3.getDone()) || !(obje4.getDone()) || !(obje5.getDone())){
                cout << "Obje numarasi giriniz: ";
                objeNumber = get_int(0); //hangi boardi secicegini belirler.
                if(objeNumber == 1){
                    obje1.playGame();
                    if(obje1.compare(obje2)){
                        cout << "O1 > O2" << endl;
                    }
                    else{
                        cout << "O2 > O1" << endl;
                    }
                }
                else if(objeNumber == 2){
                    obje2.playGame();
                    if(obje2.compare(obje3)){
                        cout << "O2 > O3" << endl;
                    }
                    else{
                        cout << "O3 > O2" << endl;
                    }
                }
                else if(objeNumber == 3){
                    obje3.playGame();
                    if(obje3.compare(obje4)){
                        cout << "O3 > O4" << endl;
                    }
                    else{
                        cout << "O4 > O3" << endl;
                    }
                }
                else if(objeNumber == 4){
                    obje4.playGame();
                    if(obje4.compare(obje5)){
                        cout << "O4 > O5" << endl;
                    }
                    else{
                        cout << "O5 > O4" << endl;
                    }
                }
                else if(objeNumber == 5){
                    obje5.playGame();
                    if(obje5.compare(obje1)){
                        cout << "O5 > O1" << endl;
                    }
                    else{
                        cout << "O1 > O5" << endl;
                    }
                }
                else{
                    cout << "Hatali Komut" << endl;
                }
            }
            check = false;
        }
        else{
            cout << "Tekrar Giriniz" << endl;
        }
    }
    return 0;
}

//Constructs
ConnectFour::ConnectFour(){
    row = 10;
    column = 10;
    initCells();
    done = false;
    player1 = true;
    player2 = false;
    computer = false;
    flag = true;
    turnCell = 0;
}

ConnectFour::ConnectFour(int newColumn,int newRow) {
    column = newColumn;
    row = newRow;
    initCells();
    done = false;
    player1 = true;
    player2 = false;
    computer = false;
    flag = true;
    turnCell = 0;

}

ConnectFour::ConnectFour(int newColumn,int newRow,char gameType){
    initCells();
    column = newColumn;
    row = newRow;
    gameType = 'P';
    done = false;
    player1 = true;
    player2 = false;
    computer = false;
    flag = true;
    turnCell = 0;

}




void ConnectFour::initCells(){
    gameCells.clear();//load edince sikinti olmasin diye.
    for(int i = 0; i < row; i++){
        vector<Cell> temp;
        for(int j = 0; j < column; j++){
           ConnectFour::Cell c('.',i,j);
           temp.push_back(c);
        }
        gameCells.push_back(temp);
    }
}

void ConnectFour::print()const{
    for(int i = 0; i < column; ++i) {
        cout << (char)('A' + i) << ' ';
    }
    cout << endl;
    for(int i = 0;i < row; i++){
        for(int j = 0;j < column; j++){
            cout << gameCells[i][j].getA();
            cout << " ";
        }
        cout << endl;
    }
}

void ConnectFour::PVP()
{
        string position;//sütun inputunu aldigimiz degisken.
        print();
        while(!(done) && flag){
            if(player1){
                if(gameType == 'P'){
                    cout << "P1 sutun giriniz: ";
                    cin >> position;
                    play(position);
                    print();
                    cout << "Living Cell: " << getLiving() << endl;
                    gameFinishPvP();
                }
                else if(gameType == 'C'){//pvp de pvc cagirirsa
                    PVC();
                    flag = false;
                }
            }
            else if(player2){
                if(gameType == 'P'){
                    cout << "P2 sutun giriniz: ";
                    cin >> position;
                    play(position);
                    print();
                    cout << "Living Cell: " << getLiving() << endl;
                    gameFinishPvP();
                }
                else if(gameType == 'C'){//pvp de pvc cagirirsa
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
        print();
        while(!(done) && flag){
            if(player1){
                if(gameType == 'C'){
                    cout << "P1 sutun giriniz: ";
                    cin >> position;
                    play(position);
                    print();
                    cout << "Living Cell: " << getLiving() << endl;
                    gameFinishPvP();
                }
                else if(gameType == 'P'){//pvc icinde pvp cagirirsa
                    PVP();
                    flag = false;
                }
            }
            else if(computer){
                print();
                play();
                print();
                gameFinishPvC();
                if(gameMode == 'M' && position != "SAVE" && position != "LOAD")
                    flag = false;
            }
        }
        flag = true;
}
void ConnectFour::playGame(){
    if(gameType == 'P'){
            PVP();
    }

    else if( gameType == 'C'){
            PVC();
    }
}
//Kodu classin icinde implement edip etmeyecegini compiler karar verir.
inline const int ConnectFour::getRow()const{
    return row;
}
//Kodu classin icinde implement edip etmeyecegini compiler karar verir.
inline const int ConnectFour::getColumn()const{
    return column;
}
//Kodu classin icinde implement edip etmeyecegini compiler karar verir.
inline const bool ConnectFour::getDone()const{
    return done;
}
inline void ConnectFour::setGameMode(char newGameMod){
    gameMode = newGameMod;
}

void ConnectFour::inputGameType(){
    char type;
    bool flag2 = true;
    while(flag2){
        cout << "PVP or PVC: ";
        cin >> type;

        if(type == 'P'){
            gameType = 'P';
            flag2 = false;
        }
        else if(type == 'C'){
            gameType = 'C';
            flag2 = false;
        }
        else
            cout << "Tekrar deneyiniz" << endl;
    }
}

ConnectFour::Cell::Cell(char other,int newColumn,int newRow){
    CellMember = other;
    y = newColumn;
    x = newRow;
}

void ConnectFour::play(string newPosition){
    string dosyaismi;
    bool status = true;//Hata mesajini verebilmek icin.
    if(newPosition == "SAVE"){
        cin >> dosyaismi;
        inputClear();
        saveGame(dosyaismi);
        status = false;
        cout << "OYUN KAYDEDILDI" << endl;
    }
    else if(newPosition == "LOAD"){
        cin >> dosyaismi;
        inputClear();
        loadGame(dosyaismi);
        cout << "OYUN YUKLENDI." << endl;
        print();
        status = false;
    }
    else{
        for (int i = 0; i < column; ++i) {
            if (newPosition[0] == 'A' + i) {
                for (int j = 0; j < row; ++j) {
                    if (gameCells[row - j - 1][i].getA() == '.') {
                        if(status)
                        {
                            if(player1){
                                gameCells[row - j - 1][i].setA('X');
                                //Hamle siralarini degistiriyorum.
                                player1 = false;
                                player2 = true;
                                computer = true;
                                livingCells++;
                                turnCell++;
                                inputClear();
                            }
                            else if(player2){
                                //Hamle siralarini degistiriyorum.
                                gameCells[row - j - 1][i].setA('O');
                                player1 = true;
                                player2 = false;
                                livingCells++;
                                turnCell++;
                                inputClear();
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

void ConnectFour::play(){
    computerAI();
    livingCells++;
    turnCell++;
    computer = false;
    player1 = true;
}

void ConnectFour::gameFinishPvC(){

        if (isFinishedO() || crossFinishedO()) {
            done = true;
            cout << "BILGISAYAR KAZANDI" << endl;;
            print();
        }
        else if (isFinishedX() || crossFinishedX()) {
            done = true;
            cout << "KAZANDINIZ" << endl;;
            print();
        }
        else if (isFilled()) {
            done = true;
            cout << "BERABERE" << endl;
            print();
        }
}

void ConnectFour::gameFinishPvP(){

        if (isFinishedO() || crossFinishedO()) {
            done = true;
            cout << "PLAYER2 KAZANDI" << endl;;
            print();
        }
        else if (isFinishedX() || crossFinishedX()) {
            done = true;
            cout << "PLAYER1 KAZANDI" << endl;;
            print();
        }
        else if (isFilled()) {
            done = true;
            cout << "BERABERE" << endl;
            print();
        }
}

void ConnectFour::toLower(int x,int y){
    if(gameCells[x][y].getA() == 'X')
        gameCells[x][y].setA('x');
    else if(gameCells[x][y].getA() == 'O')
        gameCells[x][y].setA('o');
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
            if(gameCells[i][j].getA() == '.')
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
                if (gameCells[i][j].getA() == 'O' && gameCells[i + 1][j].getA() == 'O' && gameCells[i + 2][j].getA() == 'O' && gameCells[i + 3][j].getA() == 'O') {
                    toLower(i, j);
                    toLower(i + 1, j);
                    toLower(i + 2, j);
                    toLower(i + 3, j);
                    status = 1;
                }
            }
            if (isLegal(i, j + 1) && isLegal(i, j + 2) && isLegal(i, j + 3)) {
                if (gameCells[i][j].getA() == 'O' && gameCells[i][j+1].getA() == 'O' && gameCells[i][j + 2].getA() == 'O' && gameCells[i][j + 3].getA() == 'O') {
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
                if (gameCells[i][j].getA() == 'X' && gameCells[i + 1][j].getA() == 'X' && gameCells[i + 2][j].getA() == 'X' && gameCells[i + 3][j].getA() == 'X') {
                    toLower(i, j);
                    toLower(i + 1, j);
                    toLower(i + 2, j);
                    toLower(i + 3, j);
                    status = 1;
                }
            }
            if (isLegal(i, j + 1) && isLegal(i, j + 2) && isLegal(i, j + 3)) {
                if (gameCells[i][j].getA() == 'X' && gameCells[i][j+1].getA() == 'X' && gameCells[i][j + 2].getA() == 'X' && gameCells[i][j + 3].getA() == 'X') {
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
                if(gameCells[i][j].getA() == 'O' && gameCells[i+1][j+1].getA() == 'O' && gameCells[i+2][j+2].getA() == 'O' && gameCells[i+3][j+3].getA() == 'O') {
                    toLower(i,j);
                    toLower(i+1,j+1);
                    toLower(i+2,j+2);
                    toLower(i+3,j+3);
                    status = 1;
                }
            }
            if(isLegal(i-1,j+1) && isLegal(i-2,j+2) && isLegal(i-3,j+3)){
                 if(gameCells[i][j].getA() == 'O' && gameCells[i-1][j+1].getA() == 'O' && gameCells[i-2][j+2].getA() == 'O' && gameCells[i-3][j+3].getA() == 'O') {
                     toLower(i,j);
                     toLower(i-1,j+1);
                     toLower(i-2,j+2);
                     toLower(i-3,j+3);
                     status = 1;
                 }
            }
            if(isLegal(i+1,j-1) && isLegal(i+2,j-2) && isLegal(i+3,j-3)){
                 if(gameCells[i][j].getA() == 'O' && gameCells[i+1][j-1].getA() == 'O' && gameCells[i+2][j-2].getA() == 'O' && gameCells[i+3][j-3].getA() == 'O') {
                     toLower(i,j);
                     toLower(i+1,j-1);
                     toLower(i+2,j-2);
                     toLower(i+3,j-3);
                     status = 1;
                 }
            }
            if(isLegal(i-1,j-1) && isLegal(i-2,j-2) && isLegal(i-3,j-3)) {
                if (gameCells[i][j].getA() == 'O' && gameCells[i-1][j-1].getA() == 'O' && gameCells[i-2][j-2].getA() == 'O' &&
                    gameCells[i-3][j-3].getA() == 'O') {
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
                if(gameCells[i][j].getA() == 'X' && gameCells[i+1][j+1].getA() == 'X' && gameCells[i+2][j+2].getA() == 'X' && gameCells[i+3][j+3].getA() == 'X') {
                    toLower(i,j);
                    toLower(i+1,j+1);
                    toLower(i+2,j+2);
                    toLower(i+3,j+3);
                    status = 1;
                }
            }
            if(isLegal(i-1,j+1) && isLegal(i-2,j+2) && isLegal(i-3,j+3)){
                 if(gameCells[i][j].getA() == 'X' && gameCells[i-1][j+1].getA() == 'X' && gameCells[i-2][j+2].getA() == 'X' && gameCells[i-3][j+3].getA() == 'X') {
                     toLower(i,j);
                     toLower(i-1,j+1);
                     toLower(i-2,j+2);
                     toLower(i-3,j+3);
                     status = 1;
                 }
            }
            if(isLegal(i+1,j-1) && isLegal(i+2,j-2) && isLegal(i+3,j-3)){
                 if(gameCells[i][j].getA() == 'X' && gameCells[i+1][j-1].getA() == 'X' && gameCells[i+2][j-2].getA() == 'X' && gameCells[i+3][j-3].getA() == 'X') {
                     toLower(i,j);
                     toLower(i+1,j-1);
                     toLower(i+2,j-2);
                     toLower(i+3,j-3);
                     status = 1;
                 }
            }
            if(isLegal(i-1,j-1) && isLegal(i-2,j-2) && isLegal(i-3,j-3)) {
                if (gameCells[i][j].getA() == 'X' && gameCells[i-1][j-1].getA() == 'X' && gameCells[i-2][j-2].getA() == 'X' &&
                    gameCells[i-3][j-3].getA() == 'X') {
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
                if (gameCells[i][j].getA() == 'X' && gameCells[i][j + 1].getA() == 'X' && gameCells[i][j + 2].getA() == 'X' && gameCells[i][j+3].getA() == '.') {
                    if(!(isLegal(i+1,j+3)) || gameCells[i+1][j + 3].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 3].setA('O');
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
                if (gameCells[i][j].getA() == 'O' && gameCells[i][j + 1].getA() == 'O' && gameCells[i][j + 2].getA() == 'O' && gameCells[i][j+3].getA() == '.') {
                    if(!(isLegal(i+1,j+3)) || gameCells[i+1][j + 3].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 3].setA('O');
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
                if (gameCells[i][j].getA() == 'X' && gameCells[i][j - 1].getA() == 'X' && gameCells[i][j - 2].getA() == 'X' && gameCells[i][j-3].getA() == '.') {
                    if(!(isLegal(i+1,j-3)) || gameCells[i+1][j - 3].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 3].setA('O');
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
                if (gameCells[i][j].getA() == 'O' && gameCells[i][j - 1].getA() == 'O' && gameCells[i][j - 2].getA() == 'O' && gameCells[i][j-3].getA() == '.') {
                    if(!(isLegal(i+1,j-3)) || gameCells[i+1][j - 3].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 3].setA('O');
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
                if (gameCells[i][j].getA() == 'X' && gameCells[i][j - 1].getA() == 'X' && gameCells[i][j - 2].getA() == '.') {
                    if(!(isLegal(i+1,j-2)) || gameCells[i+1][j - 2].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j - 2].setA('O');
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
                if (gameCells[i][j].getA() == 'O' && gameCells[i][j - 1].getA() == 'O' && gameCells[i][j - 2].getA() == '.') {
                    if(!(isLegal(i+1,j-2)) || gameCells[i+1][j - 2].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j - 2].setA('O');
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
                if (gameCells[i][j].getA() == 'X' && gameCells[i][j + 1].getA() == 'X' && gameCells[i][j + 2].getA() == '.') {
                    if(!(isLegal(i+1,j+2)) || gameCells[i+1][j + 2].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 2].setA('O');
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
                if (gameCells[i][j].getA() == 'O' && gameCells[i][j + 1].getA() == 'O' && gameCells[i][j + 2].getA() == '.') {
                    if(!(isLegal(i+1,j+2)) || gameCells[i+1][j + 2].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 2].setA('O');
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
                if (gameCells[i][j].getA() == 'X' && gameCells[i-1][j].getA() == 'X' && gameCells[i-2][j].getA() == 'X' && gameCells[i-3][j].getA() == '.') {
                    if(gameCells[i-3][j].getA() == '.') {
                        if(status == 0) {
                            gameCells[i - 3][j].setA('O');
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
                if (gameCells[i][j].getA() == 'O' && gameCells[i-1][j].getA() == 'O' && gameCells[i-2][j].getA() == 'O' && gameCells[i-3][j].getA() == '.') {
                    if(gameCells[i-3][j].getA() == '.') {
                        if(status == 0) {
                            gameCells[i - 3][j].setA('O');
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
                if (gameCells[i][j].getA() == 'X' && gameCells[i-1][j].getA() == 'X' &&  gameCells[i-2][j].getA() == '.') {
                    if(gameCells[i-2][j].getA() == '.') {
                        if(status == 0) {
                            gameCells[i - 2][j].setA('O');
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
                if (gameCells[i][j].getA() == 'O' && gameCells[i-1][j].getA() == 'O' &&  gameCells[i-2][j].getA() == '.') {
                    if(gameCells[i-2][j].getA() == '.') {
                        if(status == 0) {
                            gameCells[i - 2][j].setA('O');
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
                if (gameCells[i][j].getA() == 'X' &&  gameCells[i-1][j].getA() == '.') {
                    if(gameCells[i-1][j].getA() == '.') {
                        if(status == 0) {
                            gameCells[i - 1][j].setA('O');
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
                if (gameCells[i][j].getA() == 'O' &&  gameCells[i-1][j].getA() == '.') {
                    if(gameCells[i-1][j].getA() == '.') {
                        if(status == 0) {
                            gameCells[i - 1][j].setA('O');
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
                if (gameCells[i][j].getA() == 'X' && gameCells[i][j + 1].getA() == '.') {
                    if(!(isLegal(i+1,j+1)) || gameCells[i+1][j + 1].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 1].setA('O');
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
                if (gameCells[i][j].getA() == 'O' && gameCells[i][j + 1].getA() == '.') {
                    if(!(isLegal(i+1,j+1)) || gameCells[i+1][j + 1].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j + 1].setA('O');
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
                if (gameCells[i][j].getA() == 'X' &&  gameCells[i][j - 1].getA() == '.') {
                    if(!(isLegal(i+1,j-1)) || gameCells[i+1][j - 1].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j - 1].setA('O');
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
                if (gameCells[i][j].getA() == 'O' &&  gameCells[i][j - 1].getA() == '.') {
                    if(!(isLegal(i+1,j-1)) || gameCells[i+1][j - 1].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j - 1].setA('O');
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
                if (gameCells[i][j-1].getA() == 'X'  && gameCells[i][j + 1].getA() == 'X' && gameCells[i][j].getA() == '.') {
                    if(!(isLegal(i+1,j)) || gameCells[i+1][j].getA() != '.') {
                        if(status == 0) {
                            gameCells[i][j].setA('O');
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
            save << gameCells[i][j].getA();
            save << ' ';
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
        //Önceki boardin hamle sayisini cikartip yenisi ekliyorum.
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

        //vektörü load ettigimde crash yememesi icin böyle atama yapmam gerekiyor vektörü önceden sildim.
        gameCells.clear();

        for(int i = 0; i < row; i++){
            vector<Cell> v;
            for(int j = 0; j < column; j++){
                load >> tmp;
                ConnectFour::Cell c(tmp,i,j);
                v.push_back(c);
            }
            gameCells.push_back(v);
        }
        load.close();
    }
}

//burada 3 tane x veya 3 tane o bitisikse 2 puan, 2 tane bitisikse 1 puan, böylece hangi oyunun daha ilerde oldugunu tespit eder.
bool ConnectFour::compare(const ConnectFour& newObje) const{
    int point1 = 0,point2 = 0;
    for(int i = 0; i < row;i++){
        for(int j = 0;j < column;j++){
            if(isLegal(i,j) && isLegal(i+1,j) && isLegal(i+2,j)){
                if(gameCells[i][j].getA() == 'X' && gameCells[i + 1][j].getA() == 'X' && gameCells[i + 2][j].getA() == 'X')
                    point1+=2;
            }
            if(isLegal(i,j) && isLegal(i+1,j)){
                if(gameCells[i][j].getA() == 'X' && gameCells[i + 1][j].getA() == 'X'){
                    point1++;
                }
            }
            if(isLegal(i,j) && isLegal(i+1,j) && isLegal(i+2,j)){
                if(gameCells[i][j].getA() == 'O' && gameCells[i + 1][j].getA() == 'O' && gameCells[i + 2][j].getA() == 'O'){
                    point1+=2;
                }
            }
            if(isLegal(i,j) && isLegal(i+1,j))
            if(gameCells[i][j].getA() == 'O' && gameCells[i + 1][j].getA() == 'O'){
                point1++;
            }
        }
    }
    for(int k = 0; k < newObje.getRow();k++){
        for(int l = 0; l < newObje.getColumn();l++){
            if(isLegal(k,l) && isLegal(k+1,l) && isLegal(k+2,l)){
                if(newObje.gameCells[k][l].getA() == 'X' && newObje.gameCells[k + 1][l].getA() == 'X' && newObje.gameCells[k + 2][l].getA() == 'X'){
                    point2+=2;
                }
            }
            if(isLegal(k,l) && isLegal(k+1,l)){
                if(newObje.gameCells[k][l].getA() == 'X' && newObje.gameCells[k + 1][l].getA() == 'X'){
                    point2++;
                }
            }

            if(isLegal(k,l) && isLegal(k+1,l) && isLegal(k+2,l)){
                if(newObje.gameCells[k][l].getA() == 'O' && newObje.gameCells[k + 1][l].getA() == 'O' && newObje.gameCells[k + 2][l].getA() == 'O'){
                    point2+=2;
                }
            }
            if(isLegal(k,l) && isLegal(k+1,l)){
                if(newObje.gameCells[k][l].getA() == 'O' && newObje.gameCells[k + 1][l].getA() == 'O'){
                    point2++;
                }
            }
        }
    }
    return (point1 >= point2);
}

void ConnectFour::inputRow(){
    cout << "Boy giriniz: ";
    row = get_int(4);

}
void ConnectFour::inputColumn(){
    cout << "En giriniz: ";
    inputClear();
    column = get_int(4);

}

int get_int(int min){
 	int ret_integer;
    string str_number;
	while(true) {
        getline(cin, str_number);
		stringstream convert(str_number);
		if(convert >> ret_integer && !(convert >> str_number) && ret_integer >= min){
            return ret_integer;
		}

		cin.clear();
		cerr << "BOYUT >= " << min <<  endl;
	}
}
