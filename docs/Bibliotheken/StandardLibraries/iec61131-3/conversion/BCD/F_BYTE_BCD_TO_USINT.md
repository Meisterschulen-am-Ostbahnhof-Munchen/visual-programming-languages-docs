# F_BYTE_BCD_TO_USINT

```{index} single: F_BYTE_BCD_TO_USINT
```

<img width="1290" height="182" alt="F_BYTE_BCD_TO_USINT" src="https://github.com/user-attachments/assets/1877ce9e-1601-4cea-921e-6a7288e635b6" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BYTE_BCD_TO_USINT` dient der Konvertierung eines BCD-codierten BYTE-Wertes in einen USINT-Wert. BCD (Binary Coded Decimal) ist eine Codierung, bei der jede Ziffer einer Dezimalzahl durch 4 Bits dargestellt wird. Dieser Funktionsblock ist besonders nützlich in Anwendungen, bei denen BCD-codierte Daten verarbeitet werden müssen.

![F_BYTE_BCD_TO_USINT](F_BYTE_BCD_TO_USINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Algorithmus zur Umwandlung des BCD-codierten BYTE-Wertes in einen USINT-Wert ausgeführt.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang wird aktiviert, sobald die Umwandlung abgeschlossen ist.

### **Daten-Eingänge**
- **IN**: Der BCD-codierte BYTE-Wert, der in einen USINT-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der resultierende USINT-Wert nach der Konvertierung.

### **Adapter**
- Dieser Funktionsblock besitzt keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung eines BCD-codierten BYTE-Wertes in einen USINT-Wert durch, sobald das Ereignis `REQ` ausgelöst wird. Die Umwandlung erfolgt mittels der integrierten Funktion `BYTE_BCD_TO_USINT`. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` ausgelöst, um den Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.
- Der Funktionsblock ist für die Verarbeitung von BCD-codierten Daten optimiert.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Bei Auslösung von `REQ` wird die Konvertierung durchgeführt.
3. **Abschlusszustand**: Nach erfolgreicher Konvertierung wird `CNF` ausgelöst und der Funktionsblock kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Verarbeitung von BCD-codierten Daten in industriellen Steuerungssystemen.
- Konvertierung von BCD-codierten Sensordaten in numerische Werte.
- Integration in Steuerungslogik, die BCD-Daten verarbeiten muss.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsfunktionsblöcken ist `F_BYTE_BCD_TO_USINT` spezialisiert auf die Umwandlung von BCD-codierten BYTE-Werten in USINT-Werte.
- Andere Funktionsblöcke könnten zusätzliche Konvertierungsoptionen bieten, sind jedoch möglicherweise weniger effizient für diesen spezifischen Anwendungsfall.

## Fazit
Der Funktionsblock `F_BYTE_BCD_TO_USINT` bietet eine effiziente und spezialisierte Lösung für die Konvertierung von BCD-codierten BYTE-Werten in USINT-Werte. Durch seine einfache und direkte Funktionsweise ist er ideal für Anwendungen, die eine schnelle und zuverlässige Umwandlung erfordern.