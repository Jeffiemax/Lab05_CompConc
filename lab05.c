#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

#define NTHREADS  5

/* Variaveis globais */
int x = 0;
pthread_mutex_t mutex;
pthread_cond_t cond;

/* Threads que incrementam x */
void *A (void *t) {
  int *my_id = (int*)t;
  //printf("A: Comecei: thread %d\n", *my_id);
  pthread_mutex_lock(&mutex);
  //printf("O valor de x é %d\n", x);
  while(x != 4){
    pthread_cond_wait(&cond, &mutex);
  }
  printf("Volte sempre\n");
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  free(my_id); 
  pthread_exit(NULL);
}

void *B (void *t) {
  int *my_id = (int*)t;
  //printf("B: Comecei: thread %d\n", *my_id);
  pthread_mutex_lock(&mutex);
  //printf("O valor de x é %d\n", x);
  while( x == 0 ) {
    pthread_cond_wait(&cond, &mutex);
    //printf("desbloqueou\n");
  }
  printf("Fique a vontade\n");
  x++;
  //printf("somou mais um x = %d\n",x);
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  free(my_id);
  pthread_exit(NULL);
}

void *C (void *t) {
  int *my_id = (int*)t;
  //printf("C: Comecei: thread %d\n", *my_id);
  pthread_mutex_lock(&mutex);
  //printf("O valor de x é %d\n", x);
  while(x == 0){
    pthread_cond_wait(&cond, &mutex);
    //printf("desbloqueou\n");
  }
  printf("Sente-se por favor\n");
  x++;
  //printf("somou mais um x = %d\n",x);
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  free(my_id);
  pthread_exit(NULL);
}

void *D (void *t) {
  int *my_id = (int*)t;
  //printf("D: Comecei: thread %d\n", *my_id);
  pthread_mutex_lock(&mutex);
  //printf("O valor de x é %d\n", x);
  while(x == 0){
    pthread_cond_wait(&cond, &mutex);
   // printf("desbloqueou\n");
  }
  printf("Aceita um copo d'água\n");
  x++;
  //printf("somou mais um x = %d\n",x);
  pthread_cond_signal(&cond);
  pthread_mutex_unlock(&mutex);
  free(my_id);
  pthread_exit(NULL);
}

void *E (void *t) {
  int *my_id = (int*)t;
  //printf("E: Comecei: thread %d\n", *my_id);
  pthread_mutex_lock(&mutex);
  //printf("O valor de x é %d\n", x);
  if(x == 0){
    printf("Seja bem-vindo!\n");
    x++;
  }
  //printf("somou mais um x = %d\n",x);
  pthread_cond_broadcast(&cond);
  pthread_mutex_unlock(&mutex);
  free(my_id);
  pthread_exit(NULL);
}

/* Funcao principal */
int main(int argc, char *argv[]) {
  int *t1, *t2, *t3, *t4, *t5;
  pthread_t threads[NTHREADS];

  //aloca espaco para os identificadores das threads
    t1 = malloc(sizeof(int));
    t2 = malloc(sizeof(int));
    t3 = malloc(sizeof(int));
    t4 = malloc(sizeof(int));
    t5 = malloc(sizeof(int));
    *t1=1, *t2=2, *t3=3, *t4=4, *t5=5; 

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init (&cond, NULL);

  /* Cria as threads */
  pthread_create(&threads[0], NULL, A, (void*)t1);
  pthread_create(&threads[1], NULL, B, (void*)t2);
  pthread_create(&threads[2], NULL, C, (void*)t3);
  pthread_create(&threads[3], NULL, D, (void*)t4);
  pthread_create(&threads[4], NULL, E, (void*)t5);
 

  /* Espera todas as threads completarem */
  for (int i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }
  printf ("FIM.\n");

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&mutex);
  pthread_cond_destroy(&cond);
}