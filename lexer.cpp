#include "lexer.hpp"

namespace ExpressionParser
{
    Token *Lexer::next_token()
    {
        Lexer::skip_whitespace();

        Token *token{nullptr};

        switch (Lexer::current_char())
        {
        case '+':
        {
            token = new Token{Token::Token::Type::PLUS, Lexer::current_char()};
            break;
        }
        case '-':
        {
            token = new Token{Token::Type::SUBTRACT, Lexer::current_char()};
            break;
        }
        case '/':
        {
            token = new Token{Token::Type::DIVIDE, Lexer::current_char()};
            break;
        }
        case '*':
        {
            token = new Token{Token::Type::MULT, Lexer::current_char()};
            break;
        }
        case '(':
        {
            token = new Token{Token::Type::LPAREN, Lexer::current_char()};
            break;
        }
        case ')':
        {
            token = new Token{Token::Type::RPAREN, Lexer::current_char()};
            break;
        }
        case 0:
        {
            token = new Token{Token::Type::EOL};
            break;
        }
        default:
        {
            if (isdigit(Lexer::current_char()))
            {
                size_t number = Lexer::read_number();
                token = new Token{
                    Token::Type::NUMBER, number};
                break;
            }
            token = new Token{Token::Type::INVALID};
        }
        }

        advance();

        return token;
    }
}
