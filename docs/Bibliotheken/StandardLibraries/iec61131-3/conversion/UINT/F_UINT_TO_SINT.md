# F_UINT_TO_SINT

```{index} single: F_UINT_TO_SINT
```

<img width="1441" height="216" alt="F_UINT_TO_SINT" src="https://github.com/user-attachments/assets/34da5b79-b1cc-4893-9138-b98b0cbfab10" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_UINT_TO_SINT` dient der Konvertierung eines vorzeichenlosen 16-Bit-Integer-Werts (UINT) in einen vorzeichenbehafteten 8-Bit-Integer-Wert (SINT). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei Aktivierung wird der Eingangswert `IN` gelesen und verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgangswert `OUT` steht dann zur Verfügung.

### **Daten-Eingänge**
- **IN** (UINT): Der vorzeichenlose 16-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (SINT): Der resultierende vorzeichenbehaftete 8-Bit-Integer-Wert nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem der `UINT`-Wert am Eingang `IN` in einen `SINT`-Wert umgewandelt und am Ausgang `OUT` ausgegeben wird. Die Konvertierung erfolgt bei Aktivierung des `REQ`-Ereignisses, und das `CNF`-Ereignis signalisiert die Fertigstellung.

## Technische Besonderheiten
- Die Konvertierung kann zu Datenverlust führen, wenn der `UINT`-Wert außerhalb des darstellbaren Bereichs von `SINT` (0 bis 127) liegt.
- Der Baustein ist als einfacher Funktionsblock (SimpleFB) implementiert und verwendet einen ST-Algorithmus für die Konvertierung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Aktivierung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo `UINT`-Werte in `SINT`-Werte umgewandelt werden müssen.
- Datenverarbeitung in industriellen Automatisierungssystemen, wo unterschiedliche Datentypen verarbeitet werden.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen ist `F_UINT_TO_SINT` spezialisiert auf die Umwandlung von `UINT` zu `SINT`.
- Andere Konvertierungsbausteine könnten zusätzliche Funktionen wie Bereichsprüfungen oder Fehlerbehandlung bieten.

## Fazit
Der `F_UINT_TO_SINT`-Funktionsblock ist ein effizientes Werkzeug für die spezifische Konvertierung von `UINT` zu `SINT`. Seine Einfachheit und direkte Funktionsweise machen ihn ideal für Anwendungen, die eine schnelle und unkomplizierte Typumwandlung erfordern.