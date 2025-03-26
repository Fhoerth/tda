#include <string>
#include <vector>

#include "../../test_utils.h"

class Solution
{
  public:
    Solution() : alphabet("ABCDEFGHIJKLMNNOPQRSTUVWXYZ") {}

    int dobra(const std::string &s) { return backtrack(s, 0); }

  private:
    const std::string alphabet;

    bool is_vowel(char c) { return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'; }
    bool is_valid(const std::string &s)
    {
        int consecutive_vowels = 0;
        int consecutive_cons = 0;

        bool has_L = false;

        for (char c : s)
        {
            if (c == 'L')
                has_L = true;

            if (is_vowel(c))
            {
                consecutive_vowels++;
                consecutive_cons = 0;
            }
            else
            {
                consecutive_cons++;
                consecutive_vowels = 0;
            }

            if (consecutive_vowels == 3 || consecutive_cons == 3)
                return false;
        }

        return has_L;
    }

    // Complexity: O(27^x) where x=#(_) in s
    int backtrack(const std::string &s, int i)
    {
        if (i == s.size())
            return is_valid(s) ? 1 : 0;

        char current_char = s[i];
        int total = 0;

        if (current_char == '_')
            for (char ch : alphabet)
            {
                std::string next_s = s;
                next_s[i] = ch;
                total += backtrack(next_s, i + 1);
            }
        else
            total += backtrack(s, i + 1);

        return total;
    }
};

int main()
{
    Solution solution_1;
    std::cout << solution_1.dobra("R__D__P") << std::endl;
    return 0;
}