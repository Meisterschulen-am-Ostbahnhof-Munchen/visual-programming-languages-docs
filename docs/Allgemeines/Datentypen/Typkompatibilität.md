# Typ-Kompatibilität in 4diac-IDE (Datenverbindungen)

Die Regeln für erlaubte Datenverbindungen basieren auf dem Prinzip
**„Target muss Source aufnehmen können“**.

## Zentrale Dateien in der Codebasis

| Datei | Zweck |
|-------|-------|
| `plugins/org.eclipse.fordiac.ide.model/src/org/eclipse/fordiac/ide/model/data/impl/DataTypeAnnotations.java` | Definiert `isAssignableFrom(DataType other)` für jeden IEC 61131-3 Typ |
| `plugins/org.eclipse.fordiac.ide.model/src/org/eclipse/fordiac/ide/model/validation/LinkConstraints.java:200` | Prüft Verbindungen mit `targetType.isAssignableFrom(sourceType)` |
| `tests/.../datatype/helper/ElementaryDataTypeCompatibilityTest.java` | Vollständige Test-Matrix aller impliziten Zuweisungen |

## Grundprinzip

Eine Verbindung von **Source** → **Target** ist erlaubt, wenn gilt:

```java
targetType.isAssignableFrom(sourceType)
```

Das bedeutet: der Target-Typ muss gleich oder *größer/allgemeiner* sein als der Source-Typ.

## Integer-Typen

### Signed
| Source → | SINT | INT | DINT | LINT |
|----------|:----:|:---:|:----:|:----:|
| **SINT** | ✓ | ✓ | ✓ | ✓ |
| **INT** | ✗ | ✓ | ✓ | ✓ |
| **DINT** | ✗ | ✗ | ✓ | ✓ |
| **LINT** | ✗ | ✗ | ✗ | ✓ |

### Unsigned
| Source → | USINT | UINT | UDINT | ULINT |
|----------|:-----:|:----:|:-----:|:-----:|
| **USINT** | ✓ | ✓ | ✓ | ✓ |
| **UINT** | ✗ | ✓ | ✓ | ✓ |
| **UDINT** | ✗ | ✗ | ✓ | ✓ |
| **ULINT** | ✗ | ✗ | ✗ | ✓ |

> **Wichtig:** Zwischen Signed und Unsigned gibt es **keine** implizite Konvertierung.
> `INT` → `UINT` ist nicht erlaubt.

## Gleitkomma-Typen

| Source → | REAL | LREAL |
|----------|:----:|:-----:|
| **REAL** | ✓ | ✓ |
| **LREAL** | ✗ | ✓ |

REAL und LREAL akzeptieren außerdem bestimmte Ganzzahl-Typen:

- **REAL** akzeptiert: `INT`, `SINT`, `UINT`, `USINT`
- **LREAL** akzeptiert: `DINT`, `INT`, `SINT`, `UDINT`, `UINT`, `USINT`, `REAL`

## Bit-Typen

| Source → | BOOL | BYTE | WORD | DWORD | LWORD |
|----------|:----:|:----:|:----:|:-----:|:-----:|
| **BOOL** | ✓ | ✓ | ✓ | ✓ | ✓ |
| **BYTE** | ✗ | ✓ | ✓ | ✓ | ✓ |
| **WORD** | ✗ | ✗ | ✓ | ✓ | ✓ |
| **DWORD**| ✗ | ✗ | ✗ | ✓ | ✓ |
| **LWORD**| ✗ | ✗ | ✗ | ✗ | ✓ |

## Zeichen und Strings

| Source → | CHAR | WCHAR | STRING | WSTRING |
|----------|:----:|:-----:|:------:|:-------:|
| **CHAR** | ✓ | ✗ | ✓ | ✗ |
| **WCHAR**| ✗ | ✓ | ✗ | ✓ |

## Zeit- und Datums-Typen

Lang-Typen akzeptieren auch die kurzen Varianten:

- **LTIME** ← `TIME`
- **LDATE** ← `DATE`
- **LTOD** ← `TOD`
- **LDT** ← `DT`

## Zusammenfassung der Regeln

1. **Breite-Regel:** Ein kleinerer Typ darf auf einen größeren Typ verbunden werden (z. B. `UINT` → `UDINT`).
2. **Keine Verengung:** Ein größerer Typ darf nicht auf einen kleineren Typ verbunden werden (z. B. `UDINT` → `UINT` ist verboten).
3. **Sign-Grenze:** Signed und Unsigned Integer sind nicht kompatibel (z. B. `INT` → `UINT` ist verboten).
4. **Bool-Sonderregel:** `BOOL` darf auf jeden Bit-Typ (`BYTE`, `WORD`, `DWORD`, `LWORD`) verbunden werden.

## Typ-Umwandlungen (Casting)

### Direkte Bit-String-zu-Gleitkomma-Konvertierungen

In IEC 61131-3 / IEC 61499 sind folgende direkten Konvertierungen **nicht definiert**:

- `BYTE_TO_REAL` → **nicht definiert**
- `WORD_TO_REAL` → **nicht definiert**

Stattdessen müssen Sie über den passenden vorzeichenlosen Integer-Typen konvertieren:

| Quelle | Ziel | Korrekte Umwandlung |
|--------|------|---------------------|
| BYTE | REAL | `BYTE` → `USINT` → `REAL` |
| WORD | REAL | `WORD` → `UINT` → `REAL` |
| DWORD | REAL | `DWORD` → `UDINT` → `REAL` |
| LWORD | LREAL | `LWORD` → `ULINT` → `LREAL` |

### DWORD_TO_REAL, LWORD_TO_LREAL = reinterpret_cast

**Wichtig:** `DWORD_TO_REAL` und `LWORD_TO_LREAL` in 4diac entsprechen einem `reinterpret_cast` in C++. Das bedeutet:

- Die Bit-Darstellung wird direkt als REAL interpretiert
- Es findet **keine numerische Umwandlung** statt
- Beispiel: `16#41480000` als DWORD wird zu `12.5` als REAL (gleiche Bitrepräsentation)

Dies ist in der Regel **nicht** das gewünschte Verhalten für numerische Umwandlungen!

### Das 16.777.216 Problem (REAL Präzisionsverlust)

REAL hat nur 32 Bit und kann daher nur **7 Dezimalstellen** präzise darstellen.

Bei der Konvertierung von großen vorzeichenlosen Werten geht ab **16.777.216** (2^24) die Genauigkeit verloren:

```iecst
UDINT#16777216  →  REAL#16777216.0  →  Korrekt (2^24)
UDINT#16777217  →  REAL#16777216.0  →  Präzisionsverlust (Rundung)
```

**Lösung:** Bei Werten ≥ 16.777.216 `LREAL` statt `REAL` verwenden:

```iecst
UDINT#16777216  →  UDINT_TO_LREAL()  →  LREAL#16777216.0  ✓
```

Dies betrifft insbesondere:
- UDINT (32 Bit) und DWORD (32 Bit) Umwandlungen in REAL
- LWORD (64 Bit) und ULINT (64 Bit) Umwandlungen in LREAL (bei LREAL tritt der Präzisionsverlust erst ab 2^53 auf)

**Faustregel:** Alle FIELDBUS Signal-Bausteine für DWORD, UDINT, LWORD und ULINT sollten `LREAL` als Ausgabetyp verwenden.
