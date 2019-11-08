#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RESET "\x1B[0m"
#define YELLOW "\x1b[33m"  // Utilizada para os guerreiros
#define GREEN "\x1b[32m"   // Utilizada para os arqueiros
#define BLUE "\x1b[34m"    // Utilizada para os magos
#define CYAN "\x1b[36m"    // Utilizada para os assassinos

#define MAGENTA "\x1b[35m"  // Utilizada para o giant
#define RED "\x1b[31m"      // Utilizada para o dragon
#define WHITE "\x1b[37m"    // Utilizada para o skeleton

#define NUMERO_DE_GUERREIROS 6
#define NUMERO_DE_MAGOS 6
#define NUMERO_DE_ARQUEIROS 6
#define NUMERO_DE_ASSASSINOS 6

int GOOD_NEXUS = 100;  // Vida total da party
int EVIL_NEXUS = 100;  // vida total dos monstros

// Declaração de threads, mutex e semáforos
pthread_t dragon, skeleton, giant, guerreiros[NUMERO_DE_GUERREIROS],
    magos[NUMERO_DE_MAGOS], arqueiros[NUMERO_DE_ARQUEIROS],
    assassinos[NUMERO_DE_ASSASSINOS];
pthread_mutex_t mutexGuerreiro, mutexMago, mutexArqueiro, mutexAssassino;
sem_t passeAM, passeAF, passeBM, passeBF, banheiroM, banheiroF;

void print_nexus() {
  printf(CYAN "NEXUS ALIADO  ~~> [");
  for (int i = 1; i < (GOOD_NEXUS / 10); i++) {
    printf("#");
  }
  printf("]\n");

  printf(RED "NEXUS INIMIGO ~~> [");
  for (int i = 1; i < (EVIL_NEXUS / 10); i++) {
    printf("#");
  }
  printf("]\n\n\n");
}

void *ataque_guerreiro(void *arg) {
  int i = *((int *)arg);
  while (EVIL_NEXUS > 0) {
    print_nexus();
    printf(YELLOW "Guerreiro %d atacou \n", i);
    EVIL_NEXUS = EVIL_NEXUS - 1;
    sleep(3);
  }
}

void *ataque_arqueiro(void *arg) {
  int i = *((int *)arg);
  while (EVIL_NEXUS > 0) {
    print_nexus();
    printf(GREEN "Arqueiro %d atacou \n", i);
    EVIL_NEXUS = EVIL_NEXUS - 3;
    sleep(2);
  }
}

void *ataque_mago(void *arg) {
  int i = *((int *)arg);
  while (EVIL_NEXUS > 0) {
    print_nexus();
    printf(BLUE "Mago %d atacou \n", i);
    EVIL_NEXUS = EVIL_NEXUS - 5;
    sleep(5);
  }
}

void *ataque_assassino(void *arg) {
  int i = *((int *)arg);
  while (EVIL_NEXUS > 0) {
    print_nexus();
    printf(CYAN "Assassino %d atacou \n", i);
    EVIL_NEXUS = EVIL_NEXUS - 2;
    sleep(1);
  }
}

int main() {
  int i = 0;
  int *id;

  // Criação das threads de guerreiros
  for (i = 0; i < NUMERO_DE_GUERREIROS; i++) {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&(guerreiros[i]), NULL, ataque_guerreiro, (void *)id);
  }

  // Criação das threads de arqueiros
  for (i = 0; i < NUMERO_DE_ARQUEIROS; i++) {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&(arqueiros[i]), NULL, ataque_arqueiro, (void *)id);
  }

  // Criação das threads de magos
  for (i = 0; i < NUMERO_DE_MAGOS; i++) {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&(magos[i]), NULL, ataque_mago, (void *)id);
  }

  // Criação das threads de assassinos
  for (i = 0; i < NUMERO_DE_ASSASSINOS; i++) {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&(assassinos[i]), NULL, ataque_assassino, (void *)id);
  }

  for (i = 0; i < NUMERO_DE_GUERREIROS; i++) {
    pthread_join(guerreiros[i], NULL);
  }

  for (i = 0; i < NUMERO_DE_ARQUEIROS; i++) {
    pthread_join(arqueiros[i], NULL);
  }

  for (i = 0; i < NUMERO_DE_MAGOS; i++) {
    pthread_join(magos[i], NULL);
  }

  for (i = 0; i < NUMERO_DE_ASSASSINOS; i++) {
    pthread_join(assassinos[i], NULL);
  }

  return 0;
}