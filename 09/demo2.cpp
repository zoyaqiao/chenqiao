#include <iostream>
#include <string>
#include <vector>
#include <codecvt>
#include <fstream>
#include <regex>
#include <cstdlib>
#include <Windows.h>
#include <chrono>


// 关于堆区和栈区的一些思考（为什么要有堆区）

void test1(int& i) {
    std::cout << &i << std::endl;
    std::cout << i << std::endl;
}

void test2(int& i) {
    ++i;
    std::cout << &i << std::endl;
    std::cout << i << std::endl;
}

void test() {
    int i  = 2;
    std::cout << &i << std::endl;
    test1(i);
    test2(i);
    test1(i);
}
/** 关于类的一些思考 **/

/** c++ <<  >> 重载输出运算符和输入运算符 **/
std::ostream & operator<< (std::ostream& os,const std::vector<std::string>& vs)
{
    std::string res;
    res.append("[ ");
    for (auto &v : vs) {
        res.append(v).append(" ");
    }
    res.append("]");

    return os << res;
}

/** 能否通过wstring 来进行分词 
 *  1. 在linux中分词结果可以显现出来
 *  2. 在win中是乱码 **/
std::wstring String2Wstring(const std::string& s) {
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.from_bytes(s);
}
// wstring=>string
std::string WString2String(const std::wstring& ws) {
    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.to_bytes(ws);
}



void splitSentence(const std::string& s1) {
    // std::string s1 = "上海世博会abcd上海世博会abcd上海世博会abcd上海世博会abcd上海世博会abcd上海世博会abcd";
    // std::cout << s1 << std::endl;
    std::wstring ws1 = String2Wstring(s1);
    // std::cout << WString2String(ws1) << std::endl;
    std::vector<std::string> re;
    // std::cout << ws1.size() << std::endl;
    // std::wcout << ws1 << std::endl;
    // std::cout << "*******" << std::endl;
    for (auto ctr = ws1.begin(); ctr != ws1.end(); ++ctr) {
        std::wstring tmp(1, *ctr);
        std::string tmp2 = WString2String(tmp);
        // std::cout << tmp2 << std::endl;
        re.push_back(WString2String(tmp));
    }
    // std::cout << re << std::endl;
}

/** 通过unicode的特性来进行分词 **/
int string2vec(const std::string& source) {
    // std::string source = "上海世博会abcd上海世博会abcd上海世博会abcd上海世博会abcd上海世博会abcd上海世博会abcd";
    std::vector<std::string> result;
    int i = 0;
    while (source[i] != 0) {
        int byteCount;
        if (source[i] & 0x80 && source[i] & 0x40 &&
            source[i] & 0x20) {     /* NOLINT */
            if (source[i] & 0x10) { /* NOLINT */
                byteCount = 4;
            } else {
                byteCount = 3;
            }
        } else if (source[i] & 0x80 && source[i] & 0x40) { /* NOLINT */
            byteCount = 2;
        } else {
            byteCount = 1;
        }
        result.emplace_back(source.substr(i, byteCount));
        i += byteCount;
    }
    // std::cout << result << std::endl;
    return 0;
}

int main() {
    std::string str1 = "上海世博会abcd上海世博会abcd上海世博会abcd上海世博会abcd上海世博会abcd上海世博会abcd";
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0 ;i < 100; ++i) {
        splitSentence(str1);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm = end - start;
    std::cout << "use tm: " << tm.count() / 1000 << "s" << std::endl;

    for (int i = 0 ;i < 100; ++i) {
        string2vec(str1);
    }
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> tm2 = end2 - end;
    std::cout << "use tm: " << tm2.count() / 1000 << "s" << std::endl;
}