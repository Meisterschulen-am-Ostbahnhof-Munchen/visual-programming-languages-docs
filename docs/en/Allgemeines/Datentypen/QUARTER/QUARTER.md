# Data Type Details: QUARTER

## 🎧 Podcast

* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)

----

## Description
The **QUARTER** data type is a 2-bit data type that represents four states. It is not normatively defined in IEC 61131-3 or IEC 61499, but is based on definitions from **SAE J1939** and **ISO 11783-6** (ISOBUS).

## Definition and Value Range

| Property | Value |

| :--- | :--- |

| **Bits** | 2 |

| **Number of States** | 4 |

### Standard State Definition (based on SAE J1939)

| Binary Value | Decimal | Meaning (Typical) |

| :--- | :--- | :--- |

`00` | 0 | **Off** |

`01` | 1 | **On** |

`10` | 2 | **Error** (or Reserved) |

`11` | 3 | **Not Available** (or Don't Care) |

## Usage
This data type is frequently used for the efficient transmission of status information where, in addition to the pure switching state (On/Off), diagnostic information (Error, Not Available) is also relevant.


## Notes

Since **QUARTER** is not a standard data type in the IEC standards, it is often represented in programming environments as `BYTE` or `USINT`, where only the lower two bits are relevant, or multiple QUARTER values are packed into one byte.

## 🛠️ Related Exercises

* [Exercise_055](../../../Uebungen/test_B/Uebungen_doc/Uebung_055.md)]

* [Exercise_056](../../../Uebungen/test_B/Uebungen_doc/Uebung_056.md)]


