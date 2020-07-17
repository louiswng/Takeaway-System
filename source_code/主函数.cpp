#include"Takeaway.h"
int main()
{
	//新建音乐播放线程
	PlaySound(TEXT(".\\背景音乐.wav"), NULL, SND_LOOP | SND_ASYNC);

	struct Rider *Rider[10];
	struct SplitTask *SplitTask = (SPLITTASK*)malloc(sizeof(SPLITTASK)), *temp;
	SplitTask->next = NULL;
	struct Task *Task = NULL;
	int time, count, num, count1 = 1, max = 1, flag;
	double start, end;
	struct PrintResult *PrintResult = (PRINTRESULT*)malloc(sizeof(struct PrintResult));
	struct Order *statement = (ORDER*)malloc(sizeof(struct Order)), *ticket = (ORDER*)malloc(sizeof(struct Order));
	statement->next = NULL, ticket->next = NULL;

	if (INITIAL_AMOUNT <= PRICE + FINE)
		num = INITIAL_AMOUNT / PRICE;
	else
		num = (INITIAL_AMOUNT - 2 * FINE) / PRICE;
	statement->next = NULL;
	ticket->next = NULL;
	PrintResult->compeleteCnt = 0;
	PrintResult->money = INITIAL_AMOUNT - PRICE*num;
	PrintResult->receiptCnt = 0;
	PrintResult->time = 0;
	PrintResult->timeoutCnt = 0;
	for (count = 0; count<num; count++)
	{
		Rider[count] = (RIDER*)malloc(sizeof(struct Rider));
		Rider[count]->locationx = 8;
		Rider[count]->locationy = 7;
		Rider[count]->next = NULL;
		Rider[count]->task = 0;
		Rider[count]->time = 0;
		Rider[count]->area = count % 3;
		Rider[count]->former = NULL;
	}

	printResultInFile(PrintResult, num, Rider, statement, ticket);

	initgraph(WINDOW_X, WINDOW_Y);
	animationOutput(Rider, num, PrintResult);

	Task = scanfData(PrintResult, &max);
	HANDLE hThread1;
	if (Task == NULL)//鼠标键入
	{
		DWORD hThreadID1;
		hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)mouseInput, SplitTask, 0, &hThreadID1);
		start = (double)clock();
		PrintResult->time = 1;
		end = (double)clock();
		Sleep(2 * 1000 - (end - start) / CLOCKS_PER_SEC);

		for (time = 1; /*count1 != 0 || time <= max*/1; Sleep(2000 - (end - start) / CLOCKS_PER_SEC), time++, PrintResult->time++)
		{
			start = (double)clock();
			if (PrintResult->money >= PRICE + 2 * FINE&&num <= 9)
			{
				num++;
				Rider[num - 1] = (RIDER*)malloc(sizeof(struct Rider));
				Rider[num - 1]->locationx = 8;
				Rider[num - 1]->locationy = 7;
				Rider[num - 1]->next = NULL;
				Rider[num - 1]->task = 0;
				Rider[num - 1]->time = 0;
				Rider[num - 1]->area = (num - 1) % 3;
				PrintResult->money -= PRICE;
			}

			flag = path(Rider, num, time, PrintResult, statement, ticket);
			if (flag == -1)
			{
				printf("恶意废单，破产\n");
				FILE *fp = fopen("output.txt", "a");
				fprintf(fp, "恶意废单，破产\n");
				break;
			}
			if (PrintResult->money<0)
			{
				printf("现金不够，破产\n");
				FILE *fp = fopen("output.txt", "a");
				fprintf(fp, "现金不够，破产\n");
				break;
			}
			distribute_1(time, Rider, PrintResult, num, SplitTask);
			flag = success(Rider, num, time, PrintResult, statement, ticket);
			if (flag == -1)
			{
				printf("恶意废单，破产\n");
				FILE *fp = fopen("output.txt", "a");
				fprintf(fp, "恶意废单，破产\n");
				break;
			}
			if (PrintResult->money<0)
			{
				printf("现金不够，破产\n");
				FILE *fp = fopen("output.txt", "a");
				fprintf(fp, "现金不够，破产\n");
				break;
			}

			animationOutput(Rider, num, PrintResult);
			end = (double)clock();
		}
	}
	else//文件读取
	{
		SplitTask->next = splitLinkList(Task);
		start = (double)clock();
		PrintResult->time = 1;
		end = (double)clock();
		Sleep(2 * 1000 - (end - start) / CLOCKS_PER_SEC);

		for (time = 1; count1 != 0 || time <= max; /*Sleep(2000 - (end - start) / CLOCKS_PER_SEC),*/ time++, PrintResult->time++)
		{
			start = (double)clock();
			if (PrintResult->money >= PRICE + 2 * FINE&&num <= 9)
			{
				num++;
				Rider[num - 1] = (RIDER*)malloc(sizeof(struct Rider));
				Rider[num - 1]->locationx = 8;
				Rider[num - 1]->locationy = 7;
				Rider[num - 1]->next = NULL;
				Rider[num - 1]->task = 0;
				Rider[num - 1]->time = 0;
				Rider[num - 1]->area = (num - 1) % 3;
				PrintResult->money -= PRICE;
			}

			flag = path(Rider, num, time, PrintResult, statement, ticket);
			if (flag == -1)
			{
				printf("恶意废单，破产\n");
				FILE *fp = fopen("output.txt", "a");
				fprintf(fp, "恶意废单，破产\n");
				break;
			}
			if (PrintResult->money<0)
			{
				printf("现金不够，破产\n");
				FILE *fp = fopen("output.txt", "a");
				fprintf(fp, "现金不够，破产\n");
				break;
			}
			distribute(time, Rider, PrintResult, num, SplitTask);
			flag = success(Rider, num, time, PrintResult, statement, ticket);
			if (flag == -1)
			{
				printf("恶意废单，破产\n");
				FILE *fp = fopen("output.txt", "a");
				fprintf(fp, "恶意废单，破产\n");
				break;
			}
			if (PrintResult->money<0)
			{
				printf("现金不够，破产\n");
				FILE *fp = fopen("output.txt", "a");
				fprintf(fp, "现金不够，破产\n");
				break;
			}

			animationOutput(Rider, num, PrintResult);
			printResultInFile(PrintResult, num, Rider, statement, ticket);
			for (count1 = 0, count = 0; count<num; count++)
				if (Rider[count]->next != NULL)
					count1++;
			end = (double)clock();
		}
	}


	CloseHandle(hThread1);
	ege::getch();
	//closegraph();
	FreeTask(Task);
	FreeSplitTask(SplitTask);
	system("pause");
}
