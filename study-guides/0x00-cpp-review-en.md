# 0x00 From Variables to Functions

You already know how to write simple C++ programs — you can define variables, use `cin`/`cout`, write `if` and `for`. But there's a gap between writing code that *runs* and writing code that *never silently breaks*. This chapter fills that gap.

After reading this, you should be able to comfortably write all the code needed for the chapters ahead.

---

## 0x01 Variables & Data Types

Every variable in C++ has a type. A type determines two things: **what it can store**, and **how much space it takes**.

```cpp
int a = 42;           // integer, 4 bytes, range roughly ±2.1×10⁹
long long b = 1e18;   // large integer, 8 bytes, range roughly ±9×10¹⁸
double x = 3.14;      // floating-point, ~15 significant digits
char c = 'A';         // single character
bool flag = true;     // only true or false
string s = "hello";   // string (requires #include <string>)
```

### Integer Division

When two `int`s are divided, the result is still an `int`. The fractional part is **truncated toward zero** — not floored.

```cpp
cout << 5 / 2;      // 2, not 2.5 — truncated toward zero, not rounded down
cout << 5.0 / 2;    // 2.5 (one side is double, that's enough)
```

### Integer Overflow

The maximum `int` is roughly 2.1 billion. Exceed that and the value "wraps around" into negatives — the compiler won't warn you, your answer just silently goes wrong. We'll cover *why* it wraps to negatives in a later chapter.

```cpp
int a = 100000, b = 100000;
cout << a * b;      // overflow, prints garbage
cout << (long long)a * b;  // correct: cast to long long first
```

In competitive programming, whenever multiplication or accumulation is involved, **default to `long long`**, unless you're certain the result won't overflow.

### Type Casting

Converting one data type into another temporarily. You're telling the compiler: "treat this as something else."

**Implicit conversion (automatic)**

```cpp
int a = 5;
double b = a;        // int automatically becomes double, b = 5.0
double c = 3.14;
int d = c;           // double automatically becomes int, fractional part truncated, d = 3 (NOT rounding!)
```

**Explicit casting (you ask for it)**

```cpp
int a = 5, b = 2;
cout << a / b;              // prints 2 (integer division, fractional part discarded)
cout << (double)a / b;      // prints 2.5 — temporarily treat a as double
cout << 1.0 * a / b;        // prints 2.5 — another common trick: multiply by 1.0
```

Three equivalent ways, pick your favorite:

```cpp
(double)a / b                // C-style
static_cast<double>(a) / b   // C++ recommended: safest, clearest intent
double(a) / b                // C++ function-style
```

**Three most common scenarios in CP**

```cpp
// Scenario 1: avoid integer division
int a = 5, b = 2;
cout << (double)a / b;       // 2.5, not 2

// Scenario 2: char to ASCII code
char c = 'A';
cout << (int)c;              // 65

// Scenario 3: long long × int, prevent overflow
int a = 100000, b = 100000;
long long ans = (long long)a * b;   // 10¹⁰, won't fit in int — must cast
```

### = vs ==

```cpp
if (x = 5)   // assigns 5 to x, condition is always true — almost never what you want
if (x == 5)  // compares whether x equals 5
```

Every time you write `if`, do a mental check: am I *comparing* or *assigning*?

---

## 0x02 Input & Output

```cpp
int n;
cin >> n;                       // read an integer
cout << n * 2 << endl;          // output with newline

int a, b;
cin >> a >> b;                  // chained reads, separated by spaces or newlines
cout << a + b << endl;
```

### Mixing cin and getline

`cin >> n` leaves the newline character in the buffer after reading the number. A `getline(cin, s)` right after will read that newline and give you an empty string.

```cpp
int n; cin >> n;
cin.ignore();                   // consume the leftover newline
string s; getline(cin, s);      // now works correctly
```

### scanf / printf (optional)

```cpp
int n; scanf("%d", &n);                    // %d: int
long long x; scanf("%lld", &x);            // %lld: long long
double y; scanf("%lf", &y);                // %lf: double
printf("%.2f\n", y);                       // two decimal places — honestly the only reason I use printf
```

`cin`/`cout` are good enough for daily use.

In contests, I recommend sticking to one input method — either only `cin`/`cout` or only `printf`/`scanf`. Because we often need:

