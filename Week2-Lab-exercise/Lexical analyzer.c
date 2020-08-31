#include<stdio.h>
#include<ctype.h>
#include<string.h>
char keyword[30][30]={"int","while","break","for","do","if","float","char","switch","double",
"short","long","unsigned","sizeof","else","register","extern","static","auto",
"case","break","volatile","enum","typedef"};
char id[20], num[10];
char symb_tab[20][20];
int check_keyword(char s[])
{
int i;
for(i=0;i<24;i++)
if(strcmp(s,keyword[i])==0)
{
    return 1;
}
return 0;
}
//write a function to store identifier in symbol table
int store_symb_tab(char id[], char symb_tab[])
{
int j;
for(j=0;id[j]!='\0';j++)
{
    symb_tab[j]=id[j];
    printf("%c",symb_tab[j]);
}
printf(" ");
return 0;
}

int main()
{
FILE *fp1,*fp2;
char c,d;
int state=0;
int i=0,j=0,k,y;
fp1=fopen("x.txt","r");//input file containing src prog
fp2=fopen("y.txt","w");//output file name

while((c=fgetc(fp1))!=EOF)
{
switch(state)
{
case 0: if(isalpha(c)){
state=1; id[i++]=c;}
else if(isdigit(c)){
state=3; num[j++]=c;}
else if(c=='<')
{
    d=c;
    state=5;
}
else if(c=='>')
{
    d='>';
    state=5;
}
else if(c=='=')
{
    d='=';
    state=8;
}
else if(c=='!')
{
   d='!';
state=8;
}
else if(c=='/')
state=10;
else if(c==' ' || c=='\t' || c=='\n')
state=0;
else
fprintf(fp2,"\n%c",c);
break;
case 1:if(isalnum(c)){
state=1; id[i++]=c;
}
else{
id[i]='\0';
if(check_keyword(id))
{
fprintf(fp2," \n %s : keyword ",id);
}
else
{
fprintf(fp2,"\n %s : identifier",id);
for(k=0;k<20;k++)
{
    if(strcmp(id,symb_tab[k])==0)
    {
        break;
    }
    else
    {
        if(strlen(symb_tab[k])==0)
        {
            store_symb_tab(id,symb_tab[k]);
            break;
        }
    }
}
}
state=0;
i=0;
ungetc(c,fp1);
}
break;
case 3:if(isdigit(c)){
num[j++]=c;
state=3;
}
else{
num[j]='\0';
fprintf(fp2," \n%s: number",num);
state=0;
j=0;
ungetc(c,fp1);
}
break;
case 5:
    if(c=='='){
        if(d=='>'){
            fprintf(fp2,"\n%c%c: Greater than or Equal To",d,c);
        }
        else if(d=='<')
        {
            fprintf(fp2,"\n%c%c: Less than or Equal To",d,c);
        }
    state=0;
    }
    else{
        state=0;
        ungetc(c,fp1);
    }
break;
case 8:
    if(c=='='){
        if(d=='='){
            fprintf(fp2,"\n%c%c: Equal To",d,c);
        }
        else if(d=='!')
        {
            fprintf(fp2,"\n%c%c: Not Equal To",d,c);
        }
    state=0;
    }
    else{
        state=0;
        ungetc(c,fp1);
    }
break;
case 10:if(c=='*')
state=11;
else
fprintf(fp2,"\n invalid lexeme");
break;
case 11: if(c=='*')
state=12;
else
state=11;
break;
case 12:if(c=='*')
state=12;
else if(c=='/')
state=0;
else
state=11;
break;

}//End of switch
}//end of while
if(state==11)
fprintf(fp2,"comment did not close");
fclose(fp1);
fclose(fp2);
return 0;
}
