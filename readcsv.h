#include <stdio.h>
#include <string.h>

void drawLinesReadCSV();

int checkPlaceData(char str[30], int columnNo){

//Name = 1,User Name  = 2,Password = 3,Place Type =4,Location = 5,Employee Count = 6

    FILE* fp = fopen("placeDatabase.csv", "r");
    
        if (!fp)
            printf("Can't open file\n");
    
        else {

            char buffer[1024];

            int row = 0;
            int column = 0;
    
            while (fgets(buffer,1024, fp)) {
                column = 1;
                row++;
    
                // pass fisrst row
                if (row == 1)
                    continue;
    
                // Splitting the data
                char* value = strtok(buffer, ",");
    
                while (value) {
                    // Column - UserName  
                    if (column == columnNo) {
                        if(strcmp(value,str)==0){
                            return 1;
                            break;
                            //printf("\nfind\n");
                        }
                    }
    
                    //printf("%s", value);
                    value = strtok(NULL, ",");
                    column++;
                }
    
                //printf("\n");
            }
    
            // Close the file
            fclose(fp);
        }
}

int checkPersonData(char str[30],int columNo){ 
   
    FILE* fp = fopen("personDatabase.csv", "r");
    
    if (!fp)
        printf("Can't open file\n");
  
    else {

        char buffer[1024];

        int row = 0;
        int column = 0;
  
        while (fgets(buffer,1024, fp)) {
            column = 1;
            row++;
  
            // pass fisrst row
            if (row == 1)
                continue;
  
            // Splitting the data
            char* value = strtok(buffer, ",");
  
            while (value) {
                // Column - UserName  
                if (column == columNo) {
                    if(strcmp(value,str)==0){
                        return 1;
                        break;
                        //printf("\nfind\n");
                    }
                }
  
                //printf("%s", value);
                value = strtok(NULL, ",");
                column++;
            }
  
            //printf("\n");
        }
  
        // Close the file
        fclose(fp);

    }
}

int checklogin(char id[13],char pass[6],char jbrole[20]){

    FILE* fp = fopen("personDatabase.csv", "r");
    
    if (!fp)
        printf("Can't open file\n");
  
    else {

        char buffer[1024];

        int row = 0;
        int column = 0;
  
        while (fgets(buffer,1024, fp)) {
            column = 1;
            row++;
  
            // pass fisrst row
            if (row == 1)
                continue;
  
            // Splitting the data
            char* value = strtok(buffer, ",");
            int t1=0,t2=0,t3=0;
        
            while (value) {
                //printf("%s\n",value);
                // Column - UserName  
                
                if (column == 2) {
                    if(strcmp(value,id)==0){
                        t1=1;
                        
                    }
                }
                if (column == 3 && (strcmp(value,pass)==0)){    
                        t2 = 1;
                        
                         
                }
                if (column == 8 && (strcmp(value,jbrole)==0)){    
                        t3 = 1;
                            
                }
                if(t1==1 && t2==1 && t3 == 1){
                    return 1;
                    break;
                }
               
                
                //printf("%s", value);
                value = strtok(NULL, ",");
                column++;
            }
  
            //printf("\n");
        }
        
        // Close the file
        fclose(fp);

    }
}

