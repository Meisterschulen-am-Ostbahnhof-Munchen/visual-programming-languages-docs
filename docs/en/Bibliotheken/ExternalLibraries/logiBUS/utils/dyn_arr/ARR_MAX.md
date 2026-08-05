# ARR_MAX
![ARR_MAX]( )
![ARR_MAX](./ARR_MAX.svg)

* * * * * * * * * *
## Introduction
The function block `ARR_MAX` calculates the maximum value of a one-dimensional array of type `INT`. The implementation is in Structured Text (ST) according to IEC 61131-3 and is from the package `logiBUS::utils::dyn_arr`. The block is suitable for dynamic arrays of any size, with the lower and upper bounds determined at runtime.

## Interface Structure

### **Event Inputs**

| Name | Type | With Var | Description |

|------|-----|---------|--------------|

| `REQ` | Event | `A` | Starts the calculation of the maximum. The array `A` must be valid and contain values at the time of the event. |

### **Event Outputs**

| Name | Type | With Var | Description |

|------|-----|---------|--------------|

| `CNF` | Event | (empty), `A` | Confirms the end of the calculation. The event is triggered as soon as the maximum value has been determined. The array `A` remains valid during the event. |

### **Data Inputs**

| Name | Type | Initial Value | Description |

|------|-----|-------------|--------------|

| `A` (IN/OUT) | `ARRAY[*] OF INT` | – | One-dimensional integer array whose maximum is to be calculated. The size is determined dynamically at runtime. |

### **Data Outputs**

| Name | Type | Initial Value | Description |

|------|-----|--------------|--------------|

| `MAX` | `INT` | – | The determined maximum value of the array `A`. (The name `MAX` is derived from the function – in the XML definition, the output is unnamed but is treated as a function return value.)

### **Adapter**

Omitted.

## Functionality

1. **Start**: A signal at the event input `REQ` triggers the processing. The provided array `A` must be valid at this point.

2. **Initialization**: The variable `i` is set to the index of the first element (`LOWER_BOUND(A,1)`). `currentMax` receives the value of this first element.

3. **Iteration**: A loop called `FOR` iterates through all remaining elements of `A` (from index `LOWER_BOUND(A,1)+1` to `UPPER_BOUND(A,1)`). The current maximum value is updated using the standard function `MAX()`.

4. **Closure**: After the loop, `currentMax` is set as the return value of the function `ARR_MAX`. The event output `CNF` is sent, and the output signal `MAX` (interpreted here as a return value) is available.

## Technical Features
- **Dynamic Array Boundaries**: The function uses `LOWER_BOUND` and `UPPER_BOUND` to determine the actual size of the array at runtime. This allows the function block to work with arrays of any length without requiring a fixed size to be specified.
- **No State Memory**: The function block is a pure function without internal state. Each call calculates the maximum value, independent of the previous call.
- **Typing**: The function block is specialized for the data type `INT`. A separate version would need to be created for other data types (e.g., `REAL`, `LINT`).
- **Error Handling**: If the array is empty (e.g., lower bound > upper bound), access to `A[i]` would be undefined. The user must ensure that the array contains at least one element.

## State Overview

Since `ARR_MAX` is implemented as a **pure function** without a state machine (ECA algorithm), there are no explicit states. The process is strictly sequential within a single event cycle:

- **Waiting for REQ**
- **Calculation in progress** (no separate state signal, as the process is completed within one cycle)
- **CNF is being sent** (output of the maximum)

Therefore, an explicit state graph is not required.

## Application Scenarios
- **Data Analysis**: Determining the peak value in measurement series (e.g., temperature, pressure, speed).
- **Monitoring**: Detecting threshold violations by comparing them to the maximum of an array.
- **Signal Processing**: Determining the maximum level in audio or communication signals.
- **Control Engineering**: Selecting the highest value from multiple sensor data points (e.g., for priority decisions).

## Comparison with Similar Function Blocks

| Function Block | Function | Difference from ARR_MAX |

|----------|----------|------------------------|

| `ARR_MIN` | Minimum of an Array | Analogous, but minimum instead of maximum. |

| `ARR_SUM` | Sum of Array Elements | Different mathematical operation; no comparison between elements. |

| `ARR_MEAN` | Arithmetic Mean | Requires additional division by the number of elements; not just comparison. |

| `MAX` (IEC 61131-3) | Maximum of two values | Works only with scalars, not arrays. `ARR_MAX` extends this to entire arrays. |

ARR_MAX` combines array traversal capability with simple maximum determination and is therefore a specialized, yet reusable function block for dynamic arrays.

## Conclusion

The function block `ARR_MAX` offers a compact and efficient way to determine the maximum value of a dynamic integer array. Using `LOWER_BOUND` and `UPPER_BOUND` makes it flexible and robust against different array sizes. Due to its purely functional design without state storage, it is ideally suited for use in data flow-oriented automation applications.
