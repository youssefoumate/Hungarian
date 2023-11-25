#include<iostream>
#include<stdlib.h>
#include<vector>
#include <algorithm>
#include <limits.h>
#include "helpers.h"
using namespace std;

void solve(int (&Cost)[4][4], const int N, const int M, const int MODE, int *assignment_index){
  bool done;
  std::cout<<"********Step1*************\n";
  //step 1: minimum element in each row is subtracted from all the elements in that row
  for(int i=0; i<N; i++){
    int min_cost = INT_MAX;
    for (int j = 0; j < M; j++) {
      if (Cost[i][j] < min_cost){
          min_cost = Cost[i][j];
      }
    }
    for (int j=0; j<M; j++){
      Cost[i][j] = Cost[i][j] - min_cost;
    }

  }
  if (print_check_valid_assignment(Cost, N, M, assignment_index)) return;

  std::cout<<"********Step2*************\n";
  //step2: minimum element in each column is subtracted from all the elements in that column
  for(int i=0; i<M; i++){
    int min_cost = INT_MAX;
    for (int j = 0; j < N; j++) {
      if (Cost[j][i] < min_cost){
          min_cost = Cost[j][i];
      }
    }
    for (int j=0; j<N; j++){
      Cost[j][i] = Cost[j][i] - min_cost;
    }
  }
  if (print_check_valid_assignment(Cost, N, M, assignment_index)) return;
}

int main() {

  srand(time(0));
  int N = 4;
  int M = 4;

  int *assignment_index;
  assignment_index = new int[N];
  //initialize with -1
  for(int i = 0; i <N; i++)
      assignment_index[i] = -1;
  int Cost[4][4] = {
          3, 7, 3, 11,
          8, 5, 6, 5,
          2, 4, 6, 3,
          1, 10, 7, 2,
          };
  std::cout<<"\n********Input*************\n";
  print_matrix(Cost, N, M);
  print_assignment(N, assignment_index);
  const int MODE = 0;
  solve(Cost, N, M, MODE, assignment_index);

  return 0;
}