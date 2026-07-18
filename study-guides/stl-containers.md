# C++ STL Containers: Your First Toolbox

> **Prerequisites:** You know how to write a `for` loop, declare variables, and use `cin`/`cout`.  
> **Goal:** By the end of this guide, you'll know which container to reach for — and why.

---

## 📦 What is the STL?

STL = **Standard Template Library**. It's a toolbox that comes pre-installed with C++. Instead of writing everything from scratch, you use the tools already in the box. They are fast, well-tested, and used by competitive programmers worldwide.

All STL containers live under `#include` headers. For this guide, you'll need:

```cpp
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
```

---

## 1. `vector` — The Dynamic Array

### What is it?

A normal C++ array has a fixed size that you must declare in advance:

```cpp
int arr[100];  // must know the size upfront. What if you need 101 elements? 💥
```

A `vector` solves this. It's an array that **grows and shrinks automatically**. You can start with an empty vector, then keep adding elements, and it will resize itself as needed. The elements are stored side-by-side in memory (just like a normal array), so accessing any element by its index is instant.

Think of it like a **magic backpack**: you keep throwing things in, and it stretches to fit them. But you can still instantly grab the 3rd item you put in.

### Operations — Explained One by One

---

#### `v.push_back(x)` — "Add this to the end"

You have a vector `{1, 2, 3}`. You call `v.push_back(4)`. Now it's `{1, 2, 3, 4}`.

The new element is glued to the end. This is the most common way to build a vector when you don't know how many elements you'll have in advance.

```cpp
vector<int> v;
v.push_back(10);
v.push_back(20);
v.push_back(30);
// v is now {10, 20, 30}
```

> **Time:** O(1). Occasionally the vector needs to move to a bigger memory block, but on average it's constant. We call this "amortized O(1)."

---

#### `v.pop_back()` — "Remove the last element"

The reverse of `push_back`. Removes the last element. No return value — it just makes the vector one element shorter.

```cpp
v = {10, 20, 30};
v.pop_back();
// v is now {10, 20}
```

> **Time:** O(1). Always fast — just chops off the end.

---

#### `v[i]` — "Give me the element at position i"

Same as accessing a normal array. The first element is at index 0, not 1.

```cpp
vector<int> v = {10, 20, 30};
cout << v[0];  // 10
cout << v[2];  // 30
```

> **Time:** O(1). Direct memory access — no searching needed.

There's also `v.at(i)`, which does the same thing but checks if `i` is valid. If `i` is out of bounds, `v.at(i)` throws an error instead of silently crashing. Use `v[i]` for speed in contests, `v.at(i)` for debugging.

---

#### `v.front()` and `v.back()` — "First and last element"

```cpp
vector<int> v = {10, 20, 30};
cout << v.front();  // 10
cout << v.back();   // 30
```

Use these when you specifically need the very first or very last element. More readable than `v[0]` and `v[v.size() - 1]`.

> **Time:** O(1).

---

#### `v.size()` — "How many elements are in here?"

Returns the current number of elements. Not the capacity (which is how much memory is reserved), but the actual count of things you've put in.

```cpp
vector<int> v = {10, 20, 30};
cout << v.size();  // 3
```

> **Time:** O(1).

---

#### `v.empty()` — "Is it empty?"

Returns `true` if `v.size() == 0`, `false` otherwise. A cleaner way to check than `v.size() == 0`.

```cpp
if (v.empty()) {
    cout << "Nothing here!";
}
```

> **Time:** O(1).

---

#### `v.clear()` — "Remove everything"

Empties the entire vector. After calling it, `v.size()` becomes 0 and `v.empty()` returns `true`.

```cpp
v = {1, 2, 3, 4, 5};
v.clear();
cout << v.size();  // 0
```

> **Time:** O(n) — it has to destroy each element.

---

### Creating a Vector: All the Ways

```cpp
vector<int> v;                  // empty
vector<int> v(10);              // 10 elements, all 0
vector<int> v(10, 5);           // 10 elements, all 5
vector<int> v = {1, 2, 3, 4};   // 1, 2, 3, 4
vector<int> v2(v);              // copy of v
```

