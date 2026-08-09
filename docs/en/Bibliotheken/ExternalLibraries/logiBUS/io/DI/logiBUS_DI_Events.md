# logiBUS_DI_Events

![logiBUS_DI_Events](./logiBUS_DI_Events.svg)

* * * * * * * * * *
## Introduction

The GlobalConstants definition `logiBUS_DI_Events` provides a comprehensive collection of event constants for digital inputs (DI) in the logiBUS system. These constants define various button press events and their unique identifiers, which are used in the control logic for processing user input via pushbuttons.
## Functionality

The GlobalConstants definition `logiBUS_DI_Events` contains 14 different event constants of type `logiBUS_DI_Events_S`, each identified by a unique numeric value (`EType`). These constants are used to represent various states and events of pushbuttons in the control logic.

## Technical Features

- **Structure Type**: All constants use the data type `logiBUS_DI_Events_S`
- **Value Range**: The EType values range from 0-12 for valid events, with 255 for invalid events
- **Package Membership**: `logiBUS::io::DI`
- **Constant Definition**: All values are declared as global constants (CONSTANT)

Documentation for the individual events: <https://components.espressif.com/components/espressif/button>

## State Overview

The event constants cover the following states:

| EType | Constant | Description |
|-------|-----------|--------------|
| 0 | BUTTON_PRESS_DOWN | Button pressed |
| 1 | BUTTON_PRESS_UP | Button released |
2 | BUTTON_PRESS_REPEAT | Button pressed again |
3 | BUTTON_PRESS_REPEAT_DONE | Button repeat ended |
4 | BUTTON_SINGLE_CLICK | Single click |
5 | BUTTON_DOUBLE_CLICK | Double click |
6 | BUTTON_MULTIPLE_CLICK | Multi-click |
7 | BUTTON_LONG_PRESS_START | Long press begins |
8 | BUTTON_LONG_PRESS_HOLD | Long press is held |
9 | BUTTON_LONG_PRESS_UP | Long press ends |
10 | BUTTON_PRESS_END | Press ends |
11 | BUTTON_EVENT_MAX | Maximum event ID |
12 | BUTTON_NONE_PRESS | No key press |
255 | Invalid | Invalid event |
...
## Application Scenarios

- **User Interface Control**: Processing keystrokes on operator panels
- **Machine Control**: Capturing manual inputs on industrial controllers
- **Safety Systems**: Monitoring emergency stop buttons and safety switches
- **Menu Navigation**: Controlling display menus via keystrokes
- **State Monitoring**: Detecting various keystroke patterns

## ⚖️ Comparison with Similar Function Blocks

Unlike simple digital input blocks that only detect binary states (ON/OFF), `logiBUS_DI_Events` offers advanced event detection with:

- Time-resolved events (Press/Release)
- Complex interaction patterns (Clicks, Double-Clicks)
- Long-term detection (Long Press)
- Repeat functionality

## Conclusion

The `logiBUS_DI_Events` The GlobalConstants definition provides a comprehensive and structured basis for processing push-button events in industrial control systems. Through standardized event codes, it enables a consistent and maintainable implementation of user interactions via digital inputs.
