#include"Takeaway.h"
void printRider(RIDER **rider,int num)//��ӡ���������
{
	int i;
	SPLITTASK *current = NULL;
	for (i = 0; i < num; i++)
	{
		current = rider[i]->next;
		while (current != NULL)
		{
			printf("����%dλ�� %d %d\n", i, current->locationx, current->locationy);
		}
	}
}