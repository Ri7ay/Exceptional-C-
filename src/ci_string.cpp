#include <string>
#include <cstring>
#include <cassert>
#include <type_traits>

struct ci_char_traits : public std::char_traits<char> {
    static bool eq(char lhs, char rhs) {
        return std::tolower(lhs) == std::tolower(rhs);
    }

    static bool lt(char lhs, char rhs) {
        return std::tolower(lhs) < std::tolower(rhs);
    }

    // if s1 > s2  ->  1
    // if s1 == s2 ->  0
    // if s1 < s2  -> -1
    static int compare(const char *s1,
                       const char *s2,
                       size_t n) {
        // return std::memicmp(s1, s2, n); for g++ compiler
        while ((*s1 != '\0' || *s2 == '\0') && n-- > 0) {
            if (std::tolower(*s1) > std::tolower(*s2)) {
                return 1;
            } else if (std::tolower(*s1) < std::tolower(*s2)) {
                return -1;
            }
            ++s1;
            ++s2;
        }
        if (*s1 != '\0' && *s2 == '\0') {
            return 1;
        } else if (*s1 != '\0' && *s2 == '\0') {
            return -1;
        }
        return 0;
    }

    static const char *find(const char *s, int n, char a) {
        while (n-- > 0 && toupper(*s) != toupper(a)) {
            ++s;
        }
        return n >= 0 ? s : nullptr;
    }
};

typedef std::basic_string<char, ci_char_traits> ci_string;

int main() {
    ci_string s("AbCdE");
    // Нечувствительно к регистру
    assert(s == "abcde");
    assert(s == "ABCDE");
    assert(s != "abc");
    assert(s.compare("abcdee") == -1);
    // Остается чувствительно к регистру
    assert(strcmp(s.c_str(), "AbCdE") == 0);
    assert(strcmp(s.c_str(), "abcde") != 0);
    return 0;
}
