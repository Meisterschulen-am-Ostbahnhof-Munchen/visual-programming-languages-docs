![FT_PT1](FT_PT1.svg)

#FT_PT1

Low pass filter (PT1)

FT_PT1 is a low pass filter with a programmable time T and factor K.

## Interface

### Event inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | InitRequest | |
| REQ | Normal Execution Request | in, TM, K |
| RST | Reset | |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Init Confirmation | |
| CNF | Execution Confirmation | delta_t, out |

### Input Vars

| Name | Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| in | REAL | | Input signal |
| TM | TIME | | Filter Time Constant |
| K | REAL | 1.0 | Gain Factor |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| delta_t | UDINT | Delta T since last call. |
| out | REAL | Output signal |