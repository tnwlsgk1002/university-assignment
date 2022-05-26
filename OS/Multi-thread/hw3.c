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

int t_index = 0;
pthread_barrier_t barrier;

typedef struct __myarg_t {
    int n;
    float *a;
    float *b;
    float *c;
    int p;
} myarg_t;

// wrapper
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

void *GaussianElimination(void *arg)
{
  myarg_t *data = (myarg_t *) arg;
  
  int start, end, m;
  
  int p = data->p;
  int n = data->n;
  int pi = t_index++;
  
  for (int l=0;l<n-1;l++)
  {
      m = n-l-1;
      start = (pi*m)/p+1+l;
      end = ((pi + 1) * m) / p + l;
      for (int i=start;i<=end;i++){
           for (int j=1+l;j<=n-1;j++)
           {
               data->a[i*n+j] = data->a[i*n+j] - ((data->a[i*n+l] / data->a[l*n+l]) * data->a[l*n+j]);
           }
           data->b[i] = data->b[i] - ((data->a[i*n+l] / data->a[l*n+l]) * data->b[l]);
      }
      pthread_barrier_wait(&barrier); 
  }
  return NULL;
}


void *BackSubstitution(void *arg) {
  myarg_t *data = (myarg_t *) arg;
  
  int start, end;
  
  int p = data->p;
  int n = data->n;
  int pi = t_index++;

  for (int i=n-1; i>=0;i--) 
  {
      data->c[i] = data->b[i] / data->a[i*n+i];
      start = (pi*i)/p;
      end = ((pi+1)*i)/p;

      for (int j=start;j<end;j++)
      {
           data->b[j] = data->b[j] - (data->c[i]*data->a[j*n+i]);
           data->a[j*n+i] = 0;
      }
      pthread_barrier_wait(&barrier);
   }
   return NULL;
}

int main(int argc, char *argv[])
{
   myarg_t args;
   
   if (argc !=5){
      printf("Usage : %s [number] [fileA] [fileB] [fileC]\n", argv[0]);
      return 1;
   }
   
   /* 1. file read */
   
   int Afd, Bfd, Cfd;
   int p = atoi(argv[1]);
   args.p = p;
   
   Afd = Open(argv[2], O_RDONLY);
   Bfd = Open(argv[3], O_RDONLY); 
   Cfd = open(argv[4], O_WRONLY|O_CREAT, 0644);
   
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
   
   args.a = A;
   args.b = B;
   args.c = C;
   
   /* 2. Gaussian Elimination */
      
   pthread_t threads1[p];
   
   int rc;
   
   pthread_barrier_init(&barrier, NULL, p);
   
   for (int i=0;i<p;i++)
   {
       rc = pthread_create(&threads1[i], NULL, GaussianElimination, (void*)&args);
       assert(rc == 0);
   }
   
   for (int j=0;j<p;j++)
   {
       pthread_join(threads1[j], NULL);
   }
   
   /* 3. Back Substitution */
      
   pthread_t threads2[p];
      
   pthread_barrier_init(&barrier, NULL, p);
   
   t_index = 0;
   
   for (int k=0;k<p;k++)
   {
       rc = pthread_create(&threads2[k], NULL, BackSubstitution, (void*)&args);
       assert(rc == 0);
   }
   
   for (int q;q<p;q++)
   {
       pthread_join(threads2[q], NULL);
   }
   
   	
   /* 4. save file */
   Write(Cfd, &n1, sizeof(int));
   Write(Cfd, args.c, sizeof(float)*n2);

   free(args.a);
   free(args.b);
   free(args.c);
   
   close(Afd); close(Bfd); close(Cfd);
   
   return 0;
}

