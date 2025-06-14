# sequence_T_05_loop

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_T_05_loop` implementiert eine zyklische Sequenz mit fünf Zuständen, wobei die Übergänge zwischen den Zuständen zeitgesteuert erfolgen. Der Block ist besonders geeignet für Anwendungen, die eine wiederholbare Abfolge von Aktionen mit konfigurierbaren Zeitintervallen erfordern.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `START_S1`: Startet die Sequenz und führt zum ersten Zustand (State_01). Wird mit den Zeitparametern für alle Zustandsübergänge verknüpft.
- `RESET`: Setzt die Sequenz zurück in den Ausgangszustand (START), unabhängig vom aktuellen Zustand.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die Ausführung und liefert die aktuelle Zustandsnummer (`STATE_NR`).
- `EO_S1` bis `EO_S5`: Ereignisse, die beim Eintritt in die jeweiligen Zustände (State_01 bis State_05) ausgelöst werden. Jedes Ereignis ist mit einem entsprechenden Datenausgang (`DO_S1` bis `DO_S5`) verknüpft.

### **Daten-Eingänge**
- `DT_S1_S2` bis `DT_S5_S1`: Zeitintervalle (Typ `TIME`) für die Übergänge zwischen den Zuständen. Initial sind alle auf `sequence::NO_TIME` gesetzt.

### **Daten-Ausgänge**
- `STATE_NR` (Typ `SINT`): Gibt die aktuelle Zustandsnummer zurück (0 = START, 1 = State_01, ..., 5 = State_05).
- `DO_S1` bis `DO_S5` (Typ `BOOL`): Werden auf `TRUE` gesetzt, wenn der entsprechende Zustand aktiv ist.

### **Adapter**
- `timeOut` (Typ `ATimeOut`): Wird für die zeitgesteuerten Zustandsübergänge verwendet. Der Adapter startet und stoppt den Timer basierend auf den konfigurierten Zeitintervallen.

## Funktionsweise
1. **Start**: Durch das Ereignis `START_S1` wird die Sequenz initiiert, und der Block wechselt in den Zustand `State_01`.
2. **Zustandsübergänge**: Jeder Zustand (`State_01` bis `State_05`) aktiviert einen Ausgang (`DO_Sx`) und startet den Timer für den nächsten Übergang. Der Timer wird über den `timeOut`-Adapter gesteuert.
3. **Zyklus**: Nach `State_05` springt der Block zurück zu `State_01`, wodurch eine Endlosschleife entsteht.
4. **Reset**: Das Ereignis `RESET` unterbricht die Sequenz und setzt alle Ausgänge zurück. Der Block kehrt in den `START`-Zustand zurück.

## Technische Besonderheiten
- **Timer-Steuerung**: Die Zeitintervalle für die Übergänge werden dynamisch über die Daten-Eingänge (`DT_Sx_Sy`) konfiguriert.
- **Zustandsverwaltung**: Jeder Zustand hat einen eindeutigen Eintritts- (`_E`), Austritts- (`_X`) und Bestätigungsalgorithmus (`_C`), der die Ausgänge und den Timer aktualisiert.
- **Robuste Reset-Funktion**: Der `RESET`-Eingang kann jederzeit verwendet werden, um die Sequenz sicher zu unterbrechen.

## Zustandsübersicht
- **START**: Initialzustand.
- **State_01** bis **State_05**: Aktive Zustände mit jeweiligen Ausgängen.
- **RESET**: Zwischenzustand für den Reset-Vorgang.

## Anwendungsszenarien
- **Industrielle Steuerungen**: Für Maschinen mit zyklischen Arbeitsabläufen (z. B. Förderbänder, Verpackungsmaschinen).
- **Testautomation**: Zum Simulieren von zeitgesteuerten Sequenzen in Prüfständen.
- **Prozesssteuerung**: Für wiederholbare Prozessschritte mit definierten Zeitintervallen.

## Vergleich mit ähnlichen Bausteinen
- **Vorteile**: 
  - Flexibilität durch konfigurierbare Zeitintervalle.
  - Einfache Integration in bestehende Steuerungen dank standardisierter Schnittstellen.
- **Nachteile**: 
  - Keine direkte Unterstützung für ereignisgesteuerte Übergänge (nur zeitbasiert).

## Fazit
Der `sequence_T_05_loop`-Block ist ein robustes und flexibles Werkzeug für Anwendungen, die zyklische, zeitgesteuerte Abläufe erfordern. Durch die klare Schnittstellendefinition und die einfache Konfiguration eignet er sich besonders für industrielle Steuerungssysteme.