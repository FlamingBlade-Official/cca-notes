# 0x01 Bitwise Operations

In C++, integers are stored in memory as strings of 0s and 1s. Manipulating these 0s and 1s directly is often much faster than arithmetic, and saves memory. Many elegant solutions in competitive programming are built on bitwise operations — state-compression DP, fast exponentiation, the lowbit operation in Fenwick trees… at their core, they all treat an integer as a set of 01 bits.

After reading this chapter, you should be able to:

- Understand the 32-bit binary representation of `int` and two's complement
- Use `& | ^ ~ << >>` fluently and understand what each does
- Represent sets using binary numbers for state compression
- Write fast exponentiation and 64-bit multiplication by hand
- Use `lowbit` and GCC built-in bitwise functions

---

## 0x01 Bits, Bytes, and Two's Complement

### Bits and Bytes

A single **bit** can only store 0 or 1. Eight bits make a **byte**, which can represent $2^8 = 256$ states, ranging from 0x00 to 0xFF (hexadecimal; the `0x` prefix indicates a hex number).

```cpp
// 0x00 = 0, 0xFF = 255, 0x7F = 127
// A char occupies 8 bits (1 byte), with a range of -128~127 (signed)
```

### int and unsigned int

In competitions, 32-bit integers are the most commonly used. C++'s `int` is a 32-bit **signed** integer, and `unsigned int` is a 32-bit **unsigned** integer (note: the C++ standard only guarantees `int` to be at least 16 bits, but on modern OJs they are essentially all 32-bit).

| Type | Width | Range | Max Value in Hex |
|------|-------|-------|------------------|
| `int` | 32-bit signed | $-2^{31} \sim 2^{31}-1$ | `0x7FFFFFFF` |
| `unsigned int` | 32-bit unsigned | $0 \sim 2^{32}-1$ | `0xFFFFFFFF` |

> 💡 In competitions, when the data range might exceed $2\times 10^9$, use `long long` (64-bit). The signed 64-bit range is approximately $-9\times 10^{18} \sim 9\times 10^{18}$.

### Two's Complement — How Signed Integers Are Stored

C++ uses **two's complement** to store signed integers. The core rules of two's complement:

- **Positive numbers**: simply their binary representation, with high bits padded with 0.
- **Negative numbers**: take the corresponding positive number, invert all bits, then add 1.

```cpp
// 8-bit two's complement examples
// +1  →  00000001
// -1  →  ~00000001 + 1 = 11111110 + 1 = 11111111 = 0xFF
// +127 →  01111111 = 0x7F
// -128 →  10000000 = 0x80
```

The same logic applies to 32-bit `int`:
- `2147483647` → `0x7FFFFFFF` (largest positive)
- `-1` → `0xFFFFFFFF` (all 32 bits are 1)
- `-2147483648` → `0x80000000` (smallest negative)

A useful observation: under two's complement, `~c` is equivalent to `-1 - c`.

### The memset and 0x3F Trick

`memset(a, val, sizeof(a))` fills **every byte** of `a` with `val` (where `val` is between 0x00 and 0xFF). Because an `int` is 4 bytes, `memset` essentially "fills once per 8 bits".

```cpp
// Commonly used values:
memset(a, 0, sizeof(a));       // all zeros: 0x00000000 = 0
memset(a, -1, sizeof(a));      // all -1: 0xFFFFFFFF = -1
memset(a, 0x3F, sizeof(a));    // 0x3F3F3F3F ≈ 1.06×10^9
memset(a, 0x7F, sizeof(a));    // 0x7F7F7F7F ≈ 2.13×10^9 (close to INT_MAX)
```

`0x3F3F3F3F` is a wonderfully clever number — it is smaller than `INT_MAX` but large enough, and `0x3F3F3F3F + 0x3F3F3F3F` won't overflow. Many codebases use `memset(a, 0x3F, sizeof(a))` to initialize a "very large value".

---

## 0x02 Bitwise Operators

C++ provides six bitwise operators that operate directly on binary bits.

