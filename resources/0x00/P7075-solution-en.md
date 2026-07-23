# Solution: P7075 [CSP-S2020] Julian Day

> Source code: `P7075-JulianDay.cpp`

---

There are many ways to approach this problem. This editorial focuses only on the method used in my code.

## Hint 1

The counting starts from **noon** on January 1, 4713 BC. This means that "0 days elapsed" still leaves us at that noon. What convenience do we gain by adding 1 to the input $d$?

<details>
<summary>Click to expand</summary>

This converts "days elapsed" into a 1-based day index starting from day 1 (January 1). All subsequent integer division and modulo operations then map naturally to year/month/day, without needing to separately handle the "noon" boundary.

Example: input $d = 0$ → `date = 1` → represents January 1, 4713 BC.

</details>

---

## Hint 2

There are two calendar transitions in history:

- **Julian calendar**: leap year every 4 years (the same mathematical rule is applied to BC years).
- **Gregorian calendar**: after October 4, 1582, 10 days are skipped (Oct 5–14 do not exist), and the leap year rule changes to "divisible by 4 but not by 100, or divisible by 400".

How can we divide the timeline into intervals for piecewise handling?

<details>
<summary>Click to expand</summary>

We split dates into three segments:

1. **BC era**: from day 1 to $4712 \times 365 + (4712/4) \times 1 + 366$ days (covering all days from 4713 BC to 1 BC). This segment uses the **Julian calendar**, and the year is output with the `BC` suffix.
2. **AD 1 ~ October 4, 1582**: Julian calendar, standard 4-year leap cycle.
3. **October 15, 1582 and later**: Gregorian calendar. We need to compensate for the missing 10 days and subtract the extra Julian leap days (years divisible by 100 but not 400 are not leap years in the Gregorian system).

Determine which segment `date` falls into, then call the corresponding `getans()`.

</details>

---

## Hint 3

If $d$ can be as large as $10^9$, the corresponding year can reach millions. Iterating year by year would TLE. What **cyclic patterns** do the Julian and Gregorian calendars have that we can exploit?

<details>
<summary>Click to expand</summary>

- **Julian calendar**: every **4 years** is a complete cycle, containing 1 leap year + 3 common years, totaling $366 + 365 \times 3 = 1461$ days.
- **Gregorian calendar**: every **400 years** is a complete grand cycle, containing $400/4 - 400/100 + 400/400 = 97$ leap years, totaling $365 \times 400 + 97 = 146097$ days.

Algorithm:
- Use `(n-1) / cycle_days` to quickly skip whole cycles, subtract the corresponding days from `n`.
- Within the remaining incomplete cycle, iterate year by year, then month by month, to get the exact date.

This reduces each query to $O(\text{years in cycle})$, i.e., $O(4)$ or $O(400)$ constant-time operations.

</details>

---

## Hint 4

Suppose we have a function `getans(date, op)` that, when $op = 0$, returns the Julian date (4-year leap rule) after `date` days from year 0; and when $op = 1$, returns the Gregorian date (century rule) after `date` days from year 0.

If the date is in the BC era or before 1582.10.4, we can safely call `getans(date, 0)`.

But when switching from Julian to Gregorian, the Julian calendar treated years divisible by 100 but not 400 as leap years (e.g., AD 100, 200, 300, 500…). These "extra February 29ths" do not exist in the Gregorian calendar. Additionally, 10 days are missing. So we cannot directly call `getans(date, 1)`. How do we handle this?

<details>
<summary>Click to expand</summary>

From AD 1 to 1582, the number of years divisible by 100 is $1582 / 100 = 15$, and the number divisible by 400 is $1582 / 400 = 3$. Hence the Julian calendar counted $15 - 3 = 12$ extra leap years compared to the Gregorian calendar.

When entering the Gregorian segment, the code does:

```cpp
date += 10;                       // compensate for the missing 10 days (1582.10.5 ~ 10.14)
date -= 1582 / 100 - 1582 / 400;  // subtract the extra Julian leap days (12 days)
```

Now `date` is aligned with the actual Gregorian day count, and we can safely call `getans(date, 1)`.

</details>

---

## Solution

<details>
<summary>View full solution & code walkthrough</summary>

### 1. Overall Flow

```cpp
void solve() {
    cin >> date; date++;  // convert "days elapsed" to "day index"
```

Then check in order:

#### Segment 1: BC

```cpp
if (date <= (4712 / 4) * (365 * 4 + 1) + 366) {
    // BC
    Date ans = getans(date, 0);
    cout << ans.day << " " << ans.month << " "
         << 4713 - ans.year << " BC" << endl;
    return;
}
```

- Total BC days = $4712 \times 365 + (4712/4) \times 1 + 366$ (i.e., 4713 BC ~ 1 BC, where the first year 4713 BC is a leap year with 366 days, and the rest follow the 4-year cycle).
- Use Julian `getans(date, 0)` to get the year (0-based, where year 0 = 4713 BC). Actual year = $4713 - \text{year}$, output with `BC`.

