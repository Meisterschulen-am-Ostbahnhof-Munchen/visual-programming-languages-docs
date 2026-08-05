# ARR_MIN
![ARR_MIN](./ARR_MIN.svg)
* * * * * * * * * *
## Introduction
The function block **ARR_MIN** determines the minimum of all elements in a one-dimensional array of type `INT`. The block expects a dynamic array (`ARRAY[*]`) as an input/output parameter and outputs the smallest element found via a separate data output. The calculation is triggered by the event `REQ`; the result is acknowledged upon completion with the event `CNF`.
## Interface Structure

### **Event Inputs**

| Event | With Data |

|---------|-----------|

| `REQ` | `A` |

### **Event Outputs**

| Event | With Data |

|---------|-----------|

| `CNF` | `A` (and empty data output) |

### **Data Inputs**

| Name | Type | Comment |

|------|----------------|-----------|

| `A` | `ARRAY[*] OF INT` | Input Array (Input/Output) |

### **Data Outputs**

| Name | Type | Comment |

|------|------|-----------|

| (Unnamed) | `INT` | Minimum value of the array |

### **Adapter**
No adapters available.

## Functionality

1. The algorithm initializes a temporary variable `currentMin` with the value of the first array element (determined via `LOWER_BOUND(A,1)`).

2. The array is then traversed from index `LOWER_BOUND(A,1)+1` to `UPPER_BOUND(A,1)`.

3. In each iteration, the current value is compared to `currentMin`, and the minimum is updated using the function `MIN()`.

``` 4. After the loop completes, the final minimum value is output via the unnamed data output, and the event `CNF` is sent.

The calculation is performed sequentially within a single execution step; the runtime increases linearly with the array size.

## Technical Features
- **Dynamic Array**: The function block uses `ARRAY[*] OF INT`, meaning the actual array size is determined at runtime using the system's built-in functions `LOWER_BOUND` and `UPPER_BOUND`.
- **Package Assignment**: The function block belongs to the package `logiBUS::utils::dyn_arr` and is intended for use in environments that support dynamic arrays.
- **Input/Output Parameters**: The parameter `A` is declared as `VAR_IN_OUT` – the array is both read and (here without modification) passed on via the event output `CNF`.
- **No State Machine**: The function block operates purely functionally; there are no internal states or delays.

## State Overview
The function block only has two implicit states:

- **Idle**: Waiting for a `REQ` event.
- **Processing**: After `REQ` arrives, the calculation is executed, immediately followed by `CNF`, and the function block returns to the idle state.

There are no multiple states, wait loops, or time-controlled processes.

## Application Scenarios
- **Sensor Field Analysis**: Determining the lowest temperature in a series of measurements.
- **Quality Control**: Searching for the minimum reject rate in a production batch.
- **Optimization**: Determining the most favorable price from a list of offers.
- **Comparison Operations**: As a basic building block for further statistical evaluations (e.g., together with maximum and sum).

## Comparison with Similar Blocks
- **MIN (IEC 61131-3)**: The classic MIN block compares two scalar values. `ARR_MIN` extends this concept to an entire array, thus eliminating the need for iterative chaining.
- **ARR_MAX**: A logical counterpart to the maximum; The algorithm differs only in the comparison function (`MIN` vs. `MAX`).
- **Statistical Building Blocks**: `ARR_MIN` is a special case of general aggregation functions (e.g., SUM, MEAN). Its focus is on finding the minimum, enabling simple and fast implementation.

## Conclusion
`ARR_MIN` offers a compact and efficient solution for determining the minimum in dynamic integer arrays. Thanks to its simple request/confirm protocol and clean package structure, it can be easily integrated into existing 4diac industrial applications. Using `LOWER_BOUND`/`UPPER_BOUND` makes it independent of the actual array size and allows for flexible adjustments at runtime.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]