#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "reusingfunctions.h"

typedef struct person{
    char name[50],id[13],pass[6],gnDev[11],jbRole[16],wrkDev[11],tel[11],vaci[4];
    int age;
    
}personDict;

typedef struct place{
    char name[50],userName[30],plctype[16],pass[6],location[11];
    int empCount;

}placeDict;

typedef struct workplace{
    char id[13];
    char placeUsername[20];
}workplaceDict;

typedef struct data{
    char name[50],id[13],pass[6],gnDev[11],jbRole[16],wrkDev[11],tel[11],
    vaci[4],placeName[50],placeUsername[20],location[11],plctype[16];
    int age,empCount;

}fullDataDict;

typedef struct tracking{
    char time[30],id[13],placename[50],username[20],placetype[16],location[11];
}trackingDict;

//Strcuture variable arrays
personDict personVal[1000];
placeDict placeVal[1000];
workplaceDict workVal[1000];
fullDataDict dataval[1000];
trackingDict trackVal[1000];

//Main Functions
void regPerson();
void regPlace();
void PHI();
void tracking();

//update structures functions
void updatePersonDict();
void updatePlaceDict();
void updateWorkPlaceDict();
void updateFullDataDict();
void updatetrackingDict();

//special functions 
int count_lines(char csvfile[20]);
int stringcompare(char *a,char *b);
void drawLines();

//check Position functions
int checkWorkPosition(char id[20]);
int checkPersonPosition(char id[20]);
int checkPlacePosition(char id[20]);

//Refresh
void refresh(){
    updatePersonDict();
    updatePlaceDict();
    updateWorkPlaceDict();
    updatetrackingDict();
    updateFullDataDict();
    
}

int main()
{
    system("cls");
    //refresh data from databases
    refresh();
    //Print Banner
    banner();
    
    printf("\n\nSelect :=> \n");
        printf("\t\t\t[1] - Person Registration\n");
        printf("\t\t\t[2] - Place Registration\n");        
        printf("\t\t\t[3] - Place System Login\n");
        printf("\t\t\t[4] - PHI System Login\n");
        printf("\t\t\t[5] - System Exit\n");

    int mainSelect;
    char temp;
    printf("\nAnswer : ");
    scanf("%d",&mainSelect);
    scanf("%c",&temp); //get temp character "\n"
    
    system("cls");
    banner();

    switch(mainSelect){
        
        case 1 :
            regPerson();
            main();
            break;
        case 2 :
            regPlace();
            main();
            break;
        case 3 :
            tracking();
            main();
            break;
        case 4 :
            PHI();
            main();
            break;
        case 5 :
            return 0;
            break;
        default :
            printf("\n\t\tInvalid Input..! Try Again.\n\n");
            main();
            break;
    }
    return 0;
}

