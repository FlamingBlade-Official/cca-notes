# 0x00 从变量到数组

你已经知道怎么写简单的 C++ 程序了——会定义变量、会用 `cin/cout`、会写 `if` 和 `for`。但是，能写出**正确**的代码和能写出**不会悄悄出错**的代码，中间隔着一堆细节。这一章帮你把这堆细节填上。

读完这一章，你应该能轻松写出后面所有章节需要的代码。

---

## 0x01 变量与数据类型

C++ 里每个变量都有类型。类型决定两件事：**能存什么**，**占多少空间**。

```cpp
int a = 42;           // 整数，4 字节，范围约 ±2.1×10⁹
long long b = 1e18;   // 大整数，8 字节，范围约 ±9×10¹⁸
double x = 3.14;      // 浮点数，~15 位有效数字
char c = 'A';         // 单个字符
bool flag = true;     // 只有 true 或 false
string s = "hello";   // 字符串（需要 #include <string>）
```

### 整数除法

两个 `int` 相除，结果还是 `int`，小数部分被**直接丢弃**。

```cpp
cout << 5 / 2;      // 2，不是 2.5
cout << 5.0 / 2;    // 2.5（有一边是 double 就行）
```

### int 溢出

`int` 最大约 21 亿。超出这个范围，值会"绕回去"变成负数——编译器不会报错，结果悄悄错了。

```cpp
int a = 100000, b = 100000;
cout << a * b;      // 溢出，输出垃圾
cout << (long long)a * b;  // 正确：先转成 long long 再乘
```

竞赛里，只要涉及乘法或累加和，**默认用 `long long`**，除非你确定不会爆。

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
printf("%.2f\n", y);                       // 保留两位小数
```

`cin/cout` 日常够用。大数据量（10⁵ 以上）时 `scanf/printf` 更快。两种写法混用也没问题。

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

取余也常用于"限制范围"：`x % 10` 一定在 0~9 之间。

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
| `&&` | 且 | `x > 0 && x < 100` |
| `\|\|` | 或 | `c == 'Y' \|\| c == 'y'` |
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

浮点数用 `abs(a - b) < 1e-9` 判断"足够接近"。竞赛里浮点数比较不多见，先记住就行。

---

## 0x05 循环

### for——知道循环次数

```cpp
for (int i = 1; i <= n; i++) {
    cout << i << ' ';
}
// 输出 1 2 3 ... n
```

三段式：①起点 `int i = 1`、②继续条件 `i <= n`、③每轮变化 `i++`。

### while——不知道循环次数

```cpp
while (n > 1) {
    if (n % 2 == 0) n /= 2;
    else n = 3 * n + 1;
}
```

### break 和 continue

```cpp
for (int i = 1; i <= 10; i++) {
    if (i == 5) break;       // 直接跳出整个循环
    if (i % 2 == 0) continue; // 跳过本轮，进入下一轮
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
}
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
// 没有 a[5]！
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

数组大小为 N，合法下标是 `0` ~ `N-1`。下标从 1 开始写`for (int i = 1; i <= n; i++)`时开数组要 `a[n+1]`。

**② 未初始化**

```cpp
int a[100];          // 局部数组——值是随机垃圾
cout << a[0];        // 可能是任何值
```

```cpp
int a[100] = {0};    // 全部初始化为 0
```

**③ 局部数组过大**

```cpp
void f() {
    int a[1000000];  // 100 万可能爆栈
}
```

大数组（>10⁵）放在 `main` 外面做全局变量。

**④ 变长数组**

```cpp
int n; cin >> n;
int a[n];            // 不标准，不要用
```

用固定大小：`const int N = 100005; int a[N];`，或后面学 `vector`。

---

## 练习

### P1 A+B（热身）

读入两个整数 a, b，输出 a+b。

<details>
<summary>Solution</summary>

```cpp
int a, b;
cin >> a >> b;
cout << a + b << endl;
```
</details>

### P2 判断奇偶

读入整数 n，奇数输出 "Odd"，偶数输出 "Even"。

<details>
<summary>Hint</summary>
用 `%`。
</details>

<details>
<summary>Solution</summary>

```cpp
int n; cin >> n;
if (n % 2 == 0) cout << "Even" << endl;
else cout << "Odd" << endl;
```
</details>

### P3 1 到 N 求和

读入 N，输出 1+2+...+N。N ≤ 10⁵。

<details>
<summary>Hint</summary>
`for` 循环累加。注意用 `long long`。
</details>

<details>
<summary>Solution</summary>

```cpp
int n; cin >> n;
long long sum = 0;
for (int i = 1; i <= n; i++) sum += i;
cout << sum << endl;
```
</details>

### P4 找最大值

读入 n 个整数，输出最大值。

<details>
<summary>Hint</summary>
用一个变量 `mx`，初始设为一个很小的值（比如 `-1e9`），逐个比较更新。
</details>

<details>
<summary>Solution</summary>

```cpp
int n; cin >> n;
int mx = -1e9;
for (int i = 0; i < n; i++) {
    int x; cin >> x;
    if (x > mx) mx = x;
}
cout << mx << endl;
```
</details>

### P5 反转数组

读入 n 个数到数组中，从后往前输出。

<details>
<summary>Hint</summary>
`for (int i = n-1; i >= 0; i--)`。
</details>

<details>
<summary>Solution</summary>

```cpp
int n; cin >> n;
int a[100];
for (int i = 0; i < n; i++) cin >> a[i];
for (int i = n-1; i >= 0; i--) cout << a[i] << ' ';
```
</details>

### P6 乘法表

输出 9×9 乘法表：

```
1*1=1
1*2=2  2*2=4
1*3=3  2*3=6  3*3=9
...
```

<details>
<summary>Hint</summary>
双重循环：`for i: 1..9` 里面套 `for j: 1..i`。
</details>

<details>
<summary>Solution</summary>

```cpp
for (int i = 1; i <= 9; i++) {
    for (int j = 1; j <= i; j++) {
        cout << j << '*' << i << '=' << j*i << '\t';
    }
    cout << endl;
}
```
</details>

### P7 计数（桶思想预热）

读入 n 个数（每个数 1~100），输出每个数出现了多少次。

```
输入：
8
1 2 3 1 2 1 5 1
输出：
1 appears 4 times
2 appears 2 times
3 appears 1 time
5 appears 1 time
```

<details>
<summary>Hint</summary>
`cnt[101] = {0}`，每读入 x 就 `cnt[x]++`。最后遍历 1~100。
</details>

<details>
<summary>Solution</summary>

```cpp
int n; cin >> n;
int cnt[101] = {0};
for (int i = 0; i < n; i++) {
    int x; cin >> x;
    cnt[x]++;
}
for (int i = 1; i <= 100; i++) {
    if (cnt[i] > 0)
        cout << i << " appears " << cnt[i] << " time(s)" << endl;
}
```
</details>

### P8 冒泡排序（选做）

读入 n 个数，从小到大排序输出。

<details>
<summary>Hint</summary>
双重循环：外层 i 从 0 到 n-2，内层 j 从 0 到 n-2-i。如果 `a[j] > a[j+1]` 就交换。
</details>

<details>
<summary>Solution</summary>

```cpp
int n; cin >> n;
int a[100];
for (int i = 0; i < n; i++) cin >> a[i];

for (int i = 0; i < n-1; i++)
    for (int j = 0; j < n-1-i; j++)
        if (a[j] > a[j+1]) swap(a[j], a[j+1]);  // 或者手动交换

for (int i = 0; i < n; i++) cout << a[i] << ' ';
```
</details>

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
