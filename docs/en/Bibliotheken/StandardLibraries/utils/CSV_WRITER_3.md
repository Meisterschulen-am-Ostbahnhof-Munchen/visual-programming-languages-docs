# CSV_WRITER_3
![CSV_WRITER_3](https://github.com/user-attachments/assets/209218eb-3456-48f9-816f-d395f799dc7d)
* * * * * * * * * *
## Introduction
The CSV_WRITER_3 is a function block used to write data to a CSV file. It supports writing up to three different data fields to a file, specified via the parameter `FILE_NAME`. This function block is particularly useful for logging and data storage in automation systems.
![CSV_WRITER_3](CSV_WRITER_3.svg)
## Interface Structure

### **Event Inputs**
- **INIT**: Initializes the function block. Triggered with the data `QI` (Qualifier Input) and `FILE_NAME` (Filename).
- **REQ**: Starts the write operation. Triggered with the data `QI`, `SD_1`, `SD_2`, and `SD_3` (the data to be written).

### **Event Outputs**
- **INITO**: Confirms initialization. Returns `QO` (Qualifier Output) and `STATUS` (Initialization Status).
- **CNF**: Confirms completion of the write operation. Returns `QO` and `STATUS`.

### **Data Inputs**
- **QI**: Boolean value indicating the quality of the event input.
- **FILE_NAME**: String specifying the name of the CSV file.
- **SD_1**, **SD_2**, **SD_3**: Data fields of type `ANY` that are written to the CSV file.

### **Data Outputs**
- **QO**: Boolean value indicating the quality of the event output.
- **STATUS**: String indicating the status of the file access.

### **Adapters**
No adapters available.

## Functionality
The function block initializes upon receiving the `INIT` event and acknowledges this with `INITO`. Upon receiving the `REQ` event, the data `SD_1`, `SD_2`, and `SD_3` are written to the specified CSV file. The write status is reported via `CNF`.

## Technical Features
- Supports writing to up to three different data fields.
- The data type of the data to be written is `ANY`, allowing for high flexibility.
- Detailed file access status is reported.

## State Overview

1. **Initialization State**: Waiting for the `INIT` event.

2. **Ready State**: After successful initialization, waits for the `REQ` event.

3. **Write State**: Writes data to the CSV file and reports the status back.

## Application Scenarios
- Logging sensor data to a CSV file.
- Storing process data for later analysis.
- Exchanging data with other systems via CSV files.

## ⚖️ Comparison with Similar Function Blocks
- Compared to simpler CSV writer function blocks, `CSV_WRITER_3` supports writing to multiple data fields (`SD_1`, `SD_2`, `SD_3`).

Other function blocks might be restricted to specific data types, while `CSV_WRITER_3` uses the `ANY` type.

## Conclusion
The `CSV_WRITER_3` is a flexible and powerful function block for storing data in CSV files. Its support for multiple data fields and the `ANY` data type makes it particularly versatile.