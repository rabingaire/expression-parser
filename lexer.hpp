#pragma once

#include <cstring>
#include <assert.h>
#include <ctype.h>
#include <iostream>
#include <vector>

namespace ExpressionParser
{
    struct Token
    {
        enum struct Type
        {
            NUMBER,
            SUBTRACT,
            PLUS,
            MULT,
            DIVIDE,
            LPAREN,
            RPAREN,
            EOL,
            INVALID
        };

        enum struct LiteralType
        {
            STRING,
            CHARACTER,
            NUMBER,
            INVALID
        };

        Token(const Type type, const char *literal)
            : m_type{type}, m_string_literal{literal}, m_literal_type{LiteralType::STRING}
        {
            assert(m_string_literal);
        }

        Token(const Type type, const char literal)
            : m_type{type}, m_char_literal{literal}, m_literal_type{LiteralType::CHARACTER}
        {
        }

        Token(const Type type, const size_t literal)
            : m_type{type}, m_number_literal{literal}, m_literal_type{LiteralType::NUMBER}
        {
        }

        Token(const Type type) : m_type{type}, m_literal_type{LiteralType::INVALID}
        {
        }

        static Token *invalid() { return new Token{Token::Type::INVALID}; }

        bool is_operator()
        {
            return this->m_type == Type::PLUS || this->m_type == Type::SUBTRACT || this->m_type == Type::MULT || this->m_type == Type::DIVIDE;
        }

        bool is_number()
        {
            return this->m_type == Type::NUMBER;
        }

        bool is_valid()
        {
            return this->m_type != Type::INVALID;
        }

        bool is_eol()
        {
            return this->m_type == Type::EOL;
        }

        bool is_open_paren()
        {
            return this->m_type == Type::LPAREN;
        }

        bool is_close_paren()
        {
            return this->m_type == Type::RPAREN;
        }

        Type get_type()
        {
            return this->m_type;
        }

        const char *get_string_literal()
        {
            return this->m_string_literal;
        }

        const char get_char_literal()
        {
            return this->m_char_literal;
        }

        const char get_number_literal()
        {
            return this->m_number_literal;
        }

        void debug_print_token()
        {
            switch (this->m_literal_type)
            {
            case LiteralType::STRING:
            {
                std::cout << this->token_type() << ":" << this->m_string_literal << std::endl;
                break;
            }
            case LiteralType::CHARACTER:
            {
                std::cout << this->token_type() << ":" << this->m_char_literal << std::endl;
                break;
            }
            case LiteralType::NUMBER:
            {
                std::cout << this->token_type() << ":" << this->m_number_literal << std::endl;
                break;
            }
            default:
            {
                std::cout << this->token_type() << std::endl;
            }
            }
        }

    private:
        const char *token_type()
        {
            switch (this->m_type)
            {
            case Type::NUMBER:
            {
                return "NUMBER";
            }
            case Type::PLUS:
            {
                return "PLUS";
            }
            case Type::SUBTRACT:
            {
                return "SUBTRACT";
            }
            case Type::DIVIDE:
            {
                return "DIVIDE";
            }
            case Type::MULT:
            {
                return "MULT";
            }
            case Type::LPAREN:
            {
                return "LPAREN";
            }
            case Type::RPAREN:
            {
                return "RPAREN";
            }
            case Type::EOL:
            {
                return "EOL";
            }
            case Type::INVALID:
            {
                return "INVALID";
            }
            }
        }

        const Type m_type{Type::INVALID};
        union
        {
            const char *m_string_literal;
            const char m_char_literal;
            const size_t m_number_literal;
        };
        const LiteralType m_literal_type{LiteralType::INVALID};
    };

    struct Lexer
    {
        Lexer(const char *input)
            : m_input{input}, m_size{std::strlen(input)}
        {
            assert(m_input);
        }

        std::vector<Token *> tokens();

    private:
        Token *next_token()
        {
            skip_whitespace();

            Token *token{nullptr};

            switch (current_char())
            {
            case '+':
            {
                token = new Token{Token::Type::PLUS, current_char()};
                break;
            }
            case '-':
            {
                token = new Token{Token::Type::SUBTRACT, current_char()};
                break;
            }
            case '/':
            {
                token = new Token{Token::Type::DIVIDE, current_char()};
                break;
            }
            case '*':
            {
                token = new Token{Token::Type::MULT, current_char()};
                break;
            }
            case '(':
            {
                token = new Token{Token::Type::LPAREN, current_char()};
                break;
            }
            case ')':
            {
                token = new Token{Token::Type::RPAREN, current_char()};
                break;
            }
            case 0:
            {
                token = new Token{Token::Type::EOL};
                break;
            }
            default:
            {
                if (isdigit(current_char()))
                {
                    size_t number = read_number();
                    token = new Token{
                        Token::Type::NUMBER, number};
                    break;
                }
                token = new Token{Token::Type::INVALID, current_char()};
            }
            }

            advance();

            return token;
        }

        void skip_whitespace()
        {
            while (current_char() == ' ' || current_char() == '\t')
            {
                advance();
            }
        }

        const char current_char()
        {
            if (m_index >= m_size)
            {
                return 0;
            }

            return m_input[m_index];
        }

        const char peek_char()
        {
            if (m_index + 1 >= m_size)
            {
                return 0;
            }

            return m_input[m_index + 1];
        }

        void advance()
        {
            m_index++;
        }

        const size_t read_number()
        {
            size_t number{0};
            while (true)
            {
                number *= 10;
                number += current_char() - '0';
                if (!isdigit(peek_char()))
                {
                    break;
                }
                advance();
            }
            return number;
        }

        const char *m_input{nullptr};
        const size_t m_size{0};
        size_t m_index{0};
    };
}
