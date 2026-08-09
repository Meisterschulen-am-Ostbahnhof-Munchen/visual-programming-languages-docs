# CSV_WRITER_1

![CSV_WRITER_1](https://github.com/user-attachments/assets/4f7fdcfb-c9cf-4e0a-8347-ccdc85acd150)

* * * * * * * * * *
## Introduction

The function block `CSV_WRITER_1` serves as a service interface for writing data to a CSV file. It enables the initialization of the write operation and the controlled writing of data to a file with status feedback.
![CSV_WRITER_1](CSV_WRITER_1.svg)
## Interface Structure

### **Event Inputs**

- **INIT**: Initializes the write service. Triggered by the variables `QI` (qualifier) and `FILE_NAME` (filename).
- **REQ**: Requests the writing of data. Triggered by the variables `QI` and `SD_1` (data to be written).

### **Event Outputs**

- **INITO**: Confirms initialization. Returns `QO` (qualifier) and `STATUS` (initialization state).
- **CNF**: Confirms completion of the write operation. Returns `QO` and `STATUS` (write operation state).

### **Data Inputs**

- **QI**: Boolean qualifier for events.
- **FILE_NAME**: String specifying the name of the file to be written.
- **SD_1**: Data of type `ANY` to be written to the CSV file.

### **Data Outputs**

- **QO**: Boolean qualifier for output events.
- **STATUS**: String returning the file access status.

### **Adapters**

No adapters available.

## Functionality

1. **Initialization**: The `INIT` event initializes the write service with the specified filename (`FILE_NAME`). The status is returned via `INITO`.
2. **Write Data**: The `REQ` event triggers the data write operation (`SD_1`). Success or failure is reported via `CNF` and `STATUS`.

## Technical Features

- Supports generic data types (`ANY`) for the data to be written.
- Status feedback as a string for detailed error analysis.

## Status Overview

- **Initialization State**: Set by `INIT` and confirmed by `INITO`.
- **Write State**: Activated by `REQ` and completed by `CNF`.

## Application Scenarios

- Logging of process data to CSV files.
- Export of measurement data for further analysis.
- Automated data storage in industrial control systems.

## ⚖️ Comparison with Similar Blocks

- Compared to simple file write blocks, `CSV_WRITER_1` offers detailed status feedback and support for generic data types.
- Other blocks might be limited to specific data types or offer less feedback.

## Conclusion

The `CSV_WRITER_1` is a flexible and reliable function block for writing data to CSV files, ideal for applications that require robust logging and data export functionality.
