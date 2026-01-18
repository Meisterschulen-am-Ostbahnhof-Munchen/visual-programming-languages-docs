# DataPanel_FREQ_SAE_J1939

```{index} single: DataPanel_FREQ_SAE_J1939
```

Frequency/Counter Inputs 7A-8A Status

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | Service Initialization | QI, u8SAMember |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Initialization Confirm | QO, STATUS |
| IND | Indication from Resource | QO, STATUS, Hertz_Count_7A, DutyCycle_SP_7A, Hertz_Count_8A, DutyCycle_SP_8A |

### Input Vars

| Name | Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| QI | BOOL | | Event Input Qualifier |
| u8SAMember | USINT | MI::MI_00 | Node SA 224..239 |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Service Status |
| Hertz_Count_7A | UINT | Frequency (Hz) or Count for Input 7A |
| DutyCycle_SP_7A | UINT | Duty Cycle or Setpoint for Input 7A |
| Hertz_Count_8A | UINT | Frequency (Hz) or Count for Input 8A |
| DutyCycle_SP_8A | UINT | Duty Cycle or Setpoint for Input 8A |