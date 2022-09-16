#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
/** std::any_of 示例 **/

/**1. 将std::any_of 与lambda函数一起使用 **/
/*
假设有字符串向量，即
std::vector<std::string>> vecOfStrs =
    {"Hi","Hello", "test", "first", "second", "third", "fourth"};

先要检查这个向量中是否有包含大小为4的字符串，让我们使用std::any_of()来做到这一点
bool result = std::any_of(vecOfStrs.begin(), vecOfStrs.end(),
                          [](const std::string& str) {
                            return str.size() == 4;
                          });
std::any_of()将遍历vector中的每个字符串，它将调用传递的lambda函数，该函数检查字符串的大小
是否为4，如果对于任何字符串有大小为4的，则lambda函数返回true, std::any_of()将停止进一步
迭代，并返回true, 否则返回false
*/

std::vector<std::string> tmp1 =
    {"Hi","Hello", "test", "first", "second", "third", "fourth"};

void test1() {

  bool result = std::any_of(tmp1.begin(), tmp1.end(),
                            [](const std::string& s) {
                              return s.size() == 4;
                            });
  std::cout << result << std::endl;
}

/** 检查给定的字符串是否只包含小写字母 **/

void test2() {
  std::string str1 = "testString";
  bool result = std::any_of(str1.begin(), str1.end(), ::isupper);
  if (!result) {
    std::cout << "只包含小写字母" << std::endl;
  } else {
    std::cout << "包含大写字母" << std::endl;

  }
}

int main() {
  // test1();
  test2();

}