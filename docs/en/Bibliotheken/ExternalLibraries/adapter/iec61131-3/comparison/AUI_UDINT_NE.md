# AUI_UDINT_NE

![AUI_UDINT_NE](./AUI_UDINT_NE.svg)

* * * * * * * * * *

## Introduction

The function block **AUI_UDINT_NE** performs a not equal comparison between two values of type **UDINT**. It is implemented as a composite function block and uses standardized adapter interfaces for connection to other function blocks. The function block complies with IEC 61131-3 and is classified as a standard comparison function.

## Interface Structure

### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Service Request (trigger for the comparison) |

#### **Event Outputs**

The function block itself does not have direct event outputs. The result is provided via the adapter output `OUT`, which outputs an event on its `E1` port after a successful comparison.

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| IN2 | UDINT | Input value 2 (second comparison value) |

### **Data Outputs**

This function block does not have direct data outputs. The comparison value is output via the adapter output `OUT` on its `D1` port as **BOOL** (true if the values are inequality).

### **Adapter**

| Type | Direction | Name | Comment |


### **Adapter**

| Type | Direction | Name | Comment |


### **Adapter**

### **Adapter**

| Type | Direction | Name | Comment |


### **Adapter**

### **Adapter**

### **Adapter**

### **Adapter**

| ...| **Adapter**

| **Adapter**

| **Adapter**
| **Adapter**

| **Adapter**

| **Adapter**
| **Adapter**

| **Adapter**
| **Adapter**

| **Adapter**
| **Adapt |-----|----------|------|-----------|

| `adapter::types::unidirectional::AUI` | Socket | IN1 | Input value 1 (first comparison value) |

| `adapter::types::unidirectional::AX` | Plug | OUT | value 1 != value2 = true |

## Functionality

This function block compares two values of type **UDINT** for inequality. The first value is provided via socket `IN1` (port `D1`), the second value via data input `IN2`. The comparison is triggered by an event at `REQ` or by an event at socket `IN1.E1`. Inside is the function block `F_NE` (type `iec61131::comparison::F_NE`), which performs the actual inequality comparison. The result (BOOL) is output via the plugin `OUT` to `D1`, along with an event on `E1` once the comparison is complete.

The use of adapters enables loose coupling and standardized communication between function blocks in the 4diac IDE.

## Technical Features

- **Adapter-based interface:** The function block uses unidirectional adapters (`AUI` and `AX`) that are optimized for exchanging values and events between function blocks.

- **Internal Implementation:** The comparison is performed using an embedded standard function block `F_NE` from the library `iec61131::comparison`.

- **Type Environment:** The input values are defined as `UDINT` (unsigned double integer), and the result is output as `BOOL`.

- **Compatibility:** Suitable for applications according to IEC 61131-3, especially control and regulation tasks.

## State Overview

The function block does not have an explicit state machine in the XML. The internal logic of the function block `F_NE` operates in an event-driven manner:

1. **Wait:** The function block waits for an event on `REQ` or `IN1.E1`.

2. **Processing:** Upon triggering, the values `IN1.D1` and `IN2` are read and compared.

3. **Output:** The result is set to `OUT.D1`, and an event is triggered on `OUT.E1`.

## Application Scenarios

- **Status Monitoring:** Comparing counter readings or sensor measurements to detect deviations.

- **Safety Logic:** Checking whether two independent signal sources deliver different values (e.g., redundancy comparison).

- **Data Validation:** Determining whether a current value deviates from a reference value.


## Comparison with Similar Function Blocks

Other comparison blocks exist for `UDINT`, such as **AUI_UDINT_EQ** (equal), **AUI_UDINT_LT** (less than), or **AUI_UDINT_GT** (greater than). The **AUI_UDINT_NE** block described here focuses specifically on the non-equal case. Unlike simple function blocks with direct inputs/outputs, the adapter interface offers a standardized and reusable coupling option within the 4diac environment.

## Conclusion

The **AUI_UDINT_NE** function block is a specialized, adapter-based comparison block for testing the non-equality of two UDINT values. Thanks to its modular design and the internal use of a standard comparison block, it can be flexibly integrated into IEC 61131-3 projects. It is particularly suitable for applications requiring loose, event-driven data coupling.


# Conclusion ---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]