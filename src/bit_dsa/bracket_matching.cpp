#include<stdio.h>

int main()
{
	int flag = 0;
	char a[1000] = { 0 };
	char* p;
	p = &a[0];
	char temp;
	temp = getchar();
	*p = temp;
	while (temp != '\n')
	{
		switch (temp)
		{
		case '(':
		{
			p++;
			*p = temp;
			break;
		}
		case ')':
		{
			if (*p != '(')
			{
				printf("Match false!\n");
				return 0;
			}
			*p = 0;
			p--;
			break;
		}
		case '[':
		{
			p++;
			*p = temp;
			break;
		}
		case']':
		{
			if (*p != '[')
			{
				printf("Match false!\n");
				return 0;
			}
			*p = 0;
			p--;
			break;
		}


		}//endswiych
		temp = getchar();
	}//end whilw
	printf("Match succeed!\n");
	return 0;
}

