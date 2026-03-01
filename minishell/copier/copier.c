#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define Taille 1024

int main(int argc, char* argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s source_file dest_file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char tampon[Taille];
    int fd_source = open(argv[1], O_RDONLY);
    if (fd_source < 0) {
        perror("Erreur à l'ouverture du fichier source");
        exit(EXIT_FAILURE);
    }

    int fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0640);
    if (fd_dest < 0) {
        perror("Erreur à l'ouverture du fichier destination");
        close(fd_source);
        exit(EXIT_FAILURE);
    }

    int lus;
    while ((lus = read(fd_source, tampon, Taille)) > 0) {
        write(fd_dest, tampon, lus);
    }

    close(fd_source);
    close(fd_dest);

    return EXIT_SUCCESS;
}
