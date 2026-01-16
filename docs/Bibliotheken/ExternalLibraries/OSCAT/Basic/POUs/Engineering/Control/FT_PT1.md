# FT_PT1

Low Pass Filter (PT1)

FT_PT1 is an low pass filter with a programmable time T and faktor K.

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | Init Request | |
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
| in | REAL | | Input Signal |
| TM | TIME | | Filter Time Constant |
| K | REAL | 1.0 | Gain Factor |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| delta_t | UDINT | Delta T since last call. |
| out | REAL | Output Signal |
