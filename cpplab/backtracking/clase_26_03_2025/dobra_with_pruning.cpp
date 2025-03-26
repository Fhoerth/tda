#include <iostream>
#include <string>

class SolutionWithPruning
{

  public:
    int dobra(const std::string &s) { return backtrack(s, 0, 0, 0, false); }

  private:
    bool is_vowel(char c) { return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'; }

    bool is_consonant(char c) { return ('A' <= c && c <= 'Z') && !is_vowel(c); }

    int backtrack(const std::string &s, int i, int consecutive_vowels, int consecutive_cons,
                  bool has_L)
    {
        if (consecutive_vowels == 3 || consecutive_cons == 3)
            return 0;

        if (i == s.size())
            return has_L ? 1 : 0;

        char c = s[i];
        int total = 0;

        if (c == '_')
        {
            // Try 5 vowels
            total += 5 * backtrack(s, i + 1, consecutive_vowels + 1, 0, has_L);

            // Try 21 consonants (excluding L)
            total += 21 * backtrack(s, i + 1, 0, consecutive_cons + 1, has_L);

            // Try L
            total += backtrack(s, i + 1, 0, consecutive_cons + 1, true);
        }
        else
        {
            bool b_is_vowel = is_vowel(c);
            bool is_L = (c == 'L');

            total += backtrack(s, i + 1, b_is_vowel ? consecutive_vowels + 1 : 0,
                               (!b_is_vowel ? consecutive_cons + 1 : 0), has_L || is_L);
        }

        return total;
    }
};

int main()
{
    SolutionWithPruning solution;
    std::cout << solution.dobra("R__D__P") << std::endl;
    return 0;
}
