#include <vector>

#include "../../test_utils.h"
#include "./operaciones_seq.h"

struct OpNode
{
    Op op;
    std::shared_ptr<OpNode> parent;
    OpNode(Op o, std::shared_ptr<OpNode> p) : op(o), parent(p) {}
};

struct Node
{
    int idx;
    int acc;
    std::shared_ptr<OpNode> op_node;
};

class Solution
{
  public:
    std::vector<std::string> operaciones_seq(std::vector<int> v, int w)
    {
        std::vector<std::string> result;
        std::vector<std::vector<Node>> dp(w + 1);
        dp[v[0]].push_back({0, v[0], nullptr});

        for (int j = 0; j <= w; j += 1)
        {
            std::vector<Node> current_nodes = dp[j];
            for (const Node &node : current_nodes)
            {
                int next_idx = node.idx + 1;
                if (next_idx == v.size())
                    continue;

                int acc = node.acc;
                int next_num = v[next_idx];

                create_next_node(v, w, dp, node, acc + next_num, Op::Add);
                create_next_node(v, w, dp, node, acc * next_num, Op::Mul);
                create_next_node(v, w, dp, node, std::pow(acc, next_num), Op::Pow);
            }
        }

        for (Node &node : dp[w])
        {
            if (node.idx < v.size() - 1)
                continue;
            result.push_back(build_expression_from_op_node(v, node.op_node));
        }

        return result;
    }

  private:
    void create_next_node(std::vector<int> &v, int w, std::vector<std::vector<Node>> &dp,
                          const Node &node, int next_acc, Op op)
    {

        if (next_acc > w)
            return;

        int next_idx = node.idx + 1;
        auto next_op_node = std::make_shared<OpNode>(op, node.op_node);
        dp[next_acc].push_back({next_idx, next_acc, next_op_node});
    }

    std::string build_expression_from_op_node(std::vector<int> &v, std::shared_ptr<OpNode> node)
    {
        std::vector<Op> ops;
        while (node)
        {
            ops.push_back(node->op);
            node = node->parent;
        }
        std::reverse(ops.begin(), ops.end());
        return build_expression(v, ops);
    }
};

int main()
{
    Solution solution;

    std::vector<int> v_0 = {1, 1};
    int w_0 = 1;
    std::vector<std::string> expected_0 = {"(1*1)", "(1^1)"};
    std::vector<std::string> actual_0 = solution.operaciones_seq(v_0, w_0);
    assert_set_equals(actual_0, expected_0);

    std::vector<int> v_1 = {3, 1, 5, 2, 1};
    int w_1 = 400;
    std::vector<std::string> expected_1 = {"((((3+1)*5)^2)*1)", "((((3+1)*5)^2)^1)"};
    std::vector<std::string> actual_1 = solution.operaciones_seq(v_1, w_1);
    assert_set_equals(actual_1, expected_1);

    std::vector<int> v_2(20, 1);
    int w_2 = 20;
    std::vector<std::string> actual_2 = solution.operaciones_seq(v_2, w_2);
    std::vector<std::string> expected_2 = {
        "(((((((((((((((((((1+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)+1)"};
    assert_set_equals(actual_2, expected_2);

    std::cout << "✅ Todos los tests pasaron" << std::endl;
    return 0;
}
