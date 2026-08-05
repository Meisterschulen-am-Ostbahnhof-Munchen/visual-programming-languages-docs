# AUDI_UDINT_NE
![AUDI_UDINT_NE](./AUDI_UDINT_NE.svg)

* * * * * * * * * *
## Introduction
The function block **AUDI_UDINT_NE** performs a not-equal comparison between a value (type UDINT) provided via an adapter and a second direct data input. It is part of the IEC 61131-3 comparison functions and encapsulates the comparison logic in an addressable component with event control. This block is particularly suitable for use in industrial control systems where values from different sources need to be checked for inequality.
## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|------------|

| REQ | Event | Serves as a service request to initiate the comparison. The data input `IN2` is also processed. |

### **Event Outputs**

There are no separate event outputs. The comparison result and the corresponding output confirmation are provided via the **adapter output `OUT`** (adapter event `E1`).

### **Data Inputs**

| Name | Type | Comment |

|------|-------|-----------|

| IN2 | UDINT | Second comparison value. |

### **Data Outputs**

There are no direct data outputs. The comparison result (Boolean value) is output via the **adapter output `OUT`** (data point `D1`).

### **Adapter**

| Name | Type | Direction | Comment |

|------|-----|----------|-----------|

| IN1 | `adapter::types::unidirectional::AUDI` | Socket (Input) | Returns the first comparison value as type UDINT and the start event for processing. |

| OUT | `adapter::types::unidirectional::AX` | Plug (Output) | Returns the result of the inequality check (Boolean) and the confirmation event. |

## Functionality

The function block compares the two 32-bit integer values (UDINT) for inequality. The first value is provided via the **adapter input `IN1`** (data point `D1`), the second via the **data input `IN2`**. The comparison is triggered by an event at one of the two inputs:

- When the **event `REQ`** occurs, `IN2` is compared with the current value of `IN1.D1`.

`` - When an **event arrives via the adapter `IN1.E1`**, a comparison is also triggered, comparing the data value `IN1.D1` transmitted via the adapter with the value last received by `IN2`.

Internally, the comparison is performed by the embedded function block `F_NE` (type `iec61131::comparison::F_NE`). The result (`true` if there is no difference) is output via the **adapter output `OUT.D1`**, and the event `OUT.E1` is sent simultaneously.

Internally, the comparison is performed by the embedded function block `F_NE` (type `iec61131::comparison::F_NE`).
## Technical Features

- **Adapter-Based Communication:** Data and event connections are encapsulated in standardized adapters (`AUDI`, `AX`). This simplifies reuse and the modular design of function block networks.
- **Dual Triggering Options:** Comparison can be initiated via the direct event input `REQ` or via the event of the adapter input `IN1`. This enables flexible control architectures.
- **Packet-Oriented Classification:** The function block is stored in the package `iec61131::comparison` and follows the IEC 61131-3 classification for comparison functions.
- **No dedicated state logic:** All comparison logic is delegated to the internal function block `F_NE`; the function block itself does not have its own ECloch state machine.

## State Overview

The function block has **no** explicit state machine. Processing is event-driven:

1. Event at `REQ` or `IN1.E1` → internally, `F_NE` is called.

2. After the comparison is complete, the event `OUT.E1` is generated, and the result is output to `OUT.D1`.

Between events, the function block remains passive and does not store any state information.

## Application Scenarios
- **Limit Monitoring:** Checks whether a measured value (via adapter) deviates from a target value.
- **Status Queries:** Determines whether two sensor values (e.g., rotational speeds or counter readings) differ.
- **Error Detection:** Detects an unexpected input level by comparison with a reference value.
- **Modular Control Logic:** Integration into larger function block networks where data is exchanged via adapters.

## Comparison with Similar Function Blocks
- **`AUDI_UDINT_EQ` (Equal):** Performs an equal comparison. Logical inverse of the `NE` function block.
- **`AUDI_INT_NE`, `AUDI_DINT_NE`:** Analog function blocks for the data types `INT` and `DINT`, respectively. The interface structure is identical; only the data path is adapted to the respective type.
- **`F_NE` (direct comparison function block):** Offers the same comparison without adapter encapsulation. The `AUDI_UDINT_NE` adds the adapter inputs/outputs, thus simplifying the wiring in directed data flows.

## Conclusion

The **AUDI_UDINT_NE** is a specialized comparison function block for checking the inequality of 32-bit values (UDINT) in an adapter-based, event-driven environment. By encapsulating the event and data paths in standardized adapters, integration into complex automation solutions is facilitated. The component offers a clean, functional interface and, due to its simplicity and clarity, is a reliable tool for comparisons in IEC 61131-3 environments.
