# QUARTERS_TO_BOOLS

<img width="1211" height="473" alt="image" src="https://github.com/user-attachments/assets/3736c2d1-1312-41dd-8375-2cf4ab9c7c50" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `QUARTERS_TO_BOOLS` ist ein Composite Function Block, der 16 separate 2-Bit-Eingabewerte (sogenannte "Quarter Bytes") parallel in entsprechende boolesche Ausgangssignale umwandelt. Er dient als Wrapper und vereinfacht die Handhabung, indem er eine Vielzahl einzelner Konvertierungsbausteine zu einem einzigen, übersichtlichen Baustein zusammenfasst. Dieser Block ist besonders nützlich in Steuerungssystemen, in denen kompakte Datenformate (wie 2-Bit-Zustände in einem Byte) in einfache binäre Steuersignale für Aktoren oder Statusanzeigen umgesetzt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Startet die Verarbeitung. Bei Eintreffen dieses Ereignisses werden alle 16 Eingabewerte (`IB_00` bis `IB_15`) ausgelesen und verarbeitet.

### **Ereignis-Ausgänge**
*   **CNF**: Signalisiert die erfolgreiche Beendigung der Verarbeitung. Dieses Ereignis wird ausgegeben, nachdem alle 16 internen Konvertierungen abgeschlossen und die Ausgangsdaten (`Q_00` bis `Q_15`) aktualisiert sind.

### **Daten-Eingänge**
*   **IB_00** bis **IB_15** (Typ: `BYTE`): 16 Eingänge für 2-Bit-Daten (Quarter Bytes). Jeder Eingang kann einen von vier definierten Zuständen repräsentieren (z.B. `quarter::COMMAND_DISABLE`). Der Standard-Initialwert für alle Eingänge ist `quarter::COMMAND_DISABLE`.

### **Daten-Ausgänge**
*   **Q_00** bis **Q_15** (Typ: `BOOL`): 16 boolesche Ausgänge, die den konvertierten Zustand des jeweiligen Quarter-Byte-Eingangs widerspiegeln. Der Initialwert aller Ausgänge ist `FALSE`.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter-Schnittstellen.

## Funktionsweise
`QUARTERS_TO_BOOLS` ist ein Composite FB, der intern aus 16 Instanzen des Basisfunktionsblocks `QUARTER_TO_BOOL` besteht. Jede dieser Instanzen ist für die Konvertierung eines spezifischen Eingangs (`IB_xx`) zuständig.

1.  **Auslösung**: Das Eintreffen des Ereignisses `REQ` löst die Verarbeitungskette aus.
2.  **Parallele Datenverteilung**: Die an den Eingängen `IB_00` bis `IB_15` anliegenden Byte-Werte werden parallel an die entsprechenden Eingänge (`IB`) der 16 internen `QUARTER_TO_BOOL`-Blöcke weitergeleitet.
3.  **Serielle Ereignisverarbeitung**: Das `REQ`-Ereignis wird seriell durch die Kette der internen Blöcke propagiert. Es startet bei `QUARTER_TO_BOOL_00` und wird nacheinander von einem Block zum nächsten weitergereicht (`CNF` -> `REQ`), bis der letzte Block (`QUARTER_TO_BOOL_15`) seine Verarbeitung abschließt.
4.  **Konvertierung**: Jeder interne `QUARTER_TO_BOOL`-Block interpretiert seinen Byte-Eingangswert gemäß einer definierten Logik (vermutlich basierend auf den zwei niederwertigsten Bits) und setzt ihn auf einen booleschen Wahrheitswert (`TRUE` oder `FALSE`) um.
5.  **Ergebnisausgabe**: Die booleschen Ergebnisse (`Q`) der internen Blöcke werden auf die entsprechenden Ausgänge `Q_00` bis `Q_15` des Composite-Blocks geschaltet.
6.  **Abschluss**: Sobald der letzte interne Block fertig ist, löst der Composite-Block sein `CNF`-Ereignis aus, um den Abschluss des gesamten Konvertierungszyklus für alle 16 Kanäle zu signalisieren.

