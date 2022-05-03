#include<stdlib.h>
#include<stdio.h>


struct date
{
	long long * timedate;
	long h;
	int w;
	struct date* pl;
	struct date* pr;
};
typedef struct date DATE;
typedef struct date* PDATE;

PDATE setnew(PDATE p0, int w, long h, long long * num)//p0为左邻
{
	PDATE p = (PDATE)malloc(sizeof(DATE));
	p->timedate = num;
	p->pl = p0;
	p->pr = NULL;
	p0->pr = p;
	p->h = h;
	p->w = w;
	return p;
}

void output(long long* p, long n)
{
	while (n--)
		printf("%lld\n", *(++p));
}

int main()
{
	long long myclock;
	long n;
	int w;
	long h;
	PDATE p = NULL, pt = NULL;
	//set leftp
	PDATE left = (PDATE)malloc(sizeof(DATE));
	left->timedate = NULL;
	left->pl = NULL;
	left->pr = NULL;
	left->h = 1000000;
	left->w = 0;

	p = left;
	pt = left;
	scanf("%d", &n);
	long long* timedate = new long long[n + 1];
	for (long i = 0; i<n; i++)
	{
		//cin>>w>>h;
		scanf("%d%d", &w, &h);
		p = setnew(p, w, h, timedate + i + 1);
		if (pt->h>h)
			pt = p;
	}
	PDATE right = setnew(p, 0, 1000000, NULL);
	p = pt;
	myclock = 0;

	while (p->pl->h != p->pr->h)
	{
		*(p->timedate) = myclock + p->w;
		//计算时间并删除合并
		if (p->pl->h>p->pr->h)
		{
			myclock += (p->pr->h - p->h)*p->w;
			p->pr->w += p->w;
			p->pl->pr = p->pr;
			p->pr->pl = p->pl;
			pt = p;
			p = p->pr;
			delete pt;
		}
		else if (p->pl->h<p->pr->h)
		{
			myclock += (p->pl->h - p->h)*p->w;
			p->pl->w += p->w;
			p->pl->pr = p->pr;
			p->pr->pl = p->pl;
			pt = p;
			p = p->pl;
			delete pt;
		}
		//移至下一进水点
		if (p->pl->h>p->h&&p->pr->h>p->h)
			continue;
		else if (p->pl->h<p->pr->h)//左移
		{
			while (p->h>p->pl->h)
				p = p->pl;
		}
		else //右移
		{
			while (p->h>p->pr->h)
				p = p->pr;
		}
	}
	myclock += p->w;
	*(p->timedate) = myclock;
	output(timedate, n);

}

