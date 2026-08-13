# AD_SPLIT_7

![AD_SPLIT_7](./AD_SPLIT_7.svg)

* * * * * * * * * *
## Introduction

The function block **AD_SPLIT_7** is a generic function block for splitting an incoming adapter of type `AD` (unidirectional) into seven separate output adapters. It allows a single adapter signal to be forwarded in parallel to multiple downstream components without modifying or buffering the data. The function block is specifically designed for use in control engineering (e.g., agricultural machinery) and is licensed under the Eclipse Public License 2.0.
---

## Interface Structure

### **Event Inputs**

None.

#### **Event Outputs**

None.

#### **Data Inputs**

None.

#### **Data Outputs**

None.

#### **Adapters**

| Direction | Name | Type | Description |
|----------|------|-----|--------------|
Socket (Input) | `IN` | `adapter::types::unidirectional::AD` | Receives the adapter signal to be distributed. |
Plug (Output) 1 | `OUT1` | `adapter::types::unidirectional::AD` | First output – identical copy of the input signal. |
Plug (Output) 2 | `OUT2` | `adapter::types::unidirectional::AD` | Second output. |
Plug (Output) 3 | `OUT3` | `adapter::types::unidirectional::AD` | Third output. |
| Plug (Output) 4 | `OUT4` | `adapter::types::unidirectional::AD` | Fourth output. |
| Plug (Output) 5 | `OUT5` | `adapter::types::unidirectional::AD` | Fifth output. |
| Plug (Output) 6 | `OUT6` | `adapter::types::unidirectional::AD` | Sixth output. |
| Plug (Output) 7 | `OUT7` | `adapter::types::unidirectional::AD` | Seventh output. |

---

## Functionality

The function block forwards the adapter signal (type `AD`) present at socket `IN` unchanged to all seven plugs (`OUT1` … `OUT7`). No data manipulation, synchronization, or buffering takes place. The outputs are always simultaneous and identical to the input. The function block operates purely on a data flow basis without events or state logic.

--

## Technical Features

- **Generic Function Block**: The function block is declared as a generic type (GenericClassName = `'GEN_AD_SPLIT'`), which allows reuse with different adapter variants.
- **Unidirectional Adapters**: All adapters used are unidirectional (direction from the socket to the plugs).
- **No Internal States**: There is no state machine – the outputs are continuously derived from the input.
- **Type Hash**: An empty type hash (`''`) is set, but can be used for version control if needed.

---

## State Overview

The function block has no states or state machines. Its behavior is purely combinatorial: As soon as a valid signal is present at the input, it is immediately mirrored to all outputs.

---

## Application Scenarios

- **Distributing Sensor Data**: A single sensor (e.g., speed, pressure) should supply several independent evaluation units in parallel.
- **Parallel Operation of Actuators**: A control signal is simultaneously transmitted to several identical actuators (e.g., valves, motors).
- **Redundancy Setup**: The same data stream is sent to multiple redundant processing paths.
- **Test and Simulation Environments**: A simulated adapter signal is distributed across various test modules.

---

## Comparison with Similar Components

| Component | Number of Outputs | Special Feature |
----------|-----------------|--------------|
| `AD_SPLIT_2` | 2 | Simple 1:2 distribution |
| `AD_SPLIT_4` | 4 | Typical for 4-channel systems |
| **`AD_SPLIT_7`** | **7** | Extended distribution for seven parallel paths |
| `AD_MERGE` | – | Combines multiple inputs into one output |

Unlike a merge function block, `AD_SPLIT_7` is used exclusively for duplicating a signal without combining data.

---

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

AD_SPLIT_7` is a simple yet useful function block for passive signal duplication in adapter-based 4diac applications. Its generic nature and independence from events make it ideal for pure dataflow architectures. For applications requiring a higher number of parallel outputs, the function block can be extended by adjusting the GenericClassName.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
