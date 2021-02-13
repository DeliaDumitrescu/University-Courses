#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

void* reverse_string(void* str){
    int i;
    char* str2 = str;
    size_t length = strlen(str2);
    char* str_result = malloc(sizeof(char) * (length + 1));
    for(i = i; i < length; i++)
        str_result[i] = str2[length - i - 1];

    str_result[i] = 0;
    return str_result;
}

int main(int argc, char* argv[])
{
    if(argc != 2){
        printf("Enter only the string to reverse");
        return 1;
    }
    char* str_to_rev = argv[1];

    pthread_t thr = 0;

    if(pthread_create(&thr, NULL, reverse_string, str_to_rev) != 0){ //intializam threadul lansat prin reverse_string cu arg str_to_rev
        perror("Failed to create thread");
        return 0;
    }

    void* str_rev = NULL;
    pthread_join(thr, &str_rev);

    printf("%s\n", (char*)str_rev);
    free(str_rev);

    return 0;
}