```cpp
ios::sync_with_stdio(false);
cin.tie(0);
```

for fast I/O, which can cause weird buffer issues if you mix both styles — your input and output will explode!

---

## 0x03 Operators

```cpp
+  -  *     // addition, subtraction, multiplication
/           // division — integer division truncates
%           // modulo — integers only
```

### Modulo

```cpp
if (n % 2 == 0) cout << "even";
if (n % 2 == 1) cout << "odd";
```

Modulo is also great for "keeping things in range": `x % 10` is always between $0$ and $9$.

### Shorthand

```cpp
cnt++;       // equivalent to cnt = cnt + 1
sum += x;    // equivalent to sum = sum + x
a %= b;      // equivalent to a = a % b
```

### Prefix ++ vs Postfix ++

```cpp
int a = 5;
int b = a++;  // b = 5, a = 6 (use first, then increment)
int c = ++a;  // c = 7, a = 7 (increment first, then use)
```

In contests, postfix `++` is usually enough. The only rule: don't mix `a++` and `++a` inside complex expressions. Keep them on separate lines — it's safer.

---

## 0x04 Conditionals

```cpp
if (condition) {
    // ...
} else if (another condition) {
    // ...
} else {
    // ...
}
```

### Comparison Operators

`==` `!=` `<` `>` `<=` `>=`

### Logical Operators

| Operator | Meaning | Example |
|----------|---------|---------|
| `&&` | AND | `x > 0 && x < 100` — $x$ must be in $(0, 100)$ |
| `\|\|` | OR | `c == 'Y' \|\| c == 'y'` — $c$ is either uppercase or lowercase $y$ |
| `!` | NOT | `if (!done)` means `done == false` |

### Short-Circuit Evaluation

When the left side of `&&` is `false`, the right side **never executes**. Use this to write safe code:

```cpp
if (x != 0 && 10 / x > 2)   // when x=0, 10/x never runs — safe
if (10 / x > 2 && x != 0)   // dangerous! division by zero possible
```

Put the condition most likely to be `false` on the left of `&&`, and safety checks first.

### Floating-Point Comparison

```cpp
double a = 0.1 + 0.2;              // actually stored as 0.30000000000000004
if (a == 0.3) { /* false! */ }
if (abs(a - 0.3) < 1e-9) { /* this is correct */ }
```

For floating-point numbers, use `abs(a - b) < 1e-9` to check "close enough".

---

## 0x05 Loops

### for — when you know how many iterations

```cpp
for (int i = 1; i <= n; i++) {
    cout << i << ' ';
}
// prints 1 2 3 ... n
```

Three parts: ① initialization `int i = 1`, ② continuation condition `i <= n`, ③ per-iteration update `i++`. The execution logic:

1. Execute part ①
2. Check condition ② — if true, go to step 3; otherwise, exit the loop
3. Execute the body of the `for` statement
4. Execute part ③, then jump back to step 2

### while — when you don't know how many iterations

```cpp
while (n > 1) {
    if (n % 2 == 0) n /= 2;
    else n = 3 * n + 1;
}
```

Honestly, `while` is a bit redundant — `for` can replace `while` in almost every case!

### break and continue

```cpp
for (int i = 1; i <= 10; i++) {
    if (i == 5) break;          // exit the entire loop immediately
    if (i % 2 == 0) continue;   // skip this iteration, jump to i++
    cout << i << ' ';           // only prints 1 3
}
```

| | Effect |
|--|--------|
| `break` | Exit the loop entirely |
| `continue` | Skip the rest of this iteration |

### Multiple Test Cases

A common contest format: first line is T, then T test cases follow.

```cpp
int T; cin >> T;
while (T--) {
    int a, b; cin >> a >> b;
    cout << a + b << endl;
}
```

Reading until EOF (end of file):

```cpp
int a, b;
while (cin >> a >> b) {   // automatically stops when no more data
    cout << a + b << endl;
} // but this pattern is relatively rare
```

---

## 0x06 Arrays

### One-Dimensional Arrays

```cpp
int a[100];                                   // allocate 100 ints
for (int i = 0; i < n; i++) cin >> a[i];      // read n elements
for (int i = 0; i < n; i++) cout << a[i] << ' ';
```

### Zero-Based Indexing

