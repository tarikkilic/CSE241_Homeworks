#include <iostream>
#include <sstream>
using namespace std;
const int MAX_SIZE = 20;

//prototypes
void initBoard(int board[][MAX_SIZE],int size);
void printBoard(int board[][MAX_SIZE],int size);
void gameLoop(int board[][MAX_SIZE],int size);//Oyun döngüsü bu fonk içinde yer alır.
void PvP(int board[][MAX_SIZE],int size);// Player vs player fonksiyonu
void PvC(int board[][MAX_SIZE],int size);//Player vs computer fonksiyonu
int player1Move(int board[][MAX_SIZE],int size);
int player2Move(int board[][MAX_SIZE],int size);


//Oyunun bitip bitmediğini kontrol eden fonksiyonlar.
int isFilled(int board[][MAX_SIZE],int size); //Berabere bittiğini kontrol eder.
int isFinishedO(int board[][MAX_SIZE],int size); // O ların bittiğini kontrol eder.
int isFinishedX(int board[][MAX_SIZE],int size); // X lerin bittiğini kontrol eder.
int crossFinishedO(int board[][MAX_SIZE],int size); //O ların çapraz bittiğni kontrol eder.
int crossFinishedX(int board[][MAX_SIZE],int size); // X lerin çapraz bittiğni kontrol eder.
//flag değişkeni burada gameLoop un içinde ki döngüdeki done değişkenini etkiler.
void gameFinishPvP(int board[][MAX_SIZE],int size,bool &flag); //PvP seçeneğinde oyunun bittiğni kontrol eder.
void gameFinishPvC(int board[][MAX_SIZE],int size,bool &flag); //PvC seçeneğinde oyunun bittiğni kontrol eder.

//Seçilen koordinatın uygunluğunu,oyun bittiğinde harfleri küçülten ve input alan fonk.lar
int isLegal(int x,int y,int size);
void toLower(int board[][MAX_SIZE],int x,int y);
char getInput();
int get_int(int min);

//Bilgisayarın rakibe göre nasıl hareket edeceğini belirleyen fonk.lar
int computerAI(int board[][MAX_SIZE],int size);
int computer3Right(int board[][MAX_SIZE],int size);//3 tane yan yana varsa sağını kapatan
int computer3Left(int board[][MAX_SIZE],int size); // 3 tane yan yana varsa solunu kapatan vs.
int computer3Up(int board[][MAX_SIZE],int size);
int computer2Left(int board[][MAX_SIZE],int size);
int computer2Right(int board[][MAX_SIZE],int size);
int computer2Up(int board[][MAX_SIZE],int size);
int computerUp(int board[][MAX_SIZE],int size);
int computerRight(int board[][MAX_SIZE],int size);
int computerLeft(int board[][MAX_SIZE],int size);

//Bu fonk.lar ise kendi oyunu bitirmeye yönelik hareket yapan fonk.lar
int computer3RightO(int board[][MAX_SIZE],int size);//3 tane yan yana varsa sağına koyan
int computer3LeftO(int board[][MAX_SIZE],int size);//3 tane yan yana varsa soluna koyan
int computer3UpO(int board[][MAX_SIZE],int size);
int computer2LeftO(int board[][MAX_SIZE],int size);
int computer2RightO(int board[][MAX_SIZE],int size);
int computer2UpO(int board[][MAX_SIZE],int size);
int computerUpO(int board[][MAX_SIZE],int size);
int computerRightO(int board[][MAX_SIZE],int size);
int computerLeftO(int board[][MAX_SIZE],int size);
int computerMid(int board[][MAX_SIZE],int size);





int main() {

    int min = 4,board[MAX_SIZE][MAX_SIZE], b_size;
    bool flag = true;
    cout << "Enter size \n" ;
    b_size = get_int(4);
    while (flag)

        if(b_size < 20 && b_size%2 == 0) {
            initBoard(board, b_size);
            gameLoop(board, b_size);
            flag = false;
        }
        else{
            cout << "Çift ve en fazla 20 lik seçebilirsiniz.\n";
            cout << "Enter size \n" ;
            cin >> b_size;

        }

    return 0;
}

