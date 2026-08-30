# Data Type Mapping: FORTE (IEC 61499) ↔ OPC UA

## Basics

When 4diac FORTE publishes (`PUBLISH`) or subscribes to (`SUBSCRIBE`) a variable over OPC UA, the variable's IEC 61499 data type has to be mapped to a matching OPC UA data type. This mapping is **hard-wired into the FORTE source code** (not configurable), so it is identical for every adapter block (`AR_PUBLISH_1`/`AR_SUBSCRIBE_1`, etc.).

Source: `com/opc_ua/src/opcua_helper.cpp`, table `COPC_UA_Helper::scmMapForteTypeIdToOpcUa` in the [4diac-forte repository](https://github.com/eclipse-4diac/4diac-forte).

## Mapping Table

| IEC 61499 (FORTE) | OPC UA |
| :--- | :--- |
| `BOOL` | `Boolean` |
| `SINT` | `SByte` |
| `INT` | `Int16` |
| `DINT` | `Int32` |
| `LINT` | `Int64` |
| `USINT` | `Byte` |
| `UINT` | `UInt16` |
| `UDINT` | `UInt32` |
| `ULINT` | `UInt64` |
| `BYTE` | `Byte` |
| `WORD` | `UInt16` |
| `DWORD` | `UInt32` |
| `LWORD` | `UInt64` |
| `DATE` | `DateTime` |
| `TIME_OF_DAY` (`TOD`) | `DateTime` |
| `DATE_AND_TIME` (`DT`) | `DateTime` |
| `TIME` | `Int64` |
| `CHAR` | `Byte` |
| `WCHAR` | `UInt16` |
| `LDATE` | `DateTime` |
| `LTIME_OF_DAY` (`LTOD`) | `DateTime` |
| `LDATE_AND_TIME` (`LDT`) | `DateTime` |
| `LTIME` | `Int64` |
| **`REAL`** | **`Float`** |
| **`LREAL`** | **`Double`** |
| `STRING` | `String` |
| `WSTRING` | `String` |

## Key Points

- **`REAL` (32-bit) maps to `Float`, not `Double`.** This is the most common pitfall: `REAL` and `Float` are both 32-bit floating point, `LREAL` and `Double` are both 64-bit. An OPC UA peer (e.g. a web client) writing to a `REAL` variable must explicitly send the value as `Float` — sending `Double` instead will, depending on the OPC UA stack's configuration, either be rejected outright or misinterpreted.
- **`TIME`/`LTIME` are transmitted as plain `Int64`** (nanoseconds, or the base time unit depending on the FORTE version), not as an OPC UA `Duration`.
- **All date/time types** (`DATE`, `TIME_OF_DAY`, `DATE_AND_TIME`, `LDATE`, `LTIME_OF_DAY`, `LDATE_AND_TIME`) map to the same OPC UA type, `DateTime`.
- **`STRING` and `WSTRING`** both map to OPC UA `String` — the ASCII/Unicode distinction is lost on the OPC UA side.
- This table covers **scalar base types**. Arrays and structures are resolved recursively via their element type.

## Practical Example

A web client opening an `AR_SUBSCRIBE_1`/`AR_PUBLISH_1` connection to a `REAL` variable in FORTE (e.g. via `node-opcua` or `@wsopcua/wsopcua`) must use `DataType.Float` when writing:

```ts
new Variant({ dataType: DataType.Float, value: 42.0 })
```

`DataType.Double` would not match the actual internal FORTE type here.
