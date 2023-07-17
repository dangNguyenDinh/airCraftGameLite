#include<iostream>
#include<windows.h>
#include<conio.h>
#include<unistd.h>
#include<time.h>
using namespace std;

void gotoxy(int x,int y){  
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y};
    SetConsoleCursorPosition(console, a);
}
 //global initialization
enum gameCondition{maintained,end};
gameCondition gameCondition1 = maintained;
char background[30][105];	

struct craft{
/*
	 /|\
	|=|=|
*/
	int toaDoXCraft;
	void movingCraft(int &toaDoXCraft){
		if(kbhit()){
			char movingKeyPress = getch();
			if(movingKeyPress == 75){
				toaDoXCraft-=2;
			}
			if(movingKeyPress == 77){
				toaDoXCraft+=2;
			}
			if(toaDoXCraft < 2){
				toaDoXCraft = 2;
			}
			if(toaDoXCraft > 102){
				toaDoXCraft = 102;
			}
		}	
	}
	void drawInvisibleCraft(int toaDoXCraft){
//		gotoxy(toaDoXCraft-1,26);
//		cout<<"/|\\";
//		gotoxy(toaDoXCraft-2,27);
//		cout<<"|=|=|";
		gotoxy(0,0);
		background[26][toaDoXCraft-1] = ' ';
		background[26][toaDoXCraft] = ' ';
		background[26][toaDoXCraft+1] = ' ';
		background[27][toaDoXCraft-2] = ' ';
		background[27][toaDoXCraft-1] = ' ';
		background[27][toaDoXCraft] = ' ';
		background[27][toaDoXCraft+1] = ' ';	
		background[27][toaDoXCraft+2] = ' ';
	}
	void drawCraft(int toaDoXCraft){
//		gotoxy(toaDoXCraft-1,26);
//		cout<<"    ";
//		gotoxy(toaDoXCraft-2,27);
//		cout<<"     ";
		gotoxy(0,0);
		background[26][toaDoXCraft-1] = '/';
		background[26][toaDoXCraft] = '|';
		background[26][toaDoXCraft+1] = '\\';
		background[27][toaDoXCraft-2] = '|';
		background[27][toaDoXCraft-1] = '=';
		background[27][toaDoXCraft] = '|';
		background[27][toaDoXCraft+1] = '=';	
		background[27][toaDoXCraft+2] = '|';
	}
	void shot(int toaDoXCraft){	
		for(int i=1;i<104;i++){
			if(background[26][i]=='|'){
				background[25][i] = 'o';
			}	
		}
		for(int i=1;i<26;i++){
			for(int j=1;j<104;j++){
				if(background[i][j] == 'o'){
					background[i][j] = ' ';
					background[i-1][j] = 'o';
				}
			}
		}
		for(int i=0;i<30;i++){
			for(int j=0;j<105;j++){
				background[0][j] = '|';	//rebuild the destroyed wall
			}
		}
	}
	void beShot(){
		for(int i=1;i<29;i++){
			for(int j=1;j<104;j++){
				if(background[26][j] == '|'&&(background[26][j] == '*' ||background[26][j-1] == '*' || background[26][1+j] == '*'||background[27][j-2] == '*' || background[27][j+2] == '*')){
					gameCondition1 = end;
					drawInvisibleCraft(j);
					background[26][j] = '|';
					background[25][j] = '|';
					background[27][j] = '|';
					background[26][j-1] = '-';
					background[26][j+1] = '-';
					background[26][j-2] = '-';
					background[26][j+2] = '-';
					background[26][j-3] = '-';
					background[26][j+3] = '-';		
					background[27][j-1] = '/';
					background[27][j+1] = '\\';
					background[25][j-1] = '\\';
					background[25][j+1] = '/';
					background[28][j-2] = '/';
					background[28][j+2] = '\\';
					background[24][j-2] = '\\';
					background[24][j+2] = '/';
					Beep(800,100);
					Beep(800,100);
					
				}
			}
		}
		
	}
	
};

