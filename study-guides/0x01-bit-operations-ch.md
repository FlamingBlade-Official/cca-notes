# 0x01 位运算

C++ 里的整数在内存中是一串 0 和 1。直接操作这些 0 和 1，往往比加减乘除快得多，也省空间。很多竞赛题的"优雅解法"都建立在位运算上——状态压缩 DP、快速幂、lowbit 树状数组……本质都是把整数当成了一个 01 位的集合来操作。

读完这一章，你应该能做到：

- 理解 `int` 的 32 位二进制表示和补码
- 熟练使用 `& | ^ ~ << >>` 并理解它们的作用
- 用二进制表示集合，实现状态压缩
- 手写快速幂和 64 位乘法
- 使用 lowbit 和 GCC 内置位运算函数

---

## 0x01 位、字节与补码

### 位和字节

一个**位（bit）**只能存 0 或 1。8 个位组成一个**字节（byte）**，一个字节可以表示 $2^8 = 256$ 种状态，范围是 0x00~0xFF（十六进制，`0x` 前缀表示这是十六进制数）。

```cpp
// 0x00 = 0, 0xFF = 255, 0x7F = 127
// 一个 char 占 8 位（1 字节），值的范围是 -128~127（有符号）
```

### int 和 unsigned int

竞赛里最常用的是 32 位整数。C++ 的 `int` 是 32 位**有符号**整数，`unsigned int` 是 32 位**无符号**整数（注意：标准只保证 `int` 至少 16 位，但在现代 OJ 上几乎都是 32 位）。

| 类型 | 位宽 | 范围 | 最大值十六进制 |
|------|------|------|--------------|
| `int` | 32 位有符号 | $-2^{31} \sim 2^{31}-1$ | `0x7FFFFFFF` |
| `unsigned int` | 32 位无符号 | $0 \sim 2^{32}-1$ | `0xFFFFFFFF` |

> 💡 在竞赛中，当数据范围可能超过 $2\times 10^9$ 时，用 `long long`（64 位）。64 位有符号的范围是 $-9\times 10^{18} \sim 9\times 10^{18}$。

### 补码——有符号整数的存储方式

C++ 用**补码（two's complement）**存储有符号整数。补码的核心规则：

- **正数**：就是它本身的二进制表示，高位补 0。
- **负数**：对应正数按位取反再加 1。

```cpp
// 8 位补码举例
// +1  →  00000001
// -1  →  ~00000001 + 1 = 11111110 + 1 = 11111111 = 0xFF
// +127 →  01111111 = 0x7F
// -128 →  10000000 = 0x80
```

32 位 `int` 同理：
- `2147483647` → `0x7FFFFFFF`（最大正数）
- `-1` → `0xFFFFFFFF`（32 个全 1）
- `-2147483648` → `0x80000000`（最小负数）

一个有用的观察：`~c` 等价于 `-1 - c`（在补码意义下）。

### memset 与 0x3F 技巧

`memset(a, val, sizeof(a))` 会把 `a` 的**每个字节**都填成 `val`（`val` 是 0x00~0xFF 之间的值）。因为 `int` 是 4 个字节，`memset` 实际上在"每 8 位填一次"。

```cpp
// 常用值：
memset(a, 0, sizeof(a));       // 全部清零：0x00000000 = 0
memset(a, -1, sizeof(a));      // 全部置 -1：0xFFFFFFFF = -1
memset(a, 0x3F, sizeof(a));    // 0x3F3F3F3F ≈ 1.06×10^9
memset(a, 0x7F, sizeof(a));    // 0x7F7F7F7F ≈ 2.13×10^9（接近 int 最大值）
```

`0x3F3F3F3F` 是个很妙的数——它比 `int` 最大值小，但足够大，且 `0x3F3F3F3F + 0x3F3F3F3F` 不会溢出。很多代码中用 `memset(a, 0x3F, sizeof(a))` 来初始化一个"极大值"。

---

## 0x02 位运算符

C++ 提供了六个位运算符，直接对二进制位进行操作。

