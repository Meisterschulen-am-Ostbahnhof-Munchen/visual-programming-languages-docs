# AR_SPLIT_5
![AR_SPLIT_5](./AR_SPLIT_5.svg)
* * * * * * * * * *
## Introduction
The AR_SPLIT_5 function block is used to split an incoming AR adapter into five identical AR adapter outputs. It is a generic function block specifically designed for distributing unidirectional adapters (type: `adapter::types::unidirectional::AR`).
## Interface Structure
### **Event Inputs**
None available.

### **Event Outputs**
None available.

### **Data Inputs**
None available.

### **Data Outputs**
None available.

#
## ### **Adapter**
- **Socket (Input)**:
- `IN`: Type `adapter::types::unidirectional::AR` – Receives a single AR adapter.

``` - **Plugs (Outputs)**:

- `OUT1`: Type `adapter::types::unidirectional::AR`
- `OUT2`: Type `adapter::types::unidirectional::AR`
- `OUT3`: Type `adapter::types::unidirectional::AR`
- `OUT4`: Type `adapter::types::unidirectional::AR`
- `OUT5`: Type `adapter::types::unidirectional::AR`

All outputs are identical and pass the incoming AR adapter through unchanged.

## Functionality

The function block operates as a passive distributor: As soon as an AR adapter is connected to the input `IN`, it is duplicated to the five outputs `OUT1` to `OUT5`. Each connection receives an independent but identical copy of the adapter. No data processing or modification takes place.

## Technical Features
- **Unidirectionality**: The adapters of type `AR` are exclusively unidirectional, meaning signals flow only from the input to the outputs.
- **Generic Implementation**: The function block is implemented as a generic type (`GEN_AR_SPLIT`), which allows for easy reuse and adaptation to other adapter types.
- **No State Logic**: The function block has no internal states or events; The splitting is achieved purely through interconnection technology.

## State Overview
The AR_SPLIT_5 does not have its own state machine. Its behavior is static and purely structural: The input is directly passed through to all outputs.

## Application Scenarios
- **Signal Distribution**: When an AR adapter provides a control or data signal that needs to be passed on to several downstream components (e.g., actuators, sensors).
- **Module Cascading**: In complex automation systems where an AR signal needs to be split to different subsystems.

## Comparison with Similar Function Blocks
- **AR_SPLIT_2, AR_SPLIT_3, AR_SPLIT_4**: These function blocks split an AR adapter into two, three, or four outputs, respectively. The AR_SPLIT_5 is the extension to five outputs.
- **AR_MERGE_***: Unlike split function blocks, merge function blocks combine multiple AR adapters into one.

## Conclusion

The AR_SPLIT_5 is a simple yet useful function block for distributing a unidirectional AR adapter across five independent outputs. Its generic and eventless structure makes it a fundamental tool for adapter-based communication in IEC 61499 systems.
