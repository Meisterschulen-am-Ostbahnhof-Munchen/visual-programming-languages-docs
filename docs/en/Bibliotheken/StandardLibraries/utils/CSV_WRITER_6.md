# CSV_WRITER_6
![CSV_WRITER_6](https://github.com/user-attachments/assets/f5ac4221-a93b-49d5-b7b3-280d171a347a)
* * * * * * * * * *
## Introduction
The function block `CSV_WRITER_6` is used to write data to a CSV file. It allows the storage of up to six different data values in a comma-separated format. The block is particularly useful for data acquisition and logging in automation systems.
![CSV_WRITER_6](CSV_WRITER_6.svg)
## Interface Structure

### **Event Inputs**
- `INIT`: Initializes the function block. Triggered by the variables `QI` and `FILE_NAME`.
- `REQ`: Starts the write operation. Triggered by the variables `QI`, `SD_1` through `SD_6`.

### **Event Outputs**
- `INITO`: Confirms initialization. Returns `QO` and `STATUS`.
- `CNF`: Confirms successful write operation. Returns `QO` and `STATUS`.

### **Data Inputs**
- `QI` (BOOL): Qualifies the event (e.g., whether the write operation should be activated).
- `FILE_NAME` (STRING): Name of the CSV file to be written to.
- `SD_1` to `SD_6` (ANY): The data values to be written.

### **Data Outputs**
- `QO` (BOOL): Qualifies the output event (e.g., whether the operation was successful).
- `STATUS` (STRING): File access status message.

### **Adapters**
No adapters available.

## Functionality

1. **Initialization**: The `INIT` event initializes the function block with the file name (`FILE_NAME`). The status is reported via `INITO`.

2. **Write Operation**: The `REQ` event triggers the write operation. The data `SD_1` to `SD_6` are written to the CSV file. Success is confirmed via `CNF`.

## Technical Features
- Supports any data type (`ANY`) for the data to be written.
- The status (`STATUS`) provides detailed information about whether the file access was successful or failed.

## State Overview

1. **Initialization State**: Waiting for the `INIT` event.

2. **Ready State**: After successful initialization, waits for the `REQ` event.

3. **Write State**: Processes the data and writes it to the file.

## Application Scenarios
- Real-time logging of sensor data.
- Storage of process data for later analysis.
- Data acquisition in test and validation environments.

## ⚖️ Comparison with Similar Blocks
- Compared to simpler CSV writer blocks, `CSV_WRITER_6` offers the ability to store up to six different data values simultaneously.
- Other blocks may be limited to specific data types, while this block supports `ANY` types.

## Conclusion

The `CSV_WRITER_6` is a flexible and powerful function block for storing data in CSV files. Its support for various data types and the ability to store multiple values simultaneously make it ideal for complex data collection tasks.