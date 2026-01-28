# F_LINT_TO_UINT

```{index} single: F_LINT_TO_UINT
```

<img width="1436" height="214" alt="F_LINT_TO_UINT" src="https://github.com/user-attachments/assets/da4ca59c-9a44-4c2e-ad16-0ae14c1ab1de" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_UINT` dient zur Konvertierung eines 64-Bit-Ganzzahlwerts (`LINT`) in einen 16-Bit-unsigned-Ganzzahlwert (`UINT`). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen unterschiedlich großen numerischen Datentypen erforderlich ist.

![F_LINT_TO_UINT](F_LINT_TO_UINT.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen Wert vom Typ `LINT` (64-Bit-Ganzzahl), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten Wert vom Typ `UINT` (16-Bit-unsigned-Ganzzahl).

### **Adapter**
Es sind keine Adapter definiert.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `LINT` zu `UINT` durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus `REQ` nutzt die Funktion `LINT_TO_UINT`, um den Eingabewert umzuwandeln. Das Ergebnis wird über den Ausgang `OUT` ausgegeben, und das Ereignis `CNF` signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- **Typumwandlung**: Es ist wichtig zu beachten, dass bei der Konvertierung von einem größeren zu einem kleineren Datentyp Datenverlust auftreten kann, wenn der ursprüngliche Wert außerhalb des darstellbaren Bereichs von `UINT` liegt.
- **Effizienz**: Die Konvertierung erfolgt direkt und ohne zusätzliche Verzögerung.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- **Datenverarbeitung**: In Steuerungssystemen, wo unterschiedliche Datentypen harmonisiert werden müssen.
- **Schnittstellenkompatibilität**: Bei der Kommunikation zwischen Systemen, die unterschiedliche Datentypen verwenden.

## Vergleich mit ähnlichen Bausteinen
- **F_LINT_TO_INT**: Konvertiert `LINT` zu `INT`, behält aber das Vorzeichen bei.
- **F_LINT_TO_ULINT**: Konvertiert `LINT` zu `ULINT`, ohne die Bitbreite zu reduzieren.

## Fazit
Der `F_LINT_TO_UINT`-Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Typumwandlung in IEC 61499-basierten Systemen. Seine klare Schnittstelle und direkte Funktionsweise machen ihn zu einer zuverlässigen Lösung für Konvertierungsaufgaben. Beachten Sie jedoch mögliche Datenverluste bei der Umwandlung.