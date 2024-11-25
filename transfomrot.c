#include "pushswap.h"


int * do_rotations(int *list, int length, struct rots rot, int partition, int type_1, int type_2, int comp_1, int comp_2) {
    {
  int c;
  struct change rotation;
      rotation.type = type_1;
      rotation.idx = partition;
      c = 0;
      while (c < comp_1)
      {
        transform(list, rotation, length);
        c++;
      }
      rotation.type = type_2;
      rotation.idx = partition;
      c = 0;
      while (c < comp_2)
      {
        transform(list, rotation, length);
        c++;
      }
    }
    return (list);
}


int *transformrot(int *list, int length, struct rots rot, int partition)
{
  int c;
  struct change rotation;

  if (rot.type == 0)
  {
    if (rot.stepsA == 0)
      do_rotations(list, length, rot, partition, 7, 6, rot.cost - rot.stepsB, rot.stepsB);
    else
      do_rotations(list, length, rot, partition, 7, 5, rot.cost - rot.stepsA, rot.stepsA);
  }
  if (rot.type == 1)
  {
    if (rot.stepsA == 0)
      do_rotations(list, length, rot, partition, 10, 9, rot.cost - rot.stepsB, rot.stepsB);
    else
      do_rotations(list, length, rot, partition, 10, 8, rot.cost - rot.stepsA, rot.stepsA);
  }
  if (rot.type == 2)
    do_rotations(list, length, rot, partition, 5, 9,  rot.stepsA, rot.stepsB);
  if (rot.type == 3)
    do_rotations(list, length, rot, partition, 8, 6,  rot.stepsA, rot.stepsB);
  return(list);
}
