# F_REAL_TO_SINT

```{index} single: F_REAL_TO_SINT
```

<img width="1441" height="213" alt="F_REAL_TO_SINT" src="https://github.com/user-attachments/assets/90ac7b2b-bde1-414a-9764-7b9723463b8e" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_TO_SINT` dient der Konvertierung eines `REAL`-Wertes (Fließkommazahl) in einen `SINT`-Wert (8-Bit Ganzzahl mit Vorzeichen). Dieser Baustein ist besonders nützlich in Steuerungsanwendungen, bei denen eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_REAL_TO_SINT](F_REAL_TO_SINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei diesem Ereignis wird der Wert am Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Wert am Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN**: Eingang für den `REAL`-Wert, der in einen `SINT`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgang für den konvertierten `SINT`-Wert.

### **Adapter**
- Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den `REAL`-Wert am Eingang `IN` mittels der Funktion `REAL_TO_SINT` in einen `SINT`-Wert umwandelt. Die Konvertierung erfolgt bei Auftreten des Ereignisses `REQ`, und das Ergebnis wird mit dem Ereignis `CNF` ausgegeben.

## Technische Besonderheiten
- Der Baustein ist als einfacher Funktionsblock (`SimpleFB`) implementiert, der nur einen Algorithmus enthält.
- Die Konvertierung schneidet den `REAL`-Wert auf den Wertebereich von `SINT` (-128 bis 127) zu. Werte außerhalb dieses Bereichs führen zu einem Überlauf.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Konvertierung erfolgt unmittelbar bei Auftreten des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsalgorithmen, wo Fließkommawerte in Ganzzahlen umgewandelt werden müssen.
- Signalverarbeitung, bei der `REAL`-Sensordaten auf `SINT` reduziert werden müssen.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Ähnliche Bausteine wie `F_REAL_TO_INT` oder `F_REAL_TO_USINT` bieten Konvertierungen in andere Ganzzahltypen. `F_REAL_TO_SINT` ist spezifisch für 8-Bit Ganzzahlen mit Vorzeichen.

## Fazit
Der `F_REAL_TO_SINT`-Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung von Fließkommazahlen in 8-Bit Ganzzahlen mit Vorzeichen. Seine Verwendung ist in Szenarien sinnvoll, wo eine solche Typumwandlung erforderlich ist, insbesondere in Steuerungs- und Signalverarbeitungsanwendungen.