#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ds
{
    int *vclock;
    int nprocs;
    int rank;
    MPI_Comm comm;
} ds_t;

ds_t *ds_create(MPI_Comm comm)
{
    ds_t *ds = malloc(sizeof(*ds));
    if (NULL == ds)
    {
        return NULL;
    }
    ds->comm = comm;

    MPI_Comm_size(comm, &ds->nprocs);
    MPI_Comm_rank(comm, &ds->rank);

    // sizeof(int) * Comm_size
    ds->vclock = malloc(sizeof(*(ds->vclock)) * ds->nprocs);
    if (NULL == ds->vclock)
    {
        free(ds);
        return NULL;
    }

    for (int i = 0; i < ds->nprocs; i++) { 
        ds->vclock[i] = 0;
    }
    return ds;
}

void ds_free(ds_t *ds)
{
    free(ds->vclock);
    free(ds);
}

void ds_print_clock(ds_t *ds)
{
    printf("proc: %d clock: ", ds->rank);
    for (int i = 0; i < ds->nprocs; i++)
        printf("%d ", ds->vclock[i]);
    printf("\n");
}

void ds_event(ds_t *ds, char *event)
{
    ds->vclock[ds->rank]++;
    printf("proc: %d event: '%s' time: %d\n", ds->rank, event, ds->vclock[ds->rank]);
}

int ds_send(ds_t *ds, void *buf, int count, MPI_Datatype datatype, int dest, int tag)
{
    int userbuf_size, clockbuf_size, packbuf_size;
    MPI_Pack_size(count, datatype, ds->comm, &userbuf_size);
    MPI_Pack_size(ds->nprocs, MPI_INT, ds->comm, &clockbuf_size);
    packbuf_size = userbuf_size + clockbuf_size;
    char *outbuf = malloc(sizeof(*buf) * packbuf_size);
    if (NULL == outbuf)
    {
        fprintf(stderr, "error: no enough memory\n");
        MPI_Abort(ds->comm, EXIT_FAILURE);
    }

    int position = 0;
    ds->vclock[ds->rank]++; 
    MPI_Pack(buf, count, datatype, outbuf, packbuf_size, &position, ds->comm); 
    MPI_Pack(ds->vclock, ds->nprocs, MPI_INT, outbuf, packbuf_size, &position, ds->comm);
    
    MPI_Send(outbuf, position, MPI_PACKED, dest, tag, ds->comm);
    free(outbuf);
}

int ds_recv(ds_t *ds, void *buf, int count, MPI_Datatype datatype, int src, int tag)
{
    int userbuf_size, clockbuf_size, packbuf_size, comm_size;
    MPI_Pack_size(count, datatype, ds->comm, &userbuf_size);
    MPI_Pack_size(ds->nprocs, MPI_INT, ds->comm, &clockbuf_size);
    packbuf_size = userbuf_size + clockbuf_size; // MessageSize + ClockVectorSize
    char *inbuf = malloc(sizeof(*buf) * packbuf_size);
    int *vc = malloc(sizeof(*vc) * ds->nprocs);
    if (NULL == inbuf || NULL == vc)
    {
        fprintf(stderr, "error: no enough memory\n");
        MPI_Abort(ds->comm, EXIT_FAILURE);
    }

    MPI_Recv(inbuf, packbuf_size, MPI_PACKED, src, tag, ds->comm, MPI_STATUS_IGNORE);
    int position = 0;
    MPI_Unpack(inbuf, packbuf_size, &position, buf, count, datatype, ds->comm);
    MPI_Unpack(inbuf, packbuf_size, &position, vc, ds->nprocs, MPI_INT, ds->comm);
    free(inbuf);

    ds->vclock[ds->rank]++; 
    for (int i = 0; i < ds->nprocs; i++)
    {
        ds->vclock[i] = vc[i] > ds->vclock[i] ? vc[i] : ds->vclock[i];
    }

    free(vc);
}

int main(int argc, char **argv)
{
    // Init
    MPI_Comm comm = MPI_COMM_WORLD;
    int rank, commSize;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &commSize);
    ds_t *ds = ds_create(comm);
    int buf; // Message
    if (rank == 0) {
        buf = rank;
    }
    printf("INIT ");
    ds_print_clock(ds);

    // Receive message from parent node (if exists)
    if (rank != 0) {
        // Calculate parentRank
        int parentRank = (int) (rank - 1) / 2;
        printf("PARENT INFO: rank: %d, parentRank: %d\n", rank, parentRank);
        ds_recv(ds, &buf, 1, MPI_INT, parentRank, 0);
        printf("AFTER RECEIVE ");
        ds_print_clock(ds);
    }

    // Send messages for left and right children (if exists)
    int leftChildRank =  2 * rank + 1;
    int rightChildRank = 2 * rank + 2;
    if (leftChildRank < commSize) {
        ds_send(ds, &buf, 1, MPI_INT, leftChildRank, 0);
        printf("AFTER LEFT SEND ");
        ds_print_clock(ds);
        if (rightChildRank < commSize) {
            ds_send(ds, &buf, 1, MPI_INT, rightChildRank, 0);
            printf("AFTER RIGHT SEND ");
            ds_print_clock(ds);
        }   
    }

    ds_free(ds);
    MPI_Finalize();
    return 0;
}