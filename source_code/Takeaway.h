#pragma once
#define SHOW_CONSOLE
#include<stdio.h>
#include<stdlib.h>
#include<windows.h> 
#include <mmsystem.h> 
#pragma comment(lib,"WINMM.LIB")
#include<time.h>
#include<math.h>
#include<iostream>
#include<string>
#include <graphics.h>
#include <conio.h>


#define INITIAL_AMOUNT 1000
#define PRICE 300
#define SALARY 10
#define FINE 50 
#define TIMEOUT 30
#define BANKRUPTCY 60
#define XLIMIT 16
#define YLIMIT 16
#define WINDOW_X 600
#define WINDOW_Y 720
#define HOUSE_LENGTH 53
#define ROAD_WIDETH 14
#define ROAD_SIDE 8
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
#define KEY_UP(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
//�ṹ��
typedef struct Order//�洢�ᵥ���������
{
	int num;
	struct Order *next;
}ORDER;
typedef struct Task//��������
{
	int num;
	int time;
	int locationx1, locationy1, locationx2, locationy2;
	struct Task *next;
}TASK;
typedef struct SplitTask
{
	int num;//�������
	int time;//�µ�ʱ��
	int locationx, locationy;//��Ҫ����λ�õĺ�������
	int reachable;//�Ƿ�ɴ0��1�ǣ�
	char type;//ȡ�����Ǽļ���AȡB�ģ�
	struct SplitTask *next;
}SPLITTASK;
typedef struct Rider
{
	int locationx, locationy;//��ǰ����λ�ú�������
	int area;//���ֹ�Ͻ����0����1��2�ң�
	int task;//Ŀǰ������
	int time;//����ѽӶ����������ʱ��
	int direction;//���ַ���
	SPLITTASK *next;
	SPLITTASK *former;
}RIDER;
typedef struct PrintResult//��ӡ���
{
	int time;//��ǰʱ��
	int money;//��ǰ���
	int receiptCnt;//�ӵ���
	int compeleteCnt;//�����
	int timeoutCnt;//��ʱ��
}PRINTRESULT;
//����ԭ�ͣ�
int path(struct Rider **Rider, int num, int time, struct PrintResult *PrintResult, struct Order *statement, struct Order *ticket);
void printResult(PRINTRESULT *printresult, int num, RIDER **rider, ORDER *head1, ORDER *head2, FILE *fp);
void printResultInFile(PRINTRESULT *printresult, int num, RIDER **rider, ORDER *head1, ORDER *head2);
TASK *scanfData(PRINTRESULT *result, int *max);
void distribute(int moment, struct Rider **rider, struct PrintResult *result, int num, struct SplitTask *head);
int success(struct Rider **Rider, int num, int time, struct PrintResult *PrintResult, struct Order *statement, struct Order *ticket);
SPLITTASK *copyNode(SPLITTASK *currentPtr);
struct SplitTask *splitLinkList(TASK *head1);
void FreeTask(TASK *head);
void FreeSplitTask(SPLITTASK *head);
void moveto(struct Rider *Rider, int x, int y);
void animationOutput(RIDER **rider, int num, PRINTRESULT *PrintResult); //�����ƶ�
void mouseInput(SPLITTASK *head);
int coordinateTransfor_1(int &x, int &y);//����任
void coordinateTransfor_2(int &x, int &y);
void coordinateTransfor_3(int &x, int &y);
void printRider(RIDER **rider, int num);//��ӡ���������
void distribute_1(int moment, struct Rider **rider, struct PrintResult *result, int num, struct SplitTask *head);//����Ϊ���������head���(δ���)