#### Segment 2: AD up to 1582.10.4

```cpp
date -= (4712 / 4) * (365 * 4 + 1) + 366;  // subtract BC days

int date_of_gregorian = 1581 * 365 + (1581 / 4);
for (int i = 1; i <= 9; ++i) date_of_gregorian += month[i];
date_of_gregorian += 4;  // 1582.10.04 is the last day of this segment

if (date <= date_of_gregorian) {
    Date ans = getans(date + 366, 0);  // +366 because counting starts from virtual year 0
    cout << ans.day << " " << ans.month << " " << ans.year << endl;
    return;
}
```

- `date_of_gregorian` computes the total days from AD 1.1.1 to 1582.10.4.
- `getans` starts counting from year 0 internally, so we pass `date + 366` (virtual year 0 is treated as a leap year with 366 days in the Julian system).

#### Segment 3: Gregorian

```cpp
date += 10;                       // compensate for the missing ten days
date -= 1582 / 100 - 1582 / 400;  // subtract extra Julian leap years

Date ans = getans(date + 366, 1);
cout << ans.day << " " << ans.month << " " << ans.year << endl;
```

### 2. The `getans(n, op)` Function

#### Julian (`op == 0`)

```cpp
ll p4 = (n - 1) / (365 * 4 + 1);   // whole 4-year cycles
n -= p4 * (365 * 4 + 1);

for (int i = 0; i <= 4; ++i) {
    if (n > year[i]) { n -= year[i]; continue; }
    // first year of the cycle is a leap year
    if (i == 0) month[1] = 29; else month[1] = 28;

    for (int j = 0; j <= 11; ++j) {
        if (n > month[j]) n -= month[j];
        else return (Date){p4 * 4 + i, j + 1, n};
    }
}
```

- Skip whole 4-year blocks of 1461 days each.
- Within the remaining incomplete cycle, process year by year then month by month.

#### Gregorian (`op == 1`)

```cpp
ll p400 = (n - 1) / (365 * 400 + 97);  // whole 400-year cycles
n -= p400 * (365 * 400 + 97);

for (int i = 0; i < 400; ++i) {
    if (i % 400 == 0 || (i % 4 == 0 && i % 100 != 0))
        month[1] = 29;
    else month[1] = 28;

    for (int j = 0; j < 12; ++j) {
        if (n > month[j]) n -= month[j];
        else return (Date){p400 * 400 + i, j + 1, n};
    }
}
```

- Skip whole 400-year blocks of 146097 days each.
- Within the remaining incomplete cycle, process year by year with Gregorian leap year rules.

### 3. Key Boundary Summary

| Boundary | Handling |
|----------|----------|
| Input $d=0$ means the starting day | `date = d+1`, naturally maps to Jan 1 |
| First BC year (4713 BC) is a leap year | `year[0] = 366`, and `getans` starts from year 0 (leap year) |
| Virtual year 0 AD | `getans(date + 366, 0)`, skip with 366 days |
| 1582.10.5–10.14 do not exist | `date += 10` to skip |
| Gregorian has fewer leap years | `date -= 12` to deduct (12 such years between AD 1–1582) |

The entire simulation uses **piecewise judgment + cycle compression** to reduce an $O(\text{year})$ approach to $O(1)$ constant-time queries.

</details>

---

## Food for Thought

**Q1.** Why must the parameter `n` of `getans` satisfy $n \ge 1$? What would happen if $n = 0$ were passed?

<details>
<summary>Click to view answer</summary>

`(n-1) / cycle_days` with $n = 0$ gives a numerator of $-1$. In C++, integer division truncates toward zero, producing $0$ or $-1$ (implementation-defined before C++11, now defined as truncation toward zero), leading to an incorrect number of cycles skipped and breaking the subsequent loop logic. Hence $n$ must be at least $1$.

</details>

**Q2.** There are 97 leap years in a 400-year Gregorian cycle. How is that number derived?

<details>
<summary>Click to view answer</summary>

In 400 years: divisible by 4 → $400/4 = 100$; subtract those divisible by 100 → $400/100 = 4$; add back those divisible by 400 → $400/400 = 1$. $100 - 4 + 1 = 97$.

</details>

**Q3.** If the input $d$ happened to correspond to the "non-existent" dates of October 5–14, 1582, the problem guarantees such inputs won't appear. But if they did, what would your program output?

<details>
<summary>Click to view answer</summary>

The problem guarantees all queried dates are **valid and existent**, so dates like 1582.10.5–10.14 will never appear. If they did, the program's `date += 10` would push them into the normal Gregorian range, producing a "plausible-looking but actually wrong" date — which just goes to show why the problem's constraints matter.

</details>