//Tracking 
void tracking(){
    char user[13], pass[6];
    int place_p = 0;
    

    //system login
    while(1){
        
        system("cls");
        banner();
        printf("\n\t\t\t\t[@]-Place System Login-[@]\n\n");
        refresh();

        printf("\nUsername : ");
            scanf("%s",user);
            printf("Password : ");
            scanf("%s",pass);

        place_p =  checkPlacePosition(user); //in here,if checkplace functions couldn't find usesr name it will return -1

        // printf("\n%d\n",place_p);
        // printf("\n%s\n",placeVal[place_p].userName);
        // printf("\n%s\n",placeVal[place_p].pass);

        if((place_p!=-1)&&(strcmp(placeVal[place_p].pass,pass)==0)){
            printf("\nLogin Complete\n");
            break;
        }
        system("cls");
        banner();
        printf("\n\t\t\t\t[@]-Place System Login-[@]\n\n");

        printf("\n\t\tIncorrect user name or password.. Try again!\n\n");
    }

    system("cls");
    banner();
    printf("\n\t\t\t\t[@]-Customer Attendence-[@]\n\n");

    printf("\n\t\t**Enter 0 for exit system**\n\n");
    //get customer id
    while(1){
        char customerTD[13];
        printf("Customer ID : ");
        scanf("%s",customerTD);

        if(strcmp(customerTD,"0")==0){
            printf("\n\t\tSystem Exit\n\n");
            break;
        }

        //check customer id in the person database
        int e = checkPersonPosition(customerTD);
        if (e!=-1){
            //get current date and time
            time_t currentTime;
        
            //remove \n from ctime()
            currentTime = time(NULL);
            char *c_time = ctime(&currentTime);
            c_time[strcspn(c_time, "\n")] = '\0'; //replace \0 instead of \n

            
            //write to the CSV
            FILE* fp = fopen("trackingDatabase.csv", "a+");
                if (!fp) {
                        // Error in file opening
                        printf("Can't access Database\n");
                    }
                fprintf(fp,"\n%s,%s,%s,%s,%s,%s",c_time,customerTD,placeVal[place_p].name,placeVal[place_p].location,placeVal[place_p].plctype,placeVal[place_p].userName);
                printf("\n\t\tCompleted..\n\n");

                fclose(fp);
        }
        else if (e==-1){
            system("cls");
            banner();
            printf("\n\t\t\t\t[@]-Customer Attendence-[@]\n\n");
            
            printf("\n\t\tInvalid ID. This ID not in the system\n\n");
        }
    }
}

