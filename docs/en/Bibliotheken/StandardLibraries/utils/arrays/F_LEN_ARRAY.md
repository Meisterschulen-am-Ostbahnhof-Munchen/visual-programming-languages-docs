# F_LEN_ARRAY

![F_LEN_ARRAY](F_LEN_ARRAY.svg)

* * * * * * * * * *
## Introduction

`F_LEN_ARRAY` is a simple function block that returns the length (element count) of a selected dimension of an array of arbitrary type. It complements the standard functions `UPPER_BOUND`/`LOWER_BOUND` with a directly usable length calculation.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the calculation, carries `ARR` and `DIM`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **ARR** (ANY_DERIVED): The array whose length is to be determined.
- **DIM** (ANY_INT, default `DINT#1`): The array dimension to consider (for multi-dimensional arrays).

### **Data Outputs**

- **OUT** (ANY_INT): The length of the selected dimension, i.e. the element count.

## Functionality

The block is implemented as a `SimpleFB` with a single ECC state. On `REQ`, the algorithm's ST statement computes `OUT := ADD(SUB(UPPER_BOUND(ARR, DIM), LOWER_BOUND(ARR, DIM)), 1)` — i.e. the upper minus the lower index bound of the selected dimension, plus 1 (since both bounds are inclusive). `CNF` is then triggered.

## Technical Features

- **`ANY_DERIVED` input**: `ARR` accepts arrays of any element type and any dimensionality.
- **Dimension selection via `DIM`**: For multi-dimensional arrays, `DIM` selects which dimension's length to query; the default is the first dimension (`DINT#1`).
- **Based on `UPPER_BOUND`/`LOWER_BOUND`**: The block is a direct combination of these two IEC 61131-3 standard functions, saving the manual arithmetic.

## State Overview

Stateless: every `REQ` immediately results in the calculation and `CNF`.

## Application Scenarios

- **Dynamic array processing**: Looping over an array whose actual size is only known at runtime (e.g. depending on the caller).
- **Sanity checking**: Comparing the actual array length against an expected size before accessing individual elements.

## Comparison with similar function blocks

- **`UPPER_BOUND`/`LOWER_BOUND`**: the two standard functions `F_LEN_ARRAY` combines to perform its calculation.

## Conclusion

`F_LEN_ARRAY` provides a simple, directly usable length calculation for arrays of arbitrary type and a selectable dimension, without requiring `UPPER_BOUND`/`LOWER_BOUND` to be combined manually.
