![FT_PT2](FT_PT2.svg)
#FT_PT2
2nd grade filter with programmable times
# FT_PT2
## Interface
### Event inputs
| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | InitRequest | in, TM, D, K |
| REQ | Normal Execution Request | in, TM, D, K |
| RST | Reset filters | |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Init Confirmation | out |
| CNF | Execution Confirmation | out |

### Input Vars

| Name | Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| in | REAL | | Input signal |
| TM | TIME | | Time Constant |
| D | REAL | | Damping Factor |
| K | REAL | 1.0 | Gain |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| out | REAL | Filtered Output |