//PHI
void PHI(){
    char id[13], pass[6];
    int PHI_Val=0;
    printf("\n\t\t\t\t[@]-PHI System Login-[@]\n\n");
    
    int lineCount = count_lines("personDatabase.csv");
    updatePersonDict();
    //System Loggin
    while(1){

        printf("\nID : ");
        scanf("%s",id);
        printf("Password : ");
        scanf("%s",pass);

        int check1 =0;
        for (int d=0; d<lineCount; d++){
            if((strcmp(personVal[d].id,id)==0) && (strcmp(personVal[d].pass,pass)==0) && (strcmp(personVal[d].jbRole,"PHI")==0)){
                check1=1;
                PHI_Val = d;
            }
        }
        
        if (check1==1){
            break;
        }
        
        system("cls");
        banner();
        printf("\n\t\t\t\t[@]-PHI System Login-[@]\n\n");

        printf("\n\t\t\tIncorrect user name or password.. Try again!\n\n");
    }
    
    
    int run=1;
    while(run){
        
        system("cls");
        banner();
        printf("\n\t\t\t\t   [@]-PHI System-[@]\n\n");

        printf("\nSelect :=> \n");
        printf("\t\t\t[1] - Residents Details\n");
        printf("\t\t\t[2] - Tracking Details\n");        
        printf("\t\t\t[3] - Main Menu\n");
    
        int ans3;
        printf("\nAnswer : ");
        scanf("%d",&ans3);

        system("cls");
        banner();
        printf("\n\t\t\t\t[@]-Residents Details-[@]\n\n");

        //Residents Details (****)
        if(ans3 == 1){
            printf("\n\nResidents Details :=>\n");
            printf("\t\t\t[1] - All Residents\n");
            printf("\t\t\t[2] - One Resident\n");

            int ans1;
            printf("\nAnswer : ");
            scanf("%d",&ans1);

            system("cls");
            banner();
            printf("\n\t\t\t\t[@]-All Residents Details-[@]\n\n");

            printf("\n\nPHI Working Devision : %s\n\n",personVal[PHI_Val].wrkDev);
            
            
            if (ans1 == 1){
                //using this function print details of particular grama niladhari's working devision's residents
            
                for(int d=0;d<lineCount;d++){
                    
                    if(stringcompare(personVal[PHI_Val].wrkDev,personVal[d].gnDev)==0){
                        
                        //print line sperater
                        drawLines();
                        //print values
                        printf("\nName : %s\t ID : %s\t Age : %d\t Tel : %s\nVacination : %s\t GN Div : %s\n\nWork Place : %s\t Location : %s\t Type : %s\t Employee Count : %d\n",dataval[d].name,dataval[d].id,dataval[d].age,dataval[d].tel,dataval[d].vaci,dataval[d].gnDev,dataval[d].placeName,dataval[d].location,dataval[d].plctype,dataval[d].empCount);
                        
                    }
                }
                //draw line below last row
                drawLines();
                printf("\n"); 
            }
            if (ans1 == 2){
                char R_ID[13];
                int wh=0;
                while(1){
                    
                    system("cls");
                    banner();
                    printf("\n\t\t\t\t[@]-One Resident Details-[@]\n\n");

                    printf("\nEnter Resident ID : ");
                    scanf("%s",R_ID);
                    
                    int n = checkPersonPosition(R_ID);
                    if ((n!=-1) && (stringcompare(dataval[n].gnDev,dataval[PHI_Val].wrkDev)==0)){
                    
                        //print line sperater
                        drawLines();
                        //print values
                        printf("\nName : %s\t ID : %s\t Age : %d\t Tel : %s\nVacination : %s\t GN Div : %s\n\nWork Place : %s\t Location : %s\t Type : %s\t Employee Count : %d\n",dataval[n].name,dataval[n].id,dataval[n].age,dataval[n].tel,dataval[n].vaci,dataval[n].gnDev,dataval[n].placeName,dataval[n].location,dataval[n].plctype,dataval[n].empCount);
                        //draw line below last row
                        drawLines();
                        printf("\n");
                        wh=1;
                        break; 
                    }
                    
                    if(wh==1){
                        break;
                    }
                    
                    system("cls");
                    banner();
                    printf("\n\t\t\t\t[@]-One Resident Details-[@]\n\n");

                    printf("\n\t\tInvalid ID..!\n");
                    printf("\n\nDo you Need Try Again :=>\n");
                    printf("\t\t\t[1] - YES\n");
                    printf("\t\t\t[2] - NO\n");

                    int ans2;
                    printf("\nAnswer : ");
                    scanf("%d",&ans2);
                    
                    if (ans2==2){
                    break;
                    }
                }
            }
        }


        //See Tracking Details (****) 
        if(ans3 == 2){
            char R_ID[13];    
            while(1){
                
                system("cls");
                banner();
                printf("\n\t\t\t\t[@]-Tracking Details-[@]\n\n");

                printf("\nEnter Resident ID : ");
                scanf("%s",R_ID);

                drawLines();
                drawLines();
                int n = checkPersonPosition(R_ID);
                
                if ((n!=-1) && (stringcompare(dataval[n].gnDev,dataval[PHI_Val].wrkDev)==0)){
                    
                    printf("\nName : %s\t ID : %s\t Age : %d\t Tel : %s\nVacination : %s\t GN Div : %s\n\nWork Place : %s\t Location : %s\t Type : %s\t Employee Count : %d\n",dataval[n].name,dataval[n].id,dataval[n].age,dataval[n].tel,dataval[n].vaci,dataval[n].gnDev,dataval[n].placeName,dataval[n].location,dataval[n].plctype,dataval[n].empCount);
                    drawLines();
                    drawLines();
                    printf("\n");
                    
                    printf("\t\t\t\t\t-Tracking Details-\n");
                    for(int i=0; i<=1000; i++){
                        
                        if(strcmp(trackVal[i].id,R_ID)==0){

                            //print line sperater
                            drawLines();
                            //print values
                            printf("\n%s\t place : %s\t Location : %s\t Type : %s\n",trackVal[i].time,trackVal[i].placename,trackVal[i].location,trackVal[i].placetype);
                        }
                    
                    }
                    //draw line below last row
                    drawLines();

                    printf("\n");
                    break;
                }

                system("cls");
                banner();
                printf("\n\t\t\t\t[@]-Tracking Details-[@]\n\n");


                printf("\n\t\tInvalid ID..!\n");
                printf("\n\nDo you Need Try Again :=>\n");
                printf("\t\t\t[1] - YES\n");
                printf("\t\t\t[2] - NO\n");

                int ans2;
                printf("\nAnswer : ");
                scanf("%d",&ans2);
                
                if (ans2==2){
                    break;
                }
        
            }
        
        }
        

        //system PHI exite
        if (ans3 == 3){
            break;
        }
        
        //system pause  
        system("pause");
    }
}

