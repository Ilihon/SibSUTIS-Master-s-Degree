prog := mpiclocksync
prog_objs := mpiclocksync.o

CC := mpicc
CFLAGS := 
LDFLAGS := -lm

.PHONY: all clean

all: $(prog)

$(prog): $(prog_objs)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

mpiclocksync.o: mpiclocksync.c

clean:
	@rm -rf *.o $(prog)