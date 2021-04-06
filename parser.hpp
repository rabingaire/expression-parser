#pragma once

#include "lexer.hpp"

#include <assert.h>
#include <vector> // NOTE: implement your own vector
#include <ctype.h>

namespace ExpressionParser
{
    struct Parser
    {
        Parser(const char *input) : m_input{input}
        {
            assert(m_input);
            m_tokens = Lexer{m_input}.tokens();
        }

        size_t parse_expression();

    private:
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

        const char *m_input{nullptr};
        std::vector<Token *> m_tokens;
        size_t m_index{0};
    };
}
