#include"Takeaway.h"
void printResult(PRINTRESULT *printresult, int num, RIDER **rider, ORDER *head1, ORDER *head2,FILE *fp)//num为骑手数量
{
	int i;//循环控制变量
	int flag; 
	printf("时间:%d\n", printresult->time);
	printf("钱:%d\n", printresult->money);
	printf("接单数:%d\n", printresult->receiptCnt);
	printf("完成数:%d;结单:", printresult->compeleteCnt);
	fprintf(fp,"时间:%d\n", printresult->time);
	fprintf(fp, "钱:%d\n", printresult->money);
	fprintf(fp, "接单数:%d\n", printresult->receiptCnt);
	fprintf(fp, "完成数:%d;结单:", printresult->compeleteCnt);
	ORDER *current1 = head1->next, *current2 = head2->next;
	struct SplitTask *temp;
	while (current1 != NULL)
	{
		if(current1->next==NULL)
		{
			printf("%d", current1->num);
			fprintf(fp, "%d", current1->num);
		}
		else
		{
			printf("%d ", current1->num);
			fprintf(fp, "%d ", current1->num);
		}
		current1 = current1->next;
	}
	printf(";\n");
	printf("超时数:%d;罚单:", printresult->timeoutCnt);
	fprintf(fp, ";\n");
	fprintf(fp, "超时数:%d;罚单:", printresult->timeoutCnt);
	while (current2 != NULL)
	{
		if(current2->next==NULL)
		{
			printf("%d", current2->num);
			fprintf(fp, "%d", current2->num);
		}
		else
		{
			printf("%d ", current2->num);
			fprintf(fp, "%d ", current2->num);
		}
		current2 = current2->next;
	}
	printf(";\n");
	fprintf(fp, ";\n");
	for (i = 0; i < num; i++)
	{
		printf("骑手%d位置:%d,%d;停靠:", i, rider[i]->locationx, rider[i]->locationy);
		fprintf(fp, "骑手%d位置:%d,%d;停靠:", i, rider[i]->locationx, rider[i]->locationy);
		if(rider[i]->former==NULL)
		{
			printf(";\n");
			fprintf(fp,";\n");
		}
		else
		{
			while (rider[i]->former != NULL)
			{
				if (rider[i]->former->type == 'A')
				{
					flag=0;
					for(temp=rider[i]->former;temp->next!=NULL;)
						if(temp->next->locationx==rider[i]->former->locationx&&temp->next->locationy==rider[i]->former->locationy&&rider[i]->former->type=='B')
						{
							flag=2;
							temp->next=temp->next->next;
						}
						else if(temp->next->locationx==rider[i]->former->locationx&&temp->next->locationy==rider[i]->former->locationy)
						{
							temp->next=temp->next->next;
						}
						else
							temp=temp->next;
				}
				else
				{
					flag=1;
					for(temp=rider[i]->former;temp->next!=NULL;)
						if(temp->next->locationx==rider[i]->former->locationx&&temp->next->locationy==rider[i]->former->locationy&&rider[i]->former->type=='A')
						{
							flag=2;
							temp->next=temp->next->next;
						}
						else if(temp->next->locationx==rider[i]->former->locationx&&temp->next->locationy==rider[i]->former->locationy)
						{
							temp->next=temp->next->next;
						}
						else
							temp=temp->next;
				}
				if(rider[i]->former->next==NULL)
				{
					if(flag==0)
					{
						printf("餐馆 %d %d;",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "餐馆 %d %d;", rider[i]->former->locationx, rider[i]->former->locationy);
					}
					else if(flag==1)
					{
						printf("食客 %d %d;",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "食客 %d %d;", rider[i]->former->locationx, rider[i]->former->locationy);
						
					}
					else if(flag==2)
					{
						printf("餐客 %d %d;",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "餐客 %d %d;", rider[i]->former->locationx, rider[i]->former->locationy);
					}
				}
				else
				{
					if(flag==0)
					{
						printf("餐馆 %d %d ",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "餐馆 %d %d ", rider[i]->former->locationx, rider[i]->former->locationy);
					}
					else if(flag==1)
					{
						printf("食客 %d %d ",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "食客 %d %d ", rider[i]->former->locationx, rider[i]->former->locationy);
						
					}
					else if(flag==2)
					{
						printf("餐客 %d %d ",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "餐客 %d %d ", rider[i]->former->locationx, rider[i]->former->locationy);
					}
				}
				rider[i]->former=rider[i]->former->next;
			}
			printf("\n");
			fprintf(fp, "\n");
		}
	}
	free(head1->next);
	free(head2->next);
	head1->next = NULL;
	head2->next = NULL;
}
void printResultInFile(PRINTRESULT *printresult, int num, RIDER **rider, ORDER *head1, ORDER *head2)
{
	int i;//循环控制变量
	int flag;
	SPLITTASK *temp = NULL;
	FILE *fp=fopen("output.txt","a");
	for(i=0;i<num;i++)
		if(rider[i]->former!=NULL)
		{
			printResult(printresult,num,rider,head1,head2,fp);
			fclose(fp);
			return ;
		}
	fprintf(fp,"时间:%d\n", printresult->time);
	fprintf(fp, "钱:%d\n", printresult->money);
	fprintf(fp, "接单数:%d\n", printresult->receiptCnt);
	fprintf(fp, "完成数:%d;结单:;\n", printresult->compeleteCnt);
	fprintf(fp, "超时数:%d;罚单:;\n", printresult->timeoutCnt);
	for (i = 0; i < num; i++)
		fprintf(fp, "骑手%d位置:%d,%d;停靠:;\n", i, rider[i]->locationx, rider[i]->locationy);
	free(head1->next);
	free(head2->next);
	head1->next = NULL;
	head2->next = NULL;
	fclose(fp);
}
