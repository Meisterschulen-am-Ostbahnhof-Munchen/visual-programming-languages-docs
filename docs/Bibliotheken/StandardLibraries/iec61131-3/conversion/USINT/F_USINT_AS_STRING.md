# F_USINT_AS_STRING

```{index} single: F_USINT_AS_STRING
```

<img width="1481" height="214" alt="F_USINT_AS_STRING" src="https://github.com/user-attachments/assets/bdc5d422-b30f-4da1-89aa-4becb5d9337d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_USINT_AS_STRING` dient der Konvertierung eines vorzeichenlosen 8-Bit-Integer-Werts (USINT) in einen String (STRING). Diese Funktionalität ist besonders nützlich, wenn numerische Werte für die Anzeige oder Protokollierung in eine lesbare Textform umgewandelt werden müssen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Ein vorzeichenloser 8-Bit-Integer-Wert (USINT), der in einen String konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der resultierende String (STRING), der den konvertierten Wert enthält.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des Ereigniseingangs `REQ` wird der Algorithmus ausgeführt, der den USINT-Wert `IN` in einen String konvertiert und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock verwendet die Funktion `USINT_AS_STRING` zur Konvertierung.
- Es handelt sich um einen einfachen Funktionsblock ohne Zustandsautomat oder komplexe Logik.

## Zustandsübersicht
Da es sich um einen einfachen Funktionsblock handelt, gibt es keine Zustandsübergänge oder -verwaltung. Die Operation wird bei jedem `REQ`-Ereignis ausgeführt und mit `CNF` bestätigt.

## Anwendungsszenarien
- Anzeige von numerischen Werten auf einem Bedienpanel.
- Protokollierung von Messwerten in einer Textdatei oder Datenbank.
- Vorbereitung von Daten für die Kommunikation über Textprotokolle (z.B. HTTP, MQTT).

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsblöcken ist `F_USINT_AS_STRING` spezialisiert auf die Konvertierung von USINT zu STRING und daher effizienter in dieser spezifischen Anwendung.
- Andere Blöcke könnten zusätzliche Optionen wie Formatierung oder Locale-Einstellungen bieten, was hier nicht der Fall ist.

## Fazit
Der `F_USINT_AS_STRING` Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von vorzeichenlosen 8-Bit-Integern in Strings. Seine Einfachheit macht ihn besonders geeignet für Anwendungen, bei denen Performance und Zuverlässigkeit im Vordergrund stehen.
