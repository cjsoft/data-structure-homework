#include <cstring>
#include <iostream>
#include <cctype>
#include <cmath>
#include <regex>
#include <string>
namespace dij_exp_eval {
    const int MXN = 100007;
    double base[33] = {1}; // 小数数位基，在读入小数时会用到
    std::map<std::string, std::string> lst = {
        {"cos", " C "},
        {"sin", " S "},
        {"tan", " T "},
        {"sqrt", " R "},
        {"ln", " L "},
        {"floor", " F "},
        {"log", " "},
        {"exp", " E "},
        {",", " l "}
    }; // 建立单参数函数与字符的关联，将函数转化为运算符处理
    template <typename T>
    struct stk {
        T a[MXN];
        int t;
        std::string nme;
        stk(std::string nme): nme(nme) { memset(a, 0, sizeof(a)); t = 0; }
        void push(T x) {
    #ifdef DEBUG // 调试开关
            std::cout << nme << " Instack:\t" << x << std::endl;
    #endif
            a[t++] = x;
        }
        T top() { return a[t - 1]; }
        T pop() {
    #ifdef DEBUG // 调试开关
            std::cout << nme << " Outstack:\t" << a[t - 1] << std::endl;
    #endif
            return a[--t];
        }
        int size() { return t; }
        bool empty() { return t <= 0; }
    }; // 固定大小的模板栈类
    stk<double> num("NUM");
    stk<char> ops("OPS");
    int pri[256]; // 运算符优先级表
    double calc() { // 消除符号栈中的一个运算符号，并根据运算符消去并添加相应元素到数栈
        char op = ops.top();
        double b = num.top();
        ops.pop();
        num.pop();
        if (op == 'L') { // ln
            return log(b);
        } else if (op == 'S') { // sin
            return sin(b);
        } else if (op == 'C') { // cos
            return cos(b);
        } else if (op == 'T') { // tan
            return tan(b);
        } else if (op == 'R') { // sqrt
            return sqrt(b);
        } else if (op == 'F') { // floor
            return int(b);
        } else if (op == 'E') { // exp
            return exp(b);
        }
        double tmp = num.top();
        num.pop();
        if (op == '+') {
            return tmp + b;
        } else if (op == '-') {
            return tmp - b;
        } else if (op == '*') {
            return tmp * b;
        } else if (op == '/') {
            return tmp / b;
        } else if (op == '^') {
            return pow(tmp, b);
        } else if (op == 'l') {
            return log(b) / log(tmp);
        }
    }
    char s[MXN];
    double analyze(const char* sss) { // 准标准表达式解析
        memset(s, 0, sizeof(s));
        while (!num.empty()) num.pop();
        while (!ops.empty()) ops.pop();
        int len = 0, tmp = 0, i, j, k, f;
        double ftmp = 0;
        for (i = 0; sss[i] && sss[i] != '='; ++i) if (pri[sss[i]] || isdigit(sss[i]) || sss[i] == '.') s[len++] = sss[i]; // 消去空格
        // printf("%s\n", s); // 打印标准化表达式
        for (i = 0, f = 1; i < len; ++i, f = 1, tmp = 0, ftmp = 0) {
            if (isdigit(s[i])) { // 处理数字
                tmp = s[i] - '0';
    HELL:;
                for (j = i + 1; j < len && isdigit(s[j]); ++j)
                    tmp = tmp * 10 + s[j] - '0';
                if (s[j] == '.') { // 小数处理
                    for (j++, k = 1; isdigit(s[j]) && j < len; ++j, ++k) {
                        ftmp += base[k] * (s[j] - '0');
                    }
                }
                i = j - 1;
                ftmp += tmp;
                num.push(ftmp * f);
            } else if (pri[s[i]]) {
                if (s[i] == ')') { // 立即处理当前括号对
                    while (ops.top() != '(')
                        num.push(calc());
                    ops.pop();
                } else if (s[i] == '-' && (i == 0 || i && !isdigit(s[i - 1]) && s[i - 1] != ')')) { // 捕获到负数，交由数字处理部分进行处理
                        f = -f;
                        goto HELL;
                } else if (ops.empty() || s[i] == '(' || pri[ops.top()] < pri[s[i]] || (pri[ops.top()] >= 5 && pri[ops.top()] == pri[s[i]])) { // 压运算符栈
                    ops.push(s[i]);
                } else {
                    while (!ops.empty() && pri[ops.top()] >= pri[s[i]]) // 处理栈顶元素直到满足压栈要求
                        num.push(calc());
                    ops.push(s[i]);
                }
                
            }
        }
        while (!ops.empty()) // 解算最终结果
            num.push(calc());
        return num.top();
    }
    bool inittag = false; // 第一次调用时将进行初始化
    double solve(char rs[]) {
        if (!inittag) {
            for (int i = 1; i < 33; ++i) base[i] = base[i - 1] / 10; // 初始化小数数位基
            pri['('] = 1; // 初始化优先级表
            pri['l'] = 2;
            pri['+'] = 3;
            pri['-'] = 3;
            pri['*'] = 4;
            pri['/'] = 4;
            pri['^'] = 5;
            pri['C'] = 6;
            pri['S'] = 6;
            pri['L'] = 6;
            pri['R'] = 6;
            pri['E'] = 6;
            pri['F'] = 6;
            pri['T'] = 6;
            pri[')'] = 20;
        }
        std::string s(rs);
        for (auto const &i : lst)
            s = std::regex_replace(s, std::regex(i.first, std::regex::icase), i.second); // 将函数字符串替换成字符
        return analyze(s.c_str()); // 解析表达式
    }
    double solve(std::string s) {
        if (!inittag) {
            for (int i = 1; i < 33; ++i) base[i] = base[i - 1] / 10; // 初始化小数数位基
            pri['('] = 1; // 初始化优先级表
            pri['l'] = 2;
            pri['+'] = 3;
            pri['-'] = 3;
            pri['*'] = 4;
            pri['/'] = 4;
            pri['^'] = 5;
            pri['C'] = 6;
            pri['S'] = 6;
            pri['L'] = 6;
            pri['R'] = 6;
            pri['E'] = 6;
            pri['F'] = 6;
            pri['T'] = 6;
            pri[')'] = 20;
        }
        for (auto const &i : lst)
            s = std::regex_replace(s, std::regex(i.first, std::regex::icase), i.second); // 将函数字符串替换成字符
        return analyze(s.c_str()); // 解析表达式
    }
}

int main() {
    std::string s;
    while (true) {
        std::getline(std::cin, s);
        if (!std::cin) break;
        std::cout << dij_exp_eval::solve(s) << std::endl;
    }
}