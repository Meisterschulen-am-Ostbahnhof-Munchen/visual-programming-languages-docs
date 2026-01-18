# RT_E_CYCLE

```{index} single: RT_E_CYCLE
```

* * * * * * * * * *

## 📺 Video

* [E_CYCLE aus der IEC 61499 (Übung 84)](https://www.youtube.com/watch?v=PWJHijOPpFc)

## Einleitung
Der RT_E_CYCLE Funktionsblock implementiert eine periodische Ereigniserzeugung (Zyklus) mit Echtzeiteigenschaften. Er ermöglicht das Definieren von Deadlines und Ausführungszeiten (WCET).

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **START**: Startet den Zyklus.
- **STOP**: Stoppt den Zyklus.

### **Ereignis-Ausgänge**
- **EO**: Das zyklisch erzeugte Ereignis.

### **Daten-Eingänge**
- **DT** (TIME): Zykluszeit (Delay Time).
- **Deadline** (TIME): Deadline für die Ereignisverarbeitung.
- **WCET** (TIME): Worst Case Execution Time.

### **Daten-Ausgänge**
- **QO** (BOOL): Statusanzeige.

## Funktionsweise
Nach dem `START`-Ereignis wird das `EO`-Ereignis periodisch mit der Zeit `DT` ausgelöst. Die Parameter `Deadline` und `WCET` dienen der Echtzeitplanung und -überwachung.

## Metadaten
| Attribut | Wert |
| :--- | :--- |
| Copyright | (c) 2008 ACIN |
| Lizenz | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner) |
| 4diac-Paket | eclipse4diac::rtevents |