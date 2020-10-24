#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <process.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length;
int bend_no;
int len;
char key;
int life;

void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Print();
void load();
void Delay(long double);
void Food();
void Move();
void Up();
void Right();
void Left();
void Down();
void Bend();
void Boarder();
int Score();
int Scoreonly();
void ExitGame();

struct coordinate{
  int x;
  int y;
  int direction;
};

typedef struct coordinate coordinate;

coordinate head, bend[500],food,body[30];

int main(){

  char key;

  Print();

  system("cls");

  load();

  length=5;

  head.x=25;

  head.y=20;

  head.direction=RIGHT;

  Boarder();

  Food(); //to generate food coordinates initially

  life=3; //number of extra lives

  bend[0]=head;

  Move();   //initialing initial bend coordinate

  return 0;

}//fecha main


void gotoxy(int x, int y){

  COORD coord;

  coord.X = x;

  coord.Y = y;

  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}//fecha gotoxy

void GotoXY(int x, int y){

  HANDLE a;
  COORD b;
  fflush(stdout);
  b.X = x;
  b.Y = y;
  a = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleCursorPosition(a,b);

}//fecha GotoXY


void Print(){
  
  //GotoXY(10,12);
  printf("\tSNAKE GAME\n");
  //getch();
  system("cls");
  printf("\nInstrucoes:\n");
  printf("\n-> Use setas para mover\n\n-> Frutas irao aparecer na tela. Coma para crescer.\n\n-> Voce terá 3 vidas. A cada vez que encostar nas paredes, perde uma.\n\n-> Pause o jogo pressionando qualquer tecla. Volte o jogo pressionando qualquer tecla.\n\n-> Para sair do jogo, pressione ESC. \n");
  printf("\n\nPressione qualquer tecla para jogar...");
  if(getch()==27) exit(0);

}//fecha print

void load(){

  int row,col,r,c,q;
  gotoxy(36,14);
  printf("loading...");
  gotoxy(30,15);
  for(r=1;r<=20;r++){
  for(q=0;q<=1000000;q++);//to display the character slowly
  printf("%c",177);
  }//fecha for

}//fecha load

void Delay(long double k){

  Score();
  long double i;
  for(i=0;i<=(10000000);i++);

}//fecha Delay

void Food(){

  if(head.x==food.x&&head.y==food.y){
    length++;
    time_t a;
    a=time(0);
    srand(a);
    food.x=rand()%70;
    if(food.x<=10)food.x+=11;
    food.y=rand()%30;
    if(food.y<=10)food.y+=11;
    /*to create food for the first time coz global variable are initialized with 0*/
  }else if(food.x==0){
    food.x=rand()%70;
    if(food.x<=10)food.x+=11;
    food.y=rand()%30;
    if(food.y<=10)food.y+=11;
  }

fflush(stdin);
}//fecha Food


/*DESENHO DO CORPO E DIRECOES*/
void Move(){

  int a,i;

  do{

  Food();
  fflush(stdin);

  len=0;

  for(i=0;i<30;i++){

    body[i].x=0;

    body[i].y=0;

    if(i==length)

    break;

  }//fecha for

  Delay(length);

  Boarder();

  if(head.direction==RIGHT)Right();

  else if(head.direction==LEFT)Left();

  else if(head.direction==DOWN)Down();

  else if(head.direction==UP)Up();

  ExitGame();

  }while(!kbhit());

  a=getch();

  if(a==27){

    system("cls");

    exit(0);

  }//fecha if

  key=getch();

  if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN)){

    bend_no++;

    bend[bend_no]=head;

    head.direction=key;

    if(key==UP)head.y--;

    if(key==DOWN)head.y++;

    if(key==RIGHT)head.x++;

    if(key==LEFT)head.x--;

    Move();

  }else if(key==27){

    system("cls");

    exit(0);

  }else{

    printf("\a");

    Move();

  }//fecha if
  fflush(stdin);
}//fecha move

void Up(){
  int i;
  for(i=0;i<=(bend[bend_no].y-head.y)&&len<length;i++){
    GotoXY(head.x,head.y+i);
    {
      if(len==0)
      printf("O");
      else
      printf("o");
    }
    body[len].x=head.x;
    body[len].y=head.y+i;
    len++;
  }//fecha for
  Bend();
  if(!kbhit()) head.y--;
}//fecha up

