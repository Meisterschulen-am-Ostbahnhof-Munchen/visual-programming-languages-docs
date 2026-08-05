# AI_SPLIT_3
![AI_SPLIT_3](./AI_SPLIT_3.svg)
* * * * * * * * * *
## Introduction
The function block **AI_SPLIT_3** is a generic function block for duplicating an analog input signal (AI). It splits an incoming AI signal into three separate, identical output signals. The function block is entirely defined via adapters of type `AI` and operates purely in a data flow-oriented manner without its own event or data point interfaces.
## Interface Structure

The function block does not offer any direct event or data inputs/outputs. All communication takes place via **adapters**.

### Event Inputs

None available.

### Event Outputs

None available.

### Data Inputs

No direct data inputs – the AI signal is received via the socket adapter `IN`.

### Data Outputs

No direct data outputs – the three identical AI signals are provided via the plug adapters `OUT1`, `OUT2`, and `OUT3`.

### Adapters

| Direction | Designation | Type | Description |

|----------|-------------|--------------|----------------------------------------------|

| Socket | `IN` | `ADAPTER_AI` | Incoming analog signal (source) |

| Plug | `OUT1` | `ADAPTER_AI` | First output – identical to the input signal |

| Plug | `OUT2` | `ADAPTER_AI` | Second output – identical to the input signal |

| Plug | `OUT3` | `ADAPTER_AI` | Third output – identical to the input signal |

The adapters are of type `adapter::types::unidirectional::AI`. The component is generic, meaning that the specific data structure of the AI signal (e.g., value, unit, status) is only defined during instantiation by the connected adapters.
...` | `ADAPTER_AI` | qzmsdocs00009qz |
## Functionality

The functional block forwards the analog signal received via socket `IN` unchanged and simultaneously to all three plug adapters `OUT1`, `OUT2`, and `OUT3`. No signal transformation, amplification, or delay takes place. The component functions purely as a **1-to-3 splitter**.

Since no events or state machines are present, the signal is passed purely via data flow. As soon as a new AI signal is present at `IN`, it is available at all three outputs.

## Technical Features
- **Generic Function Block:** The function block is identified as `eclipse4diac::core::GenericClassName` using `'GEN_AI_SPLIT'`. This allows it to be used in various applications for different AI data types without requiring modification of the function block itself.
- **Pure Adapter Interface:** No direct event or data inputs/outputs are required. All data transmission occurs via the adapters, enabling flexible coupling with other function blocks.
- **No State Logic:** The function block does not have its own state machine (ECC) – its functionality is purely data flow-based and therefore very lightweight.

## State Overview

The function block has **no** state machine or internal states. Signals are passed directly and without delay. Therefore, a state overview is not required.

## Application Scenarios
- **Signal Distribution in Automation Systems:** An analog measured value (e.g., pressure sensor, temperature) is to be transmitted to multiple control or monitoring units.
- **Redundancy and Parallel Processing:** The same AI signal is required in parallel for different algorithms (e.g., control, alarming, logging).
- **Test Environments:** A simulated analog value can be distributed simultaneously to multiple components under test.

## Comparison with Similar Components
- **AI_SPLIT_2:** Distributes the input signal to two outputs instead of three.
- **AI_SPLIT_4 / AI_SPLIT_N:** Extended versions with four or more outputs (if available).
- **AI_SELECT:** Selects one input from multiple inputs instead of duplicating a signal.
- **AI_MERGE:** Combines multiple AI inputs into one output (counterpart to the splitter).

All split blocks share the common feature of passing the input signal to all outputs without modification. The AI_SPLIT_3 represents a typical 3-way split.

## Conclusion

The **AI_SPLIT_3** is a simple yet effective block for multiplying an analog signal to three outputs. Its generic nature and the use of adapters allow it to integrate seamlessly into adapter-based 4diac applications. It is ideally suited for applications where an AI value needs to be distributed to multiple devices without requiring additional logic or configuration.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
