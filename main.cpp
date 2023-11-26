#include<iostream>
#include<stdlib.h>
#include<vector>
#include <algorithm>
#include <limits.h>
#include "helpers.h"
using namespace std;

void solve(int (&Cost)[4][4], const int N, const int M, const int MODE, int *assignment_index, vector<tuple<int, int> > starred_zeros_coords, vector<int> marked_columns){
  bool done;
  cout<<"********Step1*************\n";
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
  if (print_and_check_valid_assignment(Cost, N, M, assignment_index, starred_zeros_coords, marked_columns)) return;

  cout<<"********Step2*************\n";
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
  if (print_and_check_valid_assignment(Cost, N, M, assignment_index, starred_zeros_coords, marked_columns)) return;
  cout<<"********Step3*************\n";
  //step3: Assignment of arbitary zeros, they can't be in the same row or column.
  tuple<int, int> coord; 
  for(int i=0; i<N; i++){
    for (int j = 0; j < M; j++){
      coord = tuple<int, int>(i,j);
      if ((Cost[i][j] == 0) && (!inlist_row_or_col(coord, starred_zeros_coords))){
        starred_zeros_coords.push_back(coord);
      }
    }
  }
  if (print_and_check_valid_assignment(Cost, N, M, assignment_index, starred_zeros_coords, marked_columns)) return;
  cout<<"********Step4-1*************\n";
  //Cover all columns containing a (starred) zero.
  for (tuple<int, int> el : starred_zeros_coords) {
      marked_columns.push_back(get<1>(el));
  }
  print_matrix(Cost, N, M, starred_zeros_coords, marked_columns);
  cout<<"********Step4-2*************\n";
  //TODO: Find a non-covered zero and prime it. (If all zeroes are covered, skip to step 5.)

}

int main() {

  srand(time(0));
  int N = 4;
  int M = 4;

  int *assignment_index;
  vector<tuple<int, int> > starred_zeros_coords;
  vector<int> marked_columns;
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
  cout<<"\n********Input*************\n";
  print_matrix(Cost, N, M, starred_zeros_coords, marked_columns);
  print_assignment(N, assignment_index);
  const int MODE = 0;
  solve(Cost, N, M, MODE, assignment_index, starred_zeros_coords, marked_columns);

  return 0;
}