/*
	Name: Snake console game
	Author: nhan tran
	Date: 14/12/16 23:17
	Description: remember to include "NewGraphics.h" header file
*/

#include <iostream>
#include "NewGraphics.h"
#include <ctime>

using namespace std;

/* Macro definition */
#define NOWHERE   0
#define UP        1
#define DOWN      2
#define RIGHT     3
#define LEFT      4
#define WINDOWS_WIDTH  20
#define WINDOWS_HEIGHT 20
#define MAX_LENGTH     100
#define SPEED_LOW      200
#define SPEED_MEDIUM   100
#define SPEED_HIGH     50
#define SPEED_VERYHIGH 30

/* Structure definition */
typedef struct{
        int x[MAX_LENGTH];
        int y[MAX_LENGTH];
        int length;
}Snake;

typedef struct{
    int x;
    int y;
}Food;

/* Global variables */
int _lastDirection;
int _currDirection;
Snake _snake;
Food _food;
bool _gameOver;
int _score;

/* Function prototype */
void init();
void keyHit();
void drawSnake();
void drawFood();
void checkCollision();
void resetGame();
bool eatFood();

/* Main program */
int main(){

    init();
    while(!_gameOver){
        keyHit();
        drawSnake();
        checkCollision();
        Sleep(SPEED_MEDIUM);
    }
}

/* Function definition */

/* Ham: init()
 * Chuc nang: khoi tao game
 * Tham so: khong
 * Tra ve: khong
 */
void init(){
    ShowCur(false);
    _gameOver = false;
    _score = 0;
    _lastDirection = NOWHERE;
    _currDirection = NOWHERE;
    _snake.x[0] = WINDOWS_WIDTH/2 - 2;     _snake.y[0] = WINDOWS_HEIGHT/2;
    _snake.x[1] = WINDOWS_WIDTH/2 - 1;     _snake.y[1] = WINDOWS_HEIGHT/2;
    _snake.x[2] = WINDOWS_WIDTH/2;         _snake.y[2] = WINDOWS_HEIGHT/2;
    _snake.length = 3;

    // Hien thi khung
    for(int i=0; i<WINDOWS_WIDTH; i++){
        gotoxy(i, 0);
        cout << "?";
    }
    for(int i=0; i<WINDOWS_WIDTH; i++){
        gotoxy(i, WINDOWS_HEIGHT-1);
        cout << "?";
    }
    for(int i=0; i<WINDOWS_HEIGHT; i++){
        gotoxy(0, i);
        cout << "?";
    }
    for(int i=0; i<WINDOWS_HEIGHT; i++){
        gotoxy(WINDOWS_WIDTH-1, i);
        cout << "?";
    }

    // Hien thi thong tin game
    gotoxy(WINDOWS_WIDTH/2-7, WINDOWS_HEIGHT+2);
    cout << "powered by SRC";

    // Hien thi text diem so
    gotoxy(WINDOWS_WIDTH+3, WINDOWS_HEIGHT/2);
    cout << "Score: ";

    // Hien thi con ran ban dau
    for(int i=0; i<_snake.length; i++){
        gotoxy(_snake.x[i], _snake.y[i]);
        cout << "*";
    }

    // Hien thi thuc an ban dau
    drawFood();
}

/* Ham: keyHit()
 * Chuc nang: kiem tra nhan nut
 * Tham so: khong
 * Tra ve: khong
 */
void keyHit(){
    if(GetAsyncKeyState(VK_UP)){
        if(_lastDirection!=DOWN) _currDirection = UP; // Kiem tra de tranh tinh trang chay nguoc lai
    }
    else if(GetAsyncKeyState(VK_DOWN)){
        if(_lastDirection!=UP) _currDirection = DOWN;
    }
    else if(GetAsyncKeyState(VK_RIGHT)){
        if(_lastDirection!=LEFT) _currDirection = RIGHT;
    }
    else if(GetAsyncKeyState(VK_LEFT)){
        if(_lastDirection!=RIGHT) _currDirection = LEFT;
    }
}

