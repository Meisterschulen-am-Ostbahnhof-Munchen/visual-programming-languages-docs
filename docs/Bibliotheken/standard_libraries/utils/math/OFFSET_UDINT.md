# OFFSET_UDINT

![OFFSET_UDINT](https://github.com/user-attachments/assets/2ed8f619-315d-455d-add5-b720dd6dc5ec)

* * * * * * * * * *
## Einleitung
Der OFFSET_UDINT Funktionsblock ist ein einfacher Baustein zur Berechnung eines Offsets für UDINT-Werte (32-Bit unsigned integer). Bei der ersten Ausführung mit einem Eingangswert >0 speichert er diesen Wert als Basis (FIRST) und berechnet fortlaufend die Differenz zwischen aktuellen Eingangswerten und diesem Basiswert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung des Funktionsblocks (Normal Execution Request). Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert die Beendigung der Berechnung (Execution Confirmation). Wird mit den Daten-Ausgängen `OUT` und `FIRST` verknüpft.

### **Daten-Eingänge**
- `IN` (UDINT): Eingangswert. Beim ersten Aufruf mit Wert >0 wird dieser als Basiswert `FIRST` gespeichert (Initialwert: 0).

### **Daten-Ausgänge**
- `OUT` (UDINT): Berechnete Differenz zwischen aktuellem Eingang (`IN`) und Basiswert (`FIRST`) (Initialwert: 0).
- `FIRST` (UDINT): Basiswert, der beim ersten Aufruf mit `IN` > 0 gesetzt wird (Initialwert: 0).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Bei Ereigniseingang `REQ` wird der Algorithmus `REQ` ausgeführt.
2. Falls `FIRST` noch 0 ist und `IN` > 0, wird `FIRST` auf den Wert von `IN` gesetzt.
3. Die Differenz `OUT = IN - FIRST` wird berechnet.
4. Das Ereignis `CNF` wird mit den aktualisierten Werten `OUT` und `FIRST` ausgelöst.

## Technische Besonderheiten
- Verwendet den Datentyp UDINT (32-Bit unsigned integer)
- Initialwerte aller Variablen sind 0
- Der Basiswert `FIRST` wird nur beim ersten Aufruf mit `IN` > 0 gesetzt und bleibt dann konstant

## Zustandsübersicht
- Einziger Zustand: `REQ` (wird bei jedem Aufruf durchlaufen)

## Anwendungsszenarien
- Berechnung von Differenzen zu einem Referenzwert
- Nullpunkt-Kalibrierung von Sensoren
- Relative Wertberechnungen in Steuerungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Gegensatz zu einfachen Subtraktions-Bausteinen speichert OFFSET_UDINT automatisch den ersten gültigen Wert als Basis und berechnet fortlaufend relative Differenzen. Dies erspart zusätzliche Speicherbausteine für die Basiswert-Speicherung.

## Fazit
OFFSET_UDINT ist ein einfacher aber nützlicher Baustein für Anwendungen, bei denen relative Differenzen zu einem einmalig gesetzten Basiswert benötigt werden. Durch die automatische Basiswert-Speicherung vereinfacht er die Implementierung solcher Funktionen.
