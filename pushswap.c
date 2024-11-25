#include "pushswap.h"

const int SEGMENTS = 9;
const int LOOKAHEAD = 60;
const int RECURSIVE_LOOKAHEAD = 0;
/*
int prerun(int *list, int length){
  struct change swap;
  int i;
  int type;
  int steps;

  i = 0;
  type = 1;
  steps = 0;
  while (i <= length) {
    swap.idx = 0;
    if (i > 0 && list[i - 1] > list[i])
      type *= 2;
    if (i < length - 1 && list[i + 1] > list[i + 2])
      type *= 3;

    if (type == 2)
      swap.type = 2;
    if (type == 3)
      swap.type = 3;
    if (type == 6)
      swap.type = 4;

    if (type != 1) {
      transform(list, swap, length);
      steps += 1;
    }
    steps += 1;
    i++;
  }
  return(steps);
}
*/
int lookahead(int *list, int length, struct rots rot, int partition, double current_min, int depth){
  int *tmplist;
  int i;
  int cost;
  int current_depth;
  struct rots goodrot;
  struct rots candidate;
  int current_cost;
  int good_cost;

  if (depth == 0)
    return 0;

  cost = 0;
  current_depth = 0;
  tmplist = malloc(sizeof(int) * (length));
  i = 0;
  while (i < length) {
    tmplist[i] = list[i];
    i++;
  }
  transformrot(tmplist, length, rot, partition);
  current_depth = 1;

  while (current_depth <= depth && partition > 0) {
    i = partition - 1;
    goodrot.type = -1;
    good_cost = INT_MAX;
    while (i >= 0) {
      if (tmplist[i] >= current_min) {
        candidate = check(tmplist, length, partition, i);
        current_cost = candidate.cost;
        if (RECURSIVE_LOOKAHEAD == 1 && depth > 1)
          current_cost += lookahead(tmplist, length, candidate, partition, current_min, depth - 1);
        if (goodrot.type == -1 || current_cost < good_cost) {
          goodrot = candidate;
          good_cost = current_cost;
        }
      }
      i--;
    }
    if (goodrot.type != -1) {
      transformrot(tmplist, length, goodrot, partition);
      cost += goodrot.cost;
      partition -= 1;
    }
    current_depth += 1;
  }
  free(tmplist);
  return cost;
}
struct rots checklookahead(int list, int length, int partition, int i, int good_cost, int current_min)
{
	int	current_cost;
	struct rots	goodrot;

        if (list[i] >= current_min) {
          candidate = check(list, length, partition, i);
          current_cost = candidate.cost;
          current_cost += lookahead(list, length, candidate, partition, current_min, LOOKAHEAD);

          if (goodrot.type == -1 || current_cost < good_cost) {
            goodrot = candidate;
            good_cost = current_cost;
          }
        }
        i--;
	return (goodrot);
}

int rotations(int *list, int segments, int min, int max, int length){
  double size_segment;
  int i;
  int j;
  int round;
  double current_min;
  int partition;
  int current_steps;
  int finished;
  int steps;
  struct change rotation;
  struct rots candidate;
  struct rots rot2;
  struct rots goodrot;
  int current_cost;
  int good_cost;

  steps = 0;
  size_segment = (max - min) / segments;
  rotation.type = 0;
  rotation.idx = length;
  partition = length;

  //steps += prerun(list, length);

  round = segments - 1;
  while (round >= 0) {
    current_min = round * size_segment;
    finished = 0;
    while (finished == 0) {
      i = partition - 1;
      goodrot.type = -1;
      good_cost = INT_MAX;
      while (i >= 0) {
	checklookahead(list, length, partition, i, good_cost, current_min)
      	i--;
      }
     transformrot(list, length, goodrot, partition);
     partition -= 1;
     steps += goodrot.cost + 1;
     /*j = 0;
     while (j < length) {
       printf("%i ", list[j]);
       j++;
     }
     printf("\n\n");
     printf("Rots cost: %i, type: %i, A: %i, B: %i", goodrot.cost, goodrot.type, goodrot.stepsA, goodrot.stepsB);
     printf("\n\n");
     printf("Steps: %i", steps);
     printf("\n\n");*/
     i = 0;
      while (i < partition) {
        if (list[i] > current_min)
          break;
        i++;
      }
      if (i == partition)
        finished = 1;
    }
    round--;
  }
  i = get_next(list, length, 0, INT_MIN);
  rotation.type = 9;
  rotation.idx = 0;
  j = 0;
  while (j < length - i) {
    transform(list, rotation, length);
    j++;
  }/*
  printf("\n\n");
  printf("Steps without i: %i", steps);
  printf("\n\n");*/
  if (i == 0)
    i = length;
  steps += (length - i);
 /* printf("\n\n");
  printf("Steps withoout length: %i", steps);
  printf("\n\n");
  printf("\n\n");
  printf("Length: %i", length);
  printf("\n\n");
  steps += length;
  j = 0;
  while (j < length) {
    printf("%i ", list[j]);
    j++;
  }
  printf("\n\n");
  printf("Steps: %i", steps);
  printf("\n\n");*/
  return (steps);
}