struct enemy{
	int xEnemy;
	int yEnemy = 2;
	void drawEnemy(int xEnemy,int yEnemy){
		gotoxy(0,0);
		background[yEnemy][xEnemy] = 'U';
		background[yEnemy][xEnemy-1] = 'H';
		background[yEnemy][xEnemy+1] = 'H';
		background[yEnemy+1][xEnemy] = 'A';
		background[yEnemy+1][xEnemy-1] = '\\';
		background[yEnemy+1][xEnemy+1] = '/';
	}
	void drawInvisibleEnemy(int xEnemy,int yEnemy){
		gotoxy(0,0);
		background[yEnemy][xEnemy] = ' ';
		background[yEnemy][xEnemy-1] = ' ';
		background[yEnemy][xEnemy+1] = ' ';
		background[yEnemy+1][xEnemy] = ' ';
		background[yEnemy+1][xEnemy-1] = ' ';
		background[yEnemy+1][xEnemy+1] = ' ';
	}
	void creatingEnemy(int &xEnemy,int &yEnemy){
		xEnemy = 2*(rand()%(51-1)+1);
		drawEnemy(xEnemy,yEnemy);
	}
	void movingDownEnemy(int &xEnemy,int &yEnemy){
		drawInvisibleEnemy(xEnemy,yEnemy);
		yEnemy++;
		drawEnemy(xEnemy,yEnemy);
	}
	void movingRightEnemy(int &xEnemy,int &yEnemy){
		drawInvisibleEnemy(xEnemy,yEnemy);
		xEnemy++;
		if(xEnemy>103){
			xEnemy = 103;
		}
		drawEnemy(xEnemy,yEnemy);
	}
	void movingLeftEnemy(int &xEnemy,int &yEnemy){
		drawInvisibleEnemy(xEnemy,yEnemy);
		xEnemy--;
		if(xEnemy < 3){
			xEnemy = 3;
		}
		drawEnemy(xEnemy,yEnemy);
	}
	void enemyShot(){
		for(int i=1;i<29;i++){
			for(int j=1;j<105;j++){
				if(background[i][j] == 'A'&&background[i][j-1] == '\\'&&background[i][j+1] == '/'){
					background[i+1][j] = '*';
				}
			}
		}
	
	}
	void continueShooting(){
			for(int i=40;i>=1;i--){
			for(int j=0;j<105;j++){
				if(background[i][j] == '*'){
					background[i][j] = ' ';
					background[i+1][j] = '*';
				}
			}
		}
	}
	void attackOfEnemy(int &xEnemy,int &yEnemy,int difficulty){
		 	for(int i=1;i<30;i++){
		 		for(int j=2;j<103;j++){
		 			if(background[i][j] == 'U' && rand()%5==0){
		 				movingDownEnemy(j,i);
					}
					if(background[i][j] == 'U' && rand()%3==1){
		 				movingLeftEnemy(j,i);
					}
					if(background[i][j] == 'U' && rand()%3==2){
		 				movingRightEnemy(j,i);
					} 
				}
			}
			if(rand()%difficulty==0){
			 	creatingEnemy(xEnemy,yEnemy);
			}
			
	}
	void enemyExploded(int xEnemy,int yEnemy){
		gotoxy(0,0);
		background[yEnemy][xEnemy] = '|';
		background[yEnemy-1][xEnemy] = '|';
		background[yEnemy+1][xEnemy] = '|';
		background[yEnemy+2][xEnemy] = '|';	
		background[yEnemy][xEnemy-1] = '\\';
		background[yEnemy][xEnemy+1] = '/';
		background[yEnemy-1][xEnemy-2] = '\\';	
		background[yEnemy-1][xEnemy+2] = '/';
		background[yEnemy+1][xEnemy-2] = '/';
		background[yEnemy+1][xEnemy+2] = '\\';
	}
	void invisibleEnemyExploded(int xEnemy,int yEnemy){
		gotoxy(0,0);
		background[yEnemy][xEnemy] = ' ';
		background[yEnemy-1][xEnemy] = ' ';
		background[yEnemy+1][xEnemy] = ' ';
		background[yEnemy+2][xEnemy] = ' ';	
		background[yEnemy][xEnemy-1] = ' ';
		background[yEnemy][xEnemy+1] = ' ';
		background[yEnemy-1][xEnemy-2] = ' ';	
		background[yEnemy-1][xEnemy+2] = ' ';
		background[yEnemy+1][xEnemy-2] = ' ';
		background[yEnemy+1][xEnemy+2] = ' ';
	}
	void beShot(){
		for(int i=2;i<24;i++){
			for(int j=1;j<104;j++){
				if(background[i][j]=='|'){
					invisibleEnemyExploded(j,i);
				}
				if(background[i][j]=='U' && (background[i+1][j]=='o' || background[i+1][j-1]=='o' ||background[i+1][j+1]=='o')){
					enemyExploded(j,i);
					 Beep(700, 50);
				}
			}
		}
	}
			
};

