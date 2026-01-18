# F_REAL_TO_UDINT

```{index} single: F_REAL_TO_UDINT
```

<img width="1448" height="213" alt="F_REAL_TO_UDINT" src="https://github.com/user-attachments/assets/2045df2e-f71d-4277-9b58-2a655adc3493" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_TO_UDINT` dient der Konvertierung eines REAL-Wertes in einen UDINT-Wert. Dieser Baustein ist Teil des `iec61131::conversion`-Pakets und implementiert eine einfache, aber wichtige Typumwandlung für die Verwendung in Steuerungsanwendungen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung der Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (REAL): Der Eingangswert, der von REAL in UDINT konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (UDINT): Der Ergebniswert der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Empfang eines Ereignisses am Eingang `REQ` wird der Algorithmus ausgeführt, der den REAL-Wert am Eingang `IN` in einen UDINT-Wert konvertiert und das Ergebnis am Ausgang `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der eingebauten Funktion `REAL_TO_UDINT`.
- Der Funktionsblock ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder -maschinen. Der Block führt die Konvertierung bei jedem `REQ`-Ereignis aus und signalisiert den Abschluss mit `CNF`.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo REAL-Werte als UDINT verarbeitet werden müssen.
- Integration in größere Funktionsblocknetzwerke, die unterschiedliche Datentypen verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Konvertierungsblöcke wie `F_REAL_TO_INT` oder `F_REAL_TO_LREAL` bieten Konvertierungen in andere Datentypen, aber nicht spezifisch in UDINT.
- Im Gegensatz zu komplexeren Blöcken bietet `F_REAL_TO_UDINT` eine einfache und direkte Lösung für diese spezifische Konvertierung.

## Fazit
Der `F_REAL_TO_UDINT`-Funktionsblock ist ein einfacher, aber essenzieller Baustein für die Typumwandlung in IEC 61499-basierten Steuerungsanwendungen. Seine deterministische und zustandslose Natur macht ihn zuverlässig und leicht integrierbar in verschiedene Anwendungen.
