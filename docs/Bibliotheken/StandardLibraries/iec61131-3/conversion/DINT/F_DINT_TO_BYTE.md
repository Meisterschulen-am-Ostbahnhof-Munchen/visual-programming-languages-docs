# F_DINT_TO_BYTE

```{index} single: F_DINT_TO_BYTE
```

<img width="1437" height="212" alt="F_DINT_TO_BYTE" src="https://github.com/user-attachments/assets/ed116d5d-f0ed-4f4d-9ddc-489b45dec70f" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_BYTE` dient der Konvertierung eines 32-Bit Ganzzahlwerts (DINT) in einen 8-Bit Ganzzahlwert (BYTE). Diese Konvertierung ist besonders nützlich, wenn Daten zwischen Systemen mit unterschiedlichen Wortbreiten ausgetauscht oder verarbeitet werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` gelesen und konvertiert.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den erfolgreichen Abschluss der Konvertierung. Der konvertierte Wert steht am Daten-Ausgang `OUT` zur Verfügung.

### **Daten-Eingänge**
- **IN**: Der Eingangswert vom Typ `DINT` (32-Bit Ganzzahl), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgangswert vom Typ `BYTE` (8-Bit Ganzzahl), der das Ergebnis der Konvertierung enthält.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus ausgeführt, der den Wert am Eingang `IN` vom Typ `DINT` in einen `BYTE`-Wert konvertiert. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert den Abschluss der Operation.

Der verwendete Algorithmus lautet:
```ST
OUT := DINT_TO_BYTE(IN);
```

## Technische Besonderheiten
- Die Konvertierung von `DINT` zu `BYTE` kann zu Datenverlust führen, wenn der ursprüngliche Wert außerhalb des darstellbaren Bereichs eines `BYTE` (0 bis 255) liegt.
- Der Funktionsblock ist einfach und deterministisch, ohne interne Zustände oder komplexe Logik.

## Zustandsübersicht
Der Funktionsblock hat keinen internen Zustand. Die Ausführung erfolgt ausschließlich bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Reduzierung der Datenbreite für die Kommunikation mit Peripheriegeräten, die nur BYTE-Daten verarbeiten können.
- Vorverarbeitung von Daten für Systeme mit begrenzter Speicherkapazität.
- Integration in größere Steuerungssysteme, wo unterschiedliche Datentypen konvertiert werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_DINT_TO_BYTE` spezialisiert und optimiert für die spezifische Konvertierung von `DINT` zu `BYTE`.
- Ähnliche Blöcke wie `F_INT_TO_BYTE` oder `F_WORD_TO_BYTE` bieten Konvertierungen zwischen anderen Datentypen, aber mit ähnlicher Funktionsweise.

## Fazit
Der `F_DINT_TO_BYTE` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von 32-Bit Ganzzahlen in 8-Bit Werte. Seine Einfachheit und Determinismus machen ihn zuverlässig, aber Anwender sollten potenzielle Datenverluste bei großen Eingangswerten berücksichtigen. Ideal für Anwendungen, wo platzsparende Datendarstellung erforderlich ist.
