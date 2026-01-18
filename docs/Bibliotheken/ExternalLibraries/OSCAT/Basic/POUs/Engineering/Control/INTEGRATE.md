# INTEGRATE

```{index} single: INTEGRATE
```

Integrator with I/O for out

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | Init Request | |
| REQ | Normal Execution Request | EN, X, K, Y |
| RST | Reset Integrator | X |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Init Confirmation | |
| CNF | Execution Confirmation | X_LAST, Y |

### Input Vars

| Name | Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| EN | BOOL | TRUE | Enable |
| X | REAL | | Input Value |
| K | REAL | 1.0 | Gain |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| X_LAST | REAL | Last Input Value |

### InOut Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| Y | REAL | Output Value |