| 运算符 | 名称 | 作用 | 示例 |
|--------|------|------|------|
| `&` | 按位与 | 对应位都为 1 才得 1 | `5 & 3 = 1`（`101 & 011 = 001`）|
| `|` | 按位或 | 对应位有一个为 1 就得 1 | `5 | 3 = 7`（`101 | 011 = 111`） |
| `^` | 按位异或 | 对应位不同得 1，相同得 0 | `5 ^ 3 = 6`（`101 ^ 011 = 110`）|
| `~` | 按位取反 | 0 变 1，1 变 0 | `~5 = -6`（补码下）|
| `<<` | 左移 | 所有位向左移动，右边补 0 | `5 << 1 = 10` |
| `>>` | 右移 | 所有位向右移动 | `5 >> 1 = 2` |

### 按位与 `&`——检查某一位

```cpp
int x = 12;          // 二进制：1100
if (x & 4) cout << "第 3 位是 1";  // 4 = 0100，x & 4 = 0100 ≠ 0
if (x & 1) cout << "奇数为 true";   // 最低位决定奇偶
```

### 按位或 `|`——把某一位设成 1

```cpp
int x = 8;           // 二进制：1000
x = x | 3;           // 把最低两位置 1：1000 | 0011 = 1011 = 11
x |= (1 << 2);       // 把第 2 位置 1（第 0 位是最低位）
```

### 按位异或 `^`——翻转/去重/交换

异或的性质非常重要：
- `a ^ a = 0`（自己异或自己得 0）
- `a ^ 0 = a`
- 满足交换律和结合律

```cpp
// 经典应用：找出数组中唯一出现奇数次的数
int ans = 0;
for (int i = 0; i < n; i++) ans ^= a[i];
// ans 就是那个数——其他数都成对消掉了

// 不用临时变量交换两个数
a ^= b;  b ^= a;  a ^= b;
// 但通常直接用 swap(a, b) 更清晰
```

### 按位取反 `~`

```cpp
int x = 5;    // 000...0101
int y = ~x;   // 111...1010 = -6（补码）
// 规律：~x = -x - 1
```

---

## 0x03 移位运算

### 左移 `<<`

`n << k` = $n \times 2^k$。所有位向左移动 $k$ 位，右边补 0。

```cpp
cout << (1 << 5);    // 32，即 2^5
cout << (3 << 2);    // 12，即 3 × 4
```

`1 << k` 是生成长度为 $k$ 的二进制位掩码（第 $k$ 位为 1）的常用写法。

### 右移 `>>`

分为两种：

- **逻辑右移**：高位补 0（用于 `unsigned`）
- **算术右移**：高位补符号位（用于有符号 `int`，保持正负号）

```cpp
int a = 5;
cout << (a >> 1);    // 2，等价于 floor(5/2)

int b = -3;
cout << (b >> 1);    // -2（算术右移，补 1）
// 注意：(-3) / 2 = -1，而 (-3) >> 1 = -2
// 右移取整是"向下取整"，整数除法是"向零取整"
```

> ⚠️ 在 C++ 中，有符号整数的右移行为是实现定义的（大多数编译器用算术右移）。不要在负数的右移行为上做假设。

### 移位 vs 乘除

```cpp
// 当需要保证向下取整的正整数除法时：
int half = n >> 1;       // 等价 floor(n/2)，比 n/2 快但编译器通常自动优化

// 2 的幂次取模：
int mod8 = n & 7;        // 等价 n % 8，但只对 2^k 有效
int mod16 = n & 15;      // 等价 n % 16
```

---

## 0x04 快速幂

计算 $a^b \bmod p$。如果直接循环乘 $b$ 次，复杂度 $O(b)$。当 $b$ 达到 $10^9$ 级别时，需要快速幂。

### 核心思想

把 $b$ 拆成二进制：$b = c_0 \cdot 2^0 + c_1 \cdot 2^1 + \cdots + c_k \cdot 2^k$，其中 $c_i \in \{0, 1\}$。

那么：
$$a^b = a^{c_0 \cdot 2^0} \times a^{c_1 \cdot 2^1} \times \cdots \times a^{c_k \cdot 2^k}$$

从低位到高位遍历 $b$ 的每一位：
- 当前位是 1：答案乘以当前 $a$ 的幂
- 每一步都把 $a$ 平方，准备处理下一位

复杂度 $O(\log b)$。

```cpp
// 计算 (a ^ b) % p
int power(int a, int b, int p) {
    int ans = 1 % p;
    for (; b; b >>= 1) {
        if (b & 1) ans = (long long)ans * a % p;
        a = (long long)a * a % p;
    }
    return ans;
}
```

