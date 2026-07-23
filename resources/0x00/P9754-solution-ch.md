# 题解：P9754 [CSP-S2023] 结构体

> 源代码：`P9754-Struct.cpp`

---

本题有多种实现方式，该题解只聚焦讨论于我的代码的写法。如果你认为有其他合适的写法，也是可以的。

## Hint 1

题目要求模拟 C++ 风格的内存对齐规则。每个类型（包括基本类型和自定义结构体）都有两个关键属性：**大小**和**对齐要求**。如何用一个统一的数据结构存储所有类型的信息？

<details>
<summary>点击展开</summary>

可以定义一个结构体数组 `a[N]`，每个元素表示一个类型：

```cpp
struct type {
    ll siz;              // 该类型总大小（字节）
    int max_alignment;   // 该类型的对齐要求（所有成员对齐要求的 max）
    int num;             // 成员个数（基本类型为 0）
    int id[N];           // 每个成员的类型编号
    string name[N];      // 每个成员的名字
} a[N];
```

四个基本类型在程序开头预先注册：

```cpp
++cnt; name[cnt] = "byte";  a[cnt] = {1, 1, 0};
++cnt; name[cnt] = "short"; a[cnt] = {2, 2, 0};
++cnt; name[cnt] = "int";   a[cnt] = {4, 4, 0};
++cnt; name[cnt] = "long";  a[cnt] = {8, 8, 0};
```

编号 0 留作"全局根类型"——所有操作 2 定义的变量都作为根类型的成员。

通过 `getid(s)` 函数（或 `unordered_map`）把类型名字映射到数组下标。

</details>

---

## Hint 2

操作 1（定义新结构体）时，如何计算它的**大小**和**对齐要求**？对齐的向上取整怎么实现？

<details>
<summary>点击展开</summary>

**对齐要求** = 所有成员类型的 `max_alignment` 的最大值。

**大小计算**：维护当前偏移量 `cur = 0`，遍历每个成员：

1. 将 `cur` 向上对齐到该成员类型的对齐要求：
   ```cpp
   cur = ((cur - 1) / alignment + 1) * alignment;
   // 或: cur = (cur + alignment - 1) / alignment * alignment;
   ```
2. 累加成员大小：`cur += member_size`。

遍历结束后，再将 `cur` 向上对齐到结构体自身的对齐要求（即 `max_alignment`），得到最终 `siz`。

结构体末尾也需要对齐到自身对齐要求，这和 C/C++ 中 `sizeof(struct)` 的行为一致——确保结构体数组中每个元素都满足对齐。

</details>

---

## Hint 3

操作 3（按路径访问地址）本质上是在类型树中从根节点逐步走向目标节点。路径中的每个 `.` 意味着什么？如何计算当前成员在父类型中的起始地址？

<details>
<summary>点击展开</summary>

路径如 `a.b.c` 表示：
- 从全局根类型（编号 0）开始，找到名为 `a` 的成员。
- 进入 `a` 的类型，找到名为 `b` 的成员。
- 进入 `b` 的类型，找到名为 `c` 的成员。

地址计算：
1. 进入一个新类型时，先将当前地址 `ans` 对齐到该类型的 `max_alignment`。
2. 遍历该类型的成员，每次先将 `ans` 对齐到成员的对齐要求。
3. 如果成员名匹配，跳转到该成员的类型，继续循环；如果不匹配，`ans += member_size`（跳过该成员占用的空间），继续找下一个。

最终 `ans` 就是目标成员的起始地址。

</details>

---

## Hint 4

操作 4（按地址寻找路径）是操作 3 的**逆过程**。需要判断一个地址落在哪个成员内部，并递归向下。地址可能落在**对齐产生的空隙**中，此时应该输出什么？

<details>
<summary>点击展开</summary>

从全局根类型开始循环：

1. 将当前起始偏移 `begin` 对齐到当前类型的 `max_alignment`。
2. 遍历当前类型的所有成员：
   - 将 `begin` 对齐到该成员的对齐要求。
   - 如果 `addr >= begin + member_size`：地址在该成员之后，`begin += member_size`，继续看下一个成员。
   - 如果 `begin <= addr < begin + member_size`：地址落在该成员内部。记录成员名，进入该成员的类型。如果该类型没有子成员（`num == 0`，即基本类型或空结构体），说明找到了终点，输出路径。
   - 否则（`addr < begin`）：地址落在对齐产生的**空隙**中（在上一成员结束后、本成员对齐开始前的间隙），此时标记 `find_ans = 2`，输出 `ERR`。

3. 如果遍历完所有成员都没找到，或地址超出根类型的总大小，同样输出 `ERR`。

关键细节：对齐空隙的判断条件是 `addr < begin`（在进入当前成员的对齐位置之前），以及 `addr >= begin + member_size` 时跳过当前成员。只有当 `begin ≤ addr < begin + member_size` 时才递归进入。

</details>

---

## Solution

<details>
<summary>查看完整思路与代码解析</summary>

### 1. 数据结构

```cpp
struct type {
    ll siz;
    int max_alignment, num;
    int id[N];
    string name[N];
} a[N];

int cnt;          // 当前类型数量
string name[N];   // 类型编号 → 类型名
```

- `a[0]`：全局根类型，存放所有操作 2 定义的变量。其 `max_alignment = 1`。
- `a[1..4]`：四个基本类型 `byte, short, int, long`。
- `a[5..]`：操作 1 定义的自定义结构体。

### 2. `get_alignment(siz, alignment)` —— 向上对齐

```cpp
ll get_alignment(ll siz, ll alignment) {
    if (siz == 0) return 0;
    return ((siz - 1) / alignment + 1) * alignment;
}
```

