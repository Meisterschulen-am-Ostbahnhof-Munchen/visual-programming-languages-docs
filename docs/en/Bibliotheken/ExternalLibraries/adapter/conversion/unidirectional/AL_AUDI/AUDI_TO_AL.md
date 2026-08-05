# AUDI_TO_AL
![AUDI_TO_AL](./AUDI_TO_AL.svg)
* * * * * * * * * *
## Introduction
The **AUDI_TO_AL** function block is a composite function block that converts an **AUDI** adapter (UDINT data format) into an **AL** adapter (LWORD data format). It serves as an interface converter between different adapter types in automation systems based on the IEC 61499 standard.
## Interface Structure

### **Event Inputs**

The function block does not have its own event inputs. Event-driven processing is handled via the **AUDI_IN** socket:

- **E1**: Event input of the AUDI adapter – triggers the conversion.

### **Event Outputs**

The function block does not have its own event outputs. The result is passed via the **AL_OUT** plug:

- **E1**: Event output of the AL adapter – signals completion of the conversion.

### **Data Inputs**

This function block does not have its own data inputs. The data to be converted is provided via the **AUDI_IN** socket:

- **D1**: Data input of the AUDI adapter (Type: UDINT) – the value to be converted.

### **Data Outputs**

This function block does not have its own data outputs. The converted result is provided via the **AL_OUT** plug:

- **D1**: Data output of the AL adapter (Type: LWORD) – the converted value.

### **Adapter**

| Name | Direction | Type | Description |

|---------|----------|----------------------------------------------|---------------------------------------------------|

| AUDI_IN | Socket | `adapter::types::unidirectional::AUDI` | UDINT adapter as input interface |

| AL_OUT | Plug | `adapter::types::unidirectional::AL` | LWORD adapter as output interface |

## Functionality

This function block is a pure encapsulation of the IEC 61131 function `F_UDINT_TO_LWORD`.

When an event occurs at **AUDI_IN.E1**, the internal function block **Convert** (type `F_UDINT_TO_LWORD`) is activated via its event input **REQ**. Simultaneously, the UDINT value present at **AUDI_IN.D1** is passed to the **IN** data input of **Convert**. Upon completion of the conversion, **Convert** signals its completion via its **CNF** event output. This event is forwarded directly to **AL_OUT.E1**, and the converted LWORD value is output by **Convert.OUT** to **AL_OUT.D1**.

The entire process is event-driven and requires no additional runtime logic within the composite function block.

## Technical Features
- The function block is implemented as a **composite function block** and uses only the standardized IEC 61131 conversion function `F_UDINT_TO_LWORD`.
- The conversion is performed directly: **UDINT** (32-bit unsigned integer) is mapped to **LWORD** (64-bit logical word).

``` Note: When converting a 32-bit value to a 64-bit word, the upper 32 bits are set to zero.

- This function block is licensed under the **Eclipse Public License 2.0**.
- The interfaces (adapters) are unidirectional: Data flows only from the socket to the plug.

## State Overview

Since this is a composite function block without its own state machine, **AUDI_TO_AL** does not have an internal state machine. Its behavior is entirely determined by the interconnected function block `F_UDINT_TO_LWORD`, which implements a simple REQ/CNF handshake.

## Application Scenarios
- **Adapter Conversion** in IEC 61499 systems where an existing AUDI adapter (UDINT-based) needs to be connected to an AL adapter (LWORD-based) – e.g., to connect sensor data to a 64-bit data processing chain.
- **Interface Adaptation** when replacing hardware components or migrating from 32-bit to 64-bit automation solutions.
- **Prototypical Implementation** in agricultural technology or other areas where UDINT and LWORD data formats are used interchangeably.

## Comparison with Similar Components

Unlike generic converters such as `UDINT_TO_LWORD` (an atomic component), **AUDI_TO_AL** offers a pre-configured adapter coupling, freeing developers from manually connecting event and data lines. Similar composite components exist, for example, for `UDINT_TO_DWORD` or `LREAL_TO_LWORD`, but these are specific to different target adapters.

## Conclusion

The **AUDI_TO_AL** function block is a compact, reusable component for cleanly separating adapter types. By encapsulating the conversion in a composite, it simplifies the maintainability and readability of applications based on different data format adapters.