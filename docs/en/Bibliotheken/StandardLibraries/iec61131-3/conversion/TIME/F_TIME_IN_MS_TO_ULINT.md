# F_TIME_IN_MS_TO_ULINT

<img width="1534" height="212" alt="F_TIME_IN_MS_TO_ULINT" src="https://github.com/user-attachments/assets/1e823341-98ae-4b40-bc4f-74b28764bb74" />
* * * * * * * * * *
The function block `F_TIME_IN_MS_TO_ULINT` converts a time value in milliseconds (`TIME`) into an unsigned 64-bit integer value (`ULINT`). This block is particularly useful when time values are needed in numerical form for further calculations or comparisons.
![F_TIME_IN_MS_TO_ULINT](F_TIME_IN_MS_TO_ULINT.svg)

- **REQ**: Starts the conversion. This input is linked to the data input `IN`.
- **CNF**: Signals the completion of the conversion. This output is linked to the data output `OUT`.
- **IN**: This input expects a time value of type `TIME`, specified in milliseconds.
- **OUT**: Returns the converted value as an unsigned 64-bit integer (`ULINT`).

### Data Outputs

### Data Inputs

### Event Outputs

### Event Inputs

## Interface Structure

## Introduction

### **Adapters**

This function block has no adapters.

The function block performs the conversion by transforming the `TIME` value in milliseconds into a `ULINT` value. The conversion occurs synchronously when the ``REQ`` event occurs. After the conversion is complete, the ``CNF`` event is triggered, and the converted value is available at output ``OUT``.

- The function block uses the ``TIME_IN_MS_TO_ULINT`` function for the conversion.
- The implementation is in Structured Text (ST).
- The function block is part of the ``iec61131::conversion`` package.

The function block has no internal states. The conversion occurs immediately upon the occurrence of the ``REQ`` event.

- Conversion of time values for mathematical operations.
- Integration into systems that store or process timestamps as numeric values.

## Application Scenarios

## State Overview

## Technical Features

## Functionality

## Reverse Conversion (Numeric to TIME)

Often, a function like `DINT_TO_TIME` is sought to convert a numeric value (e.g., 500) back into a time value (e.g., 500 ms). Such an explicit conversion block doesn't usually exist, as this is elegantly solved using multiplication.

For this purpose, use the function block **`F_MULTIME`** (from the category `arithmetic`):

* Multiply your numeric value by the desired time base.
* **Example:** `500 * T#1ms = T#500ms`
* This allows for flexible scaling (e.g., * T#1s for seconds, * T#100ms for tenths of a second).
- Unlike generic conversion blocks, this function block is specialized for converting `TIME` to `ULINT`.
- Other blocks might offer additional options, such as conversion to other data types, but are less specific.

The `F_TIME_IN_MS_TO_ULINT` function block provides an efficient and specialized solution for converting millisecond time values to unsigned 64-bit integers. Its simple interface and straightforward operation make it ideal for applications that require numeric time values.

## ⚖️ Vergleich mit ähnlichen Bausteinen

## Conclusion