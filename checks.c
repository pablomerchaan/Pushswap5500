#include "pushswap.h"

struct rots check_rrarrb(int *list, int length, int partition, int idx)
{
  struct rots rot;
  int stepsA;
  int stepsB;
  int next;

  next = get_next(list, length, partition, list[idx]);
  stepsA = idx + 1;
  stepsB = length - next;
  rot.type = 1;
  if (stepsA < stepsB)
    rot.cost = stepsB;
  else
    rot.cost = stepsA;
  rot.stepsA = rot.cost - stepsB;
  rot.stepsB = rot.cost - stepsA;
  return (rot);
}

struct rots check_rarb(int *list, int length, int partition, int idx)
{
  struct rots rot;
  int stepsA;
  int stepsB;
  int next;

  next = get_next(list, length, partition, list[idx]);
  stepsA = partition - idx - 1;
  stepsB = next - partition;
  if (stepsB < 0)
    stepsB = 0;
  rot.type = 0;
  if (stepsA < stepsB)
    rot.cost = stepsB;
  else
    rot.cost = stepsA;
  rot.stepsA = rot.cost - stepsB;
  rot.stepsB = rot.cost - stepsA;
  return (rot);
}

struct rots check_rrarb(int *list, int length, int partition, int idx)
{
  struct rots rot;
  int stepsA;
  int stepsB;
  int next;

  next = get_next(list, length, partition, list[idx]);
  stepsA = idx + 1;
  stepsB = next - partition;
  rot.type = 3;
  rot.cost = stepsA + stepsB;
  rot.stepsA = stepsA;
  rot.stepsB = stepsB;
  return (rot);
}

struct rots check_rarrb(int *list, int length, int partition, int idx)
{
  struct rots rot;
  int stepsA;
  int stepsB;
  int next;

  next = get_next(list, length, partition, list[idx]);
  stepsA = partition - idx - 1;
  stepsB = length - next;
  rot.type = 2;
  rot.cost = stepsA + stepsB;
  rot.stepsA = stepsA;
  rot.stepsB = stepsB;
  return (rot);
}

struct rots check(int *list, int length, int partition, int idx)
{
  struct rots current_min;
  struct rots candidate;

  current_min = check_rarb(list, length, partition, idx);
  candidate = check_rrarrb(list, length, partition, idx);
  if (candidate.cost < current_min.cost)
    current_min = candidate;
  candidate = check_rarrb(list, length, partition, idx);
  if (candidate.cost < current_min.cost)
    current_min = candidate;
  candidate = check_rrarb(list, length, partition, idx);
  if (candidate.cost < current_min.cost)
    current_min = candidate;
  return(current_min);
}