The constructor `vector<int> v(10, 5)` reads as: "Make a vector of 10 ints, and set all of them to 5."

---

### Iterating Through a Vector

```cpp
// Method 1: index loop (you control the position)
for (int i = 0; i < v.size(); i++) {
    cout << v[i] << " ";
}

// Method 2: range-based for (clean, when you don't need the index)
for (int x : v) {
    cout << x << " ";
}
```

---

### Sorting a Vector

```cpp
#include <algorithm>

sort(v.begin(), v.end());                        // ascending: 1, 2, 3
sort(v.begin(), v.end(), greater<int>());         // descending: 3, 2, 1
sort(v.begin(), v.begin() + 5);                   // sort only first 5 elements
```

`v.begin()` is like a pointer to the first element. `v.end()` points to the position **after** the last element. `sort` rearranges everything between these two pointers.

---

### ⚠️ Common Pitfall: Out-of-Bounds Access

```cpp
vector<int> v = {1, 2, 3};
cout << v[5];        // 💥 UNDEFINED BEHAVIOR — v only has indices 0, 1, 2
cout << v.at(5);     // throws std::out_of_range — safer for debugging
```

Always make sure `i < v.size()` before accessing `v[i]`.

---

### ⚠️ Common Pitfall: Iterator Invalidation

If you `push_back` and the vector runs out of reserved space, it moves to a new memory location. Any pointers or iterators you saved earlier become dangling — they now point to freed memory. However, if you access via indices (`v[i]`), you're always safe because the vector handles the internal pointer update.

---

### Practice

#### 📝 Problem 1: Read N numbers, output them in reverse order

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
<summary><b>💡 Hint</b></summary>

Read all numbers into a vector. Then loop from the last index (`n-1`) down to `0`.

</details>

<details>
<summary><b>✅ Solution</b></summary>

```cpp
int n;
cin >> n;
vector<int> v(n);
for (int i = 0; i < n; i++) cin >> v[i];
for (int i = n - 1; i >= 0; i--) cout << v[i] << " ";
```

</details>

---

## 2. `stack` — Last In, First Out (LIFO)

### What is it?

Imagine a stack of plates. You can only:
- Put a plate on **top** of the stack
- Take a plate from the **top** of the stack

You can't pull a plate from the middle, and you can't add a plate to the bottom. The **last plate you put on is the first one you take off**.

This is called **LIFO**: Last In, First Out.

### When to use it?

- Checking if parentheses are balanced: `((()))` ✅ vs `(()` ❌
- Undo functionality (Ctrl+Z) — the most recent action is undone first
- Depth-First Search (DFS) — explore the most recently discovered path first
- Evaluating expressions

### Operations — Explained One by One

---

#### `s.push(x)` — "Put this on top of the stack"

Places the element on the top. If the stack was `[bottom → 1, 2, 3 ← top]` and you `push(4)`, it becomes `[1, 2, 3, 4]`.

```cpp
stack<int> s;
s.push(10);
s.push(20);
s.push(30);
// stack (viewed from top): 30, 20, 10
```

> **Time:** O(1). Just attaches to the top.

---

#### `s.top()` — "What's on top?"

Returns the top element **without removing it**. You're just peeking.

```cpp
stack<int> s;
s.push(10);
s.push(20);
cout << s.top();  // 20 — the most recently pushed element
// stack is still: 20, 10 (unchanged)
```

> **Time:** O(1).

---

#### `s.pop()` — "Remove the top element"

Removes the top element. **It does NOT return the value.** If you need the value, call `s.top()` first, then `s.pop()`.

```cpp
s.push(10);
s.push(20);
int x = s.top();  // x = 20
s.pop();          // now top is 10
```

> **Time:** O(1).

---

#### `s.size()` — "How many elements?"

Returns the number of elements currently in the stack.

```cpp
cout << s.size();  // e.g., 3
```

> **Time:** O(1).

---

#### `s.empty()` — "Is it empty?"

