#pragma once

#include "lexer.hpp"

#include <assert.h>
#include <vector>
#include <ctype.h>
#include <stack>
#include <queue>
#include <iostream>
#include <stdexcept>
#include <cstdint>

namespace ExpressionParser
{
    struct Parser
    {
        Parser(const char *input) : m_input{input}
        {
            assert(m_input);
            m_tokens = Lexer{m_input}.tokens();
        }

        enum struct Precedence
        {
            LOWEST,
            SUM,     // +, -
            PRODUCT, // *, /
        };

        static bool higher_precedence(Token *cur_token, Token *past_token)
        {
            return get_precedence(cur_token) > get_precedence(past_token);
        }

        int64_t parse_expression();

    private:
        static Precedence get_precedence(Token *token)
        {
            switch (token->get_type())
            {
            case Token::Type::PLUS:
            case Token::Type::SUBTRACT:
            {
                return Precedence::SUM;
            }
            case Token::Type::MULT:
            case Token::Type::DIVIDE:
            {
                return Precedence::PRODUCT;
            }
            default:
            {
                return Precedence::LOWEST;
            }
            }
        }

        Token *current_token()
        {
            if (m_index >= m_tokens.size())
            {
                return Token::invalid();
            }
            return m_tokens[m_index];
        }

        Token *peek_token()
        {
            if (m_index + 1 >= m_tokens.size())
            {
                return Token::invalid();
            }
            return m_tokens[m_index + 1];
        }

        void advance()
        {
            m_index++;
        }

        const char *m_input{nullptr};
        std::vector<Token *> m_tokens;
        size_t m_index{0};
    };
}
