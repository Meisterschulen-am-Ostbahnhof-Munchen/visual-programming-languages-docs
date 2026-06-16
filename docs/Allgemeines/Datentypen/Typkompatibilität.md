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

## Veraltete Konvertierungen & F_MOVE

### 1. Deprecated Konvertierungsbausteine
Alle alten Identitäts-Konvertierungsbausteine aus dem Ordner `convert-1.0.0` (wie z. B. `BOOL2BOOL`, `INT2INT`, `DINT2DINT`, `REAL2REAL`, `STRING2STRING` etc.) sind **veraltet (deprecated)** und dürfen nicht mehr verwendet werden.

### 2. Verwendung von `F_MOVE`
Für das Kopieren bzw. Weiterleiten von Werten desselben Typs muss stattdessen der generische Baustein `F_MOVE` (`iec61131::selection::F_MOVE`) verwendet werden.

### 3. Konfiguration von `F_MOVE`
Da `F_MOVE` generisch ist, muss er in XML-Netzwerkdateien über das Attribut `DataType` auf den gewünschten Zieldatentyp konfiguriert werden. 

**Beispiel-Konfiguration in der XML:**
```xml
<FB Name="MeinFMove" Type="iec61131::selection::F_MOVE">
    <Attribute Name="DataType" Value="BOOL"/> <!-- Hier Datentyp konfigurieren -->
</FB>
```

Ohne dieses Attribut oder mit leerem Wert ist der Baustein ungültig und schlägt in der Validierung fehl.

## Explizite Typkonvertierungen (Casting) in ST & FB-Netzwerken

Wenn eine Zuweisung (in ST) oder eine Verbindung (im FB-Netzwerk) nicht implizit erlaubt ist (siehe Matrix oben), muss eine explizite Konvertierung durchgeführt werden:
* **In Structured Text (ST):** Verwendung einer Konvertierungsfunktion der Form `[SOURCE_TYPE]_TO_[TARGET_TYPE]` (z. B. `DINT_TO_UDINT`).
* **Im grafischen FB-Netzwerk:** Einfügen des entsprechenden Konvertierungs-Funktionsbausteins (z. B. des Bausteins `DINT_TO_UDINT`) zwischen Ausgang und Eingang.

### ⚠️ Wichtiger Sonderfall: Bit-Strings zu Numerischen Typen (reinterpret_cast)

In FORTE / 4diac werden Konvertierungen von Bit-Strings (wie `DWORD`, `WORD`, `BYTE`) zu numerischen Typen (`REAL`, `INT`, `DINT` etc.) als Bit-Ebene **`reinterpret_cast`** ausgeführt. Das bedeutet, dass die Bitmuster direkt kopiert werden, ohne den mathematischen Wert anzupassen. Dies gilt gleichermaßen für ST-Funktionsaufrufe wie für grafische Konvertierungsbausteine.

#### Szenario A: Im DWORD ist ein Zahlenwert (z.B. UDINT) gespeichert
Wenn in einem `DWORD` ein numerischer Ganzzahlwert (z. B. 123) abgelegt ist und dieser als Fließkommazahl (`REAL`) ausgegeben werden soll:
* **Falsch:**
  * *In ST:* `real_var := DWORD_TO_REAL(dword_var);`
  * *Im FB-Netzwerk:* Direkte Verbindung über den Konvertierungsbaustein `DWORD_TO_REAL`.
  * *Erklärung:* Dies kopiert die Bits von 123 direkt in das Float-Bitmuster. Nach IEEE-754 wird dies als eine extrem kleine, fast unendlich nahe Null interpretiert, was mathematisch falsch ist.
* **Richtig (doppelte Konvertierung):**
  * *In ST:*
    ```pascal
    real_var := UDINT_TO_REAL(DWORD_TO_UDINT(dword_var));
    ```
  * *Im FB-Netzwerk:* Nacheinanderfolgendes Einfügen zweier Konvertierungsbausteine in Serie:
    `[DWORD-Ausgang]` $\rightarrow$ `[DWORD_TO_UDINT]` $\rightarrow$ `[UDINT_TO_REAL]` $\rightarrow$ `[REAL-Eingang]`.
  * *Erklärung:* `DWORD_TO_UDINT` kopiert das Bitmuster (123 bleibt 123 als UDINT). `UDINT_TO_REAL` führt dann die echte mathematische Umwandlung in die Fließkommazahl `123.0` durch.

#### Szenario B: Im DWORD ist bereits ein IEEE-754 Float-Bitmuster gespeichert
Wenn das `DWORD` direkt das Roh-Bitmuster einer Fließkommazahl enthält (z. B. eingelesen über ein Modbus-Register oder eine Netzwerk-Verbindung):
* **Richtig:**
  * *In ST:* `real_var := DWORD_TO_REAL(dword_var);`
  * *Im FB-Netzwerk:* Einfügen des Konvertierungsbausteins `DWORD_TO_REAL`.
  * *Erklärung:* Hier ist der Direkt-Cast per `reinterpret_cast` genau das Gewünschte, um die Roh-Bits direkt als Fließkommazahl zu interpretieren.



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
UDINT#16777216  →  UDINT_TO_REAL()  →  REAL#16777216.0  →  Korrekt (2^24)
UDINT#16777217  →  UDINT_TO_REAL()  →  REAL#16777216.0  →  Präzisionsverlust (Rundung)
```

**Lösung:** Bei Werten ≥ 16.777.216 `LREAL` statt `REAL` verwenden:

```iecst
UDINT#16777217  →  UDINT_TO_LREAL()  →  LREAL#16777217.0  ✓
```

Dies betrifft insbesondere:
- UDINT (32 Bit) Umwandlungen in REAL (oder DWORD nach Umwandlung in UDINT)
- ULINT (64 Bit) Umwandlungen in LREAL (oder LWORD nach Umwandlung in ULINT; bei LREAL tritt der Präzisionsverlust erst ab 2^53 auf)

**Faustregel:** Alle FIELDBUS Signal-Bausteine für DWORD, UDINT, LWORD und ULINT sollten `LREAL` als Ausgabetyp verwenden.
