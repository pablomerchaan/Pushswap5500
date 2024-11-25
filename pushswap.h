#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>

enum type_of_change
{
	PA, PB, SA, SB, SS, RA, RB, RR, RRA, RRB, RRR
};

struct change
{
	enum type_of_change type;
	int idx;
};

struct rots
{
  int type;
  int cost;
  int idx;
  int stepsA;
  int stepsB;
};

int *transformrot(int *list, int length, struct rots rot, int partition);
struct rots check(int *list, int length, int partition, int idx);
int get_next(int *list, int length, int partition, int num);
int	ft_atoi(const char *str);
int	sq(int c);
int	*convert(struct change prev, struct change actual);
int	*transform(int *list, struct change actual, int length);
int	*transformSA(int *list, int idx);
int	*transformSB(int *list, int idx);
int	*transformSS(int *list, int idx);
int	*transformRA(int *list, int idx);
int	*transformRB(int *list, int idx, int length);
int	*transformRR(int *list, int idx, int length);
int	*transformRRA(int *list, int idx);
int	*transformRRB(int *list, int idx, int length);
int	*transformRRR(int *list, int idx, int length);
int rotations(int *list, int segments, int min, int max, int length);
struct rots  minrot(struct rots rot1, struct rots rot2);
