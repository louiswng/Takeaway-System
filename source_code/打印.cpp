#include"Takeaway.h"
void printResult(PRINTRESULT *printresult, int num, RIDER **rider, ORDER *head1, ORDER *head2,FILE *fp)//numΪ��������
{
	int i;//ѭ�����Ʊ���
	int flag; 
	printf("ʱ��:%d\n", printresult->time);
	printf("Ǯ:%d\n", printresult->money);
	printf("�ӵ���:%d\n", printresult->receiptCnt);
	printf("�����:%d;�ᵥ:", printresult->compeleteCnt);
	fprintf(fp,"ʱ��:%d\n", printresult->time);
	fprintf(fp, "Ǯ:%d\n", printresult->money);
	fprintf(fp, "�ӵ���:%d\n", printresult->receiptCnt);
	fprintf(fp, "�����:%d;�ᵥ:", printresult->compeleteCnt);
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
	printf("��ʱ��:%d;����:", printresult->timeoutCnt);
	fprintf(fp, ";\n");
	fprintf(fp, "��ʱ��:%d;����:", printresult->timeoutCnt);
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
		printf("����%dλ��:%d,%d;ͣ��:", i, rider[i]->locationx, rider[i]->locationy);
		fprintf(fp, "����%dλ��:%d,%d;ͣ��:", i, rider[i]->locationx, rider[i]->locationy);
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
						printf("�͹� %d %d;",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "�͹� %d %d;", rider[i]->former->locationx, rider[i]->former->locationy);
					}
					else if(flag==1)
					{
						printf("ʳ�� %d %d;",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "ʳ�� %d %d;", rider[i]->former->locationx, rider[i]->former->locationy);
						
					}
					else if(flag==2)
					{
						printf("�Ϳ� %d %d;",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "�Ϳ� %d %d;", rider[i]->former->locationx, rider[i]->former->locationy);
					}
				}
				else
				{
					if(flag==0)
					{
						printf("�͹� %d %d ",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "�͹� %d %d ", rider[i]->former->locationx, rider[i]->former->locationy);
					}
					else if(flag==1)
					{
						printf("ʳ�� %d %d ",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "ʳ�� %d %d ", rider[i]->former->locationx, rider[i]->former->locationy);
						
					}
					else if(flag==2)
					{
						printf("�Ϳ� %d %d ",rider[i]->former->locationx,rider[i]->former->locationy);
						fprintf(fp, "�Ϳ� %d %d ", rider[i]->former->locationx, rider[i]->former->locationy);
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
	int i;//ѭ�����Ʊ���
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
	fprintf(fp,"ʱ��:%d\n", printresult->time);
	fprintf(fp, "Ǯ:%d\n", printresult->money);
	fprintf(fp, "�ӵ���:%d\n", printresult->receiptCnt);
	fprintf(fp, "�����:%d;�ᵥ:;\n", printresult->compeleteCnt);
	fprintf(fp, "��ʱ��:%d;����:;\n", printresult->timeoutCnt);
	for (i = 0; i < num; i++)
		fprintf(fp, "����%dλ��:%d,%d;ͣ��:;\n", i, rider[i]->locationx, rider[i]->locationy);
	free(head1->next);
	free(head2->next);
	head1->next = NULL;
	head2->next = NULL;
	fclose(fp);
}
