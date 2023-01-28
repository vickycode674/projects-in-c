#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct items{
    char  item[20];
    float price;
    int qty;
  };

  struct orders{
   char customer[50];
   char date[50];
   int num_of_Items; 
   struct items itm[50];  //struct inside struct reprensenting the combination

  };

//function to generate a bill
void generatebillheader(char name[50],char date[50]){
    printf("\n\n");
    printf("\t    CHENGALAPATTU Restaurant");
    printf("\n \t ---------------------------");
    printf("\nDate:%s",date);
    printf("\nInvoice to:%s",name);
    printf("\n");
    printf("-------------------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n-------------------------------------------------");
    printf("\n \n");
}
//generating body of the bill

 void generatebillbody(char item[20],int qty,float price){
     printf("%s\t\t",item);
         printf("%d\t\t",qty);
         printf("%.2f\t\t",qty*price);
         printf("\n");
 }

  
//genrating footer or grandtotal of the bill
 
 void generatebillfooter(float total){
  
   printf("\n");
   float dis=0.1*total;
   float nettotal=total-dis;
   float cgst=0.09*nettotal;
   float grandtotal=nettotal+2*cgst;
   printf("--------------------------------------------------\n");
   printf("Sub total \t\t\t%0.2f",total);
   printf("\nDiscount @10 %s\t\t\t%.2f","%",dis);
   printf("\n \t\t\t\t--------");
   printf("\n Net Total\t\t\t%0.2f",nettotal);
   printf("\n CGST @9%s\t\t\t%.2f","%",cgst);
   printf("\n SGST @9%s\t\t\t%.2f","%",cgst);
   printf("\n---------------------------------------------------");
   printf("\n Grant total\t\t\t%0.2f",grandtotal);
   printf("\n-------------------------------------------------\n");
 }

int main(){

 struct  orders ord;
 struct orders order;

 float total,tot;
 int opt,n,invoicefound=0;
 char saveBill='y',contflag='y';
 char name[50];

  FILE*fp;
//dashboard
while(contflag=='y'){
printf("\t==================CHENGALAPTTUS RESTAURANT==================\n");
 printf("\n1.)Genrate Invoice");
 printf("\n2.)Show all Invoice");
 printf("\n3.)Search Inovice");
 printf("\n4.)Exit");

 printf("\n\nPlease select your option:");
 scanf("%d",&opt);
  fgetc(stdin);  //fgetc() is used to obtain input from a file single character at a time. 


 switch(opt){
   
    case 1 :  //generate invoice
    system("cls");
    printf("Please enter the name of customer : ");
    fgets(ord.customer,50,stdin);
    ord.customer[strlen(ord.customer)-1]=0;
    strcpy(ord.date,__DATE__);

    printf("\nPlease enter the no of items :");
    scanf("%d",&n);
    ord.num_of_Items=n;
    
    for(int i=0;i<n;i++){
     fgetc(stdin);
     
     printf("\nPlease enter the item %d: ",i+1);
     fgets(ord.itm[i].item,20,stdin);
     ord.itm[i].item[strlen(ord.itm[i].item)-1]=0; //intiliasing the last element as zero 
     
     printf("Please enter the quauntity:\t");
     scanf("%d",&ord.itm[i].qty);
     
     printf("Please enter the unit price:\t");
     scanf("%f",&ord.itm[i].price);

    total +=ord.itm[i].qty * ord.itm[i].price;
    }
     generatebillheader(ord.customer,ord.date); 
     for(int i=0;i<ord.num_of_Items;i++){
      generatebillbody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
     } 
     generatebillfooter(total);

     printf("Do you want to save the invoice:\t");
     scanf("%s",&saveBill);

       if(saveBill=='y'){
        fp= fopen("RestauarntBill.dat","a+");
        fwrite(&ord,sizeof(struct orders),1,fp);
         if(fwrite!=0)
          printf("Succesfully saved\n");
          else
          printf("\nError Saving");
          fclose(fp);
       }  
       break;

     case 2://show all invoices
     system("cls");
     fp=fopen("RestauarantBill.dat","r");
      printf("\n *****your Previous Invoices******\n");
      while(fread(&order,sizeof(struct orders),1,fp)){
        generatebillheader(order.customer,order.date); 
          for(int i=0;i<order.num_of_Items;i++)
           {
             generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].qty);
             tot+=order.itm[i].qty*order.itm[i].price;}
             generatebillfooter(tot);
       fclose(fp);
      }
       break;

   case 3:
    printf("\nPlease enter the name of the customer\t");
    // fgetc(stdin);
     fgets(name,50,stdin);
     name[strlen(name)-1]=0;
     system("cls");

     fp=fopen("RestauarantBill.dat","r");
      printf("\t ******* Invoices of %s*******",name);
      while(fread(&order,sizeof(struct orders),1,fp)){

      if(!strcmp(order.customer,name)){
       
       generatebillheader(order.customer,order.date); 
          for(int i=0;i<order.num_of_Items;i++)
           {
             generatebillbody(order.itm[i].item,order.itm[i].qty,order.itm[i].qty);
             tot+=order.itm[i].qty*order.itm[i].price;
          
            
             generatebillfooter(tot);
             invoicefound=1;
           }
      }  
           if(!invoicefound){
             printf("Sorry the invoice for %s not exist");
           }
      }



       fclose(fp);
       break;

    case 4:
       printf("\n\t\tFuck off  kindly visit again :)\n\n");
       exit(0);
       break;
   
    default:
      printf("Sorry invalid option pls try again");
      break;
 }

 printf("Do you want to perform another operation");
 scanf("%s",&contflag);

}
return 0;
}