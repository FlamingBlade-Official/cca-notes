# 0x00 从变量到函数

你已经知道怎么写简单的 C++ 程序了——会定义变量、会用 `cin/cout`、会写 `if` 和 `for`。但是，能写出**正确**的代码和能写出**不会悄悄出错**的代码，中间隔着一堆细节。这一章帮你把这堆细节填上。

读完这一章，你应该能轻松写出后面所有章节需要的代码。

---

## 0x01 变量与数据类型

C++ 里每个变量都有类型。类型决定两件事：**能存什么**，**占多少空间**。

```cpp
int a = 42;           // 整数，4 字节，范围约 ±2.1×10^9
long long b = 1e18;   // 大整数，8 字节，范围约 ±9×10^18
double x = 3.14;      // 浮点数，~15 位有效数字
char c = 'A';         // 单个字符
bool flag = true;     // 只有 true 或 false
string s = "hello";   // 字符串（需要 #include <string>）
```

### 整数除法

两个 `int` 相除，结果还是 `int`，小数部分被**直接丢弃**。

```cpp
cout << 5 / 2;      // 2，不是 2.5，注意这里是向 0 取整而不是向下取整
cout << 5.0 / 2;    // 2.5（有一边是 double 就行）
```

### int 溢出

`int` 最大约 21 亿。超出这个范围，值会"绕回去"变成负数——编译器不会报错，结果悄悄错了，我们会在下一章节详细讨论为什么他会爆成负数。

```cpp
int a = 100000, b = 100000;
cout << a * b;      // 溢出，输出垃圾
cout << (long long)a * b;  // 正确：先转成 long long 再乘
```

竞赛里，只要涉及乘法或累加和，**默认用 `long long`**，除非你确定不会超出数据上限。

### 强制类型转换

把一种数据类型临时转成另一种。你告诉编译器："把这个当成别的东西看。"

**隐式转换（自动发生）**

```cpp
int a = 5;
double b = a;        // int 自动变成 double，b = 5.0
double c = 3.14;
int d = c;           // double 自动变成 int，小数被截掉，d = 3（不是四舍五入！）
```

**强制转换（你主动要求）**

```cpp
int a = 5, b = 2;
cout << a / b;              // 输出 2（整数除法，丢弃小数）
cout << (double)a / b;      // 输出 2.5——把 a 临时当 double 用
cout << 1.0 * a / b;        // 输出 2.5——另一种常用手法，乘个 1.0
```

三种写法等价，挑你喜欢的：

```cpp
(double)a / b                // C 风格
static_cast<double>(a) / b   // C++ 推荐：最安全，意图最明确
double(a) / b                // C++ 函数风格
```

**竞赛中最常见的三个场景**

```cpp
// 场景一：避免整数除法
int a = 5, b = 2;
cout << (double)a / b;       // 2.5，不是 2

// 场景二：char 转 ASCII 码
char c = 'A';
cout << (int)c;              // 65

// 场景三：long long 和 int 混合运算防溢出
int a = 100000, b = 100000;
long long ans = (long long)a * b;   // 10^10，int 装不下，必须转
```

### = 和 ==

```cpp
if (x = 5)   // 把 5 赋给 x，条件永远为 true——几乎不会是你要的
if (x == 5)  // 比较 x 是否等于 5
```

每次写 `if`，脑子里过一遍：这里是要"比较"还是"赋值"？

---

## 0x02 输入输出

```cpp
int n;
cin >> n;                       // 读入整数
cout << n * 2 << endl;          // 输出，endl 换行

int a, b;
cin >> a >> b;                  // 连续读入，空格或换行分隔均可
cout << a + b << endl;
```

### cin 和 getline 混用

`cin >> n` 读完数字后，**换行符还留在缓冲区**。紧接着 `getline(cin, s)` 会读到这个换行符，得到空串。

```cpp
int n; cin >> n;
cin.ignore();                   // 吃掉残留的换行符
string s; getline(cin, s);      // 现在正常了
```

