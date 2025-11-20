# sequence_ET_04

![sequence_ET_04](https://github.com/user-attachments/assets/45499965-e192-4189-9058-341873ef42a9)

* * * * * * * * * *

## Einleitung
Der **sequence_ET_04** ist ein IEC 61499-konformer Funktionsbaustein zur Steuerung einer 4-stufigen Sequenz mit ereignis- oder zeitgesteuerten Zustandsübergängen.
Entwickelt unter EPL-2.0 Lizenz, ermöglicht er flexible Ablaufsteuerungen in Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `START_S1`: Startet Sequenz (Übergang START → State_01) mit Zeitparametern
- `S1_S2`, `S2_S3`, `S3_S4`: Manuelle Zustandsübergänge
- `S4_START`: Zyklusende (State_04 → START)
- `RESET`: Sofortiger Reset aller Zustände

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung bei Zustandswechsel (mit STATE_NR)
- `EO_S1`-`EO_S4`: Zustandsaktivierungs-Ereignisse (mit zugehörigen DO_Sx)

### **Daten-Eingänge**
- `DT_S1_S2`-`DT_S4_START` (TIME): 
  Zeitverzögerungen für automatische Übergänge (NO_TIME deaktiviert Timing)

### **Daten-Ausgänge**
- `STATE_NR` (SINT): Aktueller Zustand (0=START, 1-4=State_01-04)
- `DO_S1`-`DO_S4` (BOOL): Zustandsaktivierungs-Signale

### **Adapter**
- `timeOut` (ATimeOut): Steuert zeitgesteuerte Übergänge

## Funktionsweise

1. **Initialisierung**:
   - Startzustand: `xSTART` (STATE_NR=0)
   - Alle DO_Sx = FALSE

2. **Zustandsautomaten-Logik**:
   - Jeder Zustand aktiviert:
     - Zustandsspezifisches DO_Sx (Eintrittsaktion)
     - TimeOut-Adapter mit konfigurierbarem DT
     - CNF-Bestätigung
   - Übergänge via:
     - Ereignisse (z.B. `S1_S2`) **oder**
     - TimeOut (bei DT ≠ NO_TIME)

3. **Reset-Verhalten**:
   - Deaktiviert alle DO_Sx
   - Springt zu `sState_00`

## Technische Besonderheiten

✔ **Dualer Trigger**: Ereignis- **und** zeitgesteuerte Übergänge  
✔ **Deterministisch**: Garantierte Zustandsreihenfolge  
✔ **Flexible Timing**: Pro Übergang individuell konfigurierbar  
✔ **Adapter-basiert**: Externe TimeOut-Logik via ATimeOut  

## Zustandsübersicht

| Zustand | STATE_NR | DO_Sx | TimeOut-Aktion |
|---------|----------|-------|----------------|
| START   | 0        | -     | -              |
| State_01| 1        | DO_S1 | DT_S1_S2       |
| State_02| 2        | DO_S2 | DT_S2_S3       |
| State_03| 3        | DO_S3 | DT_S3_S4       |
| State_04| 4        | DO_S4 | DT_S4_START    |

## Anwendungsszenarien

- **Maschinenzyklen**: Schrittkette für Bearbeitungsprozesse
- **Testautomation**: Zeitgesteuerte Prüfsequenzen
- **Sicherheitssteuerungen**: Guaranteed-State-Übergänge
- **Batch-Prozesse**: Rezeptabhängige Ablaufsteuerung

## Vergleich mit ähnlichen Bausteinen

| Feature          | sequence_ET_04 | SFC-Implementierung | Timer-Kaskade |
|------------------|----------------|---------------------|---------------|
| Zustandsanzahl   | 4 (+START)     | Beliebig            | Begrenzt      |
| Trigger-Typen    | Event + Time   | Nur Event           | Nur Time      |
| Konfiguration    | Pro Übergang   | Global              | Manuell       |
| Reset-Optionen   | Vollständig    | Teilweise           | Begrenzt      |

## Fazit

Der sequence_ET_04-Baustein bietet eine optimierte Lösung für industrielle Sequenzsteuerungen:

- **Robust**: Kombinierte Event-/Time-Trigger vermeiden Hänger
- **Transparent**: Explizite Zustandsrückmeldung via STATE_NR
- **Wartungsfreundlich**: Zentrale Zeitkonfiguration pro Schritt

Idealer Einsatz bei:
- Zyklischen Prozessen mit variablen Timing-Anforderungen
- Sicherheitskritischen Zustandsmaschinen
- Schnittstellen zu übergeordneten Steuerungen

*Hinweis:* Für komplexere Zustandsautomaten empfiehlt sich eine SFC-Implementierung.
