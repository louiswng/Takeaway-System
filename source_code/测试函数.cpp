#include"Takeaway.h"
void printRider(RIDER **rider,int num)//打印待处理队列
{
	int i;
	SPLITTASK *current = NULL;
	for (i = 0; i < num; i++)
	{
		current = rider[i]->next;
		while (current != NULL)
		{
			printf("骑手%d位置 %d %d\n", i, current->locationx, current->locationy);
		}
	}
}