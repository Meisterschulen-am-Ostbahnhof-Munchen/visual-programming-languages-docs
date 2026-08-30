# CSV_WRITER_2

![CSV_WRITER_2](https://github.com/user-attachments/assets/3c2f2095-ba2e-4a3a-9484-9f5c310500e9)

* * * * * * * * * *

## Introduction

The CSV_WRITER_2 is a function block used to write data to a CSV file. It provides a simple interface for initialization and the writing process, supporting two different data fields. This function block is particularly useful for applications where data needs to be stored persistently or exported for further analysis.
![CSV_WRITER_2](CSV_WRITER_2.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Initializes the function block and configures the filename for the CSV file.
- Input data: `QI` (BOOL), `FILE_NAME` (STRING)
- **REQ**: Starts the data writing process to the CSV file.
- Input data: `QI` (BOOL), `SD_1` (ANY), `SD_2` (ANY)

### **Event Outputs**

- **INITO**: Confirms the initialization of the function block.
- Output data: `QO` (BOOL), `STATUS` (STRING)
- **CNF**: Confirms the successful completion of the write operation.
- Output data: `QO` (BOOL), `STATUS` (STRING)

### **Data Inputs**

- **QI**: Qualifies the event (TRUE for valid, FALSE for invalid).
- **FILE_NAME**: The name of the CSV file to be written to.
- **SD_1**: The first data field to be written to the CSV file (any data type).
- **SD_2**: The second data field to be written to the CSV file (any data type).

### **Data Outputs**

- **QO**: Qualifies the output event (TRUE for success, FALSE for failure).
- **STATUS**: Returns the status of the file access (e.g., success message or error description).

### **Adapters**

This function block has no adapters.

## Operation

1. **Initialization**: Sending a `INIT` event with the desired file name (`FILE_NAME`) initializes the function block. The initialization status is reported via `INITO`.
2. **Write Data**: The `REQ` event triggers the write operation. The data `SD_1` and `SD_2` are written to the CSV file. The success or failure of the write operation is reported via `CNF`.

## Technical Features

- Supports any data type for the data to be written (`SD_1` and `SD_2`).
- The status (`STATUS`) provides detailed information about the success or failure of the file access.
- The function block is part of the `eclipse4diac::utils` package.

## Status Overview

1. **Inactive**: The function block is waiting for initialization.
2. **Initialized**: The function block is ready to write data.
3. **Write Operation**: The function block is writing data to the CSV file.

## Application Scenarios

- Logging process data to a CSV file for later analysis.
- Exporting measurement data for external evaluation.
- Storing configuration data in a readable format.

## ⚖️ Comparison with Similar Function Blocks

- Compared to simpler write function blocks, `CSV_WRITER_2` supports two data fields and provides detailed status feedback.
- Other CSV write function blocks may be less flexible in their data type support or may not provide status feedback.

## Conclusion

The `CSV_WRITER_2` function block is a flexible and reliable function block for writing data to CSV files. Its support for arbitrary data types and detailed status feedback make it ideal for applications that require persistent data storage.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
