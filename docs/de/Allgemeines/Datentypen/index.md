# 💾 Datentypen (Übersicht)

### Zusammenfassung der Kategorien

Gemäß DIN EN 61131-3 werden die Datentypen in folgende Gruppen unterteilt:

- **Bit-Datentypen**: BOOL, BYTE, WORD, DWORD, LWORD
- **Ganzzahlen (mit Vorzeichen)**: SINT, INT, DINT, LINT
- **Ganzzahlen (vorzeichenlos)**: USINT, UINT, UDINT, ULINT
- **Gleitpunktzahlen**: REAL, LREAL
- **Zeit und Datum**: TIME, DATE, TOD, DT
- **Zeichenfolgen**: STRING, WSTRING

## 💾 Datentypen2

[Integer (Datentyp) – Wikipedia](https://de.wikipedia.org/wiki/Integer_(Datentyp))

[Gleitkommazahl – Wikipedia](https://de.wikipedia.org/wiki/Gleitkommazahl)

### 💾 Datentypen in der IEC 61131-3

[Datentypen](https://content.helpme-codesys.com/de/CODESYS%20Development%20System/_cds_reference_datatypes.html)

### Generische Datentypen (ANY-Typen)

Für überladene Funktionen und Standard-Bibliotheken definiert die Norm generische Datentypen.
Details zur Hierarchie und Verwendung finden Sie hier: **[ANY-Typen](GenerischeDatentypen/ANY-Typen.md)**

### 💾 Datentypen in der IEC 61499

Siehe auch: IEC 61499, Table E.1

#### 💾 Datentypen zum Rechnen

| Typ | Kürzel | BYTE Länge | Bit Länge | Wertebereich min | Wertebereich max |
| --- | --- | --- | --- | --- | --- |
| BOOL | X | 1/8 | 1 Bit | 0 = FALSE | 1 = TRUE |
| SINT | S | 1 | 8 Bit | −128 | 127 |
| INT | I | 2 | 16 Bit | −32.768 | 32.767 |
| DINT | DI | 4 | 32 Bit | −2.147.483.648 | 2.147.483.647 |
| LINT | LI | 8 | 64 Bit | −9.223.372.036.854.775.808 | 9.223.372.036.854.775.807 |
| USINT | US | 1 | 8 Bit | 0 | 255 |
| UINT | UI | 2 | 16 Bit | 0 | 65.535 |
| UDINT | UDI | 4 | 32 Bit | 0 | 4.294.967.295 |
| ULINT | ULI | 8 | 64 Bit | 0 | 18.446.744.073.709.551.615 |
| REAL | R | 4 | 32 Bit | | |
| LREAL | LR | 8 | 64 Bit | | |
| DATE | D | 8 | 64 Bit | | |
| TIME | T | 8 | 64 Bit | | |
| TIME\_OF\_DAY | TOD | 12 | 96 Bit | 1970-01-01-00:00:00.000 | |
| DATE\_AND\_TIME | DT | 20 | 160 Bit | 1970-01-01-00:00:00.000 | |

#### 💾 Datentypen für I/O (Input / Output)

| Typ | Kürzel | BYTE Länge | Bit Länge | Wertebereich min | Wertebereich max |
| --- | --- | --- | --- | --- | --- |
| BOOL | X | 1/8 | 1 Bit | 0 = FALSE | 1= TRUE |
| QUARTER [^1] | Q | 1/4 | 2 Bit | 0 | 3 |
| BYTE | B | 1 | 8 Bit | 0 | 255 |
| WORD | W | 2 | 16 Bit | 0 | 65.535 |
| DWORD | D | 4 | 32 Bit | 0 | 4.294.967.295 |
| LWORD | L | 8 | 64 Bit | 0 | 18.446.744.073.709.551.615 |

[^1]: QUARTER ist nicht normativ festgelegt.

## 🔗 Adapter und IO-Bausteine

In der folgenden Tabelle finden Sie die zugehörigen Adapter und IO-Bausteine für jeden Datentyp:

| Datentyp | Kürzel | Adapter | Input | Output |
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

In der folgenden Liste sind die elementaren Datentypen gemäß DIN EN 61131-3 aufgeführt.

## 🎧 Podcast

- [Datenkommunikation in der Automatisierung: Die Geheimnisse der IEC 61499 Datentypen](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Datenkommunikation-in-der-Automatisierung-Die-Geheimnisse-der-IEC-61499-Datentypen-e3672lj)
- [Datentypen der IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Datentypen-der-IEC-61499-e3672jf)
- [Universum der Datentypen, wie sie in der IEC 61131-3 und IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Universum-der-Datentypen--wie-sie-in-der-IEC-61131-3-und-IEC-61499-e3673kb)
- [Digitale Logik Flip-Flops und Datentypen](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Digitale-Logik-Flip-Flops-und-Datentypen-e3dic6t)
