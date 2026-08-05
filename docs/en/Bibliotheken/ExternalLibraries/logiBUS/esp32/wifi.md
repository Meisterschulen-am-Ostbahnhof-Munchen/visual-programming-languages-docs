# wifi

![wifi](./wifi.svg)

* * * * * * * * * *
## Introduction
The "wifi" function block is a Service Interface Function Block (SIFB) for controlling a WLAN connection. It provides the INIT, START, and STOP events for initializing, starting, and stopping the WLAN. The connection status is returned as a string via the STATUS output. The block is designed for use in automation systems that require a wireless network connection.

## Interface Structure
### **Event Inputs**
- **INIT** (EInit): Initializes the block and prepares the WLAN interface.

- **START** (EInit): Starts the WLAN connection.

- **STOP** (EInit): Stops the WLAN connection.

### **Event Outputs**

- **INITO** (EInit): Confirms successful initialization. Triggered in conjunction with the STATUS data output.

### **Data Inputs**
No data inputs available.

### **Data Outputs**
- **STATUS** (WSTRING): Displays the current status of the WLAN service (e.g., "OK", "Error", "Connected", "Disconnected").

#### **Adapters**
No adapters available.

## Functionality
The function block operates on the principle of a Service Interface Function Block. The internal logic is provided by the runtime environment. Typically, INIT is called first to configure the function block. The WLAN connection can then be activated with START. The connection is terminated with STOP. The STATUS output returns the current state after each operation.

## Technical Features
- The function block is implemented as a SIFB (Service Interface Function Block) according to IEC 61499-2.

- The interface is open to both the RESOURCE and APPLICATION sides, enabling flexible integration.

- The exact implementation depends on the underlying hardware and operating system.

## State Overview
The module goes through the following basic states:

- **Uninitialized**: After startup, before INIT is executed.

- **Initialized**: After successful INIT, ready for START.

- **Active (Connected)**: After successful START.

- **Inactive (Disconnected)**: After STOP or in case of an error.

## Application Scenarios

- Controlling a WLAN interface in agricultural machinery or other vehicles.

- Integrating devices into a wireless network for data transmission in automation technology.

- Remote maintenance and diagnostics via WLAN.

## Comparison with Similar Modules

Similar modules include Ethernet or serial communication modules. Unlike these, the Wi-Fi module focuses specifically on wireless WLAN connections and offers a simplified, event-driven interface. Other modules often require more complex configurations or support multiple protocols.


## Conclusion

The "wifi" function block offers a simple and standardized way to integrate a WLAN connection into IEC 61499 systems. With its three events INIT, START, and STOP, as well as its STATUS output, it is intuitive to use and particularly suitable for applications requiring fast and reliable wireless communication.