Returns `true` if the stack has zero elements. **Always check this before calling `top()` or `pop()`.**

```cpp
if (!s.empty()) {
    cout << s.top();
}
```

> **Time:** O(1).

---

### ⚠️ Fatal Pitfall: `top()` or `pop()` on an Empty Stack

```cpp
stack<int> s;
s.pop();   // 💥 UNDEFINED BEHAVIOR — the stack is empty!
s.top();   // 💥 Same thing — there's nothing to look at
```

**Never** call `top()` or `pop()` without first checking `!s.empty()`. This is the #1 stack bug.

---

### Full Example: Balanced Parentheses

```cpp
#include <stack>
#include <string>

bool isBalanced(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(') {
            st.push(c);
        } else {  // c == ')'
            if (st.empty()) return false;  // no matching '(' left
            st.pop();
        }
    }
    return st.empty();  // balanced only if nothing left unmatched
}
```

Let's trace through `"(()())"` step by step:

| Step | Char | Stack (bottom→top) | What happens |
|------|------|---------------------|--------------|
| 1 | `(` | `[ ( ]` | push |
| 2 | `(` | `[ (, ( ]` | push |
| 3 | `)` | `[ ( ]` | pop — matches the last `(` |
| 4 | `(` | `[ (, ( ]` | push |
| 5 | `)` | `[ ( ]` | pop |
| 6 | `)` | `[ ]` | pop — stack now empty |

Final stack is empty → balanced! ✅

---

### Practice

#### 📝 Problem 2: Balanced Brackets (Extended)

Check if a string containing `()`, `[]`, and `{}` is balanced.

- `([{}])` ✅
- `([)]` ❌
- `((` ❌

<details>
<summary><b>💡 Hint</b></summary>

When you see a closing bracket (`)`, `]`, or `}`), it must match the **most recently opened** bracket. That's exactly what a stack gives you — the top of the stack is the most recent opening bracket.

</details>

<details>
<summary><b>✅ Solution</b></summary>

```cpp
bool isBalanced(string s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') {
            st.push(c);
        } else {
            if (st.empty()) return false;
            char top = st.top();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}
```

</details>

---

## 3. `queue` — First In, First Out (FIFO)

### What is it?

Imagine a line of people at a ticket counter. The **first person to arrive is the first person served**. New people join at the back of the line.

This is called **FIFO**: First In, First Out.

A queue has two ends:
- **Front**: where elements leave (the person being served)
- **Back**: where elements enter (new arrivals join here)

### Stack vs Queue — Mental Picture

| | Stack | Queue |
|------|-------|-------|
| Principle | LIFO | FIFO |
| Like... | A pile of plates | A line of people |
| Add | `push()` → top | `push()` → back |
| Remove | `pop()` → top | `pop()` → front |
| View | `top()` only | `front()` (first) and `back()` (last) |

### When to use it?

- Breadth-First Search (BFS) — explore nodes in order of discovery
- Simulating a waiting line
- Processing tasks in the order they arrived

### Operations — Explained One by One

---

#### `q.push(x)` — "Join the back of the line"

Adds an element to the **back** of the queue.

```cpp
queue<int> q;
q.push(10);  // queue: [10]
q.push(20);  // queue: [10, 20]
q.push(30);  // queue: [10, 20, 30]
```

> **Time:** O(1).

---

#### `q.front()` — "Who's at the front of the line?"

Returns the element at the **front** — the one that's been waiting the longest. Does not remove it.

```cpp
cout << q.front();  // 10 (first one in)
```

> **Time:** O(1).

---

#### `q.back()` — "Who just joined at the back?"

Returns the element at the **back** — the most recently added one.

```cpp
cout << q.back();  // 30 (last one in)
```

> **Time:** O(1).

---

#### `q.pop()` — "Serve the person at the front"

Removes the front element. Like `stack::pop()`, it does **not** return the value.

```cpp
q.pop();  // removes 10. Queue becomes [20, 30]
cout << q.front();  // 20
```

> **Time:** O(1).

---

