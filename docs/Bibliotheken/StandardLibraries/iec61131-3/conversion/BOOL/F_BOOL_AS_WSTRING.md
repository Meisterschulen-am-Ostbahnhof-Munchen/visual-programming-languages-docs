# F_BOOL_AS_WSTRING

```{index} single: F_BOOL_AS_WSTRING
```

<img width="1267" height="182" alt="F_BOOL_AS_WSTRING" src="https://github.com/user-attachments/assets/846eba87-3267-475f-8b1c-02faddc7fcca" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_AS_WSTRING` dient der Konvertierung eines booleschen Wertes (`BOOL`) in eine breite Zeichenkette (`WSTRING`). Diese Funktionalität ist besonders nützlich, wenn boolesche Werte in menschenlesbarer Form ausgegeben oder weiterverarbeitet werden sollen.

![F_BOOL_AS_WSTRING](F_BOOL_AS_WSTRING.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Konvertierung des booleschen Eingabewerts `IN`.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Konvertierung und liefert das Ergebnis `OUT`.

### **Daten-Eingänge**
- `IN` (`BOOL`): Der boolesche Wert, der konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (`WSTRING`): Der konvertierte Wert als breite Zeichenkette.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock konvertiert den booleschen Eingabewert `IN` in eine breite Zeichenkette (`WSTRING`). Die Konvertierung erfolgt mithilfe der Funktion `BOOL_AS_WSTRING`, die den Wert `TRUE` in `"TRUE"` und `FALSE` in `"FALSE"` umwandelt. Die Konvertierung wird durch das Ereignis `REQ` ausgelöst und das Ergebnis wird mit dem Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus zur Konvertierung.
- Die Konvertierung erfolgt direkt und ohne Verzögerung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar nach dem Auslösen des `REQ`-Ereignisses.

## Anwendungsszenarien
- Anzeige von booleschen Werten in Benutzeroberflächen.
- Protokollierung von booleschen Zuständen in Logdateien.
- Weiterverarbeitung von booleschen Werten in Systemen, die Zeichenketten erwarten.

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu `F_BOOL_TO_STRING` wird hier eine breite Zeichenkette (`WSTRING`) anstelle einer normalen Zeichenkette (`STRING`) erzeugt.
- Ähnliche Funktionsblöcke wie `F_INT_AS_WSTRING` oder `F_REAL_AS_WSTRING` konvertieren andere Datentypen in `WSTRING`.

## Fazit
Der Funktionsblock `F_BOOL_AS_WSTRING` bietet eine einfache und effiziente Möglichkeit, boolesche Werte in breite Zeichenketten umzuwandeln. Durch seinen schlanken Aufbau ist er besonders für Anwendungen geeignet, in denen eine schnelle und unkomplizierte Konvertierung benötigt wird.