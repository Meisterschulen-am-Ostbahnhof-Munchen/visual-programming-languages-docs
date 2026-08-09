# ADI_MUX_5

![ADI_MUX_5](./ADI_MUX_5.svg)

* * * * * * * * * *
## Introduction

The **ADI_MUX_5** is a generic multiplexer function block that selects a single ADI adapter output (OUT) from five ADI adapter inputs (IN1 to IN5). Selection is event-driven via the parameter `K` (index). This function block is particularly suitable for the flexible switching of analog or digital signal sources in automation applications.
## Interface Structure

### **Event Inputs**

- **REQ** (Event) – Trigger to set the index `K` and switch the corresponding input to the output.

### **Event Outputs**

- **CNF** (Event) – Confirmation that the selection process is complete.

### **Data Inputs**

- **K** (`UINT`, with *REQ*) – Index of the input to be selected (0 = IN1, 1 = IN2, …, 4 = IN5).

### **Data Outputs**

- No dedicated data outputs are available; the output data is transmitted via the adapter output `OUT`.

### **Adapter**

- **IN1** – ADI adapter (socket) – Input signal 1
- **IN2** – ADI adapter (socket) – Input signal 2
- **IN3** – ADI adapter (socket) – Input signal 3
- **IN4** – ADI adapter (socket) – Input signal 4
- **IN5** – ADI adapter (socket) – Input signal 5
- **OUT** – ADI adapter (plug) – Output signal (corresponds to the selected input)

## Functionality

1. An event at the event input **REQ** is received.
2. The value of the data input **K** is read.
3. The function block connects the corresponding ADI input (IN1 at K=0, IN2 at K=1, … IN5 at K=4) to the ADI output **OUT**.
4. After successful switching, the confirmation event **CNF** is sent.

The selection is synchronous with the REQ event; there is no cyclic query.

## Technical Features

- **Generic Block**: The function block can be derived from a specific, type-safe multiplexer (e.g., `GEN_ADI_MUX`) via the attribute `eclipse4diac::core::GenericClassName`.
- **Adapter-Based Interface**: The use of the ADI adapter type (unidirectional) allows for flexible connection of different signal sources without specifying the actual data types.
- **Compact Index Logic**: Input K is defined as `UINT` – values outside the valid range (0…4) lead to undefined behavior; safeguards should be implemented in the application.

## State Overview

The function block has **no explicit state machine** (ECC). It reacts purely event-driven: Each REQ event triggers a one-time selection process, after which CNF is immediately output. The internal state corresponds to the last set index **K**.

## Application Scenarios

- **Sensor Switching**: Selection between different analog sensors (e.g., temperature, pressure, level) on a common evaluation channel.
- **Signal Prioritization**: Dynamic switching to redundant or alternative signals in case of a source failure.
- **Modular Controls**: Use within function block libraries where the number of inputs can be varied by generation.

## Comparison with Similar Function Blocks

- **MUX_2 / MUX_4 (Standard IEC 61499)**: These multiplexers operate with fixed data types (e.g., `ANY`) and have separate data outputs. The ADI_MUX_5, on the other hand, uses adapters and is specialized for the ADI type.
- **Generic ADI MUX (derived)**: The generic base allows for the creation of specializations with a different number of inputs (e.g., ADI_MUX_3, ADI_MUX_8) without reimplementing the logic.
- **Difference to Select Function Blocks**: Select function blocks typically operate bitwise or on scalars; ADI_MUX_5 transmits complete adapter data streams.

## Conclusion

The **ADI_MUX_5** is a compact, generic multiplexer for ADI adapters in the 4diac IDE. Its adapter-based interface and simple index control make it a practical tool for flexible signal selection in control applications. The ability to generate a GenericClassName allows for type-safe adaptation to specific projects.

---

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
