#include<iostream>
#include<stdlib.h>
#include<vector>
#include <algorithm>
#include <limits.h>
#include "helpers.h"
using namespace std;

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

void solve(int (&Cost)[4][4], const int N, const int M, vector<tuple<int, int> > starred_zeros_coords, vector<int> marked_columns, vector<tuple<int, int> > primed_zeros_coords, vector<int> marked_rows, vector<tuple<int, int> > path){
	bool done;
	int min_uncoverd;
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
	print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);

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
	print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);

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
	print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
	tuple<int, int> marked_zero_coords;
	int marked_zero_i;
	int marked_zero_j;
	int counter = 0;
	while(true){
		while(true){
			cout<<"********Step4*************\n";
			cout << "Cover all columns containing a starred zero." << endl;
			for (tuple<int, int> el : starred_zeros_coords) {
				if (get<1>(el) != -1){
					marked_columns.push_back(get<1>(el));
				}
			}
			print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
			jump:
			cout << "Find a non-covered zero and prime it. (If all zeroes are covered, skip to step 5.)" << endl;
			marked_zero_coords = find_non_marked_zero(Cost, N, M, marked_columns, marked_rows);
			marked_zero_i = get<0>(marked_zero_coords);
			marked_zero_j = get<1>(marked_zero_coords);
			if ((marked_zero_i == -1) && (marked_zero_j == -1)){
				cout << "All zeros are coverd...skip to step 5" << endl;
				break;
			}
			primed_zeros_coords.push_back(tuple<int, int>(marked_zero_i, marked_zero_j));
			print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
			cout << "If the zero is on the same row as a starred zero, cover the corresponding row," << endl;
			cout << "and uncover the column of the starred zero." << endl;
			bool starred_zero_exist = false;
			for (tuple<int, int> el : starred_zeros_coords) {
				if(marked_zero_i==get<0>(el)){
					cout << "starred zero exist." << endl;
					cout << "uncover the column of the starred zero." << endl;
					marked_columns.erase(remove(marked_columns.begin(), marked_columns.end(), get<1>(el)), marked_columns.end());
					starred_zero_exist = true;
					break;
				}
			}
			print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
			if (starred_zero_exist){
				cout << "cover the corresponding row." << endl;
				marked_rows.push_back(marked_zero_i);
				print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);	
				goto jump;
			}
			else{
				cout << "the non-covered zero has no assigned zero on its row." << endl;
				int nm_zero_i = marked_zero_i;
				int nm_zero_j = marked_zero_j;
				tuple<int, int> non_covered_zero = tuple<int, int>(nm_zero_i,nm_zero_j);
				path.push_back(non_covered_zero);
				print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
				int starred_zero_i;
				int starred_zero_j;
				while(true){
					cout<<"Find a starred zero on the corresponding column" << endl;
					bool starred_zero_exist = false;
					for (tuple<int, int> starred_zero : starred_zeros_coords) {
						if(nm_zero_j==get<1>(starred_zero)){
							starred_zero_exist = true;
							starred_zero_i = get<0>(starred_zero);
							starred_zero_j = get<1>(starred_zero);
							path.push_back(tuple<int, int>(starred_zero_i, starred_zero_j));
						}
					}
					print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
					if (starred_zero_exist){
						cout << "Find a primed zero on the corresponding row (there should always be one)." << endl;
						for (tuple<int, int> primed_zero : primed_zeros_coords) {
							if(starred_zero_i==get<0>(primed_zero)){
								starred_zero_exist = true;
								path.push_back(tuple<int, int>(get<0>(primed_zero), get<1>(primed_zero)));
								nm_zero_j = get<1>(primed_zero);
							}
						}
						print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
					}
					else{
						break;
					}
				}
				cout << "For all zeros encountered during the path, star primed zeros and unstar starred zeros." << endl;
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
						if ((get<0>(el) == get<0>(primed_zero_coords)) && (get<1>(el) == get<1>(primed_zero_coords))){
							starred_zeros_coords.push_back(primed_zero_coords);
						}
					}
				}
				print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
				cout << "Unprime all primed zeroes and uncover all lines." << endl;
				primed_zeros_coords.clear();
				marked_rows.clear();
				marked_columns.clear();
				path.clear();
				print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
			}
		}	
		cout<<"********Step5*************\n";
		min_uncoverd = find_min_uncoverd_value(Cost, N, M, marked_columns, marked_rows);
		if (min_uncoverd == INT_MAX){
			cout << "No uncoverd minimum value was found" << endl;
		}else{
			cout << "Find the lowest uncovered value: "<< min_uncoverd << endl;
			cout << "Subtract " << min_uncoverd << " from every unmarked element and add it to every element covered by two lines." <<endl;
			unmarked_sub_min_marked_add_min(Cost, N, M, marked_columns, marked_rows, min_uncoverd);
		}
		print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
		marked_columns = vector_unique(marked_columns);
		marked_rows = vector_unique(marked_rows);
		cout << "number of lines: " << marked_columns.size() + marked_rows.size() << endl;
		cout << "marked columns: ";
		for (int mc : marked_columns){
			cout << mc << ",";
		}
		cout << endl;
		cout << "marked rows: ";
		for (int mr : marked_rows){
			cout << mr << ",";
		}
		cout << endl;
		cout << "min (#people, #assignments): " << min(N,M) << endl;
		if (check_covered_zeros(Cost, N, M, marked_columns, marked_rows)){
			if ((marked_columns.size() + marked_rows.size()) == min(N,M)){
				cout << "the minimum number of lines used to cover all the 0s is equal to min(number of people, number of assignments)" <<endl;
				cout << "Done." << endl;
				break;
			}
		}
	}
}

int main() {

	int N = 4;
	int M = 4;

	vector<tuple<int, int> > starred_zeros_coords;
	vector<tuple<int, int> > primed_zeros_coords;
	vector<int> marked_columns;
	vector<int> marked_rows;
	vector<tuple<int, int> > path;
	//initialize with -1
	int Cost[4][4] = {
			3, 7, 3, 11,
			8, 5, 6, 5,
			2, 4, 6, 3,
			1, 10, 7, 8,
			};
	/*int Cost[4][4] = {
			82,	83,	69,	92,
			77,	37,	49,	92,
			11,	69,	5,	86,
			8,	9,	98,	23,
			};*/
	/*int Cost[3][3] = {
			47,	73,	29,
			83,	20,	48,
			74,	88,	58,
			};*/
	cout<<"\n********Input*************\n";
	print_matrix(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);
	solve(Cost, N, M, starred_zeros_coords, marked_columns, primed_zeros_coords, marked_rows, path);

	return 0;
}