```cpp
int a[5] = {10, 20, 30, 40, 50};
// a[0]=10  a[1]=20  a[2]=30  a[3]=40  a[4]=50
// there is NO a[5]! Remember: in programming, indices start from 0
```

The last element is `a[n-1]`, not `a[n]`. Internalizing this alone avoids the most common bug in contests.

### Two-Dimensional Arrays

```cpp
int grid[100][100];
for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
        cin >> grid[i][j];   // grid[i][j] = row i, column j
```

### Four Major Pitfalls

**① Out-of-bounds access**

```cpp
int a[100];
for (int i = 1; i <= 100; i++) a[i] = i;  // a[100] doesn't exist!
```

If the array size is $N$, valid indices are $0 \sim N-1$. If you prefer 1-based indexing with `for (int i = 1; i <= n; i++)`, declare your array as `a[n+5]` (leave some margin).

Many contest errors come from array out-of-bounds causing `Runtime Error` or `Wrong Answer` — depending on what memory you accidentally stomp on.

**② Uninitialized arrays**

```cpp
int a[100];          // local array — values are random garbage
cout << a[0];        // could be anything
```

This is why we recommend declaring arrays as **global variables** (outside any function) — then all values default to $0$.

**③ Large local arrays**

```cpp
void f() {
    int a[1000000];  // 1 million ints might overflow the stack
}
```

We strongly recommend putting large arrays ($> 10^5$ elements) in global scope.

**④ Variable-length arrays (VLA)**

```cpp
int n; cin >> n;
int a[n];            // not standard C++, don't do this
```

Use fixed sizes: `const int N = 100005; int a[N];` or learn `vector` later.

---

## 0x07 Functions

You've already written `main()` — it's a function itself. You've also called other people's functions: `swap(a, b)`, `sort(a, a+n)`, `abs(x)`. Now it's your turn to write your own.

### Why Functions

Suppose you need to check whether a number is prime, and this logic appears three times in your program. You could:

- **Option A**: copy-paste the prime-checking code three times. One bug means fixing three places.
- **Option B**: write an `isPrime(n)` function, one line each time you need it.

Functions let you **bundle, name, and reuse** a piece of logic. Shorter code, easier to fix.

### The Four Parts of a Function

```cpp
int Max(int a, int b) {  /*
 ①   ②       ③
*/
    if (a > b) return a;  // ④
    else return b; // ④
}
```

| Part | Example | Description |
|------|---------|-------------|
| ① Return type | `int` | What type of value this function sends back |
| ② Function name | `max` | Same naming rules as variables |
| ③ Parameter list | `(int a, int b)` | What the caller must pass in |
| ④ Return value | `return a;` | Sends the result back; type must match ① (or be implicitly convertible) |

Calling:

```cpp
int result = Max(10, 20);  // result = 20
cout << Max(3, 7);          // prints 7
```

### void Functions — Return Nothing

Some functions do work without returning a value. For example, printing a separator line:

```cpp
void printLine() {
    cout << "----------" << endl;
    // no return — or you can write "return;" optionally
}

int main() {
    printLine();  // just call it
    printLine();
    return 0;
}
```

`void` means "empty" — this function doesn't produce any value, it just does things.

### Parameters: Pass-by-Value vs Pass-by-Reference

**Pass-by-value (default)**: the function receives a *copy* of the variable. Modifying the copy doesn't affect the original.

```cpp
void addOne(int x) {
    x = x + 1;       // modifies the copy
}

int main() {
    int n = 5;
    addOne(n);
    cout << n;        // still 5!
    return 0;
}
```

**Pass-by-reference**: add `&`, and the function directly operates on the original variable.

```cpp
void addOne(int &x) {  // notice the &
    x = x + 1;         // modifies the original
}

int main() {
    int n = 5;
    addOne(n);
    cout << n;          // 6
    return 0;
}
```

When to use references?

- When you need to "return" multiple values (a function can only `return` one thing, but can pass multiple things out through reference parameters)
- When passing large objects (like `vector`, `string`) and don't want to copy — add `const`: `void print(const string &s)`, both safe and efficient

### Return-by-Value vs Return-by-Reference

```cpp
int square(int x) { return x * x; }              // return a value — most common
int& getElement(int a[], int i) { return a[i]; } // return a reference — allows modifying array elements
```

