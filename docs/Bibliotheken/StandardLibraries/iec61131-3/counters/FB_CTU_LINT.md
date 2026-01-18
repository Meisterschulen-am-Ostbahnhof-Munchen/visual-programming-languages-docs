# FB_CTU_LINT

```{index} single: FB_CTU_LINT
```

<img width="1396" height="277" alt="FB_CTU_LINT" src="https://github.com/user-attachments/assets/a956d757-67d1-486f-b882-ab20f78546cf" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `FB_CTU_LINT` ist ein Aufwärtszähler (Counter Up) für große Ganzzahlen. Er zählt bei jedem eintreffenden Zählereignis hoch und kann auf einen vordefinierten Wert zurückgesetzt werden. Der Block verwendet den Datentyp `LINT` (64-Bit Ganzzahl) für den Zählwert und den Sollwert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsrequest, löst die Zähloperation aus. Wird mit den Daten `CU` und `R` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung, wird nach der Zähloperation ausgegeben. Wird mit den Daten `Q` und `CV` verknüpft.

### **Daten-Eingänge**
- **CU** (BOOL): Zählbefehl (Count Up). Bei TRUE wird der Zähler hochgezählt.
- **R** (BOOL): Reset. Bei TRUE wird der Zähler auf 0 zurückgesetzt.
- **PV** (LINT): Preset Value. Der Sollwert, bei dessen Erreichen der Ausgang `Q` auf TRUE gesetzt wird.

### **Daten-Ausgänge**
- **Q** (BOOL): Ausgang. Wird TRUE, wenn der Zählerstand (`CV`) den Sollwert (`PV`) erreicht oder überschreitet.
- **CV** (LINT): Current Value. Aktueller Zählerstand.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt bei jedem `REQ`-Ereignis folgende Operationen durch:
1. Wenn `R` TRUE ist, wird der Zähler (`CV`) auf 0 zurückgesetzt.
2. Wenn `CU` TRUE ist und der Zähler noch nicht den Maximalwert (9223372036854775807) erreicht hat, wird der Zähler um 1 erhöht.
3. Der Ausgang `Q` wird auf TRUE gesetzt, wenn der Zählerstand (`CV`) den Sollwert (`PV`) erreicht oder überschreitet.

## Technische Besonderheiten
- Verwendet 64-Bit Ganzzahlen (`LINT`) für Zählerstand und Sollwert
- Maximaler Zählerstand: 9223372036854775807 (2^63-1)
- Implementierung in Structured Text (ST)

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustandsautomaten. Die Logik wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Zählung von Ereignissen in großen Zahlenbereichen
- Überwachung von Produktionsmengen
- Steuerung von Prozessen mit hohen Zählwerten

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `FB_CTU` (Standard-Counter) unterstützt dieser Block größere Zahlenbereiche (`LINT` statt `INT`)
- Ähnlich zu `FB_CTUD`, aber ohne Abwärtszählfunktion

## Fazit
Der `FB_CTU_LINT` ist ein leistungsfähiger Aufwärtszähler für Anwendungen, die große Zählbereiche erfordern. Seine einfache Schnittstelle und robuste Implementierung machen ihn zu einem nützlichen Baustein für industrielle Steuerungsanwendungen.