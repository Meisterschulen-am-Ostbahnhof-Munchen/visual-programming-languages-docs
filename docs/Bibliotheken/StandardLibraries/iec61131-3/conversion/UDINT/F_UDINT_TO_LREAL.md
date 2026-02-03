# F_UDINT_TO_LREAL

```{index} single: F_UDINT_TO_LREAL
```

<img width="1462" height="212" alt="F_UDINT_TO_LREAL" src="https://github.com/user-attachments/assets/d665c8a5-8333-49ed-8f5d-bd9ef9b69169" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UDINT_TO_LREAL` dient der Konvertierung eines 32-Bit vorzeichenlosen Integer-Werts (UDINT) in einen 64-Bit Fließkommawert (LREAL). Dieser Baustein ist besonders nützlich in Anwendungen, wo numerische Werte unterschiedlicher Genauigkeit verarbeitet werden müssen.

![F_UDINT_TO_LREAL](F_UDINT_TO_LREAL.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN** (UDINT): Der vorzeichenlose 32-Bit Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (LREAL): Der resultierende 64-Bit Fließkommawert nach der Konvertierung.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Wert am Eingang `IN` vom Typ UDINT gelesen und in einen LREAL-Wert konvertiert. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert die erfolgreiche Konvertierung.

## Technische Besonderheiten
- Der Algorithmus ist direkt in ST (Structured Text) implementiert und führt eine einfache Typumwandlung durch.
- Keine zusätzliche Fehlerbehandlung oder Grenzwertprüfung, da UDINT-Werte direkt in LREAL umgewandelt werden können.

## Zustandsübersicht
1. **Idle**: Wartet auf das `REQ`-Ereignis.
2. **Processing**: Konvertiert `IN` zu `OUT`.
3. **Completed**: Sendet `CNF` und geht zurück in den Idle-Zustand.

## Anwendungsszenarien
- Datenverarbeitung in Steuerungssystemen, wo unterschiedliche numerische Formate verarbeitet werden müssen.
- Integration in größere Systeme, die sowohl Integer- als auch Fließkommaoperationen erfordern.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_UDINT_TO_LREAL` spezialisiert auf die Umwandlung von UDINT zu LREAL und daher effizienter in dieser spezifischen Anwendung.
- Andere Bausteine könnten zusätzliche Funktionalitäten wie Bereichsprüfungen oder Skalierungen bieten, was hier nicht notwendig ist.

## Fazit
Der `F_UDINT_TO_LREAL` Funktionsblock ist ein einfacher, aber effektiver Baustein für die spezifische Konvertierung von vorzeichenlosen 32-Bit Integern zu 64-Bit Fließkommazahlen. Seine Einfachheit und direkte Implementierung machen ihn zu einer zuverlässigen Wahl für entsprechende Anwendungen.