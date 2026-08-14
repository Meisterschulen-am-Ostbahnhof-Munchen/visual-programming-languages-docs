# ReadJSON

![ReadJSON](ReadJSON.svg)

* * * * * * * * * *
## Introduction

The `ReadJSON` function block extracts the value of a named field from a JSON string. It serves as a simple, event-driven JSON decoder for use cases where a single field needs to be read from a JSON structure, without having to map the entire structure to dedicated IEC 61131-3 data types.

## Interface Structure

### **Event Inputs**

- **REQ**: Triggers the extraction, carries `JSONIn` and `FieldName`.

### **Event Outputs**

- **CNF**: Confirms completion, carries `Value`.

### **Data Inputs**

- **JSONIn** (STRING): The JSON string to search.
- **FieldName** (STRING): The name of the field to extract.

### **Data Outputs**

- **Value** (ANY): The extracted field value, generically typed.

## Functionality

On `REQ`, the block searches `JSONIn` for the field `FieldName` and outputs its value via `Value`. Since `Value` is of type `ANY`, the extracted value can be interpreted as a number, string, or boolean depending on the JSON content. `CNF` is then triggered.

## Technical Features

- **ANY return type**: `Value` generically adapts to the actual JSON field type, but when wired to a concretely typed variable must be compatible with that type.
- **Single-field extraction**: The block reads exactly one named field per call; nested or multiple fields require several `ReadJSON` calls or instances.

## State Overview

Stateless: every `REQ` immediately results in extraction and `CNF`.

## Application Scenarios

- **Reading configuration**: A JSON configuration string received over the network or from a file needs to be evaluated without defining a full STRUCT.
- **Communicating with REST/web interfaces**: Responses from HTTP APIs that return JSON can be read field by field.

## Comparison with similar function blocks

- **[ToJSON](ToJSON.md)**: the reverse direction — adds a field to a JSON string or creates a new one.
- **`GET_STRUCT_VALUE`**: reads a field from an IEC 61131-3 STRUCT instead of a JSON string.

## Conclusion

`ReadJSON` provides a simple, field-by-field JSON decoder for 4diac applications communicating with JSON-based configurations or web interfaces, without requiring a full structure type definition.