At this stage, almost always use return-by-value. Returning references is an advanced topic — just know it exists for now.

### Declaration and Definition Can Be Separate

Sometimes you want `main` at the top and helper functions below. The compiler reads top-to-bottom and will complain about function names it hasn't seen yet. The fix: **declare** at the top, **define** later.

```cpp
#include <iostream>
using namespace std;

// Declaration — only the function header, no body
int max(int a, int b);
void printLine();

int main() {
    cout << max(3, 5) << endl;
    printLine();
    return 0;
}

// Definition — the full function body
int max(int a, int b) {
    return (a > b) ? a : b;
}

void printLine() {
    cout << "----------" << endl;
}
```

### Recursion — A Function That Calls Itself

A function directly or indirectly calling itself is recursion.

The classic example: computing n! = 1×2×3×...×n.

```cpp
int factorial(int n) {
    if (n == 0) return 1;             // base case — without this, infinite recursion
    return n * factorial(n - 1);      // n! = n × (n-1)!
}

// factorial(5) = 5 * factorial(4)
//              = 5 * 4 * factorial(3)
//              = ... = 120
```

Two essential ingredients of recursion:

1. **Base case**: recursion must have a stopping point, or it loops forever
2. **Each step moves closer to the base case**: `factorial(n-1)` is closer to `n=0` than `factorial(n)`

Recursion is the foundation for search, divide-and-conquer, and dynamic programming later. For now, you just need to be able to read recursion and write the simplest recursive functions.

### Scope — Where Variables Live

```cpp
int global = 10;         // global variable — accessible everywhere in the program

void f() {
    int x = 5;           // local variable — only valid inside this function
    cout << global;      // can access globals
}

int main() {
    int y = 3;
    f();
    // cout << x;        // error! x is local to f(), invisible here
    // cout << y;        // OK, y is local to main
}
```

One rule: a variable lives inside the pair of braces where it's defined. Once execution leaves those braces, the variable dies.

### Common Pitfalls

**① Returning a reference to a local variable (serious bug)**

```cpp
int& f() {
    int x = 5;
    return x;   // dangerous! x is destroyed when the function ends — returning garbage
}
```

Local variables cease to exist when the function returns. Returning a reference to a no-longer-existing variable is called a "dangling reference" — the result is undefined behavior. At this stage, stick to `int`, `bool`, `void` as return types. Don't return `int&`.

**② Forgetting return**

```cpp
int max(int a, int b) {
    if (a > b) return a;
    // if a <= b, no return — undefined behavior!
}
```

The compiler might not warn you, but program behavior is unpredictable. Make sure every branch has a `return`, or add a fallback return at the end of the function.

Also, your `main` function needs `return 0`! Otherwise it might cause the program to behave abnormally!

**③ Passing a temporary to a non-const reference parameter**

```cpp
void f(int &x) { x++; }
f(5);  // error! 5 is a literal, cannot bind to non-const reference
```

**④ Recursion without a base case**

```cpp
int f(int n) {
    return n * f(n - 1);  // no if statement — infinite recursion, stack overflow
}
```

### Passing Arrays to Functions

```cpp
void printArray(int a[], int n) {  // array parameter + size parameter
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    printArray(arr, 5);
}
```

When an array is passed as a parameter, what's actually passed is a **pointer** — so modifying `a[i]` inside the function affects the original array (no `&` needed). You must also pass the array size separately, because the function has no way to know how large the array is.

> Once you learn `vector`, `printVector(vector<int> &v)` can call `.size()` — no need to pass the size separately.

---

## 0x08 Structs

Arrays bundle data of the **same type** together. Structs bundle data of **different types** that all belong to the same thing.

### Definition and Usage

```cpp
struct Student {
    string name;
    int age;
    double score;
};  // don't forget the semicolon!

int main() {
    Student s1;
    s1.name = "Alice";
    s1.age = 16;
    s1.score = 95.5;

    cout << s1.name << " scored " << s1.score << endl;
}
```

A struct is a custom type — just like `int` or `string`, you can declare variables, create arrays, and pass as arguments. Use `.` to access members.

### Initialization

```cpp
Student s1 = {"Bob", 17, 88.0};    // assign in definition order
Student s2{"Carol", 16, 92.5};     // can also omit the equals sign
```

### Arrays of Structs

