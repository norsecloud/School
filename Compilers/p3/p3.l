%{
#include "p3.tab.h"
%}

number      [0-9]
delimiter   [ \t]
whitespace  {delimiter}+
letter      [A-Za-z]*

%%
{number}+           return(NUMBER);
"RENAME"            return(RENAME);
"WHERE"             return(WHERE);

"UNION"             return(UNION);
"INTERSECT"         return(INTERSECT);
"MINUS"             return(MINUS);
"TIMES"             return(TIMES);
"JOIN"              return(JOIN);
"DIVIDEBY"          return(DIVIDEBY);

"S"                 return(RELATION);
"P"                 return(RELATION);
"SP"                return(RELATION);
"PRDCT"             return(RELATION);
"CUST"              return(RELATION);
"ORDERS"            return(RELATION);

"="                 return(EQ);
"<>"                return(NEQ);
"<"                 return(LSS);
"<="                return(LEQ);
">"                 return(GTR);
">="                return(GEQ);
"("                 return(LPN);
")"                 return(RPN);
"["                 return(LBR);
"]"                 return(RBR);
","                 return(COM);

"CNO"               return(ATTRIBUTE);
"CITY"              return(ATTRIBUTE);
"CNAME"             return(ATTRIBUTE);
"SNO"               return(ATTRIBUTE);
"PNO"               return(ATTRIBUTE);
"TQTY"              return(ATTRIBUTE);
"SNAME"             return(ATTRIBUTE);
"QUOTA"             return(ATTRIBUTE);
"PNAME"             return(ATTRIBUTE);
"COST"              return(ATTRIBUTE);
"AVQTY"             return(ATTRIBUTE);
"S#"                return(ATTRIBUTE);
"STATUS"            return(ATTRIBUTE);
"P#"                return(ATTRIBUTE);
"COLOR"             return(ATTRIBUTE);
"WEIGHT"            return(ATTRIBUTE);
"QTY"               return(ATTRIBUTE);

"AS"                return(AS);
.                   ;
{letter}            return(ERROR);
{whitespace}        ;
\n                  ;
%%