# AS_SPLIT_3

![AS_SPLIT_3](./AS_SPLIT_3.svg)

* * * * * * * * * *
## Introduction

The AS_SPLIT_3 function block distributes an incoming adapter data stream to three identical outputs. It is implemented as a generic function block and designed for use with the `adapter::types::unidirectional::AS` adapter type.
## Interface Structure

### **Event Inputs**

None

### **Event Outputs**

None

### **Data Inputs**

None

### **Data Outputs**

None

### **Adapter**

| Name | Type | Direction | Description |
|-------------|-----|-----------|--------------|
| IN | `adapter::types::unidirectional::AS` | Socket | Input adapter – Data source distributed to three outputs. |
OUT1 | `adapter::types::unidirectional::AS` | Plug | First output – receives the unchanged data from IN. |
OUT2 | `adapter::types::unidirectional::AS` | Plug | Second output – receives the unchanged data from IN. |
OUT3 | `adapter::types::unidirectional::AS` | Plug | Third output – receives the unchanged data from IN. |

## Functionality

The module forwards the adapter data received via socket `IN` identically and without delay to all three adapter plugs `OUT1`, `OUT2`, and `OUT3`. No data manipulation, filtering, or buffering takes place. Distribution occurs in a pure pass-through mode.

## Technical Features

- **Generic Type**: The function block uses the attribute `eclipse4diac::core::GenericClassName` with the value `'GEN_AS_SPLIT'` to enable generic instantiation. The specific adapter type (`adapter::types::unidirectional::AS`) is defined during project configuration.
- **Eventless**: Since no events (event inputs/outputs) are defined, data transmission is purely data-driven – changes to the input adapter are immediately propagated to all outputs.
- **Registered Copyright**: The function block is copyrighted under the Eclipse Public License 2.0.

## State Overview

The function block does not have an internal state machine or an ECC (Execution Control Chart). The behavior is purely combinatorial: As soon as the input adapter data changes, the output data is updated accordingly.

## Application Scenarios

- **Data Distribution in Control Systems**: Splitting a sensor data stream (e.g., AS-i bus data) across multiple parallel processing blocks.
- **Signal Copying for Diagnostic Purposes**: Connecting a separate monitor or logging path without affecting the main data.
- **Control Signal Multiplication**: Distributing a single instruction set to multiple actuators or subsystems.

## Comparison with Similar Function Blocks

- **AS_SPLIT_2**: An analog function block with only two outputs. AS_SPLIT_3 extends the number to three outputs.
- **AS_MERGE (Theoretical)**: Unlike a merge function block, which combines multiple inputs into one output, AS_SPLIT_3 performs the reverse function (1 → N).
- **Generic Split Function Blocks**: Similar concepts exist for data inputs (e.g., SPLIT_INT), but these work with elementary data, while AS_SPLIT_3 processes adapters (complex data types).

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

AS_SPLIT_3 is a simple yet useful function block for duplicating adapter data in the 4diac IDE. Its generic design and the absence of event traffic make it particularly lightweight and usable in many scenarios. The documented license (EPL 2.0) ensures that the block can be legally integrated into your own projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
