#include "pushswap.h"
int	*transformSA(int *list, int idx)
{
	int	tmp;

	tmp = list[idx - 1];
	list[idx - 1] = list[idx - 2];
	list[idx - 2] = tmp;
	return (list);
}

int	*transformSB(int *list, int idx)
{
	int	tmp;

	tmp = list[idx];
	list[idx] = list[idx + 1];
	list[idx + 1] = tmp;
	return (list);
}

int	*transformSS(int *list, int idx)
{
	int	tmp;

	tmp = list[idx - 1];
	list[idx - 1] = list[idx - 2];
	list[idx - 2] = tmp;
	tmp = list[idx];
	list[idx] = list[idx + 1];
	list[idx + 1] = tmp;
	return (list);
}
