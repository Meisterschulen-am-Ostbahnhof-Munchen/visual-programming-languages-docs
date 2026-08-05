# AD_TO_ALI
![AD_TO_ALI](./AD_TO_ALI.svg)

* * * * * * * * * *
## Introduction
The **AD_TO_ALI** is a composite function block for the unidirectional conversion of a DWORD value (via an AD adapter) to a LINT value (via an ALI adapter). The conversion is performed using the integrated standard function block `F_DWORD_TO_LINT`. The block enables simple and standardized integration of components that exchange different data types via adapter interfaces.
## Interface Structure
### **Event Inputs**
No separate event inputs are available. Event control is handled via the **AD_IN** adapter (event *E1*).

### **Event Outputs**
No separate event outputs are available. Output events are provided via the **ALI_OUT** adapter (event *E1*).

### **Data Inputs**
No separate data inputs are available. The input data (DWORD) is obtained via the **AD_IN** adapter (Data *D1*).

### **Data Outputs**
No separate data outputs are available. The output data (LINT) is output via the **ALI_OUT** adapter (Data *D1*).

### **Adapters**

| Adapter | Type | Direction | Description |

|---------|-----|----------|--------------|

| **AD_IN** | `adapter::types::unidirectional::AD` | Socket | Receives a DWORD value (*D1*) and an input event (*E1*). |

| **ALI_OUT** | `adapter::types::unidirectional::ALI` | Plug | Sends the converted LINT value (*D1*) and an output event (*E1*).

## Functionality
The function block waits for an event at the **AD_IN** adapter (event *E1*). As soon as this event arrives, the currently incoming DWORD value (Data *D1*) is read from the adapter and passed to the internal function block **Convert** (type `F_DWORD_TO_LINT`). This block performs the data type conversion. After successful conversion, the resulting LINT value is passed to the **ALI_OUT** adapter (Data *D1*), and an event (*E1*) is triggered for confirmation.

## Technical Features
- **Pure Composite Logic**: The function block does not contain its own state machine but implements the conversion exclusively through the interconnection of the embedded function block `F_DWORD_TO_LINT`.
- **Standard Compliance**: The conversion function used complies with IEC 61131-3 (type conversion `DWORD_TO_LINT`).
- **Synchronization**: Events and data are forwarded from input to output within a single execution cycle (E1 → REQ → CNF → E1).

## State Overview
As a composite function block, **AD_TO_ALI** does not have its own state machine. Its behavior is determined solely by its internal interconnection and the states of the function block `F_DWORD_TO_LINT`. A graphical state overview is not provided.

## Application Scenarios
- **Industrial Automation**: Conversion of DWORD-based sensor data (e.g., counter readings) into LINT values for further processing in systems with 64-bit integers.

## - **Memory Addressing**: Conversion of 32-bit addresses (DWORD) to 64-bit addresses (LINT) for large memory areas.
- **Data Integration**: Connecting components that use different adapter protocols via a standardized conversion interface.

## Comparison with Similar Function Blocks
Analog conversion function blocks such as `AD_TO_ALI` exist for other data types (e.g., `AD_TO_ALI` for DWORD→LINT, `AI_TO_ALI` for INT→LINT). This function block specifically covers the conversion from **DWORD** to **LINT** and is optimized for this combination. It does not replace the general `F_DWORD_TO_LINT` function, but rather encapsulates it in an adapter-based interface.

## Conclusion

The **AD_TO_ALI** offers a clean, reusable solution for converting DWORD adapters to LINT adapters. Thanks to its composite structure, the logic remains transparent and easily integrated into existing 4diac projects. It is particularly suitable for scenarios requiring a uniform adapter interface but needing to combine different data types.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