## Technische Besonderheiten
*   **Initialisierung**: Alle Eingänge sind mit dem spezifischen Wert `quarter::COMMAND_DISABLE` vorbelegt, und alle Ausgänge starten mit `FALSE`. Dies gewährleistet einen definierten, inaktiven Ausgangszustand.
*   **Verarbeitungsreihenfolge**: Während die Dateneingänge parallel verteilt werden, erfolgt die Ereignisverarbeitung streng sequenziell von Index 00 bis 15. Dies führt zu einer deterministischen, wenn auch nicht gleichzeitigen, Aktualisierung der Ausgänge.
*   **Komposit-Bauweise**: Der Block kapselt die Komplexität von 16 einzelnen Konvertierungen und bietet eine saubere, vereinheitlichte Schnittstelle, was die Wiederverwendbarkeit und Lesbarkeit in übergeordneten Applikationen erhöht.

## Zustandsübersicht
Als Composite Function Block besitzt `QUARTERS_TO_BOOLS` keinen eigenen komplexen Zustandsautomaten im herkömmlichen Sinne. Sein Verhalten wird durch das Netzwerk der internen Blöcke definiert. Vereinfacht kann der Gesamtzustand als **Idle** (wartet auf `REQ`) und **Processing** (Ereignis läuft durch die interne Kette) betrachtet werden. Der `CNF`-Ausgang markiert den Übergang zurück in den Idle-Zustand.

## Anwendungsszenarien
*   **Kompakte SPS-Anbindung**: Umwandlung von kompakten 32-Bit-Datenwörtern (die 16 2-Bit-Zustände enthalten) in 16 einzelne binäre Steuersignale für Ventile, Lampen oder Relais.
*   **Statusdekodierung**: Dekodierung von Gerätestatusinformationen, die in einem "Quarter Byte"-Format übertragen werden, in einzelne, leicht verarbeitbare Fehler- oder Betriebszustandsbits.
*   **Vereinfachung von Funktionsplanern**: Ersetzt 16 separate `QUARTER_TO_BOOL`-Blöcke und deren Verdrahtung in einem Funktionsplan durch einen einzigen, übersichtlichen Block, was die Projektwartung erleichtert.

## Vergleich mit ähnlichen Bausteinen
*   **`QUARTER_TO_BOOL`**: Dies ist der elementare Baustein, der einen einzelnen 2-Bit-Eingang konvertiert. `QUARTERS_TO_BOOLS` bündelt 16 Instanzen dieses Blocks zu einer Einheit. Die Verwendung des Composite-Blocks ist effizienter für die Handhabung mehrerer Kanäle, während der Einzelblock maximale Flexibilität bei der individuellen Platzierung und Verdrahtung bietet.
*   **`BYTE_TO_BOOL`-Blöcke**: Konventionelle Blöcke, die ein ganzes Byte in 8 einzelne Bits aufspalten. `QUARTERS_TO_BOOLS` ist spezialisierter, da er davon ausgeht, dass jedes Byte bereits in vier unabhängige 2-Bit-Einheiten unterteilt ist, die separat interpretiert werden müssen.

## Fazit
Der `QUARTERS_TO_BOOLS`-Funktionsblock ist ein praktisches und zeitsparendes Hilfsmittel für die IEC 61499-Programmierung, wenn häufig mehrere 2-Bit-Datenkanäle in boolesche Signale umgewandelt werden müssen. Durch die Kapselung von 16 Konvertierungen in einem Block reduziert er den Verdrahtungsaufwand in übergeordneten Applikationen erheblich und verbessert die Übersichtlichkeit. Seine deterministische, serielle Ereignisabarbeitung gewährleistet ein zuverlässiges Verhalten, das für Steuerungsaufgaben gut geeignet ist.
