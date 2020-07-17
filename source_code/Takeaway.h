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
//结构体
typedef struct Order//存储结单，罚单序号
{
	int num;
	struct Order *next;
}ORDER;
typedef struct Task//读入数据
{
	int num;
	int time;
	int locationx1, locationy1, locationx2, locationy2;
	struct Task *next;
}TASK;
typedef struct SplitTask
{
	int num;//订单序号
	int time;//下单时间
	int locationx, locationy;//需要到达位置的横纵坐标
	int reachable;//是否可达（0否1是）
	char type;//取件还是寄件（A取B寄）
	struct SplitTask *next;
}SPLITTASK;
typedef struct Rider
{
	int locationx, locationy;//当前所在位置横纵坐标
	int area;//骑手管辖区域（0跨区1左2右）
	int task;//目前任务数
	int time;//完成已接订单所需最短时间
	int direction;//骑手方向
	SPLITTASK *next;
	SPLITTASK *former;
}RIDER;
typedef struct PrintResult//打印结果
{
	int time;//当前时间
	int money;//当前金额
	int receiptCnt;//接单数
	int compeleteCnt;//完成数
	int timeoutCnt;//超时数
}PRINTRESULT;
//函数原型：
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
void animationOutput(RIDER **rider, int num, PRINTRESULT *PrintResult); //骑手移动
void mouseInput(SPLITTASK *head);
int coordinateTransfor_1(int &x, int &y);//坐标变换
void coordinateTransfor_2(int &x, int &y);
void coordinateTransfor_3(int &x, int &y);
void printRider(RIDER **rider, int num);//打印待处理队列
void distribute_1(int moment, struct Rider **rider, struct PrintResult *result, int num, struct SplitTask *head);//参数为待处理队列head结点(未拆分)
