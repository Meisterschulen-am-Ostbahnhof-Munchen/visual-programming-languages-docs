# F_UDINT_TO_REAL

```{index} single: F_UDINT_TO_REAL
```

<img width="1450" height="216" alt="F_UDINT_TO_REAL" src="https://github.com/user-attachments/assets/8be282c0-424f-4a10-8a26-e020cf9c2cc9" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_UDINT_TO_REAL` dient der Konvertierung eines vorzeichenlosen 32-Bit-Integer-Werts (`UDINT`) in einen 32-Bit-Gleitkommawert (`REAL`). Dieser Baustein ist besonders nützlich in Szenarien, wo numerische Werte unterschiedlicher Datentypen verarbeitet werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN**: Erwartet einen Eingabewert vom Typ `UDINT` (vorzeichenloser 32-Bit-Integer).

### **Daten-Ausgänge**
- **OUT**: Gibt den konvertierten Wert als `REAL` (32-Bit-Gleitkommazahl) aus.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus gestartet, der den `UDINT`-Wert am Eingang `IN` in einen `REAL`-Wert konvertiert und das Ergebnis am Ausgang `OUT` bereitstellt. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt mittels der eingebauten Funktion `UDINT_TO_REAL`.
- Der Funktionsblock ist einfach und effizient, da er keine komplexen Zustandsmaschinen oder zusätzliche Verarbeitungsschritte benötigt.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Verarbeitung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von Rohdaten (z.B. aus Sensoren oder Kommunikationsprotokollen) in Gleitkommawerte für weitere Berechnungen.
- Integration in Steuerungssysteme, wo unterschiedliche Datentypen verarbeitet werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_UDINT_TO_REAL` spezialisiert und optimiert für die spezifische Konvertierung von `UDINT` zu `REAL`.
- Ähnliche Bausteine könnten zusätzliche Funktionen wie Bereichsprüfungen oder Skalierungen bieten, was hier nicht der Fall ist.

## Fazit
Der `F_UDINT_TO_REAL`-Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung von vorzeichenlosen 32-Bit-Integern in Gleitkommazahlen. Seine Einfachheit macht ihn besonders geeignet für Anwendungen, wo eine schnelle und direkte Konvertierung benötigt wird.