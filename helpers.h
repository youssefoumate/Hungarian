#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
using namespace std;

void print_matrix(int (&Cost)[4][4], int N, int M, vector<tuple<int, int>> starred_zeros_coords, vector<int> marked_columns, vector<tuple<int, int> > primed_zeros_coords, vector<int> marked_rows, vector<tuple<int, int> > path);
bool inlist_row_or_col(tuple<int, int> coord, vector<tuple<int, int>> starred_zeros_coords);
tuple<int, int> find_non_marked_zero(int (&Cost)[4][4], int N, int M, vector<int> marked_columns, vector<int> marked_rows);
int find_min_uncoverd_value(int (&Cost)[4][4], int N, int M, vector<int> marked_columns, vector<int> marked_rows);
void unmarked_sub_min_marked_add_min(int (&Cost)[4][4], int N, int M, vector<int> marked_columns, vector<int> marked_rows, int min);
vector<int> vector_unique(vector<int> vec);
bool check_covered_zeros(int (&Cost)[4][4], int N, int M, vector<int> marked_columns, vector<int> marked_rows);

#endif