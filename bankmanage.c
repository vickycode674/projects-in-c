#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct user{
 char phone[50];
 char ac[40];
 char password[50];
 float balance;
};

int main()
{
struct user usr,usr1;
FILE *fp;          //syntax for creating file function
char filename[50],phone[50],pwrd[50];  //creating string is must for multiple characaters
int opt;
char cont='y';
int choice,amount; 
usr.balance=0;

printf("\n What do you want to do?");
printf("\n\n1.Register an acount");
printf("\n2.Login to an account");

printf("\n your choice:");
scanf("%d",&opt);

if(opt==1){
  system("cls"); //clean console neatly
  printf("Enter your account number:\t");
  scanf("%s",usr.ac);
  printf("Enter your phone number:\t");
  scanf("%s",usr.phone);
  printf("Enter your new password:\t");
  scanf("%s",usr.password);
  usr.balance=0;  //as it is  newly opened balance will be na
  strcpy(filename,usr.phone);
  fp=fopen(strcat(filename,".dat"),"w"); //.dat is text file .w is writing in a file
  fwrite(&usr,sizeof(struct user),1,fp);  //no of instnace and file pointer
  if(fwrite!=0)
    printf("\n\nAccount succesfully registered");
  else
    printf("\n\nSomething went wrong please try again"); 
   fclose(fp);
  } 

 if(opt==2){
  system("cls");
  printf("enter your phone number:\t");
  scanf("%s",phone);
  printf("enter your password:\t");
  scanf("%s",pwrd);
   usr.balance=0;
  strcpy(filename,phone); //filename is stored as phone number but not as old phone
  fp=fopen(strcat(filename,".dat"),"r"); //r represents reading of a file
   if(fp==NULL)
   printf("\n Account is not registered"); 
  
   else{
   fread(&usr,sizeof(struct user),1,fp);  //content of the file is read store in usr
   fclose(fp) ;
  if(!strcmp(pwrd,usr.password)) //comparting the password
   {
     while(cont=='y'){
         system("cls");
         printf("\n Press 1 to check the balance");
         printf("\n Press 2 to deposit the amount");
         printf("\n Press 3 to withdraw the amount");
         printf("\n Press 4 to online transfer the amount");  
         printf("\n Press 5 to change the password");

         printf("\n Your choice: \t");    //for working out each casae we have to do individully
         scanf("%d",&choice);

           switch(choice){
             case 1:
               printf("\n Your current balance is %.2frs only",usr.balance);
               break;
             
             case 2:
               printf("\n Enter the amount to be deposited:");
               scanf("%d",&amount);
               usr.balance+=amount;
               fp=fopen(filename,"r");
               fwrite(&usr,sizeof(struct user),1,fp);
                if(fwrite!=NULL) printf("\nSuccesfully depsoited");
               fclose(fp);
               break;

             case 3:
               printf("\n Enter the amount to be withdrawn:");
               scanf("%d",&amount);

                usr.balance-=amount;
               fp=fopen(filename,"r");
               fwrite(&usr,sizeof(struct user),1,fp);
                if(fwrite!=NULL)
                 printf("\nMoney is succesfully withdrawn");
                 fclose(fp);
                break;

             case 4:
               printf("\n Enter the phone number which amount to be tranfered:");
               scanf("%s",phone);
               printf("\nPlease enter amount to be transfered:\t");
               scanf("%f",&amount);
               strcpy(filename,phone);
                 fp=fopen(strcat(filename,".dat"),"r");
                 
                  if(fp==NULL) printf("\n Account number is not registerd\n");
                else{
                    fread(&usr1,sizeof(struct user),1,fp);
                    fclose(fp);
             
                if(amount>usr.balance)
                  printf("Insufficient balance");
               
                else{  
                 fp=fopen(filename,"w");
                 usr1.balance+=amount;
                 fwrite(&usr1,sizeof(struct user),1,fp);
                 fclose(fp);}

                 if(fwrite!=NULL){
                   printf("\n You have succesfully transfered Rs %0.2f",usr1.balance);
                   strcpy(filename,usr.phone);
                   fp=fopen(strcat(filename,".dat"),"w");
                   usr.balance-=amount;
                   fwrite(&usr,sizeof(struct user),1,fp);
                   fclose(fp);
                 }
                }
                break;

            case 5:
              printf("\n Please enter your new password:\t");
              scanf("%s",pwrd);
                fp=fopen(filename,"w");
                strcpy(usr.password,pwrd);
                fwrite(&usr,sizeof(struct user),1,fp);
               
                if(fwrite!=NULL)
                 printf("\nPassword succesfully changed");
                 fclose(fp);
                 break;
           default:
             printf("Invalid option");
         }
         printf("\nDo you want to continue  the transaction [y/n]");
         scanf("%s",&cont);
     }
   }
   else
   printf("\n Password is not matching");
  }
 }
}
