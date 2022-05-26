#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <time.h>

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

void Gaussian(int n, float A[][n], float b[])
{
    for (int l=0;l<=n-2;l++)
  {
      for (int i=l+1;i<=n-1;i++)
      {
          for (int j=1+l;j<=n-1;j++)
          {
              A[i][j] = A[i][j] - (A[i][l] / A[l][l]) * A[l][j];
          }
          b[i] = b[i] - (A[i][l] / A[l][l]) * b[l];
      }
  }
}

void BackSubstitution(int n, float A[][n], float b[], float x[])
{
  //DisplayAmatrix(n, A);
  for (int i=n-1;i>=0;i--)
  {
     x[i] = b[i] / A[i][i];
     for (int j=0;j<=i-1;j++)
     {
        b[j] = b[j] - x[i] * A[j][i];
        A[j][i] = 0;
     }
  }
}

int main(int argc, char *argv[])
{
   struct timespec start;
   
   clock_gettime(CLOCK_REALTIME, &start);
   
   if (argc !=4){
      printf("Usage : %s [fileA] [fileB] [fileC]\n", argv[0]);
      return 1;
   }
   
   /* file open  */
   
   int Afd, Bfd, Cfd;
   
   Afd = Open(argv[1], O_RDONLY);
   Bfd = Open(argv[2], O_RDONLY); 
   Cfd = open(argv[3], O_WRONLY|O_CREAT, 0644);
   
   if (Cfd < 0)
   {
       fprintf(stderr, "open error.\n");
       exit(1);
   }
   
   /* file read  */
   int n1, n2;
   
   Read(Afd, &n1, sizeof(n1));
   Read(Bfd, &n2, sizeof(n2));
   
   if (n1 != n2)
   {
      printf("The values of n are different.\n");
      exit(1);
   }
   
   float Amat[n1][n1];
   float bmat[n2];
   float x[n2];

   for (int i=0; i<n1; i++)
   {
       memset(Amat[i], 0x00, sizeof(float)*n1);
   }
   
   memset(bmat, 0x00, sizeof(float)*n2);
   memset(x, 0x00, sizeof(float)*n2);
   
   /* one by one
   for (int i=0;i<n1;i++)
   {
       for (int j=0;j<n1;j++)
           Read(Afd, &Amat[i][j], sizeof(float));
   } */
   
   /* whole
   Read(Afd, Amat, sizeof(float)*n1*n1);
   */
   
   /* row */
   for (int i=0;i<n1;i++)
   {
       Read(Afd, Amat[i], sizeof(float)*n1);
   }
   Read(Bfd, bmat, sizeof(float)*n2);
   
   /* solve a simultaneous equations  */
   
   Gaussian(n1, Amat, bmat);
   BackSubstitution(n1, Amat, bmat, x);
   
   /* file write  */
   Write(Cfd, &n1, sizeof(int));
   Write(Cfd, x, sizeof(float)*n2);
 
   close(Afd); close(Bfd); close(Cfd);
   
   struct timespec end;
   clock_gettime(CLOCK_REALTIME, &end);
   
   printf("time=%09ld.%09ld\n", end.tv_sec - start.tv_sec, end.tv_nsec - start.tv_nsec);

   return 0;
}
