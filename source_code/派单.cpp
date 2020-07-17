#include"Takeaway.h"
int riderJudge(SPLITTASK *head)//区域判断
{
	SPLITTASK *current1 = head;
	if (current1->locationx <= XLIMIT / 2 && current1->next->locationx <= XLIMIT / 2)//区域1
		return 2;
	else if (current1->locationx >= XLIMIT / 2 && current1->next->locationx >= XLIMIT / 2)//区域2
		return 3;
	else//跨区域
		return 1;
}
SPLITTASK *copyNode(SPLITTASK *currentPtr)//拷贝结点信息
{
	SPLITTASK *current = (SPLITTASK *)malloc(sizeof(SPLITTASK));
	current->num = currentPtr->num, current->time = currentPtr->time, current->locationx = currentPtr->locationx, current->locationy = currentPtr->locationy, current->reachable = currentPtr->reachable, current->type = currentPtr->type;
	return current;
}
void distribute(int moment, struct Rider **rider, struct PrintResult *result, int num, struct SplitTask *head)//输入为文件时，执行这个函数派单 
{
	SPLITTASK *current = head->next;
	SPLITTASK *head1 = (SPLITTASK *)malloc(sizeof(SPLITTASK)), *head2 = (SPLITTASK *)malloc(sizeof(SPLITTASK)), *head3 = (SPLITTASK *)malloc(sizeof(SPLITTASK));
	head1->next = NULL, head2->next = NULL, head3->next = NULL;
	SPLITTASK *last1 = head1, *last2 = head2, *last3 = head3;
	SPLITTASK *temp;
	int count, min, mini;

	if (num == 1)//骑手数为1时 
	{
		while (current != NULL&&current->time <= moment)
		{
			if (current->time<moment)
			{
				current = current->next;
				continue;
			}
			SPLITTASK *current1, *last1 = head1;
			current1 = copyNode(current), current1->next = NULL, last1->next = current1, last1 = last1->next; current1 = copyNode(current->next), current1->next = NULL, last1->next = current1, last1 = last1->next;
			if (rider[0]->next == NULL)
			{
				rider[0]->next = head1->next;
			}
			else
			{
				for (temp = rider[0]->next; temp->next != NULL; temp = temp->next);
				temp->next = head1->next;
			}
			result->receiptCnt++;
			current = current->next;
		}
		return;
	}
	else if (num == 2)//骑手数为2时 
	{
		while (current != NULL&&current->time <= moment)
		{
			if (current->time<moment)
			{
				current = current->next->next;
				continue;
			}
			SPLITTASK *current1, *last1 = head1;
			current1 = copyNode(current), current1->next = NULL, last1->next = current1, last1 = last1->next; current1 = copyNode(current->next), current1->next = NULL, last1->next = current1, last1 = last1->next;
			mini = rider[0]->time<rider[1]->time ? 0 : 1;
			if (rider[mini]->next == NULL)
			{
				rider[mini]->next = head1->next;
			}
			else
			{
				for (temp = rider[mini]->next; temp->next != NULL; temp = temp->next);
				temp->next = head1->next;
			}
			result->receiptCnt++;
			current = current->next->next;
		}
		return;
	}
	while (current != NULL&&current->time <= moment)//骑手数大于等于3时 
	{
		if (current->time<moment)
		{
			current = current->next;
			continue;
		}
		head1->next = NULL, head2->next = NULL, head3->next = NULL;
		last1 = head1, last2 = head2, last3 = head3;
		SPLITTASK *current1, *current2, *current3;
		switch (riderJudge(current))//判断区域 
		{
		case 1:
			current1 = copyNode(current), current1->next = NULL, last1->next = current1, last1 = last1->next; current1 = copyNode(current->next), current1->next = NULL, last1->next = current1, last1 = last1->next;
			for (count = 3, min = rider[0]->time, mini = 0; count<num; count += 3)
				if (rider[count]->time<min)
				{
					min = rider[count]->time;
					mini = count;
				}
			if (rider[mini]->time >= TIMEOUT)
				for (count = 0, min = rider[0]->time, mini = 0; count<num; count++)
					if (rider[count]->time<min)
					{
						min = rider[count]->time;
						mini = count;
					}
			if (rider[mini]->next == NULL)
			{
				rider[mini]->next = head1->next;
			}
			else
			{
				for (temp = rider[mini]->next; temp->next != NULL; temp = temp->next);
				temp->next = head1->next;
			}
			break;
		case 2:
			current2 = copyNode(current), current2->next = NULL, last2->next = current2, last2 = last2->next; current2 = copyNode(current->next), current2->next = NULL, last2->next = current2, last2 = last2->next;
			for (count = 4, min = rider[1]->time, mini = 1; count<num; count += 3)
				if (rider[count]->time<min)
				{
					min = rider[count]->time;
					mini = count;
				}
			if (rider[mini]->time >= TIMEOUT)
				for (count = 0, min = rider[0]->time, mini = 0; count<num; count++)
					if (rider[count]->time<min)
					{
						min = rider[count]->time;
						mini = count;
					}
			if (rider[mini]->next == NULL)
			{
				rider[mini]->next = head2->next;
			}
			else
			{
				for (temp = rider[mini]->next; temp->next != NULL; temp = temp->next);
				temp->next = head2->next;
			}
			break;
		case 3:
			current3 = copyNode(current), current3->next = NULL, last3->next = current3, last3 = last3->next; current3 = copyNode(current->next), current3->next = NULL, last3->next = current3, last3 = last3->next;
			for (count = 5, min = rider[2]->time, mini = 2; count<num; count += 3)
				if (rider[count]->time<min)
				{
					min = rider[count]->time;
					mini = count;
				}
			if (rider[mini]->time >= TIMEOUT)
				for (count = 0, min = rider[0]->time, mini = 0; count<num; count++)
					if (rider[count]->time<min)
					{
						min = rider[count]->time;
						mini = count;
					}
			if (rider[mini]->next == NULL)
			{
				rider[mini]->next = head3->next;
			}
			else
			{
				for (temp = rider[mini]->next; temp->next != NULL; temp = temp->next);
				temp->next = head3->next;
			}
			break;
		}
		result->receiptCnt++;
		current = current->next->next;
	}
	return;
}
void distribute_1(int moment, struct Rider **rider, struct PrintResult *result, int num, struct SplitTask *head)//输入为鼠标键入时，执行此函数 
{
	SPLITTASK *current = head->next;
	SPLITTASK *head1 = (SPLITTASK *)malloc(sizeof(SPLITTASK)), *head2 = (SPLITTASK *)malloc(sizeof(SPLITTASK)), *head3 = (SPLITTASK *)malloc(sizeof(SPLITTASK));
	head1->next = NULL, head2->next = NULL, head3->next = NULL;
	SPLITTASK *last1 = head1, *last2 = head2, *last3 = head3;
	SPLITTASK *temp;
	int count, min, mini;

	if (num == 1)//骑手数为1时 
	{
		while (current != NULL&&current->next != NULL)
		{
			SPLITTASK *current1, *last1 = head1;
			current1 = copyNode(current), current1->next = NULL, current1->time = moment, last1->next = current1, last1 = last1->next; current1 = copyNode(current->next), current1->next = NULL, current1->time = moment, last1->next = current1, last1 = last1->next;
			if (rider[0]->next == NULL)
			{
				rider[0]->next = head1->next;
				head->next = NULL;
			}
			else
			{
				for (temp = rider[0]->next; temp->next != NULL; temp = temp->next);
				temp->next = head1->next;
				head->next = NULL;
			}
			result->receiptCnt++;
			current = current->next->next;
		}
		return;
	}
	else if (num == 2)//骑手数为2时 
	{
		while (current != NULL&&current->next != NULL)
		{
			SPLITTASK *current1, *last1 = head1;
			current1 = copyNode(current), current1->next = NULL, current1->time = moment, last1->next = current1, last1 = last1->next; current1 = copyNode(current->next), current1->next = NULL, current1->time = moment, last1->next = current1, last1 = last1->next;
			mini = rider[0]->time<rider[1]->time ? 0 : 1;
			if (rider[mini]->next == NULL)
			{
				rider[mini]->next = head1->next;
				head->next = NULL;
			}
			else
			{
				for (temp = rider[mini]->next; temp->next != NULL; temp = temp->next);
				temp->next = head1->next;
				head->next = NULL;
			}
			result->receiptCnt++;
			current = current->next->next;
		}
		return;
	}
	while (current != NULL&&current->next != NULL)//骑手数为3或3以上时 
	{
		head1->next = NULL, head2->next = NULL, head3->next = NULL;
		last1 = head1, last2 = head2, last3 = head3;
		SPLITTASK *current1, *current2, *current3;
		switch (riderJudge(current))//判断区域 
		{
		case 1:
			current1 = copyNode(current), current1->next = NULL, current1->time = moment, last1->next = current1, last1 = last1->next; current1 = copyNode(current->next), current1->next = NULL, current1->time = moment, last1->next = current1, last1 = last1->next;
			for (count = 3, min = rider[0]->time, mini = 0; count<num; count += 3)
				if (rider[count]->time<min)
				{
					min = rider[count]->time;
					mini = count;
				}
			if (rider[mini]->time >= TIMEOUT)
				for (count = 0, min = rider[0]->time, mini = 0; count<num; count++)
					if (rider[count]->time<min)
					{
						min = rider[count]->time;
						mini = count;
					}
			if (rider[mini]->next == NULL)
			{
				rider[mini]->next = head1->next;
				head->next = NULL;
			}
			else
			{
				for (temp = rider[mini]->next; temp->next != NULL; temp = temp->next);
				temp->next = head1->next;
				head->next = NULL;
			}
			break;
		case 2:
			current2 = copyNode(current), current2->next = NULL, current2->time = moment, last2->next = current2, last2 = last2->next; current2 = copyNode(current->next), current2->next = NULL, current2->time = moment, last2->next = current2, last2 = last2->next;
			for (count = 4, min = rider[1]->time, mini = 1; count<num; count += 3)
				if (rider[count]->time<min)
				{
					min = rider[count]->time;
					mini = count;
				}
			if (rider[mini]->time >= TIMEOUT)
				for (count = 0, min = rider[0]->time, mini = 0; count<num; count++)
					if (rider[count]->time<min)
					{
						min = rider[count]->time;
						mini = count;
					}
			if (rider[mini]->next == NULL)
			{
				rider[mini]->next = head2->next;
				head->next = NULL;
			}
			else
			{
				for (temp = rider[mini]->next; temp->next != NULL; temp = temp->next);
				temp->next = head2->next;
				head->next = NULL;
			}
			break;
		case 3:
			current3 = copyNode(current), current3->next = NULL, current3->time = moment, last3->next = current3, last3 = last3->next; current3 = copyNode(current->next), current3->next = NULL, current3->time = moment, last3->next = current3, last3 = last3->next;
			for (count = 5, min = rider[2]->time, mini = 2; count<num; count += 3)
				if (rider[count]->time<min)
				{
					min = rider[count]->time;
					mini = count;
				}
			if (rider[mini]->time >= TIMEOUT)
				for (count = 0, min = rider[0]->time, mini = 0; count<num; count++)
					if (rider[count]->time<min)
					{
						min = rider[count]->time;
						mini = count;
					}
			if (rider[mini]->next == NULL)
			{
				rider[mini]->next = head3->next;
				head->next = NULL;
			}
			else
			{
				for (temp = rider[mini]->next; temp->next != NULL; temp = temp->next);
				temp->next = head3->next;
				head->next = NULL;
			}
			break;
		}
		result->receiptCnt++;
		current = current->next->next;
	}
	return;
}
