#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

sem_t empty;
sem_t full;
sem_t mutex;
sem_t synchronize;

int** queue;
int max;
int fill_ptr = 0;
int use_ptr = 0;


typedef struct __myarg_t {
    int n;
    float *a;
    float *b;
    float *c;
    int threadsize;
} myarg_t;

typedef struct value
{
   int x;
   int y;
}values;

int Open(const char *pathname, int flags)
{
    int fd = open(pathname, flags);
    
    if (fd < 0) {
       fprintf(stderr, "open error.\n");
       exit(1);
    }
    return(fd);
}

ssize_t Read(int fildes, void *buf, size_t nbyte)
{
  int res = read(fildes, buf, nbyte);
  if (res < 0)
  {
     if (errno == EINTR)
        fprintf(stderr, "read is stopped by signal.\n");
     else
        fprintf(stderr, "%s.\n", strerror(errno));
     exit(1);
  }
  return(res);
}

ssize_t Write(int fildes, const void *buf, size_t nbyte)
{
  int res = write(fildes, buf, nbyte);
  if (res < 0)
  {
     if (errno == EINTR)
        fprintf(stderr, "write is stopped by signal.\n");
     else
        fprintf(stderr, "%s.\n", strerror(errno));
     exit(1);
  }
  return(res);
}

void send(int n1, int n2)
{
   queue[fill_ptr][0] = n1;
   queue[fill_ptr][1] = n2;
   fill_ptr = (fill_ptr + 1) % max;
}

values recv()
{
   values v;
   v.x = queue[use_ptr][0];
   v.y = queue[use_ptr][1];
   use_ptr = (use_ptr + 1) % max;
   return v;       
}

void init_queue()
{
   use_ptr = 0;
   fill_ptr = 0;
}

void *MTGaussian(void *arg)
{
  myarg_t *data = (myarg_t *) arg;
 
  int n = data->n;
  
  for (int l=0;l<=n-2;l++)
  {
      for (int i=l+1;i<=n-1;i++)
      {
           sem_wait(&empty);
           sem_wait(&mutex);
           send(l, i);
           sem_post(&mutex);
           sem_post(&full);
      }

      for (int q=l+1; q<=n-1;q++) {
           sem_wait(&synchronize);
      }

  }
  
  for (int k=0;k<data->threadsize;k++)
  {
      sem_wait(&empty);
      sem_wait(&mutex);
      send(-1, -1);
      sem_post(&mutex);
      sem_post(&full);
  }
  return NULL;
}

void *WTGaussian(void *arg)
{
  myarg_t *data = (myarg_t *) arg;

  int n = data->n;
  values v;
  int l, i;
  while (1)
  {
      sem_wait(&full);
      sem_wait(&mutex);
      v = recv();
      l = v.x;
      i = v.y;
      sem_post(&mutex);
      sem_post(&empty);
      
      if ((l==-1) && (i==-1)) break;
      
      for (int j=1+l;j<=n-1;j++)
          data->a[i*n+j] = data->a[i*n+j] - ((data->a[i*n+l] / data->a[l*n+l]) * data->a[l*n+j]);
      data->b[i] = data->b[i] - ((data->a[i*n+l] / data->a[l*n+l]) * data->b[l]);

      sem_post(&synchronize);
  }
 
  return NULL;
}

void *MTBackSub(void *arg) {
  myarg_t *data = (myarg_t *) arg;

  int n = data->n;
  
  for (int i=n-1; i>=0;i--) 
  {
      data->c[i] = data->b[i] / data->a[i*n+i];

      for (int j=0;j<i;j++)
      {
           sem_wait(&empty);
           sem_wait(&mutex);
           send(i, j);
           sem_post(&mutex);
           sem_post(&full);
      }
      for (int q=0; q<i;q++) {
           sem_wait(&synchronize);
      }
   }
   for (int k=0;k<data->threadsize;k++)
   {
       sem_wait(&empty);
       sem_wait(&mutex);
       send(-1, -1);
       sem_post(&mutex);
       sem_post(&full);
   }
   return NULL;
}


void *WTBackSub(void *arg) {
  myarg_t *data = (myarg_t *) arg;
  int n = data->n;
  values v;
  int i,j;
  while (1)
  {
     sem_wait(&full);
     sem_wait(&mutex);
     v = recv();
     i = v.x;
     j = v.y;
     sem_post(&mutex);
     sem_post(&empty);
     
     if ((i==-1) && (j==-1)) break;
     
     data->b[j] = data->b[j] - (data->c[i]*data->a[j*n+i]);
     data->a[j*n+i] = 0;
     sem_post(&synchronize);
  }
  
  return NULL;
}
 

