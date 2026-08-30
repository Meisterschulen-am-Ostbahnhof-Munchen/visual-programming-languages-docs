# STEST_END

![STEST_END](https://github.com/user-attachments/assets/1b3b48f8-4224-4d02-9c1c-d69e283b22a2)

* * * * * * * * * *
## Introduction

The STEST_END function block is a Service Interface Function Block that serves as an endpoint for service requests. It is typically used in conjunction with other service function blocks to implement a service-oriented architecture in the 4diac IDE.
![STEST_END](STEST_END.svg)

## Interface Structure

### **Event Inputs**

- **REQ**: Service Request - Triggered to initiate a service request.

### **Event Outputs**

No event outputs available.

### **Data Inputs**

No data inputs available.

### **Data Outputs**

No data outputs available.

### **Adapters**

No adapters available.

## Functionality

The STEST_END function block serves as an endpoint for service requests. When the REQ input is triggered, the service request is processed. Since it is an endpoint, there are no other event or data outputs.

## Technical Features

- Implemented as a Service Interface Function Block.
- Supports communication between RESOURCE and APPLICATION interfaces.

## State Overview

The function block has no complex states. It simply responds to and processes the REQ request.

## Application Scenarios

- As an endpoint in a service-oriented architecture.
- In test environments to simulate or terminate service requests.

## ⚖️ Comparison with Similar Function Blocks

Compared to other service function blocks, STEST_END has no outputs or additional interfaces, making it ideal as an endpoint.

## Conclusion

The STEST_END function block is a simple yet essential building block for service-oriented architectures in the 4diac IDE. Its simplicity makes it a reliable endpoint for service requests.

---

### 🌐 Related topic subpages on ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
