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
    cout<<"********Cost********\n";
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
    cout<<"*******************\n";
}

bool check_covered_zeros(int (&Cost)[4][4], int N, int M, vector<int> marked_columns, vector<int> marked_rows){
	bool col_marked_zero;
	bool row_marked_zero;
	for(int i=0; i<N; i++){
		for (int j = 0; j < M; j++){
			col_marked_zero = false;
			row_marked_zero = false;
			if (Cost[i][j] == 0){
				for (int el : marked_columns){
					if (el == j){
						col_marked_zero = true;
					}
				}
				for (int el : marked_rows){
					if (el == i){
						row_marked_zero = true;
					}
				}
				if ((!col_marked_zero) && (!row_marked_zero)){
					return false;
				}
			}
		}
	}
	return true;
}

vector<int> vector_unique(vector<int> vec){
	sort(vec.begin(), vec.end());
	auto it = unique(vec.begin(), vec.end());
  	vec.resize(distance(vec.begin(), it));
	return vec;
}

void unmarked_sub_min_marked_add_min(int (&Cost)[4][4], int N, int M, vector<int> marked_columns, vector<int> marked_rows, int min){
	bool col_marked_zero;
	bool row_marked_zero;
	for(int i=0; i<N; i++){
		for (int j = 0; j < M; j++){
			col_marked_zero = false;
			row_marked_zero = false;
			for (int el : marked_columns){
				if (el == j){
					col_marked_zero = true;
				}
			}
			for (int el : marked_rows){
				if (el == i){
					row_marked_zero = true;
				}
			}
			if ((!col_marked_zero) && (!row_marked_zero)){
				Cost[i][j] -= min;
			}
			if ((col_marked_zero) && (row_marked_zero)){
				Cost[i][j] += min;
			}
		}
	}
}

int find_min_uncoverd_value(int (&Cost)[4][4], int N, int M, vector<int> marked_columns, vector<int> marked_rows){
	bool col_marked_zero;
	bool row_marked_zero;
	int min = INT_MAX;
	for(int i=0; i<N; i++){
		for (int j = 0; j < M; j++){
			col_marked_zero = false;
			row_marked_zero = false;
			for (int el : marked_columns){
				if (el == j){
					col_marked_zero = true;
				}
			}
			for (int el : marked_rows){
				if (el == i){
					row_marked_zero = true;
				}
			}
			if ((!col_marked_zero) && (!row_marked_zero)){
				if (Cost[i][j] < min){
					min = Cost[i][j];
				}
			}
		}
	}
	return min;
}

tuple<int, int> find_non_marked_zero(int (&Cost)[4][4], int N, int M, vector<int> marked_columns, vector<int> marked_rows){
	bool col_marked_zero;
	bool row_marked_zero;
	for(int i=0; i<N; i++){
		for (int j = 0; j < M; j++){
			col_marked_zero = false;
			row_marked_zero = false;
			if (Cost[i][j]==0){
				for (int el : marked_columns){
				if (el == j){
					col_marked_zero = true;
				}
				}
				for (int el : marked_rows){
					if (el == i){
						row_marked_zero = true;
					}
				}
				if ((!col_marked_zero) && (!row_marked_zero)){
					return tuple<int, int>(i,j);
				}
			}
		}
	}
	return tuple<int, int>(-1,-1);
}