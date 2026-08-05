# ALI_TO_AS
![ALI_TO_AS](./ALI_TO_AS.svg)

* * * * * * * * * *
## Introduction
The **ALI_TO_AS** function block is a composite function block that converts an ALI adapter (data type LINT) into an AS adapter (data type SINT). It encapsulates the conversion of a 64-bit integer value to an 8-bit integer value, thus enabling seamless integration between different adapter interfaces in the 4diac IDE.
## Interface Structure
### **Event Inputs**
None. The function block has no separate event inputs; event control is handled via the connected adapters.

### **Event Outputs**
None. Events are forwarded exclusively via the AS adapter.

#
# ### **Data Inputs**
None. The LINT signal to be converted is read in via the ALI adapter.

### **Data Outputs**
None. The converted SINT signal is output via the AS adapter.

### **Adapters**

| Name | Type | Direction | Description |
|------|-----|----------|--------------|
| **ALI_IN** | `adapter::types::unidirectional::ALI` | Socket (Input) | Receives a LINT value (64-bit) via event E1 and date D1. |
| **AS_OUT** | `adapter::types::unidirectional::AS` | Plug (Output) | Provision of the converted SINT value (8-bit) via event E1 and data D1. |

## Functionality
The function block operates on the principle of pure data flow without its own state machine.

1. The **ALI_IN** adapter receives the **E1** event and provides the corresponding LINT value via data **D1**.

2. This event triggers the internal function block **F_LINT_TO_SINT**, which performs the conversion.

3. After the conversion is complete, the **CNF** event of the conversion block is activated, which in turn triggers the **E1** output event of the **AS_OUT** adapter and passes the converted SINT value via data **D1**.

The conversion corresponds to the IEC 61131 function `LINT_TO_SINT`. For values outside the SINT range (-128…127), an overflow occurs – the function block does not perform any additional range checks.

## Technical Features
- **Composite Structure**: The function block consists exclusively of a single conversion block (`F_LINT_TO_SINT`).
- **Unidirectional Adapters**: Both the input and output interfaces are defined as unidirectional adapters – data flows in only one direction.
- **No State Machine**: Due to the simple transformation, an internal state machine is not used; the logic is limited to event-data chaining.

## State Overview
The function block has **no** internal state machine. It operates purely data/event-driven and performs an immediate conversion upon each incoming event.

## Application Scenarios
- **Integration of LINT data sources** (e.g., from high-resolution counters, timestamps) into systems that only process SINT values (e.g., simple actuator controls).
- **Bridges between different adapter types** within a 4diac application, without the need for manual conversion blocks.

## Comparison with Similar Blocks
- **ALI_TO_INT**: Converts LINT to INT (16-bit).
- **LINT_TO_DINT** or similar: Direct type conversions without adapter encapsulation.

The **ALI_TO_AS** is distinguished by its specific adapter interface; it simplifies the reuse of pre-built adapter couplings in modules.

## Conclusion

The **ALI_TO_AS** is a specialized composite component for lossy conversion of a LINT value to a SINT value, embedded in a unidirectional adapter structure. It offers clean, reusable encapsulation of the conversion logic and facilitates the connection of diverse data sources and sinks within the 4diac development environment.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]
