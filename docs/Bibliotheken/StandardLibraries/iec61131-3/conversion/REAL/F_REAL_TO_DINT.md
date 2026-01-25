# F_REAL_TO_DINT

```{index} single: F_REAL_TO_DINT
```

<img width="1235" height="175" alt="F_REAL_TO_DINT" src="https://github.com/user-attachments/assets/fd78a595-bfca-47f7-b4d9-acd46bf10b52" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_REAL_TO_DINT` dient der Konvertierung eines REAL-Wertes (Fließkommazahl) in einen DINT-Wert (32-Bit Ganzzahl). Diese Konvertierung erfolgt durch Abrundung des REAL-Wertes auf die nächstkleinere Ganzzahl.

![F_REAL_TO_DINT](F_REAL_TO_DINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst.

### **Daten-Eingänge**
- **IN**: Eingang für den REAL-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgang für den konvertierten DINT-Wert.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus ausgeführt, der den `IN`-Wert von REAL nach DINT konvertiert. Das Ergebnis wird am `OUT`-Ausgang ausgegeben und das `CNF`-Ereignis wird ausgelöst.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch Abrundung des REAL-Wertes.
- Der Funktionsblock ist einfach und hat keine internen Zustände.

## Zustandsübersicht
Keine Zustände vorhanden, da der Block stateless ist.

## Anwendungsszenarien
- Konvertierung von Sensorwerten (Fließkomma) in ganzzahlige Werte für Steuerungslogik.
- Datenverarbeitung in Steuerungssystemen, wo ganzzahlige Werte benötigt werden.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke könnten andere Konvertierungsmethoden anbieten, z.B. mit Rundung oder Aufrundung.
- Im Vergleich zu generischen Konvertierungsblöcken ist dieser spezialisiert auf REAL-zu-DINT Konvertierung.

## Fazit
Der `F_REAL_TO_DINT` Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung von Fließkommazahlen in Ganzzahlen. Er ist besonders nützlich in Szenarien, wo eine schnelle und direkte Konvertierung benötigt wird.