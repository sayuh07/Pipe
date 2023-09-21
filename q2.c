#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    int fd[2];
    char buffer;
    pid_t pid;
   
    if((pipe(fd)) == -1){
        perror("pipe");
        exit(1);
    }
    
    pid = fork();
    if(pid == -1){
        perror("fork");
        exit(1);
    }
    if(pid == 0){
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("My number is %d from parent.", y);
    }
    else{
        close(fd[0]);
        int x;
        printf("Number:");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }
    return 0;
}