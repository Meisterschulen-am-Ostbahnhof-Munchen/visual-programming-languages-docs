# AIS_MUX_5
![AIS_MUX_5](./AIS_MUX_5.svg)

* * * * * * * * * *
## Introduction
The function block **AIS_MUX_5** implements a 5-channel multiplexer for adapters of type `adapter::types::unidirectional::AIS`.
An index input (K) selects one of the five input adapters (IN1 … IN5) and routes its data to the output adapter (OUT).

The block is designed generically and can be adapted to specific applications by parameterizing the class name.

## Interface Structure

### **Event Inputs**

| Event | Description |
|----------|---------------|
| `REQ` | Sets the index K and triggers the selection of the corresponding input adapter. |

### **Event Outputs**

| Event | Description |
|----------|--------------|
| `CNF` | Confirmation that index K has been adopted and the output adapter has been updated. |

### **Data Inputs**

| Variable | Type | Description |
|----------|-------|----------------------------|
| `K` | UINT | Index of the input to be selected (value range 0 … 4). |

### **Data Outputs**

There are no traditional data outputs. Output is exclusively via the adapter plug.

### **Adapter**

| Adapter | Direction | Type | Description |

### **Adapter**

| Adapter | Direction | Type | Description |

### **Adapter**

| Adapter | Direction | Type | Description |
### **Data Outputs** ... |-----------|----------|--------------------------------------------|---------------------------------------------------|
| `IN1` | Socket | `adapter::types::unidirectional::AIS` | Input value for index K = 0 |
| `IN2` | Socket | `adapter::types::unidirectional::AIS` | Input value for index K = 1 |
| `IN3` | Socket | `adapter::types::unidirectional::AIS` | Input value for index K = 2 |
| `IN4` | Socket | `adapter::types::unidirectional::AIS` | Input value for index K = 3 |
| `IN5` | Socket | `adapter::types::unidirectional::AIS` | Input value for index K = 4 |
| `OUT` | Plug | `adapter::types::unidirectional::AIS` | Output adapter that mirrors the selected input. |

## Functionality

After an event at the **REQ** input, the value of the data input **K** is read.

The function block then forwards the data stream of the **INi** adapter (with i = K) to the **OUT** output adapter.

Once the switchover is complete, the **CNF** confirmation event is sent.

For example, if `K = 2` is set, the data present at the **IN3** adapter is made available via **OUT**.

## Technical Features

- **Generic Function Block**: The function block is declared as a generic function block (`GEN_AIS_MUX`). This allows its use in typed libraries and the creation of specialized instances.
- **Adapter-Based Communication**: Data transmission occurs via unidirectional adapters (`adapter::types::unidirectional::AIS`). This allows complex data structures to be encapsulated, and the function block remains flexible.
- **No Additional Logic**: The multiplexer does not perform any data manipulation; it forwards the data from the selected input unchanged to the output.

## State Overview

The function block does not have an explicit state machine (ECC). Its behavior is purely event-driven:

- In its idle state, it waits for a `REQ` event.
- Upon arrival of `REQ`, the index is evaluated, the switchover is performed, and `CNF` is immediately output.

## Application Scenarios
- **Data Source Switching**: Selection of one of five sensors or data sources that communicate via the same adapter type.
- **Flexible Routing Unit**: In automation systems where different input data must be forwarded to downstream processing logic depending on the operating mode.
- **Configurable Test Environments**: Switching between different test signals without changing the wiring.

## Comparison with Similar Components

Unlike simple multiplexers with individual data inputs and outputs, `AIS_MUX_5` operates at the adapter level. This enables the transmission of complete data packets or complex states without the user needing to know the internal data structure.

**Data Source Switching**: Selection of one of five sensors or complex states that communicate via the same adapter type. Comparable components exist for other adapter types (e.g., `AIS_MUX_2`, `AIS_MUX_10`), which differ only in the number of inputs.

## Conclusion

The **AIS_MUX_5** is a simple yet powerful adapter multiplexer for five inputs. Its generic nature and pure adapter interface make it a universal component for the flexible coupling of AIS-based data streams in IEC 61499 applications.
