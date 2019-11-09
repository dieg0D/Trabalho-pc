/**
 *  Trabalho: RPG concorrente
 *  Alunos: Diego Antônio Barbosa Cardoso - 16/0005116
 *          Icaro Nery Rezende            - 15/0037023
 *
 *
 */

#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define RESET "\x1B[0m"
#define YELLOW "\x1b[33m"  // Utilizada para os guerreiros
#define GREEN "\x1b[32m"   // Utilizada para os arqueiros
#define BLUE "\x1b[34m"    // Utilizada para os magos
#define CYAN "\x1b[36m"    // Utilizada para os assassinos

#define MAGENTA "\x1b[35m"  // Utilizada para o giant
#define RED "\x1b[31m"      // Utilizada para o dragon
#define WHITE "\x1b[37m"    // Utilizada para o skeleton

#define NUMERO_DE_GUERREIROS 15
#define NUMERO_DE_MAGOS 8
#define NUMERO_DE_ARQUEIROS 5
#define NUMERO_DE_ASSASSINOS 5

// 5 de cada classe totaliza 200 de vida
// NUMERO_DE_GUERREIROS * 20 + NUMERO_DE_MAGOS * 5 + NUMERO_DE_ARQUEIROS * 10 +
// NUMERO_DE_ASSASSINOS * 5
int GOOD_NEXUS = NUMERO_DE_GUERREIROS * 20 + NUMERO_DE_MAGOS * 5 +
                 NUMERO_DE_ARQUEIROS * 10 +
                 NUMERO_DE_ASSASSINOS * 5;  // Vida total da party
int EVIL_NEXUS = 200;                       // vida total dos monstros

int ta_pegando_fogo_bixo = 0;
int ta_tremendo_tudo_bixo = 0;
int ta_puto_bixo = 0;

// Declaração de threads, mutex e semáforos
pthread_t dragon, skeleton, giant, guerreiros[NUMERO_DE_GUERREIROS],
    magos[NUMERO_DE_MAGOS], arqueiros[NUMERO_DE_ARQUEIROS],
    assassinos[NUMERO_DE_ASSASSINOS];
pthread_mutex_t mutexparty;
sem_t ataque_dragon, ataque_giant, ataque_skeleton;

int select_target() {
  int numero_randomico;
  srand((unsigned)time(NULL));
  numero_randomico = (rand()) % 3;
  return numero_randomico;
}

void print_nexus() {
  printf(CYAN "\n\nNEXUS ALIADO  ~~> [");
  for (int i = 1; i < (GOOD_NEXUS / 10); i++) {
    printf("#");
  }
  printf("]\n");

  printf(RED "NEXUS INIMIGO ~~> [");
  for (int i = 1; i < (EVIL_NEXUS / 5); i++) {
    printf("#");
  }
  printf("]\n\n");
}

