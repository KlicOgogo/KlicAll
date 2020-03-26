#include "mpi.h"
#include <iostream>
#include <random>
#include <string>


int main(int argc, char* argv[]) {
    char* msg;
    char** msg_list;

    int rank;
    int size;
    int tag = 50;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank != 0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(10, 100);
        int msg_size = dis(gen);
        msg = new char[msg_size+1]();
        for (int i = 0; i < msg_size; ++i) {
            msg[i] = 'a';
        }
        printf("Sending from rank %d: %s --- %d characters\n", rank, msg, msg_size);
        const int destination = 0;
        MPI_Send(msg, msg_size + 1, MPI_CHAR, destination, tag, MPI_COMM_WORLD);
        delete[] msg;
    } else {
        msg_list = new char*[size-1];
        for (int i = 1; i < size; ++i) {
            int msg_size;
            MPI_Probe(MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &status);
            const int sender_rank = status.MPI_SOURCE;
            MPI_Get_count(&status, MPI_CHAR, &msg_size);
            msg_list[sender_rank-1] = new char[msg_size+1]();
            MPI_Recv(msg_list[sender_rank-1], msg_size, MPI_CHAR, sender_rank, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Received from rank %d: %s --- %d characters \n", sender_rank, msg_list[sender_rank-1], msg_size);
            delete[] msg_list[sender_rank-1];
        }
        delete[] msg_list;
    }

    MPI_Finalize();
    return 0;
}
