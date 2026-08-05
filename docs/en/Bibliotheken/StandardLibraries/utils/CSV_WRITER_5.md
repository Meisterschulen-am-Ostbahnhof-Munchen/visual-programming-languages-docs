# CSV_WRITER_5
![CSV_WRITER_5](https://github.com/user-attachments/assets/f24a7a1e-0d03-409e-8ce7-c7d9a9719c2c)
* * * * * * * * * *
## Introduction
The CSV_WRITER_5 is a function block for outputting data to a CSV file. It allows you to write up to five different data points to a user-defined file. This function block is particularly useful for data acquisition and logging applications.
![CSV_WRITER_5](CSV_WRITER_5.svg)
## Interface Structure

### **Event Inputs**
- **INIT**: Initializes the function block and opens the specified CSV file.
- Linked Data: QI (BOOL), FILE_NAME (STRING)
- **REQ**: Triggers the write operation.
- Linked Data: QI (BOOL), SD_1 to SD_5 (ANY)

### **Event Outputs**
- **INITO**: Confirms initialization.
- Linked Data: QO (BOOL), STATUS (STRING)
- **CNF**: Confirms successful write operation.
- Linked Data: QO (BOOL), STATUS (STRING)

### **Data Inputs**
- **QI**: Qualifies the event (TRUE for active, FALSE for inactive).
- **FILE_NAME**: Name of the CSV file to be written to.
- **SD_1 to SD_5**: The data to be written (any type).

### **Data Outputs**
- **QO**: Returns the status of the function block (TRUE for successful, FALSE for error).
- **STATUS**: Contains a status message about the last operation.

### **Adapters**
No adapters available.

## Functionality

1. **Initialization**: The INIT event opens the CSV file with the specified name. If the file does not exist, it will be created.

2. **Write Data**: The REQ event triggers the write operation. Data SD_1 to SD_5 is written as a single line to the CSV file.

3. **Acknowledge**: After each write operation, the CNF event is triggered, which returns the status of the operation.

## Technical Features
- Supports any data type for the output data (ANY).
- The status output (STATUS) returns detailed error messages.
- Initialization can be repeated if necessary to open a new file.

## Status Overview
- **Inactive**: Waiting for initialization.
- **Ready**: File is open and ready for write operations.
- **Error**: An error has occurred (e.g., file access denied).

## Application Scenarios
- Logging sensor data.
- Storing process data for later analysis.
- Export of data to a table-based format.

## ⚖️ Comparison with similar building blocks
- Compared to simpler CSV writer blocks, CSV_WRITER_5 offers greater flexibility by supporting five data points and any data type.
- Other blocks might be limited to specific data types or support fewer data points.

## Conclusion
CSV_WRITER_5 is a powerful and flexible function block for data collection and logging. Its support for any data type and multiple data points makes it ideal for complex applications.