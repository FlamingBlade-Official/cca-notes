# C++ STL Containers: Your First Toolbox

> **Prerequisites:** You know how to write a `for` loop, declare variables, and use `cin`/`cout`.  
> **Goal:** By the end of this guide, you'll know which container to reach for — and why.

---

## 📦 What is the STL?

STL = **Standard Template Library**. Think of it as a toolbox that comes pre-installed with C++. Instead of writing everything from scratch (like a dynamic array or a sorting algorithm), you use the tools already in the box. They are fast, well-tested, and used by competitive programmers worldwide.

All STL containers live under `#include` headers. For this guide, you'll need:

```cpp
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
```

> 💡 We'll introduce `using namespace std;` implicitly in examples. In contests, it's common practice.

---

## 1. `vector` — The Dynamic Array

### What is it?

A `vector` is an array that can **grow and shrink** automatically. You don't need to know its size in advance. It stores elements **contiguously** in memory, so accessing any element by index is O(1).

<details>
<summary><b>🧠 Think: when would you use a vector over a plain array?</b></summary>

When you don't know how many elements you'll have at compile time. For example: reading N numbers where N is given at runtime, and N can vary each time the program runs.

</details>

### Declaration & Initialization

```cpp
vector<int> v;                  // empty vector of ints
vector<int> v(10);              // 10 elements, all initialized to 0
vector<int> v(10, 5);           // 10 elements, all initialized to 5
vector<int> v = {1, 2, 3, 4};   // initializer list
vector<int> v2(v);              // copy of v
```

### Core Operations

| Operation | Code | Time |
|-----------|------|------|
| Add to end | `v.push_back(x)` | O(1)* |
| Remove from end | `v.pop_back()` | O(1) |
| Access by index | `v[i]` or `v.at(i)` | O(1) |
| First / last element | `v.front()` / `v.back()` | O(1) |
| Number of elements | `v.size()` | O(1) |
| Check if empty | `v.empty()` | O(1) |
| Remove all elements | `v.clear()` | O(n) |

> *`push_back` is **amortized** O(1). Occasionally the vector needs to reallocate, but on average it's constant time.

### Iterating

```cpp
// Classic index loop
for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
}

// Range-based for (C++11+)
for (int x : v) {
    cout << x << " ";
}
```

### Sorting a Vector

```cpp
#include <algorithm>
sort(v.begin(), v.end());                        // ascending
sort(v.begin(), v.end(), greater<int>());         // descending
sort(v.begin(), v.begin() + k);                   // sort first k elements only
```

<details>
<summary><b>⚠️ Common Pitfall: out-of-bounds access</b></summary>

```cpp
vector<int> v = {1, 2, 3};
cout << v[5];        // UNDEFINED BEHAVIOR — v only has indices 0, 1, 2
cout << v.at(5);     // Throws std::out_of_range exception (safer for debugging)
```

Always check `i < v.size()` before accessing `v[i]`.

</details>

<details>
<summary><b>⚠️ Common Pitfall: iterator invalidation</b></summary>

If you `push_back` and the vector reallocates, all iterators (and pointers) to elements become invalid. If you're just using indices (`v[i]`), you're safe.

</details>

### Practice

<details>
<summary><b>📝 Problem 1: Read N numbers, output them in reverse order</b></summary>
**Input:**

```
5
1 2 3 4 5
```
**Output:**
```
5 4 3 2 1
```

<details>
<summary><b>Solution</b></summary>

```cpp
int n;
cin >> n;
vector<int> v(n);
for (int i = 0; i < n; i++) cin >> v[i];
for (int i = n - 1; i >= 0; i--) cout << v[i] << " ";
```

</details>
</details>

---

## 2. `stack` — Last In, First Out (LIFO)

### What is it?

Imagine a stack of plates. You can only add a plate to the **top**, and you can only take a plate from the **top**. The last plate you put on is the first one you take off.

### When to use it?

- Undo / redo functionality
- Checking balanced parentheses: `((()))` ✅ vs `(()` ❌
- Depth-First Search (DFS)
- Evaluating expressions (postfix notation)
- Any problem where you need to "go back to what you just saw"

### Core Operations

| Operation | Code | Time |
|-----------|------|------|
| Push onto top | `s.push(x)` | O(1) |
| Pop from top | `s.pop()` | O(1) |
| View top element | `s.top()` | O(1) |
| Size | `s.size()` | O(1) |
| Check if empty | `s.empty()` | O(1) |