//update tracking Dict
void updatetrackingDict(){

    FILE *fp = fopen("trackingDatabase.csv","r");
    
    if (!fp){
            printf("Can't find file");
        }
    

    char buff[1000]; //store the first 1024 lines into buff
    int row_count = 0;
    int filed_count = 0;

    int i=0;
    while(fgets(buff,1000, fp))
    {
        //printf("%s\n", buff);
        filed_count =0;
        row_count++;
        if(row_count==1)
            continue;

        char *field = strtok(buff, ",");
        while (field)
        {   
            if(filed_count==0)
                strcpy(trackVal[i].time, field);
            if(filed_count==1)
                strcpy(trackVal[i].id, field);
            if(filed_count==2)
                strcpy(trackVal[i].placename, field);
            if(filed_count==3)
                strcpy(trackVal[i].location,field);    
            if(filed_count==4)
                strcpy(trackVal[i].placetype,field);
            if(filed_count==5)
                strcpy(trackVal[i].username, field);
            
            field = strtok(NULL, ",");
            filed_count++;
        }
        // printf("\n%s\n",trackVal[i].time);
        i++;
    }
    fclose(fp);

}

//update full Data Dcit
void updateFullDataDict(){
    for(int k=0; k<1000;k++){
        strcpy(dataval[k].id,personVal[k].id);
        strcpy(dataval[k].name,personVal[k].name);
        strcpy(dataval[k].pass,personVal[k].pass);
        strcpy(dataval[k].gnDev,personVal[k].gnDev);
        strcpy(dataval[k].jbRole,personVal[k].jbRole);
        strcpy(dataval[k].wrkDev,personVal[k].wrkDev);
        strcpy(dataval[k].tel,personVal[k].tel);
        strcpy(dataval[k].vaci,personVal[k].vaci);
        dataval[k].age = personVal[k].age;

        int p = checkWorkPosition(dataval[k].id); //check workplace dict to find place user_name of relevent user id
        int r = checkPlacePosition(workVal[p].placeUsername); //find position of relevant place_username

    
        strcpy(dataval[k].placeName,placeVal[r].name); //find place name using place_username
        strcpy(dataval[k].placeUsername,placeVal[r].userName);
        strcpy(dataval[k].location,placeVal[r].location);
        strcpy(dataval[k].plctype,placeVal[r].plctype);
        dataval[k].empCount=placeVal[r].empCount;

    }

}

//Read CSV to Person Dict
void updatePersonDict(){
    
    FILE *fp = fopen("personDatabase.csv","r");
  if (!fp)
    {
        printf("Can't find file");
    }

    char buff[1000]; //store the first 1024 lines into buff
    int row_count = 0;
    int filed_count = 0;

    int i=0;
    while(fgets(buff,1000, fp))
    {
        //printf("%s\n", buff);
        filed_count =0;
        row_count++;
        if(row_count==1)
            continue;

        char *field = strtok(buff, ",");
        while (field)
        {
            if(filed_count==0)
                strcpy(personVal[i].name, field);
            if(filed_count==1)
                strcpy(personVal[i].id, field);
            if(filed_count==2)
                strcpy(personVal[i].pass, field);
            if(filed_count==3){
                int cfield = atoi(field);
                personVal[i].age = cfield;
            }
            if(filed_count==4)
                strcpy(personVal[i].tel, field);
            if(filed_count==5)
                strcpy(personVal[i].vaci, field);
            if(filed_count==6)
                strcpy(personVal[i].gnDev,field);
            if(filed_count==7)
                strcpy(personVal[i].jbRole,field);
            if(filed_count==8)
                strcpy(personVal[i].wrkDev,field);

            field = strtok(NULL, ",");
            filed_count++;
        }
        i++;
    }
    fclose(fp);

    //printValues(values,count);
}

