#include <bits/stdc++.h>
#include <mpi.h>
using namespace std;



int main(int argc, char* argv[]) {
    vector<int> v(1000, 1);
    MPI_Init(&argc, &argv);

    int my_rank, comm_sz;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); 
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); 

    int size = v.size();
    int local_n = size / comm_sz; 

    int local_sum = 0, total_sum = 0;


    for (int i = my_rank * local_n; i < (my_rank + 1) * local_n; i++) {
        local_sum += v[i];
    }


    MPI_Reduce(&local_sum, &total_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        cout << "Resultado -> " << total_sum << endl;
    }

    MPI_Finalize(); 
    return 0;
}
