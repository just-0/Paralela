#include <bits/stdc++.h>
#include <mpi.h>

using namespace std;
void input(int my_rank, int comm_sz, double& a, double& b, int& n) {
    if (my_rank == 0) {
        std::cout << "a,b y n -> ";
        std::cin >> a >> b >> n;
    }
    MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
} 

double f(double x) {
    return x * x;
}

double Trapecio(double left_endpt, double right_endpt, int trap_count, double base_len) {
    double approx = (f(left_endpt) + f(right_endpt)) / 2.0;
    for (int i = 1; i <= trap_count - 1; i++) {
        double x = left_endpt + i * base_len;
        approx += f(x);
    }
    return approx * base_len;
} 
int main() {
    int my_rank, comm_sz, n, local_n;
    double a, b, h, _a, _b, _integral, Totalintegral;

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);

    input(my_rank, comm_sz, a, b, n);

    h = (b - a) / n;       
    local_n = n / comm_sz;  

    _a = a + my_rank * local_n * h;
    _b = _a + local_n * h;
    _integral = Trapecio(_a, _b, local_n, h);

    MPI_Reduce(&_integral,& Totalintegral, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (my_rank == 0) {
        cout << "Trapcios -> " << n << endl;
        cout << "Resultado -> " << Totalintegral << endl;
    }

    MPI_Finalize();
    return 0;
}
