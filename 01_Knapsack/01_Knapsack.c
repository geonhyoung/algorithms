/*
 * File Name: 01_Knapsack.c
 * Creation Date: Thu Oct 25, 2018 11:17PM
 * Description:
 * Author: jogeonhyeong-ui-MacBook-Pro
 *
 * Last modified: Fri Oct 26, 2018 12:29AM
 */

#include "01_Knapsack.h"

#include <stdio.h>
#include <stdlib.h>
#include "01_Knapsack.h"

int Largest(PW pair[], double w[], int t, int h, int i, double m) {
  /* Do binary search */
  /* returns max index u in S(i-1) s.t w + wi <= m */
  int mid = 0;
  int u = t - 1;

  while (t <= h) {
    mid = (t + h) / 2;
    if (pair[mid].w + w[i] <= m) {
      t = mid + 1;
      u = mid;
    } else
      h = mid - 1;
  }

  /* if u = t - 1 means w[i] > m */
  return u;
}

void TraceBack(double p[], double w[], PW pair[], int b[], int x[], double m,
               int n) {
  /* m: profit
   * n: # of items */
  int i;

  /* last element in S(i-1). */
  double px = pair[b[n] - 1].p;
  double wx = pair[b[n] - 1].w;

  /* find Largest index such that pair[u] + w[n] <= m. */
  int u = Largest(pair, w, b[n - 1], b[n] - 1, n, m);

  /* its profit and weight */
  double py = pair[u].p;
  double wy = pair[u].w;

  PW temp;

  if (px > py + p[n] || u < b[n - 1]) {
    /* if profit of last elemnt in S(i-1) is bigger than
     * profit of Largest element
     * or
     * u < b[n-1] means that w[n] is bigger than m.
     */
    x[n] = 0;
    temp.p = px;
    temp.w = wx;

    printf("%lf %lf ", px, wx);
  } else {
    /* include x[n] to optimal solution */
    x[n] = 1;
    temp.p = py;
    temp.w = wy;

    printf("%lf %lf ", py + p[n], wy + w[n]);
  }

  for (i = n - 1; i >= 1; i--) {
    /* binary search opt tuple in S(i-1) */
    double p1 = temp.p;
    double w1 = temp.w;

    int found = BinarySearch(pair, b[i - 1], b[i], temp.p, temp.w);

    if (found > 0) {
      /* not optimal solution */
      temp.p = p1;
      temp.w = w1;
      x[i] = 0;
    } else {
      /* optimal solution */
      x[i] = 1;
      temp.p = p1 - p[i];
      temp.w = w1 - w[i];
    }
  }
}

void DKnapsack(double p[], double w[], int x[], int n, double m) {
  int size = 10;
  /* pair is S */
  PW *pair = (PW *)malloc(sizeof(PW) * size);
  int *b = (int *)malloc(sizeof(int) * (n + 1));
  int next;

  /* Start and End of S_0 */
  int t = 1;
  int h = 1;

  /* initialize */
  b[0] = 1;
  pair[1].p = 0.0;
  pair[1].w = 0.0;

  /* next free spot in pair[] */
  b[1] = 2;
  next = 2;

  int i, j;

  int u;

  for (i = 1; i <= n - 1; i++) {
    /* Generate S_i */
    int k = t;
    u = Largest(pair, w, t, h, i, m);

    /* Generate S_i_1 and merge */
    for (j = t; j <= u; j++) {
      double pp = pair[j].p + p[i];
      double ww = pair[j].w + w[i];

      /* (pp, ww) is the next element in S_i_1.
       * p_(i+1), w_(i+1)
       */
      while ((k <= h) && (pair[k].w < ww)) {
        /* Domination Rule X */
        pair[next].p = pair[k].p;
        pair[next].w = pair[k].w;
        next++;
        k++;

        if (next >= size) {
          size = size << 1;
          pair = (PW *)realloc(pair, sizeof(PW) * size);

          if (pair == NULL) {
            printf("Memory Overflow\n");
            exit(-1);
          }
        }
      } /* end while */

      if ((k <= h) && (pair[k].w == ww)) {
        if (pp < pair[k].p) /* Domination Rule */
          pp = pair[k].p;
        k++;
      }
      if (pp > pair[next - 1].p) {
        pair[next].p = pp;
        pair[next].w = ww;
        next++;

        if (next >= size) {
          size = size << 1;
          pair = (PW *)realloc(pair, sizeof(PW) * size);

          if (pair == NULL) {
            printf("Memory Overflow\n");
            exit(-1);
          }
        }
      }
      while ((k <= h) && (pair[k].p <= pair[next - 1].p)) k++;
    } /* end for j */

    /* Merge in remaining terms from S_(i-1) */
    while (k <= h) {
      pair[next].p = pair[k].p;
      pair[next].w = pair[k].w;
      next++;
      k++;

      if (next >= size) {
        size = size << 1;
        pair = (PW *)realloc(pair, sizeof(PW) * size);

        if (pair == NULL) {
          printf("Memory Overflow\n");
          exit(-1);
        }
      }
    } /* end while */

    /* Initialize for S_(i+1) */
    t = h + 1;
    h = next - 1;
    b[i + 1] = next;
  }

  TraceBack(p, w, pair, b, x, m, n);

  free(pair);
  free(b);
}

int BinarySearch(PW pair[], int start, int end, double p, double w) {
  /* search pair element which has profit p and weight w */
  int mid = 0;

  while (start <= end) {
    mid = (start + end) / 2;
    if (pair[mid].p == p && pair[mid].w == w)
      return mid; /* found */
    else if (pair[mid].p < p)
      start = mid + 1;
    else if (pair[mid].p > p)
      end = mid - 1;
    else
      return -1; /* pair[mid].p = p but pair[mid].w != w */
  }

  return -1;
}

int main() {
  int T;
  int TestNum;
  int i;

  scanf("%d", &T);

  for (TestNum = 0; TestNum < T; TestNum++) {
    int n;
    double m;

    scanf("%d %lf", &n, &m);

    double *profit = (double *)malloc(sizeof(double) * (n + 1));
    double *weight = (double *)malloc(sizeof(double) * (n + 1));

    int *x = (int *)malloc(sizeof(int) * (n + 1));

    for (i = 1; i <= n; i++) scanf("%lf", &profit[i]);
    for (i = 1; i <= n; i++) scanf("%lf", &weight[i]);

    DKnapsack(profit, weight, x, n, m);

    for (i = 1; i <= n; i++) printf("%d ", x[i]);
    printf("\n");

    free(profit);
    free(weight);
    free(x);
  }

  return 0;
}