#### `q.size()` and `q.empty()`

Same as stack. `size()` returns the count, `empty()` returns `true` if the queue is empty.

> **Time:** O(1).

---

### ⚠️ Fatal Pitfall: Same as Stack

Never call `front()`, `back()`, or `pop()` on an empty queue. Always check `!q.empty()` first.

---

### Full Example: Simple Queue Simulation

```cpp
queue<int> q;
q.push(1);
q.push(2);
q.push(3);

while (!q.empty()) {
    cout << q.front() << " ";  // 1 2 3
    q.pop();
}
```

Outputs `1 2 3` — first in, first out.

---

### Practice

#### 📝 Problem 3: Simulate a Queue of Students

N students arrive one by one (given by their IDs). Then you serve M students (remove from front). Output the IDs of the served students.

**Input:**
```
5 3
1 2 3 4 5
```
(N=5, M=3, IDs: 1 through 5)

**Output:**
```
1
2
3
```

<details>
<summary><b>💡 Hint</b></summary>

Push all N IDs into a queue. Then loop M times: print `front()`, then `pop()`.

</details>

<details>
<summary><b>✅ Solution</b></summary>

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

---

## 4. `priority_queue` — Always Grab the Most Important One

### What is it?

A `priority_queue` is like a queue, but instead of "first come, first served", the **most important element comes out first**. By default, "most important" means **largest value**.

Behind the scenes, it maintains a **heap** — a clever tree structure where the largest element is always at the root, ready to be served. Whenever you add or remove an element, the tree rearranges itself to keep the largest on top.

### When to use it?

- "What's the current maximum?" — answered instantly
- Finding K largest elements
- Dijkstra's algorithm (shortest path)
- Any time you need repeated access to the max/min

### Operations — Explained One by One

---

#### `pq.push(x)` — "Insert this, and keep the largest on top"

Adds an element. The heap rearranges itself so `top()` still returns the maximum.

```cpp
priority_queue<int> pq;
pq.push(5);   // pq contains: {5}
pq.push(9);   // pq contains: {9, 5} — 9 is on top
pq.push(2);   // pq contains: {9, 5, 2} — 9 still on top
```

> **Time:** O(log n). The element may need to "bubble up" through the tree.

---

#### `pq.top()` — "What's the current maximum?"

Returns the largest element (in a default max-heap). Does not remove it.

```cpp
cout << pq.top();  // 9
```

> **Time:** O(1). The largest is always ready at the root.

---

#### `pq.pop()` — "Remove the largest element"

Removes the top (maximum) element. The heap rearranges so the next largest becomes the new top.

```cpp
pq.pop();         // removes 9
cout << pq.top(); // 5 — the next largest
```

> **Time:** O(log n). The new element may need to "sink down" through the tree.

---

#### `pq.size()` and `pq.empty()`

Same as other containers. Check emptiness before `top()` or `pop()`.

> **Time:** O(1).

---

### Creating a Min-Heap

By default, `priority_queue` is a **max-heap** (largest on top). To make it a **min-heap** (smallest on top), you need a special declaration:

```cpp
// Min-heap: smallest on top
priority_queue<int, vector<int>, greater<int>> pq;
```

The full template is `priority_queue<Type, Container, Comparator>`. `vector<int>` is the underlying storage (required), and `greater<int>` flips the comparison to make it a min-heap.

**Mental shortcut to remember:**
- Default → `priority_queue<int>` → largest on top → like `sort(v.rbegin(), v.rend())`
- Min-heap → add `vector<int>, greater<int>` → smallest on top → like `sort(v.begin(), v.end())`

---

### ⚠️ Two Important Limitations

**1. No iteration allowed.** You can only access the top element. There's no way to loop through a priority_queue with a for-each loop. The only way to see all elements is to repeatedly `top()` → `pop()` → `top()` → ..., which **destroys** the queue. Copy it first if you need to preserve it.

**2. No `find` or membership check.** If you want to search for a specific value, you need a different container. Priority queue only cares about the top.

---

