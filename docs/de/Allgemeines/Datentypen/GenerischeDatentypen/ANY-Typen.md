# Generische Datentypen (ANY-Typen)

In der Norm DIN EN 61131-3 werden generische Datentypen (auch als "allgemeine" Datentypen bezeichnet) verwendet, um Funktionen und Funktionsbausteine zu definieren, die mit verschiedenen, aber verwandten Datentypen arbeiten können (Überladen). Diese Typen werden durch das Präfix `ANY` gekennzeichnet.

## Hierarchie der ANY-Typen

Die folgende Grafik verdeutlicht die oberste Vererbungshierarchie der generischen Datentypen gemäß der Norm.

```mermaid
flowchart TD
    ANY["ANY (Alle Typen)"] --> ANY_DERIVED["ANY_DERIVED (Abgeleitete Typen)"]
    ANY --> ANY_ELEMENTARY["ANY_ELEMENTARY (Elementare Typen)"]
    ANY_ELEMENTARY --> ANY_MAGNITUDE["ANY_MAGNITUDE (Größentypen)"]
    ANY_ELEMENTARY --> ANY_BIT["ANY_BIT (Bitfolgetypen)"]
    ANY_ELEMENTARY --> ANY_CHARS["ANY_CHARS (Zeichentypen)"]
    ANY_ELEMENTARY --> ANY_DATE["ANY_DATE (Datumstypen)"]
```

## Beschreibung der Gruppen

### ANY_ELEMENTARY

Diese Gruppe umfasst alle vordefinierten Standard-Datentypen der Norm.

#### ANY_MAGNITUDE (Größentypen)

Typen, die eine Größe darstellen und für arithmetische Operationen geeignet sind. Hier wird weiter zwischen numerischen Typen und Zeitdauern unterschieden.

```mermaid
flowchart TD
    ANY_MAGNITUDE["ANY_MAGNITUDE (Größentypen)"] --> ANY_NUM["ANY_NUM (Numerische Typen)"]
    ANY_MAG_DURATION["ANY_DURATION (Zeitdauer)"]
    ANY_MAGNITUDE --> ANY_MAG_DURATION
    ANY_NUM --> ANY_REAL["ANY_REAL (Gleitpunktzahlen)"]
    ANY_NUM --> ANY_INT["ANY_INT (Ganzzahlen)"]
    ANY_INT --> ANY_UNSIGNED["ANY_UNSIGNED (Vorzeichenlos)"]
    ANY_INT --> ANY_SIGNED["ANY_SIGNED (Vorzeichenbehaftet)"]
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

-   **ANY_NUM**: Numerische Typen (Ganzzahlen und Gleitpunktzahlen).
-   **ANY_DURATION**: Zeitdauer-Typen (`TIME`, `LTIME`).

#### ANY_BIT (Bitfolgetypen)

Typen zur Darstellung von Bitfolgen.

```mermaid
flowchart TD
    ANY_BIT["ANY_BIT (Bitfolgetypen)"] --> BOOL
    ANY_BIT --> BYTE
    ANY_BIT --> WORD
    ANY_BIT --> DWORD
    ANY_BIT --> LWORD
```

#### ANY_CHARS (Zeichentypen)

Typen für Zeichen und Zeichenfolgen.

```mermaid
flowchart TD
    ANY_CHARS["ANY_CHARS (Zeichentypen)"] --> ANY_STRING["ANY_STRING (Zeichenfolgen)"]
    ANY_CHARS --> ANY_CHAR["ANY_CHAR (Einzelzeichen)"]
    ANY_STRING --> STRING
    ANY_STRING --> WSTRING
    ANY_CHAR --> CHAR
    ANY_CHAR --> WCHAR
```

#### ANY_DATE (Datumstypen)

Typen für Datums- und Uhrzeitangaben.

```mermaid
flowchart TD
    ANY_DATE["ANY_DATE (Datumstypen)"] --> DATE_AND_TIME
    ANY_DATE --> LDT
    ANY_DATE --> DATE
    ANY_DATE --> TIME_OF_DAY
    ANY_DATE --> LTOD
```

### ANY_DERIVED

Diese Gruppe umfasst alle vom Anwender definierten Datentypen (z.B. `STRUCT`, `ENUM`, `ARRAY`), die nicht direkt auf einen elementaren Typ zurückzuführen sind.

## Verwendung

Generische Datentypen werden primär in Standard-Bibliotheken verwendet. Ein Beispiel ist die `ADD`-Funktion, die am Eingang den Typ `ANY_NUM` akzeptiert und somit sowohl zwei `INT` als auch zwei `REAL` Werte addieren kann.

In anwenderdefinierten Programm-Organisationseinheiten (POEs) ist die Verwendung von `ANY`-Typen laut Norm nicht vorgesehen und bleibt herstellerspezifischen Erweiterungen vorbehalten.
