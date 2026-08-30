# Datentyp-Mapping: FORTE (IEC 61499) ↔ OPC UA

## Grundlegendes

Wenn 4diac FORTE eine Variable über OPC UA veröffentlicht (`PUBLISH`) oder entgegennimmt (`SUBSCRIBE`), muss der IEC-61499-Datentyp der Variable auf einen passenden OPC-UA-Datentyp abgebildet werden. Diese Zuordnung ist **fest im FORTE-Quellcode verdrahtet** (nicht konfigurierbar) und daher für jeden Adapter-Baustein (`AR_PUBLISH_1`/`AR_SUBSCRIBE_1` usw.) identisch.

Quelle: `com/opc_ua/src/opcua_helper.cpp`, Tabelle `COPC_UA_Helper::scmMapForteTypeIdToOpcUa` im [4diac-forte-Repository](https://github.com/eclipse-4diac/4diac-forte).

## Mapping-Tabelle

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

## Wichtige Punkte

- **`REAL` (32-bit) → `Float`, nicht `Double`.** Das ist der häufigste Stolperstein: `REAL` und `Float` sind beide 32-bit-Gleitkommazahlen, `LREAL` und `Double` sind beide 64-bit. Eine OPC-UA-Gegenstelle (z. B. ein Web-Client), die eine `REAL`-Variable schreiben will, muss den Wert explizit als `Float` senden — schickt sie `Double`, akzeptiert FORTE den Wert je nach OPC-UA-Stack-Konfiguration entweder gar nicht oder interpretiert ihn falsch.
- **`TIME`/`LTIME` werden als reines `Int64`** (Nanosekunden bzw. je nach FORTE-Version Basis-Zeiteinheit) übertragen, nicht als OPC-UA `Duration`.
- **Alle Datums-/Zeit-Typen** (`DATE`, `TIME_OF_DAY`, `DATE_AND_TIME`, `LDATE`, `LTIME_OF_DAY`, `LDATE_AND_TIME`) laufen auf denselben OPC-UA-Typ `DateTime`.
- **`STRING` und `WSTRING`** werden beide auf OPC UA `String` abgebildet — die Unterscheidung ASCII/Unicode geht dabei auf OPC-UA-Seite verloren.
- Diese Tabelle gilt für **skalare Basistypen**. Arrays und Strukturen werden rekursiv über den Elementtyp aufgelöst.

## Praxisbeispiel

Ein Web-Client, der eine `AR_SUBSCRIBE_1`/`AR_PUBLISH_1`-Verbindung zu einer `REAL`-Variable in FORTE aufbaut (z. B. via `node-opcua` oder `@wsopcua/wsopcua`), muss beim Schreiben `DataType.Float` verwenden:

```ts
new Variant({ dataType: DataType.Float, value: 42.0 })
```

`DataType.Double` würde hier nicht dem tatsächlichen FORTE-internen Typ entsprechen.
