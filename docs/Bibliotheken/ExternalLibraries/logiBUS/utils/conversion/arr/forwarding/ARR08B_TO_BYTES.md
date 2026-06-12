# ARR08B_TO_BYTES



<img width="1089" height="362" alt="image" src="https://github.com/user-attachments/assets/35768584-80d4-464c-b258-e26d1456fd4f" />


![ARR08B_TO_BYTES](./ARR08B_TO_BYTES.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ARR08B_TO_BYTES` dient der Zerlegung eines 8-Elemente-Byte-Arrays (`ARR08B`) in acht einzelne Byte-Ausgänge. Er ist ein Hilfsbaustein für die Datenkonvertierung und -weiterleitung innerhalb von Steuerungsapplikationen, insbesondere wenn strukturierte Daten aus einem Array in diskrete Signale aufgeteilt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Dieses eingehende Ereignis löst die Verarbeitung des Funktionsblocks aus. Bei seinem Eintreffen werden die Daten am Eingang `IN` gelesen und auf die einzelnen Ausgänge verteilt.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses ausgehende Ereignis signalisiert den Abschluss der Verarbeitung. Es wird gleichzeitig mit der Ausgabe der neuen Werte an den Datenausgängen `OUT_00` bis `OUT_07` erzeugt.

### **Daten-Eingänge**
*   **IN** (`ARRAY[0..7] OF BYTE`): Der Eingang für das 8-Byte-Array, das zerlegt werden soll. Das Array hat einen festen Indexbereich von 0 bis 7.

### **Daten-Ausgänge**
*   **OUT_00** (`BYTE`): Enthält den Wert des Array-Elements mit Index 0 (`IN[0]`).
*   **OUT_01** (`BYTE`): Enthält den Wert des Array-Elements mit Index 1 (`IN[1]`).
*   **OUT_02** (`BYTE`): Enthält den Wert des Array-Elements mit Index 2 (`IN[2]`).
*   **OUT_03** (`BYTE`): Enthält den Wert des Array-Elements mit Index 3 (`IN[3]`).
*   **OUT_04** (`BYTE`): Enthält den Wert des Array-Elements mit Index 4 (`IN[4]`).
*   **OUT_05** (`BYTE`): Enthält den Wert des Array-Elements mit Index 5 (`IN[5]`).
*   **OUT_06** (`BYTE`): Enthält den Wert des Array-Elements mit Index 6 (`IN[6]`).
*   **OUT_07** (`BYTE`): Enthält den Wert des Array-Elements mit Index 7 (`IN[7]`).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Die Funktionsweise ist deterministisch und einfach: Bei jedem Eintreffen des `REQ`-Ereignisses liest der Baustein das komplette Eingangsarray `IN`. Anschließend wird jedes Element des Arrays einem spezifischen Byte-Ausgang zugewiesen. Die Zuordnung erfolgt direkt entsprechend dem Array-Index. Nachdem alle Zuweisungen durchgeführt wurden, wird das `CNF`-Ereignis ausgelöst, um den erfolgreichen Abschluss der Operation an nachfolgende Blöcke zu melden.

Der enthaltene ST-Code (Structured Text) zeigt die direkte Implementierung:
```iecst
OUT_00 := IN[0];
OUT_01 := IN[1];
...
OUT_07 := IN[7];
```

## Technische Besonderheiten
*   **Feste Größe:** Der Block ist spezifisch für Arrays mit exakt 8 Elementen (`ARR08B`) ausgelegt. Für Arrays anderer Längen sind separate Blöcke erforderlich.
*   **Synchrone Verarbeitung:** Die Verarbeitung erfolgt in einem einzigen Zyklus ohne Verzögerung. Die Latenz zwischen `REQ` und `CNF` ist minimal.
*   **Kein internen Zustand:** Der Block besitzt keinen internen Speicher. Die Ausgabe ist zu jedem Zeitpunkt eine direkte Funktion der aktuellen Eingabe.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände im Sinne einer Zustandsmaschine. Sein Verhalten ist rein kombinatorisch und wird vollständig durch die Schnittstellenereignisse gesteuert:
1.  **Ruhezustand:** Warten auf das `REQ`-Ereignis.
2.  **Ausführungszustand:** Bei `REQ` werden die Daten transferiert und sofort das `CNF`-Ereignis generiert. Der Block kehrt unmittelbar danach in den Ruhezustand zurück.

## Anwendungsszenarien
*   **Datenverteilung:** Aufteilung eines empfangenen Datenpakets (z.B. von einer Kommunikationsschnittstelle) in seine einzelnen Byte-Komponenten für die weitere Verarbeitung in der Applikation.
*   **Schnittstellen-Adapter:** Anbindung von Funktionsblöcken, die mit Array-Strukturen arbeiten, an Blöcke, die einzelne Byte-Eingänge erwarten.
*   **Datenprotokollierung und -visualisierung:** Separierung von Array-Daten, um einzelne Bytes in HMIs oder Logging-Systemen gezielt anzuzeigen oder zu speichern.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **`SEL_n` / `MUX`-Blöcke:** Diese Blöcke wählen ein Element aus einem Array basierend auf einem Index aus. `ARR08B_TO_BYTES` hingegen extrahiert **alle** Elemente gleichzeitig und parallel.
*   **`BYTES_TO_ARR08B`:** Dies ist der inverse Baustein, der acht einzelne Byte-Eingänge zu einem 8-Byte-Array zusammenfasst.
*   **Generische Array-Zerlegungsblöcke:** Es könnten generischere Blöcke existieren, die die Array-Länge als Parameter erhalten. `ARR08B_TO_BYTES` ist durch seine feste Größe einfacher, schneller und benötigt keine Konfiguration.

## Fazit
Der `ARR08B_TO_BYTES` Funktionsblock ist ein spezialisierter, effizienter und zuverlässiger Baustein für die grundlegende Operation der Array-Zerlegung. Seine Stärke liegt in der Einfachheit und Eindeutigkeit für den spezifischen Anwendungsfall eines 8-Byte-Arrays. Für Steuerungsanwendungen, in denen diese Datenstruktur häufig vorkommt, bietet er eine optimierte und wartungsfreundliche Lösung gegenüber der manuellen Indexierung in komplexeren Blöcken.