#include<iostream>

bool check_valid_assignment(int* assignment_index, int N){
  bool done = true;
  for( int i = 0; i < N; ++i){
      if (assignment_index[i] == -1){
        done = false;
      }
  }
  return done;
}
void print_matrix(int (&Cost)[4][4], int N, int M){
  for( int i = 0; i < N; ++i){
    for( int j = 0; j < M; ++j) {
      std::cout<<Cost[i][j]<<'\t';
    }
    std::cout<<'\n';
  }
}
void print_assignment(int N, int* assignment_index){
  std::cout<<"********Assignment********\n";
  for( int i = 0; i < N; ++i){
      std::cout<<assignment_index[i]<<'\t';
  }
  std::cout<<'\n';
}
void assign_tasks(int (&Cost)[4][4], int N, int M, int* assignment_index){
  //check if assignment is possibles
  std::vector<int> crossed_cols;
  for(int i=0; i<N; i++){
    for (int j = 0; j < M; j++){
      if (!(std::count(crossed_cols.begin(), crossed_cols.end(), j))){
        if (Cost[i][j] == 0){
            assignment_index[i] = j;
            crossed_cols.push_back(j);
            break;
        }
      }
    }
  }
}
bool print_check_valid_assignment(int (&Cost)[4][4], int N, int M, int* assignment_index){
  assign_tasks(Cost, N, M, assignment_index);
  print_matrix(Cost, N, M);
  print_assignment(N, assignment_index);
  return check_valid_assignment(assignment_index, N);
}