> ⚠️ `pop()` does **not** return the value — it just removes the top. Use `top()` first to get the value.

### Example: Balanced Parentheses

```cpp
#include <stack>
#include <string>

bool isBalanced(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(') {
            st.push(c);
        } else {  // c == ')'
            if (st.empty()) return false;  // no matching '('
            st.pop();
        }
    }
    return st.empty();  // true if all '(' were matched
}
```

<details>
<summary><b>🧠 Trace through: what does the stack look like at each step for "(()())" ?</b></summary>

| Step | Char | Stack after | Notes |
|------|------|-------------|-------|
| 1 | `(` | `[(` | push |
| 2 | `(` | `[(, (]` | push |
| 3 | `)` | `[(]` | pop — matches the last `(` |
| 4 | `(` | `[(, (]` | push |
| 5 | `)` | `[(]` | pop |
| 6 | `)` | `[]` | pop — stack empty ✅ |

Final stack is empty → balanced!

</details>

<details>
<summary><b>⚠️ Common Pitfall: calling top() or pop() on an empty stack</b></summary>

```cpp
stack<int> st;
st.pop();    // UNDEFINED BEHAVIOR — always check !st.empty() first!
```

</details>

---

## 3. `queue` — First In, First Out (FIFO)

### What is it?

Like a line of people at a ticket counter. The first person to arrive is the first person served. The last person goes to the back.

### When to use it?

- Breadth-First Search (BFS)
- Simulating a waiting line
- Buffering / processing tasks in arrival order

### Core Operations

| Operation | Code | Time |
|-----------|------|------|
| Add to back | `q.push(x)` | O(1) |
| Remove from front | `q.pop()` | O(1) |
| View front element | `q.front()` | O(1) |
| View back element | `q.back()` | O(1) |
| Size | `q.size()` | O(1) |
| Check if empty | `q.empty()` | O(1) |

<details>
<summary><b>🧠 How is queue different from stack?</b></summary>

| | Stack | Queue |
|------|-------|-------|
| Principle | LIFO (Last In, First Out) | FIFO (First In, First Out) |
| Insert | `push()` — top | `push()` — back |
| Remove | `pop()` — top | `pop()` — front |
| Access | `top()` only | `front()` and `back()` |

Stack: like a pile of books — you grab the top one.  
Queue: like a checkout line — first person in line goes first.

</details>

### Example: Simple BFS Traversal (Conceptual)

```cpp
queue<int> q;
q.push(start);
while (!q.empty()) {
    int current = q.front();
    q.pop();
    
    // process current node...
    
    for (int neighbor : graph[current]) {
        q.push(neighbor);
    }
}
```

<details>
<summary><b>📝 Practice Problem: Simulate a queue of students</b></summary>

N students arrive one by one. Then M "serve" operations happen: each serves the student at the front. Output the IDs of served students.

**Input:**
```
5 3
1 2 3 4 5
```
(N=5 students, M=3 serves, IDs: 1 through 5)

**Output:**
```
1
2
3
```

<details>
<summary><b>Solution</b></summary>

```cpp
int n, m;
cin >> n >> m;
queue<int> q;
for (int i = 0; i < n; i++) {
    int id; cin >> id;
    q.push(id);
}
for (int i = 0; i < m; i++) {
    cout << q.front() << "\n";
    q.pop();
}
```

</details>
</details>

---

## 4. `priority_queue` — Always Grab the Biggest (or Smallest)

### What is it?

A `priority_queue` is like a queue, but instead of "first come, first served", the **largest** (or smallest) element is always served first. It is implemented as a **max-heap** internally — a binary tree structure where the parent is always ≥ its children.

> 🧠 By default, `priority_queue` is a **max-heap**: `top()` returns the **largest** element.

### Declaration

```cpp
#include <queue>  // priority_queue lives here!

priority_queue<int> pq;                              // max-heap (largest on top)
priority_queue<int, vector<int>, greater<int>> pq2;  // min-heap (smallest on top)
```

<details>
<summary><b>🧠 Why the weird syntax for min-heap?</b></summary>

The full template is: `priority_queue<Type, Container, Comparator>`.  
- `vector<int>` is the underlying container (always a vector for priority_queue).  
- `greater<int>` flips the comparison — making it a min-heap.