### scanf / printf（选学）

```cpp
int n; scanf("%d", &n);                    // %d: int
long long x; scanf("%lld", &x);            // %lld: long long
double y; scanf("%lf", &y);                // %lf: double
printf("%.2f\n", y);                       // 保留两位小数，我感觉这个是我使用 printf 的唯一理由
```

`cin/cout` 日常够用。

在竞赛中，我推荐你只使用一种读入，例如只使用 ```cin/cout``` 或者是只使用 ```printf/scanf```，因为在竞赛中我们可能经常需要使用 
```c++
ios::sync_with_stdio(false);
cin.tie(0);
```

进行快速读写，会导致缓存区发生一些奇怪的错误，使得你的读入和输出爆炸！

---

## 0x03 运算符

```cpp
+  -  *     // 加减乘
/           // 除——整数除法截断
%           // 取余——只能用于整数
```

### 取余

```cpp
if (n % 2 == 0) cout << "偶数";
if (n % 2 == 1) cout << "奇数";
```

取余也常用于"限制范围"：`x % 10` 一定在 $0\sim9$ 之间。

### 简写

```cpp
cnt++;       // 等价 cnt = cnt + 1
sum += x;    // 等价 sum = sum + x
a %= b;      // 等价 a = a % b
```

### 前置 ++ 和后置 ++

```cpp
int a = 5;
int b = a++;  // b = 5, a = 6（先用再+1）
int c = ++a;  // c = 7, a = 7（先+1再用）
```

竞赛里后置 `++` 基本够用。唯一要注意：不要把 `a++` 和 `++a` 混在复杂表达式里，分开写最安全。

---

## 0x04 条件判断

```cpp
if (条件) {
    // ...
} else if (另一个条件) {
    // ...
} else {
    // ...
}
```

### 比较运算符

`==` `!=` `<` `>` `<=` `>=`

### 逻辑运算符

| 运算符 | 含义 | 示例 |
|--------|------|------|
| `&&` | 且 | `x > 0 && x < 100` 意味着 $x$ 得在 $(0,100)$ 之间 |
| `\|\|` | 或 | `c == 'Y' || c == 'y'` 意味着 $c$ 得是大写或者小写 $y$。 |
| `!` | 非 | `if (!done)` 即 `done == false` |

### 短路求值

`&&` 左边为 `false` 时，右边**根本不会执行**。利用这一点可以安全地写：

```cpp
if (x != 0 && 10 / x > 2)   // x=0 时不会执行 10/x，安全
if (10 / x > 2 && x != 0)   // 危险！可能除以 0
```

把最可能为 `false` 的条件放 `&&` 左边，最安全的检查放在前面。

### 浮点数比较

```cpp
double a = 0.1 + 0.2;              // 实际存的是 0.30000000000000004
if (a == 0.3) { /* false! */ }
if (abs(a - 0.3) < 1e-9) { /* 这才是对的 */ }
```

浮点数用 `abs(a - b) < 1e-9` 判断"足够接近"。

---

## 0x05 循环

### for——知道循环次数

```cpp
for (int i = 1; i <= n; i++) {
    cout << i << ' ';
}
// 输出 1 2 3 ... n
```

三段式：①起点 `int i = 1`、②继续条件 `i <= n`、③每轮变化 `i++`。判断逻辑为：

1. 执行 ① 中的命令
2. 判断条件 ② 是否满足，若满足跳转到第三步，否则终止
3. 执行 ```for``` 语句内的内容
4. 执行条件 ③，跳转回第二步

### while——不知道循环次数

```cpp
while (n > 1) {
    if (n % 2 == 0) n /= 2;
    else n = 3 * n + 1;
}
```

但是通常来说 ```while``` 有点没有用，因为 ```while``` 完全可以被 ```for``` 代替！

### break 和 continue

```cpp
for (int i = 1; i <= 10; i++) {
    if (i == 5) break;       // 直接跳出整个循环
    if (i % 2 == 0) continue; // 跳过本轮，进入下一轮（直接跳转到 i++)
    cout << i << ' ';         // 只输出 1 3
}
```

