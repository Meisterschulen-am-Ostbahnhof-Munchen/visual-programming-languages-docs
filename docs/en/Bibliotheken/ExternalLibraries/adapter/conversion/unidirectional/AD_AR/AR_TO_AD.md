# AR_TO_AD
![AR_TO_AD](./AR_TO_AD.svg)
* * * * * * * * * *
## Introduction
The function block `AR_TO_AD` serves as a composite function block (FB) for converting a REAL value received via a unidirectional AR adapter into a DWORD value output via a unidirectional AD adapter. The conversion is performed according to IEC 61131-3 using the function block `F_REAL_TO_DWORD`. The FB encapsulates the necessary event and data connections and allows for easy integration into existing adapter-based communication structures.
## Interface Structure
### **Event Inputs**

| Input | Type | Description |

|---------|-----|---------------|

| `AR_IN.E1` | Adapter Event | Receives the trigger event from the AR adapter, which starts the conversion. |

### **Event Outputs**

| Output | Type | Description |

|---------|-----|--------------|

| `AD_OUT.E1` | Adapter Event | Sends an event to the AD adapter as soon as the converted DWORD value is available. |

### **Data Inputs**

| Input | Type | Description |

|---------|-----|--------------|

| `AR_IN.D1` | REAL | The REAL value to be converted, provided by the AR adapter. |

### **Data Outputs**

| Output | Type | Description |

|---------|-----|---------------|

| `AD_OUT.D1` | DWORD | The converted DWORD value that is passed to the AD adapter. |

### **Adapters**
The FB has a **socket** of type `adapter::types::unidirectional::AR` (labeled `AR_IN`) and a **plug** of type `adapter::types::unidirectional::AD` (labeled `AD_OUT`). The actual input and output signals are accessible via the event and data pins of these adapters.

### **Adapters**

The FB has a **socket** of type `adapter::types::unidirectional::AR` (labeled `AR_IN`) and a **plug** of type `adapter::types::unidirectional::AD` (labeled `AD_OUT`). The actual input and output signals are accessible via the event and data pins of these adapters.

#
## **Adapters** ## Functionality

1. The function block (FB) waits for an event at the event input `AR_IN.E1`.

2. Simultaneously, the current value at the data input `AR_IN.D1` (REAL) is retrieved.

3. Internally, the function block `F_REAL_TO_DWORD` (from the IEC 61131-3 library) is called, which performs the conversion.

4. After successful conversion, the resulting DWORD value is assigned to the data output `AD_OUT.D1`.

5. Subsequently, an event is output at the output `AD_OUT.E1` to notify the connected Active Directory adapter.

The entire process occurs synchronously in a single step; that is, the FB is purely event-driven and does not maintain any internal states.

## Technical Features
- **Composite FB:** The logic is implemented exclusively through the combination of the internal `F_REAL_TO_DWORD` function block. There is no separate state machine or complex algorithms.
- **Adapter Coupling:** The function block encapsulates the conversion at the adapter level, allowing it to be integrated into adapter-based architectures (e.g., distributed systems with 4diac) without additional modifications.
- **IEC 61131-3 Compliance:** The actual conversion is performed by a standardized function block, which increases portability and standards compliance.
- **Package Name:** The function block is provided under the package `adapter::conversion::unidirectional` and imports `iec61131::conversion::F_REAL_TO_DWORD`.

## State Overview
Since this is a combinational composite function block, it does not have an internal state machine. The functionality is purely event-driven and is executed once for each event at the input.

## Application Scenarios
- **Data Protocol Adaptation:** When a REAL value (e.g., a measured value) can only be transmitted as a DWORD (e.g., in many fieldbus protocols) via a bus system.
- **Adapter Bridge:** In systems that use both REAL and DWORD adapters, this function block can serve as a simple conversion unit between the two adapter types.
- **Reusable Conversion:** Due to its encapsulation, the conversion can be used multiple times in different networks without having to manually establish the connections each time.

## Comparison with Similar Function Blocks
- **F_REAL_TO_DWORD:** The direct function block from IEC 61131-3 offers the same conversion but requires manual wiring of event and data lines. `AR_TO_AD` encapsulates this in an adapter interface, simplifying integration into adapter networks.
- **AR_TO_SINT / AR_TO_INT:** Comparable conversions exist for other integer data types, but not as adapter versions. `AR_TO_AD` is specifically designed for DWORD and adapters.
- **User-defined composite function blocks:** In principle, any user could create similar encapsulation. However, this function block offers a standardized solution with a clear package structure.

## Conclusion
The `AR_TO_AD` function block is a specialized composite function block that enables the conversion of a REAL value to a DWORD value at the adapter level. It is characterized by its ease of use, standards compliance, and seamless integration into unidirectional adapter communication. The use of the proven IEC 61131-3 module `F_REAL_TO_DWORD` ensures reliable and portable conversion.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
