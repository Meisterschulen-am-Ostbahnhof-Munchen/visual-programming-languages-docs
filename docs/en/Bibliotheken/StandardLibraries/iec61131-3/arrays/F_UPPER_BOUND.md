# F_UPPER_BOUND

![F_UPPER_BOUND](F_UPPER_BOUND.svg)

* * * * * * * * * *

## Introduction

`F_UPPER_BOUND` returns the upper index bound of a selected dimension of an array of arbitrary type. Together with [F_LOWER_BOUND](F_LOWER_BOUND.md), it forms the basis for generic, size-independent array processing — e.g. `F_LEN_ARRAY` (see `utils::arrays`) is computed from both bounds.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the query, carries `ARR` and `DIM`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `OUT`.

### **Data Inputs**

- **ARR** (ANY_DERIVED): The array whose index bound is to be determined.
- **DIM** (ANY_INT, default `UDINT#1`): The array dimension to consider, 1-based.

### **Data Outputs**

- **OUT** (ANY_INT): The highest index of the selected dimension.

## Functionality

On `REQ`, the block determines the upper index bound of the dimension of `ARR` selected via `DIM` and outputs it via `OUT`. `CNF` is then triggered.

## Technical Features

- **`ANY_DERIVED` input**: `ARR` accepts arrays of any element type and any dimensionality.
- **1-based dimension selection**: `DIM = 1` denotes the first dimension; for multi-dimensional arrays, this lets a specific dimension be queried.
- **Not necessarily `0`/greater than `0`**: IEC 61131-3 arrays can be declared with arbitrary index bounds (including negative, or not starting at `0`) — `F_UPPER_BOUND` returns the actually declared bound, making no assumption about its value.

## State Overview

Stateless: every `REQ` immediately results in the query and `CNF`.

## Application Scenarios

- **Generic array processing**: Loops that iterate over an array's elements independent of its actually declared size/index bounds.
- **Building block for length calculation**: `F_LEN_ARRAY` (`utils::arrays`) combines `F_UPPER_BOUND` with `F_LOWER_BOUND` to compute the element count of a dimension.

## Comparison with similar function blocks

- **[F_LOWER_BOUND](F_LOWER_BOUND.md)**: the other index bound of the same dimension.
- **`F_LEN_ARRAY`** (`utils::arrays`): computes the element count from `F_UPPER_BOUND` and `F_LOWER_BOUND`.

## Conclusion

`F_UPPER_BOUND` provides the upper index bound of an array dimension and is a fundamental building block for generic, size-independent array processing in IEC 61131-3 applications.
