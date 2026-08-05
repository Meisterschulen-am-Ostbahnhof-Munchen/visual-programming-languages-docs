# ALI_D_FF
![ALI_D_FF](./ALI_D_FF.svg)
* * * * * * * * * *
## Introduction
The **ALI_D_FF** function block implements a clock-controlled D flip-flop (data latch) via adapter interfaces. It stores a data value on the rising edge of a clock signal and outputs it until the next clock edge. This function block is suitable for synchronous data storage in event-driven automation environments.
## Interface Structure
### **Event Inputs**
- **I.E1** (via adapter I): Clock input – the data is stored on a rising edge.

### **Event Outputs**
- **Q.E1** (via adapter Q): Confirmation of data storage – output after successful edge detection and value assignment.

### **Data Inputs**
- **I.D1** (via adapter I): Data input – the value to be stored (any data type, depending on the adapter type `ALI`).

### **Data Outputs**
- **Q.D1** (via adapter Q): Data output – the currently stored (latched) value.

### **Adapters**

| Name | Type | Direction | Description |

|-------------|------------------------------|-----------|------------------------------------|

| I | `adapter::types::unidirectional::ALI` | Socket | Provides event and data input. |

| Q | `adapter::types::unidirectional::ALI` | Plug | Provides event and data output. |

## Functionality
The function block internally uses the standard function `E_D_FF_ANY` from the IEC 61499 library.

- On a rising edge at the event input **I.E1**, the current value of **I.D1** is transferred to the internal state.
- Subsequently, an event is generated at the output **Q.E1**, signaling that the new value is present at **Q.D1**.
- The data output **Q.D1** retains the stored value until a new rising edge occurs.

## Technical Features
- **Adapter-based interface**: The function block does not have direct event/data inputs but uses two adapters (`I` and `Q`). This allows for flexible encapsulation of the connections and facilitates reuse in complex networks.
- **Internal Implementation**: The core of the function block is the FB `E_D_FF_ANY`, which operates independently of data type. The data type is determined by the adapters used.
- **Event-driven**: State changes occur exclusively upon events, allowing integration into event-driven processes.

## State Overview
The FB has two logical states:

- **State 0**: Output `Q.D1` contains the last latched value, which can be, for example, logical 0.
- **State 1**: Output `Q.D1` contains a valid value other than 0 (provided the data type allows this).

A state change occurs only on a rising edge of `I.E1`. Without a clock signal, the output remains stable.

## Application Scenarios
- **Data Synchronization**: Buffering a sensor signal until the next clock cycle of a controller.
- **State Memory**: Maintaining a switching state in sequence controllers.
- **Feedback-Free Delay**: Temporarily storing values in data paths to avoid asynchronous concurrent execution.

## Comparison with Similar Components
- **ALI_D_FF vs. Simple D-FF (e.g., `E_D_FF_ANY`)**: The ALI_D_FF encapsulates event and data connections in adapters, making it more modular and easier to integrate into predefined interfaces.
- **ALI_D_FF vs. RS Flip-Flop**: An RS flip-flop allows setting and resetting (asynchronously), while the D flip-flop operates purely clock-driven and does not offer direct set/reset inputs.
- **ALI_D_FF vs. T-Flip-Flop**: The T-FF toggles on every clock cycle, while the D-FF takes an external value.

## Conclusion
The **ALI_D_FF** offers a clean, adapter-based solution for synchronous data storage. It combines the proven functionality of a D-flip-flop with the flexibility of IEC 61499 adapters. This makes it particularly suitable for modular, reusable automation components in distributed systems.