#include "pushswap.h"


int	*transformRA(int *list, int idx)
{
	int	tmp;
	int	c;

	tmp = list[idx - 1];
	c = idx - 1;
	while (c > 0)
	{
		list[c] = list[c - 1];
		c--;
	}
	list[0] = tmp;
	return (list);
}

int	*transformRB(int *list, int idx, int length)
{
	int	tmp;
	int	c;

	tmp = list[idx];
	c = idx;
	while (c + 1 < length)
	{
		list[c] = list[c + 1];
		c++;
	}
	list[c] = tmp;
	return (list);
}

int	*transformRR(int *list, int idx, int length)
{
	int	tmp;
	int	c;

  if (idx > 1) {
    tmp = list[idx - 1];
    c = idx - 1;
    while (c != 0)
    {
      list[c] = list[c - 1];
      c--;
    }
    list[0] = tmp;
  }
  if (length - idx > 1) {
    tmp = list[idx];
    c = idx;
    while (c + 1 != length)
    {
      list[c] = list[c + 1];
      c++;
    }
    list[c] = tmp;
  }
	return (list);
}
