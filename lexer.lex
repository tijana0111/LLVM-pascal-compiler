%option noyywrap
%option nounput
%option noinput
%{
#include <iostream>
#include <cstdlib>
#include <cctype>

using namespace std;

#include <string>
#include "naredba.hpp"
#include "izraz.hpp"
#include <vector>
extern map<string, char> tablica;
#include "parser.tab.hpp"


void to_lower_case(string &s) {
  for (auto &c: s)
      c = tolower(c);
}

%}


%%

begin				return begin_token;
end					return end_token;
var					return var_token;
write				return write_token;
write_b				return write_b_token;
mod					return mod_token;
if					return if_token;
then				return then_token;
else				return else_token;
while				return while_token;
do					return do_token;
integer				return int_type_token;
boolean				return bool_type_token;
and					return and_token;
or					return or_token;
xor					return xor_token;
not					return not_token;
true				return true_token;
false				return false_token;
[/][/].*     		{  }
[0-9]+             {
                      yylval.x = atoi(yytext);
                      return num_token;
                   }
0[xX][0-9a-fA-F]+  {
                      yylval.x = (int)strtol(yytext, NULL, 16);
                      return num_token;
                   }
                   
[a-zA-Z_][a-zA-Z_0-9]*  {
							yylval.s = new string(yytext);
							to_lower_case(*(yylval.s));
							
							if(!tablica.count(*(yylval.s))){
								return n_id_token;
							}
							else if(tablica[*(yylval.s)] == 0){
								return b_id_token;
							}
							else if(tablica[*(yylval.s)] == 1)
								return i_id_token;
								
                        }
[<>().;+*/:=|&~-]     return *yytext;
[ \n\t]            {  }
.   {
  cerr << "Leksicka greska: Neprepoznat karakter " << *yytext << endl;
  exit(EXIT_FAILURE);
}
%%

