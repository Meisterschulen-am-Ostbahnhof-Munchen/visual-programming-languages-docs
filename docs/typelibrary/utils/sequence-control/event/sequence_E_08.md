# sequence_E_08

![sequence_E_08](https://github.com/user-attachments/assets/c5231931-8246-4c1c-b864-83c5d8e155b9)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **sequence_E_08** ist eine erweiterte Zustandsmaschine, die eine sequenzielle Abfolge von **acht Zuständen** steuert.
Diese erweiterte Version ermöglicht komplexere Steuerungsabläufe für anspruchsvolle industrielle Anwendungen, die mehr Prozessschritte erfordern.
Der Baustein folgt dem bewährten Prinzip der ereignisgesteuerten Zustandsübergänge und bietet zusätzliche Flexibilität durch die erweiterte Zustandsanzahl.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **START_S1**: Wechsel vom Startzustand (xSTART) zu State_01
- **S1_S2**: Wechsel von State_01 zu State_02
- **S2_S3**: Wechsel von State_02 zu State_03
- **S3_S4**: Wechsel von State_03 zu State_04
- **S4_S5**: Wechsel von State_04 zu State_05
- **S5_S6**: Wechsel von State_05 zu State_06
- **S6_S7**: Wechsel von State_06 zu State_07
- **S7_S8**: Wechsel von State_07 zu State_08
- **S8_START**: Wechsel von State_08 zurück zum Startzustand
- **RESET**: Setzt die Zustandsmaschine von jedem Zustand zurück zum Startzustand

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt die Ausführung eines Zustandswechsels (mit STATE_NR)
- **EO_S1**: Wird bei State_01 aktiviert (mit DO_S1)
- **EO_S2**: Wird bei State_02 aktiviert (mit DO_S2)
- **EO_S3**: Wird bei State_03 aktiviert (mit DO_S3)
- **EO_S4**: Wird bei State_04 aktiviert (mit DO_S4)
- **EO_S5**: Wird bei State_05 aktiviert (mit DO_S5)
- **EO_S6**: Wird bei State_06 aktiviert (mit DO_S6)
- **EO_S7**: Wird bei State_07 aktiviert (mit DO_S7)
- **EO_S8**: Wird bei State_08 aktiviert (mit DO_S8)

### **Daten-Ausgänge**

- **STATE_NR** (SINT): Aktuelle Zustandsnummer (0=Start, 1-8=State_01-08)
- **DO_S1** (BOOL): Ausgabe für State_01
- **DO_S2** (BOOL): Ausgabe für State_02
- **DO_S3** (BOOL): Ausgabe für State_03
- **DO_S4** (BOOL): Ausgabe für State_04
- **DO_S5** (BOOL): Ausgabe für State_05
- **DO_S6** (BOOL): Ausgabe für State_06
- **DO_S7** (BOOL): Ausgabe für State_07
- **DO_S8** (BOOL): Ausgabe für State_08

## Funktionsweise

1. **Initialisierung**: Start im Zustand xSTART
2. **Sequenzstart**: START_S1 aktiviert State_01 (DO_S1=TRUE)
3. **Sequenzablauf**: 
   - Jeder Zustandsübergang aktiviert die nächste Ausgabe und deaktiviert die vorherige
   - Beispiel: S2_S3 wechselt zu State_03 (DO_S3=TRUE, DO_S2=FALSE)
4. **Sequenzende**: S8_START kehrt zum Startzustand zurück (DO_S8=FALSE)
5. **Reset**: RESET setzt alle Ausgaben zurück und kehrt zu xSTART zurück

## Technische Besonderheiten

- **Erweiterte Zustandslogik**: 8 Zustände mit klaren Übergängen
- **Konsistente Schnittstelle**: Einheitliches Design wie kleinere Varianten
- **Robuste Reset-Funktion**: Deaktiviert alle Ausgaben sicher

## Zustandsübersicht

| Zustand | Aktivierte Ausgabe | Deaktivierte Ausgabe |
|---------|--------------------|----------------------|
| xSTART  | -                  | -                    |
| State_01| DO_S1              | -                    |
| State_02| DO_S2              | DO_S1                |
| State_03| DO_S3              | DO_S2                |
| State_04| DO_S4              | DO_S3                |
| State_05| DO_S5              | DO_S4                |
| State_06| DO_S6              | DO_S5                |
| State_07| DO_S7              | DO_S6                |
| State_08| DO_S8              | DO_S7                |
| sRESET  | -                  | Alle Ausgaben        |

## Anwendungsszenarien

- Komplexe Produktionslinien mit vielen Arbeitsschritten
- Mehrstufige Testsequenzen in der Qualitätssicherung
- Steuerung von Anlagen mit erweiterten Prozessabläufen

## Vergleich mit ähnlichen Bausteinen

**Vorteile**:
- Mehr Flexibilität durch zusätzliche Zustände
- Skalierbarkeit für komplexe Anwendungen

**Nachteile**:
- Höherer Speicherbedarf
- Komplexere Programmierung

## Fazit

Der **sequence_E_08**-Baustein erweitert die bewährte Funktionalität der kleineren Varianten um zusätzliche Zustände für anspruchsvolle Steuerungsaufgaben.
Durch das konsistente Design bleibt er einfach zu verwenden, während er gleichzeitig mehr Flexibilität für komplexe Automatisierungsprozesse bietet.
