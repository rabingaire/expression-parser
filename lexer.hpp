#pragma once

#include <cstring>
#include <assert.h>
#include <ctype.h>
#include <iostream>

namespace ExpressionParser
{
    struct Token
    {
        enum struct Type
        {
            NUMBER,
            PLUS,
            SUBTRACT,
            DIVIDE,
            MULT,
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

        Type get_type()
        {
            return this->m_type;
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

        Token *next_token();

    private:
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
