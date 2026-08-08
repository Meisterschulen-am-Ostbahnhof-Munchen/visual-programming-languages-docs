# GetInstancePath
![GetInstancePath](https://github.com/user-attachments/assets/325783e2-0c06-4d8f-bdf5-56508a4e6f25)

* * * * * * * * * *
The function block `GetInstancePath` is used to determine the instance path of the function block within the 4diac IDE. This path can be used, for example, for diagnostic purposes or for dynamic configuration. The function block is particularly useful in complex applications where precise identification of the instance location is required.
![GetInstancePath](GetInstancePath.svg)

- **REQ**: Service request. Triggers the determination of the instance path.

- **CNF**: Acknowledgement of the service request. Signals successful determination of the instance path.

- **Sep**: Separator character (CHAR) for the generated path. The default value is `'/'`.

- **Path**: The determined instance path as a STRING.

### Data Outputs
### Data Inputs
### Event Outputs
### Event Inputs
## Interface Structure
## Introduction
#### **Adapters**
No adapters available.

## Functionality
1. Upon receiving the `REQ` event, the function block begins determining its own instance path.

2. The path is formatted with the specified separator character (`Sep`).

3. The `CNF` event is triggered, and the determined path is output via the `Path` output.

- The function block uses a service interface to communicate with the resource level.


- **Idle**: Waiting for a `REQ` request.
- **Processing**: Determines the instance path and outputs it via `CNF`.

- Diagnostics and Logging: Identifying the exact location of a function block instance in a complex application.
- Dynamic Configuration: Using the path to dynamically adjust parameters or behaviors.

- Unlike static path specifications, `GetInstancePath` allows for dynamic path determination, which is particularly advantageous in reusable or nested components.


The `GetInstancePath`-FB is a useful tool for dynamically determining the instance path in 4diac applications. Its simple interface and flexible configuration make it ideal for diagnostic and configuration purposes.

--

* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

## Technical Features
## State Overview
## Application Scenarios
## ⚖️ Vergleich mit ähnlichen Bausteinen
## Conclusion
### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de