void drawTheConsole(){	
	for(int i=0;i<30;i++){
		for(int j=0;j<105;j++){
			cout<<background[i][j];
		}
		cout<<"\n";
	}
}

void endGame(){
	
		for(int j=0;j<105;j++){
			if(background[28][j] == 'A'){
				gameCondition1 = end;
			}
		}
	
}
int main(int argc, char** argv){
	bool continueGame = true;
	int difficulty;
	cout<<"--------------------WELCOME TO AIRCRAFT CONSOLE GAME-----------------\n";
	cout<<"press space to continue....";
	getch();
	while(continueGame == true){
		//clear screen
		system("cls");
		
		gotoxy(40,10);
		cout<<"choose the difficulty:\n";
		cout<<"1. easy\n";
		cout<<"2. immediate\n";
		cout<<"3. Asian\n";
		cout<<"--your choice: ";
		fflush(stdin);
		difficulty = (int)(getch());
		switch(difficulty){
			case 49:
				difficulty = 10;
				break;
			case 50:
				difficulty = 5;
				break;
			case 51:
				difficulty = 2;
				break;
			default:
				{
					gotoxy(40,10);
					cout<<"Default difficulty is easy.";
					getch();
					difficulty = 10;
				}			
		}
		
		srand(time(NULL));
	// khoi tao background
	for(int i=0;i<30;i++){
		for(int j=0;j<105;j++){
			if(i==0||i==29||j==0||j==104){
				background[i][j] = '|';
			}else{
				background[i][j] = ' ';
			}
		}
		cout<<"\n";
	}
	//khoi tao vi tri ban dau cua craft
	craft craft1;				//khoi tao 1 craft
	enemy enemy1;	
	craft1.toaDoXCraft = 50;	//khoi tao vi tri ban dau cho craft1
	int timeRun = 0;
	
		while(1){
			sleep(0); timeRun++;
			gotoxy(0,0);
			//build the aircraft	
			craft1.drawInvisibleCraft(craft1.toaDoXCraft);
			craft1.movingCraft(craft1.toaDoXCraft);
			craft1.drawCraft(craft1.toaDoXCraft);
			if(timeRun%1 == 0){					//decrease the fire rate
				craft1.shot(craft1.toaDoXCraft);
			}
			//build the enemies
			if(timeRun%5==0){
				enemy1.attackOfEnemy(enemy1.xEnemy,enemy1.yEnemy,difficulty);	
			}
			if(rand()%8 == 0){
					enemy1.enemyShot();	
			}
			enemy1.continueShooting();
			//check exploded aircraft or enemies
			enemy1.beShot();
			craft1.beShot();
			
			drawTheConsole();	// the most important thing of building screen
			
			endGame();
			gotoxy(0,30); cout<<"TIME: "<<timeRun;
			if(gameCondition1 == end){	
				break;
			}	
		}
A:		gotoxy(20,30); cout<<"GAME OVER! ";
		cout<<"Press space to continue or ESC to exit game :";
		fflush(stdin);
		char check = getch();
		if((int)check == 32){
			continueGame = true;
			gameCondition1 = maintained;
		}else if((int)check == 27){
			return 0;
		}
		else{
			goto A;
		}
	}	
}
                                                                                  