/* Ham: drawSnake()
 * Chuc nang: ve con ran ra man hinh
 * Tham so: khong
 * Tra ve: khong
 */
void drawSnake(){

    if(_currDirection != NOWHERE){ // Neu chua nhan phim thi ko di chuyen
        // Xoa duoi ran
        gotoxy(_snake.x[_snake.length-1], _snake.y[_snake.length-1]);
        if(eatFood()){
            _snake.length++; // Tang do dai len 1
            drawFood();
        }
        else{
            cout << " ";
        }

        // Dich ran tu duoi len dau
        for(int i=_snake.length-1; i>0; i--){
            _snake.x[i] = _snake.x[i-1];
            _snake.y[i] = _snake.y[i-1];
        }

        // Dich dau ran
        if(_currDirection==RIGHT){
            _snake.x[0]++;
        }
        else if(_currDirection==LEFT){
            _snake.x[0]--;
        }
        else if(_currDirection==UP){
            _snake.y[0]--;
        }
        else if(_currDirection==DOWN){
            _snake.y[0]++;
        }

        // Neu dau ran va cham voi tuong
        if(_snake.x[0]==0){
            _snake.x[0] = WINDOWS_WIDTH-2;
        }
        else if(_snake.x[0]==WINDOWS_WIDTH-1){
            _snake.x[0] = 1;
        }
        else if(_snake.y[0]==0){
            _snake.y[0] = WINDOWS_HEIGHT-2;
        }
        else if(_snake.y[0]==WINDOWS_HEIGHT-1){
            _snake.y[0] = 1;
        }
        // Thay doi _lastDirection
        _lastDirection = _currDirection;

        // In dau ran moi
        gotoxy(_snake.x[0], _snake.y[0]);
        cout << "*";
    }

    // Hien thi diem so hien tai
    gotoxy(WINDOWS_WIDTH+10, WINDOWS_HEIGHT/2);
    cout << _score;
}

/* Ham: drawFood()
 * Chuc nang: ve thuc an ra man hinh
 * Tham so: khong
 * Tra ve: khong
 * Vi du: int a = rand() % 50 + 1; // random trong khoang [1, 50]
 */
void drawFood(){
    srand(time(NULL));
    _food.x = rand() % (WINDOWS_WIDTH-2)  + 1;
    _food.y = rand() % (WINDOWS_HEIGHT-2) + 1;

    gotoxy(_food.x, _food.y);
    cout << (char)3; // Trai tim
}

/* Ham: checkCollision()
 * Chuc nang: kiem tra su va cham cua dau ran voi than ran
 * Tham so: khong
 * Tra ve: khong
 */
void checkCollision(){
    for(int i=1; i<_snake.length; i++){
        if(_snake.x[i] == _snake.x[0]
        && _snake.y[i] == _snake.y[0]){
            _gameOver = true;
            resetGame();
        }
    }
}

/* Ham: resetGame()
 * Chuc nang: cho nguoi dung nhan phim SPACE de choi lai tu dau
 * Tham so: khong
 * Tra ve: khong
 */
void resetGame(){
    clearScreen(); // Xoa man hinh
    gotoxy(0, 1);
    cout << "GAME OVER";
    gotoxy(0, 3);
    cout << "Final score: " << _score;
    gotoxy(0, 5);
    cout << "Press ENTER to play again, ESC to escape!";
    while(1){
        if(GetAsyncKeyState(VK_RETURN)){
            clearScreen();            
            init();
            break;
        }
        if(GetAsyncKeyState(VK_ESCAPE)){
            break;
        }
    }
}

/* Ham: eatFood()
 * Chuc nang: kiem tra ran da an thuc an hay chua
 * Tham so: khong
 * Tra ve: TRUE or FALSE
 */
bool eatFood(){
    if(_snake.x[0]==_food.x && _snake.y[0]==_food.y){
        _score++;
        return true;
    }
    return false;
}
