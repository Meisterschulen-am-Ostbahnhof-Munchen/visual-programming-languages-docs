# CYCLE_TIME

```{index} single: CYCLE_TIME
```

<img width="1186" height="212" alt="image" src="https://github.com/user-attachments/assets/9a52222d-13af-45a6-94bb-67de45036241" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `CYCLE_TIME` dient zur Berechnung der verstrichenen Zeit zwischen zwei aufeinanderfolgenden Aufrufen. Er ist ein nützliches Werkzeug zur Überwachung und Diagnose von Zykluszeiten in Echtzeitanwendungen, beispielsweise zur Leistungsanalyse oder zur Erkennung von unerwarteten Verzögerungen in einem Steuerungssystem.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Startet die Berechnung der Zykluszeit. Bei diesem Ereignis wird der Algorithmus ausgeführt.

### **Ereignis-Ausgänge**
*   **CNF**: Wird ausgelöst, sobald die Berechnung abgeschlossen ist. Dieses Ereignis bestätigt die Ausführung und liefert die berechneten Werte an die Datenausgänge.

### **Daten-Eingänge**
*   **TM** (DINT): Stellt den aktuellen Zeitstempel zum Zeitpunkt des Aufrufs bereit. Dieser Wert wird typischerweise von einer Systemuhr oder einem Timer-Baustein geliefert. Initialwert ist `0`.

### **Daten-Ausgänge**
*   **CYCLE** (DINT): Enthält die berechnete Zykluszeit, also die Differenz zwischen dem aktuellen (`TM`) und dem vorherigen Zeitstempel (`LAST`). Initialwert ist `0`.
*   **LAST** (DINT): Speichert den Zeitstempel des letzten Aufrufs (`TM`). Dieser Wert wird für die nächste Berechnung verwendet. Initialwert ist `0`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapterschnittstellen.

## Funktionsweise
Bei jedem Eintreffen des `REQ`-Ereignisses wird der zugehörige Algorithmus `REQ` ausgeführt. Dieser Algorithmus führt zwei wesentliche Operationen durch:
1.  **Berechnung der Zykluszeit**: Die Differenz zwischen dem neu eingehenden Zeitwert `TM` und dem gespeicherten Wert `LAST` (vom vorherigen Aufruf) wird berechnet und an den Ausgang `CYCLE` ausgegeben.
2.  **Aktualisierung des Zeitstempels**: Der aktuelle Eingangswert `TM` wird im internen Speicher `LAST` für den nächsten Berechnungszyklus gesichert.

Unmittelbar nach der Ausführung des Algorithmus wird das `CNF`-Ereignis mit den aktualisierten Werten an `CYCLE` und `LAST` ausgelöst.

## Technische Besonderheiten
*   Der Baustein ist ein **Simple Function Block (Basic FB)** gemäß IEC 61499.
*   Die verwendeten Datentypen (`DINT`) sind vorzeichenbehaftete 32-Bit-Integer, die für die Darstellung großer Zeitwerte (z.B. in Millisekunden oder Mikrosekunden) geeignet sind.
*   Die Initialwerte von `TM`, `CYCLE` und `LAST` sind auf `0` gesetzt. Der erste gültige `CYCLE`-Wert nach dem Start ergibt sich daher aus der Differenz `TM - 0`. Dies sollte bei der Initialisierungslogik der Anwendung berücksichtigt werden.

## Zustandsübersicht
Der Baustein besitzt einen einzigen Execution Control State (EC-State) mit dem Namen `REQ`. Bei Eintritt in diesen Zustand wird stets der Algorithmus `REQ` ausgeführt und anschließend das `CNF`-Ereignis produziert.

## Anwendungsszenarien
*   **Zykluszeitüberwachung**: Kontinuierliche Messung der Ausführungszeit eines Programms oder eines bestimmten Programmteils.
*   **Performance-Monitoring**: Identifikation von Engpässen oder ungewöhnlich langen Zykluszeiten in einer Steuerungsapplikation.
*   **Diagnose**: Protokollierung von Zykluszeiten zu Analysezwecken oder zur Erstellung von Systemlaufzeitstatistiken.
*   **Adaptive Steuerung**: Bereitstellung der aktuellen Zykluszeit für Algorithmen, deren Verhalten von der verfügbaren Rechenzeit abhängen soll.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu generischen Zeitmessbausteinen (wie `E_DELAY` oder `E_CYCLE`) ist `CYCLE_TIME` spezialisiert auf die **Differenzbildung zwischen aufeinanderfolgenden Zeitpunkten**. Er führt keinen eigenen Timer, sondern wertet extern bereitgestellte Zeitstempel aus. Bausteine wie `E_SR` oder `E_R_TRIG` dienen grundlegend anderen Zwecken (Speichern, Flankenerkennung) und bieten keine Zeitdifferenzberechnung.

## Fazit
Der `CYCLE_TIME`-Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Laufzeitmessung in IEC 61499-basierten Steuerungssystemen. Seine klare Schnittstelle und einfache Funktionsweise machen ihn zu einer robusten Komponente für Diagnose- und Monitoring-Aufgaben, wo die Genauigkeit und Zuverlässigkeit der Zykluszeiterfassung im Vordergrund steht.