### Example: K Largest Numbers

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
```

---

### Practice

#### 📝 Problem 4: Dynamic Maximum

Read N numbers one by one. After reading each number, output the **largest number seen so far**.

<details>
<summary><b>💡 Hint</b></summary>

Push each number into a max-heap. `top()` always gives the current maximum.

</details>

<details>
<summary><b>✅ Solution</b></summary>

```cpp
int n; cin >> n;
priority_queue<int> pq;
for (int i = 0; i < n; i++) {
    int x; cin >> x;
    pq.push(x);
    cout << pq.top() << "\n";
}
```

</details>

---

## 5. `set` — Sorted, No Duplicates

### What is it?

A `set` is a collection where:
1. Every element is **unique** (no duplicates)
2. Elements are automatically kept in **sorted order**

Behind the scenes, it's a **balanced binary search tree** (a red-black tree). This means insertion, deletion, and search are all O(log n).

Think of it like a **phone book that auto-sorts itself**. You throw in names in any order, and it always stays alphabetized. If you try to add the same name twice, it says "already got that one" and ignores it.

### When to use it?

- Remove duplicates **and** get sorted output: `{5, 2, 5, 1}` → `{1, 2, 5}`
- "Does this element exist?" — answered in O(log n)
- Find the smallest/largest element instantly
- Find the first element ≥ some value (lower_bound)

### Operations — Explained One by One

---

#### `s.insert(x)` — "Add this, but only if it's not already there"

Inserts the element. If it already exists, nothing happens.

```cpp
set<int> s;
s.insert(5);  // s = {5}
s.insert(2);  // s = {2, 5}
s.insert(5);  // s = {2, 5} — the second 5 is ignored
s.insert(1);  // s = {1, 2, 5}
```

`insert` returns a `pair<iterator, bool>`. The `bool` is `true` if insertion happened, `false` if the element was already present. You usually don't need this return value, but it's good to know.

> **Time:** O(log n). The tree needs to find the right spot.

---

#### `s.erase(x)` — "Remove this element"

Removes the specified value. If it doesn't exist, nothing happens.

```cpp
s = {1, 2, 5};
s.erase(2);  // s = {1, 5}
s.erase(99); // s = {1, 5} — 99 wasn't there, no error
```

> **Time:** O(log n).

---

#### `s.erase(it)` — "Remove the element at this position"

If you have an iterator pointing to a specific element, you can remove it directly. This is O(1) amortized if you already have the iterator.

```cpp
auto it = s.find(5);
if (it != s.end()) s.erase(it);
```

> **Time:** O(1) amortized.

---

#### `s.find(x)` — "Where is this element?"

Returns an **iterator** pointing to the element. If the element isn't in the set, it returns `s.end()` (a special marker meaning "not found").

```cpp
auto it = s.find(42);
if (it != s.end()) {
    cout << "Found: " << *it << "\n";  // *it dereferences the iterator
} else {
    cout << "Not found\n";
}
```

> **Time:** O(log n).

---

#### `s.count(x)` — "Is this element in the set?"

Returns `1` if it exists, `0` if it doesn't. For a `set`, it can never return more than `1` (unlike `multiset`).

```cpp
if (s.count(42)) {
    cout << "Exists!";
}
```

Use `count()` when you just need a yes/no answer. Use `find()` when you need to then do something with the element (like erase it or get its neighbors).

> **Time:** O(log n).

---

#### `*s.begin()` — "Smallest element"

`begin()` returns an iterator to the first (smallest) element. The `*` dereferences the iterator to get the value.

```cpp
s = {5, 2, 8, 1};
cout << *s.begin();  // 1 — the smallest
```

> **Time:** O(1).

---

#### `*s.rbegin()` — "Largest element"

`rbegin()` is "reverse begin" — it points to the last (largest) element.

```cpp
cout << *s.rbegin();  // 8 — the largest
```

Alternatively: `*prev(s.end())`. `s.end()` points past the last element, and `prev()` steps back one.

> **Time:** O(1).

---

#### `s.lower_bound(x)` — "First element that is ≥ x"

This is one of the most powerful set operations. Given a value `x`, it finds the **smallest element in the set that is ≥ x**.

```cpp
set<int> s = {1, 3, 5, 8, 10, 15};

