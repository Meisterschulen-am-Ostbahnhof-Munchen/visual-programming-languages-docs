# AUDI_GE

![AUDI_GE](./AUDI_GE.svg)

* * * * * * * * * *
## Introduction
The function block `AUDI_GE` performs a "greater than or equal to" comparison of two values. It provides the result as a Boolean value. The block is implemented as a composition and internally uses the standard comparison block `F_GE` from the IEC 61131-3 library. Input and output are exclusively via unidirectional adapters.

## Interface Structure
### **Event Inputs**

- **No direct event inputs**

The comparison is triggered via the **socket adapters** `IN1` and `IN2`. Each of these adapters sends an event to the internal module as soon as valid data is available.

### **Event Outputs**

- **No direct event outputs**

The result of the comparison is passed on as an event via the **Plug Adapter** `OUT` as soon as the evaluation is complete.

### **Data Inputs**

The data values to be compared are obtained via the following adapters:

- **Adapter `IN1`** – provides the first comparison value (type corresponding to adapter `AUDI`).

- **Adapter `IN2`** – provides the second comparison value (type corresponding to adapter `AUDI`).


### **Data Outputs**

- **Adapter `OUT`** – outputs the Boolean value `TRUE` if `IN1 ≥ IN2` is present, otherwise `FALSE` (type corresponds to adapter `AX`).

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|-----|--------------|

| `IN1` | Socket | `adapter::types::unidirectional::AUDI` | First Input Value |

| `IN2` | Socket | `adapter::types::unidirectional::AUDI` | Second Input Value |

| `OUT` | Plug | `adapter::types::unidirectional::AX` | Output: `IN1 >= IN2` (boolean) |

## Functionality

1. The events from `IN1.E1` and `IN2.E1` are routed to the internal `F_GE` module (via an OR operator – both events trigger the same `REQ` input).


``` 2. Simultaneously, the data `IN1.D1` and `IN2.D1` are transferred to the corresponding inputs `F_GE.IN1` and `F_GE.IN2`.

3. The internal function block `F_GE` calculates `IN1 ≥ IN2`.

4. The result appears at output `F_GE.OUT` and is passed on to adapter `OUT.D1`.

5. The event `F_GE.CNF` triggers `OUT.E1` to signal to the environment that a new result is available.


## Technical Features

- The function block is entirely adapter-based – it has no traditional event or data inputs at the top level.

- The adapters `AUDI` and `AX` are unidirectional and must be defined in the corresponding project.

- Execution is asynchronous: As soon as one of the two input adapters provides an event, the comparison is recalculated. Synchronization of the values is not required, as both data must be available simultaneously for the result to be meaningful.

- The function block configuration complies with the IEC 61131-3 standard and the Eclipse 4diac environment.

## State Overview

The function block itself does not have an explicit state machine – all control logic resides in the internal `F_GE`. Its behavior is deterministic:

- **Waiting for Trigger**: As long as no event arrives at `IN1` or `IN2`, the output `OUT` remains unchanged.

- **Calculation**: When an event arrives, the comparison is performed.

- **Result Output**: The result is provided at the output, and an event is sent to the `OUT` adapter.

## Application Scenarios

- **Status Monitoring**: Checking whether a measured value reaches or exceeds a threshold.

- **Actuator Control**: Activating an output as soon as a condition `Wert1 ≥ Wert2` is met.

- **Value Comparison in Production Plants**: Comparing target/actual values in continuous processes.

- **Simple Logical Interconnections**: As part of more complex safety or control logic.

## Comparison with Similar Function Blocks

- **AUDI_GT** (greater than) – compares against `>`, returns `TRUE` only if the first value is strictly greater.

- **AUDI_EQ** (equal) – compares for equality.

- **AUDI_LE** (less or equal) – the counterpart to `≤`.

- **AUDI_GE** is the direct counterpart to `AUDI_LE` and covers the case of "at least equal". Compared to a single function block like `F_GE`, `AUDI_GE` offers adapter-based encapsulation, which facilitates reuse in different projects.

## Conclusion

`AUDI_GE` is a specialized comparison block that enables flexible and clean interface definition through the use of adapters. It is particularly suitable for modular automation projects where values are exchanged via standardized interfaces. Internal use of the proven `F_GE` block guarantees correct and efficient comparison operations.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```