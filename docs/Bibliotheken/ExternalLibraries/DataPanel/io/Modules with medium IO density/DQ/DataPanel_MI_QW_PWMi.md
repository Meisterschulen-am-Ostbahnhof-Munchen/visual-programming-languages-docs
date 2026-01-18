# DataPanel_MI_QW_PWMi

```{index} single: DataPanel_MI_QW_PWMi
```

Output service interface function block for Current Controlled PWM output data (Current Mode 4)

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | Service Initialization | QI, PARAMS, u8SAMember, Output, KP, KI |
| REQ | Service Request | QI, OUT, KP, KI |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Initialization Confirm | QO, STATUS |
| CNF | Confirmation of Requested Service | QO, STATUS |

### Input Vars

| Name | Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| QI | BOOL | | Event Input Qualifier |
| PARAMS | STRING | | Service Parameters |
| OUT | WORD | | Output data to resource |
| KP | UINT | 70 | Proportional gain for current control |
| KI | UINT | 30 | Integral gain for current control |
| u8SAMember | USINT | MI::MI_00 | Node SA 224..239 |
| Output | DataPanel::io::MI::DQ::DataPanel_MI_DO_S | Invalid | Identify the Output DigitalOutput_1A..8B and Input_Power_Port_5..8 |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Service Status |
