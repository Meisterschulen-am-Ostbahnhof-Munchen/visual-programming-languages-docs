# AUI_LE

![AUI_LE](./AUI_LE.svg)

* * * * * * * * * *

## Introduction

The function block **AUI_LE** performs a less-than-equal-to comparison of two analog input values. It is implemented as a composite block that internally uses the IEC 61131-3 block `F_LE`. The result (a BOOL value) is provided via an output adapter. The function block is suitable for event-driven limit monitoring in automation systems.

## Interface Structure

### **Event Inputs**

- **IN1.E1** (via adapter IN1) – Event that triggers the comparison as soon as the first input value is available.
- **IN2.E1** (via adapter IN2) – Event that triggers the comparison as soon as the second input value is available.

### **Event Outputs**

- **OUT.E1** (via adapter OUT) – Event output after a successful comparison, indicating that the result is valid.

### **Data Inputs**

- **IN1.D1** (via adapter IN1) – First input value (analog, type according to adapter `AUI`).
- **IN2.D1** (via adapter IN2) – Second input value (analog, type according to adapter `AUI`).

### **Data Outputs**

- **OUT.D1** (via adapter OUT) – Comparison result (BOOL): `TRUE` if IN1 ≤ IN2, otherwise `FALSE`.

### **Adapters**

- **IN1** – Socket (Type: `adapter::types::unidirectional::AUI`) for the first analog value.
- **IN2** – Socket (Type: `adapter::types::unidirectional::AUI`) for the second analog value.
- **OUT** – Plug (Type: `adapter::types::unidirectional::AX`) for the comparison result.

## Functionality

The module contains an internal network with a `F_LE` module. The events of the two input adapters (`IN1.E1` and `IN2.E1`) are connected to the `REQ` input of the `F_LE` module. Each incoming event (regardless of the input) triggers a comparison of the current data values `IN1.D1` and `IN2.D1`. The internal `F_LE` calculates `(IN1 ≤ IN2)` and stores the result on its output `OUT`. This result is output via the adapter `OUT.D1`, and simultaneously, an event is sent via `OUT.E1`.

## Technical Features

- **Adapter-based interface**: The inputs and outputs are implemented as unidirectional adapters, enabling flexible integration with other components.
- **Event triggering**: The comparison is triggered by any event present at either input – simultaneous events at both inputs are not required.
- **Internal Standard Block**: The comparison logic uses the tested IEC 61131-3 block `F_LE`.
- **License**: This block is licensed under the Eclipse Public License 2.0 (EPL-2.0), Copyright (c) 2013 TU Wien ACIN.

## State Overview

The block does not have an explicit state machine. It operates in an event-driven manner, and its output is the direct result of the internal combinatorial comparison. After event processing, the result remains stable until the next event.

## Application Scenarios

- **Limit Monitoring**: Checking whether a measured value (e.g., temperature, pressure) exceeds a set threshold.
- **Control Logic**: Triggering an action when two analog signals are in a defined relationship (e.g., fill level ≤ maximum fill level).
- **Safety Functions**: Compares redundant sensor values for "less than or equal to" for fault detection.

## Comparison with Similar Function Blocks

- **AUI_LT**: Performs a "less than" (strict less) comparison.
- **AUI_EQ**: Checks for equality between the two values.
- **AUI_GT**: Checks for "greater than".
- **AUI_GE**: Checks for "greater than or equal to".

All these function blocks have the same adapter interface (AUI for inputs, AX for outputs) and differ only in their comparison operation.

## Conclusion

The `AUI_LE` function block offers a simple and reliable way to check analog signals for "less than or equal to". Thanks to its adapter-based interface and event-driven execution, it can be seamlessly integrated into automation projects that require standardized comparison functions.