void Right(){

  int i;
  for(i=0;i<=(head.x-bend[bend_no].x)&&len<length;i++){
    //GotoXY((head.x-i),head.y);
    body[len].x=head.x-i;
    body[len].y=head.y;
    GotoXY(body[len].x,body[len].y);
    {
    if(len==0) printf("O");
    else printf("o");
    }
    /*body[len].x=head.x-i;
    body[len].y=head.y;*/
    len++;
  }//fecha for
  Bend();
  if(!kbhit()) head.x++;

}//fecha Right

void Left(){

  int i;
  for(i=0;i<=(bend[bend_no].x-head.x)&&len<length;i++){
    GotoXY((head.x+i),head.y);
    {
    if(len==0) printf("O");
    else printf("o");
    }
    body[len].x=head.x+i;
    body[len].y=head.y;
    len++;
  }//fecha for
  Bend();
  if(!kbhit())head.x--;

}//fecha Left

void Down(){

  int i;
  for(i=0;i<=(head.y-bend[bend_no].y)&&len<length;i++){
    GotoXY(head.x,head.y-i);
    {
      if(len==0) printf("O");
      else printf("o");
    }
    body[len].x=head.x;
    body[len].y=head.y-i;
    len++;
  }
  Bend();
  if(!kbhit())head.y++;

}//fecha Down
/* ******************************* */


void Bend(){

  int i,j,diff;
  for(i=bend_no;i>=0&&len<length;i--){
    if(bend[i].x==bend[i-1].x){
      diff=bend[i].y-bend[i-1].y;
      if(diff<0)
      for(j=1;j<=(-diff);j++){
        body[len].x=bend[i].x;
        body[len].y=bend[i].y+j;
        GotoXY(body[len].x,body[len].y);
        printf("o");
        len++;
        if(len==length)
        break;
      }else if(diff>0)
      for(j=1;j<=diff;j++){
        /*GotoXY(bend[i].x,(bend[i].y-j));
        printf("*");*/
        body[len].x=bend[i].x;
        body[len].y=bend[i].y-j;
        GotoXY(body[len].x,body[len].y);
        printf("o");
        len++;
        if(len==length)
        break;
      }//fecha for
    }else if(bend[i].y==bend[i-1].y){
      diff=bend[i].x-bend[i-1].x;
      if(diff<0)
      for(j=1;j<=(-diff)&&len<length;j++){
        /*GotoXY((bend[i].x+j),bend[i].y);
        printf("*");*/
        body[len].x=bend[i].x+j;
        body[len].y=bend[i].y;
        GotoXY(body[len].x,body[len].y);
        printf("o");
        len++;
        if(len==length)
        break;
      }//fecha for
      else if(diff>0)
      for(j=1;j<=diff&&len<length;j++){
        /*GotoXY((bend[i].x-j),bend[i].y);
        printf("*");*/
        body[len].x=bend[i].x-j;
        body[len].y=bend[i].y;
        GotoXY(body[len].x,body[len].y);
        printf("o");
        len++;
        if(len==length)
        break;
      }//fecha for
    }//fecha if else
  }//fecha for

fflush(stdin);
}//fecha bend

//MAPA - AREA DO JOGO
void Boarder(){

  system("cls");
  int i;
  /*mostra a comida*/
  GotoXY(food.x,food.y);
  printf("%c",42);

  for(i=10;i<71;i++){
    GotoXY(i,10);
    printf("%c",176);
    GotoXY(i,30);
    printf("%c",176);
  }//fecha for
  for(i=10;i<31;i++){
    GotoXY(10,i);
    printf("%c",176);
    GotoXY(70,i);
    printf("%c",176);
  }//fecha for

}//fecha Boarder

int Score(){
  int score;
  GotoXY(20,8);
  score=length-5;
  printf("SCORE : %d",(length-5));
  score=length-5;
  GotoXY(50,8);
  printf("Vidas : %d",life);
  return score;
}//fecha score

int Scoreonly(){
  int score=Score();
  system("cls");
  return score;
}//fecha scoreonly

void ExitGame(){

  int i,check=0;
  //starts with 4 because it needs minimum 4 element to touch its own body
  for(i=4;i<length;i++){
    if(body[0].x==body[i].x&&body[0].y==body[i].y){
    //check's value increases as the coordinates of head is equal to any other body coordinate
    check++;
    }//fecha if
    if(i==length||check!=0)break;
  }//fecha for
  if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0){
    life--;
    if(life>=0){
      head.x=25;
      head.y=20;
      bend_no=0;
      head.direction=RIGHT;
      Move();
    }else{
      system("cls");
      printf("Perdeu todas as vidas\nPressione qualquer tecla para sair.\n");
      exit(0);
    }//fecha if else
  }//fecha if

}//fecha ExitGame

