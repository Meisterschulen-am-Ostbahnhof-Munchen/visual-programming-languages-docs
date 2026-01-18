# F_DINT_TO_SINT

```{index} single: F_DINT_TO_SINT
```

<img width="1437" height="217" alt="F_DINT_TO_SINT" src="https://github.com/user-attachments/assets/a19ea1e6-6fc7-492c-8a92-09e3466d0f6c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_TO_SINT` dient der Konvertierung eines 32-Bit Ganzzahlwertes (DINT) in einen 8-Bit Ganzzahlwert (SINT). Dieser Baustein ist besonders nützlich in Szenarien, wo eine Typumwandlung zwischen unterschiedlich großen Integer-Datentypen erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Löst die Konvertierung aus. Wird mit dem Eingabewert `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Liefert den konvertierten Wert über `OUT`.

### **Daten-Eingänge**
- **IN** (DINT): Der 32-Bit Ganzzahlwert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (SINT): Der resultierende 8-Bit Ganzzahlwert nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `DINT` zu `SINT` durch, sobald das Ereignis `REQ` ausgelöst wird. Der Algorithmus nutzt die eingebaute Funktion `DINT_TO_SINT`, um die Umwandlung durchzuführen. Nach erfolgreicher Konvertierung wird das Ereignis `CNF` mit dem Ergebnis `OUT` ausgegeben.

## Technische Besonderheiten
- **Typumwandlung**: Die Konvertierung kann zu Datenverlust führen, wenn der ursprüngliche `DINT`-Wert außerhalb des darstellbaren Bereichs von `SINT` (-128 bis 127) liegt.
- **Einfache Implementierung**: Der Baustein ist als einfacher Funktionsblock (SimpleFB) ohne interne Zustände implementiert.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- **Datenreduktion**: Wenn nur die unteren 8 Bit eines 32-Bit-Wertes relevant sind.
- **Kompatibilität**: Anpassung von Werten für Systeme oder Komponenten, die nur `SINT` verarbeiten können.
- **Protokollierung**: Speicherplatzoptimierte Speicherung von Werten, bei denen die höheren Bits nicht benötigt werden.

## Vergleich mit ähnlichen Bausteinen
- **F_INT_TO_SINT**: Ähnlicher Baustein, aber für 16-Bit zu 8-Bit Konvertierung.
- **F_ANY_TO_<Typ>**: Generische Konvertierungsbausteine, die flexibler, aber möglicherweise weniger effizient sind.

## Fazit
Der `F_DINT_TO_SINT` Funktionsblock bietet eine einfache und effiziente Möglichkeit, 32-Bit Ganzzahlen in 8-Bit Ganzzahlen umzuwandeln. Seine Verwendung ist besonders in ressourcenbeschränkten Umgebungen oder bei der Anpassung von Datentypen zwischen verschiedenen Systemkomponenten sinnvoll. Beachten Sie jedoch die möglichen Datenverluste bei großen Eingabewerten.