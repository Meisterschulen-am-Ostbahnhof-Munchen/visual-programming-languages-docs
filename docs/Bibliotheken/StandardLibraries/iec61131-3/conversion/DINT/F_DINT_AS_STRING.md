# F_DINT_AS_STRING

```{index} single: F_DINT_AS_STRING
```

<img width="1255" height="182" alt="F_DINT_AS_STRING" src="https://github.com/user-attachments/assets/541e2cdc-bed5-4e61-822c-cb2a32505087" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DINT_AS_STRING` dient der Konvertierung eines 32-Bit-Ganzzahlwerts (DINT) in eine Zeichenkette (STRING). Diese Funktionalität ist besonders nützlich, wenn numerische Werte für die Anzeige oder Protokollierung in einem menschenlesbaren Format benötigt werden.

![F_DINT_AS_STRING](F_DINT_AS_STRING.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Wird dieser Eingang ausgelöst, wird der Wert am Daten-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang wird zusammen mit dem konvertierten Wert am Daten-Ausgang `OUT` aktiviert.

### **Daten-Eingänge**
- **IN**: Erwartet einen 32-Bit-Ganzzahlwert (DINT), der in eine Zeichenkette umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Liefert den konvertierten Wert als Zeichenkette (STRING).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Bei Auslösung des `REQ`-Ereignisses wird der Algorithmus gestartet, der den Wert von `IN` vom Typ DINT in einen STRING konvertiert. Das Ergebnis wird an `OUT` ausgegeben und das `CNF`-Ereignis signalisiert die erfolgreiche Konvertierung.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der Funktionsblock ist Teil des Pakets `iec61131::conversion`.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von Messwerten in Textdateien oder Datenbanken.
- Vorbereitung von Daten für die Kommunikation mit Systemen, die nur Zeichenketten verarbeiten können.

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu anderen Konvertierungsbausteinen bietet `F_DINT_AS_STRING` eine spezialisierte und effiziente Lösung für die Umwandlung von DINT zu STRING. Andere Bausteine könnten zusätzliche Funktionen wie Formatierung oder Locale-Einstellungen bieten, sind jedoch oft komplexer in der Handhabung.

## Fazit
Der `F_DINT_AS_STRING` Funktionsblock ist eine einfache und effektive Lösung für die Konvertierung von Ganzzahlen in Zeichenketten. Seine klare Schnittstelle und direkte Funktionsweise machen ihn ideal für Anwendungen, bei denen eine schnelle und unkomplizierte Umwandlung benötigt wird.