It's ugly, but you'll get used to it. Just memorize:

```cpp
// Max-heap (default, most common)
priority_queue<int> pq;

// Min-heap
priority_queue<int, vector<int>, greater<int>> pq;
```

> ⚠️ Don't forget the space between `>>` in older C++ standards. C++11+ handles it, but `> >` is safer.

</details>

### Core Operations

| Operation | Code | Time |
|-----------|------|------|
| Insert element | `pq.push(x)` | O(log n) |
| Remove top | `pq.pop()` | O(log n) |
| View top | `pq.top()` | O(1) |
| Size | `pq.size()` | O(1) |
| Check if empty | `pq.empty()` | O(1) |

<details>
<summary><b>🧠 Why is push/pop O(log n) and not O(1)?</b></summary>

The priority queue maintains a **heap** structure internally. Every insert and delete requires "bubbling" the element up or down the tree to maintain the heap property. The height of the tree is O(log n), so each operation is O(log n).

</details>

### Example: K Largest Elements

```cpp
// Read N numbers, output the K largest in descending order
int n, k;
cin >> n >> k;
priority_queue<int> pq;
for (int i = 0; i < n; i++) {
    int x; cin >> x;
    pq.push(x);
}
for (int i = 0; i < k; i++) {
    cout << pq.top() << " ";
    pq.pop();
}
// Outputs K largest numbers, from largest to smallest
```

<details>
<summary><b>🧠 What if you want the K *smallest* numbers?</b></summary>

Two approaches:
1. Use a **min-heap**: `priority_queue<int, vector<int>, greater<int>> pq;`
2. Use a max-heap but push **negative** values: `pq.push(-x);` then output `-pq.top()`. This trick works when you only need integers and the default max-heap is convenient.

</details>

<details>
<summary><b>⚠️ Common Pitfall: priority_queue has no iterators</b></summary>

You cannot loop through a priority_queue with a range-based for loop. The only way to access elements is `top()` → `pop()` → `top()` → `pop()`... This **destroys** the queue. If you need to preserve it, copy it first.

</details>

### Practice

<details>
<summary><b>📝 Problem: "Dynamic Median" (warming up to the idea)</b></summary>

Read N numbers one by one. After reading each number, output the current **largest** number seen so far.

<details>
<summary><b>Solution</b></summary>

```cpp
int n; cin >> n;
priority_queue<int> pq;
for (int i = 0; i < n; i++) {
    int x; cin >> x;
    pq.push(x);
    cout << pq.top() << "\n";  // current maximum
}
```

</details>
</details>

---

## 5. `set` — Sorted Unique Elements

### What is it?

A `set` stores a collection of **unique** elements, automatically kept in **sorted order**. Internally, it is a **balanced binary search tree** (usually a red-black tree).

### When to use it?

- Removing duplicates while keeping order: `{5, 2, 5, 1, 2}` → `{1, 2, 5}`
- "Does this element exist?" queries — O(log n)
- Finding the smallest / largest element quickly
- Any time you need a sorted collection with fast insert, delete, and search

### Declaration

```cpp
#include <set>

set<int> s;                         // sorted ascending, unique elements
set<int, greater<int>> s2;          // sorted descending
```

### Core Operations

| Operation | Code | Time |
|-----------|------|------|
| Insert | `s.insert(x)` | O(log n) |
| Remove | `s.erase(x)` | O(log n) |
| Remove by iterator | `s.erase(it)` | O(1) amortized |
| Check if exists | `s.count(x)` — returns 0 or 1 | O(log n) |
| Find element | `s.find(x)` — returns iterator (or `s.end()`) | O(log n) |
| Smallest element | `*s.begin()` | O(1) |
| Largest element | `*s.rbegin()` or `*prev(s.end())` | O(1) |
| Size | `s.size()` | O(1) |

<details>
<summary><b>🧠 What happens if you insert a duplicate?</b></summary>

```cpp
set<int> s;
s.insert(5);
s.insert(5);
s.insert(5);
cout << s.size();  // 1
```

The `insert` operation on a set returns a `pair<iterator, bool>`. The `bool` is `true` if the insertion happened, `false` if the element already existed. Duplicates are silently ignored.

</details>

### Iterating a Set

