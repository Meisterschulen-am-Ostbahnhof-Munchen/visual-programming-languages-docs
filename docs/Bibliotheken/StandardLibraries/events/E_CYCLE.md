# E_CYCLE

```{index} single: E_CYCLE
```
## Einleitung
Der `E_CYCLE` ist ein Funktionsbaustein nach IEC 61499, der als periodischer Ereignisgenerator dient. Nach dem Starten feuert der Baustein in einem festgelegten Zeitintervall (`DT`) wiederholt ein Ausgangsereignis (`EO`). Er ist das grundlegende Werkzeug zur Erstellung von Taktgebern und zyklischen Abläufen.

![E_CYCLE](E_CYCLE.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **START**: Startet die periodische Generierung von `EO`-Ereignissen.
    - **Verbundene Daten**: `DT`
- **STOP**: Stoppt die Generierung von `EO`-Ereignissen.

### **Ereignis-Ausgänge**
- **EO (Event Output)**: Das zyklisch ausgelöste Ausgangsereignis.

### **Daten-Eingänge**
- **DT (Delay Time)**: Die Zeitdauer zwischen den einzelnen `EO`-Ereignissen (Datentyp: `TIME`).

## Funktionsweise
Die Funktionalität des `E_CYCLE` basiert intern auf einer Rückkopplungsschleife mit einem `E_DELAY`-Baustein.

1.  **Starten des Zyklus**:
    - Ein `START`-Ereignis am Eingang löst den internen Timer mit der am `DT`-Eingang angegebenen Zeitdauer aus.
    - Nach Ablauf dieser Zeit `DT` wird das erste `EO`-Ereignis am Ausgang ausgelöst.

2.  **Zyklischer Betrieb**:
    - Das ausgelöste `EO`-Ereignis wird intern sofort wieder auf den Starteingang des Timers zurückgekoppelt.
    - Dadurch wird der Timer umgehend neu gestartet, und nach einer weiteren Zeitspanne `DT` wird das nächste `EO`-Ereignis ausgelöst.
    - Dieser Prozess wiederholt sich kontinuierlich und erzeugt so eine periodische Folge von `EO`-Ereignissen im Abstand von `DT`.

3.  **Stoppen des Zyklus**:
    - Ein `STOP`-Ereignis am Eingang unterbricht die interne Rückkopplungsschleife.
    - Der Timer wird gestoppt und es werden keine weiteren `EO`-Ereignisse mehr generiert, bis ein erneutes `START`-Ereignis eintrifft.

## Technische Besonderheiten
- **Ereignisgenerator**: Der Baustein erzeugt eine Kette von Ereignissen, keinen kontinuierlichen Zustand (wie z.B. eine Rechteckwelle). Um ein Blinken zu realisieren, müsste das `EO`-Ereignis beispielsweise einen `E_T_FF` (Toggle Flip-Flop) ansteuern.
- **Präzise Zeitsteuerung**: Ermöglicht eine genaue Definition der Zykluszeit über den `TIME`-Datentyp.
- **Ereignisgesteuerte Architektur**: Die gesamte Steuerung (Start/Stopp) erfolgt rein ereignisbasiert.

## Anwendungsszenarien
- **Taktgeber**: Periodisches Anstoßen von anderen Funktionsblöcken in einem festen Takt (z.B. für Abtastungen oder Berechnungen).
- **Blinker/Warnleuchten**: Als Impulsgeber für einen nachgeschalteten Flip-Flop, um ein visuelles Signal zu erzeugen.
- **Watchdog**: Periodisches Senden eines "Lebenszeichens". Wenn das Signal ausbleibt, kann ein Fehler erkannt werden.
- **Testautomatisierung**: Generierung von periodischen Stimuli für zu testende Systeme.

## ⚖️ Vergleich mit ähnlichen Bausteinen

| Merkmal      | E_CYCLE                 | E_DELAY                      | E_PULSE (hypothetisch)       |
|--------------|-------------------------|------------------------------|------------------------------|
| Funktion     | Periodischer Taktgeber  | Einmalige Verzögerung        | Einmaliger Impuls fester Dauer|
| Wiederholung | Kontinuierlich          | Einmalig pro `START`-Ereignis| Einmalig pro `REQ`-Ereignis |
| Steuerung    | START/STOP              | START/STOP                   | REQ                          |






## 🛠️ Zugehörige Übungen

* [Uebung_007](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_007.md)
* [Uebung_007_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_007_AX.md)
* [Uebung_007a1](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_007a1.md)
* [Uebung_007a1_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_007a1_AX.md)
* [Uebung_007a2](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_007a2.md)
* [Uebung_007a2_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_007a2_AX.md)
* [Uebung_007a3](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_007a3.md)
* [Uebung_008](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_008.md)
* [Uebung_009](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_009.md)
* [Uebung_020c3](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020c3.md)
* [Uebung_020c3_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020c3_AX.md)
* [Uebung_020e2](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020e2.md)
* [Uebung_020e2_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020e2_AX.md)
* [Uebung_020f2](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_020f2.md)
* [Uebung_020f2_AX](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_AX/Uebungen_doc/Uebung_020f2_AX.md)
* [Uebung_084](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_084.md)
* [Uebung_152](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_152.md)
* [Uebung_153](../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_153.md)

## Fazit
Der `E_CYCLE`-Baustein ist ein essenzielles Werkzeug für alle Anwendungen, die eine periodische oder zyklische Logik erfordern. Er implementiert auf einfache Weise einen Taktgeber, dessen Frequenz über den `DT`-Parameter präzise eingestellt werden kann. Sein rein ereignisbasiertes Verhalten macht ihn zu einer effizienten und fundamentalen Komponente in der IEC 61499-Systemarchitektur.