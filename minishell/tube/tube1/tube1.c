#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int tube[2];
    int val;

    pipe(tube);
    pid_t pid = fork();

    switch (pid) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        case 0:
            close(tube[1]);
            if (read(tube[0], &val, sizeof(val)) > 0) {
                printf("valeur = %d\n", val);
            }
            close(tube[0]);
            break;

        default:
            close(tube[0]);
            val = 10;
            write(tube[1], &val, sizeof(val));
            close(tube[1]);
            wait(NULL);
            break;
    }

    return EXIT_SUCCESS;
}




