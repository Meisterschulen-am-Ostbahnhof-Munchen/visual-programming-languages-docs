![AB2](AB2.svg)

# AB2

bidirectional adapter interface for 1 event and 1 byte

## Interface

### Event inputs

| Name | Comment | With |
| :--- | :--- | :--- |
| EI1 | Request (or Indication) | DI1 |

### Event Outputs

| Name | Comment | With |
| :--- | :--- | :--- |
| EO1 | Indication (or Request) | DO1 |

### Input Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| DI1 | BYTE | Request (or Indication) to Socket |

### Output Vars

| Name | Type | Comment |
| :--- | :--- | :--- |
| DO1 | BYTE | Indication (or Request) Data from Plug |