> 💡 乘 `(long long)` 是为了防溢出：两个 `int`（最大约 $2\times 10^9$）相乘可能超出 `int` 范围。

### 逐步理解

以 $a=3$, $b=13$, $p=100$ 为例，$b = 13 = 1101_2$：

| 步骤 | b（二进制） | b & 1? | ans | a |
|------|------------|--------|-----|---|
| 初值 | 1101 | — | 1 | 3 |
| 第 1 轮 | 1101 | ✓ | $1 \times 3 = 3$ | $3^2 = 9$ |
| 第 2 轮 | 110 | ✗ | 3 | $9^2 = 81$ |
| 第 3 轮 | 11 | ✓ | $3 \times 81 = 243 \equiv 43$ | $81^2 = 6561 \equiv 61$ |
| 第 4 轮 | 1 | ✓ | $43 \times 61 = 2623 \equiv 23$ | — |

所以 $3^{13} \bmod 100 = 23$。

---

## 0x05 64 位整数乘法

当 $a, b, p$ 都达到 $10^{18}$ 级别时，$a \times b$ 会超出 `long long`（64 位）的范围（`long long` 最大约 $9\times 10^{18}$）。我们需要在不溢出的前提下计算 $a \times b \bmod p$。

### 方法一：类似快速幂

把乘法拆成二进制加法。复杂度 $O(\log b)$。

```cpp
// 计算 (a * b) % p，a,b,p 都在 long long 范围内
long long mul(long long a, long long b, long long p) {
    long long ans = 0;
    for (; b; b >>= 1) {
        if (b & 1) ans = (ans + a) % p;
        a = a * 2 % p;
    }
    return ans;
}
```

### 方法二：用 `long double` 估算

利用 `long double` 的精度（约 18~19 位有效数字）来估算 $\lfloor a\times b / p \rfloor$，然后做修正。

```cpp
long long mul(long long a, long long b, long long p) {
    a %= p, b %= p;
    long long c = (long double)a * b / p;
    long long ans = a * b - c * p;
    if (ans < 0) ans += p;
    else if (ans >= p) ans -= p;
    return ans;
}
```

这个方法比二进制拆分更快，但依赖 `long double` 精度，在某些极端数据下可能出错。竞赛中两种都可以，新手优先掌握方法一。

---

## 0x06 二进制状态压缩

$n$ 个元素的集合，每个元素可以选或不选，一共 $2^n$ 种状态。用一个 $n$ 位的二进制数就能表示所有状态——第 $i$ 位是 1 表示选了第 $i$ 个元素。

这就是**状态压缩**的核心思想。

### 基本操作

```cpp
int mask = 0;                     // 空集
mask |= (1 << i);                 // 加入第 i 个元素
mask ^= (1 << i);                 // 切换第 i 个元素（有则去，无则加）
mask &= ~(1 << i);                // 移除第 i 个元素
if (mask & (1 << i)) { /* 第 i 个在集合中 */ }

// 枚举 mask 的所有子集
for (int sub = mask; sub; sub = (sub - 1) & mask) {
    // sub 是 mask 的一个非空子集
}
// 空集需要单独处理

// 检查 n 的第 k 位（从 0 开始编号）
if (n & (1 << k)) { /* ... */ }
// 等价于 if ((n >> k) & 1) { /* ... */ }
```

### 经典应用：Hamilton 路径

> 给定 $n$（$n \le 20$）个点的带权有向图，求从点 0 出发、经过每个点恰好一次、最终到达点 $n-1$ 的最短路径长度。

定义 `f[i][j]`：从 0 出发，当前在点 $j$，已经访问过的点集为 $i$（二进制表示）的最短路径长度。

转移：`f[i][j] = min{ f[i xor (1 << j)][k] + weight[k][j] }`，其中 $k$ 是 $i$ 中去掉 $j$ 之后的某个点。

```cpp
int f[1 << 20][20];

int hamilton(int n, int weight[20][20]) {
    memset(f, 0x3F, sizeof(f));
    f[1][0] = 0;                         // 只访问了点 0，在点 0
    for (int i = 1; i < (1 << n); i++)
        for (int j = 0; j < n; j++)
            if (i >> j & 1)              // j 在集合 i 中
                for (int k = 0; k < n; k++)
                    if ((i >> k) & 1)    // k 在集合 i 中
                        f[i][j] = min(f[i][j],
                            f[i ^ (1 << j)][k] + weight[k][j]);
    return f[(1 << n) - 1][n - 1];
}
```

