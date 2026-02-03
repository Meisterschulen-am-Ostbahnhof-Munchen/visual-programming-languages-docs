# F_LINT_AS_STRING

```{index} single: F_LINT_AS_STRING
```

<img width="1256" height="183" alt="F_LINT_AS_STRING" src="https://github.com/user-attachments/assets/c1d86074-155a-49cf-b025-bacefa300e09" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_AS_STRING` dient der Konvertierung eines LINT-Datentyps (64-Bit-Ganzzahl) in einen STRING-Datentyp (Zeichenkette). Dieser Baustein ist besonders nützlich, wenn numerische Werte für die Ausgabe oder Weiterverarbeitung als Text benötigt werden.

![F_LINT_AS_STRING](F_LINT_AS_STRING.svg)

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Bei Aktivierung dieses Ereignisses wird der Wert am Daten-Eingang `IN` verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieses Ereignis wird zusammen mit dem konvertierten Wert am Daten-Ausgang `OUT` ausgegeben.

### **Daten-Eingänge**
- **IN** (LINT): Der Eingang für den zu konvertierenden LINT-Wert.

### **Daten-Ausgänge**
- **OUT** (STRING): Der Ausgang für den konvertierten STRING-Wert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt bei Aktivierung des `REQ`-Ereignisses die Konvertierung des LINT-Wertes am Eingang `IN` in einen STRING-Wert durch. Das Ergebnis wird am Ausgang `OUT` ausgegeben und durch das `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Baustein (SimpleFB) und verwendet einen ST-Algorithmus für die Konvertierung.
- Die Konvertierung erfolgt direkt durch die Funktion `LINT_AS_STRING(IN)`.

## Zustandsübersicht
1. **Initialisierung**: Der Funktionsblock wartet auf das `REQ`-Ereignis.
2. **Konvertierung**: Bei `REQ` wird der LINT-Wert konvertiert.
3. **Bestätigung**: Das `CNF`-Ereignis wird ausgelöst und der konvertierte Wert ausgegeben.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von numerischen Daten in Textdateien.
- Vorbereitung von Daten für die Kommunikation über Text-basierte Protokolle.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `F_INT_AS_STRING` oder `F_DINT_AS_STRING` unterstützt dieser Baustein den größeren LINT-Datentyp (64-Bit).

## Fazit
Der `F_LINT_AS_STRING` Funktionsblock bietet eine einfache und effiziente Möglichkeit, große Ganzzahlen in lesbare Zeichenketten umzuwandeln. Durch seine klare Schnittstelle und einfache Funktionsweise ist er ideal für Anwendungen, die eine Konvertierung zwischen diesen Datentypen erfordern.