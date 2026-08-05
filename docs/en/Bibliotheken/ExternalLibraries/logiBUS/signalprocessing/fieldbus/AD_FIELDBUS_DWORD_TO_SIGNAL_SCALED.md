# AD_FIELDBUS_DWORD_TO_SIGNAL_SCALED
![AD_FIELDBUS_DWORD_TO_SIGNAL_SCALED](./AD_FIELDBUS_DWORD_TO_SIGNAL_SCALED.svg)
* * * * * * * * * *
## Introduction
The function block `AD_FIELDBUS_DWORD_TO_SIGNAL_SCALED` processes a digital fieldbus signal (DWORD) into a scaled analog output value. It mirrors the input value to the output, provided the signal is valid, and applies linear scaling with an offset. The valid signal state information is synchronized via an edge-triggered flip-flop and provided as a separate output signal.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |

|----------|-----|---------------|

| INIT | EInit | Initialization request for the entire function block (forwarded to internal core function block) |

### **Event Outputs**

| Event | Type | Description |

|----------|-----|--------------|

| INITO | EInit | Initialization confirmation after successful initialization |

### **Data Inputs**

| Name | Data Type | Initial Value | Description |

|------|----------|-------------|--------------|

| SCALE | LREAL | 1.0 | Scaling factor by which the input value is multiplied |

| OFFSET | DINT | 0 | Integer offset that is added after scaling |

### **Data Outputs**

This module has no direct data outputs. All output data is provided via the adapter interfaces.

### **Adapters**

| Name | Type | Direction | Description |

|------|-----|----------|--------------|

| IN | AD (unidirectional) | Socket | Input adapter for the DWORD value (fieldbus signal) |

| OUT | ALR (unidirectional) | Plug | Output adapter for the scaled analog value |

| VALID | AX (unidirectional) | Plug | Output adapter for signal validity (TRUE = valid) |

## Functionality

The module implements the following signal chain:

1. **Initialization**: The event `INIT` is forwarded directly to the internal core module `FIELDBUS_DWORD_TO_SIGNAL_SCALED`. Upon completion, `INITO` is output.

2. **Data Processing**: The DWORD value present at socket `IN` is inherited with each data event (E1). The core module multiplies the value by `SCALE` (LREAL) and adds `OFFSET` (DINT). The result is output as LREAL to plug `OUT`.

3. **Validity Signal**: The core module outputs an internal Boolean validity signal indicating whether the current data value is valid. This signal is synchronized via an edge-triggered D flip-flop (`E_D_FF`) and output to the plug `VALID`. The flip-flop clocks with the same event (`CNF` of the core module), so the validity is updated simultaneously with the output value.

The internal circuitry ensures that the validity status always corresponds to the last processed data value.

## Technical Features
- **Scaling Order**: First, multiplication by `SCALE` (LREAL), then addition by `OFFSET` (DINT). This allows the offset to be specified in units of the scaled range.
- **Edge Synchronization**: The validity signal is output via a D flip-flop using edge triggering, so there are no metastable states on the output side.
- **Initial Value Default**: `SCALE` is predefined to 1.0, `OFFSET` to 0. In the unscaled case, the output thus directly corresponds to the input.
- **Adapter Structure**: The inputs and outputs are implemented as adapters, enabling type-safe connections with other devices from the same adapter family (AD, ALR, AX).

## State Overview

The device does not have its own explicit state diagram (ECC). All state logic resides in the internal core device `FIELDBUS_DWORD_TO_SIGNAL_SCALED` and the edge-triggered D flip-flop. This stores the last valid validity state. With each processing event, the flip-flop is clocked and outputs the current validity value.

## Application Scenarios
- **Fieldbus Data Acquisition**: A raw DWORD value (e.g., from an analog-to-digital converter or encoder) is converted using physical factors (scaling) and offset and transmitted as an analog value to a controller.
- **Signal Validation with Storage**: When the fieldbus provides a validity flag (e.g., "Data Updated"), this can be evaluated via the validity adapter level. The flip-flop ensures that the validity signal remains stable until the next update.
- **Configurable Scaling**: By externally specifying `SCALE` and `OFFSET`, the same function block can be used for different sensor ranges without modifying the function block itself.
- ## Comparison with Similar Function Blocks

Compared to a simple `MOVE` or `SCALE` function block, this FB offers integrated validation handling and a clean separation between data and event adapters. Similar function blocks (e.g., `FIELD_DWORD_TO_ANALOG`) often lack separate signal validity output or edge-synchronous storage. The combination of core function block and D flip-flop used here is a proven solution for safety-critical applications where the validity of a data value must be reliably maintained.

## Conclusion

The `AD_FIELDBUS_DWORD_TO_SIGNAL_SCALED` function block is a robust and configurable function block for converting digital fieldbus signals into scaled analog values with synchronous validity output. Thanks to its modular adapter connections and integrated edge synchronization, it is particularly suitable for industrial automation systems where data consistency and signal quality are equally important.