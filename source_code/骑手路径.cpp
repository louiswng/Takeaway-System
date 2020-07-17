#include"Takeaway.h"
int success(struct Rider **Rider,int num,int time,struct PrintResult *PrintResult,struct Order *statement,struct Order *ticket)
{
	int count,count1;
	struct SplitTask *temp,*temp2,*re,*temp3,*temp4;
	struct Order *order1=statement,*order2=ticket;
	
	for(count=0;count<num;count++) 
	{
		temp=Rider[count]->next;
		for(count1=0;count1<Rider[count]->task;count1++)
			temp=temp->next;
		while(temp!=NULL)
		{
			re=temp;
			if(Rider[count]->locationx%2==0)
			{
				if(Rider[count]->task!=0&&((temp->locationx>=Rider[count]->locationx&&temp->locationx<=Rider[count]->next->locationx)||(temp->locationx<=Rider[count]->locationx&&temp->locationx>=Rider[count]->next->locationx))&&((temp->locationy>=Rider[count]->locationy-1&&temp->locationy<=Rider[count]->next->locationy)||(temp->locationy<=Rider[count]->locationy+1&&temp->locationy>=Rider[count]->next->locationy)))
				{
					if(temp->type=='A')
					{
						for(temp4=Rider[count]->next;temp4->next!=temp;temp4=temp4->next);
						temp3=temp;
						temp4->next=temp->next;
						temp3->next=Rider[count]->next;
						Rider[count]->next=temp3;
						temp=temp4->next;
					}
				}
				else if(Rider[count]->task!=0)
				{
					for(temp2=Rider[count]->next;temp2!=temp;temp2=temp2->next)
					{
						if(((temp->locationx>=temp2->locationx&&temp->locationx<=temp2->next->locationx)||(temp->locationx<=temp2->locationx&&temp->locationx>=temp2->next->locationx))&&((temp->locationy>=temp2->locationy-1&&temp->locationy<=temp2->next->locationy)||(temp->locationy<=temp2->locationy+1&&temp->locationy>=temp2->next->locationy)))
						{
							if(temp->type=='B')
								for(temp4=Rider[count]->next;temp4!=temp2->next;temp4=temp4->next)
								{
									if(temp4->num==temp->num)
									{
										for(temp4=Rider[count]->next;temp4->next!=temp;temp4=temp4->next);
										temp3=temp;
										temp4->next=temp->next;
										temp3->next=temp2->next;
										temp2->next=temp3;
										temp=temp4->next;
										goto exit;
									}
								}
							else
							{
								for(temp4=Rider[count]->next;temp4->next!=temp;temp4=temp4->next);
								temp3=temp;
								temp4->next=temp->next;
								temp3->next=temp2->next;
								temp2->next=temp3;
								temp=temp4->next;
								break;
							}
						}
					}
				}
			}
			else
			{
				if(Rider[count]->task!=0&&((temp->locationx>=Rider[count]->locationx-1&&temp->locationx<=Rider[count]->next->locationx)||(temp->locationx<=Rider[count]->locationx+1&&temp->locationx>=Rider[count]->next->locationx))&&((temp->locationy>=Rider[count]->locationy&&temp->locationy<=Rider[count]->next->locationy)||(temp->locationy<=Rider[count]->locationy&&temp->locationy>=Rider[count]->next->locationy)))
				{
					if(temp->type=='A')
					{
						for(temp4=Rider[count]->next;temp4->next!=temp;temp4=temp4->next);
						temp3=temp;
						temp4->next=temp->next;
						temp3->next=Rider[count]->next;
						Rider[count]->next=temp3;
						temp=temp4->next;
					}
				}
				else if(Rider[count]->task!=0)
				{
					for(temp2=Rider[count]->next;temp2!=temp;temp2=temp2->next)
					{
						if(((temp->locationx>=temp2->locationx-1&&temp->locationx<=temp2->next->locationx)||(temp->locationx<=temp2->locationx+1&&temp->locationx>=temp2->next->locationx))&&((temp->locationy>=temp2->locationy&&temp->locationy<=temp2->next->locationy)||(temp->locationy<=temp2->locationy&&temp->locationy>=temp2->next->locationy)))
						{
							if(temp->type=='B')
								for(temp4=Rider[count]->next;temp4!=temp2->next;temp4=temp4->next)
								{
									if(temp4->num==temp->num)
									{
										for(temp4=Rider[count]->next;temp4->next!=temp;temp4=temp4->next);
										temp3=temp;
										temp4->next=temp->next;
										temp3->next=temp2->next;
										temp2->next=temp3;
										temp=temp4->next;
										goto exit;
									}
								}
							else
							{
								for(temp4=Rider[count]->next;temp4->next!=temp;temp4=temp4->next);
								temp3=temp;
								temp4->next=temp->next;
								temp3->next=temp2->next;
								temp2->next=temp3;
								temp=temp4->next;
								break;
							}
						}
					}
				}
			}
			exit:;
			Rider[count]->task++;
			if(re==temp)
			{
				if(temp!=Rider[count]->next)
				{
					for(temp2=Rider[count]->next;temp2->next!=temp;temp2=temp2->next);
					Rider[count]->time+=(fabs(temp2->locationx-temp2->next->locationx)+fabs(temp2->locationy-temp2->next->locationy))/2+1;
				}
				else
				{
					temp2=Rider[count]->next;
					Rider[count]->time+=(fabs(temp2->locationx-Rider[count]->locationx)+fabs(temp2->locationy-Rider[count]->locationy))/2+1;
				}
				temp=temp->next;
			}
		}
		if(Rider[count]->locationx%2==0)
		{
			while(Rider[count]->next!=NULL&&(Rider[count]->next->locationx==Rider[count]->locationx)&&(Rider[count]->next->locationy-1==Rider[count]->locationy||Rider[count]->next->locationy+1==Rider[count]->locationy))
			{
				if(Rider[count]->next->type=='A')
				{
					for(temp=Rider[count]->next->next;temp->num!=Rider[count]->next->num;temp=temp->next);
					temp->reachable=1;
				}
				temp=Rider[count]->next;
				Rider[count]->next=temp->next;
				if(Rider[count]->former==NULL)
				{
					temp->next=Rider[count]->former;
					Rider[count]->former=temp;
					if(Rider[count]->former->type=='B')
					{
						if(time-Rider[count]->former->time>BANKRUPTCY)
							return -1;
						else if(time-Rider[count]->former->time>TIMEOUT)
						{
							order2->next=(Order *)malloc(sizeof(struct Order));
							order2=order2->next;
							order2->num=Rider[count]->former->num;
							order2->next=NULL;
							PrintResult->money-=FINE;
							PrintResult->timeoutCnt++;
						}
						else
						{
							order1->next=(Order *)malloc(sizeof(struct Order));
							order1=order1->next;
							order1->num=Rider[count]->former->num;
							order1->next=NULL;
							PrintResult->money+=SALARY;
						}
						PrintResult->compeleteCnt++;
					}
				}
				else
				{
					for(temp2=Rider[count]->former;temp2->next!=NULL;temp2=temp2->next);
					temp->next=temp2->next;
					temp2->next=temp;
					if(temp2->next->type=='B')
					{
						if(time-temp2->next->time>BANKRUPTCY)
							return -1;
						else if(time-temp2->next->time>TIMEOUT)
						{
							order2->next=(Order *)malloc(sizeof(struct Order));
							order2=order2->next;
							order2->num=temp2->next->num;
							order2->next=NULL;
							PrintResult->money-=FINE;
							PrintResult->timeoutCnt++;
						}
						else
						{
							order1->next=(Order *)malloc(sizeof(struct Order));
							order1=order1->next;
							order1->num=temp2->next->num;
							order1->next=NULL;
							PrintResult->money+=SALARY;
						}
						PrintResult->compeleteCnt++;
					}
				}
				Rider[count]->task--;
			}
		}
		else
		{
			while(Rider[count]->next!=NULL&&(Rider[count]->next->locationy==Rider[count]->locationy)&&(Rider[count]->next->locationx-1==Rider[count]->locationx||Rider[count]->next->locationx+1==Rider[count]->locationx))
			{
				if(Rider[count]->next->type=='A')
				{
					for(temp=Rider[count]->next->next;temp->num!=Rider[count]->next->num;temp=temp->next);
					temp->reachable=1;
				}
				temp=Rider[count]->next;
				Rider[count]->next=temp->next;
				if(Rider[count]->former==NULL)
				{
					temp->next=Rider[count]->former;
					Rider[count]->former=temp;
					if(Rider[count]->former->type=='B')
					{
						if(time-Rider[count]->former->time>BANKRUPTCY)
							return -1;
						else if(time-Rider[count]->former->time>TIMEOUT)
						{
							order2->next=(Order *)malloc(sizeof(struct Order));
							order2=order2->next;
							order2->num=Rider[count]->former->num;
							order2->next=NULL;
							PrintResult->money-=FINE;
							PrintResult->timeoutCnt++;
						}
						else
						{
							order1->next=(Order *)malloc(sizeof(struct Order));
							order1=order1->next;
							order1->num=Rider[count]->former->num;
							order1->next=NULL;
							PrintResult->money+=SALARY;
						}
						PrintResult->compeleteCnt++;
					}
				}
				else
				{
					for(temp2=Rider[count]->former;temp2->next!=NULL;temp2=temp2->next);
					temp->next=temp2->next;
					temp2->next=temp;
					if(temp2->next->type=='B')
					{
						if(time-temp2->next->time>BANKRUPTCY)
							return -1;
						else if(time-temp2->next->time>TIMEOUT)
						{
							order2->next=(Order *)malloc(sizeof(struct Order));
							order2=order2->next;
							order2->num=temp2->next->num;
							order2->next=NULL;
							PrintResult->money-=FINE;
							PrintResult->timeoutCnt++;
						}
						else
						{
							order1->next=(Order *)malloc(sizeof(struct Order));
							order1=order1->next;
							order1->num=temp2->next->num;
							order1->next=NULL;
							PrintResult->money+=SALARY;
						}
						PrintResult->compeleteCnt++;
					}
				}
				Rider[count]->task--;
			}
		}
	}
}
void moveto(struct Rider *Rider,int x,int y)
{
	if(Rider->locationx%2==0)
	{
		if(x>Rider->locationx+2)
			Rider->locationx+=2;
		else if(x<Rider->locationx-2)
			Rider->locationx-=2;
		else if(x>Rider->locationx)
		{
			Rider->locationx++;
			Rider->locationy+=(y<Rider->locationy)?-1:1;
		}
		else if(x<Rider->locationx)
		{
			Rider->locationx--;
			Rider->locationy+=(y<Rider->locationy)?-1:1;
		}
		else if(Rider->locationx==XLIMIT)
		{
			Rider->locationx--;
			Rider->locationy+=(y<Rider->locationy)?-1:1;
		}
		else
		{
			Rider->locationx++;
			Rider->locationy+=(y<Rider->locationy)?-1:1;
		}
	}
	else
	{
		if(y>Rider->locationy+2)
			Rider->locationy+=2;
		else if(y<Rider->locationy-2)
			Rider->locationy-=2;
		else if(y<Rider->locationy)
		{
			Rider->locationy--;
			Rider->locationx+=(x<Rider->locationx)?-1:1;
		}
		else if(y>Rider->locationy)
		{
			Rider->locationy++;
			Rider->locationx+=(x<Rider->locationx)?-1:1;
		}
		else if(Rider->locationy==YLIMIT)
		{
			Rider->locationy--;
			Rider->locationx+=(x<Rider->locationx)?-1:1;
		}
		else
		{
			Rider->locationy++;
			Rider->locationx+=(x<Rider->locationx)?-1:1;
		}
	}
}
int path(struct Rider **Rider,int num,int time,struct PrintResult *PrintResult,struct Order *statement,struct Order *ticket)
{
	int count,count1;
	struct SplitTask *temp,*temp2,*temp3,*temp4,*re;
	struct Order *order1=statement,*order2=ticket;
	
	for(count=0;count<num;count++)
	{
		if(Rider[count]->next==NULL)
		{
			Rider[count]->time=0;
			if(num<3&&(Rider[count]->locationx!=8||Rider[count]->locationy!=7))
				moveto(Rider[count],8,7);
			else if(count%3==0&&(Rider[count]->locationx!=8||Rider[count]->locationy!=7))
				moveto(Rider[count],8,7);
			else if(count%3==1&&(Rider[count]->locationx!=4||Rider[count]->locationy!=7))
				moveto(Rider[count],4,7);
			else if(count%3==2&&(Rider[count]->locationx!=12||Rider[count]->locationy!=7))
				moveto(Rider[count],12,7);
			continue;
		}
		if(Rider[count]->locationx%2==0)
		{
			if(Rider[count]->next->locationx>Rider[count]->locationx+2)
				Rider[count]->locationx+=2;
			else if(Rider[count]->next->locationx<Rider[count]->locationx-2)
				Rider[count]->locationx-=2;
			else if(Rider[count]->next->locationx>Rider[count]->locationx)
			{
				Rider[count]->locationx++;
				Rider[count]->locationy+=(Rider[count]->next->locationy<Rider[count]->locationy)?-1:1;
			}
			else if(Rider[count]->next->locationx<Rider[count]->locationx)
			{
				Rider[count]->locationx--;
				Rider[count]->locationy+=(Rider[count]->next->locationy<Rider[count]->locationy)?-1:1;
			}
			else if(fabs(Rider[count]->next->locationy-Rider[count]->locationy==1))
			{
				Rider[count]->locationx+=(Rider[count]->next->locationx<Rider[count]->locationx)?-2:2;
			}
			else if(Rider[count]->locationx==XLIMIT)
			{
				Rider[count]->locationx--;
				Rider[count]->locationy+=(Rider[count]->next->locationy<Rider[count]->locationy)?-1:1;
			}
			else
			{
				Rider[count]->locationx++;
				Rider[count]->locationy+=(Rider[count]->next->locationy<Rider[count]->locationy)?-1:1;
			}
		}
		else
		{
			if(Rider[count]->next->locationy>Rider[count]->locationy+2)
				Rider[count]->locationy+=2;
			else if(Rider[count]->next->locationy<Rider[count]->locationy-2)
				Rider[count]->locationy-=2;
			else if(Rider[count]->next->locationy<Rider[count]->locationy)
			{
				Rider[count]->locationy--;
				Rider[count]->locationx+=(Rider[count]->next->locationx<Rider[count]->locationx)?-1:1;
			}
			else if(Rider[count]->next->locationy>Rider[count]->locationy)
			{
				Rider[count]->locationy++;
				Rider[count]->locationx+=(Rider[count]->next->locationx<Rider[count]->locationx)?-1:1;
			}
			else if(fabs(Rider[count]->next->locationx-Rider[count]->locationx==1))
			{
				Rider[count]->locationy+=(Rider[count]->next->locationy<Rider[count]->locationy)?-2:2;
			}
			else if(Rider[count]->locationy==YLIMIT)
			{
				Rider[count]->locationy--;
				Rider[count]->locationx+=(Rider[count]->next->locationx<Rider[count]->locationx)?-1:1;
			}
			else
			{
				Rider[count]->locationy++;
				Rider[count]->locationx+=(Rider[count]->next->locationx<Rider[count]->locationx)?-1:1;
			}
		}
		Rider[count]->former=NULL;
		if(Rider[count]->locationx%2==0)
		{
			while(Rider[count]->next!=NULL&&(Rider[count]->next->locationx==Rider[count]->locationx)&&(Rider[count]->next->locationy-1==Rider[count]->locationy||Rider[count]->next->locationy+1==Rider[count]->locationy))
			{
				if(Rider[count]->next->type=='A')
				{
					for(temp=Rider[count]->next->next;temp->num!=Rider[count]->next->num;temp=temp->next);
					temp->reachable=1;
				}
				temp=Rider[count]->next;
				Rider[count]->next=temp->next;
				temp->next=Rider[count]->former;
				Rider[count]->former=temp;
				if(Rider[count]->former->type=='B')
				{
					if(time-Rider[count]->former->time>BANKRUPTCY)
						return -1;
					else if(time-Rider[count]->former->time>TIMEOUT)
					{
						order2->next=(Order *)malloc(sizeof(struct Order));
						order2=order2->next;
						order2->num=Rider[count]->former->num;
						order2->next=NULL;
						PrintResult->money-=FINE;
						PrintResult->timeoutCnt++;
					}
					else
					{
						order1->next=(Order *)malloc(sizeof(struct Order));
						order1=order1->next;
						order1->num=Rider[count]->former->num;
						order1->next=NULL;
						PrintResult->money+=SALARY;
					}
					PrintResult->compeleteCnt++;
				}
				Rider[count]->task--;
			}
		}
		else
		{
			while(Rider[count]->next!=NULL&&(Rider[count]->next->locationy==Rider[count]->locationy)&&(Rider[count]->next->locationx-1==Rider[count]->locationx||Rider[count]->next->locationx+1==Rider[count]->locationx))
			{
				if(Rider[count]->next->type=='A')
				{
					for(temp=Rider[count]->next->next;temp->num!=Rider[count]->next->num;temp=temp->next);
					temp->reachable=1;
				}
				temp=Rider[count]->next;
				Rider[count]->next=temp->next;
				temp->next=Rider[count]->former;
				Rider[count]->former=temp;
				if(Rider[count]->former->type=='B')
				{
					if(time-Rider[count]->former->time>BANKRUPTCY)
						return -1;
					else if(time-Rider[count]->former->time>TIMEOUT)
					{
						order2->next=(Order *)malloc(sizeof(struct Order));
						order2=order2->next;
						order2->num=Rider[count]->former->num;
						order2->next=NULL;
						PrintResult->money-=FINE;
						PrintResult->timeoutCnt++;
					}
					else
					{
						order1->next=(Order *)malloc(sizeof(struct Order));
						order1=order1->next;
						order1->num=Rider[count]->former->num;
						order1->next=NULL;
						PrintResult->money+=SALARY;
					}
					PrintResult->compeleteCnt++;
				}
				Rider[count]->task--;
			}
		}
		Rider[count]->time--;
	}
}
