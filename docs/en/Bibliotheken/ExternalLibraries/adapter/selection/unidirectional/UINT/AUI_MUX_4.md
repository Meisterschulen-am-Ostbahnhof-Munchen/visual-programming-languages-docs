# AUI_MUX_4
![AUI_MUX_4](./AUI_MUX_4.svg)

* * * * * * * * * *
## Introduction
The function block **AUI_MUX_4** is a generic multiplexer for AUI (Unidirectional Application Interface) adapters. It enables dynamic switching between four AUI inputs (IN1 to IN4) to a common AUI output (OUT) using an integer index.
## Interface Structure
### **Event Inputs**

| Event | Description |

|----------|--------------|

| REQ | Sets the index **K** and enables the switching. |

### **Event Outputs**

| Event | Description |

|----------|--------------|

| CNF | Confirmation that the selection was made according to **K**. |

### **Data Inputs**

| Variable | Type | Description |

|----------|-------|------------------------|

| K | UINT | Selection Index (0 … 3) |

### **Data Outputs**
None.

### **Adapters**

| Adapter | Direction | Type | Description |

|---------|----------|--------|-------------------------------------------------|

| OUT | Plug | AUI | Output Adapter (multiplexed signal) |

| IN1 | Socket | AUI | Data source for K = 0 |

| IN2 | Socket | AUI | Data source for K = 1 |

| IN3 | Socket | AUI | Data source for K = 2 |

| IN4 | Socket | AUI | Data Source for K = 3 |

## Functionality
When a signal is applied to the **REQ** event input, the current value of the **K** input is evaluated. Depending on **K** (0 … 3), one of the four AUI sockets (IN1…IN4) is connected to the **OUT** plug. The selected AUI path is immediately activated, and the **CNF** event is then output. The function block (FB) operates in an event-driven manner; no cyclic polling takes place.

## Technical Features
- The FB is declared as a **generic block** (GenericClassName `'GEN_AUI_MUX'`) and can therefore be reused in various contexts.
- All adapters are of type `adapter::types::unidirectional::AUI` – a unidirectional interface protocol.
- The **K** index is defined as `UINT`; values outside 0…3 are not processed.
- The attribute `eclipse4diac::core::TypeHash` enables unique identification of the type definition in the 4diac framework.

## State Overview
The function block has **no explicit internal state machine** (ECC). Its functionality is purely event-driven: A REQ event immediately triggers the switching and the CNF confirmation.

## Application Scenarios
- **Data source switching** in distributed automation systems when multiple AUI-compliant sensors or actuators need to be connected via a common channel.
- **Dynamic path selection** in AUI-based communication networks, e.g., for fault switching or load balancing.
- **Parameterizable configuration** of devices where the index is set from a higher-level control program.

## Comparison with Similar Components

The **AUI_MUX_4** is functionally identical to a classic 4-to-1 multiplexer, but specifically tailored to the AUI adapter type. Unlike generic data multiplexers (e.g., MUX from IEC 61499 standard libraries), it does not work with elementary data types, but rather with complex adapter connections. This simplifies cabling in AUI-based architectures.

## Conclusion
The **AUI_MUX_4** offers a clean, reusable solution for selecting between four AUI signals. Its event-driven operation and generic type definition make it flexible to use, especially in modular automation solutions based on the 4diac framework.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
