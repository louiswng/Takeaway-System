#include"Takeaway.h"
int coordinateTransfor_1(int &x, int &y)//��������任Ϊλ������
{
	int i, j;
	int x1 = ROAD_SIDE - 1, y1 = ROAD_SIDE - 1, x2 = HOUSE_LENGTH + ROAD_SIDE - 1, y2 = HOUSE_LENGTH + ROAD_SIDE - 1;
	int find = 0;
	for (i = 0; i < 9; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (x >= x1&&x <= x2&&y >= y1&&y <= y2)//����Ƿ����ڷ��ӵ�λ��
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
	if (find == 0)//��겻�ڷ�Χ��
		return -1;
	x = 2 * j;
	y = 2 * i;
	return 1;
}
int judgeHouse(int x, int y)//�ж���������Ƿ��ڷ��ӷ�Χ��
{
	if (x % 2 == 0 && y % 2 == 0)
		return 1;
	return 0;
}
void mouseInput(SPLITTASK *head)//����̴߳���
{
	static int num = 1;
	int x, y;
	int left_pressed = 0;

	PIMAGE img[10];




	mouse_msg m1, m2;//������������¼�
	while (1)
	{
		SPLITTASK *current = head;//current�ƶ������������ĩβ
		while (current->next != NULL)
		{
			current = current->next;
		}
		//printf("123\n");
		//while (!(m1 = getmouse()).is_down());//�ȴ�����������
		if ((m1 = getmouse()).is_down())
		{
			mousepos(&x, &y);
			//��ABͼ

			if (coordinateTransfor_1(x, y) == -1)//����任
				continue;
			if (judgeHouse(x, y) == 1)//����ڷ��ӷ�Χ�ڣ��������
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
				while (!(m2 = getmouse()).is_up());//�ȴ�����������
			
				mousepos(&x, &y);
				if (coordinateTransfor_1(x, y) == -1)//����任
					continue;
				if (judgeHouse(x, y) == 1)//����ڷ��ӷ�Χ��
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
