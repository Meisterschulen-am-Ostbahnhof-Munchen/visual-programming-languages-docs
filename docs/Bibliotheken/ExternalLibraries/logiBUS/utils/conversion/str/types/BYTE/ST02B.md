# ST02B

```{index} single: ST02B
```

* * * * * * * * * *
## Einleitung
`ST02B` ist ein benutzerdefinierter, strukturierter Datentyp innerhalb der 4diac-IDE. Er definiert eine Datenstruktur, die zwei einzelne Bytes zu einer logischen Einheit zusammenfasst. Dies vereinfacht die Handhabung von Paaren von Byte-Werten.

## Strukturdefinition
Da `ST02B` ein Datentyp und kein Funktionsblock ist, besitzt er keine Schnittstellen im Sinne von Ereignis-Ein-/Ausgängen, Daten-Ein-/Ausgängen oder Adaptern. Stattdessen werden hier die internen Komponenten des Datentyps beschrieben.

### **Komponenten der Struktur**
Die Struktur `ST02B` besteht aus den folgenden zwei Byte-Variablen:

*   **B_00** (Typ: `BYTE`): Das erste Byte der Struktur (BYTE 00).
*   **B_01** (Typ: `BYTE`): Das zweite Byte der Struktur (BYTE 01).

## Funktionsweise
Als passiver Datentyp hat `ST02B` keine eigene "Funktionsweise". Seine Funktion besteht darin, eine definierte Vorlage für Daten bereitzustellen. Instanzen dieses Datentyps können verwendet werden, um Daten zu speichern, zu organisieren und als Einheit zwischen verschiedenen Funktionsblöcken auszutauschen.

## Technische Besonderheiten
`ST02B` ist als `StructuredType` definiert und besteht aus zwei aufeinanderfolgenden `BYTE`-Variablen. Die Gesamtgröße einer Instanz dieses Datentyps beträgt daher 2 Bytes.

## Anwendungsszenarien
*   **Datenübertragung**: Bündelung von 2 Bytes, die als Einheit behandelt werden sollen.
*   **Registerabbildung**: Repräsentation eines 2-Byte-Registers (ähnlich einem WORD, aber mit explizitem Byte-Zugriff).
*   **Kleine Datenpakete**: Vereinfachte Handhabung von kleinen, fest definierten Datenpaketen.

## Vergleich mit ähnlichen Bausteinen
*   **Array von Bytes (ARRAY OF BYTE [2])**: Ein Array von 2 Bytes erfüllt den gleichen Zweck. `ST02B` bietet jedoch den Vorteil benannter Felder (B_00, B_01).
*   **`WORD`**: Repräsentiert ebenfalls 2 Bytes. `ST02B` ist flexibler, wenn die einzelnen Bytes unabhängig voneinander manipuliert werden müssen.

## Fazit
`ST02B` ist ein einfacher, nützlicher strukturierter Datentyp zur Verwaltung von zwei Bytes als kohärente Einheit.