auto it = s.lower_bound(7);
cout << *it;  // 8 — the first element ≥ 7

it = s.lower_bound(5);
cout << *it;  // 5 — 5 itself is ≥ 5
```

If no such element exists, it returns `s.end()`.

> **Time:** O(log n).

---

#### `s.upper_bound(x)` — "First element that is > x"

Like `lower_bound`, but strictly greater (not equal to x).

```cpp
auto it = s.upper_bound(5);
cout << *it;  // 8 — the first element strictly > 5
```

> **Time:** O(log n).

---

### ⚠️ Critical Pitfall: Don't Use `std::lower_bound` on a Set

```cpp
// WRONG — O(n)! It walks through the tree linearly.
auto it = lower_bound(s.begin(), s.end(), x);

// RIGHT — O(log n). Uses the tree structure properly.
auto it = s.lower_bound(x);
```

Always use the **member function** `s.lower_bound(x)`, never the free function `std::lower_bound`. The free function doesn't know it's dealing with a tree and falls back to a slow linear scan.

---

### Iterating Through a Set

Elements come out in **sorted order** automatically:

```cpp
set<int> s = {5, 1, 8, 3};

for (int x : s) {
    cout << x << " ";  // 1 3 5 8 — always sorted!
}
```

---

### Practice

#### 📝 Problem 5: Unique Sorted Output

Read N numbers. Output them sorted, each number appearing only once (remove duplicates).

<details>
<summary><b>💡 Hint</b></summary>

Insert all numbers into a `set<int>`. The set automatically removes duplicates and keeps them sorted. Then iterate and print.

</details>

<details>
<summary><b>✅ Solution</b></summary>

```cpp
int n; cin >> n;
set<int> s;
for (int i = 0; i < n; i++) {
    int x; cin >> x;
    s.insert(x);
}
for (int x : s) {
    cout << x << " ";
}
```

</details>

---

## 6. `multiset` — Like `set`, But Allows Duplicates

### What is it?

Exactly the same as `set` (sorted, tree-based, O(log n) operations), with one difference: **duplicates are allowed**.

```cpp
multiset<int> ms;
ms.insert(5);
ms.insert(2);
ms.insert(5);  // allowed — ms = {2, 5, 5}
```

### When to use it?

- You need sorted order **and** duplicates
- Maintaining a running list of scores where ties are common
- Finding the K-th smallest/biggest in a dynamic collection

### Operations — Differences from `set`

All operations are the same as `set`, with these critical differences:

---

#### `ms.count(x)` — can return > 1

In `set`, `count(x)` is always 0 or 1. In `multiset`, it can be any number.

```cpp
multiset<int> ms = {2, 5, 5, 5, 8};
cout << ms.count(5);  // 3
```

> **Time:** O(log n + k) where k is the count. It has to find the first occurrence, then count.

---

#### `ms.erase(x)` — removes ALL copies in one go

This is the **#1 source of multiset bugs**.

```cpp
multiset<int> ms = {1, 2, 2, 2, 3};

ms.erase(2);  
// ms is now {1, 3} — ALL THREE 2's are gone!
```

If you want to remove **only one** occurrence, you must:

1. Find it with `find()` to get an iterator
2. Erase the iterator

```cpp
ms = {1, 2, 2, 2, 3};

