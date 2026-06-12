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

