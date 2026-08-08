# AIWS_WSTRING_AX_SEL_AIWS

![AIWS_WSTRING_AX_SEL_AIWS](./AIWS_WSTRING_AX_SEL_AIWS.svg)

* * * * * * * * * *
## Introduction

The function block `AIWS_WSTRING_AX_SEL_AIWS` is a composite function block for the 4diac IDE. It performs binary selection between two `WSTRING` input signals based on a selection signal (`G`).

This block combines classic IEC 61499 events and data variables with modern, unidirectional adapters. It enables clean, event-driven signal switching directly within the control network.


## Interface Structure

### **Event Inputs**

* **EI1**: Updates and adopts the value at data input `IN1`.

### **Event Outputs**

* *No direct event outputs are available. Event output is encapsulated via the output adapter `OUT`.*

### **Data Inputs**

* **IN1** (`WSTRING`): Freely selectable data input that is read when an event occurs at `EI1`.

### **Data Outputs**

* *No direct data outputs are available. Data is transmitted in an encapsulated manner via the output adapter `OUT`.*

### **Adapter**

* **OUT** (Plug, Type: `adapter::types::unidirectional::AIWS`): The selected output as a unidirectional adapter. This output carries the selected `WSTRING` value (`D1`) and the corresponding update event (`E1`).

* **IN0** (Socket, Type: `adapter::types::unidirectional::AIWS`): The default selected input (unidirectional adapter) that provides the alternative `WSTRING` value.

* * **G** (Socket, Type: `adapter::types::unidirectional::AX`): The selector input (unidirectional adapter) determines which of the two inputs is enabled.

---

## Functionality

The module's internal network (`FBNetwork`) manages the synchronization and logical selection of signals:

1. **Buffering & Synchronization:**

The input values of `IN0` (via the adapter), `IN1` (via the local data input), and the selector `G` are buffered in internal memory modules (`E_D_FF_ANY` and `E_D_FF`, respectively) upon the arrival of a corresponding event. This ensures that data and events are processed synchronously.


The input values of `E_D_FF_ANY` and `E_D_FF`, respectively, are buffered when a corresponding event occurs. 2. **Value Transfer:**

The buffered data is transferred to the central selection block via conversion and assignment elements (`F_MOVE_IN0` and `F_MOVE_IN1`).

3. **Selection Logic (`F_SEL`):**

A standard selection block (`iec61131::selection::F_SEL`) performs the selection:

* If the state of selector `G` is equal to `FALSE`, the value of **IN0** is passed to the output.

* If the state of selector `G` is equal to `TRUE`, the value of **IN1** is selected.


* 4. **Output:**

The selected `WSTRING` value is passed via an output buffer (`E_D_FF_ANY_OUT`) to the output adapter `OUT`. Simultaneously, the output event `OUT.E1` is triggered to inform subsequent program components of the change.



       +-------------+
IN0 -->|             |
       |    F_SEL    |--> OUT (Wenn G = FALSE -> IN0)
IN1 -->|             |--> OUT (Wenn G = TRUE  -> IN1)
       +-------------+
              ^
              |
        G (Selector)



---

## Technical Features

* **Mixed Operation:** This function block cleverly combines classic IEC 61499 data and event elements (for `IN1` / `EI1`) with modern adapter structures (`IN0`, `G`, `OUT`).

* **Data Consistency:** The use of internal D flip-flops (`E_D_FF_ANY`) ensures that only consistent and stable data states are passed to the output and that no race conditions occur.

## State Overview

Since this is a composite function block (FB), it does not have its own Execution Control Chart (ECC). The behavior is purely data- and event-driven and depends on the states of the internal signal connections.

## Application Scenarios

* **Dynamic Text Switching:** Switching status messages, recipe names, or error messages in the `WSTRING` format on an HMI or display.

* **Default Value Override:** Providing a default path or value via the `IN0` adapter, which can be overwritten by the signal at `IN1` if needed (e.g., during setup or user interaction).


## Comparison with Similar Building Blocks

Compared to the basic standard selection block `F_SEL` from the IEC 61131-3 library, `AIWS_WSTRING_AX_SEL_AIWS` offers direct integration into adapter-based architectures. Developers do not need to manually decouple or merge events and data using auxiliary blocks, as this block handles encapsulation and synchronization internally and fully automatically.

## Conclusion

`AIWS_WSTRING_AX_SEL_AIWS` is a robust and ready-to-use auxiliary block for structured application development in 4diac. It is ideally suited for modular architectures where strings need to be switched flexibly and event-driven.