| | 效果 |
|--|------|
| `break` | 彻底退出循环 |
| `continue` | 跳过本轮剩余代码 |

### 多组数据输入

竞赛题常见格式：第一行 T，接下来 T 组数据。

```cpp
int T; cin >> T;
while (T--) {
    int a, b; cin >> a >> b;
    cout << a + b << endl;
}
```

读入直到文件末尾（EOF）：

```cpp
int a, b;
while (cin >> a >> b) {   // 读到没数据时自动结束
    cout << a + b << endl;
}//但这种情况通常比较少见
```

---

## 0x06 数组

### 一维数组

```cpp
int a[100];                                   // 开 100 个 int
for (int i = 0; i < n; i++) cin >> a[i];      // 读入 n 个
for (int i = 0; i < n; i++) cout << a[i] << ' ';
```

### 下标从 0 开始

```cpp
int a[5] = {10, 20, 30, 40, 50};
// a[0]=10  a[1]=20  a[2]=30  a[3]=40  a[4]=50
// 没有 a[5]！注意到编程中下标从 0 开始
```

最后一个元素是 `a[n-1]`，不是 `a[n]`。记住这一点就已经避开了竞赛里最常见的 bug。

### 二维数组

```cpp
int grid[100][100];
for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        cin >> grid[i][j];   // grid[i][j] = 第 i 行第 j 列
```

### 四大易错点

**① 越界**

```cpp
int a[100];
for (int i = 1; i <= 100; i++) a[i] = i;  // a[100] 不存在！
```

数组大小为 $N$，合法下标是 $0 \sim N-1$。如果你习惯下标从 $1$ 开始写 `for (int i = 1; i <= n; i++)`，开数组时记得开 `a[n+5]`（多留一点余量）。

有不少竞赛中的错误源自于数组的越界而导致的 ```Runtime Error``` 或者 ```Wrong Answer```。取决于你越界到哪里。

**② 未初始化**

```cpp
int a[100];          // 局部数组——值是随机垃圾
cout << a[0];        // 可能是任何值
```

这也就是为什么我们建议你把数组的定义放在函数外开成全局数组，这样所有的默认值都是 $0$。

**③ 局部数组过大**

```cpp
void f() {
    int a[1000000];  // 100 万可能爆栈
}
```

我们强烈建议你把大数组（$>10^5$ ）放到全局定义里。

**④ 变长数组**

```cpp
int n; cin >> n;
int a[n];            // 不标准，不要用
```

用固定大小：`const int N = 100005; int a[N];`或后面学 `vector`。

---

## 0x07 函数

你已经写过 `main()` 了——它本身就是一个函数。你也调用过别人的函数：`swap(a, b)`、`sort(a, a+n)`、`abs(x)`。现在轮到你写自己的函数了。

### 为什么需要函数

假设你需要判断一个数是不是质数，而且这段逻辑在程序里出现了三次。你可以：

- **方案 A**：把判断质数的代码复制粘贴三遍。改一个 bug 要改三处。
- **方案 B**：写一个 `isPrime(n)` 函数，每次调用一行。

函数让你把一段逻辑**打包、起名、复用**。代码变短，也更容易改。

### 函数的四个要素

```cpp
int Max(int a, int b) {  /*
 ①  ②       ③
*/
    if (a > b) return a;  // ④
    else return b; // ④
}
```

| 要素 | 位置 | 说明 |
|------|------|------|
| ① 返回类型 | `int` | 这个函数返回什么类型的值 |
| ② 函数名 | `max` | 和变量命名规则一样 |
| ③ 参数列表 | `(int a, int b)` | 调用时需要传什么进去 |
| ④ 返回值 | `return a;` | 把结果扔回去，类型必须匹配①，如果不匹配会进行强制转换。 |

调用：

```cpp
int result = Max(10, 20);  // result = 20
cout << Max(3, 7);          // 输出 7
```

