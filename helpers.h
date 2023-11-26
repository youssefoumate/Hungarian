#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

void print_matrix(int (&Cost)[4][4], int N, int M, std::vector<std::tuple<int, int>> starred_zeros_coords, std::vector<int> marked_columns);
void print_assignment(int N, int* assignment_index);
bool print_and_check_valid_assignment(int (&Cost)[4][4], int N, int M, int* assignment_index, std::vector<std::tuple<int, int>> starred_zeros_coords, std::vector<int> marked_columns);
bool inlist_row_or_col(std::tuple<int, int> coord, std::vector<std::tuple<int, int>> starred_zeros_coords);

#endif