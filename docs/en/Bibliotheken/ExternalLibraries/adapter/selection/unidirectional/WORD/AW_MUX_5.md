# AW_MUX_5
![AW_MUX_5](./AW_MUX_5.svg)

* * * * * * * * * *
## Introduction
The AW_MUX_5 is a generic multiplexer function block that, based on an integer index (K), switches one of five unidirectional adapter inputs (IN1–IN5) to a common adapter output (OUT). It serves for flexible source selection in automation solutions where signals are transported via adapters instead of direct data ports.
## Interface Structure
### **Event Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| REQ | Event | Sets the index K and triggers the switching (connected to K) |

### **Event Outputs**

| Name | Type | Comment |

|------|-----|-----------|

| CNF | Event | Confirms successful switching to the selected input |

### **Data Inputs**

| Name | Type | Comment |

|------|-----|-----------|

| K | UINT | Selection Index (Value range 0–4) |

### **Data Outputs**
No data outputs available.

### **Adapters**
**Plug (Output):**

- **OUT** – Type: `AW` (unidirectional adapter)

Returns the value of the input selected by K.

**Sockets (Inputs):**

| Name | Type | Comment |

|------|-----|-----------|

| IN1 | AW | Input value for K = 0 |

IN2 | AW | Input value for K = 1 |

IN3 | AW | Input value for K = 2 |

IN4 | AW | Input value for K = 3 |

IN5 | AW | Input value for K = 4 |

## Functionality
The function block operates in an event-driven manner:

1. An event at the **REQ** input triggers processing.

2. The current value of the **K** index is evaluated.

3. Depending on K (0–4), the corresponding adapter socket (IN1–IN5) is switched to the **OUT** adapter plug.

4. After successful switching, the **CNF** event is output.

If the index is outside the valid range (e.g., K > 4), the output remains unchanged or assumes an undefined state; the FB specification does not provide any guidance in this regard.

## Technical Features
- **Generic Type:** The function block (FB) is declared as a generic function block (`GenericClassName = 'GEN_AW_MUX'`), meaning it can be reused in various adaptations.
- **Pure Adapter Interface:** No direct data ports (except K) are used. All signals are transmitted via unidirectional adapters of type `AW`.
- **Simple Index Mapping:** Fixed mapping K=0→IN1 to K=4→IN5.
- **Event-Driven:** Switching occurs only upon a REQ event, not continuously.

## State Overview
The FB does not have explicit states in its XML definition. The implicit behavior can be described as follows:

| State | Description |

|---------|--------------|

IDLE | Waiting for a REQ event |

SELECT | Evaluate K and switch the corresponding input |

DONE | Send CNF, return to IDLE |

These states are purely internal and not directly controllable by the user.

## Application Scenarios
- **Signal Source Switching:** A controller can select between five different sensors (e.g., temperature, pressure, level) connected via adapters.
- **Test and Simulation Tasks:** Switching between real and simulated data sources.
- **Operating Mode Selection:** Input and output configuration depending on an operating mode identifier (index).
- **Adapter-Based Multiplexers:** Universally applicable where adapters are used instead of standard data types (e.g., in object-oriented IEC 61499 components).

## Comparison with Similar Components
- **Standard MUX in IEC 61499:** A conventional MUX uses direct data ports (e.g., ANY type) and an index. The AW_MUX_5 is specifically designed for the unidirectional adapter `AW`, which allows for more robust encapsulation of the data structure.
- **Multi-channel switches (e.g., MUX_2, MUX_4):** These offer a smaller number of inputs. The AW_MUX_5, with its five inputs, covers a medium requirement.
- **Generic multiplexers:** Some implementations allow a variable number of inputs via parameters. The AW_MUX_5, however, is fixed at exactly five, but offers the advantage of a clear adapter interface.

## Conclusion

The AW_MUX_5 is a compact, event-driven multiplexer function block for unidirectional adapters of type `AW`. It allows for the easy selection of one of five signal sources and is particularly suitable for modular, adapter-based control architectures. Its clear index assignment, generic design, and integration under an EPL 2.0 license make it a useful component in the 4diac IDE environment.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
