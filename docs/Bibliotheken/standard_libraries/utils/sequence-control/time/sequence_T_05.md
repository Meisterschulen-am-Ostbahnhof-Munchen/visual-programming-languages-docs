# sequence_T_05

![sequence_T_05](https://github.com/user-attachments/assets/1e4b22f8-222d-4db9-8aef-f3b21e326abe)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_T_05` implementiert eine zeitgesteuerte Sequenz mit 5 Ausgängen. Er ermöglicht den Übergang zwischen verschiedenen Zuständen basierend auf konfigurierbaren Zeitintervallen. Der Block wurde von HR Agrartechnik GmbH entwickelt und ist unter der EPL-2.0 Lizenz verfügbar.

* * * * * * * * * *
## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `START_S1`: Startet die Sequenz (Übergang von START zu State_01)
- `RESET`: Setzt die Sequenz zurück (Übergang von jedem Zustand zurück zu START)

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung der Ausführung (mit STATE_NR als Datenausgabe)
- `EO_S1` bis `EO_S5`: Ereignisausgänge für die jeweiligen Zustände (mit entsprechenden Datenausgaben)

### **Daten-Eingänge**
- `DT_S1_S2`: Zeitintervall für Übergang von State_01 zu State_02
- `DT_S2_S3`: Zeitintervall für Übergang von State_02 zu State_03
- `DT_S3_S4`: Zeitintervall für Übergang von State_03 zu State_04
- `DT_S4_S5`: Zeitintervall für Übergang von State_04 zu State_05
- `DT_S5_START`: Zeitintervall für Übergang von State_05 zurück zu START

### **Daten-Ausgänge**
- `STATE_NR`: Aktueller Zustand (0=START, 1=State_01, ..., 5=State_05)
- `DO_S1` bis `DO_S5`: Boolesche Ausgänge für die jeweiligen Zustände

### **Adapter**
- `timeOut`: ATimeOut-Adapter für die Zeitsteuerung

* * * * * * * * * *
## Funktionsweise
Der Funktionsblock durchläuft eine feste Sequenz von Zuständen (State_01 bis State_05), wobei die Übergänge zwischen den Zuständen durch die konfigurierten Zeitintervalle gesteuert werden. Jeder Zustand aktiviert seinen entsprechenden Ausgang (`DO_Sx`) und deaktiviert den Ausgang des vorherigen Zustands. Der `timeOut`-Adapter wird verwendet, um die Zeitintervalle zu verwalten.

* * * * * * * * * *
## Technische Besonderheiten
- Verwendet einen ATimeOut-Adapter für präzise Zeitsteuerung
- Implementiert saubere Zustandsübergänge mit Entry/Exit-Aktionen
- Bietet eine klare Zustandsrückmeldung über STATE_NR
- Unterstützt sofortigen Reset von jedem Zustand aus

* * * * * * * * * *
## Zustandsübersicht
1. **START** (Initialzustand)
2. **State_01**: Aktiviert DO_S1
3. **State_02**: Aktiviert DO_S2
4. **State_03**: Aktiviert DO_S3
5. **State_04**: Aktiviert DO_S4
6. **State_05**: Aktiviert DO_S5
7. **State_00**: Zwischenzustand nach State_05
8. **RESET**: Reset-Zustand

* * * * * * * * * *
## Anwendungsszenarien
- Steuerung von zeitlich getakteten Prozessen
- Automatisierte Ablaufsteuerungen
- Zustandsmaschinen mit zeitgesteuerten Übergängen
- Industrielle Steuerungssequenzen

* * * * * * * * * *
## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Timer-Blöcken bietet `sequence_T_05` eine vollständige Zustandsmaschine mit mehreren zeitgesteuerten Übergängen. Gegenüber generischen Zustandsmaschinen-Blöcken bietet er eine spezialisierte, vorkonfigurierte Lösung für Sequenzen mit genau 5 Zuständen.

* * * * * * * * * *
## Fazit
Der `sequence_T_05`-Block ist eine robuste Lösung für Anwendungen, die eine zeitgesteuerte Sequenz mit 5 klar definierten Zuständen erfordern. Seine klare Schnittstelle und die integrierte Zeitsteuerung machen ihn besonders geeignet für industrielle Steuerungsanwendungen, wo präzise und wiederholbare Abläufe benötigt werden.
