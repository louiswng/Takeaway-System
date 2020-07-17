#include"Takeaway.h"
int coordinateTransfor_1(int &x, int &y)//像素坐标变换为位置坐标
{
	int i, j;
	int x1 = ROAD_SIDE - 1, y1 = ROAD_SIDE - 1, x2 = HOUSE_LENGTH + ROAD_SIDE - 1, y2 = HOUSE_LENGTH + ROAD_SIDE - 1;
	int find = 0;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (x >= x1&&x <= x2&&y >= y1&&y <= y2)//鼠标是否点击在房子的位置
			{
				find = 1; break;
			}
			x1 += ROAD_WIDETH + HOUSE_LENGTH;
			x2 += ROAD_WIDETH + HOUSE_LENGTH;
		}
		if (find == 1)
			break;
		x1 = ROAD_SIDE - 1, x2 = HOUSE_LENGTH + ROAD_SIDE - 1;
		y1 += ROAD_WIDETH + HOUSE_LENGTH; y2 += ROAD_WIDETH + HOUSE_LENGTH;
	}
	if (find == 0)//鼠标不在范围内
		return -1;
	x = 2 * j;
	y = 2 * i;
	return 1;
}
int judgeHouse(int x, int y)//判断鼠标坐标是否在房子范围内
{
	if (x % 2 == 0 && y % 2 == 0)
		return 1;
	return 0;
}
void mouseInput(SPLITTASK *head)//鼠标线程处理
{
	static int num = 1;
	int x, y;
	int left_pressed = 0;

	PIMAGE img[10];




	mouse_msg m1, m2;//保存两次鼠标事件
	while (1)
	{
		SPLITTASK *current = head;//current移动到待处理队列末尾
		while (current->next != NULL)
		{
			current = current->next;
		}
		//printf("123\n");
		//while (!(m1 = getmouse()).is_down());//等待鼠标左键按下
		if ((m1 = getmouse()).is_down())
		{
			mousepos(&x, &y);
			//贴AB图

			if (coordinateTransfor_1(x, y) == -1)//坐标变换
				continue;
			if (judgeHouse(x, y) == 1)//鼠标在房子范围内，添加任务
			{
				SPLITTASK *last = (SPLITTASK*)malloc(sizeof(SPLITTASK));
				current->next = last;
				last->locationx = x;
				last->locationy = y;
				last->num = num;
				last->reachable = 1;
				last->type = 'A';
				last->next = NULL;
				current = current->next;
				printf("x=%d y=%d\n", x, y);
			}
				while (!(m2 = getmouse()).is_up());//等待鼠标左键弹起
			
				mousepos(&x, &y);
				if (coordinateTransfor_1(x, y) == -1)//坐标变换
					continue;
				if (judgeHouse(x, y) == 1)//鼠标在房子范围内
				{
					SPLITTASK *last = (SPLITTASK*)malloc(sizeof(SPLITTASK));
					current->next = last;
					last->locationx = x;
					last->locationy = y;
					last->num = num;
					num++;
					last->reachable = 0;
					last->type = 'B';
					last->next = NULL;
					current = current->next;
					printf("x=%d y=%d\n", x, y);
				}
			}
			//Sleep(20);
		}
}
