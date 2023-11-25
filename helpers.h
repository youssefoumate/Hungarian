#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

void print_matrix(int (&Cost)[4][4], int N, int M);
void print_assignment(int N, int* assignment_index);
bool print_check_valid_assignment(int (&Cost)[4][4], int N, int M, int* assignment_index);

#endif