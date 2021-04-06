#include "lexer.hpp"

int main()
{
  const char *input = "1 + 2*(4+5)";
  ExpressionParser::Lexer *lex = new ExpressionParser::Lexer{input};

  ExpressionParser::Token *token = lex->next_token();
  while (token->get_type() != ExpressionParser::Token::Type::EOL)
  {
    token->debug_print_token();
    token = lex->next_token();
  }

  return 0;
}