例如 `siz=5, alignment=4` → `(4/4+1)*4 = 8`。

### 3. 操作 1：定义结构体

```cpp
string s; int num;
cin >> s >> num;
++cnt;
a[cnt].num = num;
name[cnt] = s;

for (int i = 1; i <= num; ++i) {
    string _type, _name;
    cin >> _type >> _name;
    a[cnt].id[i] = getid(_type);
    a[cnt].name[i] = _name;
    a[cnt].max_alignment = max(
        a[cnt].max_alignment,
        a[a[cnt].id[i]].max_alignment
    );
}

// 计算大小
for (int i = 1; i <= num; ++i) {
    a[cnt].siz = get_alignment(a[cnt].siz, a[a[cnt].id[i]].max_alignment);
    a[cnt].siz += a[a[cnt].id[i]].siz;
}
a[cnt].siz = get_alignment(a[cnt].siz, a[cnt].max_alignment);

cout << a[cnt].siz << " " << a[cnt].max_alignment << endl;
```

### 4. 操作 2：定义变量

```cpp
string _type, _name;
cin >> _type >> _name;
int id = getid(_type);

a[0].siz = get_alignment(a[0].siz, a[id].max_alignment);
cout << a[0].siz << endl;   // 输出起始地址
a[0].siz += a[id].siz;
a[0].num++;
a[0].id[a[0].num] = id;
a[0].name[a[0].num] = _name;
```

### 5. 操作 3：访问地址

```cpp
string _name; cin >> _name;
string tmp = "";
int p = 0;
ll ans = 0;

for (int i = 0; i <= _name.size(); ++i) {
    if (i == _name.size() || _name[i] == '.') {
        ans = get_alignment(ans, a[p].max_alignment);
        for (int j = 1; j <= a[p].num; ++j) {
            ans = get_alignment(ans, a[a[p].id[j]].max_alignment);
            if (a[p].name[j] == tmp) {
                p = a[p].id[j];
                tmp = "";
                break;
            } else {
                ans += a[a[p].id[j]].siz;
            }
        }
    } else {
        tmp += _name[i];
    }
}
cout << ans << endl;
```

以 `.` 分割路径，逐层深入。

### 6. 操作 4：按地址寻路

```cpp
ll addr; cin >> addr;
string ans[105]; int anscnt = 0;
int p = 0, find_ans = 0;
ll begin = 0;

if (addr >= a[0].siz) { cout << "ERR" << endl; continue; }

while (1) {
    begin = get_alignment(begin, a[p].max_alignment);
    for (int i = 1; i <= a[p].num; ++i) {
        int id = a[p].id[i];
        begin = get_alignment(begin, a[id].max_alignment);

        if (addr >= begin + a[id].siz) {
            begin += a[id].siz;
            continue;
        } else if (addr >= begin && addr < begin + a[id].siz) {
            ans[++anscnt] = a[p].name[i];
            p = id;
            if (a[p].num == 0) { find_ans = 1; }
            break;
        } else {
            find_ans = 2;
            break;
        }
    }
    if (find_ans == 1) {
        for (int i = 1; i <= anscnt; ++i) {
            cout << ans[i];
            if (i != anscnt) cout << ".";
        }
        cout << endl;
        break;
    }
    if (find_ans == 2) {
        cout << "ERR" << endl;
        break;
    }
}
```

找出地址落在哪个成员内部，递归向下，直到叶子或发现空隙。

### 7. 复杂度分析

- 操作 1 和 2：$O(k)$，$k$ 为成员数量。
- 操作 3：$O(\text{路径深度} \times \text{平均成员数})$。
- 操作 4：$O(\text{路径深度} \times \text{平均成员数})$。

由于题目限制总操作数 ≤ 100 且结构体成员总数有限，完全可行。

</details>

---

## 思考题

**Q1.** 为什么在操作 1 计算结构体大小时，遍历完所有成员后还需要将 `cur` 再向上对齐一次？

<details>
<summary>点击查看参考答案</summary>

这对应 C/C++ 中结构体末尾的 padding。如果结构体数组中有多个元素，每个元素的起始地址都必须满足该结构体的对齐要求。尾部对齐保证了 `sizeof(struct)` 是对齐要求的整数倍，从而使数组中第二个元素能正确对齐。

</details>

**Q2.** 操作 4 中，地址落在"对齐空隙"有几种情况？分别对应代码中的哪个判断分支？

<details>
<summary>点击查看参考答案</summary>

有两种情况：
1. **成员之前**：`addr < begin`（当前成员对齐后的起始地址大于目标地址），说明 `addr` 落在了上一成员结束后到当前成员对齐开始之间的 padding 区域。
2. **所有成员之后**：遍历完所有成员仍未找到，且 `addr < a[0].siz`。此时 `addr` 落在最后一个成员结束后到结构体末尾对齐之间的 padding 区域，或者结构体末尾 padding 中。代码中这种情况会因 `find_ans == 0` 而在 while 循环结束后什么也不输出，但更稳妥的做法是在最后也输出 `ERR`（取决于实现）。

代码中主要处理的是第一种情况（`find_ans = 2`）。

</details>

**Q3.** 如果两个不同的结构体类型包含完全相同的成员定义，它们在内存中的布局一定相同吗？对齐要求呢？

<details>
<summary>点击查看参考答案</summary>

是的，如果成员类型、数量和顺序完全相同，按照题目给出的对齐规则，它们在内存中的布局（每个成员的偏移量、总大小、对齐要求）将是完全一样的。对齐要求由所有成员的对齐要求取 max 决定，大小由对齐规则唯一确定，因此相同定义必然产生相同布局。

</details>
