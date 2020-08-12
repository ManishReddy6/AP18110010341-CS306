#include<stdio.h>
void main()
{
  int state=0,i=0;
  char a[20],current;
  printf("Enter a string:");
  scanf("%s",&a);
  while((current=a[i++])!='\0')
  {
      switch(state)
      {
          case 0:
              if(current=='a')state=1;
              else if(current=='b')state=2;
              else{
                    printf("Invalid");
                    exit(0);
              }
              break;
          case 1:
            if(current=='a')state=3;
            else if(current=='b')state=2;
            else{
                printf("Invalid");
                exit(0);
            }
            break;
          case 2:
            if(current=='a')state=1;
            else if(current=='b')state=4;
            else{
                printf("Invalid");
                exit(0);
            }
            break;
          case 3:
            if(current=='a')state=3;
            else if(current=='b')state=2;
            else{
                printf("Invalid");
                exit(0);
            }
            break;
          case 4:
            if(current=='a')state=1;
            else if(current=='b')state=4;
            else{
                printf("Invalid");
                exit(0);
            }
            break;
      }
  }
  if(state==3||state==4)
  {
      printf("String Accepted\n");
  }
  else{
    printf("String not Accepted\n");
  }
}
