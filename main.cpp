#include "lexer.hpp"

int main()
{
  const char *input = "1 + 2*(4+5)";
  ExpressionParser::Lexer *lex = new ExpressionParser::Lexer{input};

  for (ExpressionParser::Token *token : lex->tokens())
  {
    token->debug_print_token();
  }

  return 0;
}
