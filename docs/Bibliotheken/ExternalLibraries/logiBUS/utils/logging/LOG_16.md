# LOG_16

```{index} single: LOG_16
```

<img width="971" height="474" alt="image" src="https://github.com/user-attachments/assets/768789e5-7784-41c2-9d5c-c9492d64a38b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `LOG_16` ist ein Ring-Logger, der für den zyklischen Aufzeichnung von Daten beliebigen Typs (`ANY`) konzipiert ist. Er dient dazu, eingehende Werte in einem Puffer mit 16 Speicherplätzen zu halten, wobei ältere Einträge bei neuen Aufrufen überschrieben werden (Ringpuffer-Prinzip). Dieser Baustein ist besonders für die Protokollierung von Prozessdaten oder Zuständen in Echtzeitsteuerungen geeignet.

![LOG_16](LOG_16.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ (Service Request)**: Löst einen Log-Vorgang aus. Bei Eintreten dieses Ereignisses wird der aktuelle Wert am Daten-Eingang `IN` in den Ringpuffer übernommen.

### **Ereignis-Ausgänge**
*   **CNF (Confirmation of Requested Service)**: Wird nach erfolgreicher Verarbeitung des `REQ`-Ereignisses ausgelöst. Dieses Ereignis bestätigt den Log-Vorgang und stellt gleichzeitig alle 16 gespeicherten Werte an den Datenausgängen bereit.

### **Daten-Eingänge**
*   **IN (ANY)**: Der Datenwert, der bei einem `REQ`-Ereignis in den Ringpuffer geschrieben werden soll. Der Datentyp ist beliebig (`ANY`).

### **Daten-Ausgänge**
*   **OUT1 bis OUT16 (ANY)**: Die 16 Ausgänge, die den gesamten aktuellen Inhalt des Ringpuffers repräsentieren. `OUT1` enthält dabei den jüngsten Eintrag (das letzte geloggte `IN`), `OUT16` den ältesten. Bei jedem neuen Log-Vorgang (`REQ`) werden alle Werte im Puffer um eine Position verschoben.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Der `LOG_16` implementiert einen Ringpuffer (First-In-First-Out mit fester Größe) mit 16 Elementen. Bei jedem eintreffenden `REQ`-Ereignis wird der folgende Algorithmus ausgeführt:
1.  Der aktuelle Wert am Eingang `IN` wird als neuester Eintrag gespeichert.
2.  Alle bisher gespeicherten Werte werden um eine Position "nach hinten" (in Richtung `OUT16`) verschoben.
3.  Der Wert, der sich zuvor an Position 16 (`OUT16`) befand, wird verworfen.
4.  Das Bestätigungsereignis `CNF` wird ausgelöst.
5.  Die neuen 16 Pufferinhalte werden an den Ausgängen `OUT1` (neuester) bis `OUT16` (ältester) ausgegeben.

## Technische Besonderheiten
*   **Generischer Datentyp**: Die Verwendung des `ANY`-Datentyps für Ein- und Ausgänge macht den Baustein extrem flexibel. Er kann mit beliebigen Datentypen (z.B. `BOOL`, `INT`, `REAL`, `STRING` oder sogar strukturierten Typen) instanziiert und verwendet werden.
*   **Feste Puffergröße**: Die Puffergröße ist auf 16 Einträge festgelegt und nicht konfigurierbar.
*   **Sofortige Ausgabe**: Bei jedem Log-Vorgang wird der gesamte Pufferinhalt an den Ausgängen aktualisiert und mit dem `CNF`-Ereignis bestätigt.

## Zustandsübersicht
Der Baustein besitzt keinen persistenten internen Zustand im Sinne einer Zustandsmaschine außer dem Ringpuffer selbst. Sein Verhalten ist rein reaktiv: Auf ein `REQ`-Ereignis folgt stets eine Pufferaktualisierung und die Ausgabe von `CNF` mit den aktuellen Daten.

## Anwendungsszenarien
*   **Protokollierung von Prozesswerten**: Kurzfristige Aufzeichnung von Sensordaten (z.B. Temperaturverlauf der letzten 16 Zyklen).
*   **Fehlerhistorie**: Speicherung der letzten 16 Fehlercodes oder Alarmmeldungen.
*   **Datenvorverarbeitung**: Bereitstellung eines gleitenden Fensters über die letzten 16 Werte für nachfolgende Berechnungen (z.B. in einem weiteren FB).
*   **Debugging**: Einfache Überwachung von Variablenverläufen während der Entwicklung und Inbetriebnahme.

## Vergleich mit ähnlichen Bausteinen
*   **`E_DELAY` / Verzögerungsbausteine**: Diese Bausteine geben einen Eingangswert erst nach einer definierten Zeit verzögert wieder aus. Der `LOG_16` hingegen speichert eine Historie mehrerer Werte und gibt sie sofort, aber geordnet nach Aktualität, aus.
*   **`FIFO`-Bausteine**: Klassische FIFO-Speicher (First-In-First-Out) haben oft variable Längen und ein separates Lese-/Schreib-Interface. Der `LOG_16` ist ein spezieller FIFO mit fester Länge (16), der bei jedem Schreibvorgang automatisch den gesamten Inhalt ausgibt und überschreibt.
*   **Einfache `LOG`-Bausteine**: Einfache Logger ohne Puffer schreiben typischerweise nur einen einzelnen Wert. Die Stärke des `LOG_16` liegt in der ringförmigen Historie.


## Zugehörige Übungen

* [Uebung_122](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_122.md)
* [Uebung_122b](../../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_122b.md)

## Fazit
Der `LOG_16` ist ein nützlicher und generischer Funktionsblock für grundlegende Logging- und Pufferaufgaben in 4diac FORTE-Applikationen. Seine Stärken liegen in der Einfachheit, der generischen Typunterstützung und dem deterministischen Verhalten. Die feste Puffergröße von 16 ist für viele Überwachungsaufgaben ausreichend, für Anwendungen, die eine andere Puffertiefe oder ein selektives Lesen benötigen, sind jedoch angepasste oder erweiterte Bausteine erforderlich.