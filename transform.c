#include "pushswap.h"

int	*transform(int *list, struct change actual, int length)
{
	if (actual.type == 2)
		list = transformSA(list, actual.idx);
	else if (actual.type == 3)
		list = transformSB(list, actual.idx);
	else if (actual.type == 4)
		list = transformSS(list, actual.idx);
	else if (actual.type == 5)
		list = transformRA(list, actual.idx);
	else if (actual.type == 6)
		list = transformRB(list, actual.idx, length);
	else if (actual.type == 7)
		list = transformRR(list, actual.idx, length);
	else if (actual.type == 8)
		list = transformRRA(list, actual.idx);
	else if (actual.type == 9)
		list = transformRRB(list, actual.idx, length);
	else if (actual.type == 10)
		list = transformRRR(list, actual.idx, length);
	return (list);
}
