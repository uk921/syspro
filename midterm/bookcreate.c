#include <stdio.h> 
#include "book.h"

int main(int argc, char* argv[]) 
{ 
   struct book rec;
   FILE *fp;

   if (argc != 2) {
      fprintf(stderr, "How to use: %s FileName\n", argv[0]);
      return 1; 
   }

   fp = fopen(argv[1], "w");
   if(fp == NULL){
	   fprintf(stderr,"file open error\n");
	   return 1;
   }

   printf("%s %s %s %s %s %s\n", "책 고유 번호", "책 이름", "저자 이름", "출판년도", "대출 횟수", "대출 유무"); 
   
   while(scanf("%d %s %s %d %d %d", &rec.id, rec.name, rec.write, &rec.year, &rec.time, &rec.tf) == 6){
   		fprintf(fp, "%d %s %s %d %d %d\n", rec.id, rec.name, rec.write, rec.year, rec.time, rec.tf);
   }

   fclose(fp);
   return 0;
}

