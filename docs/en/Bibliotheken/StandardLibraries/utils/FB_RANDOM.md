# FB_RANDOM
* * * * * * * * * *
## Introduction
The FB_RANDOM function block generates a random REAL number between 0 and 1.
![FB_RANDOM](FB_RANDOM.svg)
## Interface Structure

### **Event Inputs**
- **INIT**: Initializes the random number generator with a seed.
- **REQ**: Calculates a new random number.

### **Event Outputs**
- **INITO**: Initialization complete.
- **CNF**: Calculation complete, new value available.

### **Data Inputs**
- **SEED** (UINT): The seed value for the random number generator. A value of 0 uses the current system time.

### **Data Outputs**
- **VAL** (REAL): The generated random number.

## Metadata

| Attribute | Value |
| :--- | :--- |
Copyright | (c) 2012 Profactor GmbH |
License | EPL-2.0 |
Version | 3.0 (2025-04-14, Patrick Aigner) |
4diac Package | eclipse4diac::utils |

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Color Reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

]