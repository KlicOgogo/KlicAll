#include "mpi.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <iostream>
#include <vector>


double f(double x) {
    return x-1;
}

std::array<uint32_t, 2> parse_params(int argc, char** argv) {
    if (argc == 5 && std::string(argv[1]) == "-n" && std::string(argv[3]) == "-r") {
        return {static_cast<uint32_t>(atoi(argv[2])), static_cast<uint32_t>(atoi(argv[4]))};
    } else if (argc == 3 && (std::string(argv[1]) == "-n" || std::string(argv[1]) == "-r")) {
        if (std::string(argv[1]) == "-n") {
            return {static_cast<uint32_t>(atoi(argv[2])), 10000};
        } else {
            return {100000000, static_cast<uint32_t>(atoi(argv[2]))};
        }
    }
    return {100000000, 10000};
}

int main(int argc, char** argv) {
    constexpr uint32_t kMainProcessID = 0;
    constexpr uint32_t kCalculateTag = 1;
    constexpr uint32_t kFinishTag = 2;

    const double a = 0;
    const double b = 3;

    const auto params = parse_params(argc, argv);
    const uint32_t r = params[1];
    const uint32_t n = params[0];
    const double h = (b - a) / n;

    MPI_Init(&argc, &argv);
    MPI_Status status;
    status.MPI_TAG = 0;
    int rank;
    int p;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);

    std::vector<double> interval(2);

    if (rank == kMainProcessID) {
        double intergal_process_part = 0;
        double integral = 0;
        for (double i = a; std::abs(i - b) > 1e-5; i += r * h) {
            MPI_Recv(&intergal_process_part, 1, MPI_DOUBLE, MPI_ANY_SOURCE, kCalculateTag, MPI_COMM_WORLD, &status);
            integral += intergal_process_part;
            interval[0] = i;
            interval[1] = std::min(b, i + r * h);
            MPI_Send(interval.data(), interval.size(), MPI_DOUBLE, status.MPI_SOURCE, kCalculateTag, MPI_COMM_WORLD);
        }
        for (int i = 1; i < p; ++i) {
            MPI_Recv(&intergal_process_part, 1, MPI_DOUBLE, MPI_ANY_SOURCE, kCalculateTag, MPI_COMM_WORLD, &status);
            integral += intergal_process_part;
            MPI_Send(interval.data(), interval.size(), MPI_DOUBLE, status.MPI_SOURCE, kFinishTag, MPI_COMM_WORLD);
        }
        std::cout << "Integral value: " << integral << ".\n";
    } else {
        MPI_Send(0, 0, MPI_DOUBLE, 0, kCalculateTag, MPI_COMM_WORLD);
        while (status.MPI_TAG != kFinishTag) {
            MPI_Recv(interval.data(), interval.size(), MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            if (status.MPI_TAG != kFinishTag) {
                double intergal_process_part = 0;
                double s = f(interval[0]);
                for(double i = interval[0] + h; i <= interval[1]; i += h) {
                    intergal_process_part += (s + f(i)) * h / 2;
                    s = f(i);
                }
                MPI_Send(&intergal_process_part, 1, MPI_DOUBLE, kMainProcessID, kCalculateTag, MPI_COMM_WORLD);
            }
        }
    }

    MPI_Finalize();
    return 0;
}