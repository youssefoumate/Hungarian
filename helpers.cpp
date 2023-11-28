#include<iostream>
#include<vector>
using namespace std;

bool check_valid_assignment(int* assignment_index, int N){
  bool done = true;
  for( int i = 0; i < N; ++i){
      if (assignment_index[i] == -1){
        done = false;
      }
  }
  return done;
}

bool inlist_row_or_col(tuple<int, int> coord, vector<tuple<int, int> > starred_zeros_coords){
    for (tuple<int, int> el : starred_zeros_coords) {
        if ((get<0>(coord) == get<0>(el)) || (get<1>(coord) == get<1>(el))){
            return true;
        }
    }
    return false;
}

bool inlist_row_and_col(tuple<int, int> coord, vector<tuple<int, int> > list){
    for (tuple<int, int> el : list) {
        if ((get<0>(coord) == get<0>(el)) && (get<1>(coord) == get<1>(el))){
            return true;
        }
    }
    return false;
}

void print_matrix(int (&Cost)[4][4], int N, int M, vector<tuple<int, int> > starred_zeros_coords, vector<int> marked_columns, vector<tuple<int, int> > primed_zeros_coords, vector<int> marked_rows, vector<tuple<int, int> > path){
    tuple<int, int> coord;
    bool marked;
    for( int j = 0; j < M; ++j) {
        marked = false;
        for (int el : marked_columns){
            if (el == j){
                marked = true;
            }
        }
        if (marked){
            cout<<"x"<<'\t';
        }
        else{
            cout<<"-"<<'\t';
        }
    }
    cout<<'\n';
    for( int i = 0; i < N; ++i){
        bool is_row_marked = false;
        for( int j = 0; j < M; ++j) {
            coord = tuple<int, int>(i,j);
            cout<<Cost[i][j];
            if (inlist_row_and_col(coord, path)){
                cout<<"p";
            }
            if (inlist_row_and_col(coord, starred_zeros_coords)){
                cout<<"*";
            }
            else if(inlist_row_and_col(coord, primed_zeros_coords)){
                cout<<"'";
            }
            cout<<'\t';
        }
        for (int el : marked_rows) {
			if(i==el){
				is_row_marked = true;
            }
        }
        if (is_row_marked){
            cout<<"x";
        }
        cout<<'\n';
    }
}
void print_assignment(int N, int* assignment_index){
  cout<<"********Assignment********\n";
  for( int i = 0; i < N; ++i){
      cout<<assignment_index[i]<<'\t';
  }
  cout<<'\n';
}
void assign_tasks(int (&Cost)[4][4], int N, int M, int* assignment_index){
  //check if assignment is possibles
  vector<int> crossed_cols;
  for(int i=0; i<N; i++){
    for (int j = 0; j < M; j++){
      if (!(count(crossed_cols.begin(), crossed_cols.end(), j))){
        if (Cost[i][j] == 0){
            assignment_index[i] = j;
            crossed_cols.push_back(j);
            break;
        }
      }
    }
  }
}
bool print_and_check_valid_assignment(int (&Cost)[4][4], int N, int M, int* assignment_index, vector<tuple<int, int> > starred_zeros_coords, vector<int> marked_columns, vector<tuple<int, int> > primed_zeros_coords, vector<int> marked_rows, vector<tuple<int, int> > path){
  assign_tasks(Cost, N, M, assignment_index);
  print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
  print_assignment(N, assignment_index);
  return check_valid_assignment(assignment_index, N);
}