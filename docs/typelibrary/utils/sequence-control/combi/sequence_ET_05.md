# sequence_ET_05

![sequence_ET_05](https://github.com/user-attachments/assets/fd43d0f3-84da-4119-bc52-80a4462e3085)

* * * * * * * * * *

## Einleitung
Der **sequence_ET_05** ist ein erweiterter IEC 61499-Funktionsbaustein mit 5 Arbeitszuständen und kombinierter Ereignis-/Zeitsteuerung.
Entwickelt unter EPL-2.0 Lizenz, ermöglicht er komplexe Ablaufsteuerungen mit vollständigem Zustandsrücklauf (State_05 → START).

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Eingang | Triggerziel | Verknüpfte Daten |
|---------|-------------|------------------|
| `START_S1` | START → State_01 | DT_S1_S2 bis DT_S5_START |
| `S1_S2` | State_01 → State_02 | - |
| `S2_S3` | State_02 → State_03 | - |
| `S3_S4` | State_03 → State_04 | - |
| `S4_S5` | State_04 → State_05 | - |
| `S5_START` | State_05 → START | - |
| `RESET` | Any → START | - |

### **Ereignis-Ausgänge**
| Ausgang | Auslöser | Daten |
|---------|----------|-------|
| `CNF` | Zustandswechsel | STATE_NR |
| `EO_S1`-`EO_S5` | Zustandseintritt | DO_Sx |

### **Daten-Eingänge**
- `DT_S1_S2`-`DT_S5_START` (TIME):
  - Zeitverzögerungen (1ms-49d)
  - `NO_TIME` deaktiviert Zeitsteuerung

### **Daten-Ausgänge**
| Variable | Typ | Beschreibung |
|----------|-----|--------------|
| `STATE_NR` | SINT | 0=START, 1-5=State_01-05 |
| `DO_S1`-`DO_S5` | BOOL | Zustandsaktivierung |

### **Adapter**
- `timeOut` (ATimeOut): Steuert zeitgesteuerte Übergänge

## Funktionsweise

1. **Initialisierungsphase**:
   - Startet im Zustand `xSTART` (STATE_NR=0)
   - Alle DO_Sx-Ausgänge deaktiviert

2. **Zustandsmaschine**:
   ```plaintext
   START → State_01 → State_02 → State_03 → State_04 → State_05 → START
   ```
   - Pro Zustand:
     1. STOP des vorherigen Timers
     2. Exit-Aktion (DO_Sx-1 = FALSE)
     3. Entry-Aktion (DO_Sx = TRUE)
     4. START des neuen Timers

3. **Übergangsoptionen**:
   - **Ereignisgesteuert**: Direkter Trigger via Sx_Sy
   - **Zeitgesteuert**: Automatisch nach DT_Sx_Sy

## Technische Besonderheiten

✔ **Erweiterte Zustandslogik**: 5 Arbeitszustände + START  
✔ **Bidirektionale Steuerung**: Vorwärts/Rückwärts durch Events  
✔ **Fehlertoleranz**: Vollständiger Reset aus jedem Zustand  
✔ **Echtzeitfähig**: Präzise Zeitsteuerung bis 1ms  

## Zustandsmatrix

| Zustand | STATE_NR | Aktiver Ausgang | TimeOut-Parameter | Verweildauer |
|---------|----------|-----------------|-------------------|--------------|
| START   | 0        | -               | -                 | -            |
| State_01| 1        | DO_S1           | DT_S1_S2          | T#1ms-T#49d  |
| State_02| 2        | DO_S2           | DT_S2_S3          | T#1ms-T#49d  |
| State_03| 3        | DO_S3           | DT_S3_S4          | T#1ms-T#49d  |
| State_04| 4        | DO_S4           | DT_S4_S5          | T#1ms-T#49d  |
| State_05| 5        | DO_S5           | DT_S5_START       | T#1ms-T#49d  |

## Anwendungsszenarien

- **Mehrstufige Produktionsprozesse**: 
  - Materialzufuhr → Bearbeitung → Qualitätskontrolle → Verpackung → Auslieferung
- **Testsequenzen**:
  - Systemcheck → Kalibrierung → Funktionstest → Protokollierung → Reset
- **Sicherheitskritische Abläufe**:
  - Notstopp-Prozeduren mit bestätigten Zwischenzuständen

## Vergleich mit ähnlichen Bausteinen

| Parameter        | sequence_ET_05 | sequence_ET_04 | SFC-Editor |
|------------------|----------------|----------------|------------|
| Max. Zustände    | 5              | 4              | Unbegrenzt |
| Zeitsteuerung    | Pro Schritt    | Pro Schritt    | Global     |
| Reset-Tiefe      | Vollständig    | Vollständig    | Teilweise  |
| Echtzeitgarantie | ✔              | ✔              | ✖          |

## Fazit

Der sequence_ET_05-Baustein bietet erweiterte Möglichkeiten für:

1. **Komplexe Prozessketten**: Mehrstufige Abläufe mit klarer Zustandstrennung  
2. **Flexible Steuerung**: Kombinierte Event-/Time-Trigger pro Schritt  
3. **Industrietauglichkeit**: Robuste Reset-Funktion und Echtzeitverhalten  

*Empfohlener Einsatz*:  
- Mehrstufige Maschinensteuerungen  
- Validierte Produktionsprozesse  
- Sicherheitsrelevante Zustandsautomaten  

*Hinweis*: Für einfachere Prozesse kann sequence_ET_04 ausreichend sein.
