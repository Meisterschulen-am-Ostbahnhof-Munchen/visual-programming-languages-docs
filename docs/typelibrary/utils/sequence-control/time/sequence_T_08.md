# sequence_T_08

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_T_08` implementiert eine Sequenzsteuerung mit 8 Zuständen, wobei die Zustandsübergänge zeitgesteuert erfolgen. Der Block ist besonders geeignet für Anwendungen, bei denen eine festgelegte Abfolge von Aktionen mit definierten Zeitintervallen zwischen den Zustandswechseln benötigt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `START_S1`: Startet die Sequenz vom Anfangszustand (START) zu State_01. Übernimmt dabei alle Zeitparameter für die Zustandsübergänge.
- `RESET`: Setzt die Sequenz von jedem beliebigen Zustand zurück zum Anfangszustand (START).

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die Ausführung eines Zustandswechsels und liefert die aktuelle Zustandsnummer.
- `EO_S1` bis `EO_S8`: Ereignisausgänge, die bei Aktivierung des jeweiligen Zustands (State_01 bis State_08) ausgelöst werden.

### **Daten-Eingänge**
- `DT_S1_S2` bis `DT_S8_START`: TIME-Werte, die die Dauer der Zustandsübergänge definieren. Initial sind alle mit `sequence::NO_TIME` voreingestellt.

### **Daten-Ausgänge**
- `STATE_NR`: Aktuelle Zustandsnummer (0 = START, 1 = State_01, ..., 8 = State_08).
- `DO_S1` bis `DO_S8`: BOOL-Ausgänge, die im jeweiligen Zustand aktiv sind (TRUE).

### **Adapter**
- `timeOut`: ATimeOut-Adapter zur Realisierung der zeitgesteuerten Zustandsübergänge.

## Funktionsweise
Der Funktionsblock durchläuft die Zustände State_01 bis State_08 in sequenzieller Reihenfolge. Jeder Zustandswechsel erfolgt nach Ablauf der jeweils konfigurierten Zeit (`DT_Sx_Sy`). Beim Erreichen von State_08 kehrt der Block automatisch zum START-Zustand zurück. Ein `RESET`-Ereignis unterbricht die Sequenz und setzt sie sofort zurück.

## Technische Besonderheiten
- Zeitgesteuerte Übergänge mit konfigurierbaren Intervallen
- Explizite Entry/Exit-Aktionen für jeden Zustand
- Zustandsnummer als SINT-Wert verfügbar
- Separate BOOL-Ausgänge für jeden Zustand

## Zustandsübersicht
1. **START** (Initialzustand)
2. **State_01** bis **State_08** (sequenzielle Zustände)
3. **RESET** (Zwischenzustand für Reset-Operation)

## Anwendungsszenarien
- Steuerung von Produktionsprozessen mit festen Zeitabläufen
- Automatisierte Testsequenzen
- Schrittketten in Maschinensteuerungen
- Zeitgesteuerte Ablaufsteuerungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Timer-Blöcken bietet `sequence_T_08` eine vollständige Zustandsmaschine mit konfigurierbaren Übergangszeiten und expliziten Ein-/Ausgangsaktionen für jeden Zustand. Gegenüber allgemeinen Sequenzern hat dieser Block den Vorteil der festen 8-Zustands-Struktur mit integrierter Zeitsteuerung.

## Fazit
Der `sequence_T_08`-Funktionsblock ist eine leistungsfähige Lösung für Anwendungen, die eine zeitgesteuerte Sequenz mit genau 8 Zuständen erfordern. Die klare Struktur und die detaillierte Zustandsrückmeldung machen ihn besonders geeignet für komplexere Steuerungsaufgaben mit festen Zeitabläufen.