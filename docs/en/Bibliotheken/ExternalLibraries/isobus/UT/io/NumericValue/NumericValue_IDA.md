# NumericValue_IDA

* * * * * * * * * *

## Introduction

The function block **NumericValue_IDA** is a service interface function block specifically designed for processing numeric input data (double word input data) in the context of ISOBUS universal terminals (UTs). It serves to transfer changes to numeric values made on a user interface (e.g., a tractor terminal) into the control logic.

Unlike standard input blocks, this block does not provide the received data via direct data outputs, but rather via an adapter connection (`IN`). It encapsulates the functionality of the block `NumericValue_ID` and redirects its signals to an adapter interface.


![NumericValue_IDA](NumericValue_IDA.svg)

## Interface Structure

The function block has standard initialization and request events as well as specific configuration parameters. The actual data transfer takes place via the adapter.

### **Event Inputs**

* **INIT** (Type: `EInit`): Service initialization. Used to start and configure the function block.

* **REQ** (Type: `Event`): Service request. Can be used to update the status or request a specific interaction (depending on the internal implementation of the service layer).

### **Event Outputs**

* **INITO** (Type: `EInit`): Initialization confirmation. Indicates whether the function block has been successfully configured.


### **Data Inputs**

* **QI** (Type: `BOOL`): Event Input Qualifier. Enables the execution of actions associated with the events.

* **PARAMS** (Type: `STRING`): Service parameter for specific configurations of the underlying service layer.

* **u16ObjId** (Type: `UINT`): Object ID. References the specific numeric input object on the Universal Terminal (UT) whose value is to be monitored. The default value is `ID_NULL`.

### **Data Outputs**

* **QO** (Type: `BOOL`): Event Output Qualifier. Indicates whether the last operation (e.g., initialization) was successful.

* **STATUS** (Type: `STRING`): Service status. Contains error codes or status messages for diagnostic purposes.

### **Adapter**

* **IN** (Type: `adapter::types::unidirectional::AD`):

* This is a unidirectional adapter plug ("Input data from resource").

* It combines the event signal (E1) and the data signal (D1), which contains the current numeric value from the terminal.

* The adapter is triggered when the internal `NumericValue_ID` block sends a `IND` (Indication) or `CNF` (Confirmation) event.

## Functionality

The **NumericValue_IDA** acts as a wrapper for the internal block `NumericValue_ID`.

1. **Initialization:** The connection to the specific object on the ISOBUS terminal is established via the event `INIT` and the data inputs `PARAMS` and `u16ObjId`.

2. **Data Reception:** When the value of the referenced object on the terminal changes or is updated by the system, the internal block receives this information.

3. **Forwarding:** The internal block forwards the new value (`IN`) and the associated event to the adapter `IN` of the **NumericValue_IDA**.

* The adapter's event `E1` is triggered.

* The adapter's data point `D1` provides the numerical value.

This mechanism enables clean encapsulation of communication, where the application logic only needs to connect to the adapter `IN` to react to value changes.

## Technical Features

* **Composition:** The function block is implemented as a composite function block (FB) that uses instances from the package `isobus::UT::io::NumericValue`.

* **Adapter Usage:** The special feature lies in the use of the adapter `AD` for data output. This reduces the visual complexity in the function block diagram, as data and event flow are bundled in a single connection line.

* **ISOBUS Context:** This function block is explicitly designed for use in the ISOBUS stack (ISO 11783), as indicated by the use of `u16ObjId` to identify UT objects.

## Status Overview

Since this is a composite function block, its status is primarily determined by its internal service blocks.

* **Not Initialized:** After startup or during `QI=FALSE` and `INIT`.

* **Initialized / Ready:** After successful `INIT` (`QO=TRUE`). The function block listens for updates from the terminal.


* * **Error:** If `QO=FALSE` and `STATUS` contain an error message (e.g., invalid object ID).

## Application Scenarios

* **Setpoint Input:** An operator enters a quantity (e.g., application rate in liters) or a target speed on the terminal. This function block receives the value.

* **Parameterization:** Setting machine parameters via numeric fields on the display.

* **Modular Applications:** Used in applications that rely heavily on adapter connections to avoid the "spaghetti code" of parallel event and data lines.

## ⚖️ Comparison with Similar Function Blocks

* **NumericValue_ID:** This is the internal base function block. It offers the same functionality but provides the data via classic `IND`/`CNF` events and a `IN` data output. **NumericValue_IDA** is the adapter version of this function block.

* **Other `_IDA` function blocks:** Similar to `Button_IDA` (for buttons) or `String_IDA` (for text), this function block follows the design pattern of providing terminal input via adapters.

* ## 🛠️ Related Exercises

* [Exercise_011_AUDI](../../../../../../Uebungen/test_AX/Uebungen_doc/Uebung_011_AUDI.md)

## Conclusion

The **NumericValue_IDA** is a specialized interface block for ISOBUS applications in 4diac. By using an adapter for data output, it enables compact and clear routing of numerical input values in the function block diagram. It is ideally suited for developers who prefer a structured and modular application architecture and need to process numerical input from the Universal Terminal.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)


```