/**
 * @file    CUDASimpleVerletList.h
 * @date    29/set/2010
 * @author  lorenzo
 *
 */

#ifndef CUDASIMPLEVERLETLIST_H_
#define CUDASIMPLEVERLETLIST_H_

#include "CUDABaseList.h"
#include "../CUDAUtils.h"

/**
 * @brief CUDA implementation of a {@link VerletList Verlet list}.
 */

class CUDASimpleVerletList: public CUDABaseList{
protected:
	int _max_neigh = 0;
	int _N_cells_side[3];
	int _max_N_per_cell = 0;
	size_t _vec_size = 0;
	bool _auto_optimisation = true;
	c_number _max_density_multiplier = 1;
	int _N_cells, _old_N_cells;

	c_number _verlet_skin = 0.;
	c_number _sqr_verlet_skin = 0.;
	c_number _sqr_rverlet = 0.;

	int *_d_cells = nullptr;
	int *_d_counters_cells = nullptr;
	int *_d_number_neighs_no_doubles = nullptr;
	bool *_d_cell_overflow = nullptr;

	CUDA_kernel_cfg _cells_kernel_cfg;

	virtual void _init_cells();

public:
	int *d_matrix_neighs = nullptr;
	int *d_number_neighs = nullptr;
	edge_bond *d_edge_list = nullptr;
	int N_edges;

	CUDASimpleVerletList();
	virtual ~CUDASimpleVerletList();

	void init(int N, c_number rcut, CUDABox*h_cuda_box, CUDABox*d_cuda_box);
	void update(c_number4 *poss, c_number4 *list_poss, LR_bonds *bonds);
	void clean();

	void get_settings(input_file &inp);
};

#endif /* CUDASIMPLEVERLETLIST_H_ */
