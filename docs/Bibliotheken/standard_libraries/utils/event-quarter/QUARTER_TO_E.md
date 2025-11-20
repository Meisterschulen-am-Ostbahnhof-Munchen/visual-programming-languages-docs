# QUARTER_TO_E

![QUARTER_TO_E](https://github.com/user-attachments/assets/720ecd6c-2fb4-4633-a85c-a4725625eb61)

* * * * * * * * * *
## Einleitung
Der Funktionsblock QUARTER_TO_E dient zur Umwandlung eines 2-Bit-Zustands (ein "Quarter Byte") in vier verschiedene Ereignisausgänge. Er ist besonders nützlich für Steuerungsanwendungen, bei denen ein Eingangszustand in spezifische Ereignisse übersetzt werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Normaler Ausführungsanforderung. Wird mit dem Daten-Eingang `IB` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Ausführungsbestätigung. Wird mit dem Daten-Ausgang `Q` verknüpft.
- **S**: Aktiviert (ein, aktiv, etc.).
- **R**: Deaktiviert (aus, passiv, etc.).
- **ERR**: Fehlerindikator.
- **NONE**: Nicht verfügbar oder nicht installiert.

### **Daten-Eingänge**
- **IB**: Ein 2-Bit-Eingang (Byte-Typ) mit vier Zuständen. Initialwert: `quarter::COMMAND_DISABLE`.

### **Daten-Ausgänge**
- **Q**: Boolescher Ausgang.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock übersetzt den Eingangszustand `IB` in eines der vier möglichen Ereignisse (`S`, `R`, `ERR`, `NONE`). Abhängig vom Zustand von `IB` wird der entsprechende Ereignisausgang ausgelöst und der boolesche Ausgang `Q` entsprechend gesetzt oder zurückgesetzt.

## Technische Besonderheiten
- Verwendet einen 2-Bit-Eingang (`IB`) zur Darstellung von vier Zuständen.
- Initialzustand ist `START`, von dem aus je nach Eingangszustand in die entsprechenden Zustände (`SET`, `RESET`, `Error`, `none`) gewechselt wird.
- Nach der Ausführung eines Zustands wird immer der Zustand `ok` erreicht, von dem aus zurück zum Initialzustand `START` gewechselt wird.

## Zustandsübersicht
1. **START**: Initialzustand.
2. **SET**: Wird bei `IB = quarter::STATUS_ENABLED` erreicht. Setzt `Q` auf `TRUE` und löst `S` aus.
3. **RESET**: Wird bei `IB = quarter::STATUS_DISABLED` erreicht. Setzt `Q` auf `FALSE` und löst `R` aus.
4. **Error**: Wird bei `IB = quarter::STATUS_ERROR` erreicht. Setzt `Q` auf `FALSE` und löst `ERR` aus.
5. **none**: Wird bei `IB = quarter::STATUS_NOT_AVAILABLE` erreicht. Löst `NONE` aus ohne `Q` zu ändern.
6. **ok**: Bestätigungszustand, von dem aus zurück zu `START` gewechselt wird.

## Anwendungsszenarien
- Steuerung von Maschinenzuständen (ein/aus, Fehler, nicht verfügbar).
- Übersetzung von Hardwarezuständen in logische Ereignisse.
- Fehlerbehandlung und Zustandsüberwachung.

## Vergleich mit ähnlichen Bausteinen
- Ähnlich zu Zustandsmaschinen, aber spezialisiert auf die Übersetzung von 2-Bit-Eingängen in Ereignisse.
- Im Vergleich zu generischen Zustandsmaschinen bietet QUARTER_TO_E eine vordefinierte Logik für spezifische Zustände.

## Fazit
QUARTER_TO_E ist ein spezialisierter Funktionsblock zur effizienten Übersetzung von 2-Bit-Zuständen in Ereignisse. Er eignet sich besonders für Anwendungen, bei denen klare Zustandsübergänge und Ereignisauslösungen benötigt werden.