### void 函数——不返回东西

有些函数干活但不返回值。比如打印一行分隔线：

```cpp
void printLine() {
    cout << "----------" << endl;
    // 没有 return——或者说 return 可写可不写
}

int main() {
    printLine();  // 直接调用
    printLine();
    return 0;
}
```

`void` 就是"空的"——这个函数不产生任何值，它只是做事情。

### 参数：传值 vs 传引用

**传值（默认）**：函数拿到的是变量的副本，改副本不影响原变量。

```cpp
void addOne(int x) {
    x = x + 1;       // 改的是副本
}

int main() {
    int n = 5;
    addOne(n);
    cout << n;        // 还是 5！
    return 0;
}
```

**传引用**：加上 `&`，函数直接操作原变量。

```cpp
void addOne(int &x) {  // 注意那个 &
    x = x + 1;         // 改的是原变量
}

int main() {
    int n = 5;
    addOne(n);
    cout << n;          // 6
    return 0;
}
```

什么时候用引用？

- 需要"返回"多个值时（函数只能 `return` 一个值，但可以通过引用参数往外带）
- 传大的东西（比如 `vector`、`string`）不想复制一份时——加 `const`：`void print(const string &s)`，又安全又高效

### 值返回 vs 引用返回

```cpp
int square(int x) { return x * x; }          // 返回一个值——最常见
int& getElement(int a[], int i) { return a[i]; }  // 返回引用——可以修改数组元素
```

初学阶段几乎只用值返回。返回引用是高级用法，先记住它存在就好。

### 声明和定义可以分开

有时候你希望 `main` 写在前面，辅助函数写在后面。编译器从上往下读，遇到没见过的函数名会报错。解决办法：先在顶部**声明**，后面再**定义**。

```cpp
#include <iostream>
using namespace std;

// 声明——只写函数头，不写函数体
int max(int a, int b);
void printLine();

int main() {
    cout << max(3, 5) << endl;
    printLine();
    return 0;
}

// 定义——完整的函数体
int max(int a, int b) {
    return (a > b) ? a : b;
}

void printLine() {
    cout << "----------" << endl;
}
```

### 递归——函数调用自己

一个函数直接或间接调用自己，叫递归。

最经典的例子：计算 n! = 1×2×3×...×n。

```cpp
int factorial(int n) {
    if (n == 0) return 1;             // 终止条件——没有这行会无限递归
    return n * factorial(n - 1);      // n! = n × (n-1)!
}

// factorial(5) = 5 * factorial(4)
//              = 5 * 4 * factorial(3)
//              = ... = 120
```

递归的两个必备要素：

1. **终止条件**（base case）：递归要有尽头，不然就死循环了
2. **每次向终止条件靠近一步**：`factorial(n-1)` 比 `factorial(n)` 更接近 `n=0`

递归是后面搜索、分治、动态规划的基础。现在你只需要能看懂递归、能写出最简单的递归函数就行了。

### 作用域——变量在哪活着

```cpp
int global = 10;         // 全局变量——整个程序都能访问

void f() {
    int x = 5;           // 局部变量——只在这个函数里有效
    cout << global;      // 可以访问全局
}

int main() {
    int y = 3;
    f();
    // cout << x;        // 报错！x 是 f() 的局部变量，这里看不到
    // cout << y;        // 可以，y 是 main 的局部变量
}
```

一条规律：变量在哪对大括号里定义的，就在哪对大括号里活着。出了大括号就死了。

### 常见陷阱

**① 返回局部变量的引用（严重 bug）**

```cpp
int& f() {
    int x = 5;
    return x;   // 危险！x 在函数结束时销毁，返回的是垃圾
}
```

局部变量在函数结束时就不在了。返回引用指向一个已经不存在的变量——这叫"悬垂引用"，结果是未定义的。初学阶段，函数返回类型用 `int`、`bool`、`void` 就够，不要返回 `int&`。

**② 忘记 return**

