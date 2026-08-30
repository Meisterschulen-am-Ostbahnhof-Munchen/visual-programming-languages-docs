# CSV_WRITER_8

![CSV_WRITER_8](https://github.com/user-attachments/assets/1bef9b69-8591-4f61-b6e1-2589d51844b3)

* * * * * * * * * *

## Introduction

The CSV_WRITER_8 is a function block for outputting data to a CSV file. It allows you to write up to 8 different data values to a specified file. This function block is part of the eclipse4diac::utils package family and is particularly suitable for data acquisition and logging tasks.
![CSV_WRITER_8](CSV_WRITER_8.svg)

## Interface Structure

### **Event Inputs**

- **INIT**: Initializes the function block. It uses the variables QI (Qualifier) and FILE_NAME (Filename).
- **REQ**: Triggers a write operation. It uses QI and the data variables SD_1 to SD_8.

### **Event Outputs**

- **INITO**: Confirms initialization. Returns QO (qualifier) and STATUS (status message).
- **CNF**: Confirms the completion of the write operation. Also returns QO and STATUS.

### **Data Inputs**

- **QI**: Boolean qualifier for events.
- **FILE_NAME**: String specifying the path and name of the CSV file.
- **SD_1 to SD_8**: Data variables of type ANY to be written to the CSV file.

### **Data Outputs**

- **QO**: Boolean qualifier for output events.
- **STATUS**: String describing the status of the file access.

## Functionality

The function block initializes itself upon receiving the INIT event and confirms this with INITO. The REQ event writes the current values of SD_1 to SD_8 to the specified CSV file. After the write operation is complete, the CNF event is triggered.

## Technical Features

- Supports generic data types (ANY) for output data.
- Provides status messages for successful and failed operations.
- Part of the eclipse4diac::utils package.

## State Overview

1. **Initialization State**: Waiting for the INIT event.
2. **Ready**: After successful initialization.
3. **Write Operation**: Active during the REQ event.
4. **Acknowledgement**: Sends CNF upon completion.

## Application Scenarios

- Logging of process data.
- Data acquisition for analysis purposes.
- Export of control data in CSV format.

## ⚖️ Comparison with Similar Blocks

Compared to simpler CSV writer blocks, CSV_WRITER_8 offers the ability to write up to 8 different data values simultaneously and process generic data types.

## Conclusion

CSV_WRITER_8 is a powerful function block for data acquisition and logging in CSV files. Its data processing flexibility and detailed status messages make it a good choice for complex applications.

---

### 🌐 Related Topic Subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
