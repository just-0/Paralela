#include<bits/stdc++.h>
#include <mpi.h>

using namespace std;

using namespace std;

void Read_n(int& n, int& local_n, int my_rank, int comm_sz, MPI_Comm comm) {
    if (my_rank == 0) {
        cout << "What's the order of the vectors?" << endl;
        cin >> n;
        if (n <= 0 || n % comm_sz != 0) {
            cerr << "Error: n must be > 0 and evenly divisible by comm_sz" << endl;
            MPI_Abort(comm, 1);
        }
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, comm);
    local_n = n / comm_sz;
}

void Read_vector(vector<double>& local_a, int local_n, int n, const char vec_name[], int my_rank, MPI_Comm comm) {
    vector<double> a;
    if (my_rank == 0) {
        a.resize(n);
        cout << "Enter the vector " << vec_name << endl;
        for (int i = 0; i < n; i++) cin >> a[i];
    }
    MPI_Scatter(a.data(), local_n, MPI_DOUBLE, local_a.data(), local_n, MPI_DOUBLE, 0, comm);
}


void Parallel_vector_sum(const vector<double>& local_x, const vector<double>& local_y, vector<double>& local_z, int local_n) {
    for (int i = 0; i < local_n; i++) {
        local_z[i] = local_x[i] + local_y[i];
    }
}

int main() {
    int n, local_n, comm_sz, my_rank;
    MPI_Comm comm;
    
    MPI_Init(nullptr, nullptr);
    comm = MPI_COMM_WORLD;
    MPI_Comm_size(comm, &comm_sz);
    MPI_Comm_rank(comm, &my_rank);

    Read_n(n, local_n, my_rank, comm_sz, comm);
    
    vector<double> local_x(local_n);
    vector<double> local_y(local_n);
    vector<double> local_z(local_n);

    Read_vector(local_x, local_n, n, "x", my_rank, comm);
    

    Read_vector(local_y, local_n, n, "y", my_rank, comm);
    

    Parallel_vector_sum(local_x, local_y, local_z, local_n);
    

    MPI_Finalize();
    return 0;
}
