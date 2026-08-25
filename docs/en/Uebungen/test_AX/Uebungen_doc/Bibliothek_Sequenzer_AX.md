# 📚 Libraries: Sequencer (AX Adapter)

This section describes the sequencer blocks available in the logiBUS® library that are optimized for use with the **AX Adapter**.
---
## ℹ️ General Information

The sequencer blocks enable the implementation of sequential function charts (SFCs). The AX versions are distinguished by their use of **AX Adapters** (plug/socket) for controlling the outputs. This significantly reduces wiring effort, as status events and data bits are bundled in a single connection.

---

## ⚙️ Event-driven sequencers (`sequence_ET_xx_AX`)

These function blocks advance to the next step when either an external event (`S1_S2`, `S2_S3`, etc.) occurs or a defined time (`DT_S*_S*`) has elapsed.

### Available types

- `sequence_ET_04_AX`: 4 steps, 4 outputs.
- `sequence_ET_04_loop_AX`: 4 steps, cyclic (loop).
- `sequence_ET_05_AX`: 5 steps, 5 outputs.
- `sequence_ET_05_loop_AX`: 5 steps, cyclic.
- `sequence_ET_08_AX`: 8 steps, 8 outputs.
- `sequence_ET_08_loop_AX`: 8 steps, cyclic.

--

## ⚙️ Time-controlled sequencers (`sequence_T_xx_AX`)

These function blocks advance automatically after the time defined for the respective step has elapsed.

### Available types

- `sequence_T_04_AX`: 4 steps, time-controlled.
- `sequence_T_04_loop_AX`: 4 steps, cyclic.
- `sequence_T_05_AX`: 5 steps, time-controlled.
- `sequence_T_05_loop_AX`: 5 steps, cyclic.
- `sequence_T_08_AX`: 8 steps, timed.
- `sequence_T_08_loop_AX`: 8 steps, cyclic.

--

## ⚙️ Pattern Sequencers (Cam Switches)

The pattern sequencers (`sequence_Pattern_xx_AX`) allow you to define an individual bit pattern for the outputs for each step. This is ideal for applications where multiple actuators need to be switched simultaneously in specific patterns within a single step.

### Available Types

- **[sequence_Pattern_04_04_loop_AX](../../../Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/pattern/sequence_Pattern_04_04_loop_AX.md)**: 4 steps, 4 outputs, cyclic.
- **[sequence_Pattern_08_08_loop_AX](../../../Bibliotheken/ExternalLibraries/logiBUS/utils/sequence/pattern/sequence_Pattern_08_08_loop_AX.md)**: 8 steps, 8 outputs, cyclic.

### Functionality

Each state `S1` to `Sx` has a corresponding input `P_S1` to `P_Sx` of type `BYTE`. The individual bits of this byte control the adapter outputs `Q1` to `Qx`:

- Bit 0 -> Output Q1
- Bit 1 -> Output Q2
- ...and so on.

Upon transitioning to a new state, the corresponding pattern is immediately applied to the outputs.

---

## ⚙️ Pure Event Sequencers (`sequence_E_xx_AX`)

Unlike the `ET` series, these components **do not have integrated timing**. Advancement occurs exclusively via external event signals.

### Available Types

- `sequence_E_04_AX`: 4 steps.
- `sequence_E_04_loop_AX`: 4 steps, cyclic.
- `sequence_E_05_AX`: 5 steps.
- `sequence_E_05_loop_AX`: 5 steps, cyclic.
- `sequence_E_08_AX`: 8 steps.
- `sequence_E_08_loop_AX`: 8 steps, cyclic.

---

## ⚙️ Specialized Sequence Blocks

In addition to the universal step sequences, there are specialized blocks for frequently occurring tasks.

### Slide Control (`SchieberControl_AX`)

This block is used for the sequential control of slides or valves with end-position feedback. It combines the logic for opening/closing and monitoring the runtime.

### Left-Right Diverter (`LinksRechts_AX`)

Specialized block for applications such as conveyor belts or diverters that need to switch between two directions or states, including the necessary interlocks and switching pauses.

--

## 🔌 Interface Description (Example AX)

| Connection | Type | Description |
| :--- | :--- | :--- |
| **Plugs (Outputs)** | `adapter::types::unidirectional::AX` | Bundled outputs for data and events. |
| **START_S1** | `Event` | Starts the sequence in the first step. |
| **RESET** | `Event` | Immediately resets the sequence to the initial state (START). |
| **STATE_NR** | `SINT` | Current step number (0 = START, 1 = S1, ...). |
| **timeOut** | `adapter` | Adapter for connecting a timeout management system. |

---

## 🛠️ Related exercises

- [Uebung_035a1_AX](Uebung_035a1_AX.md) (Usage of `sequence_Pattern_04_04_loop_AX`)
- [Uebung_039_AX](Uebung_039_AX.md) (Usage of `sequence_ET_05_AX`)