int main(int argc, char *argv[])
{
   struct timespec s, sg, sb, e, eg, eb; 
   clock_gettime(CLOCK_REALTIME, &s);
   
   myarg_t args;
   
   if (argc !=6){
      printf("Usage : %s [thread size] [bounded buffer size] [fileA] [fileB] [fileC]\n", argv[0]);
      return 1;
   }
   /* 1. file read */
   
   int threadsize = atoi(argv[1]);
   args.threadsize = threadsize;
   max = atoi(argv[2]);
   
   queue = malloc(sizeof(int*)*max);
   
   for (int i=0;i<max;i++)
   {
       queue[i] = (int*)malloc(sizeof(int)*2);
   }
   
   int Afd, Bfd, Cfd;
   
   Afd = Open(argv[3], O_RDONLY);
   Bfd = Open(argv[4], O_RDONLY); 
   Cfd = open(argv[5], O_WRONLY|O_CREAT, 0644);
   
   if (Cfd < 0)
   {
       fprintf(stderr, "open error.\n");
       exit(1);
   }
   
   int n1, n2;
   
   Read(Afd, &n1, sizeof(n1));
   Read(Bfd, &n2, sizeof(n2));

   
   if (n1 != n2)
   {
      printf("The values of n are different.\n");
      exit(1);
   }

   args.n = n1;

   float *A = (float*)malloc(sizeof(float)*n1*n1);
   float *B = (float*)malloc(sizeof(float)*n1);
   float *C = (float*)malloc(sizeof(float)*n1);
   
   Read(Afd, A, sizeof(float)*n1*n1);
   Read(Bfd, B, sizeof(float)*n1);
   
   close(Afd);
   close(Bfd);
   
   args.a = A;
   args.b = B;
   args.c = C;
      
   pthread_t pros;
   pthread_t cons[threadsize];
   
   int rc;
   
   /*2. semaphore init*/
   
   sem_init(&mutex, 0, 1);
   sem_init(&full, 0, 0);
   sem_init(&empty, 0, max-1);
   sem_init(&synchronize, 0, 0);
   
   /* 3. Gaussian Elimination */
   
   clock_gettime(CLOCK_REALTIME, &sg);
   
   rc = pthread_create(&pros, NULL, MTGaussian, (void*)&args);
   assert(rc == 0);
  
   for (int i=0;i<threadsize;i++)
   {
       rc = pthread_create(&cons[i], NULL, WTGaussian, (void*)&args);
       assert(rc == 0);
   }
   pthread_join(pros, NULL);
   
   for (int j=0;j<threadsize;j++)
   {
       pthread_join(cons[j], NULL);
   }
   
   clock_gettime(CLOCK_REALTIME, &eg);
   
   /* 4. Back Substitution */

   clock_gettime(CLOCK_REALTIME, &sb);
   
   rc = pthread_create(&pros, NULL, MTBackSub, (void*)&args);
   assert(rc == 0);

   for (int k=0;k<threadsize;k++)
   {
       rc = pthread_create(&cons[k], NULL, WTBackSub, (void*)&args);
       assert(rc == 0);
   }
   pthread_join(pros,NULL);
   for (int j=0;j<threadsize;j++)
   {
       pthread_join(cons[j], NULL);
   }
   
   clock_gettime(CLOCK_REALTIME, &eb);
   
   /* 5. save file */
   Write(Cfd, &n1, sizeof(int));
   Write(Cfd, args.c, sizeof(float)*n2);
   close(Cfd);

   free(A);
   free(B);
   free(C);
   for (int i=0;i<max;i++)
   {
       free(queue[i]);
   }
   free(queue);
   
   clock_gettime(CLOCK_REALTIME, &e);
   
   double programtime = (double)((double)(e.tv_sec - s.tv_sec) + (double)(e.tv_nsec - s.tv_nsec)/1000000000);
   double Gausstime = (double)((double)(eg.tv_sec - sg.tv_sec) + (double)(eg.tv_nsec - sg.tv_nsec)/1000000000);
   double Backsubtime = (double)((double)(eb.tv_sec - sb.tv_sec) + (double)(eb.tv_nsec - sb.tv_nsec)/1000000000);
   
   printf("GaussianElimination Time : %f\n", Gausstime);
   printf("Backsubstitution Time : %f\n", Backsubtime);
   printf("Total Time(Gaussian + Backsub) : %f\n", Gausstime + Backsubtime);   
   printf("Total Time(program) : %f\n", programtime);
   

   return 0;
}

