#include "pushswap.h"

struct s_minmax	oneargument(char **argv, int *list)
{
	int	c;
	struct s_minmax	m;

	c = 0;
	while (argv[1][c] != '\0')
	{
		if(argv[1][c] == ' ')
			c++;
		if (ft_atoi(&argv[1][c]) == '\0')
		{
			printf("Error");
			m.max = 0;
			m.min = 0;
			c = 10000;
		}
		list[c] = ft_atoi(&argv[1][c]);
		if (list[c] > m.max)
			m.max = list[c];
		if (list[c] < m.min)
			m.min = list[c];
		c++;
	}
	return (m);
}

int	howmany(char **argv)
{
	int	c;
	int	r;

	r = 0;
	c = 0;
	while (argv[1][c] != '\0')
	{
		if (argv[1][c] == ' ')
			r++;
		c++;
	}
	r++;
	return (r);
}