int main(int argc, char **argv) {
  struct change bestchange;
  struct change candidate;
  struct change tmp;
  int *list;
  int partition;
  int length;
  int jump_candidate;
  int jump_best;
  double m_candidate;
  double m_best;
  int d_candidate;
  int d_best;
  double m_actual;
  int l;
  int n;
  int cum;
  int max;
  int min;
  double diff;
  double mean_step;
  int x;
  int stack_step;
  int tol;

  stack_step = 1;
  cum = 0;
  list = NULL;
  if (argc < 2)
    printf("mensaje de error");
  list = malloc(sizeof(int) * (argc - 1));
  length = 0;
  max = INT_MIN;
  min = INT_MAX;
  while (length < argc - 1) {
    list[length] = ft_atoi(argv[length + 1]);
    if (list[length] > max)
      max = list[length];
    if (list[length] < min)
      min = list[length];
    length++;
  }
  diff = (max - min);
  mean_step = diff / length;
/*  bestchange.type = 1;
  bestchange.idx = 0;
  partition = length;
  // partition = 0;
  x = partition;
  tol = 0;
  // while (x <= length) {
  while (bestchange.type != 0) {
    bestchange.type = 0;
    bestchange.idx = 0;
    candidate.type = 2;
    candidate.idx = 2;
    m_actual = fastmeasure(list, length);
    while (candidate.type != 0) {
      m_best =
          measure(bestchange, list, length);
      d_best = distance(bestchange, partition);
      jump_best = jump(bestchange, list, length);
      m_candidate = measure(candidate, list, length);
      d_candidate = distance(candidate, partition);
      jump_candidate = jump(candidate, list, length);
      if (m_candidate < m_actual && partition >= candidate.idx - tol) {
        if (bestchange.type == 0 || d_candidate < d_best || (d_candidate == d_best && m_candidate < m_best)) {
          bestchange = candidate;
        }
      }
      candidate = gen_change(candidate, length, 2, 10, partition);
      // printf("%i", bestchange.type);
    }
    if (bestchange.type == 2 || bestchange.type == 3) {
      bestchange = checkSS(bestchange, list, length, mean_step, diff, m_actual, m_best, partition);
    }
    if (bestchange.type != 0) {
      transform(list, bestchange, length);
      n = distance(bestchange, partition);
      cum += n;
      printf(
          "TYPE %i at INDEX %i WITH POSITION %i COST %i TOTAL %i MEASURE %f\n",
          bestchange.type, bestchange.idx, partition, d_best, cum, m_best);
      partition = bestchange.idx;
    }
  }
  printf("\n\nSECOND PASS\n\n");
  bestchange.type = 1;
  bestchange.idx = 0;
*/
//  cum += partition;

  cum += rotations(list, SEGMENTS, min, max, length);

  /*
  partition = 0;
  tol = 0;

  while (bestchange.type != 0) {
    bestchange.type = 0;
    bestchange.idx = 0;
    candidate.type = 2;
    candidate.idx = 2;
    m_actual = fastmeasure(list, length);
    while (candidate.type != 0) {
      m_best =
          measure(bestchange, list, length);
      d_best = distance(bestchange, partition);
      jump_best = jump(bestchange, list, length);
      m_candidate = measure(candidate, list, length);
      d_candidate = distance(candidate, partition);
      jump_candidate = jump(candidate, list, length);
      if (m_candidate < m_actual && partition <= candidate.idx + tol) {
        if (bestchange.type == 0 || d_candidate < d_best || (d_candidate == d_best && m_candidate <= m_best)) {
          bestchange = candidate;
        }
      }
      candidate = gen_change(candidate, length, 2, 10, partition);
      // printf("%i", bestchange.type);
    }
    if (bestchange.type == 2 || bestchange.type == 3) {
      bestchange = checkSS(bestchange, list, length, mean_step, diff, m_actual, m_best, partition);
    }
    if (bestchange.type != 0) {
      transform(list, bestchange, length);
      n = distance(bestchange, partition);
      cum += n;
      printf(
          "TYPE %i at INDEX %i WITH POSITION %i COST %i TOTAL %i MEASURE %f\n",
          bestchange.type, bestchange.idx, partition, d_best, cum, m_best);
      partition = bestchange.idx;
    }
  }
  printf("\n\nTHIRD PASS\n\n");
  bestchange.type = 1;
  bestchange.idx = 0;

  //cum += length - partition;
  //partition = length;
  tol = 0;

  while (bestchange.type != 0) {
    bestchange.type = 0;
    bestchange.idx = 0;
    candidate.type = 2;
    candidate.idx = 2;
    m_actual = fastmeasure(list, length);
    while (candidate.type != 0) {
      m_best =
          measure(bestchange, list, length);
      d_best = distance(bestchange, partition);
      jump_best = jump(bestchange, list, length);
      m_candidate = measure(candidate, list, length);
      d_candidate = distance(candidate, partition);
      jump_candidate = jump(candidate, list, length);
      if (m_candidate < m_actual && partition >= candidate.idx - tol) {
        if (bestchange.type == 0 || d_candidate < d_best || (d_candidate == d_best && m_candidate <= m_best)) {
          bestchange = candidate;
        }
      }
      candidate = gen_change(candidate, length, 2, 10, partition);
      // printf("%i", bestchange.type);
    }
    if (bestchange.type == 2 || bestchange.type == 3) {
      bestchange = checkSS(bestchange, list, length, mean_step, diff, m_actual, m_best, partition);
    }
    if (bestchange.type != 0) {
      transform(list, bestchange, length);
      n = distance(bestchange, partition);
      cum += n;
      printf(
          "TYPE %i at INDEX %i WITH POSITION %i COST %i TOTAL %i MEASURE %f\n",
          bestchange.type, bestchange.idx, partition, d_best, cum, m_best);
      partition = bestchange.idx;
    }
  }
  printf("\n\nFOURTH PASS\n\n");
  bestchange.type = 1;
  bestchange.idx = 0;

  //cum += partition;
  //partition = 0;
  tol = 0;

  while (bestchange.type != 0) {
    bestchange.type = 0;
    bestchange.idx = 0;
    candidate.type = 2;
    candidate.idx = 2;
    m_actual = fastmeasure(list, length);
    while (candidate.type != 0) {
      m_best =
          measure(bestchange, list, length);
      d_best = distance(bestchange, partition);
      jump_best = jump(bestchange, list, length);
      m_candidate = measure(candidate, list, length);
      d_candidate = distance(candidate, partition);
      jump_candidate = jump(candidate, list, length);
      if (m_candidate < m_actual && partition <= candidate.idx + tol) {
        if (bestchange.type == 0 || d_candidate < d_best || (d_candidate == d_best && m_candidate <= m_best)) {
          bestchange = candidate;
        }
      }
      candidate = gen_change(candidate, length, 2, 10, partition);
      // printf("%i", bestchange.type);
    }
    if (bestchange.type == 2 || bestchange.type == 3) {
      bestchange = checkSS(bestchange, list, length, mean_step, diff, m_actual, m_best, partition);
    }
    if (bestchange.type != 0) {
      transform(list, bestchange, length);
      n = distance(bestchange, partition);
      cum += n;
      printf(
          "TYPE %i at INDEX %i WITH POSITION %i COST %i TOTAL %i MEASURE %f\n",
          bestchange.type, bestchange.idx, partition, d_best, cum, m_best);
      partition = bestchange.idx;
    }
  }
  printf("\n\nFIFTH PASS\n\n");
  bestchange.type = 1;
  bestchange.idx = 0;

  while (bestchange.type != 0) {
    bestchange.type = 0;
    bestchange.idx = 0;
    candidate.type = 2;
    candidate.idx = 2;
    m_actual = fastmeasure(list, length);
    while (candidate.type != 0) {
      m_best =
          measure(bestchange, list, length);
      d_best = distance(bestchange, partition);
      jump_best = jump(bestchange, list, length);
      m_candidate = measure(candidate, list, length);
      d_candidate = distance(candidate, partition);
      jump_candidate = jump(candidate, list, length);
      if (m_candidate < m_actual) {
        if (bestchange.type == 0 || d_candidate < d_best || (d_candidate == d_best && m_candidate <= m_best)) {
          bestchange = candidate;
        }
      }
      candidate = gen_change(candidate, length, 2, 10, partition);
      // printf("%i", bestchange.type);
    }
    if (bestchange.type == 2 || bestchange.type == 3) {
      bestchange = checkSS(bestchange, list, length, mean_step, diff, m_actual, m_best, partition);
    }
    if (bestchange.type != 0) {
      transform(list, bestchange, length);
      n = distance(bestchange, partition);
      cum += n;
      printf(
          "TYPE %i at INDEX %i WITH POSITION %i COST %i TOTAL %i MEASURE %f\n",
          bestchange.type, bestchange.idx, partition, d_best, cum, m_best);
      partition = bestchange.idx;
    }
  }
  */
  /*x += stack_step;*/
  /*if (x > length) x = length;*/
  /*}*/
  // printf("== %i\n ", cum);
  /*
  l = 0;
  while (l < length) {
    printf("%i ", list[l]);
    l++;
  }
  printf("\n");
  */
  free(list);
  return (0);
}
