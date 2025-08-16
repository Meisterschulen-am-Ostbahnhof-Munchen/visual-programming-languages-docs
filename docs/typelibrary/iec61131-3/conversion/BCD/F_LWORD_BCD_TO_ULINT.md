# F_LWORD_BCD_TO_ULINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LWORD_BCD_TO_ULINT` dient der Konvertierung eines BCD-kodierten `LWORD`-Werts in einen `ULINT`-Wert. Dies ist besonders nützlich in Anwendungen, wo BCD-kodierte Daten verarbeitet werden müssen, wie z.B. in industriellen Steuerungen oder Kommunikationsprotokollen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang für den BCD-kodierten `LWORD`-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang für den konvertierten `ULINT`-Wert.

### **Adapter**
Es sind keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das `REQ`-Ereignis eintrifft. Dabei wird der BCD-kodierte `LWORD`-Wert am Eingang `IN` in einen `ULINT`-Wert umgewandelt und am Ausgang `OUT` bereitgestellt. Das `CNF`-Ereignis signalisiert die erfolgreiche Konvertierung.

## Technische Besonderheiten
- Der Funktionsblock verwendet den BCD-zu-ULINT-Konvertierungsalgorithmus, der in der IEC 61131-3-Standardbibliothek definiert ist.
- Die Konvertierung erfolgt synchron mit dem `REQ`-Ereignis.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Bei Eintreffen von `REQ` wird die Konvertierung durchgeführt und das `CNF`-Ereignis ausgelöst.

## Anwendungsszenarien
- Verarbeitung von BCD-kodierten Daten in industriellen Steuerungen.
- Konvertierung von BCD-kodierten Werten in numerische Werte für weitere Berechnungen.

## Vergleich mit ähnlichen Bausteinen
- **F_BCD_TO_ULINT**: Konvertiert BCD-kodierte Werte in `ULINT`, jedoch für andere Datentypen als `LWORD`.
- **F_LWORD_TO_ULINT**: Konvertiert `LWORD` in `ULINT`, jedoch ohne BCD-Kodierung.

## Fazit
Der `F_LWORD_BCD_TO_ULINT`-Funktionsblock ist ein spezialisierter Baustein für die Konvertierung von BCD-kodierten `LWORD`-Werten in `ULINT`. Er ist einfach zu verwenden und eignet sich besonders für Anwendungen, die mit BCD-kodierten Daten arbeiten.