#include "pushswap.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	unsigned long long	result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\r' || str[i] == '\t'
	|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > __LONG_LONG_MAX__)
			return (sign == -1 ? 0 : -1);
		result *= 10;
		result += (str[i] - '0');
		i++;
	}
	return (result * sign);
}

int *convert(struct change prev, struct change actual) {
  int c;
  int *moves;
// TODO asegurarse de como inicializar moves y porque, para despues alocarlo
  // correctamente.
  if (prev.idx <= actual.idx) {
    c = actual.idx - prev.idx;
    moves = malloc(sizeof(int) * (c + 2));
    if (!moves)
      return (NULL);
    moves[c] = actual.type;
    c--;
    while (c <= 0) {
      moves[c] = 0;
      c--;
    }
  } else {
    c = prev.idx - actual.idx;
    moves = malloc(sizeof(int) * (c + 1));
    moves[c] = actual.type;
    c--;
    while (c <= 0) {
      moves[c] = 1;
      c--;
    }
  }
  return (moves);
}

int get_next(int *list, int length, int partition, int num)
{
  int c;
  int next;
  int current_next;
  if (partition == length)
    return (length - 1);
  c = partition;
  next = partition;
  current_next = INT_MAX;
  while (c < length)
  {
    if (list[c] - num < current_next && list[c] - num > 0)
    {
      current_next = list[c] - num;
      next = c;
    }
    c++;
  }
  c--;
  if (current_next == INT_MAX)
  {
    while (c != partition)
    {
      if (list[c] < list[next])
        next = c;
      c--;
    }
  }
    return (next);
}

int getmin(int A, int B)
{
  if (A < B)
    return(A);
  else
    return(B);
}

struct rots  minrot(struct rots rot1, struct rots rot2)
{
  if (rot1.cost < rot2.cost)
    return(rot1);
  return (rot2);
}
