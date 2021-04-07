#include "parser.hpp"

namespace ExpressionParser
{
    int64_t Parser::parse_expression()
    {
        // shunting yard algorithm
        std::queue<Token *> literal_queue;
        std::stack<Token *> operator_stack;

        while (!this->current_token()->is_eol())
        {
            assert(this->current_token()->is_valid());

            if (this->current_token()->is_number())
            {
                literal_queue.push(this->current_token());
            }

            if (this->current_token()->is_operator())
            {
                if (operator_stack.empty())
                {
                    operator_stack.push(this->current_token());
                }
                else
                {
                    if (!Parser::higher_precedence(this->current_token(), operator_stack.top()))
                    {
                        literal_queue.push(operator_stack.top());
                        operator_stack.pop();
                        continue;
                    }
                    operator_stack.push(this->current_token());
                }
            }

            if (this->current_token()->is_open_paren())
            {
                operator_stack.push(this->current_token());
            }

            if (this->current_token()->is_close_paren())
            {
                while (!operator_stack.top()->is_open_paren())
                {
                    literal_queue.push(operator_stack.top());
                    operator_stack.pop();
                }
                operator_stack.pop();
            }

            advance();
        }

        while (!operator_stack.empty())
        {
            literal_queue.push(operator_stack.top());
            operator_stack.pop();
        }

        // evaluate expression
        std::stack<int64_t> evaluation_stack;

#ifdef DEBUG_PARSER
        std::cout << "### DEBUG_PARSER:" << std::endl;
#endif

        while (!literal_queue.empty())
        {

#ifdef DEBUG_PARSER
            literal_queue.front()->debug_print_token();
#endif

            if (literal_queue.front()->is_number())
            {
                evaluation_stack.push(literal_queue.front()->get_number_literal());
            }

            if (literal_queue.front()->is_operator())
            {
                int64_t right{0}, left{0};

                if (!evaluation_stack.empty())
                {
                    right = evaluation_stack.top();
                    evaluation_stack.pop();
                }

                if (!evaluation_stack.empty())
                {
                    left = evaluation_stack.top();
                    evaluation_stack.pop();
                }

                switch (literal_queue.front()->get_type())
                {
                case Token::Type::PLUS:
                {
                    evaluation_stack.push(left + right);
                    break;
                }
                case Token::Type::SUBTRACT:
                {
                    evaluation_stack.push(left - right);
                    break;
                }
                case Token::Type::MULT:
                {
                    evaluation_stack.push(left * right);
                    break;
                }
                case Token::Type::DIVIDE:
                {
                    evaluation_stack.push(left / right);
                    break;
                }
                default:
                {
                    std::runtime_error("Parse Error: Invalid token type");
                }
                }
            }

            literal_queue.pop();
        }

#ifdef DEBUG_PARSER
        std::cout << std::endl;
#endif

        return evaluation_stack.top();
    }
}
