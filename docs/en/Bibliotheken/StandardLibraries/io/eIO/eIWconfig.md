# eIWconfig
<img width="1398" height="243" alt="image" src="https://github.com/user-attachments/assets/9688743e-0091-4849-bd83-351768377028" />
* * * * * * * * * *
## Introduction
The eIWconfig function block serves as a service interface for configuring eIO instances. It allows you to set thresholds and gradients for industrial I/O operations.
![eIWconfig](eIWconfig.svg)

## Interface Structure

### **Event Inputs**
- **CONF**: Configuration request - triggers the configuration of the eIO instance

### **Event Outputs**
- **CNF**: Confirmation of the requested service - signals the completion of the configuration

### **Data Inputs**
- **ST** (WORD): "Smaller than" - Lower threshold
- **BT** (WORD): "Bigger than" - Upper threshold
- **GRAD** (WORD): Gradient in percent - Steepness of the transitions

### **Data Outputs**
- **STATUS** (WSTRING): Service status - feedback on the configuration process

### **Adapter**
- **eIW**: Connection to the eIO instance (Type: eclipse4diac::io::eio::eGenAdapter)

## Functionality
The function block receives via The CONF event is a configuration request along with the parameters ST, BT, and GRAD. These parameters are transmitted to the eIO instance via the eIW adapter. After successful configuration, the block confirms the process with the CNF event and provides status feedback via STATUS.

Conf event. ## Technical Features
- Uses WORD data types for all numeric inputs
- STATUS output as WSTRING for detailed status information
- Adapter-based architecture for loose coupling to the eIO instance

## State Overview
1. **Ready**: Waiting for CONF event

2. **Configuring**: Processing configuration parameters
3. **Acknowledging**: Sending CNF event with status information

## Application Scenarios
- Configuration of I/O thresholds in automation systems
- Setting filter parameters for sensor signals
- Dynamic adjustment of limit values in control systems

## ⚖️ Comparison with Similar Blocks
Compared to simple I/O configuration blocks, eIWconfig offers extended functionality with gradient control and an adapter-based architecture for greater flexibility.

## Conclusion

The eIWconfig function block provides a flexible and extensible solution for configuring eIO instances, distinguished by its adapter-based architecture and extensive parameterization options.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]