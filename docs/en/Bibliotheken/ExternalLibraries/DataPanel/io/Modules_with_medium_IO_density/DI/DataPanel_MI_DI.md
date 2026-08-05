# DataPanel_MI_DI
![DataPanel_MI_DI](./DataPanel_MI_DI.svg)

* * * * * * * * * *
## Introduction
DataPanel_MI_DI is a global constant definition for medium I/O density DataPanel modules for digital inputs (DI). This constant defines the pin assignments for various digital input channels of a DataPanel system.
## Interface Structure
### **Event Inputs**
*No event inputs available*

### **Event Outputs**
*No event outputs available*

### **Data Inputs**
*No data inputs available*

### **Data Outputs**
*No data outputs available*

#### **Adapters**
*No adapters available*

## Functionality
DataPanel_MI_DI is a global constant definition that provides fixed values for the pin assignments of the digital inputs. The constant defines structured data of type `DataPanel_MI_DI_S` with PIN numbers for various digital input channels.

```
## Technical Features
- Defines pin assignments for 8 digital input channels (5A, 5B, 6A, 6B, 7A, 7B, 8A, 8B)
- Pin numbers range from 9 to 16
- Includes a special "Invalid" constant with a pin value of 255 for error handling
- Uses the structured data type `DataPanel_MI_DI_S`
- Organized in the package `DataPanel::io::MI::DI`

## State Overview
*No state transitions are present - this is a static constant definition*

## Application Scenarios
- Configuration of DataPanel systems with medium I/O density
- Hardware abstraction for digital inputs in control systems
- Simplification of pin assignment in IEC 61499-based applications
- Reusable constant definition for multiple projects

## ⚖️ Comparison with Similar Components

Compared to other constant definitions, DataPanel_MI_DI offers:

- Specific pin assignments for DataPanel hardware
- Structured data types for improved type safety
- Predefined invalid constant for robustness

## Conclusion
DataPanel_MI_DI provides a standardized and type-safe way to configure digital input pins in DataPanel systems with medium I/O density. The use of structured constants increases maintainability and reduces configuration errors in automation projects.