```cpp
for (int x : s) {
    cout << x << " ";  // elements come out in sorted order
}

// Or with iterators:
for (auto it = s.begin(); it != s.end(); it++) {
    cout << *it << " ";
}
```

### Finding Elements

```cpp
auto it = s.find(42);
if (it != s.end()) {
    cout << "Found: " << *it << "\n";
} else {
    cout << "Not found\n";
}
```

<details>
<summary><b>🧠 When is count() better than find()?</b></summary>

`count(x)` just returns 0 or 1 for a set — it tells you existence but not position. Use it when you only need a yes/no answer.

`find(x)` returns an iterator, so you can then erase it, get its successor, etc. Use it when you need to **do something** with the element.

</details>

### Lower / Upper Bound

This is where `set` really shines:

```cpp
auto it = s.lower_bound(x);  // first element >= x
auto it2 = s.upper_bound(x); // first element > x
```

<details>
<summary><b>📝 Example: "Find the smallest number in the set that is ≥ 7"</b></summary>

```cpp
set<int> s = {1, 3, 5, 8, 10, 15};

auto it = s.lower_bound(7);
if (it != s.end()) {
    cout << *it;  // 8
}
```

</details>

<details>
<summary><b>⚠️ Common Pitfall: using std::lower_bound on a set</b></summary>

```cpp
// SLOW — O(n) for set! std::lower_bound doesn't know the tree structure
auto it = lower_bound(s.begin(), s.end(), x);

// FAST — O(log n). Use the member function.
auto it = s.lower_bound(x);
```

Always use `s.lower_bound(x)`, never `std::lower_bound(s.begin(), s.end(), x)`.

</details>

---

## 6. `multiset` — Like `set`, But Allows Duplicates

### What is it?

Exactly the same as `set` (sorted, tree-based), but **duplicates are allowed**. `{5, 2, 5, 1}` → `{1, 2, 5, 5}`.

### When to use it?

- You need sorted order + duplicates (e.g., maintaining a running list of scores where ties are common)
- "Multiple students can have the same score"

### Key Differences from `set`

| | `set` | `multiset` |
|---|-------|------------|
| Duplicates | ❌ | ✅ |
| `count(x)` | 0 or 1 | Can be > 1 |
| `erase(x)` | Removes the element | Removes **ALL** copies of x |
| `erase(it)` | Removes one element | Removes **one** element (at the iterator) |

<details>
<summary><b>⚠️ Critical Pitfall: erase(x) vs erase(it) in multiset</b></summary>

```cpp
multiset<int> ms = {1, 2, 2, 2, 3};

ms.erase(2);    // Removes ALL three 2s. Now: {1, 3}

// To remove only ONE copy:
auto it = ms.find(2);
if (it != ms.end()) ms.erase(it);  // Removes only one 2
```

This is the #1 source of bugs with `multiset`. Always use `erase(it)` when you want to remove exactly one occurrence.

</details>

### Example: Maintain a Running List of Scores

```cpp
multiset<int> scores;
scores.insert(85);
scores.insert(92);
scores.insert(85);  // duplicate allowed

cout << scores.count(85);  // 2
```

---

## 7. `map` — A Dictionary (Key → Value)

### What is it?

A `map` associates **keys** with **values**. Think of it as a dictionary: you look up a word (key) and find its definition (value). Internally, it's a balanced BST ordered by key.

### When to use it?

- Counting frequencies: "How many times does each number appear?"
- Storing extra information per element: student ID → score
- Any key-value lookup

### Declaration

```cpp
#include <map>

map<string, int> age;            // name → age
map<int, vector<int>> graph;     // node ID → list of neighbors
map<char, int> freq;             // character → frequency
```

### Core Operations

| Operation | Code | Time |
|-----------|------|------|
| Insert / Update | `m[key] = value` | O(log n) |
| Access | `m[key]` | O(log n) |
| Check if key exists | `m.count(key)` or `m.find(key)` | O(log n) |
| Remove | `m.erase(key)` | O(log n) |
| Size | `m.size()` | O(1) |

### The Magic of `m[key]`

<details>
<summary><b>🧠 What happens when you access m[key] and the key doesn't exist yet?</b></summary>

```cpp
map<string, int> m;
cout << m["alice"];  // 0 — it AUTO-CREATES the key with default value!
```

`m["alice"]` creates the entry `"alice" → 0` if it doesn't exist. This is **very useful** for counting:

