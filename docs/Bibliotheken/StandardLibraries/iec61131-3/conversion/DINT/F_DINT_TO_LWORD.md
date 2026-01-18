# F_DINT_TO_LWORD

```{index} single: F_DINT_TO_LWORD
```

<img width="1454" height="217" alt="F_DINT_TO_LWORD" src="https://github.com/user-attachments/assets/2b51d495-a600-44ab-afbf-3f6e94586a86" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_LWORD` dient der Konvertierung eines 32-Bit Integer-Werts (DINT) in einen 64-Bit unsigned Integer-Wert (LWORD). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Erweiterung des Wertebereichs oder eine Typanpassung für nachfolgende Verarbeitungsschritte erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, liest der Funktionsblock den Wert am Daten-Eingang `IN` und führt die Konvertierung durch.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Gleichzeitig wird der konvertierte Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN** (DINT): Der 32-Bit Integer-Wert, der in einen 64-Bit unsigned Integer-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (LWORD): Der resultierende 64-Bit unsigned Integer-Wert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus des Funktionsblocks aktiviert. Dieser liest den Wert am Eingang `IN`, konvertiert ihn von DINT zu LWORD und legt das Ergebnis am Ausgang `OUT` ab. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt durch die direkte Zuweisung des DINT-Werts zu einem LWORD, wobei der Wert entsprechend erweitert wird.
- Der Funktionsblock ist deterministisch und führt keine zusätzlichen Berechnungen oder Checks durch.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Operation wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Erweiterung des Wertebereichs für nachfolgende Operationen, die 64-Bit Werte erfordern.
- Typkonvertierung in heterogenen Systemen, wo verschiedene Datentypen verarbeitet werden müssen.
- Einsatz in Steuerungssystemen, wo eine höhere Präzision oder ein größerer Wertebereich benötigt wird.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu generischen Konvertierungsbausteinen ist `F_DINT_TO_LWORD` spezialisiert auf die Konvertierung von DINT zu LWORD.
- Ähnliche Bausteine wie `F_INT_TO_DINT` oder `F_LINT_TO_LWORD` bieten Konvertierungen zwischen anderen Integer-Typen.

## Fazit
Der `F_DINT_TO_LWORD` Funktionsblock ist ein einfacher, aber effektiver Baustein für die Konvertierung von 32-Bit zu 64-Bit Integer-Werten. Seine deterministische Funktionsweise und klare Schnittstelle machen ihn zu einer verlässlichen Komponente in Steuerungs- und Automatisierungslösungen.
