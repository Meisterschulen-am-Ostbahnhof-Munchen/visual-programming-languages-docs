# Generic Data Types (ANY Types)

The DIN EN 61131-3 standard uses generic data types (also called "generic" data types) to define functions and function blocks that can work with different but related data types (overloading). These types are identified by the prefix `ANY`.

## Hierarchy of ANY Types

The following graphic illustrates the top-level inheritance hierarchy of generic data types according to the standard.

```mermaid
flowchart TD
    ANY["ANY (All types)"] --> ANY_DERIVED["ANY_DERIVED (Derived types)"]
    ANY --> ANY_ELEMENTARY["ANY_ELEMENTARY (Elementary types)"]
    ANY_ELEMENTARY --> ANY_MAGNITUDE["ANY_MAGNITUDE (Magnitude types)"]
    ANY_ELEMENTARY --> ANY_BIT["ANY_BIT (Bit string types)"]
    ANY_ELEMENTARY --> ANY_CHARS["ANY_CHARS (Character types)"]
    ANY_ELEMENTARY --> ANY_DATE["ANY_DATE (Date types)"]
```

## Group Descriptions

### ANY_ELEMENTARY

This group includes all predefined standard data types of the standard.

#### ANY_MAGNITUDE (Magnitude Types)

Types that represent a magnitude and are suitable for arithmetic operations. A further distinction is made between numeric types and time durations.

```mermaid
flowchart TD
    ANY_MAGNITUDE["ANY_MAGNITUDE (Magnitude types)"] --> ANY_NUM["ANY_NUM (Numeric types)"]
    ANY_MAG_DURATION["ANY_DURATION (Duration)"]
    ANY_MAGNITUDE --> ANY_MAG_DURATION
    ANY_NUM --> ANY_REAL["ANY_REAL (Floating-point types)"]
    ANY_NUM --> ANY_INT["ANY_INT (Integer types)"]
    ANY_INT --> ANY_UNSIGNED["ANY_UNSIGNED (Unsigned)"]
    ANY_INT --> ANY_SIGNED["ANY_SIGNED (Signed)"]
    ANY_REAL --> REAL
    ANY_REAL --> LREAL
    ANY_UNSIGNED --> USINT
    ANY_UNSIGNED --> UINT
    ANY_UNSIGNED --> UDINT
    ANY_UNSIGNED --> ULINT
    ANY_SIGNED --> SINT
    ANY_SIGNED --> INT
    ANY_SIGNED --> DINT
    ANY_SIGNED --> LINT
    ANY_MAG_DURATION --> TIME
    ANY_MAG_DURATION --> LTIME
```

* **ANY_NUM**: Numeric types (integers and floating-point numbers).
* **ANY_DURATION**: Duration types (`TIME`, `LTIME`).

#### ANY_BIT (Bit String Types)

Types for representing bit strings.

```mermaid
flowchart TD
    ANY_BIT["ANY_BIT (Bit string types)"] --> BOOL
    ANY_BIT --> BYTE
    ANY_BIT --> WORD
    ANY_BIT --> DWORD
    ANY_BIT --> LWORD
```

#### ANY_CHARS (Character Types)

Types for characters and strings.

```mermaid
flowchart TD
    ANY_CHARS["ANY_CHARS (Character types)"] --> ANY_STRING["ANY_STRING (Strings)"]
    ANY_CHARS --> ANY_CHAR["ANY_CHAR (Character)"]
    ANY_STRING --> STRING
    ANY_STRING --> WSTRING
    ANY_CHAR --> CHAR
    ANY_CHAR --> WCHAR
```

#### ANY_DATE (Date Types)

Types for date and time values.

```mermaid
flowchart TD
    ANY_DATE["ANY_DATE (Date types)"] --> DATE_AND_TIME
    ANY_DATE --> LDT
    ANY_DATE --> DATE
    ANY_DATE --> TIME_OF_DAY
    ANY_DATE --> LTOD
```

### ANY_DERIVED

This group includes all user-defined data types (e.g., `STRUCT`, `ENUM`, `ARRAY`) that are not directly derived from an elementary type.

## Usage

Generic data types are primarily used in standard libraries. An example is the `ADD` function, which accepts the type `ANY_NUM` as an input and can therefore add both two `INT` and two `REAL` values.

In user-defined program organizational units (POEs), the use of `ANY` types is not provided for in the standard and remains reserved for manufacturer-specific extensions.
