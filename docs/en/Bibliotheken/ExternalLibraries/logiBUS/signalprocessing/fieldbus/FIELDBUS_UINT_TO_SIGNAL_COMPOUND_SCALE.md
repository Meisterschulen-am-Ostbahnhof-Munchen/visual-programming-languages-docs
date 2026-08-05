# FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE
![FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE](./FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE.svg)
* * * * * * * * * *
## Introduction
The function block `FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE` is used to process a 16-bit fieldbus signal (type `UINT`) into a scaled real value. The incoming word is split into an upper and a lower byte, each byte is multiplied by its own scaling factor, and an offset is added. Additionally, a validity signal (`VALID`) is output, based on a predefined threshold. This function block is particularly suitable for protocols that encode two measured variables (e.g., temperature and pressure) in a single register.
## Interface Structure

### **Event Inputs**

| Event | Type | Description |

|----------|-------|--------------------------------------------------------|

| `INIT` | EInit | Initialization Request (Parameter Transfer) |

| `REQ` | Event | Normal Execution Request (Processing of `IN`) |

### **Event Outputs**

| Event | Type | Description |

|----------|-------|-------------------------------------------|

| `INITO` | EInit | Initialization Confirmation |

| `CNF` | Event | Execution Confirmation (after `REQ`) |

### **Data Inputs**

| Variable | Type | Initial Value | Description |

|-------------|--------|---------------------------|----------------------------------------------------------|

| `IN` | UINT | `WORD_TO_UINT(NOT_AVAILABLE_WM)` | Raw value from fieldbus |

| `SCALE_HIGH` | REAL | `0.256` | Scaling factor for the upper byte |

| `SCALE_LOW` | REAL | `0.001` | Scaling factor for the lower byte |

`OFFSET` | DINT | `0` | Offset added after scaling (in REAL) |

### **Data Outputs**

| Variable | Type | Initial Value | Description |

|----------|--------|-------------|---------------------------------------------------|

| `OUT` | REAL | `0.0` | Scaled Output Value |

| `VALID` | BOOL | `FALSE` | `TRUE`, if the input signal is recognized as valid |

### **Adapter**
None.

## Functionality
1. **Initialization** (`INIT`):

The algorithm `INIT` is empty, but the parameters `SCALE_HIGH`, `SCALE_LOW`, and `OFFSET` are linked to the event via the `With` relationship and can thus be set when `INIT` is called.

``` 2. **Normal Processing** (`REQ`):

- The input value `IN` is compared to a constant `VALID_SIGNAL_W` (from the imported name `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL::VALID_SIGNAL_W`):

`IF (IN <= WORD_TO_UINT(VALID_SIGNAL_W)) THEN`

- If the condition is **true** (signal valid):
- The upper byte is extracted by right-shifting 8 bits and masking with `0x00FF`:

`highByte := (IN >> 8) & 0xFF`

- The lower byte is obtained directly by masking:

`lowByte := IN & 0xFF`

- Both bytes are converted to `REAL` and multiplied by the respective scaling factors. and the offset is added:

`OUT := highByte * SCALE_HIGH + lowByte * SCALE_LOW + OFFSET`

- `VALID` is set to `TRUE`.
- If the condition is **false** (invalid signal):
- `OUT` is set to `0.0`.
- `VALID` is set to `FALSE`.
- The event `CNF` is then output.

## Technical Features
- **Compound Scaling**: The function block allows separate scaling for the upper and lower bytes of a 16-bit word. This is useful when two different physical quantities are combined in one register.
- **Validity Check**: Comparison with `VALID_SIGNAL_W` defines a threshold. Values above this threshold are considered invalid – typical for fieldbus error codes (e.g., "Not Available").
- **Parameterization via `INIT`**: The scaling factors and offset can be set once via the `INIT` event so that they remain constant during operation.
- **Initial Values**: The predefined values (`SCALE_HIGH=0.256`, `SCALE_LOW=0.001`, `OFFSET=0`) are examples; they should be adapted to the specific application.

## State Overview
The FB has two EC states:

- **INIT**: Executes the empty algorithm `INIT` and exits the state via the output `INITO`.
- **REQ**: Executes the algorithm `REQ`, which performs all signal processing, and exits the state via the output `CNF`.

The FB is implemented as a SimpleFB; there are no other states such as IDLE or WAIT.

## Application Scenarios
- **Two-in-one Sensor Values**: A temperature sensor and a pressure sensor provide their values as 8-bit numbers each in a 16-bit register. The function block (FB) converts these values into physical units using separate scaling.
- **Fieldbus Error Detection**: If the fieldbus protocol specifies a particular bit code (e.g., all bits 1) for invalid measured values, validity can be detected using the threshold value `VALID_SIGNAL_W`.
- **Post-processing of Logging Data**: Raw data from a fieldbus logger is converted back into physical units using the original scaling.

## Comparison with Similar Function Blocks

| Function Block | Property | Difference |

|----------|--------------|-------------|

| `SCALE` (e.g., according to IEC 61131) | Linear factor and offset on the entire value | No division into bytes, no validity check |

| `LINEAR` (Fieldbus Standard) | Moving average or simple linear transformation | No compound approach |

| `UINT_TO_REAL` | Direct type conversion | No scaling, no error detection |

This function block is unique in combining byte separation with dual scaling and integrated validation, making it particularly suitable for special fieldbus protocols with compound registers.

## Conclusion
The `FIELDBUS_UINT_TO_SIGNAL_COMPOUND_SCALE` is a powerful function block for processing 16-bit fieldbus signals that encode two independent measured values in a single register. Separate scaling of high and low bytes, along with integrated validation, allows for the efficient and reliable conversion of complex sensor registers into physical quantities. Parameterization via `INIT`The event and the clear separation of initialization and operation make the function block reusable and adaptable.

--

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]