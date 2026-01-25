# F_STRING_AS_WORD

```{index} single: F_STRING_AS_WORD
```

<img width="1472" height="212" alt="F_STRING_AS_WORD" src="https://github.com/user-attachments/assets/8e482512-b995-4049-9756-73367fae1729" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_STRING_AS_WORD` dient zur Konvertierung eines `STRING`-Wertes in einen `WORD`-Wert. Diese Funktionalität ist insbesondere in Szenarien nützlich, in denen Zeichenketten in numerische Werte umgewandelt werden müssen, um sie in weiteren Berechnungen oder Steuerungslogiken zu verwenden.

![F_STRING_AS_WORD](F_STRING_AS_WORD.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderungseingang. Wird verwendet, um die Konvertierung zu starten. Ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird nach erfolgreicher Konvertierung ausgelöst. Ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Eingabe vom Typ `STRING`. Enthält den zu konvertierenden Zeichenkettenwert.

### **Daten-Ausgänge**
- **OUT**: Ausgabe vom Typ `WORD`. Enthält das Ergebnis der Konvertierung des Eingabestrings.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` empfangen wird. Dabei wird der Eingabestring `IN` mittels der Funktion `STRING_AS_WORD` in einen `WORD`-Wert umgewandelt und das Ergebnis an `OUT` ausgegeben. Anschließend wird das Bestätigungsereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock ist einfach aufgebaut und enthält nur einen Algorithmus zur Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Zustandsverwaltung.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Konvertierung von Benutzereingaben oder Kommunikationsdaten in numerische Werte.
- Verwendung in Steuerungslogiken, die numerische Verarbeitung erfordern.
- Integration in größere Automatisierungssysteme, die String- und Wort-Daten verarbeiten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_STRING_TO_INT` oder `F_STRING_TO_REAL` konvertiert dieser Baustein spezifisch in den `WORD`-Datentyp.
- Einfacher und direkter als Bausteine mit zusätzlichen Funktionen wie Fehlerbehandlung oder Formatierung.

## Fazit
Der `F_STRING_AS_WORD`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, Zeichenketten in `WORD`-Werte umzuwandeln. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für den Einsatz in verschiedenen Automatisierungs- und Steuerungsszenarien.