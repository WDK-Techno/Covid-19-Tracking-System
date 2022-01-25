#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

int main(){
    
    time_t currentTime;      
    //remove \n from ctime()
    currentTime = time(NULL);
    char *c_time = ctime(&currentTime);
    c_time[strcspn(c_time, "\n")] = '\0'; //replace \0 instead of \n

   
    printf("\n%s dsfgdg\n",c_time);


    return 0;
}