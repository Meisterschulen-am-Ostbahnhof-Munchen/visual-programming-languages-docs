# FT_PT2

2nd grade filter with programmable times

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | Init Request | in, TM, D, K |
| REQ | Normal Execution Request | in, TM, D, K |
| RST | Reset Filter | |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Init Confirmation | out |
| CNF | Execution Confirmation | out |

### Input Vars

| Name | Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| in | REAL | | Input Signal |
| TM | TIME | | Time Constant |
| D | REAL | | Damping Factor |
| K | REAL | 1.0 | Gain |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| out | REAL | Filtered Output |
