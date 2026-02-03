# ST16X

```{index} single: ST16X
```

* * * * * * * * * *
## Einleitung
ST16X ist ein benutzerdefinierter Datentyp, der eine Struktur von 16 einzelnen BOOL-Werten definiert. Er dient dazu, eine Sammlung von binären Zuständen oder Flags in einer einzigen, organisierten Einheit zu kapseln. Obwohl es sich um einen Datentyp und nicht um einen Funktionsblock handelt, wird seine Struktur und Verwendungsweise hier beschrieben. Der Datentyp wurde erstellt, um eine übersichtliche und typsichere Möglichkeit zur Verwaltung von 16 logischen Zuständen zu bieten.

## Schnittstellenstruktur
Da ST16X ein Datentyp und kein Funktionsblock ist, besitzt er keine klassischen Schnittstellen im Sinne von Ereignis- oder Daten-Ein-/Ausgängen. Stattdessen definiert seine 'Struktur' die internen Mitglieder, die im Folgenden detailliert werden.

### **Ereignis-Eingänge**
Nicht zutreffend für einen Datentyp.

### **Ereignis-Ausgänge**
Nicht zutreffend für einen Datentyp.

### **Daten-Eingänge**
Nicht zutreffend für einen Datentyp.

### **Daten-Ausgänge**
Nicht zutreffend für einen Datentyp.

### **Adapter**
Nicht zutreffend für einen Datentyp.

Die Struktur des Datentyps ST16X ist wie folgt definiert:

| Name | Typ | Kommentar |
| :--- | :--- | :--- |
| X_00 | BOOL | BIT 00 |
| X_01 | BOOL | BIT 01 |
| X_02 | BOOL | BIT 02 |
| X_03 | BOOL | BIT 03 |
| X_04 | BOOL | BIT 04 |
| X_05 | BOOL | BIT 05 |
| X_06 | BOOL | BIT 06 |
| X_07 | BOOL | BIT 07 |
| X_08 | BOOL | BIT 08 |
| X_09 | BOOL | BIT 09 |
| B_10 | BOOL | BIT 10 |
| B_11 | BOOL | BIT 11 |
| B_12 | BOOL | BIT 12 |
| B_13 | BOOL | BIT 13 |
| B_14 | BOOL | BIT 14 |
| B_15 | BOOL | BIT 15 |

## Funktionsweise
Ein Datentyp wie ST16X hat keine aktive 'Funktionsweise' im Sinne eines Algorithmus, der ausgeführt wird. Er definiert lediglich eine Vorlage für Daten. Die 'Funktionsweise' ergibt sich aus der Art und Weise, wie dieser Datentyp in Funktionsblöcken oder anderen Programmlogiken verwendet wird, um 16 individuelle boolesche Zustände zu speichern und zu verwalten. Eine Variable vom Typ ST16X kann erstellt werden, und ihre einzelnen BOOL-Elemente können gelesen und geschrieben werden (z.B. `meineST16XVariable.X_00 := TRUE;`).

## Technische Besonderheiten
*   **Strukturierte Anordnung:** Der Datentyp fasst 16 unabhängige BOOL-Werte zu einer logischen Einheit zusammen.
*   **Eindeutige Benennung:** Jedes Bit ist über einen individuellen Namen (`X_00` bis `B_15`) anstatt über einen Index ansprechbar, was die Lesbarkeit des Codes verbessert.
*   **Kommentar:** Jeder Variable ist ein Kommentar zugeordnet ("BIT xx"), der die Bitposition verdeutlicht.
*   **Modularität:** Fördert die Modularität und Wiederverwendbarkeit von Code, indem komplexe Statusinformationen gebündelt werden.

## Zustandsübersicht
Als reiner Datentyp hat ST16X selbst keine 'Zustandsübersicht' im Sinne eines endlichen Automaten oder einer internen Logik. Der 'Zustand' wird durch die aktuellen Werte der 16 enthaltenen BOOL-Variablen repräsentiert, die jeweils `TRUE` oder `FALSE` sein können. Die Kombination dieser 16 Booleschen Werte ergibt 2^16 (65.536) mögliche Zustände für eine Instanz des Datentyps.

## Anwendungsszenarien
*   **Statusregister:** Darstellung des Zustands von bis zu 16 verschiedenen Komponenten, Sensoren oder Funktionen (z.B. "Motor EIN", "Fehler aktiv", "Grenzwert erreicht").
*   **Bit-Flags:** Speicherung von Konfigurations-Flags oder Fehlerindikatoren in Steuerungsanwendungen.
*   **Digitale Ein-/Ausgangssignale:** Bündelung von digitalen Ein- oder Ausgängen eines Moduls, um sie als eine einzige Datenstruktur zu übergeben.
*   **Datenpaketierung:** Vereinfachte Übergabe von mehreren binären Informationen zwischen Funktionsblöcken oder über Kommunikationsschnittstellen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Da ST16X ein Datentyp ist, kann er nicht direkt mit einem 'Baustein' im Sinne eines Funktionsblocks verglichen werden. Er kann jedoch mit anderen Möglichkeiten zur Speicherung von Binärdaten verglichen werden:

*   **Einzelne BOOL-Variablen:** ST16X bietet den Vorteil, 16 BOOLs als eine Einheit zu behandeln, was die Datenstrukturierung und Übergabe vereinfacht und die Anzahl der deklarierten Variablen reduziert.
*   **ARRAY OF BOOL:** Ein `ARRAY [0..15] OF BOOL` bietet eine ähnliche Funktionalität. ST16X hat den Vorteil, dass die einzelnen Bits über sprechende Namen (z.B. `meineST16XVariable.X_00`) adressiert werden können, was die Lesbarkeit verbessert, anstatt über Indizes (`meinARRAY[0]`).
*   **WORD/INT-Typen:** Diese können ebenfalls zur Speicherung von Bits verwendet werden. ST16X bietet eine typsichere und selbstdokumentierende Möglichkeit, Bits zu verwalten, ohne manuelle Bit-Maskierungsoperationen oder typische Umwandlungsfehler.

## Fazit
Der Datentyp ST16X stellt eine effiziente und übersichtliche Methode dar, um eine Gruppe von 16 booleschen Werten zu strukturieren. Er verbessert die Lesbarkeit des Codes, vereinfacht die Handhabung komplexer binärer Zustände und fördert die Typsicherheit in 4diac-Anwendungen, insbesondere in Szenarien, wo viele individuelle binäre Informationen als eine zusammengehörige Einheit verwaltet werden müssen.