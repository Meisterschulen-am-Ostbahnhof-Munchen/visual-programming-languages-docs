# CSV_WRITER_7

![CSV_WRITER_7](https://github.com/user-attachments/assets/7ae443fb-c96d-4894-a2ac-9103f6e76007)

* * * * * * * * * *
## Introduction

The CSV_WRITER_7 is a function block that writes data to a CSV file. It supports writing up to seven different data fields to a specified file. This function block is particularly useful for logging and data storage in automation applications.
![CSV_WRITER_7](CSV_WRITER_7.svg)
## Interface Structure

### **Event Inputs**

- **INIT**: Initializes the function block. Used with the variables `QI` (Qualifier Input) and `FILE_NAME` (CSV file name).
- **REQ**: Starts the write operation. Used with the variables `QI` and the seven data fields `SD_1` to `SD_7`.

### **Event Outputs**

- **INITO**: Confirms initialization. Returns `QO` (qualifier output) and `STATUS` (initialization status).
- **CNF**: Confirms the write operation is complete. Returns `QO` and `STATUS`.

### **Data Inputs**

- **QI**: Boolean qualifier indicating whether the operation should be performed.
- **FILE_NAME**: Name of the CSV file to which data should be written.
- **SD_1** to **SD_7**: Data fields that are written to the CSV file. Each field can have any data type (`ANY`).

### **Data Outputs**

- **QO**: Boolean qualifier indicating the success or failure of the operation.
- **STATUS**: String describing the status of the file access.

### **Adapters**

No adapters are present.

## Operation

1. **Initialization**: The function block is initialized by the `INIT` event. The filename (`FILE_NAME`) is passed to this event.
2. **Write Operation**: The `REQ` event triggers the write operation. The data `SD_1` to `SD_7` will be written to the specified CSV file.
3. **Confirmation**: Upon completion of the operation, the `CNF` event is triggered, which returns the status of the operation.

## Technical Features

- Supports writing to up to seven different data fields.
- The data fields can be of any data type (`ANY`).
- The file access status is returned in detail.

## State Overview

1. **Initialization State**: Waiting for the `INIT` event.
2. **Ready**: After successful initialization, the function block waits for the `REQ` event.
3. **Write Operation**: The function block is active during the write operation.
4. **Completed**: The `CNF` event is triggered after the write operation is complete.

## Application Scenarios

- Logging of process data in industrial automation.
- Storage of measurement data for later analysis.
- Data acquisition in real-time systems.

## ⚖️ Comparison with Similar Function Blocks

- **CSV_WRITER_5**: Supports only five data fields.
- **FILE_WRITER**: More general function block that is not specifically optimized for CSV files.

## Conclusion

The CSV_WRITER_7 is a powerful function block for storing data in CSV files. Its flexibility in supporting various data types and its detailed status feedback make it an ideal choice for many automation applications.
