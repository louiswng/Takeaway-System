#include"Takeaway.h"
void FreeTask(TASK*head)
{
	TASK*p = head;
	while (p != NULL)
	{
		head = head->next;
		free(p);
		p = head;
	}
}
void FreeSplitTask(SPLITTASK*head)
{
	SPLITTASK*p = head;
	while (p != NULL)
	{
		head = head->next;
		free(p);
		p = head;
	}
}