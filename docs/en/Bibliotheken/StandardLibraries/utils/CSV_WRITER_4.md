# CSV_WRITER_4

![CSV_WRITER_4](https://github.com/user-attachments/assets/376f3f75-18f2-4d8b-95ab-be25457694f3)

* * * * * * * * * *
## Introduction
The CSV_WRITER_4 function block is used to write data to a CSV file. It supports saving up to four different data values in a structured format. The function block is particularly useful for data acquisition and logging in automation applications.

![CSV_WRITER_4](CSV_WRITER_4.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Initializes the function block and configures the output file. It links to data in `QI` and `FILE_NAME`.

- **REQ**: Triggers the write operation. Linked to `QI` and the data values `SD_1` through `SD_4`.

### **Event Outputs**

- **INITO**: Confirms initialization. Returns `QO` and `STATUS`.

- **CNF**: Confirms the write operation is complete. Returns `QO` and `STATUS`.

### **Data Inputs**

- **QI** (BOOL): Qualifies the INIT and REQ events.

- **FILE_NAME** (STRING): Name of the CSV file.

- **SD_1** to **SD_4** (ANY): The data values to be written (up to 4 different ones).

### **Data Outputs**

- **QO** (BOOL): Qualifies the output events.

- **STATUS** (STRING): Status message about file access.

#### **Adapters**
No adapters available.

## Functionality

1. **Initialization**: The INIT event with `QI` active prepares the CSV file with the specified `FILE_NAME`.

2. **Write Data**: The REQ event with `QI` active triggers the write operation. The values from `SD_1` to `SD_4` are written to the file.

3. **Confirmation**: After each operation (INIT or REQ), the status is reported via `INITO` or `CNF`.

## Technical Features
- Supports generic data types (ANY) for the data to be written.

- The function block is part of the `eclipse4diac::utils` package.

- The generic class is defined as `GEN_CSV_WRITER`.

## Status Overview
1. **Inactive**: Waiting for initialization.

2. **Initialized**: File is ready, waiting for write requests.

3. **Writing**: Processing a write request.

## Application Scenarios

- Logging of process data.

- Data acquisition for analysis purposes.

- Export of measured values to a standardized format.

## ⚖️ Comparison with Similar Function Blocks
- Compared to simpler write function blocks, CSV_WRITER_4 offers the ability to store multiple data values simultaneously.

- The use of ANY types makes it more flexible than function blocks with fixed data types.

## Conclusion
CSV_WRITER_4 is a versatile function block for data acquisition, particularly well-suited for applications that require logging structured data. Its flexibility and ease of integration make it a practical solution for many automation tasks.

--

### 🌐 Related topic subpages on ms-muc-docs.de

* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]