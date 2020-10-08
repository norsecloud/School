%{
#include <stdio.h>
#include <stdlib.h>
extern yylex();
extern yytest[];
extern FILE *yyin;
%}

%start start
%token NUMBER RENAME WHERE UNION INTERSECT MINUS TIMES JOIN DIVIDEBY RELATION EQ NEQ LSS LEQ GTR GEQ LPN RPN LBR RBR COM ATTRIBUTE AS ERROR

%%

start                           : expression {};
expression                      : oneRelationExpression {} | twoRelationExpression {};
oneRelationExpression           : renaming {} | restriction {} | projections {};
renaming                        : term RENAME ATTRIBUTE AS ATTRIBUTE {};
term                            : RELATION {} | LPN expression RPN {};
restriction                     : term WHERE comparison {};
projections                     : term {} | term LBR attributeCommaList RBR {};
attributeCommaList              : ATTRIBUTE {} | ATTRIBUTE COM attributeCommaList {};
twoRelationExpression           : projections binaryOperation expression {};
binaryOperation                 : UNION {} | INTERSECT {} | MINUS {} | TIMES {}| JOIN {} | DIVIDEBY {};
comparison                      : ATTRIBUTE compare number {};
compare                         : EQ {} | NEQ {} | LSS {} | LEQ {} | GTR {} | GEQ {};
number                          : val {} | val NUMBER {};
val                             : NUMBER {}

%%

int main(int argc, char *argv[])
{
   yyin = fopen(argv[1], "r");
   if (!yyin)
   {
      printf("no file\n");
      exit(0);
   }
   yyparse();
   printf("ACCEPT");
}
yyerror()
{
   printf("\nREJECT\n");
//   printf("error from yyerror\n");
   exit(0);
}
yywrap()
{
   return 1;
}