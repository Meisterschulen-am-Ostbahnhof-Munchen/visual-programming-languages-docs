# TIMESTAMP_NS

![TIMESTAMP_NS](https://github.com/user-attachments/assets/4c753c7c-ff7e-40de-87ed-fbcf46d758a9)

* * * * * * * * * *
## Introduction

The **TIMESTAMP_NS** is an IEC 61499-compliant function block for generating high-resolution timestamps in nanoseconds.
By default, it generates Unix epoch timestamps (from January 1, 1970), but supports alternative time references by adjusting the start date (`startDate`).

Developed under the EPL 2.0 license.

--

## Interface Structure

### **Event Inputs**

- **REQ** (Trigger):

Starts the timestamp calculation. Must be linked to the input parameter `startDate`.

*Example:* `REQ(startDate := DT#2000-01-01-00:00:00)`

### **Event Outputs**

- **CNF** (Acknowledgement):

Signals the completion of the calculation. The generated timestamp is then available as the value `ULINT`.

### **Data Inputs**

- **startDate** (DT):

Start date for the timestamp calculation.

*Default:* `DT#1970-01-01-00:00:00` (Unix epoch).

*Note:* Other values allow user-defined references (e.g., system startup).

### **Data Outputs**

- **ULINT** (Output Variable):

Timestamp in nanoseconds since the defined `startDate`.

*Example:* `1680000000000000000` (1.68e18 ns ≈ 2023-03-28).

---

## Functionality

1. **Initialization**:
- Activated by the `REQ` event.
- Uses the current system time (`NOW()`).
2. **Calculation**:
- Subtracts `startDate` from the current system time.
- Converts the difference to nanoseconds via `TIME_IN_NS_TO_ULINT()`.
- Outputs the result as `ULINT` and triggers `CNF`.
3. **Error Handling**:
- No explicit error message, but overflow is possible in the case of:
- Extremely large time differences (>584 years).
- Invalid `startDate` (e.g., future date).

--

## Technical Features

- **Nanosecond Precision**: 64-bit counter (`ULINT`) prevents overflow up to ~584 years.
- **Flexible References**: Any starting date (e.g., `DT#2000-01-01` for Y2K reference).
- **License**: Eclipse Public License 2.0 (EPL-2.0).

--

## Return Codes

- **Success**: Valid `ULINT` value (nanoseconds).
- **Errors**: No explicit codes, but:
- `0` for invalid calculations (e.g., `startDate > NOW()`).
- Overflow for differences >26 ns.

--

## Application Scenarios

1. **High-Performance Logging**:

Synchronization of events in distributed systems.

2. **Real-Time Measurements**:

Runtime analysis with nanosecond precision.

3. **User-Defined Time Periods**:

Calculation of intervals from arbitrary reference points.

--

## ⚖️ Comparison with Similar Building Blocks

| Function | `TIMESTAMP_NS` | `NOW()` | `F_NOW_MONOTONIC` |
|---------------------|-----------------------|-----------------------|-----------------------|
| **Output Format** | Nanoseconds (ULINT) | Time Interval (TIME) | Time Interval (TIME) |
| **Reference Point** | Configurable | System Startup | Hardware Dependent |
| **Precision** | 1 ns | 1 ms | 1 ns (typical) |
| **Use Case** | Absolute Timestamps | Relative Time Measurement | Monotonical Measurement |

---

## Conclusion

TIMESTAMP_NS` is an essential component for applications requiring highly precise and flexible timestamps. Its support for user-defined start dates and nanosecond precision makes it ideal for:

- **Industrial Data Recording**
- **Real-Time Controls**
- **Scientific Measurement Systems**

*Note:* For monotonous time measurements, `F_NOW_MONOTONIC` should be preferred.
