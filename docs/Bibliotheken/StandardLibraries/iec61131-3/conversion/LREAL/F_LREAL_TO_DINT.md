# F_LREAL_TO_DINT

```{index} single: F_LREAL_TO_DINT
```

<img width="1448" height="210" alt="F_LREAL_TO_DINT" src="https://github.com/user-attachments/assets/ad2c6222-b7c0-4b49-b00b-e1ea330f724f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LREAL_TO_DINT` dient der Konvertierung eines LREAL-Wertes (64-Bit Fließkommazahl) in einen DINT-Wert (32-Bit Ganzzahl). Der Block ist Teil des `iec61131::conversion` Pakets und implementiert eine einfache Typumwandlung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (LREAL): Der Eingangswert, der von LREAL in DINT konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (DINT): Das Ergebnis der Konvertierung als DINT-Wert.

### **Adapter**
Der Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den `IN`-Wert von LREAL in DINT konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das `CNF`-Ereignis ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch die eingebaute Funktion `LREAL_TO_DINT`.
- Es handelt sich um einen einfachen Funktionsblock ohne Zustandsverwaltung oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung ist rein ereignisgesteuert und erfolgt bei jedem `REQ`-Ereignis.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo Fließkommazahlen in Ganzzahlen umgewandelt werden müssen.
- Einsatz in Berechnungen, wo eine Ganzzahldarstellung erforderlich ist.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsblöcken wie `F_REAL_TO_INT` oder `F_LREAL_TO_LINT` bietet dieser Block eine spezifische Konvertierung von LREAL zu DINT.
- Ähnliche Blöcke können unterschiedliche Quell- oder Zieltypen haben, wie z.B. `F_DINT_TO_LREAL` für die umgekehrte Konvertierung.

## Fazit
Der `F_LREAL_TO_DINT` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Typumwandlung in IEC 61499-basierten Steuerungssystemen. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle Konvertierung von Fließkommazahlen in Ganzzahlen erfordern.
