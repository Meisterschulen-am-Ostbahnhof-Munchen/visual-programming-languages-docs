# F_NOW
![F_NOW](https://github.com/user-attachments/assets/3a8b2855-6d9a-49b3-ae77-6050fb2763d9)

* * * * * * * * * *
## Introduction
The **F_NOW** function is an IEC 61499-1 compliant helper function for querying the current local date and time, developed under the EPL-2.0 license (version 3.0).
The function serves as a wrapper for the ST function NOW().

## Interface Structure

### **Event Inputs**
- `REQ`: Triggers the time query

### **Event Outputs**
- `CNF`: Acknowledges the time query

### **Data Outputs**

| Parameter | Type | Description | Format |

|-----------|-----|---------------|--------|

| (implicit) | DATE_AND_TIME | Current timestamp | DT#2025-04-14-15:30:45 |

## Functionality

1. **Query**:

- `REQ` triggers the time query
- System time is captured in the local time zone

2. **Output**:

- `CNF` returns the result in DATE_AND_TIME format
- Contains date and time with second accuracy

## Technical Features

✔ **IEC 61499-1 compliant**
✔ **Local time zone support** (including daylight saving time)
✔ **Easy integration** as a NOW() wrapper
✔ **Eclipse 4diac integration**

## Application Scenarios
- **Logging**: Timestamps for events
- **Reports**: Generation with creation date
- **Time-controlled processes**: Current time check
- **Diagnostics**: Time-based error analysis

## Example Values

| Call time | Return value |

|-----------------|--------------|

| 14.04.2025 15:30:45 | DT#2025-04-14-15:30:45 |

| 31.12.2024 23:59:59 | DT#2024-12-31-23:59:59 |

## ⚖️ Comparison with similar functions

| Feature | F_NOW | NOW | TIME() |

|---------|-------|-----|--------|

| Return type | DATE_AND_TIME | DATE_AND_TIME | TIME |

| Time zone | Local | Local | System |

| Accuracy | Seconds | Seconds | Milliseconds |

| Daylight Saving Time | Yes | Yes | No |

## Limitations

⚠ **Time jumps possible** with:

- Daylight Saving Time
- Manual time adjustments
- NTP synchronization

## Conclusion

The F_NOW function offers easy access to the system time:

- **Practical**: Quick integration of existing NOW functions
- **Localized**: Automatic time zone adjustment
- **Standards compliant**: IEC-compatible implementation

Ideal for:

- Event logging
- Time-controlled processes
- Diagnostic functions
- Report generation

*The simple solution for time-critical applications in 4diac*

---

### 🌐 Related topic subpages on ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & color reference on ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)