//Update Work Place Dict from place database
void updateWorkPlaceDict(){
    FILE *fp = fopen("placeDatabase.csv","r");
    if (!fp)
    {
        printf("Can't find file");
    }
    //find line count
    //int count= count_lines("personDatabase.csv");


    char buff[1000]; //store the first 1024 lines into buff
    int row_count = 0;
    int filed_count = 0;

    //personDict values[1000]; //array to structs to store values

    int i=0;
    while(fgets(buff,1000, fp)){
        char username[20],id[13];
        int empCount=0;
        //printf("%s\n", buff);
        filed_count =0;
        row_count++;
        if(row_count==1)
            continue;

        char *field = strtok(buff, ",");
        while (field){
            int found = 0;
            if (filed_count == 1) {
            
                strcpy(username,field);
            }
            if (filed_count == 5){
                empCount = atoi(field);

            }
            if((filed_count > 5) && (filed_count <= (5+empCount))){
                strcpy(id,field);
                found = 1;
            }
            field = strtok(NULL, ",");
            filed_count++;
            
            if(found == 1){
                // drawLinesM();
                // //print values
                // printf("\nID : %s\t User Name : %s\n",id,username);
                strcpy(workVal[i].id,id);
                strcpy(workVal[i].placeUsername,username);
                i++;
            }
        }
        
    }
    fclose(fp);

}

//Update CSV to Place Dict
void updatePlaceDict(){
    FILE *fp = fopen("placeDatabase.csv","r");
  if (!fp)
    {
        printf("Can't find file");
    }
    //find line count
    //int count= count_lines("personDatabase.csv");


    char buff[1000]; //store the first 1024 lines into buff
    int row_count = 0;
    int filed_count = 0;

    //personDict values[1000]; //array to structs to store values

    int i=0;
    while(fgets(buff,1000, fp))
    {
        //printf("%s\n", buff);
        filed_count =0;
        row_count++;
        if(row_count==1)
            continue;

        char *field = strtok(buff, ",");
        while (field)
        {
            if(filed_count==0)
                strcpy(placeVal[i].name, field);
            if(filed_count==1)
                strcpy(placeVal[i].userName, field);
            if(filed_count==2)
                strcpy(placeVal[i].pass, field);
            if(filed_count==3)
                strcpy(placeVal[i].plctype, field);
            if(filed_count==4)
                strcpy(placeVal[i].location, field);
            if(filed_count==5){
                int empcount = atoi(field);
                placeVal[i].empCount = empcount;
            }
            
            field = strtok(NULL, ",");
            filed_count++;
        }
        i++;
    }
    fclose(fp);
}

//Count line numbers in CSV file
int count_lines(char csvfile[20]){

FILE *fp = fopen(csvfile,"r");
  if (!fp)
    {
        printf("Can't find file");
        return 0;
    }
    int count = 0;
     char c;
     for (c = getc(fp); c != EOF; c = getc(fp)){
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;}
    //printf("count of lines : %d\n\n", count);
    fclose(fp);
    return count;
}

//Draw LInes in Main.c
void drawLines(){
    for(int k=0;k<110;k++){
            printf("_");}
        printf("\n");
}

// Comparing both the strings using pointers  
int stringcompare(char *a,char *b) {
   int flag=0;  
    while(*a!='\0' && *b!='\0')  // while loop 
    {  
        if(*a!=*b){  
            flag=1;  
        }  
        a++;  
        b++;  
    }  
      
    if(flag==0)  
    return 0;  
    else  
    return 1;  
}  

