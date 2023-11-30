#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
using namespace std;

void print_matrix(int (&Cost)[4][4], int N, int M, vector<tuple<int, int>> starred_zeros_coords, vector<int> marked_columns, vector<tuple<int, int> > primed_zeros_coords, vector<int> marked_rows, vector<tuple<int, int> > path);
bool inlist_row_or_col(tuple<int, int> coord, vector<tuple<int, int>> starred_zeros_coords);

#endif