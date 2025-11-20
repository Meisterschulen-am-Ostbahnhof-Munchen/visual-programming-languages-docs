# FB_CTD_LINT

<img width="1399" height="282" alt="FB_CTD_LINT" src="https://github.com/user-attachments/assets/49df9c31-e52a-4ab3-9ab5-c17c58f2ee98" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FB_CTD_LINT` ist ein Abwärtszähler (Counter Down) für 64-Bit-Ganzzahlen (LINT). Er ermöglicht das Herunterzählen eines internen Zählwerts und bietet Funktionen zum Laden eines vordefinierten Werts. Der Block ist besonders für Anwendungen geeignet, die mit großen Zahlenbereichen arbeiten müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die normale Ausführung des Zählvorgangs. Verknüpft mit den Daten `CD`, `PV` und `LD`.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die Ausführung und liefert die aktuellen Werte von `Q` und `CV`.

### **Daten-Eingänge**
- `CD` (BOOL): Signalisiert, ob der Zähler heruntergezählt werden soll.
- `LD` (BOOL): Lädt den vordefinierten Wert (`PV`) in den Zähler.
- `PV` (LINT): Der vordefinierte Wert, der geladen wird, wenn `LD` aktiv ist.

### **Daten-Ausgänge**
- `Q` (BOOL): Signalisiert, ob der Zählerwert (`CV`) kleiner oder gleich Null ist.
- `CV` (LINT): Der aktuelle Zählerwert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock arbeitet nach folgender Logik:
1. Wenn `LD` aktiv ist, wird der vordefinierte Wert (`PV`) in den Zähler (`CV`) geladen.
2. Wenn `CD` aktiv ist und der Zählerwert (`CV`) nicht den minimalen 64-Bit-Wert erreicht hat, wird `CV` um 1 verringert.
3. Der Ausgang `Q` wird auf `TRUE` gesetzt, wenn `CV` kleiner oder gleich Null ist.

## Technische Besonderheiten
- Verwendet den Datentyp `LINT` (64-Bit-Ganzzahl), was einen sehr großen Zahlenbereich ermöglicht.
- Der minimale Wert für `LINT` wird berücksichtigt, um Überläufe zu vermeiden.

## Zustandsübersicht
- **Initialisierung**: Keine spezifische Initialisierung, `CV` startet mit einem undefinierten Wert.
- **Laden**: Wenn `LD` aktiv ist, wird `CV` mit `PV` überschrieben.
- **Zählen**: Bei aktivem `CD` wird `CV` dekrementiert, sofern nicht der Minimalwert erreicht ist.
- **Ausgabe**: `Q` wird basierend auf dem aktuellen `CV`-Wert gesetzt.

## Anwendungsszenarien
- Steuerung von Prozessen mit großen Zählbereichen, z.B. in der Produktionsautomatisierung.
- Überwachung von Zeitintervallen oder Ereigniszählungen in industriellen Steuerungen.

## Vergleich mit ähnlichen Bausteinen
- Ähnlich zu `FB_CTD_INT`, aber mit erweitertem Zahlenbereich (`LINT` statt `INT`).
- Bietet im Vergleich zu einfacheren Zählern mehr Flexibilität durch den großen Wertebereich und die Ladefunktion.

## Fazit
Der `FB_CTD_LINT` ist ein leistungsfähiger Abwärtszähler für Anwendungen, die große Zahlenbereiche erfordern. Seine einfache Handhabung und die robuste Implementierung machen ihn zu einer zuverlässigen Wahl für komplexe Steuerungsaufgaben.
