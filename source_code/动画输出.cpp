#include"Takeaway.h"
using namespace std;
void coordinateTransfor_2(int &x, int &y)//λ������任Ϊ��������
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
void coordinateTransfor_3(int &x, int &y)//λ������任Ϊ��������
{
	x = ROAD_SIDE + x / 2 * HOUSE_LENGTH + x / 2 * ROAD_WIDETH;
	y = ROAD_SIDE + y / 2 * HOUSE_LENGTH + y / 2 * ROAD_WIDETH;

}
void animationOutput(RIDER **rider, int num, PRINTRESULT *PrintResult)
{
	int i, j;

	//����ͼ
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


	getimage(img[0], "1.jpg", 56, 30);//����
	getimage(img[1], "2.jpg", 50, 50);//ʱ��
	getimage(img[2], "3.jpg", 50, 50);//��Ǯ
	getimage(img[3], "4.jpg", 50, 50);//��ɵ���
	getimage(img[4], "5.jpg", 50, 50);//��ʱ����
	getimage(img[5], "6.jpg", 0, 0);//����
	getimage(img[6], "7.jpg", 50, 50);//ʳ��	
	getimage(img[7], "8.jpg", 50, 50);//�Ϳ�

									  //��ͼ
	putimage(0, 0, img[0]);//����
	putimage_withalpha(NULL, img[1], 35, 610);//ʱ��
	putimage_withalpha(NULL, img[2], 340, 610);//��Ǯ
	putimage(30, 665, img[3]);//����ɵ���
	putimage(340, 665, img[4]);//��ʱ����

							   //�����Ϳ� ʳ��
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

	//��ӡ��
	setfont(30, 0, "����");
	setcolor(BLACK);
	setbkmode(TRANSPARENT);
	string str[4];
	char s[50];
	sprintf(s, "��ǰʱ�䵥λ %d", PrintResult->time);
	outtextxy(80, 620, s);
	sprintf(s, "Ǯ�� %d", PrintResult->money);
	outtextxy(400, 620, s);
	sprintf(s, "����ɵ��� %d", PrintResult->compeleteCnt);
	outtextxy(80, 670, s);
	sprintf(s, "��ʱ���� %d", PrintResult->timeoutCnt);
	outtextxy(400, 670, s);

	for (i = 0; i < num; i++)//���ֶ���
	{
		x = rider[i]->locationx, y = rider[i]->locationy;
		coordinateTransfor_2(x, y);
		putimage_withalpha(NULL, img[5], x, y);
	}

	for (i = 0; i < 9; i++)//�ͷ�img�ռ�
		delimage(img[i]);
}