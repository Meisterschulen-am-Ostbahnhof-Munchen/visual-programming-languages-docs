# ALR_D_FF

![ALR_D_FF](./ALR_D_FF.svg)

* * * * * * * * * *

## Introduction

The function block **ALR_D_FF** implements a data-driven flip-flop (D-latch) with an adapter-based interface. It takes a data value on a clock event and makes it available at the output. The block encapsulates the IEC 61499 standard function `E_D_FF_ANY` and offers a unidirectional adapter connection for modular system integration.

## Interface Structure

The function block has no direct event or data inputs/outputs. All communication takes place via two adapters:

### **Event Inputs**

- **I.E1** (via socket `I`): Clock event – the current data value is taken on a rising edge.

### **Event Outputs**

- **Q.E1** (via plug `Q`): Acknowledge event – sent after successful data value transfer.

### **Data Inputs**

- **I.D1** (via socket `I`): Data input – the value to be latched (data type is defined by adapter `ALR`).

### **Data Outputs**

- **Q.D1** (via plug `Q`): Data output – the stored, latched value.

### **Adapters**

| Adapter | Type | Direction | Description |
| ---------- | -------------------------- | ---------- | ---------------------------------- |
| `I` | adapter::types::unidirectional::ALR | Socket (Input) | Returns the clock event and the data value. |
| `Q` | adapter::types::unidirectional::ALR | Plug (Output) | Outputs the output event and the latched value. |

## Functionality

1. The function block expects a clock event at the adapter input `I.E1`.
2. Simultaneously, the data value from `I.D1` is read.
3. The internal function block `E_D_FF_ANY` receives the data value on the rising edge of the clock signal.
4. The received value is output unchanged to `Q.D1`.
5. An output event on `Q.E1` signals that the new value is ready.

This process repeats with each subsequent clock event. The output value remains stable between clock cycles (latch behavior).

## Technical Features

- **Adapter-based interface**: The function block (FB) uses the unidirectional adapter `ALR`, which carries exactly one event and one data value. This enables loose coupling and easy interconnection with other adapter blocks.
- **Delegation to IEC 61499 standard**: The actual flip-flop logic is implemented by the standard FB `E_D_FF_ANY`, which is designed for any data type ("ANY"). `ALR_D_FF` therefore inherits its robustness and type neutrality.
- **No dedicated state machine**: The function block (FB) does not have an internal state machine – state management is handled entirely within the embedded `E_D_FF_ANY`.

## State Overview

The function block has no explicit states. The internal logic (flip-flop) only recognizes two implicit states:

- **Waiting for clock event**: The output retains the last latched value.
- **Latch moment**: Upon a clock event, the input value is adopted and the output is updated.

## Application Scenarios

- **Data storage**: Holding a digital signal (e.g., switch position) until the next query.
- **Synchronization**: Transferring asynchronous data into a clocked context.
- **Buffering**: Temporarily storing values in control sequences, e.g., in state machines or sequence controllers.

## Comparison with Similar Components

- **`ALR_SR_FF`** (Set-Reset Flip-Flop): Offers two control inputs (Set/Reset) instead of a clock input. Suitable for priority-driven applications.
- **`ALR_JK_FF`** (JK Flip-Flop): More complex switching behavior with toggling and holding. More flexible, but more expensive.
- **`E_D_FF_ANY`** (Direct): Offers the same functionality, but with separate event and data inputs/outputs instead of an adapter. The `ALR_D_FF` simplifies coupling in adapter-based frameworks.

## Conclusion

The `ALR_D_FF` is a lean yet reliable D flip-flop component for use in adapter-oriented 4diac applications. It combines proven IEC 61499 standard logic with a clearly structured adapter interface and is particularly suitable for modular, reusable control systems.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
