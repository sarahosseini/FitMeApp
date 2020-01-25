#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
//include header file

#define MAX_NAME_LEN 50
//calories burnt function
//distance travelled - height
//average speed


char name[MAX_NAME_LEN];
int age;
int weight; //change to floating point later
int height; //height in centimeters
char sex;


void getUserInfo();
void strWrk(void);


int main(){
    
    char stwrk;
    
    //display main page - hello
    
    printf("Hello! Welcome to FitMe by RPS.Co.\nOur goal is to make sure you become the person you want to become by getting the body you want.\nTo ensure this, we need to ask a few questions first.\n");
    
    //go to function to input information
    getUserInfo();
    
    //ask if they want to see progress or start working out
    printf("Would you like to start working out now, or just see your progress?\nClick y to start working out\n");
    scanf("%c", &stwrk);
    
    if (stwrk == 'y'){
        //call function to start workout;
        strWrk();
    }
    
}

void strWrk(void){
    
    double casualWalk;
    
    double caloriePerStep;
    
    double calories;
    
    int steps;
    
    char stopWkt;
    
    time_t startTime;
    
    time_t endTime;
    
    startTime = time(NULL);
    
    sleep(5);
    
    printf("Are you done your workout? Enter 'y' if you are\n");
    
    //scanf("%c", &stopWkt);
    
    //if (stopWkt == 'y'){
        
        srandom((unsigned)&endTime);
        
        steps = (random()%10000);
        
        casualWalk = weight * 0.57; //per mile
        
        caloriePerStep = casualWalk / steps;
        
        calories = caloriePerStep * steps;
        
         endTime = time(NULL);
        
        printf("%ld\n", endTime - startTime);
    
    printf("For the casual walk that you made : \n");
    printf("Steps taken : %d\n", steps);
    
    printf("Calories burned : %f\n", calories);
    
   
    
    
}




void getUserInfo(void){
    
    FILE *fp;
    
    //validate the answers - for all
    
    printf("Register your first name\n");
    scanf("%s", name);
    
    printf("Enter your age\n");
    scanf("%d", &age);
    
    printf("Enter you weight (in pounds)\n");
    scanf("%d", &weight);
    
    printf("Enter you height (in cms)");
    scanf("%d", &height);
    
    printf("Enter your gender : f for female and m for male\n");
    scanf("%c", &sex);
    
    
    //open and save in file
    fp = fopen("UserInfo.txt", "w");
    
    if (fp == NULL){
        printf("ERROR - Cannot open file\n");
        return;
    }
    
    fprintf(fp, "%s\n", name);
    fprintf(fp, "%d\n", age);
    fprintf(fp, "%d\n", weight);
    fprintf(fp, "%d\n", height);
    fprintf(fp, "%c\n", sex);
    
    fclose(fp);
    
    printf("Hello %s, let's get started", name);
    return ;
    
}
