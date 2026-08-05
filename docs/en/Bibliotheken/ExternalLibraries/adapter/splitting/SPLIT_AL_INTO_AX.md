# SPLIT_AL_INTO_AX
![SPLIT_AL_INTO_AX](./SPLIT_AL_INTO_AX.svg)

* * * * * * * * * *
## Introduction
The **SPLIT_AL_INTO_AX** function block decomposes a value encoded as an LWORD (64-bit) into 64 individual BOOL signals. The input value is provided via an **AL adapter** (analog longword), and the output is provided via 64 separate **AX adapters** (analog bits). Each output adapter provides the status of a bit along with a corresponding event. This function block is particularly suitable for processing digital signals from a compact data word, e.g., for the parallel control of 64 discrete outputs.
## Interface Structure
### **Event Inputs**
- **IN.E1** (in the IN adapter): Starts processing as soon as a new LWORD value is present at the adapter.

### **Event Outputs**
Each AX adapter provides an event output:

- **BIT_00.E1** .. **BIT_63.E1** (in the corresponding adapters): Triggered as soon as the associated bit in the internal flip-flop is updated.

### **Data Inputs**
- **IN.D1** (LWORD): The 64-bit data set to be parsed.

### **Data Outputs**
- **BIT_00.D1** .. **BIT_63.D1** (BOOL): The state of the respective bit (0 or 1).

### **Adapters**
- **IN** (Socket, Type: `adapter::types::unidirectional::AL`): Returns the LWORD value and the start event.
- **BIT_00** .. **BIT_63** (Plugs, Type: `adapter::types::unidirectional::AX`): Each outputs a BOOL signal (bit value) and an associated event.

## Functionality

1. An incoming LWORD value via the AL adapter **IN** triggers processing via the **E1** event.

2. The internal component **SPLIT_LWORD_INTO_BOOLS** extracts all 64 bits from the LWORD.

3. Each bit is assigned to the **D** data input of an associated **E_D_FF** (Edge-Triggered D Flip-Flop).

4. Simultaneously, all 64 flip-flops receive the **CLK** clock pulse via the **CNF** event of the splitter. This transfers all bits to the flip-flops at once.

5. The flip-flops output the stored value at their output **Q**, which is provided via the data output **D1** of the respective AX adapter.

6. Each flip-flop generates an event at its output **EO**, which is forwarded to the event input **E1** of the corresponding AX adapter.

## Technical Features
- **Synchronization**: All bits are transferred to the flip-flops simultaneously via a common event (CNF of SPLIT_LWORD_INTO_BOOLS). This ensures a consistent output state without race conditions.
- **Storage**: The use of **E_D_FF** ensures that the output state is retained until a new LWORD value is processed. The function block thus operates as a "sample and hold" for all 64 bits.
- **Large Number of Outputs**: The function block offers 64 independent BOOL outputs, which can be mapped to many device adapters in the 4diac IDE.
- **Adapter-based interface**: Inputs and outputs are implemented as unidirectional adapters, which facilitates modular encapsulation and reuse.

## State overview
The function block (FB) does not have its own explicit state machine. The internal state is represented by the 64 **E_D_FF**:

- **Initial**: All flip-flops are set to FALSE (0).
- **After processing**: Each flip-flop stores the current bit value of the last received LWORD. The state changes only upon a new event on **IN.E1**.

## Application scenarios
- **Parallel output of digital signals** from a serial or packetized data word, e.g., from a bus system or a communication interface.
- **Masked control**: Combination with logic blocks to selectively evaluate individual bits of a status word.
- **Test and Diagnostic Interfaces**: Processes a 64-bit error word for display on separate lights or in visualizations.
- **Interface to Discrete Actuators**: Each AX adapter can be directly connected to a digital output module.

## Comparison with Similar Components
- **SPLIT_LWORD_INTO_BOOLS** (purely functional splitter without memory): Provides the bits only during processing and does not retain the value. **SPLIT_AL_INTO_AX** adds the memory function and provides a stable output until the next update.
- **Type Converters like DWORD_TO_BOOL_ARRAY**: These usually operate at the array level and not at the adapter level; the present component is specifically designed for the 4diac adapter interface.
- **Flip-flop-based solutions, each with its own F_TRIG or similar:** This function block simplifies configuration because all 64 bits are combined in a single block.

## Conclusion

**SPLIT_AL_INTO_AX** is a powerful, adapter-based function block for splitting an LWORD data set into 64 discrete BOOL signals. The integrated flip-flops maintain the output state until the next update. The large number of outputs and synchronous processing make it ideal for applications requiring parallel, time-consistent signal generation. The use of unidirectional adapters ensures clear interface definition and facilitates integration into existing 4diac projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
