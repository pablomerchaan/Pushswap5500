#include "pushswap.h"


int	*transformRRA(int *list, int idx)
{
	int	tmp;
	int	c;

	c = 0;
	tmp = list[0];
	while (c < idx - 1)
	{
		list[c] = list[c + 1];
		c++;
	}
	list[c] = tmp;
	return (list);
}
int	*transformRRB(int *list, int idx, int length)
{
	int	tmp;
	int	c;

	tmp = list[length - 1];
	c = length - 1;
	while (c > idx)
	{
		list[c] = list[c - 1];
		c--;
	}
	list[idx] = tmp;
	return (list);
}

int	*transformRRR(int *list, int idx, int length)
{
	int	*r;
	r = transformRRA(list, idx);
	r = transformRRB(list, idx, length);
	return (r);
}
