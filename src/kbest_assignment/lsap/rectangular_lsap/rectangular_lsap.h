#ifndef RECTANGULAR_LSAP_H
#define RECTANGULAR_LSAP_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

int solve_rectangular_linear_sum_assignment(intptr_t nr, intptr_t nc, double* input_cost,
                                            double_t* u, double_t* v, int64_t* col4row);

#ifdef __cplusplus
}
#endif

#endif
