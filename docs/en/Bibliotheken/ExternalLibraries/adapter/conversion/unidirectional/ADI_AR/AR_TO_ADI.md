# AR_TO_ADI

![AR_TO_ADI](./AR_TO_ADI.svg)

* * * * * * * * * *
## Introduction
The function block **AR_TO_ADI** is a composite block that converts a REAL adapter (AR) into a DINT adapter (ADI). It is used to mediate between interfaces with different data types, with the conversion occurring in an event-driven manner.

## Interface Structure
The block's interface consists exclusively of adapters that bundle both events and data. There are no separate inputs or outputs.

### **Event Inputs**

- **AR_IN.E1** – Event input via the AR adapter

Triggers the conversion of the incoming REAL value.


### **Event Outputs**

- **ADI_OUT.E1** – Event output via the ADI adapter

Activated after successful conversion.

### **Data Inputs**

- **AR_IN.D1** (Data type REAL) – The floating-point value to be converted.

### **Data Outputs**

- **ADI_OUT.D1** (Data type DINT) – The converted integer value.

### **Adapters**

| Adapter | Name | Direction | Description |

|---------|------|----------|-------------|

| AR | AR_IN | Socket (Input) | Unidirectional REAL adapter that provides the input signal. |

| ADI | ADI_OUT | Plug (Output) | Unidirectional DINT adapter that forwards the converted signal. |

## Functionality

The function block is implemented as a composite function block. It contains an instance of the IEC 61131 standard function block `F_REAL_TO_DINT`.

As soon as an event arrives at the event input **AR_IN.E1**, the REAL value present at **AR_IN.D1** is passed to the internal converter. After the conversion is complete, the result is forwarded to **ADI_OUT.D1** and the event **ADI_OUT.E1** is triggered.

## Technical Features

- The function block uses the data type converter `F_REAL_TO_DINT` from the IEC 61131 library.

- It is a composite function block that does not have its own state logic; instead, the functionality is implemented through the internal function block.

- The interface is purely adapter-based, allowing for easy integration into existing adapter networks.

## State Overview
Since the FB does not contain a state machine, the following simple sequence applies:

1. **Waiting** – The FB is ready to receive an event on **AR_IN.E1**.

2. **Conversion** – As soon as an event arrives, the REAL value is converted to DINT.

3. **Output** – After the conversion is complete, the result is output and the output event is sent. The FB then returns to the wait state.

## Application Scenarios

- Adapting a sensor that delivers REAL values to a controller that expects DINT values.

- Bridging the gap between two adapter-based components with different data types in an IEC 61499 system.

- Use in data preprocessing chains where floating-point numbers need to be converted to integers.

## Comparison with similar function blocks

- **`F_REAL_TO_DINT`** – This function block performs the actual conversion but expects separate event and data connections. **AR_TO_ADI** encapsulates this functionality in an adapter-based interface, thus simplifying integration into adapter networks.

- **Other adapter converters** – Similar function blocks exist for other data type combinations (e.g., AR_TO_AINT, ADI_TO_AR). They all follow the same pattern: using an internal conversion function block embedded in a uniform adapter shell.

## Conclusion

**AR_TO_ADI** is a compact, reusable composite function block that enables clean conversion from REAL to DINT adapters. Thanks to its simple, event-driven structure and the use of standardized conversion modules, it is ideally suited for adapter-based designs in industrial control systems.