Here is the documentation for exercise `Uebung_171_AX` based on the provided data.
# Exercise_171_AX: Exercise for ASR_AX_SR
* * * * * * * * * *
## Introduction
This exercise covers the use of adapters in the context of set/reset logic (SR flip-flops) within a sub-application network. The focus is on converting discrete events (button clicks) into adapter interactions and controlling an SR function block and a digital output via adapter interfaces.
## Function Blocks (FBs) Used

This exercise uses specific function blocks for input processing, adapter conversion, and output control.

### Sub-modules:

### DigitalInput_CLK_I1 & DigitalInput_CLK_I2
- **Type**: `logiBUS::io::DI::logiBUS_IE`
- **Description**: These modules serve as an interface to the physical pushbuttons.

### Sub-modules:

### DigitalInput_CLK_I1 & DigitalInput_CLK_I2
- **Type**: `logiBUS::io::DI::logiBUS_IE`
- **Description**: These modules serve as an interface to the physical pushbuttons. ... - **Parameters**:
- `QI`: `TRUE` (Block is active)
- `Input`: `Input_I1` or `Input_I2` (Input selection)
- `InputEvent`: `BUTTON_SINGLE_CLICK` (Responds to a single click)
- **Event Output**:
- `IND`: Triggers an event when the button is pressed.

### ASR_2EVENTS_TO_SR
- **Type**: `adapter::conversion::unidirectional::ASR_2EVENTS_TO_SR`
- **Description**: A converter block that receives two separate events (Set and Reset) and translates them into adapter communication for SR behavior.
- **Event Input**:
- `SET`: Connected to Button 1.
- `RESET`: Connected to Button 2.
- **Adapter Output**:
- `ASR_OUT`: The adapter interface for transmitting commands.

### ASR_AX_SR_1
- **Type**: `adapter::events::unidirectional::ASR_AX_SR`
- **Description**: This block implements SR logic (Set/Reset) based on adapter inputs.
- **Adapter Input**:
- `S_R`: Receives the set/reset signals from the converter.
- **Adapter Output**:
- `Q`: Transmits the current state.

### DigitalOutput_Q1
- **Type**: `logiBUS::io::DQ::logiBUS_QXA`
- **Description**: This chip controls the physical output but accepts adapter connections.
- **Parameters**:
- `QI`: `TRUE`
- `Output`: `Output_Q1`
- **Adapter Input**:
- `OUT`: Connected to the output of the SR chip.

## Program Flow and Connections

The exercise proceeds as follows:

1. **Input Acquisition**:

* The function block `DigitalInput_CLK_I1` monitors the input `I1`. A click triggers the event `IND`.
* The function block `DigitalInput_CLK_I2` monitors the input `I2`. A click triggers the event `IND`.

2. **Signal Processing and Conversion**:

* The `IND` event of `DigitalInput_CLK_I1` is connected to the input `SET` of the function block `ASR_2EVENTS_TO_SR`.
* The `IND` event from `DigitalInput_CLK_I2` is connected to the input `RESET` of the function block `ASR_2EVENTS_TO_SR`.
* The function block `ASR_2EVENTS_TO_SR` converts these events into commands on the adapter line `ASR_OUT`.

3. **Logic and Output**:

* The adapter connection runs from `ASR_2EVENTS_TO_SR.ASR_OUT` to `ASR_AX_SR_1.S_R`. The state is stored here (set or reset).
* The resulting state is passed on to the output function block `DigitalOutput_Q1.OUT` via the adapter connection `ASR_AX_SR_1.Q`.
* This causes the physical output `Q1` to be activated when `I1` is pressed and deactivated when `I2` is pressed.

**Learning Objectives:**

* Understanding the adapter concept in IEC 61499/4diac.
* Converting event-based logic to adapter-based logic.
* Implementing a memory function (SR) using adapter blocks.

## Summary
The exercise `Uebung_171_AX` demonstrates a modern implementation of a classic memory function. Instead of directly linking signals via Boolean connections, adapters are used to encapsulate the communication between input conversion, logic, and output. This reduces the apparent complexity of the connections and demonstrates the flexibility of the adapter concept for standard automation tasks, such as switching an output using two push buttons.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]