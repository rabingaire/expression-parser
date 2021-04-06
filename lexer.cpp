#include "lexer.hpp"

namespace ExpressionParser
{
    std::vector<Token *> Lexer::tokens()
    {
        std::vector<Token *> tokens;

        for (;;)
        {
            Token *token = this->next_token();
            tokens.push_back(token);
            if (token->get_type() == Token::Type::EOL)
            {
                break;
            }
        }

#ifdef DEBUG_LEXER
        for (Token *token : tokens)
        {
            token->debug_print_token();
        }
#endif

        return tokens;
    }
}