```cpp
int max(int a, int b) {
    if (a > b) return a;
    // 如果 a <= b，没有 return——undefined behavior！
}
```

编译器可能不报错，但程序行为不可预测。确保每个分支都有 `return`，或者在函数末尾补一个。

注意你的 ```main``` 函数也需要添加 ```return 0```！不然有概率导致程序不正常！

**③ 传引用时传入临时值**

```cpp
void f(int &x) { x++; }
f(5);  // 报错！5 是字面量，不能绑定到非 const 引用
```

**④ 递归忘记终止条件**

```cpp
int f(int n) {
    return n * f(n - 1);  // 没有 if 判断——无限递归，栈溢出
}
```

### 数组如何传给函数

```cpp
void printArray(int a[], int n) {  // 数组参数 + 大小参数
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    printArray(arr, 5);
    return 0;
}
```

数组作为参数传递时，实际上传的是**指针**，所以函数内修改 `a[i]` 会影响原数组（不需要加 `&`）。同时你必须把数组大小也传进去，因为函数内部无法知道数组有多大。

> 以后学了 `vector`，`printVector(vector<int> &v)` 可以调用 `.size()`，就不用额外传大小了。

---

## 0x08 结构体

数组把**同类型**的数据捆在一起。结构体把**不同类型**但属于同一个东西的数据捆在一起。

### 定义和使用

```cpp
struct Student {
    string name;
    int age;
    double score;
};  // 注意分号！

int main() {
    Student s1;
    s1.name = "Alice";
    s1.age = 16;
    s1.score = 95.5;

    cout << s1.name << " scored " << s1.score << endl;
    return 0;
}
```

结构体就是自定义类型——和 `int`、`string` 一样，可以声明变量、建数组、传参。用 `.` 访问成员。

### 初始化

```cpp
Student s1 = {"Bob", 17, 88.0};    // 按定义顺序依次赋值
Student s2{"Carol", 16, 92.5};     // 也可以省略等号
```

### 结构体数组

```cpp
Student a[50];              // 50 个学生
for (int i = 0; i < n; i++)
    cin >> a[i].name >> a[i].age >> a[i].score;
```

### 结构体嵌套

```cpp
struct Date { int year, month, day; };

struct Student {
    string name;
    Date birthday;          // 结构体里放结构体
    double score;
};

// 访问：s.birthday.year
```

### 结构体作为函数参数

```cpp
void print(const Student &s) {   // const 引用：只读不复制，高效
    cout << s.name << endl;
}

void update(Student &s, double ns) {  // 引用：能改动原数据
    s.score = ns;
}
```

和普通变量一样：传值复制一份，加 `&` 传引用操作原数据。结构体可能很大，传引用更高效。

### 结构体 vs 数组 vs 变量

| 场景 | 用什么 |
|------|--------|
| 一堆同类型的数 | `int a[100]` |
| 不同类型但属于同一个东西 | `struct Student s` |
| 一堆结构体 | `Student a[50]` |

### 常见陷阱

**① 忘了分号**

```cpp
struct Point { int x, y; }   // 编译错误！末尾缺 ;
```

**② 用 `==` 比较两个结构体**

```cpp
Student a = {"Alice", 16, 90.0};
Student b = {"Alice", 16, 90.0};
if (a == b) { /* 编译错误！结构体不能直接用 == */ }
```

需要手动比较每个字段。等学了运算符重载可以解决。

**③ 内存对齐**

结构体在内存中可能插入填充字节（padding），`sizeof(StructName)` 可能比成员大小之和略大。初学不用深究，先知道有这回事。感兴趣的同学可以去做一下课后作业的 P9754 [CSP-S 2023] 结构体。

## 0x09 复杂度分析

你学会了写 `for` 循环，可能也感觉到一个循环跑 $N$ 次时，$N$ 越大越慢。但究竟慢了多少？两个不同的算法怎么比较而不必把两个都写出来？这就是复杂度分析要解决的问题。