```cpp
Student a[50];              // 50 students
for (int i = 0; i < n; i++)
    cin >> a[i].name >> a[i].age >> a[i].score;
```

### Nested Structs

```cpp
struct Date { int year, month, day; };

struct Student {
    string name;
    Date birthday;          // struct inside struct
    double score;
};

// access: s.birthday.year
```

### Structs as Function Parameters

```cpp
void print(const Student &s) {   // const reference: read-only, no copy, efficient
    cout << s.name << endl;
}

void update(Student &s, double ns) {  // reference: can modify original
    s.score = ns;
}
```

Same as with regular variables: pass by value makes a copy; add `&` to pass by reference and operate on the original. Structs can be large, so passing by reference is more efficient.

### Struct vs Array vs Variable

| Scenario | Use |
|----------|-----|
| A bunch of numbers of the same type | `int a[100]` |
| Different types belonging to one thing | `struct Student s` |
| A bunch of structs | `Student a[50]` |

### Common Pitfalls

**① Forgetting the semicolon**

```cpp
struct Point { int x, y; }   // compiler error! missing ; at the end
```

**② Using `==` to compare two structs**

```cpp
Student a = {"Alice", 16, 90.0};
Student b = {"Alice", 16, 90.0};
if (a == b) { /* compiler error! structs can't be compared with == */ }
```

You must compare each field manually. Once you learn operator overloading, this can be solved.

**③ Memory alignment (padding)**

Structs may have padding bytes inserted between members in memory. `sizeof(StructName)` might be slightly larger than the sum of member sizes. Don't worry about this for now — just know it exists. Interested students can try the challenge problem P9754 [CSP-S 2023] on struct alignment.

## Practice Problems

### P1 [CSP-J 2019] Number Game (P5660) [P5660 Number Game](https://www.luogu.com.cn/problem/P5660)

> Given an 8-character string of 0s and 1s, count how many `1`s there are.

<details>
<summary>Hint</summary>

Traverse each character of the string. Every time you see `'1'`, increment a counter. The string length is always 8, so a `for` loop from 0 to 7 works.

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
    for (int i = 0; i < s.size(); i++)
        if (s[i] == '1') cnt++;
    cout << cnt << endl;
    return 0;
}
```

</details>

### P2 [NOIP 2005 Popularization] Tao Tao Picking Apples (P1046) [P1046 Tao Tao Picking Apples](https://www.luogu.com.cn/problem/P1046)

> 10 apple heights + Tao Tao's maximum reach height. With a 30cm stool, how many apples can she reach?

<details>
<summary>Hint</summary>

Tao Tao's maximum reach = her height + 30. Loop through the 10 apples; if apple height ≤ max reach, increment the counter.

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
using namespace std;

int main() {
    int a[10];
    for (int i = 0; i < 10; i++) cin >> a[i];
    int h;
    cin >> h;
    int cnt = 0;
    for (int i = 0; i < 10; i++)
        if (a[i] <= h + 30) cnt++;
    cout << cnt << endl;
    return 0;
}
```

</details>

### P3 [NOIP 2004 Improvement] Jinjin's Savings Plan (P1089) [P1089 Jinjin's Savings Plan](https://www.luogu.com.cn/problem/P1089)

> Each month, Mom gives 300 yuan. Jinjin budgets 12 months of expenses. If any month runs out of money, print `-month`. Otherwise, at year's end, print total savings + 20% interest.

<details>
<summary>Hint</summary>

Simulate all 12 months: each month, add 300, subtract the budget. If balance < 0, immediately print `-month` and exit. Otherwise, deposit whole hundreds (`saved += balance / 100 * 100`), and keep only the remainder (`balance %= 100`). At year's end, output `balance + saved * 1.2`.

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
using namespace std;