void *ataque_guerreiro(void *arg) {
  int i = *((int *)arg);
  while (EVIL_NEXUS > 0) {
    switch (select_target()) {
      case 0:
        sem_wait(&ataque_dragon);
        if (ta_pegando_fogo_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(YELLOW "O Guerreiro %d atacou o dragão\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 1;
        sleep(2);
        sem_post(&ataque_dragon);
        break;

      case 1:
        sem_wait(&ataque_giant);
        if (ta_tremendo_tudo_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(YELLOW "O Guerreiro %d atacou o Gigante\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 1;
        sleep(2);
        sem_post(&ataque_giant);
        break;

      case 2:
        sem_wait(&ataque_skeleton);
        if (ta_puto_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(YELLOW "O Guerreiro %d atacou o Esqueleto\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 1;
        sleep(2);
        sem_post(&ataque_skeleton);
        break;

      default:
        break;
    }
  }
  printf(CYAN "Os herois venceram\n");
  exit(0);
}

void *ataque_arqueiro(void *arg) {
  int i = *((int *)arg);
  while (EVIL_NEXUS > 0) {
    switch (select_target()) {
      case 0:
        sem_wait(&ataque_dragon);
        if (ta_pegando_fogo_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(GREEN "O Arqueiro %d atacou o dragão\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 2;
        sleep(1);
        sem_post(&ataque_dragon);
        break;

      case 1:
        sem_wait(&ataque_giant);
        if (ta_tremendo_tudo_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(GREEN "O Arqueiro %d atacou o Gigante\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 2;
        sleep(1);
        sem_post(&ataque_giant);
        break;

      case 2:
        sem_wait(&ataque_skeleton);
        if (ta_puto_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(GREEN "O Arqueiro %d atacou o Esqueleto\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 2;
        sleep(1);
        sem_post(&ataque_skeleton);
        break;

      default:
        break;
    }
  }
  printf(CYAN "\n\nOs herois venceram\n");
  exit(0);
}

void *ataque_mago(void *arg) {
  int i = *((int *)arg);
  while (EVIL_NEXUS > 0) {
    switch (select_target()) {
      case 0:
        sem_wait(&ataque_dragon);
        if (ta_pegando_fogo_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(BLUE "O Mago %d atacou o dragão\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 5;
        sleep(8);
        sem_post(&ataque_dragon);
        break;

      case 1:
        sem_wait(&ataque_giant);
        if (ta_tremendo_tudo_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(BLUE "O Mago %d atacou o Gigante\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 5;
        sleep(8);
        sem_post(&ataque_giant);
        break;

      case 2:
        sem_wait(&ataque_skeleton);
        if (ta_puto_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(BLUE "O Mago %d atacou o Esqueleto\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 5;
        sleep(8);
        sem_post(&ataque_skeleton);
        break;

      default:
        break;
    }
  }
  printf(CYAN "\n\nOs herois venceram\n");
  exit(0);
}

void *ataque_assassino(void *arg) {
  int i = *((int *)arg);
  while (EVIL_NEXUS > 0) {
    switch (select_target()) {
      case 0:
        sem_wait(&ataque_dragon);
        if (ta_pegando_fogo_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(CYAN "O Assassino %d atacou o dragão\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 4;
        sleep(4);
        sem_post(&ataque_dragon);
        break;

      case 1:
        sem_wait(&ataque_giant);
        if (ta_tremendo_tudo_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(CYAN "O Assassino %d atacou o Gigante\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 4;
        sleep(4);
        sem_post(&ataque_giant);
        break;

      case 2:
        sem_wait(&ataque_skeleton);
        if (ta_puto_bixo) {
          pthread_mutex_lock(&mutexparty);
          pthread_mutex_unlock(&mutexparty);
        }
        printf(CYAN "O Assassino %d atacou o Esqueleto\n", i);
        EVIL_NEXUS = EVIL_NEXUS - 4;
        sleep(4);
        sem_post(&ataque_skeleton);
        break;

      default:
        break;
    }
  }
  printf(CYAN "\n\nOs herois venceram\n");
  exit(0);
}

void *ataque_especial_dragon(void *arg) {
  while (GOOD_NEXUS > 0) {
    sleep(15);
    printf(RED "\n\nO Dragão se prepara para atacar \n");
    pthread_mutex_lock(&mutexparty);
    ta_pegando_fogo_bixo = 1;
    printf(RED "O Dragão ta mandando fogo pra todo lado \n");
    sleep(1);
    GOOD_NEXUS = GOOD_NEXUS - 30;
    printf(RED "O Dragão terminou de atacar \n");
    print_nexus();
    ta_pegando_fogo_bixo = 0;
    pthread_mutex_unlock(&mutexparty);
  }
  printf(RED "\n\nOs Monstros Venceram\n");
  exit(0);
}

void *ataque_especial_giant(void *arg) {
  while (GOOD_NEXUS > 0) {
    sleep(10);
    printf(MAGENTA "\n\nO Gigante se prepara para atacar \n");
    pthread_mutex_lock(&mutexparty);
    ta_tremendo_tudo_bixo = 1;
    printf(MAGENTA "O Gigante ta pisando em todo mundo \n");
    sleep(1);
    GOOD_NEXUS = GOOD_NEXUS - 15;
    printf(MAGENTA "O Gigante terminou de atacar \n");
    print_nexus();
    ta_tremendo_tudo_bixo = 0;
    pthread_mutex_unlock(&mutexparty);
  }
  printf(RED "\n\nOs Monstros Venceram\n");
  exit(0);
}

void *ataque_especial_skeleton(void *arg) {
  while (GOOD_NEXUS > 0) {
    sleep(5);
    printf(WHITE "\n\nO Esqueleto se prepara para atacar \n");
    pthread_mutex_lock(&mutexparty);
    ta_puto_bixo = 1;
    printf(WHITE "O Esqueleto grita: 'SE EU PUDESSE EU MATAVA 1000' \n");
    sleep(1);
    GOOD_NEXUS = GOOD_NEXUS - 5;
    printf(WHITE "O Esqueleto terminou de atacar \n");
    print_nexus();
    ta_puto_bixo = 0;
    pthread_mutex_unlock(&mutexparty);
  }
  printf(RED "\n\nOs Monstros Venceram\n\n");
  exit(0);
}

int main() {
  int i = 0;
  int *id;

  printf(RED "############################################\n");
  printf(RED "###                                      ###\n");
  printf(RED "###    A BATALHA FINAL IRÁ COMEÇAR!!!!   ###\n");
  printf(RED "###                                      ###\n");
  printf(RED "############################################\n\n");

  print_nexus();

  sem_init(&ataque_dragon, 0, 1);
  sem_init(&ataque_giant, 0, 1);
  sem_init(&ataque_skeleton, 0, 1);

  pthread_mutex_init(&mutexparty, NULL);

  // Criação das threads de guerreiros
  for (i = 0; i < NUMERO_DE_GUERREIROS; i++) {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&(guerreiros[i]), NULL, ataque_guerreiro, (void *)id);
  }

  for (i = 0; i < NUMERO_DE_ARQUEIROS; i++) {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&(arqueiros[i]), NULL, ataque_arqueiro, (void *)id);
  }

  for (i = 0; i < NUMERO_DE_MAGOS; i++) {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&(magos[i]), NULL, ataque_mago, (void *)id);
  }

  for (i = 0; i < NUMERO_DE_ASSASSINOS; i++) {
    id = (int *)malloc(sizeof(int));
    *id = i;
    pthread_create(&(assassinos[i]), NULL, ataque_assassino, (void *)id);
  }

  pthread_create(&dragon, NULL, ataque_especial_dragon, NULL);
  pthread_create(&giant, NULL, ataque_especial_giant, NULL);
  pthread_create(&skeleton, NULL, ataque_especial_skeleton, NULL);

  for (i = 0; i < NUMERO_DE_GUERREIROS; i++) {
    pthread_join(guerreiros[i], NULL);
  }

  for (i = 0; i < NUMERO_DE_GUERREIROS; i++) {
    pthread_join(arqueiros[i], NULL);
  }

  for (i = 0; i < NUMERO_DE_GUERREIROS; i++) {
    pthread_join(magos[i], NULL);
  }

  for (i = 0; i < NUMERO_DE_GUERREIROS; i++) {
    pthread_join(assassinos[i], NULL);
  }
  pthread_join(dragon, NULL);
  pthread_join(giant, NULL);
  pthread_join(skeleton, NULL);

  return 0;
}