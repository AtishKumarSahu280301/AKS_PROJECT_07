#include<stdio.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>

#define N 25
#define M 90

int row, col, field[N][M], x, y, head, tail, Gy, game, fruit, a, b, variable, direction = 'd', score, highscore, speed;

FILE *f;
void snake() //create of snake
{
	f  = fopen("E:\\highscore.txt","r");
	fscanf(f,"High Score : %d",&highscore);
	fclose(f);
	
	for(row = 0; row < N; row++)
	{
		for(col = 0; col < M; col++)
		{
			field[row][col] = 0; 
		}
	}
	x = row/2;
	y = col/2;
	
	head = 3;
	tail = 1;
	
	Gy = y;
	
	game = 0;
	
	fruit = 0;
	
	score = 0;
	
	speed = 99;
	
	for(row = 0; row < head; row++)
	{
		Gy++;
		field[x][Gy-head] = row + 1;
	}
}
void print() //boundary
{
	for(row = 0; row <= M+1; row++)
	{
		if(row == 0)
		{
			printf("%c",201);
		}
		else if(row == M+1)
		{
			printf("%c",187);
		}
		else
		{
			printf("%c",205);
		}
	}
	printf("\n");
	for(row = 0; row < N; row++)
	{
		printf("%c",186);
		for(col = 0; col < M; col++)
		{
			if(field[row][col] == 0)
				printf(" ");
				
			if(field[row][col] > 0 && field[row][col] != head)
				printf("o");
				
			if(field[row][col] == head)
				printf("O");
			
			if(field[row][col] == -1) //generate fruit in screen
				printf("*");
			
			if(col == M-1)
				printf("%c\n",186);
		}
	}
	for(row = 0; row <= M+1; row++)
	{
		if(row == 0)
		{
			printf("%c",200);
		}
		else if(row == M+1)
		{
			printf("%c",188);
		}
		else
		{
			printf("%c",205);
		}
	}
	printf("\nCurrent Score : %d",score);
	printf("\nHigh Score : %d",highscore);
}
void resetscreenposition()//reset the entire screen
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut,Position);
	
}
void Random() //random generation of fruit
{
	srand(time(0));
	a = 1 + rand() % 23;
	b = 1 + rand() % 88;
	
	if(fruit == 0 && field[a][b] == 0)
	{
		field[a][b] = -1;
		fruit = 1;
		if(speed > 10 && score != 0)
			speed = speed - 5;
	}
}
int getchar()
{
	if(_kbhit())
		return _getch();
	else
		return -1;
}

void movement()
{
	variable = getchar();
	variable = tolower(variable);
	
	if(((variable == 'd' || variable == 'a')|| (variable == 'w' || variable == 's')) && (abs(direction - variable) > 3))
		direction = variable;

	if(direction == 'd')
	{
		y++;
		if(field[x][y] != 0 && field[x][y] != -1)
			gameover();
		if(y == M-1)
			y = 0;
		if(field[x][y] == -1)
		{
			fruit = 0;
			score += 10;
			tail -= 3;
		}
		head++;
		field[x][y] = head;
	}
	
	if(direction == 'a')
	{
		y--;
		if(field[x][y] != 0 && field[x][y] != -1)
			gameover();
		if(y == 0)
			y = M-1;
		if(field[x][y] == -1)
		{
			fruit = 0;
			score += 10;
			tail -= 3;
		}
		head++;
		field[x][y] = head;
	}
	
	if(direction == 'w')
	{
		x--;
		if(field[x][y] != 0 && field[x][y] != -1)
			gameover();
		if(x == 0)
			x = N-1;
		if(field[x][y] == -1)
		{
			fruit = 0;
			score += 10;
			tail -= 3;
		}
		head++;
		field[x][y] = head;
	}
	
	if(direction == 's')
	{
		x++;
		if(field[x][y] != 0 && field[x][y] != -1)
			gameover();
		if(x == N - 1)
			x = 0;
		if(field[x][y] == -1)
		{
			fruit = 0;
			score += 10;
			tail -= 3;
		}
		head++;
		field[x][y] = head;
	}
	
}
void TailRemove()
{
	for(row = 0; row < N; row++)
	{
		for(col = 0; col < M; col++)
		{
			if(field[row][col] == tail)
			{
				field[row][col] = 0;
			}
		}
	}
	tail++;
}
int gameover()
{
	printf("\a");
	Sleep(100);
	system("cls");
	
	if(score > highscore)
	{
		printf("\nNew High Score : %d\n",score);
		system("pause");
		f = fopen("E:\\highscore.txt","w");
		fprintf(f,"High Score : %d",score);
		fclose(f);
	}
	
	system("cls");
	printf("\nGame Over!");
	printf("\nScore : %d",score);
	printf("\nPlease Enter To Play Again Or Esc To Exit: ");
	
	while(1)
	{
		variable = getchar();
		if(variable == 13)
		{
			game = 0;
			snake();
			break;	
		}
		else if(variable == 27)
		{
			game = 1;
			break;
		}
	}
	system("Cls");
}
int main()
{	

	snake();
	
	while(game == 0)
	{
		print();
		resetscreenposition();
		Random();
		movement();
		TailRemove();
		Sleep(speed);
	}
}