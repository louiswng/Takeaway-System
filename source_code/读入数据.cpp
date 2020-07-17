#include"Takeaway.h"
TASK*scanfData(PRINTRESULT *result, int *max)
{
	FILE*fp = fopen("sales.txt", "r");
	int num, time, locationx1, locationy1, locationx2, locationy2;
	TASK*head = (TASK*)malloc(sizeof(TASK)), *last = head, *current = NULL;
	if (fp)//能打开文件
	{
		printf("文件打开成功！\n");
		while (fscanf(fp, "%d %d %d %d %d %d", &num, &time, &locationx1, &locationy1, &locationx2, &locationy2) != EOF)
		{
			current = (TASK*)malloc(sizeof(TASK));
			current->num = num, current->time = time, current->locationx1 = locationx1, current->locationy1 = locationy1, current->locationx2 = locationx2, current->locationy2 = locationy2;
			current->next = NULL;
			last->next = current;
			last = current;
			*max = *max<time ? time : *max;
		}
		fclose(fp);
	}
	else//文件无法打开
	{
		return NULL;
	}
	return head->next;
}