读完本章你将能够：
- 读懂 $O(n)$、$O(n^2)$、$O(\log n)$ 并明白它们的意思  
- 估算你的解法是否能在时限内跑完（通常 1 秒 ≈ $10^9$ 次简单运算）  
- 根据数据范围选择合适的算法  

---

### 什么是复杂度？

- **时间复杂度**：运行时间随输入规模 $n$ 的增长规律。  
- **空间复杂度**：内存占用随 $n$ 的增长规律。

我们用**大 O 记号**描述最坏情况下的增长阶，忽略常数和低次项。

| 大 O          | 常见称呼 | 1 秒内可处理的 $n$（C++ 参考） |
| ------------- | -------- | ------------------------------ |
| $O(1)$        | 常数     | 任意                           |
| $O(\log n)$   | 对数     | 极大，如 $10^{18}$             |
| $O(\sqrt{n})$ | 平方根   | $\approx 10^{12}$              |
| $O(n)$        | 线性     | $10^7$                         |
| $O(n \log n)$ | 对数线性 | $5 \times 10^5 \sim 10^6$      |
| $O(n^2)$      | 平方     | $5000$                         |
| $O(n^3)$      | 立方     | $500$                          |
| $O(2^n)$      | 指数     | $20\sim 25$                    |

> 以上数字是典型 OJ 上 C++ 的大致经验值。如果你的代码常数很大（如多次除法、大量 `set` 操作或递归），最好把 $n$ 再压低一些。

---

### 简单代码的分析方法

**规则一：顺序语句相加** – 取最高阶项。

```cpp
for (int i = 0; i < n; i++)  // O(n)
    do_something();
for (int i = 0; i < m; i++)  // O(m)
    do_something_else();
// 总复杂度：O(n + m)
```

**规则二：嵌套循环相乘。**

```cpp
for (int i = 0; i < n; i++)        // n 次
    for (int j = 0; j < n; j++)    // 每次 n 次
        do_work();                 // O(1)
// 总复杂度：O(n * n) = O(n²)
```

**规则三：边界每次减半（或翻倍）的循环是对数级的。**

```cpp
while (n > 1) {
    n /= 2;       // 能把 n 除以 2 多少次？log₂ n 次
    do_work();
}
// O(log n)
```

同理，`i *= 2` 且 $i < n$ 的 `for` 循环也是 $O(\log n)$。

**规则四：库函数有自身的复杂度。**  
- `sort(a, a+n)` — $O(n \log n)$  
- 在有序数组中使用 `lower_bound` / `upper_bound` — $O(\log n)$  
- `set::insert`、`map::find` — $O(\log n)$

---

### 常见模式

### 两重循环不同边界

```cpp
for (int i = 0; i < n; i++)
    for (int j = 0; j < i; j++)   // 执行 0+1+2+...+(n-1) = n(n-1)/2 次
        do_work();
```
仍然是 $O(n^2)$，只是常数因子是 $\frac12$。

### 递减的 while

```cpp
int i = n;
while (i > 0) {
    i -= 2;           // 约 n/2 次 → O(n)
}
```

### 外循环线性、内循环对数
```cpp
for (int i = 0; i < n; i++) {
    int j = 1;
    while (j < n) {
        j *= 2;       // log n 步
        do_work();
    }
}
// O(n log n) — 外层 n 次，内层每次 log n 步
```

---

### 空间复杂度

通常我们只关注输入数据之外的**额外**内存。

```cpp
int arr[1000000];          // O(n)，n ≈ 1e6
vector<int> dp(n);         // O(n)
int a, b, cnt = 0;         // O(1) — 几个变量
```

递归深度也算空间：一个递归调用 $n$ 层的函数会使用 $O(n)$ 的栈空间。

---

###  为什么要关心复杂度

开始写代码之前，先看题目数据范围：
- $n \le 500$：$O(n^3)$ 没问题，$O(2^n)$ 也可能行。  
- $n \le 10^6$：你需要 $O(n \log n)$ 或更快的算法。  
- $n \le 10^7$：尽量 $O(n)$。

