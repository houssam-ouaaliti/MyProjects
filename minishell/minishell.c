#include <stdio.h>
#include <stdlib.h>
#include "readcmd.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>

void traiter_sigchld(int sig) {
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED)) > 0) {
        printf("[Processus %d terminé]\n", pid);
    }
}

void handler_signal(int sig) {
    write(STDOUT_FILENO, "\n> ", 3);
}

void changer_repertoire(char *chemin) {
    if (chemin == NULL) {
        char *home = getenv("HOME");
        if (home != NULL) {
            if (chdir(home) == -1) {
                perror("Erreur chdir vers HOME");
            }
        } else {
            fprintf(stderr, "Erreur : la variable d'environnement HOME n'est pas définie\n");
        }
    } else {
        if (chdir(chemin) == -1) {
            perror("Erreur chdir");
        }
    }
}

void lister_repertoire(char *chemin) {
    DIR *dir = opendir(chemin ? chemin : ".");
    if (dir == NULL) {
        perror("Erreur ouverture du répertoire");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
}

int main(void) {
    bool fini = false;

    struct sigaction sa;
    sa.sa_handler = traiter_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);

    signal(SIGINT, SIG_IGN);
    signal(SIGTSTP, SIG_IGN);

    sigset_t set_signaux;
    sigemptyset(&set_signaux);
    sigaddset(&set_signaux, SIGINT);
    sigaddset(&set_signaux, SIGTSTP);
    sigprocmask(SIG_BLOCK, &set_signaux, NULL);

    while (!fini) {
        printf("> ");
        struct cmdline *commande = readcmd();

        if (commande == NULL) {
            perror("erreur lecture commande\n");
            exit(EXIT_FAILURE);
        }

        if (commande->err) {
            printf("erreur saisie de la commande : %s\n", commande->err);
        } else {
            int indexseq = 0;
            char **cmd;
            int tube[2];  // Tube pour le pipeline
            int fd_entree = 0; // Variable pour gérer l'entrée

            // Parcours des commandes dans la séquence (pour gérer les pipelines)
            while ((cmd = commande->seq[indexseq])) {
                if (cmd[0]) {
                    if (strcmp(cmd[0], "exit") == 0) {
                        fini = true;
                        printf("Au revoir ...\n");
                    } else if (strcmp(cmd[0], "cd") == 0) {
                        if (cmd[1]) {
                            changer_repertoire(cmd[1]);
                        } else {
                            changer_repertoire(NULL);
                        }
                    } else if (strcmp(cmd[0], "dir") == 0) {
                        if (cmd[1]) {
                            lister_repertoire(cmd[1]);
                        } else {
                            lister_repertoire(NULL);
                        }
                    } else {
                        bool background = false;
                        int last_index = 0;
                        while (cmd[last_index] != NULL) {
                            last_index++;
                        }
                        if (last_index > 0 && strcmp(cmd[last_index - 1], "&") == 0) {
                            background = true;
                            cmd[last_index - 1] = NULL;
                        }

                        char *input_file = NULL;
                        char *output_file = NULL;

                        // Gérer les redirections
                        for (int i = 0; cmd[i] != NULL; i++) {
                            if (strcmp(cmd[i], "<") == 0) {
                                input_file = cmd[i + 1];
                                cmd[i] = NULL;
                            } else if (strcmp(cmd[i], ">") == 0) {
                                output_file = cmd[i + 1];
                                cmd[i] = NULL;
                            }
                        }

                        commande->in = input_file;
                        commande->out = output_file;

                        // Création du tube si nécessaire
                        if (commande->seq[indexseq + 1] != NULL) {
                            if (pipe(tube) == -1) {
                                perror("Erreur création tube");
                                exit(EXIT_FAILURE);
                            }
                        }

                        pid_t pid = fork();
                        if (pid == -1) {
                            perror("Erreur fork");
                            exit(EXIT_FAILURE);
                        } else if (pid == 0) {
                            signal(SIGINT, SIG_DFL);
                            signal(SIGTSTP, SIG_DFL);
                            sigprocmask(SIG_UNBLOCK, &set_signaux, NULL);

                            // Gérer les redirections de fichier
                            if (commande->in != NULL) {
                                int fd_in = open(commande->in, O_RDONLY);
                                if (fd_in == -1) {
                                    perror("Erreur d'ouverture du fichier d'entrée");
                                    exit(EXIT_FAILURE);
                                }
                                dup2(fd_in, 0);
                                close(fd_in);
                            }

                            if (commande->out != NULL) {
                                int fd_out = open(commande->out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                                if (fd_out == -1) {
                                    perror("Erreur d'ouverture du fichier de sortie");
                                    exit(EXIT_FAILURE);
                                }
                                dup2(fd_out, 1);
                                close(fd_out);
                            }

                            // Redirection de la sortie vers le tube si nécessaire
                            if (commande->seq[indexseq + 1] != NULL) {
                                close(tube[0]);
                                dup2(tube[1], 1);
                                close(tube[1]);
                            }

                            // Exécution de la commande
                            if (execvp(cmd[0], cmd) == -1) {
                                perror("Erreur execvp");
                                exit(EXIT_FAILURE);
                            }
                        } else {
                            // Gérer l'entrée du tube pour la commande suivante
                            if (commande->seq[indexseq + 1] != NULL) {
                                close(tube[1]);
                                fd_entree = tube[0];
                            }

                            if (!background) {
                                int status;
                                waitpid(pid, &status, 0);
                            } else {
                                printf("[Processus %d lancé en arrière plan]\n", pid);
                            }
                        }
                    }
                    indexseq++;
                }
            }
        }
    }

    return EXIT_SUCCESS;
}

