# sequence_ET_04_04

<img width="1365" height="423" alt="image" src="https://github.com/user-attachments/assets/1b79f526-dd1e-44ec-995c-0dc1aa53c95a" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_ET_04_04` implementiert eine Sequenzsteuerung mit 8 Ausgangszuständen. Der Übergang zwischen den Zuständen kann entweder durch ein Ereignis (EVENT) oder zeitgesteuert (TIME) erfolgen. Der Block bietet umfassende Konfigurationsmöglichkeiten für zeitgesteuerte Übergänge und unterstützt einen Reset-Mechanismus von jedem Zustand zurück zum Startzustand.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `EI1`: Allgemeines Eingangsereignis
- `START_S1`: Wechsel vom START-Zustand zu State_01
- `S4_S5`: Wechsel von State_04 zu State_05
- `EI_RESET`: Reset von jedem Zustand zurück zum START-Zustand

### **Ereignis-Ausgänge**
- `CNF`: Ausführungsbestätigung mit STATE_NR
- `EO_S1` bis `EO_S8`: Zustandsereignisse mit entsprechenden DO_Sx Werten
- `EO_RESET`: Reset-Bestätigung

### **Daten-Eingänge**
- `DT_S1_S2` bis `DT_S8_START`: Zeitwerte für zeitgesteuerte Zustandsübergänge (TIME-Typ, NO_TIME zum Deaktivieren)

### **Daten-Ausgänge**
- `STATE_NR`: Aktueller Zustand (0=START, 1=State_01, etc.)
- `DO_S1` bis `DO_S8`: Zustandsausgänge (BOOL)

### **Adapter**
- `timeOut`: ATimeOut-Adapter für Zeitsteuerung

## Funktionsweise
Der FB implementiert eine Zustandsmaschine mit folgenden Hauptzuständen:
- START (Initialzustand)
- State_01 bis State_08 (aktive Zustände)
- RESET (Reset-Zustand)

Zustandsübergänge können erfolgen durch:
1. Zeitsteuerung (wenn entsprechende DT_xx Werte ≠ NO_TIME)
2. Explizite Ereignisse (START_S1, S4_S5)
3. Reset-Ereignis (EI_RESET)

Bei jedem Zustandswechsel werden entsprechende Ausgangsvariablen gesetzt und Bestätigungsereignisse ausgelöst.

## Technische Besonderheiten
- Zeitgesteuerte Übergänge sind individuell konfigurierbar/deaktivierbar
- Zustandsnummer wird kontinuierlich ausgegeben
- Parallele Ausführung von Entry/Exit-Aktionen und Bestätigungen
- Umfassender Reset-Mechanismus

## Zustandsübersicht
1. **START**: Initialzustand
2. **State_01**: Erster aktiver Zustand (DO_S1=TRUE)
3. **State_02** bis **State_08**: Folgezustände mit entsprechenden Ausgängen
4. **RESET**: Zwischenzustand für Reset-Operation

## Anwendungsszenarien
- Steuerung von sequentiellen Prozessen
- Zeitgesteuerte Ablaufsteuerungen
- Maschinensteuerungen mit definierten Zustandsfolgen
- Prozesse mit manueller Reset-Möglichkeit

## Vergleich mit ähnlichen Bausteinen
- Bietet mehr Zustände als einfache Sequenzer
- Flexiblere Zeitsteuerung durch individuelle Zeiten pro Übergang
- Umfassendere Reset-Logik als Basis-Varianten
- Explizite Zustandsnummerierung zur einfachen Diagnose

## Fazit
Der `sequence_ET_04_04` Funktionsblock ist eine leistungsfähige Lösung für Anwendungen, die eine sequentielle Steuerung mit bis zu 8 Zuständen erfordern. Die Kombination aus ereignis- und zeitgesteuerten Übergängen sowie die umfassende Reset-Funktionalität machen ihn besonders flexibel einsetzbar. Die klare Zustandsnummerierung und konfigurierbaren Zeitparameter unterstützen die Anpassung an verschiedene Anwendungsfälle.