| Operator | Name | Effect | Example |
|----------|------|--------|---------|
| `&` | Bitwise AND | Result bit is 1 only if both corresponding bits are 1 | `5 & 3 = 1` (`101 & 011 = 001`) |
| `|` | Bitwise OR | Result bit is 1 if either corresponding bit is 1 | `5 | 3 = 7` (`101 | 011 = 111`) |
| `^` | Bitwise XOR | Result bit is 1 if the two bits differ, 0 if they are the same | `5 ^ 3 = 6` (`101 ^ 011 = 110`) |
| `~` | Bitwise NOT | 0 becomes 1, 1 becomes 0 | `~5 = -6` (under two's complement) |
| `<<` | Left shift | All bits shift left; 0s fill in on the right | `5 << 1 = 10` |
| `>>` | Right shift | All bits shift right | `5 >> 1 = 2` |

### Bitwise AND `&` — Checking a Specific Bit

```cpp
int x = 12;          // binary: 1100
if (x & 4) cout << "bit 3 is 1";  // 4 = 0100, x & 4 = 0100 ≠ 0
if (x & 1) cout << "odd number → true";   // the lowest bit determines parity
```

### Bitwise OR `|` — Setting a Bit to 1

```cpp
int x = 8;           // binary: 1000
x = x | 3;           // set the lowest two bits to 1: 1000 | 0011 = 1011 = 11
x |= (1 << 2);       // set bit 2 to 1 (bit 0 is the least significant bit)
```

### Bitwise XOR `^` — Flipping / Deduplication / Swapping

The properties of XOR are extremely important:
- `a ^ a = 0` (anything XOR itself gives 0)
- `a ^ 0 = a`
- XOR is commutative and associative

```cpp
// Classic application: find the element that appears an odd number of times
int ans = 0;
for (int i = 0; i < n; i++) ans ^= a[i];
// ans is that number — all other numbers cancel out in pairs

// Swap two numbers without a temporary variable
a ^= b;  b ^= a;  a ^= b;
// But usually swap(a, b) is clearer
```

### Bitwise NOT `~`

```cpp
int x = 5;    // 000...0101
int y = ~x;   // 111...1010 = -6 (two's complement)
// Pattern: ~x = -x - 1
```

---

## 0x03 Shift Operations

### Left Shift `<<`

`n << k` = $n \times 2^k$. All bits move left by $k$ positions; 0s fill in on the right.

```cpp
cout << (1 << 5);    // 32, i.e. 2^5
cout << (3 << 2);    // 12, i.e. 3 × 4
```

`1 << k` is the standard way to generate a bitmask of length $k$ (with the $k$-th bit set to 1).

### Right Shift `>>`

There are two kinds:

- **Logical right shift**: high bits are filled with 0 (used for `unsigned`)
- **Arithmetic right shift**: high bits are filled with the sign bit (used for signed `int`, preserving the sign)

```cpp
int a = 5;
cout << (a >> 1);    // 2, equivalent to floor(5/2)

int b = -3;
cout << (b >> 1);    // -2 (arithmetic right shift, fills with 1s)
// Note: (-3) / 2 = -1, but (-3) >> 1 = -2
// Right shift rounds "downwards" (toward negative infinity),
// while integer division rounds "toward zero"
```

> ⚠️ In C++, the right shift of a signed integer is **implementation-defined** (most compilers use arithmetic right shift). Do not make assumptions about the right-shift behavior of negative numbers.

### Shift vs. Multiplication/Division

```cpp
// For positive integer division with guaranteed floor semantics:
int half = n >> 1;       // equivalent to floor(n/2); faster than n/2,
                         // though compilers usually optimize this automatically

// Modulo by powers of 2:
int mod8 = n & 7;        // equivalent to n % 8, but only works for 2^k
int mod16 = n & 15;      // equivalent to n % 16
```

---

## 0x04 Fast Exponentiation

Compute $a^b \bmod p$. If you simply multiply $b$ times in a loop, the complexity is $O(b)$. When $b$ reaches the order of $10^9$, fast exponentiation is needed.

### Core Idea

Decompose $b$ into binary: $b = c_0 \cdot 2^0 + c_1 \cdot 2^1 + \cdots + c_k \cdot 2^k$, where $c_i \in \{0, 1\}$.

Then:
$$a^b = a^{c_0 \cdot 2^0} \times a^{c_1 \cdot 2^1} \times \cdots \times a^{c_k \cdot 2^k}$$

Traverse the bits of $b$ from low to high:
- If the current bit is 1: multiply the answer by the current power of $a$
- Square $a$ at each step to prepare for the next bit

Complexity: $O(\log b)$.

```cpp
// Compute (a ^ b) % p
int power(int a, int b, int p) {
    int ans = 1 % p;
    for (; b; b >>= 1) {
        if (b & 1) ans = (long long)ans * a % p;
        a = (long long)a * a % p;
    }
    return ans;
}
```

> 💡 The cast to `(long long)` prevents overflow: multiplying two `int`s (each up to $\sim 2\times 10^9$) can exceed the `int` range.

### Step-by-Step Walkthrough

Take $a=3$, $b=13$, $p=100$ as an example. $b = 13 = 1101_2$:

| Step | b (binary) | b & 1? | ans | a |
|------|------------|--------|-----|---|
| Initial | 1101 | — | 1 | 3 |
| Round 1 | 1101 | ✓ | $1 \times 3 = 3$ | $3^2 = 9$ |
| Round 2 | 110 | ✗ | 3 | $9^2 = 81$ |
| Round 3 | 11 | ✓ | $3 \times 81 = 243 \equiv 43$ | $81^2 = 6561 \equiv 61$ |
| Round 4 | 1 | ✓ | $43 \times 61 = 2623 \equiv 23$ | — |

Thus $3^{13} \bmod 100 = 23$.

---

## 0x05 64-bit Integer Multiplication

When $a, b, p$ are all on the order of $10^{18}$, $a \times b$ will exceed the range of `long long` (64-bit, max ~$9\times 10^{18}$). We need to compute $a \times b \bmod p$ without overflow.

### Method 1: Binary Decomposition (Analogue of Fast Exponentiation)

Decompose multiplication into binary addition. Complexity: $O(\log b)$.

```cpp
// Compute (a * b) % p; a, b, p are all within the long long range
long long mul(long long a, long long b, long long p) {
    long long ans = 0;
    for (; b; b >>= 1) {
        if (b & 1) ans = (ans + a) % p;
        a = a * 2 % p;
    }
    return ans;
}
```

### Method 2: Estimate with `long double`

Use the precision of `long double` (about 18–19 significant digits) to estimate $\lfloor a\times b / p \rfloor$, then apply a correction.

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

This method is faster than binary decomposition, but relies on `long double` precision and may fail on extreme test data. Both methods are viable in contests; beginners should prioritize mastering Method 1.

---

## 0x06 Binary State Compression

For a set of $n$ elements, where each element can be chosen or not, there are $2^n$ possible states. An $n$-bit binary number can represent all states — the $i$-th bit being 1 means the $i$-th element is selected.

This is the core idea of **state compression**.

### Basic Operations

```cpp
int mask = 0;                     // empty set
mask |= (1 << i);                 // add the i-th element
mask ^= (1 << i);                 // toggle the i-th element (add if absent, remove if present)
mask &= ~(1 << i);                // remove the i-th element
if (mask & (1 << i)) { /* the i-th element is in the set */ }

// Enumerate all subsets of mask
for (int sub = mask; sub; sub = (sub - 1) & mask) {
    // sub is a non-empty subset of mask
}
// The empty set must be handled separately

// Check the k-th bit of n (0-indexed)
if (n & (1 << k)) { /* ... */ }
// Equivalent to: if ((n >> k) & 1) { /* ... */ }
```

---

## 0x07 lowbit

`lowbit(n)`: the value represented by the **lowest 1-bit** in the binary representation of $n$.

```cpp
lowbit(n) = n & (-n)
```

Explanation: Under two's complement, `-n = ~n + 1`. Let the lowest 1-bit of $n$ be at position $k$. Then in `~n`, the $k$-th bit is 0 and all lower bits are 1; adding 1 restores the $k$-th bit to 1 and sets all lower bits to 0. Taking `n & (-n)` keeps only the $k$-th bit's 1.

```cpp
// lowbit(12) = lowbit(1100₂) = 4 (the 1 at bit position 2)
// lowbit(7)  = lowbit(0111₂) = 1 (the 1 at bit position 0)
```

### Application: Enumerating All 1-bits in a Number

```cpp
const int MAX_N = 1 << 20;
int H[MAX_N + 1];
for (int i = 0; i <= 20; i++) H[1 << i] = i;  // precompute the exponent for each power of 2

int n;
while (cin >> n) {
    while (n > 0) {
        int lb = n & -n;
        cout << H[lb] << ' ';   // output the position of the lowest 1-bit
        n -= lb;                // remove the lowest 1-bit
    }
}
```

`lowbit` is the foundational operation behind the **Fenwick Tree (Binary Indexed Tree)**, which will be explored in detail in chapter 0x42.

---

## 0x08 GCC Built-in Bitwise Functions

The GCC compiler provides efficient built-in bitwise functions that compile directly to CPU instructions.

```cpp
// Count the number of 1-bits (population count)
int cnt = __builtin_popcount(x);         // unsigned int
int cnt = __builtin_popcountll(x);       // unsigned long long

// Count trailing zeros
int tz = __builtin_ctz(x);               // how many zeros after the lowest 1-bit
int tz = __builtin_ctzll(x);             // long long version

// Count leading zeros
int lz = __builtin_clz(x);               // how many zeros before the highest 1-bit
```

These functions are much faster than manual loop implementations and are very useful in problems that require frequent bit counting.

```cpp
// Example: inspect the binary representation of a number
int x = 42;  // 101010₂
cout << __builtin_popcount(x);  // 3 (three 1-bits)
cout << __builtin_ctz(x);       // 1 (the lowest 1-bit is at position 1, i.e., the 2nd from the right)
```

---

## 0x09 More XOR Tricks

### Pairwise Transformation

For any integer $n$:
- If $n$ is even, `n ^ 1 = n + 1`
- If $n$ is odd, `n ^ 1 = n - 1`

```cpp
// This property is very useful in the "paired edge storage" technique in graph theory
// When storing undirected edges, forward and reverse edges are stored adjacently
// (IDs 2 and 3, 4 and 5, ...).
// Use i ^ 1 to find the reverse edge of the current edge.
```

This trick is used in the adjacency list (chained forward star) section in 0x13 and in later network flow chapters.

---

## Practice Problems

### P1 Count the 1-bits

> Input an `unsigned int`; output the number of 1-bits in its binary representation.

<details>
<summary>Hint</summary>
Method 1: Loop 32 times, checking the lowest bit each time.

Method 2: Use `n &= (n-1)` to remove the lowest 1-bit each iteration.

Method 3: Use `__builtin_popcount`.

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
        n &= (n - 1);  // remove the lowest 1-bit
        cnt++;
    }
    cout << cnt << endl;
    return 0;
}
```

</details>

### P2 Find the Number that Appears Only Once

> Given $n$ integers, exactly one of which appears an odd number of times; all others appear an even number of times. Find that number. $n \le 10^6$.

<details>
<summary>Hint</summary>

Use `a ^ a = 0` and `a ^ 0 = a`. XOR all numbers together; numbers appearing in pairs cancel out, leaving only the answer.

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

### P3 Enumerate Subsets

> Input $n$ ($n \le 16$) and an $n$-bit binary mask `mask`. Output the decimal values of all subsets of `mask` (including the empty set and `mask` itself).

<details>
<summary>Hint</summary>

You can use `for (int sub = mask; ; sub = (sub - 1) & mask)`, but remember to handle the empty set separately at the end.

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

### P4 Fast Exponentiation (Template) [**Luogu P1226**](https://www.luogu.com.cn/problem/P1226)

> **Luogu P1226**: Given $a, b, p$, compute $a^b \bmod p$. $0 \le a, b < 2^{31}$, $2 \le p < 2^{31}$.

<details>
<summary>Hint</summary>
Standard fast exponentiation template.

Notes: (1) Take `a` modulo `p` after reading input;

(2) Initialize `ans` as `1 % p` (to handle the edge case `p = 1`);

(3) Use `long long` for intermediate multiplication results to prevent overflow. Output format: `a^b mod p=s`.

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

### ⭐ P5 The Perplexing Switch [**Luogu P10449**](https://www.luogu.com.cn/problem/P10449)

> **Luogu P10449**: Given a $5 \times 5$ 01 matrix. Changing the state of one light also flips the state of its four orthogonal neighbors (up, down, left, right). Determine whether all lights can be turned on (all 1s) within 6 moves. Output the minimum number of moves, or `-1` if impossible within 6 moves. Up to $n \le 500$ test cases.

*This is a challenge problem. Please devise your own solution.*

---

### ⭐ P6 Getting Up Is Hard [**Luogu P2114 (NOI 2014)**](https://www.luogu.com.cn/problem/P2114)

> **Luogu P2114 (NOI 2014)**: There are $n$ defense gates, each performing a bitwise operation (`AND` / `OR` / `XOR`) with a parameter $t$. The initial attack power $x$ can be chosen freely from $[0, m]$. After passing through all gates, a final damage value is produced. Find the maximum possible damage. $n \le 10^5$, $m, t \le 10^9$.

*This is a challenge problem. Please devise your own solution.*

---

## Self-Check

Go through each item; you should be able to answer every one off the top of your head:

- [ ] Know that `int` is a 32-bit signed integer with a range of approximately $\pm 2.1\times 10^9$
- [ ] Understand two's complement: know that `~x = -x - 1` and that `0xFFFFFFFF = -1`
- [ ] Can use `memset(a, 0x3F, sizeof(a))` to initialize an array with a "large value"
- [ ] Proficiently use the six bitwise operators `& | ^ ~ << >>`
- [ ] Know that `a ^ a = 0` and `a ^ 0 = a`
- [ ] Can use XOR to find the sole number that appears an odd number of times
- [ ] Understand the difference between arithmetic and logical right shifts
- [ ] Can write fast exponentiation `(a^b) % p` with $O(\log b)$ complexity
- [ ] Understand the role of the `(long long)` cast in fast exponentiation
- [ ] Can write 64-bit integer multiplication `(a*b) % p` (binary decomposition method)
- [ ] Can use `1 << k` to generate a bitmask
- [ ] Can use `mask | (1 << i)` to add an element and `mask & ~(1 << i)` to remove an element
- [ ] Can represent sets using binary state compression
- [ ] Know that `lowbit(n) = n & (-n)` and understand the principle behind it
- [ ] Can use `lowbit` to enumerate all 1-bits in a number
- [ ] Know the purposes of `__builtin_popcount` and `__builtin_ctz`
- [ ] Know the role of `n ^ 1` in pairing even/odd adjacent indices
