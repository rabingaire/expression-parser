#include "parser.hpp"

int main()
{
  const char *input = "-1 + -2";
  ExpressionParser::Parser *parser = new ExpressionParser::Parser{input};
  std::cout << parser->parse_expression() << std::endl;
  return 0;
}
