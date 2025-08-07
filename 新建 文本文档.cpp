#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<time.h>
#include<graphics.h>
#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define MAX_SNAKE 600

enum dir
{
	up,
	down,
	left,
	right

};
struct by
{
	int x;
	int y;
	DWORD color;


};
struct snake {
	int num;
	int width;
	int score;
	int speed;
	int dir;
	struct by where[MAX_SNAKE];
}snake;
struct food {
	int x;
	int y;
	DWORD color;
	bool flag;

}food;
void 	gameinit()
{
	srand(time(NULL));
	snake.num = 3;
	snake.score = 0;
	snake.speed = 10;
	snake.width = 10;
	snake.dir = right;
	snake.where[0].x = 20;
	snake.where[0].y = 0;
	snake.where[0].color = (RGB(100, 100, 100));
	snake.where[1].x = 10;
	snake.where[1].y = 0;
	snake.where[1].color = (RGB(100, 100, 100));
	snake.where[2].x = 0;
	snake.where[2].y = 0;
	snake.where[2].color = (RGB(100, 100, 100));

	food.x = rand() % (WIN_WIDTH / 10) * 10;
	food.x = rand() % (WIN_HEIGHT / 10) * 10;
	food.color = RGB(rand() % 255, rand() % 255, rand() % 255);
	food.flag = true;
}

void gamedraw() {
	cleardevice();
	setfillcolor(snake.where[0].color);//color
	for (int i = 0; i < snake.num; i++)
	{
		setfillcolor(snake.where[i].color);
		fillrectangle(snake.where[i].x, snake.where[i].y, snake.where[i].x + 10, snake.where[i].y + 10);
	}

	if (food.flag)
	{
		setfillcolor(food.color);
		solidellipse(food.x, food.y, food.x + 10, food.y + 10);

	}
	char temp[20] = "";
	sprintf(temp, "得分%d", snake.score);
	outtextxy(10, 10, temp);


}

void gamemove() {
	for (int i = snake.num; i > 0; i--)
	{
		snake.where[i].x = snake.where[i - 1].x;
		snake.where[i].y = snake.where[i - 1].y;

	}
	switch (snake.dir)
	{
	case up:
		snake.where[0].y = snake.where[0].y - snake.speed;
		break;
	case down:
		snake.where[0].y = snake.where[0].y + snake.speed;
		break;
	case left:
		snake.where[0].x = snake.where[0].x - snake.speed;
		break;
	case right:
		snake.where[0].x = snake.where[0].x + snake.speed;
		break;




	}


}
void gamecontrol() {

	char key = _getch();
	if (key == 72) {
		snake.dir = up;
	}
	if (key == 80) {
		snake.dir = down;
	}
	if (key == 75) {
		snake.dir = left;
	}
	if (key == 77) {
		snake.dir = right;
	}


}

void creatfood() {
	if (!food.flag)
	{
		srand(time(NULL));
		food.x = rand() % (WIN_WIDTH / 10) * 10;
		food.y = rand() % (WIN_HEIGHT / 10) * 10;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.flag = true;
	}


}

void eat() {
	if (food.flag && snake.where[0].x == food.x && snake.where[0].y == food.y)
	{
		food.flag = false;
		snake.num++;
		snake.score += 10;
		snake.where[snake.num - 1].color = RGB(rand() % 256, rand() % 256, rand() % 256);
		creatfood();

	}



}
bool over()
{
	for (int i = snake.num; i > 0; i--)
	{
		if (snake.where[0].x == snake.where[i].x && snake.where[0].y == snake.where[i].y)
		{
			return true;
		}
	}
	return false;
}


void overdraw()
{
	cleardevice();
	char arr[100] = "";
	sprintf(arr, "您失败了，您的最终得分是%d", snake.score);
	outtextxy(WIN_WIDTH / 2 - 100, WIN_HEIGHT / 2, arr);

}


int main()
{
	initgraph(WIN_WIDTH, WIN_HEIGHT);
	setbkcolor(RGB(0, 0, 0));//背景颜色
	cleardevice();
	gameinit();
	while (1)
	{
		int a = 0;
		gamedraw();
		gamemove();
		BeginBatchDraw();
		if (_kbhit())
		{
			gamecontrol();

		}
		FlushBatchDraw();
		eat();
		Sleep(100);
		if (over()) {

			break;
		}

	}
	while (1)
	{
		overdraw();

	}
	closegraph();
	return 0;
}
