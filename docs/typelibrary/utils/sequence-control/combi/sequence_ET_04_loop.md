# sequence_ET_04_loop

![sequence_ET_04_loop](https://github.com/user-attachments/assets/713dab33-e014-44d8-b72c-40e3a7b10b45)

* * * * * * * * * *

## Einleitung
Der **sequence_ET_04_loop** ist ein zyklischer IEC 61499-Funktionsbaustein mit 4 Zuständen, der automatisch von State_04 zurück zu State_01 springt.
Entwickelt unter EPL-2.0 Lizenz, ermöglicht er endlose Arbeitszyklen in Automatisierungsprozessen mit kombinierter Ereignis- und Zeitsteuerung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `START_S1`: Initiiert den Zyklus (START → State_01) mit Zeitparametern
- `S1_S2`, `S2_S3`, `S3_S4`: Manuelle Zustandsübergänge
- `S4_S1`: Manueller Neustart des Zyklus (State_04 → State_01)
- `RESET`: Sofortiger Abbruch zum Startzustand

### **Ereignis-Ausgänge**
- `CNF`: Zustandswechselbestätigung (mit STATE_NR)
- `EO_S1`-`EO_S4`: Zustandsaktivierungs-Signale (mit DO_Sx)

### **Daten-Eingänge**
- `DT_S1_S2`-`DT_S4_S1` (TIME):
  Zeitintervalle für automatische Übergänge (NO_TIME = deaktiviert)

### **Daten-Ausgänge**
- `STATE_NR` (SINT): Aktueller Zustand (0=START, 1-4=State_01-04)
- `DO_S1`-`DO_S4` (BOOL): Aktive Zustandsausgänge

### **Adapter**
- `timeOut` (ATimeOut): Realisiert zeitgesteuerte Übergänge

## Funktionsweise

1. **Initialisierung**:
   - Startzustand: `xSTART` (STATE_NR=0)
   - Alle Ausgänge (DO_Sx) deaktiviert

2. **Zustandslogik**:
   - Jeder Zustand:
     1. Deaktiviert vorherige DO_Sx (Exit-Aktion)
     2. Aktiviert eigene DO_Sx (Entry-Aktion)
     3. Startet TimeOut-Adapter mit konfigurierbarem DT
   - Übergänge erfolgen durch:
     - Explizite Events (z.B. `S2_S3`) **oder**
     - TimeOut (wenn DT ≠ NO_TIME)

3. **Zyklusverhalten**:
   - State_04 → State_01 (automatisch via `DT_S4_S1` oder `S4_S1`-Event)
   - Endloswiederholung bis RESET

## Technische Besonderheiten

✔ **Zyklischer Modus**: Automatischer Neustart nach State_04  
✔ **Hybride Triggerung**: Kombination aus Events und Timings  
✔ **Atomare Zustandswechsel**: Garantiert konsistente DO_Sx-Ausgänge  
✔ **Deterministisch**: Zeitgesteuerte Übergänge mit Nanosekunden-Präzision  

## Zustandsübersicht

| Zustand | STATE_NR | Aktiver Ausgang | TimeOut-Parameter |
|---------|----------|-----------------|-------------------|
| START   | 0        | -               | -                 |
| State_01| 1        | DO_S1           | DT_S1_S2          |
| State_02| 2        | DO_S2           | DT_S2_S3          |
| State_03| 3        | DO_S3           | DT_S3_S4          |
| State_04| 4        | DO_S4           | DT_S4_S1          |

## Anwendungsszenarien

- **Maschinenzyklen**: Kontinuierliche Bearbeitungsprozesse
- **Prüfautomation**: Wiederholende Testsequenzen
- **Batch-Betrieb**: Materialzufuhr in Fertigungslinien
- **Anlagensteuerung**: Zyklische Wartungsroutinen

## Vergleich mit ähnlichen Bausteinen

| Feature          | sequence_ET_04_loop | sequence_ET_04 | SFC-Cycle       |
|------------------|---------------------|----------------|-----------------|
| Zyklusende      | State_01 (Loop)     | START          | Beliebig        |
| Triggerarten    | Event + Time        | Event + Time   | Nur Event       |
| Reset-Verhalten | Vollständig         | Vollständig    | Teilweise       |
| Echtzeitfähig   | ✔                   | ✔              | ✖               |

## Fazit

Der sequence_ET_04_loop-Baustein ist die optimale Lösung für zyklische Prozesse:

- **Effizient**: Automatischer Neustart ohne zusätzliche Steuerlogik
- **Flexibel**: Individuelle Timing pro Zustand
- **Robust**: Explizite Reset-Funktion für Notfälle

Ideale Einsatzgebiete:
- Kontinuierliche Fertigungsprozesse
- Zyklische Diagnoseroutinen
- Automatisierte Testsysteme

*Hinweis:* Für einmalige Abläufe sollte `sequence_ET_04` verwendet werden.