void displayPersonDetails(char workDevision[13]){
    
    char name[50],id[13],gnDev[11],jbRole[16],wrkDev[13],tel[11],vaci[4];
    int age;
    printf("\n%s\n",workDevision);
    FILE* fp = fopen("personDatabase.csv", "r");
    
    if (!fp)
        printf("Can't open file\n");
  
    else {

        char buffer[1024];

        int row = 0;
        int column = 0;
  
        while (fgets(buffer,1024, fp)) {
            column = 1;
            row++;
  
            // pass fisrst row
            if (row == 1)
                continue;
  
            // Splitting the data
            char* value = strtok(buffer, ",");

            int belongDev =0;

            while (value) {
                if(column == 1){
                   strcpy(name,value);
                }
                if(column == 2){
                   strcpy(id,value);
                }
                if(column == 4){
                   age = atoi(value);
                }
                if(column == 5){
                   strcpy(tel,value);
                }
                if(column == 6){
                   strcpy(vaci,value);
                }
                
                if(column == 8){
                   strcpy(jbRole,value);
                }
                // Chech gramaniladhari's devision is equal to residents division
                if (column == 7) {
                    if(strcmp(value,workDevision)==0){
                        belongDev = 1;
                        printf("\nBelong\n");    
                    }
                    strcpy(gnDev,value);
                }
                
               
               
  
                //printf("%s", value);
                value = strtok(NULL, ",");
                column++;
            }
            //if this person is in selected grama nildharis' working area,print the details 
            if (belongDev==1){
                //drawlinreadCSV is use to draw lines
                drawLinesReadCSV();
                printf("\nName : %s\t ID : %s\t Age : %d\t Tel : %s\nVacination : %s\t GN Div : %s\n",name,id,age,tel,vaci,gnDev);
            }
  
            //printf("\n");
        }
        drawLinesReadCSV();
        printf("\n"); 
        // Close the file
        fclose(fp);

    }
}

void drawLinesReadCSV(){
    for(int k=0;k<100;k++){
            printf("_");}
        printf("\n");
}

void checkWorkingDIV (char id[13], char* returnWorkDev) {

    char findGNDev[13];

    FILE* fp = fopen("personDatabase.csv", "r");
    
    if (!fp)
        printf("Can't open file\n");
  
    else {

        char buffer[1024];

        int row = 0;
        int column = 0;
  
        while (fgets(buffer,1024, fp)) {
            column = 1;
            row++;
  
            // pass fisrst row
            if (row == 1)
                continue;
  
            // Splitting the data
            char* value = strtok(buffer, ",");

            int findID = 0;

            while (value) {
                // Column - UserName  
                if (column == 2) {
                    if(strcmp(value,id)==0){
                        findID = 1;
                        //printf("\nFind ID\n");
                                                
                        //printf("\nfind\n");
                    }
                }
                if (column == 9){
                    //printf("\n%s\n",value);
                    if (findID == 1){
                        //printf("\n%s\n",value);
                        strcpy(findGNDev,value);
                        printf("dome");
                        printf("\n%s\n",findGNDev);
                        displayPersonDetails(findGNDev);

                    }
                }
  
                //printf("%s", value);
                value = strtok(NULL, ",");
                column++;
            }
  
            //printf("\n");
        }
  
        // Close the file
        fclose(fp);

        // displayPersonDetails(findGNDev);
    }
}

void placeCSVtoWorkCSV(){
    char username[20],id[13];
    FILE* fp = fopen("placeDatabase.csv", "r");
    
        if (!fp)
            printf("Can't open file\n");
    
        else {

            char buffer[1024];

            int row = 0;
            int column = 0;
    
            while (fgets(buffer,1024, fp)) {
                column = 1;
                row++;
    
                // pass fisrst row
                if (row == 1)
                    continue;
    
                // Splitting the data
                char* value = strtok(buffer, ",");
    
                while (value) {
                    // Column - UserName  
                    if (column == 2) {
                        strcpy(username,value);
                    }
                    if(column > 6){
                        strcpy(id,value);

                        //write to the worlplace database
                        FILE* fp1 = fopen("workPlace.csv", "a+");
                        if (!fp1) {
                                // Error in file opening
                                printf("Can't access Database\n");
                            }
                        ///write to csv
                        fprintf(fp1,"\n%s,%s",id,username);
                        //print 
                        printf("\n%s\t%s",id,username);
                        fclose(fp1); 
                        printf("\n");
                    }
                    
                    value = strtok(NULL, ",");
                    column++;
                }
    
                
            }
    
            // Close the file
            fclose(fp);
        }
}

