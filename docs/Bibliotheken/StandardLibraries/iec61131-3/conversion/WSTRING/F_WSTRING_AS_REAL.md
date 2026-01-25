# F_WSTRING_AS_REAL

```{index} single: F_WSTRING_AS_REAL
```

<img width="1481" height="214" alt="F_WSTRING_AS_REAL" src="https://github.com/user-attachments/assets/6c4a0b16-af89-44e9-80ef-d3aff2884324" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_WSTRING_AS_REAL` dient der Konvertierung eines WSTRING-Wertes in einen REAL-Wert. Dieser Baustein ist besonders nützlich, wenn Zeichenketten, die numerische Werte repräsentieren, in numerische Datentypen umgewandelt werden müssen, um sie für weitere Berechnungen oder Steuerungslogik zu verwenden.

![F_WSTRING_AS_REAL](F_WSTRING_AS_REAL.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der im Daten-Eingang `IN` enthaltene WSTRING-Wert in einen REAL-Wert umgewandelt.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang wird aktiviert, sobald die Umwandlung abgeschlossen ist und der Ergebniswert im Daten-Ausgang `OUT` verfügbar ist.

### **Daten-Eingänge**
- **IN**: Hier wird der WSTRING-Wert eingegeben, der in einen REAL-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Enthält den konvertierten REAL-Wert nach erfolgreicher Ausführung des Funktionsblocks.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das Ereignis `REQ` ausgelöst wird. Die Umwandlung erfolgt mithilfe der internen Funktion `WSTRING_AS_REAL`, die den WSTRING-Eingang `IN` in einen REAL-Wert umwandelt und das Ergebnis im Ausgang `OUT` speichert. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock unterstützt die Konvertierung von WSTRING nach REAL, was besonders in internationalen Anwendungen nützlich ist, da WSTRING Unicode-Zeichen unterstützt.
- Die Konvertierung erfolgt in einem einzigen Algorithmusschritt, was eine effiziente Ausführung gewährleistet.

## Zustandsübersicht
1. **Idle-Zustand**: Der Funktionsblock wartet auf das Auslösen des `REQ`-Ereignisses.
2. **Konvertierungszustand**: Bei Auslösen von `REQ` wird die Konvertierung durchgeführt.
3. **Bestätigungszustand**: Nach erfolgreicher Konvertierung wird `CNF` ausgelöst und der Funktionsblock kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- **Datenverarbeitung**: Umwandlung von Benutzereingaben oder gelesenen Zeichenketten in numerische Werte für Berechnungen.
- **Schnittstellenkommunikation**: Konvertierung von Zeichenketten, die über Netzwerke oder Schnittstellen empfangen werden, in numerische Werte für die Steuerungslogik.
- **Internationale Anwendungen**: Verarbeitung von Unicode-kodierten Zeichenketten, die numerische Daten enthalten.

## Vergleich mit ähnlichen Bausteinen
- **F_STRING_AS_REAL**: Ähnlicher Funktionsblock, jedoch für den Datentyp STRING anstelle von WSTRING. `F_WSTRING_AS_REAL` ist vorzuziehen, wenn Unicode-Unterstützung erforderlich ist.
- **F_WSTRING_TO_***: Andere Konvertierungsbausteine für WSTRING, die jedoch in andere Datentypen wie INT oder BOOL umwandeln.

## Fazit
Der `F_WSTRING_AS_REAL`-Funktionsblock ist ein effizientes Werkzeug zur Konvertierung von Unicode-Zeichenketten in numerische REAL-Werte. Seine einfache Schnittstelle und zuverlässige Funktionsweise machen ihn ideal für Anwendungen, die internationale Zeichensätze oder komplexe Datenverarbeitung erfordern.