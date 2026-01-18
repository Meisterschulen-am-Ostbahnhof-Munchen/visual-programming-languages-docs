# ST04B

```{index} single: ST04B
```

* * * * * * * * * *
## Einleitung
`ST04B` ist ein benutzerdefinierter, strukturierter Datentyp innerhalb der 4diac-IDE. Im Gegensatz zu einem Funktionsblock (FB), der eine spezifische Funktionalität implementiert, definiert ein Datentyp eine Datenstruktur, die von Funktionsblöcken oder anderen Datentypen verwendet werden kann. Dieser Datentyp fasst vier einzelne Bytes zu einer logischen Einheit zusammen, um deren gemeinsame Handhabung zu vereinfachen.

## Strukturdefinition
Da `ST04B` ein Datentyp und kein Funktionsblock ist, besitzt er keine Schnittstellen im Sinne von Ereignis-Ein-/Ausgängen, Daten-Ein-/Ausgängen oder Adaptern. Die nachfolgenden Abschnitte adaptieren die ursprüngliche Anforderung einer Schnittstellenstruktur, um die internen Komponenten des Datentyps darzustellen.

### **Komponenten der Struktur**
Die Struktur `ST04B` besteht aus den folgenden vier Byte-Variablen:

*   **B_00** (Typ: `BYTE`): Das erste Byte der Struktur (BYTE 00).
*   **B_01** (Typ: `BYTE`): Das zweite Byte der Struktur (BYTE 01).
*   **B_02** (Typ: `BYTE`): Das dritte Byte der Struktur (BYTE 02).
*   **B_03** (Typ: `BYTE`): Das vierte Byte der Struktur (BYTE 03).

## Funktionsweise
Als passiver Datentyp hat `ST04B` keine eigene "Funktionsweise" im Sinne einer Logik oder eines Algorithmus. Seine Funktion besteht darin, eine definierte Vorlage für Daten bereitzustellen. Instanzen dieses Datentyps können in Funktionsblöcken deklariert und verwendet werden, um Daten zu speichern, zu organisieren und als kohärente Einheit zwischen verschiedenen Funktionsblöcken auszutauschen. Die internen Komponenten (B_00 bis B_03) sind direkt adressierbar.

## Technische Besonderheiten
`ST04B` ist als `StructuredType` definiert und besteht aus vier aufeinanderfolgenden `BYTE`-Variablen. Die Gesamtgröße einer Instanz dieses Datentyps beträgt daher 4 Bytes. Im Kontext der 4diac-Laufzeitumgebung wird dieser Datentyp entsprechend seiner Definition im Speicher abgelegt. Die interne Struktur ermöglicht einen direkten Zugriff auf jedes einzelne Byte über seinen Namen (z.B. `myST04B.B_00`).

Der 4diac-Compiler ordnet diesen Datentyp dem Paket `logiBUS::utils::conversion::types` zu.

## Zustandsübersicht
Als passiver Datentyp, der lediglich eine Datenstruktur definiert, besitzt `ST04B` keine eigene interne Logik oder Zustandsmaschine im Sinne eines Funktionsblocks. Sein "Zustand" ist ausschließlich durch die Werte seiner vier Komponenten-Bytes bestimmt. Eine Zustandsübersicht im Sinne von Verhaltenszuständen ist daher nicht anwendbar.

## Anwendungsszenarien
*   **Datenübertragung**: Bündelung von 4 Bytes, die über eine Kommunikationsschnittstelle (z.B. seriell, Modbus, CAN) empfangen oder gesendet werden, und die als Einheit behandelt werden sollen.
*   **Registerabbildung**: Repräsentation eines 4-Byte-Registers oder einer Gruppe von Registern in einer speicherprogrammierbaren Steuerung (SPS) oder einem anderen Steuerungssystem.
*   **Kleine Datenpakete**: Vereinfachte Handhabung von kleinen, fest definierten Datenpaketen in der industriellen Automatisierung.
*   **Typkonvertierungshilfsmittel**: Interne Verwendung in Konvertierungsfunktionsblöcken, um spezifische Byte-Sequenzen zu verarbeiten und in andere Datentypen umzuwandeln.

## Vergleich mit ähnlichen Bausteinen
*   **Array von Bytes (ARRAY OF BYTE [4])**: Ein Array von 4 Bytes erfüllt den gleichen Zweck bezüglich der Speicherung. `ST04B` bietet jedoch den Vorteil, dass die einzelnen Bytes über benannte Felder (B_00, B_01, etc.) anstatt über Indizes (z.B. `myArray[0]`, `myArray[1]`) angesprochen werden können, was die Lesbarkeit und Selbstbeschreibung des Codes verbessern kann.
*   **Andere strukturierte Typen**: Wenn die Bytes eine spezifische Bedeutung (z.B. Statusflag, Zählerwert) hätten, könnten komplexere strukturierte Typen mit aussagekräftigeren Variablennamen oder sogar Bitfeldern sinnvoller sein. `ST04B` ist bewusst generisch gehalten, um eine flexible Gruppierung von Bytes zu ermöglichen.
*   **`WORD`, `DWORD`**: Diese Standarddatentypen repräsentieren ebenfalls eine bestimmte Anzahl von Bytes (2 bzw. 4). `ST04B` ist jedoch flexibler, wenn die einzelnen Bytes unabhängig voneinander manipuliert werden müssen oder wenn die Byte-Reihenfolge (Endianness) eine Rolle spielt und explizit gesteuert werden soll.

## Fazit
`ST04B` ist ein grundlegender, aber nützlicher strukturierter Datentyp in 4diac, der die Verwaltung von vier Bytes als kohärente Einheit vereinfacht. Er verbessert die Code-Lesbarkeit und Modularität, insbesondere in Anwendungen, die den Austausch oder die Verarbeitung von Byte-sequenzierten Daten erfordern. Seine einfache Definition macht ihn zu einem flexiblen Baustein für vielfältige Datenmanagementaufgaben in der Automatisierungstechnik.