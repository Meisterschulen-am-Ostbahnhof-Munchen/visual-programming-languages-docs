# F_REAL_TO_LINT

```{index} single: F_REAL_TO_LINT
```

<img width="1433" height="216" alt="F_REAL_TO_LINT" src="https://github.com/user-attachments/assets/27a08bc4-5fb5-42da-95cd-5c700436c357" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_TO_LINT` dient der Konvertierung eines REAL-Wertes (Fließkommazahl) in einen LINT-Wert (64-Bit Ganzzahl). Diese Konvertierung ist besonders nützlich, wenn numerische Berechnungen mit unterschiedlichen Datentypen durchgeführt werden müssen.

![F_REAL_TO_LINT](F_REAL_TO_LINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Ereigniseingang ausgelöst, wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Der Eingang für den REAL-Wert, der in einen LINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang, an dem der konvertierte LINT-Wert ausgegeben wird.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus `REQ` ausgeführt. Dieser konvertiert den REAL-Wert am Eingang `IN` mittels der Funktion `REAL_TO_LINT` in einen LINT-Wert und schreibt das Ergebnis an den Ausgang `OUT`. Anschließend wird das `CNF`-Ereignis ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung von REAL zu LINT kann zu Datenverlust führen, wenn der REAL-Wert Nachkommastellen besitzt, da diese bei der Konvertierung abgeschnitten werden.
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar nach Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Konvertierung von Sensorwerten (z.B. Temperaturmessungen) für weitere Verarbeitung in Ganzzahl-Operationen.
- Integration in Steuerungssysteme, die gemischte Datentypen verarbeiten müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen (z.B. `F_REAL_TO_INT`) bietet `F_REAL_TO_LINT` eine höhere Präzision durch die Verwendung des 64-Bit LINT-Datentyps.
- Ähnliche Bausteine wie `F_LINT_TO_REAL` führen die umgekehrte Konvertierung durch.

## Fazit
Der Funktionsblock `F_REAL_TO_LINT` ist ein einfacher und effizienter Baustein zur Konvertierung von Fließkommazahlen in 64-Bit Ganzzahlen. Seine Verwendung ist besonders in Szenarien mit hohen Präzisionsanforderungen zu empfehlen, wobei auf mögliche Datenverluste bei der Konvertierung zu achten ist.