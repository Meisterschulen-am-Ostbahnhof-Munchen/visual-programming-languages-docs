# FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE
![FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE](./FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE.svg)

* * * * * * * * * *
## Introduction
This function block maps a 16-bit word input to a scaled real value. The incoming word is first checked for validity. If the signal is valid, the upper and lower bytes are multiplied by their respective scaling factors and added with an offset. The result is output as the scale of the original fieldbus signal.
## Interface Structure
### **Event Inputs**
- **INIT** (EInit) – Initialization request; with the parameters `SCALE_HIGH`, `SCALE_LOW`, and `OFFSET`.
- **REQ** (Event) – Normal execution request; with the parameter `IN`.

### **Event Outputs**
- **INITO** (EInit) – Confirmation of initialization.
- **CNF** (Event) – Confirmation of execution; with the parameters `OUT` and `VALID`.

### **Data Inputs**

| Name | Type | Initial Value | Description |

|------|-----|--------------|--------------|

| `IN` | WORD | `NOT_AVAILABLE_WM` | The 16-bit fieldbus signal to be processed. |

| `SCALE_HIGH` | REAL | 0.256 | Scaling factor for the upper byte (high byte). |

| `SCALE_LOW` | REAL | 0.001 | Scaling factor for the lower byte (low byte). |

| `OFFSET` | DINT | 0 | Integer offset added after scaling. |

### **Data Outputs**

| Name | Type | Initial Value | Description |

|------|-----|-------------|--------------|

| `OUT` | REAL | 0.0 | Calculated scalar output value. |

| `VALID` | BOOL | FALSE | Indicates whether the input signal is valid (`TRUE`) or not (`FALSE`). |

### **Adapters**
No adapters available.

## Functionality
The function block operates in two steps, controlled by events:

1. **Initialization (INIT)**

- The internal algorithm is empty; only the event output `INITO` is set.
- The scaling parameters (`SCALE_HIGH`, `SCALE_LOW`, `OFFSET`) are passed during the initialization event but are not used until the **REQ** cycle.

2. **Processing (REQ)**

- The incoming value `IN` is compared to the external constant `VALID_SIGNAL_W`.
- **Valid Signal** (`IN` ≤ `VALID_SIGNAL_W`):

1. The upper byte is extracted by right-shifting 8 bits and masking with `0x00FF`.

2. The lower byte is obtained by masking with `0x00FF`.

3. Both bytes are converted to `REAL`, multiplied by the corresponding scaling factors, and added to the offset:

OUT = (highByte * SCALE_HIGH) + (lowByte * SCALE_LOW) + OFFSET`

4. `VALID` is set to `TRUE`.

- **Invalid signal** (otherwise):
- `OUT` is set to `0.0`.
- `VALID` is set to `FALSE`.

The following ST code illustrates the internal logic:

IF (WORD_TO_UINT(IN) <= WORD_TO_UINT(VALID_SIGNAL_W)) THEN
temp := SHR(IN, SINT#8);
highByte := temp AND WORD#16#00FF;
lowByte := IN AND WORD#16#00FF;
OUT := UINT_TO_REAL(WORD_TO_UINT(highByte)) * SCALE_HIGH

+ UINT_TO_REAL(WORD_TO_UINT(lowByte)) * SCALE_LOW
+ DINT_TO_REAL(OFFSET);
VALID := BOOL#TRUE;
ELSE
OUT := REAL#0.0;
VALID := BOOL#FALSE;
END_IF;
## Technical Features
- **Compound Scaling:** The two bytes of a word are scaled separately. This allows for the representation of measured values whose information is distributed across two bytes (e.g., different resolutions or units).
- **Fieldbus Constants:** The two external constants `VALID_SIGNAL_W` and `NOT_AVAILABLE_WM` define the valid value range and the "not available" state, respectively. They are taken from the package `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL`.
- **Initial Values:** The default values `SCALE_HIGH = 0.256`, `SCALE_LOW = 0.001`, and `OFFSET = 0` are field-tested values for typical fieldbus signals (e.g., temperature measurement).
- **No State Dependency:** The component has no internal state machines beyond INIT/REQ – the response is purely combinatorial during the REQ event.

## State Overview
The component has two simple states that directly correspond to the events:

| State | Triggered by | Action performed | Output event |

|---------|----------------|--------------------|------------------|

| `INIT` | Event `INIT` | Algorithm `INIT` (empty) | `INITO` |

| `REQ` | Event `REQ` | Algorithm `REQ` (Scaling) | `CNF` |

No further states or branches exist.

## Application Scenarios
- **Temperature Measurement via Two Channels** – The high byte represents the integer part, the low byte the decimal part of a temperature (e.g., 0.256°C/LSB for high, 0.001°C/LSB for low).
- **Pressure or Level Sensors** – Provide a 16-bit raw value, which is decomposed into two differently scaled parts to determine the physical value.
- **Fieldbus Data Preprocessing** – In a logiBUS signal processing chain, this component can be used as the first stage for converting word values into real physical quantities.

## Comparison with Similar Function Blocks
- **FIELDBUS_WORD_TO_SIGNAL** (without compound) – Applys only a single scaling factor to the entire word. Suitable when the high and low bytes have the same weight.
- **FIELDBUS_BYTE_TO_SIGNAL** – Processes only a single byte. Requires two instances to handle both bytes of a word.
- **FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE** is characterized by the separate scaling of the two bytes, which enables a more flexible and accurate representation of many sensor protocols.

## Conclusion
The **FIELDBUS_WORD_TO_SIGNAL_COMPOUND_SCALE** function block is a specialized tool for processing 16-bit fieldbus signals where the two bytes have different physical meanings or resolutions. The clear separation of validation, byte extraction, and compound scaling makes it a reliable and configurable element in the signal processing chain. Externally defined fieldbus constants allow for easy adaptation to various protocols.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
