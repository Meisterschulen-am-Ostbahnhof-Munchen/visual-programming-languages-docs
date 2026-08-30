# AIWS_SPLIT_6

![AIWS_SPLIT_6](./AIWS_SPLIT_6.svg)

* * * * * * * * * *
## Introduction

The AIWS_SPLIT_6 function block is used to distribute an incoming AIWS signal (adapter type) to six identical outputs. It is designed as a generic function block and enables simple signal multiplication in control applications based on the 4diac IDE framework.
## Interface Structure

### **Event Inputs**

None.

### **Event Outputs**

None.

### **Data Inputs**

None.

### **Data Outputs**

None.

### **Adapters**

**Socket (Input):**

- `IN` (Type: `adapter::types::unidirectional::AIWS`): Input adapter for the AIWS signal to be distributed.

**Plugs (Outputs):**

- `OUT1` (Type: `adapter::types::unidirectional::AIWS`): First output with the split signal.
- `OUT2` (Type: `adapter::types::unidirectional::AIWS`): Second output.
- `OUT3` (Type: `adapter::types::unidirectional::AIWS`): Third output.
- `OUT4` (Type: `adapter::types::unidirectional::AIWS`): Fourth output.
- `OUT5` (Type: `adapter::types::unidirectional::AIWS`): Fifth output.
- `OUT6` (Type: `adapter::types::unidirectional::AIWS`): Sixth output.

## Functionality

The AIWS_SPLIT_6 module receives the AIWS signal present at its socket `IN` and forwards it unchanged to all six plug outputs `OUT1` to `OUT6`. No signal processing or modification takes place; the module functions as a passive splitter (1:6). Communication occurs via adapters according to the unidirectional AIWS interface definition.

## Technical Features

- The function block is implemented as a generic function block, identifiable by the attributes `GenericClassName` and `TypeHash`. This allows it to be created in various forms (e.g., AIWS_SPLIT_2, AIWS_SPLIT_4) as an instance of a generic type.
- There are no event or data inputs/outputs; all data transmission occurs exclusively via the adapter interfaces.
- The function block does not contain its own state logic or processing algorithms.

## State Overview

The function block has no defined states, as it does not require event-driven execution. Signal propagation is continuous and passive.

## Application Scenarios

- Distribution of an analog input signal (e.g., from a sensor) to multiple downstream function blocks.
- Provision of a reference signal for multiple parallel control loops.
- Use in modular automation solutions that require signal multiplication without additional hardware.

## Comparison with similar function blocks

- **AIWS_SPLIT_2, AIWS_SPLIT_4:** These function blocks distribute the signal to two and four outputs, respectively. AIWS_SPLIT_6 extends the number to six.
- **AIWS_MERGE:** A compound function block that combines multiple AIWS inputs into one output – the functional inverse of a splitter.
- **Direct connection:** Instead of a splitter function block, multiple parallel connections could be made in the application model, but this reduces clarity and is more complex to modify.

## Change Detection

Each output plug is updated independently: the incoming value is written to a given output, and its adapter event sent, only if it differs from that output's current value. Outputs that are already in sync stay quiet, while an output that was just connected (or has drifted out of sync) still receives the update it needs.


## Conclusion

The AIWS_SPLIT_6 is a simple yet useful function block for multiplying AIWS signals in IEC 61499-based controllers. Its generic nature and clear adapter interface facilitate reuse and integration into larger projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
