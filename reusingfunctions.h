#include <stdio.h>
#include <string.h>

 void selectDivisions(char* str){
     int ans;
    char devisions[11][11]={"Palapoluwa", "Arandara", "Kobbewala", "Hathnagoda", "Pindeniya", "Yattogoda", "Nawagamuwa", "Dewalegama", "Bisowela", "Ballapana"};
    for(int i=0;i<10;i++){
        printf("\t\t\t[%d] - %s\n",i+1,devisions[i]);
    }
    printf("\n");
    while (1)
    {
        printf("Answer : ");
        scanf("%d",&ans);
        if (ans>=1 && ans<=10){
            break;
        }
        printf("\t\tINVALID INPUT..!\tTry Again\n");
    }   
    //return string value
    strcpy(str, devisions[ans-1]);      
}

void selectJobRoles(char* str){
    int ans;
   char jobroles[5][16]={"PHI", "Police", "Grama Niladhari", "Other"};
   for(int i=0;i<4;i++){
        printf("\t\t\t[%d] - %s\n",i+1,jobroles[i]);
    }
    printf("\n");  
    while (1)
    {
        printf("Answer : ");
        scanf("%d",&ans);
        if (ans>=1 && ans<=4){
            break;
        }
        printf("\t\tINVALID INPUT..!\tTry Again\n");
    }    
    //return string value
    strcpy(str, jobroles[ans-1]);   
}

void selectPlaceTypes(char*  str){
    int ans;
   char placetypes[9][16]={"Bank", "Restaurant", "Grocery", "Supermarket", "Liquor shop", "Pharmacy", "Textile shop", "Saloon"};
   for(int i=0;i<8;i++){
        printf("\t\t\t[%d] - %s\n",i+1,placetypes[i]);
    }
    printf("\n");  
    while (1)
    {
        printf("Answer : ");
        scanf("%d",&ans);
        if (ans>=1 && ans<=8){
            break;
        }
        printf("\t\tINVALID INPUT..!\tTry Again\n");
    }    
    //return string value
    strcpy(str, placetypes[ans-1]);   
}

