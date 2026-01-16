# RT_E_DELAY

* * * * * * * * * *

## Einleitung
Der RT_E_DELAY Funktionsblock verzögert ein Ereignis um eine definierte Zeit (DT) unter Berücksichtigung von Echtzeitanforderungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Initialisierung.
- **START**: Startet die Verzögerung.
- **STOP**: Bricht die Verzögerung ab.

### **Ereignis-Ausgänge**
- **INITO**: Initialisierung bestätigt.
- **EO**: Das verzögerte Ereignis.

### **Daten-Eingänge**
- **QI** (BOOL): Qualifizierer.
- **DT** (TIME): Verzögerungszeit.
- **Tmin** (TIME): Minimale Zeit.
- **Deadline** (TIME): Deadline.
- **WCET** (TIME): Worst Case Execution Time.

### **Daten-Ausgänge**
- **QO** (BOOL): Status.

## Metadaten
| Attribut | Wert |
| :--- | :--- |
| Copyright | (c) 2008, 2014 ACIN, Profactor GmbH |
| Lizenz | EPL-2.0 |
| Version | 3.0 (2025-04-14, Patrick Aigner) |
| 4diac-Paket | eclipse4diac::rtevents |
