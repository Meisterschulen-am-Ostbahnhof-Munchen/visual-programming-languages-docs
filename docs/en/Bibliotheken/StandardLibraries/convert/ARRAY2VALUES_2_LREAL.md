# ARRAY2VALUES_2_LREAL
<img width="1227" height="178" alt="image" src="https://github.com/user-attachments/assets/1fda84e9-cd29-43f7-a566-6a8e259fa26f" />
* * * * * * * * * *
## Introduction
The function block `ARRAY2VALUES_2_LREAL` is a service interface module designed to split an array of two `LREAL` values into two separate `LREAL` output variables. It facilitates the simple conversion from a structured array format to individual data points.
![ARRAY2VALUES_2_LREAL](ARRAY2VALUES_2_LREAL.svg)
## Interface Structure
### **Event Inputs**
* **REQ**: A service request event that initiates the conversion. It is associated with the data input `IN`.

### **Event Outputs**
* **CNF**: An acknowledgment event that signals the completion of the requested service. It is associated with the data outputs `OUT_1` and `OUT_2`.

### **Data Inputs**
* **IN**: An array input of type `LREAL` with a size of 2 elements. This array contains the two values to be split.

### **Data Outputs**
* **OUT_1**: The first output value of type `LREAL`, corresponding to the first element of the `IN` array.

### **Data Inputs**
* **OUT_1**: The first output value of type `LREAL`, corresponding to the first element of the `IN` array. * **OUT_2**: The second output value of type `LREAL`, corresponding to the second element of the `IN` array.

### **Adapter**
Not present.

## Functionality
When the `REQ` event is received, the `ARRAY2VALUES_2_LREAL` function block reads the two `LREAL` values from the `IN` array. The first element of the `IN` array (`IN[0]`) is assigned to the output `OUT_1`, and the second element (`IN[1]`) is assigned to the output `OUT_2`. Upon successful assignment, the `CNF` event is triggered to signal the completion of the operation.

## Technical Details
This function block is specifically designed to process exactly one array of two `LREAL` values and split them into two separate `LREAL` variables. Its implementation is straightforward and optimized for this specific conversion purpose.

* **Generic Implementation:** Interestingly, the attribute `eclipse4diac::core::GenericClassName` references `'GEN_ARRAY2ARRAY'`. This suggests that the function block may be derived from a generic array-to-array class, even though its function is to split the array into individual values. This could be a detail of the implementation history.

## State Overview
This function block is stateless. Each triggering of the `REQ` event results in direct processing of the current `IN` values and output via `OUT_1` and `OUT_2` without any internal state changes beyond the current transaction.

# State Overview ## Application Scenarios
* **Data Preparation**: When sensors or other components deliver data as an array of two `LREAL` values (e.g., X/Y coordinates, minimum/maximum values), but subsequent components require individual variables.
* **Interface Adaptation**: Adapting interfaces where a source component sends array data, but the target component expects discrete input variables.
* **Logic Simplification**: Increasing readability and simplifying logic by converting array accesses into individual variables that can be more easily processed in subsequent steps.

## ⚖️ Comparison with Similar Components

Similar components could be generic array splitters that can divide a variable number of array elements into a corresponding number of outputs. However, ``ARRAY2VALUES_2_LREAL`` is optimized for the specific case of a ``LREAL`` array of size 2, making it easier to configure and potentially more efficient for this particular use case than a more flexible, but potentially more complex, generic component.

## Metadata

| Attribute | Value |

| :--- | :--- |

| Copyright | (c) 2014 Profactor GmbH |

| License | EPL-2.0 |

| Version | 3.0 (2025-04-14, Patrick Aigner), 1.0 (2014-07-09, Matthias Plasch) |

| 4diac Package | eclipse4diac::convert |

## Conclusion

The `ARRAY2VALUES_2_LREAL` function block is a useful tool for the targeted conversion of a size 2 `LREAL` array into two separate `LREAL` outputs. It offers a simple and efficient solution for data preparation and interface adaptation in 4diac applications where this specific conversion is required.

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de ](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]