auto it = ms.find(2);  // points to the first 2
if (it != ms.end()) ms.erase(it);
// ms is now {1, 2, 2, 3} — only ONE 2 removed
```

> **Mental rule:** `erase(value)` = delete all. `erase(iterator)` = delete one.

---

#### `ms.find(x)` — returns an iterator to the first occurrence

If there are multiple copies, `find()` points to the first one (the smallest, since elements are sorted).

---

### Practice

#### 📝 Problem 6: Dynamic Scores

Scores are added during a contest. After each addition, output the **current highest score**.

<details>
<summary><b>💡 Hint</b></summary>

Use a `multiset`. `*ms.rbegin()` gives the largest element. Or use `*prev(ms.end())`.

</details>

<details>
<summary><b>✅ Solution</b></summary>

```cpp
multiset<int> scores;
int q; cin >> q;
while (q--) {
    int score; cin >> score;
    scores.insert(score);
    cout << *scores.rbegin() << "\n";
}
```

</details>

---

## 7. `map` — A Dictionary (Key → Value)

### What is it?

A `map` pairs **keys** with **values**. You give it a key, it gives you back the associated value — like looking up a word in a dictionary.

Behind the scenes, it's the same balanced BST as `set`, but each node stores a `(key, value)` pair, ordered by key.

### When to use it?

- **Counting frequencies**: "How many times did each word appear?"
- **Storing extra data per ID**: student ID → test score
- **Building a graph**: node number → list of neighbors
- Any time you need a lookup table that stays sorted by key

### Operations — Explained One by One

---

#### `m[key] = value` — "Associate this key with this value"

Sets or updates the value for a given key. If the key already exists, the old value is overwritten. If not, a new entry is created.

```cpp
map<string, int> age;
age["Alice"] = 17;
age["Bob"] = 16;
age["Alice"] = 18;  // overwrites 17 → 18
```

> **Time:** O(log n).

---

#### `m[key]` — "What value is associated with this key?"

Returns the value. **But there's a catch**: if the key doesn't exist yet, `m[key]` **creates it automatically** with a default value (0 for int, empty string, etc.).

```cpp
map<string, int> m;
cout << m["Charlie"];  // 0 — Charlie was created with default value!

// This is SUPER USEFUL for counting:
map<int, int> freq;
for (int x : arr) {
    freq[x]++;  // works even the first time — starts at 0, then ++
}
```

> **Time:** O(log n).

---

#### `m.at(key)` — "Give me the value, but don't create if missing"

Like `m[key]` but **does not create** the key. If the key doesn't exist, it throws an error.

```cpp
map<string, int> m;
m["Alice"] = 17;
cout << m.at("Alice");   // 17
cout << m.at("Bob");     // throws std::out_of_range
```

> Use `m.at()` when you're reading and want to catch bugs. Use `m[key]` when you're building/updating.

---

#### `m.count(key)` — "Does this key exist?"

Returns `1` if the key exists, `0` if not. Unlike `m[key]`, it does **not** create the key.

```cpp
if (m.count("Alice")) {
    cout << "Alice is in the map";
}
```

> **Time:** O(log n). This is the safe way to check existence.

---

#### `m.find(key)` — "Where is this key?"

Returns an iterator to the `(key, value)` pair. If not found, returns `m.end()`.

```cpp
auto it = m.find("Alice");
if (it != m.end()) {
    cout << it->first << " → " << it->second << "\n";
    //        key                  value
}
```

> **Time:** O(log n). Use `find()` when you need the value AND want to avoid accidental creation.

---

#### `m.erase(key)` — "Remove this entry"

Deletes the key and its associated value. If the key doesn't exist, nothing happens.

```cpp
m.erase("Alice");  // Alice is gone
```

> **Time:** O(log n).

---

#### `m.size()` and `m.empty()`

Standard. `size()` returns the number of key-value pairs.

> **Time:** O(1).

---

### Iterating Through a Map

Keys come out in **sorted order** (ascending by default):

```cpp
map<string, int> age;
age["Charlie"] = 18;
age["Alice"] = 17;
age["Bob"] = 16;

// Method 1: classic
for (auto &p : age) {
    cout << p.first << " is " << p.second << "\n";
}
// Output:
// Alice is 17
// Bob is 16
// Charlie is 18

// Method 2: structured binding (C++17, cleaner)
for (auto &[name, years] : age) {
    cout << name << " is " << years << "\n";
}
```

---

### Example: Word Frequency Counter

```cpp
map<string, int> freq;
string word;
while (cin >> word) {
    freq[word]++;
}

