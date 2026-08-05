# TEST_CONDITION
![TEST_CONDITION](https://github.com/user-attachments/assets/4dae2b3c-d1d5-4286-a466-46948ad2a767)
* * * * * * * * * *
## Introduction
The function block `TEST_CONDITION` is used to check a condition and signals whether it is met or not. It is typically used in test environments to validate specific conditions.
![TEST_CONDITION](TEST_CONDITION.svg)
## Interface Structure

### **Event Inputs**
- **REQ**: Starts the condition check. When this input is triggered, the function block begins evaluating the data input `check`.

### **Event Outputs**
- **CNF**: Signals the completion of the check. This event is triggered after the condition has been evaluated.

#
## ### **Data Inputs**
- **Check**: A Boolean value (`BOOL`) representing the condition to be checked.
- If `check == TRUE`, the condition is considered fulfilled (test passed).
- If `check == FALSE`, the condition is considered not fulfilled (test failed).

### **Data Outputs**
- None present.

### **Adapters**
- None present.

## Functionality
1. The function block is activated by the event `REQ`.

2. The value of the data input `check` is evaluated.

3. The result of the evaluation is processed internally (no direct feedback via data outputs).

4. The event `CNF` is triggered to signal the completion of the check.

## Technical Features
- The function block has a simple structure and does not contain any complex state machines.
- No data outputs are provided, as the result of the check is processed internally only.

## State Overview
The function block has a simple sequence:

1. **Idle State**: Waits for the `REQ` event.

2. **Evaluation State**: Evaluates `check` and triggers `CNF`.

3. Returns to the **Idle State**.

## Application Scenarios
- **Test Automation**: Checking conditions in automated test sequences.
- **Fault Detection**: Validating system states or input data.
- **Prototypical Implementation**: Rapid integration into test environments for logic validation.

## ⚖️ Comparison with Similar Function Blocks
- Compared to other test blocks, `TEST_CONDITION` offers a minimalist interface and is specialized for evaluating a single condition.
- More complex test blocks might support additional features such as time monitoring or multiple conditions.

## Conclusion
The `TEST_CONDITION` function block is a simple yet effective tool for checking conditions in test environments. Its streamlined interface makes it easy to integrate, while its functionality is sufficient for basic validations. However, for more complex requirements, more advanced test blocks should be considered.
