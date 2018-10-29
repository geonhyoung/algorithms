/*
 * File Name: 01_Knapsack.h
 * Creation Date: Thu Oct 25, 2018 11:10PM
 * Description:
 * Author: jogeonhyeong-ui-MacBook-Pro
 *
 * Last modified: Fri Oct 26, 2018 12:35AM
 */

#ifndef _01_KNAPSACK_H
#define _01_KNAPSACK_H

typedef struct pw {
  double p, w;
} PW;

void TraceBack(double p[], double w[], PW pair[], int b[], int x[], double m,
                int n);

void DKnapsack(double p[], double w[], int x[], int n, double m);

int Largest(PW pair[], double w[], int t, int h, int i, double m);

int BinarySearch(PW pair[], int start, int end, double p, double w);

#endif /* _01_KNAPSACK_H */
