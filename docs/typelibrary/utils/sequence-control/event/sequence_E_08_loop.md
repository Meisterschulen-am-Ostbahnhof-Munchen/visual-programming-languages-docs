# sequence_E_08_loop

![sequence_E_08_loop](https://github.com/user-attachments/assets/b7d13e1f-e629-4cbb-9d0d-3e639e9e20d2)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **sequence_E_08_loop** ist eine zyklische Erweiterung der sequence_E_08 Zustandsmaschine, die eine endlose Wiederholung einer **8-stufigen Zustandssequenz** ermöglicht.
Durch den direkten Übergang vom letzten Zustand (State_08) zurück zum ersten Zustand (State_01) eignet sich dieser Baustein ideal für kontinuierliche Prozesse in der industriellen Automatisierung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis   | Beschreibung                          |
|------------|--------------------------------------|
| START_S1   | Startet Sequenz (xSTART → State_01)  |
| S1_S2      | State_01 → State_02                  |
| S2_S3      | State_02 → State_03                  |
| S3_S4      | State_03 → State_04                  |
| S4_S5      | State_04 → State_05                  |
| S5_S6      | State_05 → State_06                  |
| S6_S7      | State_06 → State_07                  |
| S7_S8      | State_07 → State_08                  |
| S8_S1      | State_08 → State_01 (Zyklus)         |
| RESET      | Sofortiger Reset zu xSTART           |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung                     | Variable   |
|----------|---------------------------------|------------|
| CNF      | Zustandswechselbestätigung      | STATE_NR   |
| EO_S1    | State_01 Aktivierung            | DO_S1      |
| EO_S2    | State_02 Aktivierung            | DO_S2      |
| EO_S3    | State_03 Aktivierung            | DO_S3      |
| EO_S4    | State_04 Aktivierung            | DO_S4      |
| EO_S5    | State_05 Aktivierung            | DO_S5      |
| EO_S6    | State_06 Aktivierung            | DO_S6      |
| EO_S7    | State_07 Aktivierung            | DO_S7      |
| EO_S8    | State_08 Aktivierung            | DO_S8      |

### **Daten-Ausgänge**

| Variable   | Typ   | Beschreibung                |
|------------|-------|----------------------------|
| STATE_NR   | SINT  | Aktueller Zustand (0-8)     |
| DO_S1      | BOOL  | Ausgabe State_01            |
| DO_S2      | BOOL  | Ausgabe State_02            |
| DO_S3      | BOOL  | Ausgabe State_03            |
| DO_S4      | BOOL  | Ausgabe State_04            |
| DO_S5      | BOOL  | Ausgabe State_05            |
| DO_S6      | BOOL  | Ausgabe State_06            |
| DO_S7      | BOOL  | Ausgabe State_07            |
| DO_S8      | BOOL  | Ausgabe State_08            |

## Funktionsweise

1. **Initialisierung**: Start im Zustand xSTART
2. **Sequenzstart**: 
   - START_S1 aktiviert State_01 (DO_S1=TRUE)
3. **Zustandsübergänge**:
   - Jeder Sx_Sy-Event führt zum nächsten Zustand
   - Aktiviert neue Ausgabe, deaktiviert vorherige
4. **Zyklusbildung**:
   - S8_S1 springt direkt zurück zu State_01
5. **Reset**:
   - RESET deaktiviert alle Ausgaben
   - Setzt STATE_NR auf 0
   - Kehrt zu xSTART zurück

## Technische Besonderheiten

- **Zyklische Logik**: S8_S1 ersetzt S8_START für endlosen Betrieb
- **Konsistente Architektur**: Gleiches Design wie lineare Variante
- **Vollständige Reset-Funktion**: Deaktiviert alle 8 Ausgaben sicher

## Zustandsübersicht

| Zustand    | Aktivierung | Deaktivierung       |
|------------|-------------|---------------------|
| xSTART     | -           | -                   |
| State_01   | DO_S1       | - (oder DO_S8)      |
| State_02   | DO_S2       | DO_S1               |
| State_03   | DO_S3       | DO_S2               |
| State_04   | DO_S4       | DO_S3               |
| State_05   | DO_S5       | DO_S4               |
| State_06   | DO_S6       | DO_S5               |
| State_07   | DO_S7       | DO_S6               |
| State_08   | DO_S8       | DO_S7               |
| sRESET     | -           | Alle DO_Sx          |

## Anwendungsszenarien

- Kontinuierliche Fertigungslinien
- Zyklische Testabläufe
- Periodische Wartungsprozesse
- Rundumsteuerungen für rotierende Maschinen

## Vergleich mit sequence_E_08

| Feature          | sequence_E_08 | sequence_E_08_loop |
|------------------|---------------|--------------------|
| Zyklusende       | Zu xSTART     | Zu State_01        |
| Reset-Logik      | Identisch     | Identisch          |
| Betriebsart      | Einmalig      | Dauerhaft          |

**Vorteile**:
- Kein manueller Neustart nötig
- Ideal für Dauerbetrieb

**Nachteile**:
- Nicht für einmalige Abläufe geeignet

## Fazit

Der **sequence_E_08_loop**-Baustein erweitert die 8-stufige Sequenzsteuerung um zyklische Funktionalität für kontinuierliche Prozesse.
Durch die bewährte Architektur bleibt er einfach zu handhaben, während er gleichzeitig komplexe, wiederkehrende Automatisierungsaufgaben zuverlässig bewältigt.
