#include<iostream>
#include<stdlib.h>
#include<vector>
#include <algorithm>
#include <limits.h>
#include "helpers.h"
using namespace std;

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

void solve(int (&Cost)[4][4], const int N, const int M, int *assignment_index, vector<tuple<int, int> > starred_zeros_coords, vector<int> marked_columns, vector<tuple<int, int> > primed_zeros_coords, vector<int> marked_rows, vector<tuple<int, int> > path){
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
	if (print_and_check_valid_assignment(Cost, N, M, assignment_index, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path)) return;

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
	if (print_and_check_valid_assignment(Cost, N, M, assignment_index, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path)) return;

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
	if (print_and_check_valid_assignment(Cost, N, M, assignment_index, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path)) return;
	tuple<int, int> marked_zero_coords;
	int marked_zero_i;
	int marked_zero_j;
	int counter = 0;
	while(true){
		counter++;
		if (counter > 3){
			return;
		}
		cout<<"********Step4*************\n";
		//Cover all columns containing a (starred) zero.
		for (tuple<int, int> el : starred_zeros_coords) {
			marked_columns.push_back(get<1>(el));
		}
		//Find a non-covered zero and prime it. (If all zeroes are covered, skip to step 5.)
		cout << "start" << endl;
		jump:
		marked_zero_coords = find_non_marked_zero(Cost, N, M, marked_columns, marked_rows);
		marked_zero_i = get<0>(marked_zero_coords);
		marked_zero_j = get<1>(marked_zero_coords);
		if ((marked_zero_i != -1) && (marked_zero_j != -1)){
			cout << "if" << endl;
			primed_zeros_coords.push_back(tuple<int, int>(marked_zero_i, marked_zero_j));
			//If the zero is on the same row as a starred zero, cover the corresponding row, 
			// and uncover the column of the starred zero.
			bool starred_zero_exist = false;
			for (tuple<int, int> el : starred_zeros_coords) {
				if(marked_zero_i==get<0>(el)){
					//remove marked column of the starred zero
					marked_columns.erase(remove(marked_columns.begin(), marked_columns.end(), get<1>(el)), marked_columns.end());
					starred_zero_exist = true;
					break;
				}
			}
			if (starred_zero_exist){
				marked_rows.push_back(marked_zero_i);
				print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);	
				goto jump;
			}
			else{
				cout << "else" << endl;
				//the non-covered zero has no assigned zero on its row.
				int nm_zero_i = marked_zero_i;
				int nm_zero_j = marked_zero_j;
				tuple<int, int> non_covered_zero = tuple<int, int>(nm_zero_i,nm_zero_j);
				path.push_back(non_covered_zero);
				int starred_zero_i;
				int starred_zero_j;
				while(true){
					//Find a starred zero on the corresponding column
					bool starred_zero_exist = false;
					for (tuple<int, int> starred_zero : starred_zeros_coords) {
						if(nm_zero_j==get<1>(starred_zero)){
							starred_zero_exist = true;
							starred_zero_i = get<0>(starred_zero);
							starred_zero_j = get<1>(starred_zero);
							path.push_back(tuple<int, int>(starred_zero_i, starred_zero_j));
						}
					}
					if (starred_zero_exist){
						//Find a primed zero on the corresponding row (there should always be one).
						for (tuple<int, int> primed_zero : primed_zeros_coords) {
							if(starred_zero_i==get<0>(primed_zero)){
								starred_zero_exist = true;
								path.push_back(tuple<int, int>(get<0>(primed_zero), get<1>(primed_zero)));
								nm_zero_j = get<1>(primed_zero);
							}
						}
					}
					else{
						break;
					}
				}
				//For all zeros encountered during the path, star primed zeros and unstar starred zeros.
				tuple<int, int> starred_zero_coords;
				tuple<int, int> primed_zero_coords;
				for (tuple<int, int> el: path){
					for (int index = 0; index < starred_zeros_coords.size(); ++index){
						starred_zero_coords = starred_zeros_coords[index];
						if (get<0>(el) == get<0>(starred_zero_coords) && get<1>(el) == get<1>(starred_zero_coords)){
							starred_zeros_coords[index] = tuple<int, int> (-1,-1);
						}
					}
				}
				for (tuple<int, int> el: path){
					for (int index = 0; index < primed_zeros_coords.size(); ++index){
						primed_zero_coords = primed_zeros_coords[index];
						if (get<0>(el) == get<0>(primed_zero_coords) && get<1>(el) == get<1>(primed_zero_coords)){
							starred_zeros_coords.push_back(primed_zero_coords);
						}
					}
				}
				primed_zeros_coords.clear();
				marked_rows.clear();
				marked_columns.clear();
				print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);	
			}
		}
	}//TODO:implement step5
}

int main() {

	int N = 4;
	int M = 4;

	int *assignment_index;
	vector<tuple<int, int> > starred_zeros_coords;
	vector<tuple<int, int> > primed_zeros_coords;
	vector<int> marked_columns;
	vector<int> marked_rows;
	vector<tuple<int, int> > path;
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
	print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
	print_assignment(N, assignment_index);
	solve(Cost, N, M, assignment_index, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);

	return 0;
}