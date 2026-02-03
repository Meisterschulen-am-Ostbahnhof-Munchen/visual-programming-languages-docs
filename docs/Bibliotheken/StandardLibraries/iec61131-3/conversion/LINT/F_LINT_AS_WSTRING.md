# F_LINT_AS_WSTRING

```{index} single: F_LINT_AS_WSTRING
```

<img width="1265" height="183" alt="F_LINT_AS_WSTRING" src="https://github.com/user-attachments/assets/541513e7-d8aa-464e-9e9c-48ecd85a527a" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_AS_WSTRING` dient zur Konvertierung eines LINT-Wertes (64-Bit-Ganzzahl) in einen WSTRING (Wide-String). Dieser Baustein ist besonders nützlich in Szenarien, wo numerische Werte als Zeichenketten ausgegeben oder weiterverarbeitet werden müssen.

![F_LINT_AS_WSTRING](F_LINT_AS_WSTRING.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung des LINT-Wertes zu einem WSTRING. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN** (LINT): Der LINT-Wert, der in einen WSTRING konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (WSTRING): Der resultierende WSTRING nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, sobald das `REQ`-Ereignis eintrifft. Dabei wird der LINT-Wert von `IN` in einen WSTRING umgewandelt und an `OUT` ausgegeben. Die Konvertierung wird durch das `CNF`-Ereignis bestätigt.

## Technische Besonderheiten
- Der Baustein nutzt die `LINT_AS_WSTRING`-Funktion zur Konvertierung.
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Konvertierungszustand**: Führt die Konvertierung durch und gibt das Ergebnis aus.
3. **Bestätigungszustand**: Sendet das `CNF`-Ereignis zur Bestätigung der Konvertierung.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von numerischen Daten in Textdateien.
- Kommunikation mit Systemen, die String-Daten erwarten.

## ⚖️ Vergleich mit ähnlichen Bausteinen
- **F_INT_AS_WSTRING**: Konvertiert INT (16-Bit) zu WSTRING.
- **F_DINT_AS_WSTRING**: Konvertiert DINT (32-Bit) zu WSTRING.
- **F_LINT_AS_STRING**: Konvertiert LINT zu STRING (nicht Wide-String).

## Fazit
Der `F_LINT_AS_WSTRING`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, 64-Bit-Ganzzahlen in Wide-Strings umzuwandeln. Durch seine klare Schnittstelle und direkte Funktionsweise ist er ideal für Anwendungen, die eine Konvertierung zwischen diesen Datentypen erfordern.