int main() {
    int budget, balance = 0, saved = 0;
    for (int month = 1; month <= 12; month++) {
        cin >> budget;
        balance += 300;
        if (balance < budget) {
            cout << -month << endl;
            return 0;
        }
        balance -= budget;
        saved += balance / 100 * 100;
        balance %= 100;
    }
    cout << balance + saved * 1.2 << endl;
    return 0;
}
```

</details>

### P4 [NOIP 2013 Popularization] Counting Problem (P1980) [P1980 Counting Problem](https://www.luogu.com.cn/problem/P1980)

> Count how many times digit $x$ appears in all integers from $1$ to $n$. $n \le 10^6$.

<details>
<summary>Hint</summary>

Loop from $1$ to $n$. For each number, break it down digit by digit: `while (t > 0) { if (t % 10 == x) cnt++; t /= 10; }`. Note that $x$ could be 0, but leading digits of a number are never 0 — and we're only counting $1 \sim n$, so no leading-zero issue arises.

</details>

<details>
<summary>Solution</summary>

```cpp
#include <iostream>
using namespace std;

int main() {
    int n, x, cnt = 0;
    cin >> n >> x;
    for (int i = 1; i <= n; i++) {
        int t = i;
        while (t > 0) {
            if (t % 10 == x) cnt++;
            t /= 10;
        }
    }
    cout << cnt << endl;
    return 0;
}
```

</details>

---

### ⭐ Challenge P5 [CSP-S 2020] Julian Day (P7075) [P7075 Julian Day](https://www.luogu.com.cn/problem/P7075)

> Given a Julian day number, convert it to a Gregorian calendar date. Involves BC/AD transitions, leap year rule changes, and the 10 days deleted in October 1582. $Q \le 10^5$, Julian day up to $10^9$.

This problem barely uses syntax beyond this chapter, but tests your **simulation skills** and **attention to detail**. You'll need to carefully handle:
- BC era (the year after 1 BC is AD 1 — there is no year 0)
- Julian vs Gregorian leap year rules differ
- October 4, 1582 is followed by October 15, 1582
- Multiple queries require $O(1)$ or $O(\log n)$ per query — no day-by-day simulation

### ⭐ Challenge P6 [CSP-S 2023] Struct (P9754) [P9754 Struct](https://www.luogu.com.cn/problem/P9754)

> Simulate C++-like struct definitions, supporting four operations: define a struct type, define an element, access an element's address, and reverse-lookup an element from an address. Involves memory alignment rules.

This problem is directly related to section 0x08 on structs, but its difficulty far exceeds the introductory level. You'll need to:
- Understand and simulate C++ memory alignment rules
- Maintain a mapping of type name → size/alignment/member list
- Maintain the starting address of defined elements
- Implement `.`-separated nested access path resolution
- Implement address reverse-lookup: determine which element a given address belongs to

> Hint: use `map<string, TypeInfo>` for type info and `map<string, ElementInfo>` for element info. For operation 4 (address lookup), you can maintain an address-to-element-name mapping. Operations 1 and 2 are essentially about computing sizes and offsets according to alignment rules.

> **Suggested approach**: complete P1–P4 first to ensure a solid foundation. If you're eager after reading 0x08, go for P6. P5 is great for those who enjoy astronomy/history simulation. Neither challenge problem affects your ability to study subsequent chapters.

---

## Self-Check

Go through each item — you should be able to answer without hesitation:

- [ ] Know when to use `long long` instead of `int`
- [ ] Won't write `5 / 2` expecting 2.5
- [ ] Won't confuse `=` and `==`
- [ ] Can use `cin`/`cout` to read and write data
- [ ] Can use `%` to check odd/even
- [ ] Can write `if / else if / else` structures
- [ ] Understand the short-circuit behavior of `&&` and `||`
- [ ] Can write `for` and `while`, know `break` and `continue`
- [ ] Can handle multiple test cases (`while(T--)` and `while(cin>>...)`)
- [ ] Can define and traverse arrays, know indices start from 0
- [ ] Know what out-of-bounds means and how to avoid it

- [ ] Can write a function with parameters and a return value
- [ ] Understand `void` — a function that doesn't return anything
- [ ] Understand pass-by-value vs pass-by-reference, and when to add `&`
- [ ] Understand that function declaration and definition can be separate
- [ ] Can read recursion, know what a base case is
- [ ] Won't write code that returns a reference to a local variable
- [ ] Know how to pass an array to a function

- [ ] Can define a struct, create an instance, and access members with `.`
- [ ] Can initialize a struct: `{"Alice", 16, 95.5}`
- [ ] Can create and traverse an array of structs
- [ ] Understand nested structs (struct inside struct)
- [ ] Know that `const &` is the most efficient way to pass structs as parameters
- [ ] Know that structs can't be compared with `==` directly
