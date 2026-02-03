# F_ULINT_AS_WSTRING

```{index} single: F_ULINT_AS_WSTRING
```

<img width="1490" height="214" alt="F_ULINT_AS_WSTRING" src="https://github.com/user-attachments/assets/b7e7929e-cc1c-4998-8090-b8ceb12f4d39" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_ULINT_AS_WSTRING` dient der Konvertierung eines vorzeichenlosen 64-Bit-Integer-Werts (`ULINT`) in einen Unicode-String (`WSTRING`). Diese Funktionalität ist besonders nützlich in Szenarien, wo numerische Werte für die Anzeige oder Weiterverarbeitung als Text benötigt werden.

![F_ULINT_AS_WSTRING](F_ULINT_AS_WSTRING.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der vorzeichenlose 64-Bit-Integer-Wert (`ULINT`), der in einen Unicode-String konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der resultierende Unicode-String (`WSTRING`) nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` ausgelöst wird. Dabei wird der Wert am Eingang `IN` mittels der Funktion `ULINT_AS_WSTRING` in einen Unicode-String umgewandelt und am Ausgang `OUT` ausgegeben. Das Ereignis `CNF` signalisiert den erfolgreichen Abschluss der Konvertierung.

## Technische Besonderheiten
- Verwendet die Funktion `ULINT_AS_WSTRING` zur Konvertierung.
- Unterstützt den vollständigen Wertebereich von `ULINT` (0 bis 18.446.744.073.709.551.615).

## Zustandsübersicht
- **Idle**: Wartet auf das `REQ`-Ereignis.
- **Converting**: Führt die Konvertierung durch und gibt das Ergebnis über `CNF` aus.

## Anwendungsszenarien
- Anzeige von großen numerischen Werten in Benutzeroberflächen.
- Protokollierung von numerischen Daten in Textform.
- Vorbereitung von Daten für die Kommunikation mit Systemen, die String-Daten erwarten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_INT_AS_WSTRING` oder `F_DINT_AS_WSTRING` unterstützt dieser Baustein den größeren Wertebereich von `ULINT`.
- Ähnlich zu `F_ULINT_TO_WSTRING`, jedoch mit direkter Konvertierung ohne zusätzliche Formatierungsoptionen.

## Fazit
Der `F_ULINT_AS_WSTRING` Funktionsblock bietet eine einfache und effiziente Möglichkeit, große vorzeichenlose Integer-Werte in Unicode-Strings umzuwandeln. Seine klare Schnittstelle und zuverlässige Funktionsweise machen ihn zu einem wertvollen Baustein in der 4diac-IDE.