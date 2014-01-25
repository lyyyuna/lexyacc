%{

%}

%%

[\t ]+  ;

is |
am |
did |
been |
do |
will |
go      { printf("%s: is a verb\n", yytext); }

[a-zA-Z]+       { printf("%s: is not a verb\n", yytext); }

.|\n    { ECHO; }

%%

int main()
{
    yylex();
}
