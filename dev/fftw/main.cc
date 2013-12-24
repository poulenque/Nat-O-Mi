#include <fftw3-mpi.h>
	
int main(int argc, char **argv) {
	const ptrdiff_t N0 = ..., N1 = ...;
	fftw_plan plan;
	fftw_complex *data;
	ptrdiff_t alloc_local, local_n0, local_0_start, i, j;
 
	MPI_Init(&argc, &argv);
	fftw_mpi_init();
 
	/* get local data size and allocate */
	alloc_local = fftw_mpi_local_size_2d(N0, N1, MPI_COMM_WORLD,
										  &local_n0, &local_0_start);
	data = fftw_alloc_complex(alloc_local);
 
	 create plan for in-place forward DFT 
	plan = fftw_mpi_plan_dft_2d(N0, N1, data, data, MPI_COMM_WORLD,
								 FFTW_FORWARD, FFTW_ESTIMATE);
 
	/* initialize data to some function my_function(x,y) */
	for (i = 0; i < local_n0; ++i) for (j = 0; j < N1; ++j)
		data[i*N1 + j] = my_function(local_0_start + i, j);
 
	/* compute transforms, in-place, as many times as desired */
	fftw_execute(plan);
 
	fftw_destroy_plan(plan);
 
	MPI_Finalize();
}