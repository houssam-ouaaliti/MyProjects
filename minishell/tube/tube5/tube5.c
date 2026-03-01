#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define N 10000

int main(void) {
    char tampon[N];
    char lecture[10 * N];
    int tube[2];
    int ecrit, lus;

    pipe(tube);
    pid_t pidFils = fork();

    switch (pidFils) {
        case -1:
            perror("fork");
            exit(EXIT_FAILURE);

        case 0:
            close(tube[1]);
            signal(SIGINT, SIG_IGN);
            signal(SIGTSTP, SIG_IGN);
            lus = read(tube[0], lecture, sizeof(lecture));
            close(tube[0]);
            exit(EXIT_SUCCESS);

        default:
            close(tube[0]);
            while (1) {
                ecrit = write(tube[1], tampon, sizeof(tampon));
                sleep(1);
                printf("valeur_write = %d\n", ecrit);
            }
    }

    return EXIT_SUCCESS;
}

