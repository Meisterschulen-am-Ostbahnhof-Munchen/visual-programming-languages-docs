# VALUES2ARRAY_2_LREAL

![VALUES2ARRAY_2_LREAL](https://github.com/user-attachments/assets/a41a0f4c-d21e-435f-a700-9b89c4fb623c)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `VALUES2ARRAY_2_LREAL` dient dazu, zwei einzelne LREAL-Werte in ein Array mit zwei Elementen zusammenzuführen. Dieser Block ist besonders nützlich, wenn mehrere Einzelwerte in einer strukturierten Form weiterverarbeitet werden sollen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage, die die Verarbeitung der Eingabewerte auslöst. Wird mit den Daten-Eingängen `IN_1` und `IN_2` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der abgeschlossenen Verarbeitung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN_1**: Erster Eingabewert (LREAL).
- **IN_2**: Zweiter Eingabewert (LREAL).

### **Daten-Ausgänge**
- **OUT**: Ausgabearray (LREAL) mit zwei Elementen. Die Elemente entsprechen den Eingabewerten `IN_1` (Index 0) und `IN_2` (Index 1).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Bei Empfang des Ereignisses `REQ` werden die Werte von `IN_1` und `IN_2` in das Array `OUT` kopiert.
2. `OUT[0]` erhält den Wert von `IN_1`.
3. `OUT[1]` erhält den Wert von `IN_2`.
4. Das Ereignis `CNF` signalisiert die erfolgreiche Verarbeitung.

## Technische Besonderheiten
- Der Funktionsblock unterstützt den Datentyp `LREAL` (64-Bit Gleitkommazahl).
- Das Ausgabearray hat eine feste Größe von 2 Elementen.

## Zustandsübersicht
1. **Initialisierung**: Der Block wartet auf das Ereignis `REQ`.
2. **Verarbeitung**: Bei `REQ` werden die Eingabewerte verarbeitet und das Array erstellt.
3. **Bestätigung**: Das Ereignis `CNF` wird ausgelöst.

## Anwendungsszenarien
- Zusammenführen von Messwerten für eine weitere Verarbeitung.
- Vorbereitung von Daten für Array-basierte Algorithmen.
- Integration in Steuerungssysteme, die Array-Daten erfordern.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Array-Bausteinen ist `VALUES2ARRAY_2_LREAL` speziell für zwei LREAL-Werte optimiert.
- Ähnliche Blöcke wie `VALUES2ARRAY` können mehr Eingabewerte unterstützen, sind aber weniger spezifisch.

## Fazit
Der `VALUES2ARRAY_2_LREAL` Funktionsblock ist eine effiziente Lösung für die Konvertierung von zwei LREAL-Werten in ein Array. Seine Einfachheit und Spezialisierung machen ihn ideal für spezifische Anwendungsfälle.
