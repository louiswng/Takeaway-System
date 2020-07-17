#include"Takeaway.h"
using namespace std;
void coordinateTransfor_2(int &x, int &y)//位置坐标变换为像素坐标
{
	if (x % 2 == 1 && y % 2 == 0)
	{
		x = ROAD_SIDE + (x + 1) / 2 * HOUSE_LENGTH + (x - 1) / 2 * ROAD_WIDETH - 16;
		y = ROAD_SIDE + y / 2 * HOUSE_LENGTH + y / 2 * ROAD_WIDETH;
	}
	else
	{
		x = ROAD_SIDE + x / 2 * HOUSE_LENGTH + x / 2 * ROAD_WIDETH;
		y = ROAD_SIDE + (y + 1) / 2 * HOUSE_LENGTH + (y - 1) / 2 * ROAD_WIDETH - 19;
	}
}
void coordinateTransfor_3(int &x, int &y)//位置坐标变换为像素坐标
{
	x = ROAD_SIDE + x / 2 * HOUSE_LENGTH + x / 2 * ROAD_WIDETH;
	y = ROAD_SIDE + y / 2 * HOUSE_LENGTH + y / 2 * ROAD_WIDETH;

}
void animationOutput(RIDER **rider, int num, PRINTRESULT *PrintResult)
{
	int i, j;

	//创建图
	PIMAGE img[9];
	img[0] = newimage(600, 720);
	img[1] = newimage(20, 20);
	img[2] = newimage(20, 20);
	img[3] = newimage(20, 20);
	img[4] = newimage(20, 20);
	img[5] = newimage(20, 20);
	img[6] = newimage(20, 20);
	img[7] = newimage(20, 20);
	img[8] = newimage(20, 20);


	getimage(img[0], "1.jpg", 56, 30);//背景
	getimage(img[1], "2.jpg", 50, 50);//时间
	getimage(img[2], "3.jpg", 50, 50);//金钱
	getimage(img[3], "4.jpg", 50, 50);//完成单数
	getimage(img[4], "5.jpg", 50, 50);//超时单数
	getimage(img[5], "6.jpg", 0, 0);//骑手
	getimage(img[6], "7.jpg", 50, 50);//食客	
	getimage(img[7], "8.jpg", 50, 50);//餐客

									  //贴图
	putimage(0, 0, img[0]);//背景
	putimage_withalpha(NULL, img[1], 35, 610);//时间
	putimage_withalpha(NULL, img[2], 340, 610);//金钱
	putimage(30, 665, img[3]);//已完成单数
	putimage(340, 665, img[4]);//超时单数

							   //点亮餐客 食客
	int x, y;
	SPLITTASK *current = NULL;
	for (i = 0; i < num; i++)
	{
		current = rider[i]->next;
		while (current != NULL)
		{
			x = current->locationx;
			y = current->locationy;
			coordinateTransfor_3(x, y);
			if (current->type == 'A')
				putimage(x, y, img[6]);
			else
				putimage(x, y, img[7]);
			current = current->next;
		}
	}

	//打印字
	setfont(30, 0, "宋体");
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	string str[4];
	char s[50];
	sprintf(s, "当前时间单位 %d", PrintResult->time);
	outtextxy(80, 620, s);
	sprintf(s, "钱数 %d", PrintResult->money);
	outtextxy(400, 620, s);
	sprintf(s, "已完成单数 %d", PrintResult->compeleteCnt);
	outtextxy(80, 670, s);
	sprintf(s, "超时单数 %d", PrintResult->timeoutCnt);
	outtextxy(400, 670, s);

	for (i = 0; i < num; i++)//骑手动画
	{
		x = rider[i]->locationx, y = rider[i]->locationy;
		coordinateTransfor_2(x, y);
		putimage_withalpha(NULL, img[5], x, y);
	}

	for (i = 0; i < 9; i++)//释放img空间
		delimage(img[i]);
}