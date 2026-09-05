# 💾 Data Types (Overview)

### Summary of Categories

According to DIN EN 61131-3, data types are divided into the following groups:

- **Bit Data Types**: BOOL, BYTE, WORD, DWORD, LWORD
- **Signed Integers**: SINT, INT, DINT, LINT
- **Unsigned Integers**: USINT, UINT, UDINT, ULINT
- **Floating Point Numbers**: REAL, LREAL
- **Time and Date**: TIME, DATE, TOD, DT
- **Strings**: STRING, WSTRING

## 💾 Data Types 2

[Integer (Data Type) – Wikipedia](https://de.wikipedia.org/wiki/Integer_(Datentyp))

[Floating Point Number – Wikipedia](https://de.wikipedia.org/wiki/Gleitkommazahl)

### 💾 Data Types in the IEC 61131-3

[Data Types](index.md)

### Generic Data Types (ANY Types)

The standard defines generic data types for overloaded functions and standard libraries.

Details on the hierarchy and usage can be found here: **[ANY Types](GenerischeDatentypen/ANY-Typen.md)**

### 💾 Data Types in IEC 61499

See also: IEC 61499, Table E.1

#### 💾 Data Types for Computation

| Type | Abbreviation | BYTE Length | Bit Length | Minimum Value Range | Maximum Value Range |
| --- | --- | --- | --- | --- | --- |
| BOOL | X | 1/8 | 1 Bit | 0 = FALSE | 1 = TRUE |
| SINT | S | 1 | 8 Bit | −128 | 127 |
| INT | I | 2 | 16 bits | −32,768 | 32,767 |
| DINT | DI | 4 | 32 bits | −2,147,483,648 | 2,147,483,647 |
| LINT | LI | 8 | 64 bit | −9,223,372,036,854,775,808 | 9,223,372,036,854,775,807 |
| USINT | US | 1 | 8 bits | 0 | 255 |
| UINT | UI | 2 | 16 bits | 0 | 65,535 |
| UDINT | UDI | 4 | 32 bits | 0 | 4,294,967,295 |
| ULINT | ULI | 8 | 64 bit | 0 | 18,446,744,073,709,551,615 |
| REAL | R | 4 | 32 bits | | |
| LREAL | LR | 8 | 64 bit | | |
| DATE | D | 8 | 64 bit | | |
| TIME | T | 8 | 64 bit | | |
| TIME\_OF\_DAY | DEATH | 12 | 96 bits | 1970-01-01-00:00:00.000 | |
| DATE\_AND\_TIME | DT | 20 | 160 bits | 1970-01-01-00:00:00.000 | |

#### 💾 Data types for I/O (Input / Output)

| Type | Abbreviation | BYTE Length | Bit Length | Minimum Value Range | Maximum Value Range |

-----------------

BOOL | X | 1/8 | 1 Bit | 0 = FALSE | 1 = TRUE |
QUARTER [^1] | Q | 1/4 | 2 Bits | 0 | 3 |
BYTE | B | 1 | 8 Bits | 0 | 255 |
WORD | W | 2 | 16 Bits | 0 | 65,535 |
DWORD | D | 4 | 32 Bits | 0 | 4,294,967,295 |
LWORD | L | 8 | 64 Bits | 0 | 18,446,744,073,709,551,615 |

[^1]: QUARTER is not a standard.

## 🔗 Adapters and I/O Blocks

The following table lists the corresponding adapters and I/O blocks for each data type:

| Data Type | Abbreviation | Adapter | Input | Output |
| --- | --- | --- | --- | --- |
| BOOL | X | [AX](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/BOOL/AX/) | [IX](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/StandardLibraries/io/IX/) | [QX](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/StandardLibraries/io/QX/) |
| BYTE | B | [AB](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/BYTE/AB/) | [IB](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/StandardLibraries/io/IB/) | [QB](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/StandardLibraries/io/QB/) |
| WORD | W | [AW](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/WORD/AW/) | [IW](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/StandardLibraries/io/IW/) | [QW](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/StandardLibraries/io/QW/) |
| DWORD | D | [AD](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/DWORD/AD/) | [ID](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/StandardLibraries/io/ID/) | [QD](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/StandardLibraries/io/QD/) |
| LWORD | L | [AL](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/LWORD/AL/) | [IL](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/StandardLibraries/io/IL/) | [QL](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/StandardLibraries/io/QL/) |
| SINT | S | [AS](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/SINT/AS/) | — | — |
| INT | I | [AI](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/INT/AI/) | — | — |
| DINT | DI | [ADI](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/DINT/ADI/) | — | — |
| LINT | LI | [ALI](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/LINT/ALI/) | — | — |
| USINT | US | [AUS](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/USINT/AUS/) | — | — |
| UINT | UI | [AUI](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/UINT/AUI/) | — | — |
| UDINT | UDI | [AUDI](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/UDINT/AUDI/) | — | — |
| ULINT | ULI | [AULI](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/ULINT/AULI/) | — | — |
| REAL | R | [AR](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/REAL/AR/) | — | — |
| LREAL | LR | [ALR](https://docs.ms-muc-docs.de/projects/4diac-library-reference-docs/en/latest/ExternalLibraries/adapter/types/unidirectional/LREAL/ALR/) | — | — |
| DATE | D | — | — | — |
| TIME | T | — | — | — |
| TIME_OF_DAY | TOD | — | — | — |
| DATE_AND_TIME | DT | — | — | — |
| QUARTER | Q | — | — | — |

The following list contains the elementary data types according to DIN EN 61131-3.

## 🎧 Podcast

- [Data Communication in Automation: The Secrets of IEC 61499 Data Types ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Datenkommunikation-in-der-Automatisierung-Die-Geheimnisse-der-IEC-61499-Datentypen-e3672lj)
- [Data Types of IEC 61499 ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Datentypen-der-IEC-61499-e3672jf)
- [Universe of Data Types as defined in IEC 61131-3 and IEC 61499 ](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Universum-der-Datentypen--wie-sie-in-der-IEC-61131-3-und-IEC-61499-e3673kb)
- [Digital Logic Flip-Flops and Data Types ](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Digitale-Logik-Flip-Flops-und-Datentypen-e3dic6t)

]