// Output in alphabetical order
for (auto &[word, count] : freq) {
    cout << word << ": " << count << "\n";
}
```

Each time `freq[word]++` runs:
- If `word` is new → `freq[word]` auto-creates the entry with value 0, then `++` makes it 1
- If `word` already exists → `freq[word]` returns current count, `++` increments it

---

### What About `unordered_map`?

If you don't need sorted keys and just want fast lookup, `unordered_map` gives O(1) average access using a hash table:

```cpp
#include <unordered_map>
unordered_map<string, int> m;  // hash table, O(1) average
```

Trade-off: no sorted iteration, potentially slower worst-case (hash collisions), more memory. For beginners, start with `map` and switch to `unordered_map` only if you have a performance reason.

---

### Practice

#### 📝 Problem 7: Most Frequent Number

Read N integers. Output the number that appears **most frequently**. If there's a tie, output the **smallest** number.

<details>
<summary><b>💡 Hint</b></summary>

Step 1: Use a `map<int, int>` to count frequencies.  
Step 2: Iterate through the map. Since keys are in sorted order, you automatically break ties by choosing the first (smallest) one that ties for max frequency.

</details>

<details>
<summary><b>✅ Solution</b></summary>

```cpp
int n; cin >> n;
map<int, int> freq;
for (int i = 0; i < n; i++) {
    int x; cin >> x;
    freq[x]++;
}

int maxFreq = 0;
int answer = 0;
for (auto &[num, cnt] : freq) {
    if (cnt > maxFreq) {
        maxFreq = cnt;
        answer = num;
    }
    // No need for tie-breaking logic: since map iterates
    // in sorted order, we naturally pick the smallest key
    // when frequencies are equal.
}
cout << answer;
```

</details>

---

## 🎯 Quick Reference: Choosing the Right Container

| I want to... | Use | Why |
|-------------|------|-----|
| Store a list, access by position | `vector` | O(1) random access, grows automatically |
| Add/remove only at the top | `stack` | LIFO, simple and fast |
| Process in arrival order | `queue` | FIFO, simple and fast |
| Always get the largest element | `priority_queue` (default) | Heap, O(log n) per push/pop |
| Always get the smallest element | `priority_queue` (min-heap) | Min-heap, O(log n) per push/pop |
| Unique + sorted elements | `set` | Balanced BST |
| Sorted elements, duplicates OK | `multiset` | Like set but allows copies |
| Key → value, sorted by key | `map` | Balanced BST, O(log n) |
| Key → value, order doesn't matter | `unordered_map` | Hash table, O(1) average |

---

## 📝 More Practice Problems

<details>
<summary><b>P8: K-th Smallest in a Stream</b></summary>

Read N numbers. After each number, Q queries ask for the K-th smallest element seen so far.

<details>
<summary><b>💡 Hint</b></summary>

A `multiset` and an iterator tracking the "current K-th" element can work. Or consider using two priority queues — a max-heap for the K smallest elements and a min-heap for the rest.

</details>
</details>

<details>
<summary><b>P9: Frequency Sort</b></summary>

Read N numbers. Sort them by frequency (most frequent first). If frequencies tie, output the smaller number first.

<details>
<summary><b>💡 Hint</b></summary>

Step 1: `map<int, int>` for frequency. Step 2: put the pairs into a `vector` and write a custom comparator for `sort`.

</details>
</details>

---

## ✅ Self-Check

Before moving on, make sure you can:

- [ ] Declare and use `vector`, `stack`, `queue`, `priority_queue`, `set`, `multiset`, `map`
- [ ] Explain the difference between LIFO (stack) and FIFO (queue) in your own words
- [ ] Explain why `priority_queue::push` and `pop` are O(log n)
- [ ] Use `lower_bound` / `upper_bound` correctly on a `set`
- [ ] Call `erase(it)` instead of `erase(x)` when removing one copy from a `multiset`
- [ ] Use `m[key]++` for counting in a `map`, and know when to use `m.count()` instead
- [ ] Look at a problem and pick the right container without hesitation
