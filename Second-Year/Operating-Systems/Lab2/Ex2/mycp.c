#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Wrong number of arguments. Type ./mycp <source> <destination>");
        return 0;
    }
    int sourceDesc, destDesc;
    char* source = argv[1];
    char* destination = argv[2];

    sourceDesc = open(source, O_RDONLY);
    if (sourceDesc == -1) {
        printf("Error with source file -> Error no%d", errno);
        return 0;
    }
    //opened source file successfully

    destDesc = open(destination, O_CREAT | O_WRONLY, S_IRWXU);
    if(destDesc == -1){
        printf("Error with destination file -> Error no%d", errno);
        return 0;
    }
    //opened destination file successfully; time to copy

  char buff[1024];
  int r_bytes = 0;
  int w_bytes;
  int curr_w_bytes;

    while ((r_bytes = read(sourceDesc, buff, 1024)) > 0) {
        w_bytes = 0;
        curr_w_bytes;

        while ( ( curr_w_bytes = write(destDesc, buff + w_bytes, r_bytes - w_bytes) ) > 0)
            w_bytes += curr_w_bytes;

        if (curr_w_bytes < 0) {
          printf("Error while writing to dest file-> Error no%d", errno);
        return 0;
        }
    }

    if (r_bytes == -1) {
        printf("Error while reading from source file-> Error no%d", errno);
        return 0;
    }

    //close files
    close(sourceDesc);
    close(destDesc);

    return 0;

}