$n \le 20$ 时 $2^n \approx 10^6$，配合 $O(n^2 \cdot 2^n)$ 的 DP 刚好能过。

---

## 0x07 lowbit

`lowbit(n)`：$n$ 在二进制表示下**最低位的 1** 所代表的值。

```cpp
lowbit(n) = n & (-n)
```

解释：在补码下，`-n = ~n + 1`。设 $n$ 最低位 1 在第 $k$ 位，则 `~n` 的第 $k$ 位是 0，后面全是 1，加 1 后第 $k$ 位恢复为 1，后面全为 0。取 `n & (-n)` 就只保留了第 $k$ 位的 1。

```cpp
// lowbit(12) = lowbit(1100₂) = 4（第 2 位的 1）
// lowbit(7)  = lowbit(0111₂) = 1（第 0 位的 1）
```

### 应用：枚举二进制中所有的 1

```cpp
const int MAX_N = 1 << 20;
int H[MAX_N + 1];
for (int i = 0; i <= 20; i++) H[1 << i] = i;  // 预处理 2^i 对应的指数

int n;
while (cin >> n) {
    while (n > 0) {
        int lb = n & -n;
        cout << H[lb] << ' ';   // 输出最低位 1 的位置
        n -= lb;                 // 去掉最低位的 1
    }
}
```

lowbit 是**树状数组（Fenwick Tree）**的基础操作，后面 0x42 章会详细展开。

---

## 0x08 GCC 内置位运算函数

GCC 编译器提供了一些高效的位运算内置函数，直接编译成 CPU 指令。

```cpp
// 统计二进制中 1 的个数（population count）
int cnt = __builtin_popcount(x);         // unsigned int
int cnt = __builtin_popcountll(x);       // unsigned long long

// 统计末尾 0 的个数（count trailing zeros）
int tz = __builtin_ctz(x);               // 最低位 1 后面有多少个 0
int tz = __builtin_ctzll(x);             // long long 版本

// 统计前导 0 的个数（count leading zeros）
int lz = __builtin_clz(x);               // 最高位 1 前面有多少个 0
```

这些函数比自己用循环实现快得多，在需要频繁统计二进制位的题目中很有用。

```cpp
// 示例：统计一个数的二进制表示
int x = 42;  // 101010₂
cout << __builtin_popcount(x);  // 3（三个 1）
cout << __builtin_ctz(x);       // 1（最低位 1 在第 1 位，即从右数第 2 个）
```

---

## 0x09 异或的更多玩法

### 成对变换

对于任意整数 $n$：
- $n$ 是偶数时，`n ^ 1 = n + 1`
- $n$ 是奇数时，`n ^ 1 = n - 1`

```cpp
// 这个性质在图论的"成对存储边"技巧中非常有用
// 存无向边时，正向边和反向边相邻存储（编号 2 和 3、4 和 5...）
// 用 i ^ 1 就能找到当前边的反向边
```

这个技巧在前面 0x13 链式前向星和后面网络流章节都会用到。

---

## 练习题

### P1 二进制中 1 的个数

> 输入一个 `unsigned int`，输出其二进制表示中 1 的个数。

<details>
<summary>Hint</summary>
方法一：循环 32 次，每次检查最低位。

方法二：用 `n &= (n-1)` 每次去掉最低位的 1。

方法三：用 `__builtin_popcount`。

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
using namespace std;

int main() {
    unsigned int n;
    cin >> n;
    int cnt = 0;
    while (n) {
        n &= (n - 1);  // 去掉最低位的 1
        cnt++;
    }
    cout << cnt << endl;
    return 0;
}
```

</details>

### P2 找出只出现一次的数

> 给定 $n$ 个整数，其中只有一个数出现了奇数次，其余都出现了偶数次。找出这个数。$n \le 10^6$。

<details>
<summary>Hint</summary>

利用 `a ^ a = 0` 和 `a ^ 0 = a`。把所有数异或起来，成对的消掉，剩下的就是答案。

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
using namespace std;

int main() {
    int n, x, ans = 0;
    cin >> n;
    while (n--) {
        cin >> x;
        ans ^= x;
    }
    cout << ans << endl;
    return 0;
}
```

</details>

### P3 枚举子集

