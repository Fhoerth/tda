#ifndef OPERACIONES_SEQ_H
#define OPERACIONES_SEQ_H

#include <algorithm>
#include <string>
#include <vector>

enum class Op
{
    Add = 0,
    Mul = 1,
    Pow = 2
};

std::string op_to_char(Op op)
{
    switch (op)
    {
    case Op::Add:
        return "+";
    case Op::Mul:
        return "*";
    case Op::Pow:
        return "^";
    }
    return "?";
}

std::string build_expression(const std::vector<int> &values, const std::vector<Op> &ops)
{
    std::string expr = std::to_string(values[0]);

    for (size_t i = 0; i < ops.size(); ++i)
        expr = "(" + expr + op_to_char(ops[i]) + std::to_string(values[i + 1]) + ")";

    return expr;
}

#endif // EXPRESSION_UTILS_H