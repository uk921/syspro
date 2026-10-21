#include <stdio.h>

int main(int argc, char *argv[])
{
   FILE *fp;
   int c, num;
   if (argc < 2) 
      fp = stdin; 			
   else  fp = fopen(argv[1],"r");	

   printf("0: list of all books, 1: list of available books ) ");
   scanf("%d", &num);
   printf("id bookname author year numofborrow borrow\n");
   if(num==0){
   		c = getc(fp); 			
   		while (c != EOF) { 		
   		   putc(c, stdout); 		
     		 c = getc(fp); 		
   		}
   }
   else if(num==1){
   }
   
   fclose(fp); 
   return 0;
}