void gameLoop(int board[][MAX_SIZE],int size)
{
    char gameType;
    bool flag = true;
    cout << "If you play a friend ,press P. if you play AI , press C\n";
    cin >> gameType; //Oyun Tipi
    while(flag) {
        if (gameType == 'P' || gameType == 'p') {
            PvP(board, size);
            flag = false;
        }
        else if (gameType == 'C' || gameType == 'c') {
            PvC(board, size);
            flag = false;
        }
        else {
            cout << "Wrong button, again\n";
            cout << "If you play a friend ,press P. if you play AI , press C\n";
            cin >> gameType; //Oyun Tipi
        }
    }
}

void PvC(int board[][MAX_SIZE],int size){
    bool player2 = true,done = false,computer = false; //Sıranın kimde olduğunu kontrol eden flagler.

    while (!done) { //Oyunun bitip bitmediğini kontrol eden flag

        if (computer) { //Bilgisayar hamlesi
            computerAI(board, size);
            computer = false;
            player2 = true;
        }
        else if (player2) { //Oyuncu hamlesi
            printBoard(board, size);
            if(player2Move(board,size) == 1){
                computer = true;
                player2 = false;
            }
        }
        gameFinishPvC(board,size,done);//Oyunun bitip bitmediğini kontrol eden fonksiyon
    }
}

void PvP(int board[][MAX_SIZE],int size){
    bool player1 = true, player2 = false,done = false; //Sıranın kimde olduğunu kontrol eden flagler.
    printBoard(board,size);
    while(!done) {  //Oyunun bitip bitmediğini kontrol eden flag
        if(player2) { //Hamle player1 de
            if(player1Move(board,size) == 1){
                player1 = true;
                player2 = false;
            }
        }
        else if(player1){ // Hamle player2 de
            if(player2Move(board,size) == 1){
                player1 = false;
                player2 = true;
            }

        }
        gameFinishPvP(board,size,done); //Oyunun bitip bitmediğini kontrol eden fonksiyon
        printBoard(board, size);
    }
}

int player1Move(int board[][MAX_SIZE],int size){
    bool status = true; //Sadece bir kere hamle yapabilmesi için gerekli oland değişken.
    char input;
    int flag = 0;
    input = getInput(); //kullanıcının kolonu seçen fonksiyon.
    for (int i = 0; i < size; ++i) {
        if (input == 'A' + i || input == 'a' + i) {
            for (int j = 0; j < size; ++j) {
                if (board[size - j - 1][i] == 0) {
                    if(status)
                    {
                        board[size - j - 1][i] = 1;
                        status = false;
                        flag = 1;
                    }

                }
            }
        }
    }

    if(status){
        cout << "Dogru kolon secin.\n";
    }
    return flag;
}

int player2Move(int board[][MAX_SIZE],int size){
    bool status = true; //Sadece bir kere hamle yapabilmesi için gerekli oland değişken.
    char input;
    int flag = 0;
    input = getInput(); //kullanıcının kolonu seçen fonksiyon.
    for (int i = 0; i < size; ++i) {
        if (input == 'A' + i || input == 'a' + i) {
            for (int j = 0; j < size; ++j) {
                if (board[size - j - 1][i] == 0) {
                    if(status)
                    {
                        board[size - j - 1][i] = 2;
                        status = false;
                        flag = 1;
                    }

                }
            }
        }
    }
    if(status){
        cout << "Dogru kolon secin.\n";
    }
    return flag;
}

void gameFinishPvC(int board[][MAX_SIZE],int size,bool &flag){

        if (isFinishedO(board, size) == 1 || crossFinishedO(board, size) == 1) {
            flag = true;
            cout << "Computer won\n";
            printBoard(board, size);
        }
        else if (isFinishedX(board, size) == 2 || crossFinishedX(board, size) == 2) {
            flag = true;
            cout << "Player won\n";
            printBoard(board, size);
        }
        else if (isFilled(board, size)) {
            flag = true;
            cout << "Filled Board\n";
            printBoard(board, size);
        }

}

