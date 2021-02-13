#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

const char shm_name[] = "/shmcollatz";


int main(int argc, char* argv[]) {

    int i, j;
    printf("Starting parent %d\n", getpid());

    int shm_fd = shm_open(shm_name, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (shm_fd < 0) {
        perror("Failed to open shared memory handle");
        return 1;
    }

    const int nr_arg = argc - 1;
    const size_t page_size = getpagesize();

    if (ftruncate(shm_fd, nr_arg * page_size) == -1) {
        perror(NULL);
        shm_unlink(shm_name);
        return errno;
    }

    int* parent_ptr = mmap(NULL, nr_arg * page_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    for (i = 0; i < nr_arg; ++i) {
        pid_t pid = fork();
        if (pid < 0) {
            return errno;
        } else if (pid == 0) {
            int* child_ptr = parent_ptr + i * page_size / sizeof(int);
            if (child_ptr == MAP_FAILED)
                return errno;

            int nr, seqLength = 0;;
            sscanf(argv[1 + i], "%d", &nr);
            int copynr = nr;

            while (nr != 1){
                child_ptr[seqLength++] = nr;
                if (nr % 2 == 0) {
                    nr /= 2;
                } else {
                    nr = nr * 3 + 1;
                }
            }

            child_ptr[seqLength] = nr;
            child_ptr[seqLength + 1] = copynr; //pastram nr initial pe ultima poz ca sa l afisam
            child_ptr[0] = seqLength; //pastram lungimea pe prima sa stim cat afisam

            exit(0);
        }
    }

    for (i = 0; i < nr_arg; ++i) {
        pid_t pid = wait(NULL);
        printf("Done Parent %d Me %d\n", getpid(), pid);
    }

    for (i = 0; i < nr_arg; ++i) {
        int* child_ptr = &parent_ptr[i * page_size / sizeof(int)];
        int to_print = child_ptr[0];
        int nr = child_ptr[to_print + 1];
        printf("%d: ", nr);
        for (j = 1; j <= to_print; ++j) {
            printf("%d ", child_ptr[j]);
        }
        printf("\n");
    }

    munmap(parent_ptr, nr_arg * page_size);

}