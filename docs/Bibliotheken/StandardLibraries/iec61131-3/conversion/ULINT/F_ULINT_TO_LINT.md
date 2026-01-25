# F_ULINT_TO_LINT

```{index} single: F_ULINT_TO_LINT
```

<img width="1448" height="214" alt="F_ULINT_TO_LINT" src="https://github.com/user-attachments/assets/198ce0c4-05ea-4392-8b16-aa83ed6ab931" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_LINT` dient der Konvertierung eines vorzeichenlosen 64-Bit-Integer-Werts (ULINT) in einen vorzeichenbehafteten 64-Bit-Integer-Wert (LINT). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

![F_ULINT_TO_LINT](F_ULINT_TO_LINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (ULINT): Der vorzeichenlose 64-Bit-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (LINT): Der resultierende vorzeichenbehaftete 64-Bit-Integer-Wert nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den Wert des Eingangs `IN` vom Typ `ULINT` in den Typ `LINT` umwandelt. Die Umwandlung erfolgt direkt und ohne weitere Bearbeitung. Das Ergebnis wird am Ausgang `OUT` ausgegeben, sobald das Ereignis `CNF` ausgelöst wird.

## Technische Besonderheiten
- Die Konvertierung erfolgt mittels der Funktion `ULINT_TO_LINT`, die im Algorithmus des Funktionsblocks implementiert ist.
- Der Baustein ist für die Verwendung in Echtzeitsystemen geeignet, da er keine Verzögerungen oder komplexe Berechnungen beinhaltet.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem Auftreten des `REQ`-Ereignisses durchgeführt und unmittelbar bestätigt.

## Anwendungsszenarien
- Typumwandlung in Steuerungs- und Automatisierungssystemen.
- Datenverarbeitung in industriellen Anwendungen, wo vorzeichenlose und vorzeichenbehaftete Werte verarbeitet werden müssen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen, wie z.B. `F_DINT_TO_INT`, ist dieser speziell für 64-Bit-Datentypen ausgelegt.
- Ähnliche Bausteine könnten zusätzliche Funktionen wie Bereichsprüfungen oder Fehlerbehandlungen beinhalten, was hier nicht der Fall ist.

## Fazit
Der `F_ULINT_TO_LINT` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung zwischen den Datentypen `ULINT` und `LINT`. Seine Einfachheit macht ihn zuverlässig und leicht in bestehende Systeme integrierbar.