/* this is the program using strtok Library function in order to seperate the time format into hours minutes and seconds.
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.h>
struct athlete{
					int id;// for athlete id
					char hour;
					char min;
					char sec;
					char time[15];// array to read time format
					struct athlete *nextList;
					}Athlete;
typedef struct athlete *ATHLETEPNT;
ATHLETEPNT headList= NULL;
void Ranking(ATHLETEPNT , int);
void printascendingorder();// never used this fuction
void swap();// never used this one
void output();// never used this one
int main()
{
	 char buffer[40];
	 int control,counter=0;
	 char *a, *b ,*c;
	 FILE *fp;
	 ATHLETEPNT   athleteList; //tempPnt;
	 printf(" \n\n******************************************************\n");
	 printf(" *             RANKING OF RACE                          *\n");
	 printf("******************************************************\n\n\n");
	 do
	 {
				 control=0;
	 if((fp= fopen("race.txt","r"))==NULL)
	 {
			printf("file could not open\n");
			control=1;
			}
	 else{
			 printf("the read file is as \n\n");
	   printf("<Athlete id> \t <Arrival time>\n");
             headList=NULL;
	 while(fgets(buffer,39,fp)!=NULL)
	 {
	 athleteList=(ATHLETEPNT)malloc(sizeof(struct athlete));
	 
	 sscanf(buffer,"%d %s",&athleteList->id,athleteList->time);


		athleteList->nextList=headList;
		headList=athleteList;
		counter++;
		//printf(" the time : %s ",athleteList->time);
		
		a=strtok(athleteList->time,":" );
		b=strtok(NULL,":" );
		c=strtok(NULL,":" );
		//printf(" a= %s b=%s c=%s ",a,b,c);
		athleteList->hour=atoi(a);
		athleteList->min=atoi(b);
		athleteList->sec=atoi(c);
		printf("\t %d \t %+d:%02d:%02d \n",athleteList->id,athleteList->hour,athleteList->min,athleteList->sec);
		
					}//end while
			}// end else
			Ranking(headList , counter);// fuction call



  system("PAUSE");

}while(control);
 return 0;
}
void Ranking(ATHLETEPNT headList, int counter)
{
     int Atime[counter]; // array for time in seconds
     int aid[counter]; // array for athlete id
      int h[counter]; 
	 int delay[counter];
	 ATHLETEPNT athleteList;
	 int n=0,HOUR=0,MIN=0,SEC=0,pass,i,hold=0,t=0;

for(athleteList=headList;athleteList!=NULL && n<counter;athleteList=athleteList->nextList)
     {
                        HOUR=(athleteList->hour)*60*60;
                        MIN=(athleteList->min)*60;
                        SEC=athleteList->sec;
                        Atime[n]=HOUR+MIN+SEC;// total time in seconds
                        aid[n]=athleteList->id;
                         n++;
                         }
                        // sorting  
     for(pass=1,athleteList=headList;athleteList!=NULL && pass<counter;athleteList=athleteList->nextList,pass++){
         for(i=0;i<counter-1;i++){
                                  if(Atime[i]>Atime[i+1]){
                                                          // swap
                                                          hold=Atime[i];
                                                          Atime[i]=Atime[i+1];
                                                          Atime[i+1]=hold;
                                                          t=aid[i];
                                                          aid[i]= aid[i+1];
                                                          aid[i+1]=t;                            
                                                          }// end if
                                                          
                                                          }// end inner for
                                  h[0]=Atime[0];                                                
          } // end outer for 
         for(i=0;i<counter-1;i++){
         delay[i]=Atime[i+1]-Atime[0];
         h[i+1]=delay[i];
         }
         // converting seconds back to HH:MM:SS 
         for(i=0;i<counter;i++){
         SEC=h[i]%60;
         MIN=(h[i]/60)%60;
         HOUR=h[i]/3600;
    printf("\n\n %d \t %+d:%02d:%02d \n",aid[i],HOUR,MIN,SEC);
         }
         }
         

