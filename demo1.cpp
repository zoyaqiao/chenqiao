#include <iostream>
#include <regex>
using namespace std;
/** 判断一个输入的qq号是否有效
 *  判断步骤：
 *  1. 长度大于5，小于等于11
 *  2. 首位不能为0
 *  3，是否为纯数字 **/
int isValid() {
    regex qq_req("[1-9]\\d{5,10}");
    string qq = "11985119851";
    smatch result;
    bool ret = regex_match(qq, result, qq_req);
    cout << (ret ? "cunzai" : "bucunzai") << endl;
    return 0;

}

/** 匹配match
 * 用于匹配的模板函数为std::regex_match()
 * 
 * bool regex_match(string s, regext pattern)
 * bool regex_match(string s, smatch result, regex pattern)
 * bool regex_match(s.cbegin() + i, s.cend(), smatch result, regex pattern)
 */
void match() {
    // 9 + [3578]中的一个数字 + %[0-9]匹配9次
    regex pattern("中");
    string s = "中华人民共和国";
    smatch result;
    bool is_match = regex_match(s, result, pattern);
    if (is_match) {
        cout << "sucess match" << result[0] << endl;
    } else {
        cout << "fail match" << endl;
    }
}

/**搜索search
 * 
 * [搜索]与[匹配]非常相像，其对应的函数为std::regex_search 也是一个模板函数，
 * 用法和regex_match一样，不同在于搜索，只要字符串出现目标就会返回，而非完全匹配
 * 
 * bool regex_search(string s, regex pattern)
 * bool regex_search(string s, smatch result, regex pattern)
 * bool regex_search(s.cbegin() + i, s.cend(), smatch result, regex pattern)
 * 
 * 搜索给定字符串中是否存在于模式匹配的子串，如果存在返回true
 * 同样用samtch记录结果，但不同的是result[0]记录的是整个字符串从左往右第一个匹配模式的子串
 * 假如有多个子串符合模式，若想知道result[0]存储的是第几个子串，可用result.position()函数
 * 返回数从0开始
 */

void search() {
    regex pattern("\\d+");
    string s = "51x41+(5-13/2)x3a";
    smatch result;
    string::const_iterator iter_begin = s.cbegin();
    string::const_iterator iter_end = s.cend();
    while(regex_search(iter_begin, iter_end, result, pattern)) {
        cout << "查找成功: "  << result[0] << endl;
        cout << "查找结果子串在源串中的迭代器位置：" << *result[0].first << endl;
        cout << "查找结果子串在源串后面的迭代器位置：" << *result[0].second << endl;
        iter_begin = result[0].second;
    }
}

/**替换 
 * 最后一种操作为替换，即将正则表达式的内容替换成指定内容，
 * regex模板库函数std::regex_replace提供替换操作
 */
void replace() {
    char data[] = "he....ll..o,..wor..l.....d";
    regex reg("\\.+");
    cout << regex_replace(data, reg, "");
}

int main() {
    // isValid();
    match();
    // search();
    // replace();
}