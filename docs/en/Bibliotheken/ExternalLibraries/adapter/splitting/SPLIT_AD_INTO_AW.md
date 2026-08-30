# SPLIT_AD_INTO_AW

![SPLIT_AD_INTO_AW](./SPLIT_AD_INTO_AW.svg)

* * * * * * * * * *

## Introduction

The function block **SPLIT_AD_INTO_AW** is used to split a 32-bit DWORD value, received via a **AD** adapter (unidirectional), into two 16-bit WORD values and output them via two separate **AW** adapters (unidirectional). The splitting is event-driven, and the output data is stabilized by flip-flops until a new trigger arrives. The function block is implemented as a composite function block and internally uses the **SPLIT_DWORD_INTO_WORDS** function block as well as two **E_D_FF_ANY** flip-flops.

## Interface Structure

### **Event Inputs**

| Name | Adapter | Event | Description |
|-------------|---------|----------|-----------|
| IN | AD (Socket) | E1 | Starts the partitioning of the incoming DWORD value. |

### **Event Outputs**

| Name | Adapter | Event | Description |
| ------------- | --------- | ---------- | ------------ |
| WORD_00 | AW (Plug) | E1 | Signals that the lower-order WORD (low word) is valid. |
| WORD_01 | AW (Plug) | E1 | Indicates that the higher-order WORD (High Word) is valid. |

### **Data Inputs**

| Name | Adapter | Data Type | Description |
|-------------|---------|----------|------------|
| IN | AD (Socket) | D1 (DWORD) | 32-bit input value that is split. |

### **Data Outputs**

| Name | Adapter | Data Type | Description |
| ------------- | --------- | ---------- | ------------- |
| WORD_00 | AW (Plug) | D1 (WORD) | Low-order 16-bit word of the input DWORD. |
| WORD_01 | AW (Plug) | D1 (WORD) | High-order 16-bit word of the input DWORD. |

### **Adapters**

The adapters are designed as **unidirectional**:

- **AD** (Input): Provided via a socket, containing one event (E1) and one data (D1) channel.
- **AW** (Output): Provided via two plugs, each with one event (E1) and one data (D1) channel.

## Functionality

1. An event at input **IN.E1** triggers processing.
2. The current DWORD value of **IN.D1** is read and passed to the internal function block **SPLIT_DWORD_INTO_WORDS**.
3. This block splits the 32-bit value into two 16-bit words: **WORD_00** (lower order) and **WORD_01** (higher order).
4. The two results are transferred in parallel to the flip-flops **E_D_FF_ANY_00** and **E_D_FF_ANY_01** and held there until the next event.
5. Simultaneously, the output events **WORD_00.E1** and **WORD_01.E1** are triggered, indicating that the corresponding data (**WORD_00.D1** and **WORD_01.D1**) are valid.

...

## Technical Features

- **Data Synchronization:** The flip-flops ensure that the output data remains stable, even if the input value changes between two events. Only a new event at the input updates both outputs.
- **Simultaneous Output:** Both WORD outputs are updated by the same input event – there is no staggered timing.
- **Adapter Compatibility:** The function block is specifically designed for use with **AD-** and **AW-** adapters and allows seamless integration into adapter-based data flows.

## State Overview

The function block does not have an explicit state machine. Its behavior is purely event-driven:

- **Idle:** Waiting for an event at **IN.E1**.
- **Processing:** Upon receipt of **IN.E1**, the data is split and the flip-flops are set.
- **Output:** The events at the outputs are triggered exactly once after processing.

## Application Scenarios

- **Adapter-Based Decomposition:** Splitting a 32-bit value (e.g., from a sensor data word) into two 16-bit parts for separate processing chains.
- **Communication Protocols:** Preparing data for interfaces that transmit WORD-wise (e.g., Modbus registers or CAN messages).
- **Bit Manipulation:** Preprocessing for subsequent components that only expect WORD adapters.

## Comparison with Similar Components

| Component | Description | Difference |
| ---------- | -------------- | ------------- |
| **SPLIT_DWORD_INTO_WORDS** | Pure data splitting without event output or adapters. | Provides only data outputs, no events, and no adapter connectivity. |
| **SPLIT_AD_INTO_AW** | Adapter-based variant with stabilized outputs. | Integrates flip-flops and event output, specifically for AD/AW adapters. |

## Conclusion

**SPLIT_AD_INTO_AW** is a practical, combined function block that simplifies the splitting of a DWORD adapter signal into two WORD adapter signals. Thanks to its built-in flip-flops and synchronized event output, it is particularly well-suited for time-critical and adapter-oriented applications in industrial control systems.