void gameFinishPvP(int board[][MAX_SIZE],int size,bool &flag){

        if(isFinishedO(board,size) == 1 || crossFinishedO(board,size) == 1){
            flag = true;
            cout << "Player 2 won\n";
        }
        else if(isFinishedX(board,size) == 2 || crossFinishedX(board,size) == 2){
            flag = true;
            cout << "Player 1 won\n";
        }
        else if(isFilled(board,size)){
            flag = true;
            cout << "Filled Board\n";
        }

}

int computer3Right(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j+1, size) && isLegal(i , j+2, size) && isLegal(i, j+3, size)) {
                if (board[i][j] == 2 && board[i][j + 1] == 2 && board[i][j + 2] == 2 && board[i][j + 3] == 0) {
                    if(!(isLegal(i+1,j+3,size)) || board[i+1][j + 3] != 0) {
                        if(status == 0) {
                            board[i][j + 3] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer3RightO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j+1, size) && isLegal(i , j+2, size) && isLegal(i, j+3, size)) {
                if (board[i][j] == 1 && board[i][j + 1] == 1 && board[i][j + 2] == 1 && board[i][j + 3] == 0) {
                    if(!(isLegal(i+1,j+3,size)) || board[i+1][j + 3] != 0) {
                        if(status == 0) {
                            board[i][j + 3] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer3Left(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j-1, size) && isLegal(i , j-2, size) && isLegal(i, j-3, size)) {
                if (board[i][j] == 2 && board[i][j - 1] == 2 && board[i][j - 2] == 2 && board[i][j - 3] == 0) {
                    if(!(isLegal(i+1,j-3,size)) || board[i+1][j - 3] != 0) {
                        if(status == 0) {
                            board[i][j - 3] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer3LeftO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j-1, size) && isLegal(i , j-2, size) && isLegal(i, j-3, size)) {
                if (board[i][j] == 1 && board[i][j - 1] == 1 && board[i][j - 2] == 1 && board[i][j - 3] == 0) {
                    if(!(isLegal(i+1,j-3,size)) || board[i+1][j - 3] != 0) {
                        if(status == 0) {
                            board[i][j - 3] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer2Left(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j-1, size) && isLegal(i , j-2, size)) {
                if (board[i][j] == 2 && board[i][j - 1] == 2  && board[i][j - 2] == 0) {
                    if(!(isLegal(i+1,j-2,size)) || board[i+1][j - 2] != 0) {
                        if(status == 0) {
                            board[i][j - 2] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer2LeftO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j-1, size) && isLegal(i , j-2, size)) {
                if (board[i][j] == 1 && board[i][j - 1] == 1  && board[i][j - 2] == 0) {
                    if(!(isLegal(i+1,j-2,size)) || board[i+1][j - 2] != 0) {
                        if(status == 0) {
                            board[i][j - 2] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer2Right(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j+1, size) && isLegal(i , j+2, size)) {
                if (board[i][j] == 2 && board[i][j + 1] == 2  && board[i][j + 2] == 0) {
                    if(!(isLegal(i+1,j+2,size)) || board[i+1][j + 2] != 0) {
                        if(status == 0) {
                            board[i][j + 2] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer2RightO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j+1, size) && isLegal(i , j+2, size)) {
                if (board[i][j] == 1 && board[i][j + 1] == 1  && board[i][j + 2] == 0) {
                    if(!(isLegal(i+1,j+2,size)) || board[i+1][j + 2] != 0) {
                        if(status == 0) {
                            board[i][j + 2] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer3Up(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i - 1, j, size) && isLegal(i-2 , j, size) && isLegal(i-3, j, size)) {
                if (board[i][j] == 2 && board[i-1][j] == 2 && board[i-2][j] == 2 && board[i-3][j] == 0) {
                    if(board[i-3][j] == 0) {
                        if(status == 0) {
                            board[i - 3][j] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer3UpO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i - 1, j, size) && isLegal(i-2 , j, size) && isLegal(i-3, j, size)) {
                if (board[i][j] == 1 && board[i-1][j] == 1 && board[i-2][j] == 1 && board[i-3][j] == 0) {
                    if(board[i-3][j] == 0) {
                        if(status == 0) {
                            board[i - 3][j] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer2Up(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i - 1, j, size) && isLegal(i-2 , j, size)) {
                if (board[i][j] == 2 && board[i-1][j] == 2  && board[i-2][j] == 0) {
                    if(board[i-2][j] == 0) {
                        if(status == 0) {
                            board[i - 2][j] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computer2UpO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i - 1, j, size) && isLegal(i-2 , j, size)) {
                if (board[i][j] == 1 && board[i-1][j] == 1  && board[i-2][j] == 0) {
                    if(board[i-2][j] == 0) {
                        if(status == 0) {
                            board[i - 2][j] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computerUp(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i - 1, j, size)) {
                if (board[i][j] == 2   && board[i-1][j] == 0) {
                    if(board[i-1][j] == 0) {
                        if(status == 0) {
                            board[i - 1][j] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computerUpO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i - 1, j, size)) {
                if (board[i][j] == 1   && board[i-1][j] == 0) {
                    if(board[i-1][j] == 0) {
                        if(status == 0) {
                            board[i - 1][j] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computerRight(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j+1, size)) {
                if (board[i][j] == 2   && board[i][j + 1] == 0) {
                    if(!(isLegal(i+1,j+1,size)) || board[i+1][j + 1] != 0) {
                        if(status == 0) {
                            board[i][j + 1] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computerRightO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j+1, size)) {
                if (board[i][j] == 1   && board[i][j + 1] == 0) {
                    if(!(isLegal(i+1,j+1,size)) || board[i+1][j + 1] != 0) {
                        if(status == 0) {
                            board[i][j + 1] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computerLeft(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j-1, size) && isLegal(i , j-2, size)) {
                if (board[i][j] == 2  && board[i][j - 1] == 0) {
                    if(!(isLegal(i+1,j-1,size)) || board[i+1][j - 1] != 0) {
                        if(status == 0) {
                            board[i][j - 1] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}
int computerLeftO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j-1, size) && isLegal(i , j-2, size)) {
                if (board[i][j] == 1  && board[i][j - 1] == 0) {
                    if(!(isLegal(i+1,j-1,size)) || board[i+1][j - 1] != 0) {
                        if(status == 0) {
                            board[i][j - 1] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}

int computerMid(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i, j+1, size) && isLegal(i , j-1, size)) {
                if (board[i][j-1] == 2  && board[i][j + 1] == 2 && board[i][j] == 0) {
                    if(!(isLegal(i+1,j,size)) || board[i+1][j] != 0) {
                        if(status == 0) {
                            board[i][j] = 1;
                            status = 1;
                        }
                    }
                }
            }
        }
    }
    return status;
}


int computerAI(int board[][MAX_SIZE],int size){

    if(computer3RightO(board,size)){
        return 0;
    }
    else if(computer3LeftO(board,size)){
        return 0;
    }
    else if(computer3UpO(board,size)){
        return 0;
    }
    else if(computer3Up(board,size)){
        return 0;
    }
    else if(computer3Left(board,size)){
        return 0;
    }
    else if(computer3Right(board,size)){
        return 0;
    }
    else if(computerMid(board,size)){
        return 0;
    }
    else if(computer2Right(board,size)){
        return 0;
    }
    else if(computer2Up(board,size)){
        return 0;
    }
    else if(computer2Left(board,size)){
        return 0;
    }
    else if(computer2UpO(board,size)){
        return 0;
    }
    else if(computer2LeftO(board,size)){
        return 0;
    }
    else if(computer2RightO(board,size)){
        return 0;
    }
    else if(computerUp(board,size)){
        return 0;
    }
    else if(computerRight(board,size)){
        return 0;
    }
    else if(computerLeft(board,size)){
        return 0;
    }
    else if(computerUpO(board,size)){
        return 0;
    }
    else if(computerRightO(board,size)){
        return 0;
    }
    else if(computerLeftO(board,size)){
        return 0;
    }

    return 0;
}


char getInput(){
    char column;
    cout << "Choose column: \n";
    cin >> column;
    return column;
}
int crossFinishedX(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int k = 0; k < size; ++k) {
        for (int l = 0; l < size; ++l) {
            if(isLegal(k+1,l+1,size) && isLegal(k+2,l+2,size) && isLegal(k+3,l+3,size)){
                if(board[k][l] == 2 && board[k+1][l+1] == 2 && board[k+2][l+2] == 2 && board[k+3][l+3] == 2) {
                    toLower(board,k,l);
                    toLower(board,k+1,l+1);
                    toLower(board,k+2,l+2);
                    toLower(board,k+3,l+3);
                    status = 2;
                }
            }
            if(isLegal(k-1,l+1,size) && isLegal(k-2,l+2,size) && isLegal(k-3,l+3,size)){
                if(board[k][l] == 2 && board[k-1][l+1] == 2 && board[k-2][l+2] == 2 && board[k-3][l+3] == 2) {
                    toLower(board,k,l);
                    toLower(board,k-1,l+1);
                    toLower(board,k-2,l+2);
                    toLower(board,k-3,l+3);
                    status = 2;
                }
            }
            if(isLegal(k+1,l-1,size) && isLegal(k+2,l-2,size) && isLegal(k+3,l-3,size)){
                if(board[k][l] == 2 && board[k+1][l-1] == 2 && board[k+2][l-2] == 2 && board[k+3][l-3] == 2) {
                    toLower(board,k,l);
                    toLower(board,k+1,l-1);
                    toLower(board,k+2,l-2);
                    toLower(board,k+3,l-3);
                    status = 2;
                }
            }
            if(isLegal(k-1,l-1,size) && isLegal(k-2,l-2,size) && isLegal(k-3,l-3,size)) {
                if (board[k][l] == 2 && board[k - 1][l - 1] == 2 && board[k - 2][l - 2] == 2 &&
                    board[k - 3][l - 3] == 2) {
                    toLower(board,k,l);
                    toLower(board,k-1,l-1);
                    toLower(board,k-2,l-2);
                    toLower(board,k-3,l-3);
                    status = 2;
                }
            }
        }
    }
    return status;
}

int crossFinishedO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(isLegal(i+1,j+1,size) && isLegal(i+2,j+2,size) && isLegal(i+3,j+3,size)){
                if(board[i][j] == 1 && board[i+1][j+1] == 1 && board[i+2][j+2] == 1 && board[i+3][j+3] == 1) {
                    toLower(board,i,j);
                    toLower(board,i+1,j+1);
                    toLower(board,i+2,j+2);
                    toLower(board,i+3,j+3);
                    status = 1;
                }
            }
            if(isLegal(i-1,j+1,size) && isLegal(i-2,j+2,size) && isLegal(i-3,j+3,size)){
                 if(board[i][j] == 1 && board[i-1][j+1] == 1 && board[i-2][j+2] == 1 && board[i-3][j+3] == 1) {
                     toLower(board,i,j);
                     toLower(board,i-1,j+1);
                     toLower(board,i-2,j+2);
                     toLower(board,i-3,j+3);
                     status = 1;
                 }
            }
            if(isLegal(i+1,j-1,size) && isLegal(i+2,j-2,size) && isLegal(i+3,j-3,size)){
                 if(board[i][j] == 1 && board[i+1][j-1] == 1 && board[i+2][j-2] == 1 && board[i+3][j-3] == 1) {
                     toLower(board,i,j);
                     toLower(board,i+1,j-1);
                     toLower(board,i+2,j-2);
                     toLower(board,i+3,j-3);
                     status = 1;
                 }
            }
            if(isLegal(i-1,j-1,size) && isLegal(i-2,j-2,size) && isLegal(i-3,j-3,size)) {
                if (board[i][j] == 1 && board[i - 1][j - 1] == 1 && board[i - 2][j - 2] == 1 &&
                    board[i - 3][j - 3] == 1) {
                    toLower(board,i,j);
                    toLower(board,i-1,j-1);
                    toLower(board,i-2,j-2);
                    toLower(board,i-3,j-3);
                    status = 1;
                }
            }
        }
    }


    return status;
}

void toLower(int board[][MAX_SIZE],int x,int y){
    if(board[x][y] == 1)
        board[x][y] = 4;
    else if(board[x][y] == 2)
        board[x][y] = 3;

}

int isFilled(int board[][MAX_SIZE],int size){
    int status = 1;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(board[i][j] == 0)
                status = 0;
        }
    }
    return status;
}

int isFinishedO(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (isLegal(i + 1, j, size) && isLegal(i + 2, j, size) && isLegal(i + 3, j, size)) {
                if (board[i][j] == 1 && board[i + 1][j] == 1 && board[i + 2][j] == 1 && board[i + 3][j] == 1) {
                    toLower(board, i, j);
                    toLower(board, i + 1, j);
                    toLower(board, i + 2, j);
                    toLower(board, i + 3, j);
                    status = 1;
                }
            }
            if (isLegal(i, j + 1, size) && isLegal(i, j + 2, size) && isLegal(i, j + 3, size)) {
                if (board[i][j] == 1 && board[i][j + 1] == 1 && board[i][j + 2] == 1 && board[i][j + 3] == 1) {
                    toLower(board, i, j);
                    toLower(board, i, j + 1);
                    toLower(board, i, j + 2);
                    toLower(board, i, j + 3);
                    status = 1;
                }
            }

        }
    }


    return  status;
}
int isFinishedX(int board[][MAX_SIZE],int size){
    int status = 0;
    for (int k = 0; k < size; ++k) {
        for (int l = 0; l < size; ++l) {
            if(isLegal(k+1,l,size) && isLegal(k+2,l,size) && isLegal(k+3,l,size)) {
                if (board[k][l] == 2 && board[k + 1][l] == 2 && board[k + 2][l] == 2 && board[k + 3][l] == 2) {
                    toLower(board,k,l);
                    toLower(board,k+1,l);
                    toLower(board,k+2,l);
                    toLower(board,k+3,l);
                    status = 2;
                }
            }
            if(isLegal(k,l+1,size) && isLegal(k,l+2,size) && isLegal(k,l+3,size)) {
                if (board[k][l] == 2 && board[k][l + 1] == 2 && board[k][l + 2] == 2 && board[k][l + 3] == 2) {
                    toLower(board,k,l);
                    toLower(board,k,l+1);
                    toLower(board,k,l+2);
                    toLower(board,k,l+3);
                    status = 2;
                }
            }
        }
    }
    return status;
}

int isLegal(int x,int y,int size){
    int status = 0;
    if(x >= 0 && y >= 0 && x < size && y < size)
        status = 1;

    return status;
}



void initBoard(int board[][MAX_SIZE],int size)
{
    for (int i = 0; i < MAX_SIZE; ++i) {
        for (int j = 0; j < MAX_SIZE; ++j) {
            board[i][j] = 5;
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            board[i][j] = 0;
        }
    }
}

void printBoard(int board[][MAX_SIZE],int size){
    char letter;
    for (int i = 0; i < size; ++i) {
        letter = 'A' + i;
        cout <<  letter << " ";
    }
    cout << "\n";

    for (int k = 0; k < size; ++k) {
        for (int l = 0; l < size; ++l) {
            if(board[k][l] == 0)
                cout << ". ";
            if(board[k][l] == 1)
                cout << "O ";
            if(board[k][l] == 2)
                cout << "X ";
            if(board[k][l] == 3)
                cout << "x ";
            if(board[k][l] == 4)
                cout << "o ";
        }
        cout << "\n";
    }
}

int get_int(int min)
{
	int ret_integer;
    string str_number;

	while(true) {
        getline(cin, str_number);
		stringstream convert(str_number);
		if(convert >> ret_integer && !(convert >> str_number) && ret_integer >= min) return ret_integer;

		cin.clear();
		cerr << "Input must be >= " << min << ". Please try again.\n";
	}
}

