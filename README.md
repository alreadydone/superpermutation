# Superpermutation

In combinatorial mathematics, a superpermutation on n symbols is a string that contains each permutation of n symbols as a substring.

It has been shown that for 1 ≤ n ≤ 5, the smallest superpermutation on n symbols has length 1! + 2! + … + n! (sequence [A180632](https://oeis.org/A180632) in the OEIS). The first five superpermutations have respective lengths 1, 3, 9, 33, and 153, forming the strings 1, 121, 123121321, 123412314231243121342132413214321, and the 8 strings for n=5.

The following program produces permutations and the string using greedy algorithm.

Example output for n=4:

Command line
```
./superp 4
```
Output:

```
1234
2341
3412
4123
===========
2314
3142
1423
4231
===========
3124
1243
2431
4312
===========
===========
2134
1342
3421
4213
===========
1324
3241
2413
4132
===========
3214
2143
1432
4321
==============================================
len=33
```

In superperm-4.txt the string

```
123412314231243121342132413214321
```
