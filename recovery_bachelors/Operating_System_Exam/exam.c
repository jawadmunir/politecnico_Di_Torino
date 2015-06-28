
/* write a C program:
a) A father must fork three sons(SonA, SonB, SonC)
b)SonA sends to SonB a string using pipe and exit.
c)SonB check if palindrome or pass to sonC.
d)SonC not able to recieve nothing from input in 3 seconds he exits
e)SonC after getting string has to reverse it.
f)SonB prints both original and the reversed one.and exit
g) father process wait for three children before exit.*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/errno.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<signal.h> // used for handler.
#include<time.h>
#define MAXLINE 100
#define N 30 
// father process
void handler(int signum )//  used for wait of 3 seconds.
{ 
kill(getpid(),SIGKILL);
}

int main()
{
pid_t pid_1,pid_2,pid_3;// for SonA, SonB, SonC
int check=0;// add a check to tell if string is palindrome or not.

int i,j,temp;
char revstr[N];
char string[N]="civic";// i took this one paticular example where i used a palindrome word civic to test my C program.
char b[N],revstring[N];
int status,ret,ret2,ret3,mypipe1[2],mypipe2[2],mypipe3[2];
pipe(mypipe1);
pipe(mypipe2);
pipe(mypipe3);

//  sonA
pid_1=fork();
if(pid_1==0)
{
//  only for sonA nothing special for father in this.
 write(mypipe1[1],string,strlen(string)+1);
 exit(0);// sonA exit okk 
}
// sonB
pid_2=fork();
if(pid_2==0)
{
//  only sonB
 ret=read(mypipe1[0],string,N);
 // Algorithm to find the palindrome. 
 strcpy(b,string);// copy from string to b

// reverse the string by taking care of null character.
 for(i=strlen(b)-1,j=0;i>=0;i--,j++)
    {
     revstr[j]=b[i];
     
    }
printf("reversed");
 revstr[j]='\0';
 if(strcmp(string,revstr)==0)// the string is palindrome
    {
      check++; // if palindrome do check++
    }
// the string is palindrome
 if(check>0)
    {
      printf("Palindrom string recieved\n");
      // print if palindrome
     }
 else
   {
     // not a palindrome
// SonB sends string  to SonC using a pipe
    write(mypipe2[1],string,strlen(string)+1);
    read(mypipe3[0],revstring,N);
    
   
   // printf("%s no2 \n",revstring);
   }
//printf("%s no1\n",string);
exit(0); //  we terminated sonB
}

// fork SonC
pid_3=fork();
if(pid_3==0)
{ //  sonC starts 
signal(sigalrm,handler);// register the signal handler for alarm signal.
alarm(3);
ret2=read(mypipe2[0],string,N);
  if(ret==-1)
  exit(0);
  else
     {// reverse the string
      revstring[ret2]=0;
      
      j=strlen(revstring)-1;
      i=0;
      while(i<j)
           {
            temp=revstring[i];
            revstring[i++]=revstring[j];
            revstring[j--]=temp;
           }
      write(mypipe3[1],revstring,strlen(revstring)+1);
      exit(0);
      }
} // sonC finished

// father Process agian.
waitpid(pid_1,&status,0);// to show that father dont die before sonA
waitpid(pid_3,&status,0);// to show that father dont die before sonC
waitpid(pid_2,&status,0);// to show that father dont die before sonB
exit(0);

}