> 输入 $n$（$n \le 16$）和一个 $n$ 位的二进制掩码 `mask`，输出 `mask` 的所有子集的十进制值（包含空集和 `mask` 自身）。

<details>
<summary>Hint</summary>

可以用 `for (int sub = mask; ; sub = (sub - 1) & mask)` 的写法，但要注意最后处理空集。

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1e6 + 5;
int ans[N];
int mask, cnt = 0;
int main() {
    cin >> mask;
    for (int i = mask;i;(--i) &= mask)
        ans[++cnt] = i;
    ans[++cnt] = 0;
    for (int i = cnt;i >= 1;--i) cout << ans[i] << " ";
    cout << endl;
    return 0;
}
```

</details>

---

### P4 快速幂（模板）[**洛谷 P1226**](https://www.luogu.com.cn/problem/P1226)

> **洛谷 P1226**：给定 $a, b, p$，求 $a^b \bmod p$。$0 \le a, b < 2^{31}$，$2 \le p < 2^{31}$。

<details>
<summary>Hint</summary>
标准快速幂模板。

注意：(1) 读入后先对 `a` 取模；

(2) `ans` 初始化为 `1 % p`（防止 `p=1` 的边界情况）；

(3) 乘法中间结果用 `long long` 防溢出。输出格式：`a^b mod p=s`。

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
using namespace std;

int qpow(int a, int b, int p) {
    int ans = 1 % p;
    a %= p;
    for (; b; b >>= 1) {
        if (b & 1) ans = (long long)ans * a % p;
        a = (long long)a * a % p;
    }
    return ans;
}

int main() {
    int a, b, p;
    cin >> a >> b >> p;
    cout << a << "^" << b << " mod " << p << "=" << qpow(a, b, p) << endl;
    return 0;
}
```

</details>

---

### ⭐ P5 费解的开关 [**洛谷 P10449**](https://www.luogu.com.cn/problem/P10449)

> **洛谷 P10449**：$5 \times 5$ 的 01 矩阵，每改变一个灯的状态会同时翻转它上下左右四个相邻灯的状态。问能否在 6 步以内使所有灯变亮（全 1），输出最少步数，若 6 步以内无法完成则输出 `-1`。$n \le 500$ 组数据。

*本题为挑战题，请自行思考解法。*

---

### ⭐ P6 起床困难综合症 [**洛谷 P2114（NOI 2014）**](https://www.luogu.com.cn/problem/P2114)

> **洛谷 P2114（NOI 2014）**：有 $n$ 扇防御门，每扇门执行一种位运算（`AND` / `OR` / `XOR`）并带一个参数 $t$。初始攻击力 $x$ 可在 $[0, m]$ 中任选，经过所有门后得到最终伤害。求最大可能的伤害值。$n \le 10^5$，$m, t \le 10^9$。

*本题为挑战题，请自行思考解法。*

---

## Self-Check

逐条确认，每条都应该能脱口而出：

- [ ] 知道 `int` 是 32 位有符号整数，范围约 $\pm 2.1\times 10^9$
- [ ] 理解补码：知道 `~x = -x - 1`，知道 `0xFFFFFFFF = -1`
- [ ] 能用 `memset(a, 0x3F, sizeof(a))` 初始化"大值"数组
- [ ] 熟练使用 `& | ^ ~ << >>` 六个位运算符
- [ ] 知道 `a ^ a = 0` 和 `a ^ 0 = a`
- [ ] 会用异或找唯一出现奇数次的数
- [ ] 理解算术右移和逻辑右移的区别
- [ ] 能写快速幂 `(a^b) % p`，复杂度 $O(\log b)$
- [ ] 理解快速幂中 `(long long)` 强制转换的作用
- [ ] 能写 64 位整数乘法 `(a*b) % p`（二进制拆分法）
- [ ] 会用 `1 << k` 生成位掩码
- [ ] 会用 `mask | (1 << i)` 添加元素、用 `mask & ~(1 << i)` 删除元素
- [ ] 能用二进制状态压缩表示集合
- [ ] 知道 `lowbit(n) = n & (-n)`，理解其原理
- [ ] 能用 `lowbit` 枚举二进制中的所有 1
- [ ] 知道 `__builtin_popcount` 和 `__builtin_ctz` 的作用
- [ ] 知道 `n ^ 1` 在偶数/奇数邻接对中的作用
