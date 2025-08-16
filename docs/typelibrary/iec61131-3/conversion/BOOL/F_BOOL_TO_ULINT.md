# F_BOOL_TO_ULINT

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_ULINT` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen vorzeichenlosen 64-Bit-Ganzzahlwert (`ULINT`). Diese Konvertierung ist insbesondere in Szenarien nützlich, in denen boolesche Zustände in numerische Werte umgewandelt werden müssen, beispielsweise für die Verarbeitung in mathematischen Operationen oder für die Speicherung in Datenbanken.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Löst die Konvertierung aus. Verknüpft mit dem Daten-Eingang `IN`.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst. Verknüpft mit dem Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- **IN**: Eingang für den booleschen Wert (`BOOL`), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Ausgang für den konvertierten vorzeichenlosen 64-Bit-Ganzzahlwert (`ULINT`).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von `BOOL` zu `ULINT` durch, wenn das Ereignis `REQ` empfangen wird. Der boolesche Wert `IN` wird in einen `ULINT`-Wert umgewandelt, wobei `FALSE` zu `0` und `TRUE` zu `1` konvertiert wird. Das Ergebnis wird am Ausgang `OUT` ausgegeben und das Ereignis `CNF` wird ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt mittels der Funktion `BOOL_TO_ULINT`, die den booleschen Wert direkt in einen `ULINT`-Wert umwandelt.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von booleschen Schaltzuständen in numerische Werte für weitere Berechnungen.
- Integration in Steuerungssysteme, die boolesche Signale in numerische Datenbanken speichern müssen.
- Verwendung in Datenverarbeitungsketten, die eine Typkonvertierung erfordern.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_BOOL_TO_INT` oder `F_BOOL_TO_DINT` konvertieren boolesche Werte in andere numerische Typen, jedoch nicht in `ULINT`.
- `F_BOOL_TO_ULINT` ist spezifisch für die Konvertierung in den vorzeichenlosen 64-Bit-Typ und eignet sich daher für Anwendungen, die einen großen Wertebereich erfordern.

## Fazit
Der Funktionsblock `F_BOOL_TO_ULINT` bietet eine einfache und effiziente Möglichkeit, boolesche Werte in vorzeichenlose 64-Bit-Ganzzahlen umzuwandeln. Durch seine klare Schnittstelle und direkte Funktionsweise ist er ideal für Anwendungen, die eine Typkonvertierung mit hoher Genauigkeit und großem Wertebereich benötigen.