//Registration of Persons
void regPerson(){
    char name[50],id[13],pass1[6],pass2[6],gnDev[11],jbRole[16],wrkDev[11],tel[11];
    int age,vaci;

    system("cls");
    banner();
    printf("\t\t\t       [@]-Person Registration-[@]\n\n");
    //name
   printf("Name : ");
   scanf("%[^\n]s",name);
    
    //ID
   while(1){
        printf("ID : ");
        scanf("%s",id);

        int s = checkPersonPosition(id);
        if (s!=-1){
        printf("\t\t\n*This is user is already in the system*\n\n");
    
        }
       else if(strlen(id)==10){
           if(id[9]=='v'||id[9]=='V'){
               int findAlpha=0;
               for(int i=0;i<9;i++){
                   if(isalpha(id[i]))
                       findAlpha=1;
               }
               if (findAlpha!=1)
                   break;
           }

       }else if(strlen(id)==12){
               int findAlpha=0;
               for(int i=0;i<12;i++){
                   if(isalpha(id[i]))
                       findAlpha=1;
       }if (findAlpha!=1)
                   break;
       }
       printf("\t\t\tInvalid ID! Re-Enter\n");
   }
   
   //pasword
   printf("\t\tEnter password (*password should be contain 5 character*)\n");
   while(1){

   printf("Password : ");
   scanf("%s",pass1);
   printf("Re-Enter Password : ");
   scanf("%s",pass2);
   if((strcmp(pass1,pass2))==0 && strlen(pass1)==5){
       break;}
       printf("\t\t\tInvalid Password! Re-Enter\n");
   }
   //Age
    while(1){
        printf("Age : ");
        scanf("%d",&age);
        if(age>=15 && age<100)break;
        
        printf("\t\tINVALID INPUT..!\tRe-Enter\n");   
    }

    //Telephone Numebr
    while(1){
        printf("Tel No : ");
        scanf("%s",tel);
        if(strlen(tel)==10){
            int findAlpha=0;
               for(int i=0;i<10;i++){
                   if(isalpha(tel[i]))
                       findAlpha=1;
               }
               if (findAlpha!=1)
                   break;
        }
        printf("\t\tINVALID INPUT..!\tRe-Enter\n"); 
    }
   //Vacination Status
    char vaciF[3][10]={"no","yes"};
    printf("\nVaccination Status :=> \n");
    printf("\t\t[1] - Yes\n\t\t[0] - No\n");
    while (1)
    {
        printf("Answer : ");
        scanf("%d",&vaci);
        if (vaci==1 || vaci==0)break;
        printf("\t\tINVALID INPUT..!\tRe-Enter\n");
    }    

    //select devision
    printf("\nSelect your division :=> \n");
    selectDivisions(gnDev);

    //select jobrole
    printf("\nSelect your Jobrole :=> \n");
    selectJobRoles(jbRole);

        //if PHI --> get his Working Deivision
        if(strcmp(jbRole,"PHI")==0){
            printf("\nSelect your working division :=> \n");
            selectDivisions(wrkDev);
        }else strcpy(wrkDev, "None");

    printf("\n%s\t%s\t%s\t%d\t%s\t%s\t%s\t%s\t%s\n\n",name,id,pass1,age,tel,vaciF[vaci],gnDev,jbRole,wrkDev);
    //write to the CSV
    FILE* fp = fopen("personDatabase.csv", "a+");
        if (!fp) {
                // Error in file opening
                printf("Can't access Database\n");
            }
        fprintf(fp,"\n%s,%s,%s,%d,%s,%s,%s,%s,%s",name,id,pass1,age,tel,vaciF[vaci],gnDev,jbRole,wrkDev);
        printf("Registration completed..\n\n");

        fclose(fp);

}

