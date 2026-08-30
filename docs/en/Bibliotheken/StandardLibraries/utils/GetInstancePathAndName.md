# GetInstancePathAndName

![GetInstancePathAndName](https://github.com/user-attachments/assets/818b4609-9a6a-4ec7-b8d8-dfd54f003751)

* * * * * * * * * *

## Introduction

The function block `GetInstancePathAndName` is used to retrieve the instance path and instance name from the runtime environment. This is particularly useful for debugging purposes or for dynamic configurations where the exact path of an instance is required.
![GetInstancePathAndName](GetInstancePathAndName.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service request that triggers the retrieval of the instance path and name. Concatenated with the separator character `Sep`.

### **Event Outputs**

- **CNF**: Acknowledgement of the requested service request. The output variables `Path` (instance path) and `Name` (instance name) are linked.

### **Data Inputs**

- **Sep** (CHAR): Separator character for the generated output path. The default value is `'/'`.

### **Data Outputs**

- **Path** (STRING): The instance path of the function block.
- **Name** (STRING): The instance name of the function block.

### **Adapters**

No adapters are available.

## Functionality

1. The function block is activated upon receiving a `REQ` event.
2. The function block determines the current instance path and instance name from the runtime environment.
3. The instance path is formatted with the specified separator character `Sep`.
4. The `CNF` event is triggered, and the determined values for `Path` and `Name` are output.

## Technical Features

- The default separator for the path is `'/'`, but it can be changed via the input `Sep`.
- The output variables `Path` and `Name` are of type `STRING` and contain the complete path and the instance name, respectively.

## State Overview

The function block has no internal state. It reacts exclusively to the `REQ` event and immediately outputs the corresponding data.

## Application Scenarios

- **Debugging**: Determining the exact path of an instance for troubleshooting.
- **Dynamic Configuration**: Using the instance path for dynamic configurations or logging.
- **System Monitoring**: Monitoring and logging instance paths in complex systems.

## ⚖️ Comparison with Similar Blocks

- Compared to other function blocks that provide similar information, `GetInstancePathAndName` offers the flexibility to customize the path separator.
- Other blocks might only provide the path or only the name, while this function block combines both.

## Conclusion

The `GetInstancePathAndName` function block is a simple yet powerful tool for retrieving instance information from the runtime environment. Its flexibility and simplicity make it ideal for debugging and dynamic configurations.
