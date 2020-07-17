#include"Takeaway.h"
struct SplitTask *splitLinkList(TASK *head1)
{
	SPLITTASK *head2 = (SPLITTASK *)malloc(sizeof(SPLITTASK)), *current2 = NULL, *last2 = head2;//创建一个链表，前一个放A，后一个放B
	TASK *current1 = head1;
	while (current1 != NULL)
	{
		//类型A
		current2 = (SPLITTASK*)malloc(sizeof(SPLITTASK));
		current2->num = current1->num;//订单序号
		current2->time = current1->time;//订单时间
		current2->locationx = current1->locationx1; current2->locationy = current1->locationy1;//餐馆位置
		current2->type = 'A';
		current2->reachable = 1;
		current2->next = NULL;
		last2->next = current2;
		last2 = current2;

		//类型B
		current2 = (SPLITTASK*)malloc(sizeof(SPLITTASK));
		current2->num = current1->num;//订单序号
		current2->time = current1->time;//订单时间
		current2->locationx = current1->locationx2; current2->locationy = current1->locationy2;//食客位置
		current2->type = 'B';
		current2->reachable = 0;
		current2->next = NULL;
		last2->next = current2;
		last2 = current2;

		current1 = current1->next;
	}
	return head2->next;
}
