/* "I pledge my honor that I have not cheated, and will not cheat, on this assignment." Cole Barbes */
%option yylineno
%option noyywrap

%{
  #define DEBUG 1
  typedef YYTOKENTYPE Token;
  Token scanned(Token t);
%}

digit	[0-9]
label	[a-z][a-zA-Z0-9]*
wspace	[ \t\r]*

%%

<<EOF>>     { return scanned(ENDFILE);}
error       { return scanned(ERROR);}
end         { return scanned(END);}
if          { return scanned(IF); }
then        { return scanned(THEN); }
else        { return scanned(ELSE); }
repeat      { return scanned(REPEAT); }
until       { return scanned(UNTIL); }
read        { return scanned(READ); }
write       { return scanned(WRITE); }
{digit}     { return scanned(NUM); }
{label}     { return scanned(ID); }
" "         { printf(" ");}
":="        { return scanned(ASSIGN); } 
"<"         { return scanned(LT); }
"="         { return scanned(EQ); }
"+"         { return scanned(PLUS); }
"-"         { return scanned(MINUS); }
"*"         { return scanned(TIMES); }
"("         { return scanned(LPAREN); }
")"         { return scanned(RPAREN); } 
";"         { return scanned(SEMI); }
"{"         { char c = input();
             while(c!='}' && c!=EOF) c=input();
          }
[\n]        { printf("\n"); }
             
{wspace}   { /*skip whitespace*/ }
.          { if(DEBUG) printf("\n");
             printf("Lex error on line %d: Illegal character %s\n",
                    yylineno,yytext);
             exit(-1);
           }
%%

Token scanned(Token t) {
    if(DEBUG==0) return t; 
    switch(t){
        case ENDFILE: printf("ENDFILE \n"); exit(-1); 
        case ERROR: printf("ERROR \n");
        case END: printf("END "); return t;
        case NUM: printf("NUM(%s) ", yytext); return t;
        case ID: printf("ID(%s) ", yytext); return t;
        case IF: printf("IF "); return t;
        case THEN: printf("THEN ");return t;
        case ELSE: printf("ELSE ");return t;
        case REPEAT: printf("REPEAT ");return t;
        case UNTIL: printf("UNTIL ");return t;
        case READ: printf("READ ");return t;
        case WRITE: printf("WRITE ");return t;
        case ASSIGN: printf("ASSIGN ");return t;
        case LT: printf("LT ");return t;
        case EQ: printf("EQ ");return t;
        case PLUS: printf("PLUS");return t;
        case MINUS: printf("MINUS ");return t;
        case TIMES: printf("TIMES ");return t;
        case LPAREN: printf("LPAREN ");return t;
        case RPAREN: printf("RPAREN ");return t;
        case SEMI: printf("SEMI ");return t;
        default: printf("ERROR: invalid token in scanned().\n"); exit(-1);
    }
}