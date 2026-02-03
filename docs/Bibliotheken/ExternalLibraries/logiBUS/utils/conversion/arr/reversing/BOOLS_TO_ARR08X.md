# BOOLS_TO_ARR08X

```{index} single: BOOLS_TO_ARR08X
```

<img width="1090" height="362" alt="image" src="https://github.com/user-attachments/assets/61dbe877-33a2-4798-8137-868082aad02a" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `BOOLS_TO_ARR08X` dient der Konvertierung von acht einzelnen booleschen (`BOOL`) Eingangssignalen in ein boolesches Array (`ARRAY[0..7] OF BOOL`). Er ist ein grundlegender Baustein zur Signalzusammenführung und Datenstrukturierung in Steuerungsanwendungen, insbesondere wenn diskrete digitale Signale für eine kompakte Weiterverarbeitung oder Übertragung gebündelt werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   `REQ` (Request): Löst die Konvertierungsoperation aus. Bei Eintreffen dieses Ereignisses werden die aktuellen Werte an den acht `IN_xx`-Eingängen gelesen und in das Ausgangsarray `OUT` geschrieben.

### **Ereignis-Ausgänge**
*   `CNF` (Confirm): Wird ausgelöst, sobald die Konvertierung abgeschlossen ist und das Ausgangsarray `OUT` mit den neuen Werten bereitsteht.

### **Daten-Eingänge**
Acht einzelne boolesche Eingänge (`BOOL`), die jeweils einem Bit im resultierenden Array entsprechen:
*   `IN_00`: Wert für Bit 00 / Array-Index 0.
*   `IN_01`: Wert für Bit 01 / Array-Index 1.
*   `IN_02`: Wert für Bit 02 / Array-Index 2.
*   `IN_03`: Wert für Bit 03 / Array-Index 3.
*   `IN_04`: Wert für Bit 04 / Array-Index 4.
*   `IN_05`: Wert für Bit 05 / Array-Index 5.
*   `IN_06`: Wert für Bit 06 / Array-Index 6.
*   `IN_07`: Wert für Bit 07 / Array-Index 7.

### **Daten-Ausgänge**
*   `OUT`: Das Ausgangssignal vom Typ `ARRAY[0..7] OF BOOL`. Nach Auslösung des `REQ`-Ereignisses enthält es die zu diesem Zeitpunkt an den Eingängen anliegenden Werte, wobei `IN_00` auf `OUT[0]` und `IN_07` auf `OUT[7]` abgebildet wird.

### **Adapter**
Dieser Funktionsblock besitzt keine Adapterschnittstellen.

## Funktionsweise
Die Funktionsweise ist deterministisch und einfach. Bei jedem Eintreffen eines Ereignisses am `REQ`-Eingang wird der enthaltene ST-Code ausgeführt. Dieser Code weist jedem Element des Ausgangsarrays `OUT` direkt den Wert des entsprechenden einzelnen `IN_xx`-Eingangs zu. Die Abbildung ist fest verdrahtet:
`OUT[0] := IN_00;`
`OUT[1] := IN_01;`
...
`OUT[7] := IN_07;`
Unmittelbar nach dieser Zuweisung wird das `CNF`-Ereignis generiert, um den erfolgreichen Abschluss der Operation zu signalisieren. Es findet keine Pufferung, Verzögerung oder logische Verknüpfung der Eingangswerte statt.

## Technische Besonderheiten
*   **Echtzeitverhalten:** Die Operation ist atomar und sehr schnell, da sie nur aus direkten Zuweisungen besteht. Sie fügt keine nennenswerte Latenz in den Steuerungszyklus ein.
*   **Größenfestlegung:** Das Ausgangsarray ist mit der festen Größe `[0..7]` definiert, was genau acht Elementen entspricht.
*   **Synchrone Abarbeitung:** Alle Eingangswerte werden zum Zeitpunkt des `REQ`-Ereignisses synchron erfasst. Änderungen an den Eingängen während der Abarbeitung haben keinen Einfluss auf den aktuellen Zyklus.

## Zustandsübersicht
Der Funktionsblock ist zustandslos (stateless). Er besitzt kein internes Gedächtnis. Seine Ausgabe ist zu jedem Zeitpunkt ausschließlich eine Funktion der aktuellen Eingangswerte beim letzten `REQ`-Ereignis.

## Anwendungsszenarien
*   **Bündelung von Schaltzuständen:** Zusammenfassen der Zustände mehrerer Endschalter, Taster oder Ventile in ein einziges Array für die Übertragung über ein Netzwerk oder an einen übergeordneten Steuerungsbaustein.
*   **Vorverarbeitung für Array-basierte Blöcke:** Bereitstellung von Eingangsdaten für Funktionsblöcke, die ihre Operationen auf ganzen Arrays durchführen (z.B. logische Verknüpfungen, Verschiebeoperationen).
*   **Strukturierung von E/A-Daten:** Ordnung von verteilten digitalen Eingangssignalen einer SPS in einer definierten Datenstruktur für verbesserte Lesbarkeit und Wartbarkeit des Programms.
*   **Schnittstelle zu Visualisierungssystemen:** Einfacheres Mapping von vielen Einzelsignalen auf ein zusammengesetztes Symbol oder eine Statusanzeige in einer HMI.

## ⚖️ Vergleich mit ähnlichen Bausteinen
*   **`BOOL_TO_xxx` Blöcke:** Blöcke wie `BOOL_TO_INT` oder `BOOL_TO_BYTE` konvertieren mehrere Bool-Werte ebenfalls in ein kompakteres Datum. `BOOLS_TO_ARR08X` erzeugt hingegen explizit ein Array, was den indizierten Zugriff auf jedes einzelne Bit erhält und die semantische Bedeutung der Position bewahrt.
*   **Manuelle Verkabelung:** Die Alternative wäre die direkte Verkabelung jedes Einzelbits auf die Indizes eines Array-Variablenbausteins. `BOOLS_TO_ARR08X` kapselt diese Operation, verbessert die Übersichtlichkeit im FBD/LD-Editor und reduziert Verdrahtungsaufwand.
*   **`MERGE`/`CONCAT`-Blöcke:** Allgemeine Zusammenführungsblöcke können verschiedene Datentypen verbinden. `BOOLS_TO_ARR08X` ist spezialisiert und typsicher für genau acht BOOL-Eingänge und ein BOOL-Array als Ausgang.




## 🛠️ Zugehörige Übungen

* [Uebung_054](../../../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_054.md)

## Fazit
Der `BOOLS_TO_ARR08X` ist ein spezialisierter, robuster und effizienter Funktionsblock für eine häufige Aufgabe in der industriellen Automatisierung: die Bündelung diskreter Signale. Seine Stärke liegt in der Einfachheit, der deterministischen Ablaufzeit und der klaren Schnittstellendefinition. Er ist die erste Wahl, wenn acht boolesche Signale in einer geordneten Array-Struktur für die Weiterverarbeitung bereitgestellt werden müssen.