如果你计划的复杂度和数据范围不匹配，**先不要写代码**——换一个更优的算法再说。

## 练习题

### P1 [ABC081A] Placing Marbles（[AtCoder](https://atcoder.jp/contests/abc081/tasks/abc081_a)）

> 给定一个长度为 3 的字符串，由 `0` 和 `1` 组成（如 `101`），统计其中字符 `1` 的个数。

<details>
<summary>Hint</summary>

字符串长度固定为 3。遍历 3 个字符，遇到 `'1'` 就计数 +1。

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;
    int cnt = 0;
    for (int i = 0; i < 3; i++)
        if (s[i] == '1') cnt++;
    cout << cnt << endl;
    return 0;
}
```

</details>

### P2 [CF 158A] Next Round（[Codeforces](https://codeforces.com/problemset/problem/158/A)）

> $n$ 个选手的分数（非递增排列），第 $k$ 名选手的分数是晋级线。晋级条件：分数 $>0$ 且分数 $\ge$ 晋级线。问有多少人晋级。

<details>
<summary>Hint</summary>

读入 $n,k$，读入 $n$ 个分数到数组。设 `threshold = a[k-1]`（注意数组下标从 0 开始）。遍历数组，如果 `a[i] > 0 && a[i] >= threshold`，计数 +1。

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int a[55];
    for (int i = 0; i < n; i++) cin >> a[i];
    int threshold = a[k - 1], cnt = 0;
    for (int i = 0; i < n; i++)
        if (a[i] > 0 && a[i] >= threshold) cnt++;
    cout << cnt << endl;
    return 0;
}
```

</details>

### P3 [CF 122A] Lucky Division（[Codeforces](https://codeforces.com/problemset/problem/122/A)）

> 如果一个数每一位都是 4 或 7，它叫「幸运数」。给定 $n$（$1 \le n \le 1000$），判断 $n$ 是否能被**任意一个**幸运数整除。

<details>
<summary>Hint</summary>

这道题**天然需要写一个函数** `bool isLucky(int x)`——判断 $x$ 的每一位是否都是 4 或 7。然后在 $[4, n]$ 范围内枚举幸运数：如果 `isLucky(i)` 为真且 `n % i == 0`，输出 `"YES"`。枚举完都没找到就输出 `"NO"`。

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
using namespace std;

