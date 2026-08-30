# SUM

![SUM](./SUM.svg)

* * * * * * * * * *

## Introduction

The **SUM** function block allows you to calculate the sum of all elements in a dynamic array. It is triggered by an event at the REQ input and, after successful calculation, outputs the result via the data output and a confirmation event via CNF.

## Interface Structure

### **Event Inputs**

| Name | Description |
|------|--------------|
| REQ | Starts the sum calculation of array A. |

### **Event Outputs**

| Name | Description |
|------|--------------|
| CNF | Signals the completion of the calculation and the validity of the result. |

### **Data Inputs**

There are no pure data inputs. The required array is provided via the **InOut** port `A`.

### **Data Outputs**

| Name | Type | Description |
|------|------|---------------|
| (empty) | DINT | Resultant sum of all array elements (type DINT). |

### **Adapters**

None.

## Functionality

The FB `SUM` accepts a one-dimensional array `A` of type `INT` with arbitrary length (declared as `ARRAY[*]`). When the event `REQ` is triggered, the array's contents are summed element by element. The sum is accumulated in a temporary variable of type `DINT` to prevent overflow. After iterating completely over all valid indices (from `LOWER_BOUND(A,1)` to `UPPER_BOUND(A,1)`), the result is passed to the output (data type `DINT`), and the event `CNF` is triggered.

**Important Note:** Although `A` is declared as an **InOut** variable, its value is not modified during the calculation. It functions solely as an input in this function block.

**Important Note:**

## Technical Features

- **Dynamic Array Size:** The function block supports variable-length arrays by using the functions `LOWER_BOUND` and `UPPER_BOUND`, as specified by IEC 61131-3.
- **Type Extension:** The sum is returned as a `DINT` value (32-bit), allowing even larger sums of `INT` values (16-bit) to be represented without overflow.
- **Event-Driven Execution:** Computation is performed only when needed, enabling efficient resource utilization.

## State Overview

The function block does not have an explicit state machine. Its behavior can be described as follows:

1. **Waiting:** No event is active – initial state.
2. **Calculation:** Entry after receiving `REQ`; summation of the array.
3. **Acknowledgement:** After completion of the calculation, `CNF` is sent; return to the wait state.

## Application Scenarios

- Summing sensor readings over a specific period.
- Calculating totals in a production plant (e.g., quantities, fill levels).
- Preprocessing data arrays before further logical or arithmetic processing.

## Comparison with Similar Function Blocks

- **SUM in IEC 61131-1:** This function block is closely based on the function of the same name from IEC 61131-3, but additionally enables event-driven execution and direct integration into the 4diac event model.
- **ADD / MULT:** While `ADD` or `MULT` process individual number pairs, `SUM` allows the processing of an entire array in one step, simplifying the application logic.

## Conclusion

The function block `SUM` offers a simple and efficient way to calculate the sum of all elements in a dynamic array. Its event-driven execution and robust handling of different array sizes make it particularly suitable for industrial control tasks where large amounts of data need to be aggregated.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
