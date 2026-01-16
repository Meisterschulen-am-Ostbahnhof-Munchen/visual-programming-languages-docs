# DataPanel_MI_IW

Input service interface function block for analog input data

## Interface

### Event Inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INIT | Service Initialization | QI, PARAMS, u8SAMember, Input |
| REQ | Service Request | QI |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| INITO | Initialization Confirm | QO, STATUS |
| CNF | Confirmation of Requested Service | QO, STATUS, IN |
| IND | Indication from Resource | QO, STATUS, IN |

### Input Vars

| Name | Type | Initial Value | Comment |
| :--- | :--- | :--- | :--- |
| QI | BOOL | | Event Input Qualifier |
| PARAMS | STRING | | Service Parameters |
| u8SAMember | USINT | MI::MI_00 | Node SA 224..239 |
| Input | DataPanel::io::MI::AI::DataPanel_MI_AI_S | Invalid | Identify the Input AnalogInput_1A..8B |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| QO | BOOL | Event Output Qualifier |
| STATUS | STRING | Service Status |
| IN | WORD | Input data from resource |
