# F_ULINT_TO_BYTE

```{index} single: F_ULINT_TO_BYTE
```

<img width="1453" height="214" alt="F_ULINT_TO_BYTE" src="https://github.com/user-attachments/assets/f578910e-677f-4594-b1b6-3901e60763ec" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_TO_BYTE` dient der Konvertierung eines 64-Bit-unsigned-Integer-Werts (ULINT) in einen 8-Bit-unsigned-Integer-Wert (BYTE). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen diesen beiden Datentypen erforderlich ist.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (ULINT): Der 64-Bit-unsigned-Integer-Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (BYTE): Der resultierende 8-Bit-unsigned-Integer-Wert nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von ULINT zu BYTE durch, wenn das `REQ`-Ereignis ausgelöst wird. Die Konvertierung erfolgt mittels der Funktion `ULINT_TO_BYTE(IN)`. Nach erfolgreicher Konvertierung wird das `CNF`-Ereignis ausgelöst, und der konvertierte Wert steht am Ausgang `OUT` zur Verfügung.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Algorithmus ohne Zustandsverwaltung.
- Die Konvertierung kann zu Datenverlust führen, wenn der ULINT-Wert außerhalb des darstellbaren Bereichs eines BYTE (0 bis 255) liegt.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder komplexe Zustandslogik.

## Anwendungsszenarien
- Typumwandlung in Steuerungsanwendungen, wo ULINT-Werte auf BYTE reduziert werden müssen.
- Datenverarbeitung in eingebetteten Systemen mit begrenzter Speicherkapazität.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_BYTE` oder `F_UINT_TO_BYTE` führen ähnliche Konvertierungen durch, jedoch mit anderen Ausgangsdatentypen.
- `F_ULINT_TO_BYTE` ist spezifisch für die Konvertierung von 64-Bit-unsigned-Integer zu 8-Bit-unsigned-Integer.

## Fazit
Der `F_ULINT_TO_BYTE` Funktionsblock bietet eine einfache und effiziente Möglichkeit, ULINT-Werte in BYTE-Werte umzuwandeln. Er ist besonders nützlich in Anwendungen, wo eine Reduktion der Datenbreite erforderlich ist, jedoch sollte auf mögliche Datenverluste geachtet werden.