```cpp
map<int, int> freq;
for (int x : arr) {
    freq[x]++;  // works even on first occurrence — starts at 0 then ++
}
```

But it can also be a bug if you just want to check existence. Use `m.count(key)` for that.

</details>

### Iterating a Map

```cpp
for (auto &p : m) {
    cout << p.first << " → " << p.second << "\n";
}

// With structured bindings (C++17):
for (auto &[key, value] : m) {
    cout << key << " → " << value << "\n";
}
```

Keys come out in **sorted order** (by default, ascending).

### Example: Word Frequency Counter

```cpp
map<string, int> freq;
string word;
while (cin >> word) {
    freq[word]++;
}

// Output words in alphabetical order with their frequencies
for (auto &[word, count] : freq) {
    cout << word << ": " << count << "\n";
}
```

<details>
<summary><b>🧠 What if I don't need sorted order? Is there a faster map?</b></summary>

Yes! `unordered_map` gives you O(1) average access instead of O(log n), but keys are **not sorted**. Use it when you only need key-value lookup and don't care about order.

```cpp
#include <unordered_map>
unordered_map<string, int> m;  // hash table, O(1) average
```

Trade-off: `unordered_map` can be slower in the worst case (hash collisions) and uses more memory. For competitive programming, `map` is often the safer default unless you have a specific reason to use `unordered_map`.

</details>

<details>
<summary><b>⚠️ Common Pitfall: m.at(key) vs m[key]</b></summary>

- `m[key]` — creates the key if it doesn't exist
- `m.at(key)` — throws `std::out_of_range` if key doesn't exist (safer for debugging)

When you're reading from a map and don't want accidental insertions, use `.at()`.

</details>

---

## 🎯 Cheat Sheet: Choosing the Right Container

| I want to... | Use | Why |
|-------------|------|-----|
| Store a list, access by index | `vector` | O(1) random access |
| Add/remove only at the top | `stack` | LIFO, simple |
| Process in arrival order | `queue` | FIFO, simple |
| Always get the largest/smallest | `priority_queue` | Heap, O(log n) insert/pop |
| Unique + sorted elements | `set` | Balanced BST |
| Sorted elements, duplicates OK | `multiset` | Like set but allows copies |
| Key → value lookup, sorted by key | `map` | Balanced BST, O(log n) |
| Key → value, order doesn't matter | `unordered_map` | Hash table, O(1) avg |

---

## 📝 Final Practice Problems

Try these on your own. The vjudge contest link will be in the CCA group.

<details>
<summary><b>P1: Unique Sorted Output</b></summary>
Read N numbers. Output them sorted, each number only once.
<br><br>
<details><summary><b>Hint</b></summary>Insert all into a `set`, then iterate.</details>
</details>

<details>
<summary><b>P2: Balanced Brackets (Extended)</b></summary>
Check if a string of `()[]{}` is balanced. `([{}])` ✅, `([)]` ❌
<br><br>
<details><summary><b>Hint</b></summary>Use a `stack<char>`. When you see a closing bracket, check if it matches the top.</details>
</details>

<details>
<summary><b>P3: K-th Smallest Element</b></summary>
Read N numbers, then Q queries. Each query is a number K — output the K-th smallest element among all numbers seen so far. Numbers are added one by one between queries.
<br><br>
<details><summary><b>Hint</b></summary>Could a `multiset` help? What if you maintain an iterator to the "current K-th" element?</details>
</details>

<details>
<summary><b>P4: Frequency Sort</b></summary>
Read N numbers. Output them sorted by frequency (descending). If two numbers have the same frequency, the smaller number comes first.
<br><br>
<details><summary><b>Hint</b></summary>Use a `map<int, int>` for frequency, then think about how to sort by a custom rule.</details>
</details>

---

## ✅ Self-Check

Before moving on, make sure you can:

- [ ] Declare and use `vector`, `stack`, `queue`, `priority_queue`, `set`, `multiset`, `map`
- [ ] Explain the difference between LIFO (stack) and FIFO (queue)
- [ ] Explain why `priority_queue` push/pop is O(log n)
- [ ] Use `lower_bound` / `upper_bound` on a `set`
- [ ] Avoid the `erase(x)` pitfall in `multiset`
- [ ] Use `m[key]` for counting in a `map`
- [ ] Choose the right container for a given problem
