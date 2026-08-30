# ToJSON

![ToJSON](ToJSON.svg)

* * * * * * * * * *

## Introduction

The `ToJSON` function block adds a named field with a value to a JSON string. If `JSONIn` is empty, a new JSON object containing exactly that one field is created — by chaining several `ToJSON` calls (`JSONOut` of one as `JSONIn` of the next), a complete JSON object can be built up step by step.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the addition, carries `JSONIn`, `Value`, and `FieldName`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `JSONOut`.

### **Data Inputs**

- **JSONIn** (STRING): The existing JSON string a field is added to (an empty string creates a new object).
- **Value** (ANY): The value to store, generically typed.
- **FieldName** (STRING): The key (field name) under which `Value` is stored.

### **Data Outputs**

- **JSONOut** (STRING): The updated JSON string with the newly added field.

## Functionality

On `REQ`, the block checks `JSONIn`: if the string is empty, a new JSON object `{"FieldName": Value}` is created; otherwise the field `FieldName` with `Value` is inserted into the existing object (overwriting an existing field of the same name, if any). The result is output via `JSONOut`, then `CNF` is triggered.

## Technical Features

- **ANY input type**: `Value` generically accepts numbers, strings, and boolean values, which are translated to the corresponding JSON data type.
- **Chainable**: Since `JSONOut` has the same type as `JSONIn`, multiple `ToJSON` instances can be chained to build up a JSON object with several fields step by step.
- **Empty `JSONIn` creates a new object**: No separate "create" block is needed — the first call in a chain can start directly with an empty `JSONIn`.

## State Overview

Stateless: every `REQ` immediately results in the field being inserted and `CNF`.

## Application Scenarios

- **Building JSON payloads**: A JSON object is assembled step by step from several process values for sending to a REST API or an MQTT topic.
- **Logging**: Structured log entries in JSON format, with individual fields added from different parts of a program.

## Comparison with similar function blocks

- **[ReadJSON](ReadJSON.md)**: the reverse direction — extracts a field from a JSON string.
- **`SET_STRUCT_VALUE`**: sets a field in an IEC 61131-3 STRUCT instead of a JSON string.

## Conclusion

`ToJSON` enables the step-by-step, chainable construction of JSON strings from individual field/value pairs and is suitable for building JSON payloads in 4diac applications without requiring a full structure type definition.
