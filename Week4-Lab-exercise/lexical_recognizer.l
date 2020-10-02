digit [0-9]*
id [a-zA-Z][a-zA-Z0-9]*
signed_num [+-]?[0-9]*
unsigned_float digit*\.digit*
signed_float [+-]?[0-9]*\.[0-9]*
exp {digit}[e]{digit}
%{
#include<stdio.h>
#include<string.h>
int i=0,j=0,cnt=0,n=0,com=0,scom=0;
char st[10][10];
FILE *ifp,*ofp;
int look_up(char st[10][10],char *id,int n);
%}
%%
"//"([a-z]|[0-9]|[A-Z]|" ")*
"/*"([a-z)|[0-9]|[A-Z]|" "|"\n")+"*/"
int |
float |
char |
double |
void |
unsigned  |
signed  |
if |
for |
while |
main {fprintf(ofp," \n %s is keyword",yytext);}
{digit} {fprintf(ofp,"\n %s is unsigned num",yytext);}
{signed_num} { fprintf(ofp,"\n %s is signed num",yytext);}
{unsigned_float} {fprintf(ofp,"\n %s is unsigned fractional float",yytext);}
{signed_float} { fprintf(ofp,"\n %s is signed fractional float",yytext);}
{exp}	   {fprintf(yyout,"%s: exponential float\n",yytext)};
{id} { fprintf(ofp,"\n %s is identifier",yytext);
if(!look_up(st,yytext,i))
strcpy(st[i++],yytext);cnt++;
}
"<=" {fprintf(ofp,"\n %s is Relational operator Lessthan or Equal to",yytext);}
"<" {fprintf(ofp, "\n %s is Relational operator Lessthan",yytext);}
">=" {fprintf(ofp,"\n %s is Relational operator Greaterthan or Equal to",yytext);}
">" { fprintf(ofp,"\n %s is Relational operator Greaterthan",yytext);}
"==" { fprintf(ofp,"\n %s is Relational operator Equal to",yytext);}
"!=" { fprintf(ofp,"\n %s is Relational operator Not Equal to",yytext);}
"="  { fprintf(ofp,"\n %s is Assignment Operator Equal to",yytext);}
%%
main()
{
char ip_file[10],op_file[10];;
printf("\n Enter input file name\n");
scanf("%s",ip_file);
printf("\n Enter output file name\n");
scanf("%s",op_file);
printf("The input file u entered is :%s",ip_file);
ifp=fopen(ip_file,"r");
ofp=fopen(op_file,"w");
if(ifp==NULL)
{
printf("\n Input file Doesnot exists\n");
exit(0);
}
else
{
yyin=ifp;yyout=ofp;
yylex();
fclose(ifp); fclose(ofp);
printf("\n the contents of symbol table are :\n");
for(j=0;j<i;j++)
printf("\n %s",st[j]);
printf("\n\n");
}
return 0;
}
int yywrap()
{
return 1;
}
int look_up(char st[10][10],char *id,int n)
{
for(j=0;j<n;j++)
  if(!strcmp(st[j],id))
    return 1;
return 0;
}
