# START

## 🎧 Podcast

![START](./START.svg)

* [Events and IEC 61499: The Starting Signal for Intelligent Systems ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Ereignisse-und-IEC-61499-Der-Startschuss-fr-intelligente-Systeme-e368461)
## Introduction

The `START` constant declaration defines a set of integer constants (of type `UINT`) for use in control programs. These constants represent specific states typically used in sequence controls, such as for sliders. They improve code readability and maintainability by replacing numeric values with meaningful names.

## Interface Structure

START` is a **GlobalConstants** declaration and not a function block. Therefore, it does not have event- or data-flow-based interfaces such as inputs or outputs. Instead, it defines global, constant values that can be referenced within other function blocks or programs.

### **Event Inputs**

*Not applicable.* This declaration does not contain any event inputs.

### **Event Outputs**

*Not applicable.* This declaration does not contain any event outputs.

### **Data Inputs**

*Not applicable.* This declaration does not contain any data inputs.

### **Data Outputs**

*Not applicable.* This declaration does not contain any data outputs.

### **Adapters**

*Not applicable.* This declaration does not use adapters.

## Functionality

The `START` constant declaration assigns fixed, unchanging numerical values to the symbolic names `STARTClosed`, `STARTOpened`, and `STARTUnknown`. Once this declaration is included in a project, the defined names can be used throughout the application code instead of the raw numbers (5, 6, 7). During compilation, the compiler replaces any reference to, for example, `STARTClosed` with the value `UINT#5`.

## Technical Details

* **Type:** All constants are of type `UINT` (unsigned integer).
* **Scope of Validity:** The constants are defined globally (`VAR_GLOBAL CONSTANT`) and available within the declared package (`logiBUS::utils::sequence::schieber::const`).
* **Immutability:** As constants (`CONSTANT`), their values cannot be changed at runtime.
* **Package Structure:** The constants are organized in a specific package hierarchy that reflects their application domain (auxiliary functions for sequence control of sliders).

## State Overview

The constants themselves represent abstract states:

* `STARTClosed` (value 5): Represents the state "closed" or "in starting position".
* `STARTOpened` (value 6): Represents the state "open" or "in end position".
* `STARTUnknown` (value 7): Represents an undefined, unknown, or error state.

## Application Scenarios

Primarily, these constants are used in state machines or sequencer function blocks to uniquely and readably encode the current position or status of an actuator (such as a linear slider). For example, a function block could set its internal state or an output value to `STARTOpened` to indicate that the slider is fully open.

## ⚖️ Comparison with Similar Function Blocks

Unlike function blocks such as `E_SR` (flip-flop) or `E_CYCLE` (cycle encoder), `START` has no algorithm or behavioral logic. It is a pure data declaration. Similar constructs would be other `GlobalConstants` or `Type` declarations, which also provide symbolic names for values (e.g., for error codes or operating modes).

## Conclusion

The `START` constant declaration is a simple yet essential tool for structuring and professionalizing IEC 61499-based control applications. By using meaningful names instead of "magic numbers," the code becomes significantly more understandable, less error-prone, and easier to maintain. Its integration is particularly recommended in larger projects or reusable library components.
