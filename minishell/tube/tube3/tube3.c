#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int N = 10;
int val;
int lus;

int main(void) {
    int tube[2];
    pipe(tube);

    pid_t pidFils = fork();

    switch (pidFils) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        case 0:
            close(tube[1]);
            while ((lus = read(tube[0], &val, sizeof(val))) > 0) {
                printf("valeur = %d\n", val);
                printf("valeur_read = %d\n", lus);
            }
            printf("sortie de boucle\n");
            close(tube[0]);
            exit(EXIT_SUCCESS);

        default:
            close(tube[0]);
            for (val = 0; val < N; val++) {
                write(tube[1], &val, sizeof(val));
            }
            close(tube[1]);
            pause();
    }

    return EXIT_SUCCESS;
}