bool isLucky(int x) {
    while (x > 0) {
        int d = x % 10;
        if (d != 4 && d != 7) return false;
        x /= 10;
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    for (int i = 4; i <= n; i++) {
        if (n % i == 0 && isLucky(i)) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}
```

</details>

### P4 [P5740] 最厉害的学生（[洛谷](https://www.luogu.com.cn/problem/P5740)）

> 输入 $N$ 个学生的姓名、语文、数学、英语成绩，输出总分最高的学生（并列则输出最先输入的那个）。$N \le 1000$。

<details>
<summary>Hint</summary>

定义 `struct Student { string name; int ch, ma, en; };`。读入每个学生，计算总分。维护一个 `best` 结构体和 `bestTotal`，遍历时如果当前总分 $>$ `bestTotal` 就更新。

这道题是 0x08 结构体最直接的应用——一个学生天然就是一个结构体。

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
#include <string>
using namespace std;

struct Student {
    string name;
    int ch, ma, en;
};

int main() {
    int n;
    cin >> n;
    Student best;
    int bestTotal = -1;
    for (int i = 0; i < n; i++) {
        Student s;
        cin >> s.name >> s.ch >> s.ma >> s.en;
        int total = s.ch + s.ma + s.en;
        if (total > bestTotal) {
            bestTotal = total;
            best = s;
        }
    }
    cout << best.name << " " << best.ch << " " << best.ma << " " << best.en << endl;
    return 0;
}
```

</details>

---

### ⭐ 挑战题 P5 [CSP-S 2020] 儒略日（P7075）[P7075 儒略日](https://www.luogu.com.cn/problem/P7075)

> 给定一个儒略日数，转换成公历日期。涉及公元前后、闰年规则变化、1582 年删除的 10 天。数据范围 $Q \le 10^5$，儒略日可达 $10^9$。

这道题几乎不涉及超出本章范围的语法，但考验**模拟能力**和**细节处理**——你需要仔细处理：
- 公元前（公元前 1 年的下一年是公元 1 年，没有公元 0 年）
- 儒略历 vs 格里高利历的闰年规则不同
- 1582 年 10 月 4 日的下一天是 10 月 15 日
- 多组数据要求 $O(1)$ 或 $O(\log n)$ 单次查询，不能逐天模拟

### ⭐ 挑战题 P6 [CSP-S 2023] 结构体（P9754）[P9754 结构体](https://www.luogu.com.cn/problem/P9754)

> 模拟类似 C++ 的结构体定义方式，支持四种操作：定义结构体类型、定义元素、访问某元素的地址、根据地址反查元素。涉及内存对齐规则。

这道题和本章的 0x08 结构体直接相关，但难度远超入门水平。你需要：
- 理解并模拟 C++ 的内存对齐规则
- 维护类型名 → 大小/对齐/成员列表的映射
- 维护已定义元素的起始地址
- 实现 `.` 分隔的嵌套访问路径解析
- 实现内存地址反查：判断某个地址属于哪个元素

> 提示：用 `map<string, TypeInfo>` 存类型信息，用 `map<string, ElementInfo>` 存元素信息。地址查询 4 可以维护一个地址 → 元素名的映射表。定义操作 1 和 2 本质上是按规则计算大小和偏移量。

> **选做建议**：先完成 P1~P4，确保基础扎实。如果你读完 0x08 后跃跃欲试，可以挑战 P6。P5 适合喜欢天文/历史模拟的同学。两道挑战题都不影响后续章节的学习。

---

## Self-Check

逐条确认，每条都应该能脱口而出：

- [ ] 知道什么时候用 `long long` 而不是 `int`
- [ ] 不会写出 `5 / 2` 然后指望得到 2.5
- [ ] 不会把 `=` 和 `==` 搞混
- [ ] 能用 `cin/cout` 读写数据
- [ ] 能用 `%` 判断奇偶
- [ ] 能写 `if / else if / else` 结构
- [ ] 理解 `&&` 和 `||` 的短路行为
- [ ] 能写 `for` 和 `while`，知道 `break` 和 `continue`
- [ ] 能处理多组输入（`while(T--)` 和 `while(cin>>...)`）
- [ ] 能定义和遍历数组，知道下标从 0 开始
- [ ] 知道什么是越界，如何避免

- [ ] 能写出一个带参数、有返回值的函数
- [ ] 理解 `void`——不返回东西的函数
- [ ] 理解传值和传引用的区别，知道什么时候加 `&`
- [ ] 理解函数声明和定义可以分开
- [ ] 能看懂递归，知道终止条件是什么
- [ ] 不会写出返回局部变量引用的代码
- [ ] 知道怎么把数组传给函数

- [ ] 能定义一个结构体，创建实例并用 `.` 访问成员
- [ ] 能初始化结构体：`{"Alice", 16, 95.5}`
- [ ] 能创建结构体数组并遍历
- [ ] 理解结构体嵌套（结构体里放结构体）
- [ ] 知道结构体传参用 `const &` 最高效
- [ ] 知道结构体不能用 `==` 直接比较
- [ ] 我懂得 $O(1)$、$O(\log n)$、$O(n)$、$O(n^2)$ 的含义。
- [ ] 我能看着一段循环写出它的时间复杂度。
- [ ] 我能根据数据范围判断一个 $O(n^2)$ 的算法能否通过。
- [ ] 我明白大 O 忽略常数，但对于很小的 $n$ 或很重的操作（如 set、map），常数因素仍需留意。
- [ ] 我知道一次 `sort` 的复杂度是 $O(n \log n)$。
- [ ] 我知道怎么估算数组和递归所需的空间复杂度。
