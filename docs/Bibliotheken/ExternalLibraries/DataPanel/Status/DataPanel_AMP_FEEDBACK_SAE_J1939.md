# DataPanel_AMP_FEEDBACK_SAE_J1939

```{index} single: DataPanel_AMP_FEEDBACK_SAE_J1939
```

Amperage Feedback of 1 DataPanel Node

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | Service Initialization | QI, u8SAMember |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Initialization Confirm | QO, STATUS |
| IND | Indication from Resource | QO, STATUS, Current_1A, Current_1B, Current_2A, Current_2B, Current_3A, Current_3B, Current_4A, Current_4B, Current_5A, Current_5B, Current_6A, Current_6B, Current_7A, Current_7B, Current_8A, Current_8B |

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
| Current_1A | UINT | Current in mA or 0.1A depending on module |
| Current_1B | UINT | |
| Current_2A | UINT | |
| Current_2B | UINT | |
| Current_3A | UINT | |
| Current_3B | UINT | |
| Current_4A | UINT | |
| Current_4B | UINT | |
| Current_5A | UINT | |
| Current_5B | UINT | |
| Current_6A | UINT | |
| Current_6B | UINT | |
| Current_7A | UINT | |
| Current_7B | UINT | |
| Current_8A | UINT | |
| Current_8B | UINT | |