//Registration of places
void regPlace(){
    char name[50],userName[30],plctype[16],pass1[6],pass2[6],location[11],empID[100][13];
    int empCount,reg;
    system("cls");
    banner();
    printf("\t\t\t       [@]-Place Registration-[@]\n\n");
    refresh();
    printf("\n");
 //place name
   printf("Name : ");
   scanf("%[^\n]s",name);
    
//place user name
    printf("\n\t\tCreate User Name [*don't use space*]\n");
    while(1){
        char temp;
        printf("User Name : ");
        scanf("%c",&temp); // temp statement to clear buffer
        scanf("%[^\n]s",userName);
       
        
        //check existing user name in place database
        int findspace=0;
        for(int i=0;i<strlen(userName);i++){
            if(isspace(userName[i]))
                findspace = 1;
        }
        int r=checkPlacePosition(userName);
            if (r==-1){

                if (findspace!= 1){
                    break;
                }else{ 
                    printf("\t\t\t*Invalid username! Re-Enter without space*\n");
                }
                
            }else printf("\n\t\t!!Error *This user name already used. Enter new user name*\n");
        
            
    
    }
//password
   printf("\n\t\tEnter password (*password should be contain 5 character*)\n");
   while(1){
   printf("Password : ");
   scanf("%s",pass1);
   printf("Re-Enter Password : ");
   scanf("%s",pass2);
   if((strcmp(pass1,pass2))==0 && strlen(pass1)==5){
       break;}
    printf("\t\t\tInvalid Password! Re-Enter\n");
   }

//place type
    printf("\nSelect place type :=> \n");
    selectPlaceTypes(plctype);
    
//place Location
    printf("\nSelect place location :=> \n");
    selectDivisions(location);
    
//employee count
    printf("\nCount of employees : ");
    scanf("%d",&empCount);

//collect employee IDs
    printf("\nEnter employees NIC Numbers one by one => \n");
    int i=0;
    while (i<empCount)
    {
        printf("\n\t\t[%d] employee NIC : ",i+1);
        scanf("%s",empID[i]);
        int s=checkPersonPosition(empID[i]);

        if (s!=-1){
            i++;
        }
        else {
            printf("\n\t!!Error. *This employee not registered in the system*\n");
            printf("\nDo you like to register him first :=> \n");
            printf("\t\t[1] - Yes\n\t\t[0] - No\n");
            while (1)
            {
                printf("Answer : ");
                scanf("%d",&reg);
                if (reg==1 || reg==0)break;
                printf("\t\tINVALID INPUT..!\tRe-Enter\n");
            }
            if (reg==1){
                char temp1;
                scanf("%c",&temp1); // temp statement to clear buffer
                regPerson();
                printf("\n\n\t\t*Back to the place registration*\n");
            }  
        }

    }
    
    FILE* fp = fopen("placeDatabase.csv", "a+");
    if (!fp) {
            // Error in file opening
            printf("Can't access Database\n");
        }
    ///write to csv
    fprintf(fp,"\n%s,%s,%s,%s,%s,%d",name,userName,pass1,plctype,location,empCount);
    //print 
    printf("\n%s\t%s\t%s\t%s\t%s\t%d",name,userName,pass1,plctype,location,empCount);
    
    //employee IDs
    for (int d = 0; d < empCount; d++)
    {   
        fprintf(fp,",%s",empID[d]); //write to csv
        printf("\t%s",empID[d]); //print
    }
    int end = 0;
    fprintf(fp,",%d",end);
    fclose(fp); 
    printf("\n");
    printf("Registration completed..\n\n");




}

//check position from Work Place Dict
int checkWorkPosition(char id[20]){
   
   for(int i=0;i<1000;i++){
        if(strcmp(id,workVal[i].id)==0){
            return i;
        }
   }
}

//check position from Person Dict
int checkPersonPosition(char id[20]){
   
   for(int i=0;i<1000;i++){
        if(strcmp(id,personVal[i].id)==0){
            return i;
        }
   }return -1;
}

//check position from Place Dict
int checkPlacePosition(char id[20]){
   
   for(int i=0;i<1000;i++){
        if(strcmp(id,placeVal[i].userName)==0){
            return i;
        }
   }return -1;
}



