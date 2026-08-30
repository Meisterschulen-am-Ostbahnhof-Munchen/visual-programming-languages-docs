# STATES

![STATES](./STATES.svg)

* * * * * * * * * *
## Introduction

The global constant declaration `STATES` defines a collection of predefined state labels as strings (STRING). These constants are typically used to name operating states in a control sequence, especially for processes with alternating direction (clockwise/counterclockwise) and integrated pauses. It serves as a central and consistent source for these state names within a project.
## Interface Structure

Global constants are not function blocks with event or data interfaces. Instead, they declare constant values that are available project-wide.

### **Data Declarations**

The following constants are defined:

- `Rechtslauf`: String with the value `'Rechtslauf'`
- `Linkslauf`: String with the value `'Linkslauf'`
- `Linkslauf_Pause`: String with the value `'Linkslauf_Pause'`
- `Rechtslauf_Pause`: String with the value `'Rechtslauf_Pause'`

## Functionality

The constants themselves have no active functionality. They merely provide named values. Their main purpose is to avoid "magic numbers" or hard-coded strings in the program code. Using these constants makes the code more readable, maintainable, and less error-prone, as changes to the state names only need to be made in one central location.

## Technical Details

- **Type:** All declared constants are of the data type `STRING`.
- **Scope:** As global constants, they are available within the entire namespace `logiBUS::utils::sequence::verteiler::LinksRechts` and in components that depend on it.
- **Initialization:** The values are set directly during declaration using the `InitialValue` attribute.

## State Overview

Not applicable, as this is a static data declaration and not a stateful component.

## Application Scenarios

Typical applications for these constants include:

- **State Machines:** These constants can serve as unique identifiers for the different states of a state machine that controls a process with changes of direction and pauses (e.g., a distribution table).
- **Documentation and Logging:** They can be used to display the current operating state in messages, log files, or on operator panels.
- **Comparisons and Switching Logic:** In program logic, variables or outputs can be compared with these constants to make decisions based on the current state.

## ⚖️ Comparison with Similar Function Blocks

- **Global Variables (VAR_GLOBAL):** Unlike global variables, the values of constants (`CONSTANT`) cannot be changed at runtime.
- **Enumerations (ENUM):** While ENUM data types serve similar purposes in some programming languages, the IEC 61499 standard library does not provide a built-in ENUM type. Using STRING constants is a common method for defining semantically named values in this environment.
- **Function Block-Internal Constants:** Constants can also be defined within function blocks. However, global constants are visible across block boundaries, thus promoting reusability and consistency throughout an entire project.

## Conclusion

The global constant declaration `STATES` is a simple yet useful construct for structuring control software. It improves code quality by providing central and immutable state labels specifically tailored for sequences with forward/reverse and pause states. Its use makes programs more understandable and facilitates future modifications.
