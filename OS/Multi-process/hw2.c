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

void GaussianElimination(int n, float A[], float b[], int p, pid_t pids[], int p2c[][2], int c2p[][2])
{
  int start, end, m;
  int data;
  int pi = p;
  pid_t id = getpid();
  
  for(int i=0;i<p;i++)
  {
     if (id == pids[i])
     {
        pi = i;
     }
  }
  

  for (int l=0;l<n-1;l++)
  {
      if (pi == p) // parent process
      {
        // sync child
	for(int k=0;k<p;k++)
            Read(c2p[k][0], &data, sizeof(data));
         
         for (int q=0;q<p;q++)
            Write(p2c[q][1], &data, sizeof(data));
         
      }
      else {
           m = n-l-1;
           start = (pi*m)/p+1+l;
           end = ((pi+1)*m)/p+l;
           for (int i=start;i<=end;i++){
               for (int j=1+l;j<=n-1;j++)
                   A[i*n+j] = A[i*n+j] - (A[i*n+l] / A[l*n+l]) * A[l*n+j];
               b[i] = b[i] - (A[i*n+l] / A[l*n+l]) * b[l];
           }
           // sync parent
           Write(c2p[pi][1], &data, sizeof(data));
           Read(p2c[pi][0], &data, sizeof(data));
      }
  }
}


void BackSubstitution(int n, float a[], float b[], float x[], int p, pid_t pids[], int p2c[][2], int c2p[][2]) {
  int start, end;
  int data;
  int pi = p;
  
  pid_t id = getpid();

  for(int i=0;i<p;i++)
  {
     if (id == pids[i])
     {
        pi = i;
     }
  }
  
  for (int i=n-1; i>=0;i--) 
  {
      x[i] = b[i] / a[i*n+i];
      if (pi == p) // parent process
      {  
         // sync child
         for (int k=0;k<p;k++)
            Read(c2p[k][0], &data, sizeof(data));
         
         for (int q=0;q<p;q++)
            Write(p2c[q][1], &data, sizeof(data));
      }
      else
      {
         start = (pi*i)/p;
         end = ((pi+1)*i)/p;
         for (int j=start;j<end;j++)
         {
             b[j] = b[j] - (x[i]*a[j*n+i]);
             a[j*n+i] = 0;
         }
         // sync parent
         Write(c2p[pi][1], &data, sizeof(data));
         Read(p2c[pi][0], &data, sizeof(data));
      }
  }
}

int main(int argc, char *argv[])
{
   //struct timespec s, sg, sb, e, eg, eb; 
   
   //clock_gettime(CLOCK_REALTIME, &s);
   
   if (argc !=5){
      printf("Usage : %s [number] [fileA] [fileB] [fileC]\n", argv[0]);
      return 1;
   }
   
   /* 1, 3 file read, share memory  */
   
   int Afd, Bfd, Cfd;
   int p = atoi(argv[1]);
   
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
   
   int fd = shm_open("/sm", O_CREAT | O_RDWR , 0666);
   int size = n1*n1*sizeof(float) + 2*n1*sizeof(float);
   
   ftruncate(fd, size);
   float *a = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
   float *b = (a+n1*n1);
   float *c = (b+n1);

   Read(Afd, a, sizeof(float)*n1*n1);
   Read(Bfd, b, sizeof(float)*n1);
   
   /* 2. make child process */
   
   pid_t pid;
   pid_t pids[p];
   
   pid_t p2c[p][2];
   pid_t c2p[p][2];
   
   int pi;
   
   for (int i=0;i<p;i++)
   {
       pipe(p2c[i]);
       pipe(c2p[i]);
   }
   
   for (pi=0;pi<p;pi++)
   {
      pid = fork();
      if (pid == 0) // child process
      {
          pids[pi] = getpid();
          break;
      }
      else if (pid < 0)
      {
          printf("fork error");
          exit(1);
      }
      
   }
   
   /* 4. Gaussian Elimination */
   //clock_gettime(CLOCK_REALTIME, &sg);
   
   GaussianElimination(n1, a, b, p, pids, p2c, c2p);
   
   //clock_gettime(CLOCK_REALTIME, &eg);
   
   /* 5. Back Substitution */
   //clock_gettime(CLOCK_REALTIME, &sb);
   
   BackSubstitution(n1, a, b, c, p, pids, p2c, c2p);
   
   //clock_gettime(CLOCK_REALTIME, &eb);
   
   /* 6. Terminate child processes */
   if(pi<p)
    	exit(1);
    	
   /* 7. save file */
   Write(Cfd, &n1, sizeof(int));
   Write(Cfd, c, sizeof(float)*n2);
   
   munmap(a, n1*n1*sizeof(float));
   munmap(b, n1*sizeof(float));
   munmap(c, n1*sizeof(float));
   
   close(Afd); close(Bfd); close(Cfd);
   
   //clock_gettime(CLOCK_REALTIME, &e);
   
   //double programtime = (double)((double)(e.tv_sec - s.tv_sec) + (double)(e.tv_nsec - s.tv_nsec)/1000000000);
   //double Gausstime = (double)((double)(eg.tv_sec - sg.tv_sec) + (double)(eg.tv_nsec - sg.tv_nsec)/1000000000);
   //double Backsubtime = (double)((double)(eb.tv_sec - sb.tv_sec) + (double)(eb.tv_nsec - sb.tv_nsec)/1000000000);
   
   //printf("GaussianElimination Time : %f\n", Gausstime);
   //printf("Backsubstitution Time : %f\n", Backsubtime);
   //printf("Total Time(Gaussian + Backsub) : %f\n", Gausstime + Backsubtime);   
   //printf("Total Time(program) : %f\n", programtime);   
   
   return 0;
}

