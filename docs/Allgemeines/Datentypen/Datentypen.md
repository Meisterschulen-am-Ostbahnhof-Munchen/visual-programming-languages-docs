# Datentypen (Übersicht)

```{index} single: Datentypen (Übersicht)
```

### Zusammenfassung der Kategorien
Gemäß DIN EN 61131-3 werden die Datentypen in folgende Gruppen unterteilt:
- **Bit-Datentypen**: BOOL, BYTE, WORD, DWORD, LWORD
- **Ganzzahlen (mit Vorzeichen)**: SINT, INT, DINT, LINT
- **Ganzzahlen (vorzeichenlos)**: USINT, UINT, UDINT, ULINT
- **Gleitpunktzahlen**: REAL, LREAL
- **Zeit und Datum**: TIME, DATE, TOD, DT
- **Zeichenfolgen**: STRING, WSTRING
## Datentypen2

[Integer (Datentyp) – Wikipedia](https://de.wikipedia.org/wiki/Integer_(Datentyp))

[Gleitkommazahl – Wikipedia](https://de.wikipedia.org/wiki/Gleitkommazahl)

### Datentypen in der IEC 61131-3

[Datentypen](https://content.helpme-codesys.com/de/CODESYS%20Development%20System/_cds_reference_datatypes.html)

### Datentypen in der IEC 61499

Siehe auch: IEC 61499, Table E.1

#### Datentypen zum Rechnen

| Typ | BYTE Länge | Bit Länge | Wertebereich min | Wertebereich max |
| --- | --- | --- | --- | --- |
| BOOL | 1/8 | 1 Bit | 0 = FALSE | 1 = TRUE |
| SINT | 1 | 8 Bit | −128 | 127 |
| INT | 2 | 16 Bit | −32.768 | 32.767 |
| DINT | 4 | 32 Bit | −2.147.483.648 | 2.147.483.647 |
| LINT | 8 | 64 Bit | −9.223.372.036.854.775.808 | 9.223.372.036.854.775.807 |
| USINT | 1 | 8 Bit | 0 | 255 |
| UINT | 2 | 16 Bit | 0 | 65.535 |
| UDINT | 4 | 32 Bit | 0 | 4.294.967.295 |
| ULINT | 8 | 64 Bit | 0 | 18.446.744.073.709.551.615 |
| REAL | 4 | 32 Bit |   |   |
| LREAL | 8 | 64 Bit |   |   |
| DATE | 8 | 64 Bit |   |   |
| TIME | 8 | 64 Bit |   |   |
| TIME\_OF\_DAY | 12 | 96 Bit | 1970-01-01-00:00:00.000 |   |
| DATE\_AND\_TIME | 20 | 160 Bit | 1970-01-01-00:00:00.000 |   |

#### Datentypen für I/O (Input / Output)

| Typ | BYTE Länge | Bit Länge | Wertebereich min | Wertebereich max |
| --- | --- | --- | --- | --- |
| BOOL | 1/8 | 1 Bit | 0 = FALSE | 1= TRUE |
| QUARTER [^1] | 1/4 | 2 Bit | 0 | 3 |
| BYTE | 1 | 8 Bit | 0 | 255 |
| WORD | 2 | 16 Bit | 0 | 65.535 |
| DWORD | 4 | 32 Bit | 0 | 4.294.967.295 |
| LWORD | 8 | 64 Bit | 0 | 18.446.744.073.709.551.615 |

[^1]: QUARTER ist nicht normativ festgelegt.

In der folgenden Liste sind die elementaren Datentypen gemäß DIN EN 61131-3 aufgeführt.

```{toctree}
BOOL/BOOL
BYTE/BYTE
DATE/DATE
DATE_AND_TIME/DATE_AND_TIME
DINT/DINT
DWORD/DWORD
INT/INT
LINT/LINT
LREAL/LREAL
LWORD/LWORD
REAL/REAL
SINT/SINT
STRING/STRING
QUARTER/QUARTER
TIME/TIME
TIME_OF_DAY/TIME_OF_DAY
UDINT/UDINT
UINT/UINT
ULINT/ULINT
USINT/USINT
WORD/WORD
WSTRING/WSTRING
```
## 🎧 Podcast

* [Datenkommunikation in der Automatisierung: Die Geheimnisse der IEC 61499 Datentypen](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Datenkommunikation-in-der-Automatisierung-Die-Geheimnisse-der-IEC-61499-Datentypen-e3672lj)
* [Datentypen der IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Datentypen-der-IEC-61499-e3672jf)
* [Universum der Datentypen, wie sie in der IEC 61131-3 und IEC 61499](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Universum-der-Datentypen--wie-sie-in-der-IEC-61131-3-und-IEC-61499-e3673kb)
* [Digitale Logik Flip-Flops und Datentypen](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Digitale-Logik-Flip-Flops-und-Datentypen-e3dic6t)
