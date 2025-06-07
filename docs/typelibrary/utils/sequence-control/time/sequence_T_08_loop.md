# sequence_T_08_loop

![sequence_T_08_loop](https://github.com/user-attachments/assets/dc9c08fc-e69c-4352-b596-be966b02f846)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `sequence_T_08_loop` implementiert eine zyklische Sequenz mit 8 Zuständen, wobei die Zustandsübergänge zeitgesteuert erfolgen. Der Block ist besonders geeignet für Anwendungen, bei denen eine wiederholbare Abfolge von Aktionen mit konfigurierbaren Zeitintervallen benötigt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `START_S1`: Startet die Sequenz von Zustand 1 (State_01). Wird mit allen Zeitparametern für die Zustandsübergänge verknüpft.
- `RESET`: Setzt die Sequenz zurück in den Ausgangszustand (START), unabhängig vom aktuellen Zustand.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung der Ausführung, gibt die aktuelle Zustandsnummer aus (`STATE_NR`).
- `EO_S1` bis `EO_S8`: Ereignisausgänge, die aktiv werden, wenn der entsprechende Zustand (State_01 bis State_08) betreten wird. Jeder Ausgang ist mit einem booleschen Datenausgang (`DO_S1` bis `DO_S8`) verknüpft.

### **Daten-Eingänge**
- `DT_S1_S2` bis `DT_S8_S1`: Zeitintervalle (Typ `TIME`) für die Übergänge zwischen den Zuständen. Die Initialwerte sind standardmäßig auf `sequence::NO_TIME` gesetzt.

### **Daten-Ausgänge**
- `STATE_NR` (SINT): Gibt die aktuelle Zustandsnummer aus (0 = START, 1 = State_01, ..., 8 = State_08).
- `DO_S1` bis `DO_S8` (BOOL): Werden auf `TRUE` gesetzt, wenn der entsprechende Zustand aktiv ist.

### **Adapter**
- `timeOut` (Typ `ATimeOut`): Wird verwendet, um die zeitgesteuerten Zustandsübergänge zu realisieren. Der Adapter startet einen Timer mit dem konfigurierten Zeitintervall und löst den Übergang beim Timeout aus.

## Funktionsweise
1. **Initialisierung**: Der Block startet im Zustand `xSTART`.
2. **Sequenzstart**: Durch das Ereignis `START_S1` wird der erste Zustand (`State_01`) aktiviert. Der zugehörige Ausgang `DO_S1` wird auf `TRUE` gesetzt, und der Timer für den Übergang zu `State_02` wird gestartet.
3. **Zustandsübergänge**: Jeder Zustand aktiviert den nächsten nach Ablauf des konfigurierten Zeitintervalls (z. B. `DT_S1_S2` für den Übergang von `State_01` zu `State_02`). Der vorherige Zustand wird deaktiviert (`DO_Sx` auf `FALSE`), und der neue Zustand wird aktiviert (`DO_Sy` auf `TRUE`).
4. **Zyklus**: Nach `State_08` springt die Sequenz zurück zu `State_01`, wodurch ein endloser Zyklus entsteht.
5. **Reset**: Das Ereignis `RESET` unterbricht die Sequenz und setzt alle Ausgänge zurück. Der Block kehrt in den `xSTART`-Zustand zurück.

## Technische Besonderheiten
- **Zeitgesteuerte Übergänge**: Die Dauer jedes Zustands wird durch die Eingangsvariablen `DT_Sx_Sy` definiert.
- **Zustandsbestätigung**: Der Ausgang `CNF` gibt die aktuelle Zustandsnummer aus, was für Debugging und Überwachung nützlich ist.
- **Adapter-basierte Timer**: Die Zeitsteuerung erfolgt über den `timeOut`-Adapter, der flexibel konfiguriert werden kann.

## Zustandsübersicht
- `xSTART`: Initialzustand.
- `sState_01` bis `sState_08`: Aktive Zustände der Sequenz.
- `sRESET`: Zwischenzustand für den Reset-Vorgang.

## Anwendungsszenarien
- **Steuerung von Maschinenabläufen**: Zyklische Prozesse mit festen Zeitintervallen (z. B. Förderbänder, Verpackungsmaschinen).
- **Lichtsteuerungen**: Sequenzielle Aktivierung von Beleuchtungselementen.
- **Testautomation**: Automatisierte Testsequenzen mit zeitlich definierten Schritten.

## Vergleich mit ähnlichen Bausteinen
- **Vorteile**: 
  - Flexibilität durch konfigurierbare Zeitintervalle.
  - Einfache Integration dank standardisierter Schnittstellen.
- **Nachteile**: 
  - Keine ereignisgesteuerten Übergänge (nur zeitbasiert).
  - Begrenzt auf 8 Zustände (für komplexere Sequenzen sind Erweiterungen notwendig).

## Fazit
Der `sequence_T_08_loop`-Block ist ein robustes und einfach zu konfigurierendes Werkzeug für zyklische Steuerungsaufgaben mit zeitgesteuerten Übergängen. Seine klare Struktur und die standardisierten Schnittstellen machen ihn besonders geeignet für industrielle Automatisierungsanwendungen.
