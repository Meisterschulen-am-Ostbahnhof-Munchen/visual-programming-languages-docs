# F_LINT_TO_WORD

```{index} single: F_LINT_TO_WORD
```

<img width="1436" height="214" alt="F_LINT_TO_WORD" src="https://github.com/user-attachments/assets/4aa4298e-3732-42d1-a295-e26f81c02b3d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_WORD` dient der Konvertierung eines LINT-Datentyps (64-Bit Ganzzahl) in einen WORD-Datentyp (16-Bit Ganzahl). Diese Konvertierung ist nützlich, wenn Daten zwischen Systemen mit unterschiedlicher Wortbreite ausgetauscht werden müssen oder wenn eine explizite Typumwandlung erforderlich ist.

![F_LINT_TO_WORD](F_LINT_TO_WORD.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ` (Normal Execution Request): Startet die Ausführung der Konvertierung. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF` (Execution Confirmation): Signalisiert den erfolgreichen Abschluss der Konvertierung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (LINT): Der Eingangswert, der von LINT in WORD konvertiert werden soll.

### **Daten-Ausgänge**
- `OUT` (WORD): Der konvertierte Ausgangswert im WORD-Format.

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung von LINT zu WORD durch, wenn das Ereignis `REQ` ausgelöst wird. Die Konvertierung erfolgt mittels der eingebauten Funktion `LINT_TO_WORD`, die den Wert des Eingangs `IN` nimmt und ihn in den WORD-Datentyp umwandelt. Das Ergebnis wird am Ausgang `OUT` ausgegeben, und das Ereignis `CNF` signalisiert die erfolgreiche Ausführung.

## Technische Besonderheiten
- Die Konvertierung schneidet die höherwertigen Bits des LINT-Werts ab, da WORD nur 16 Bit speichern kann.
- Es gibt keine Überprüfung auf Überlauf oder Unterlauf während der Konvertierung.

## Zustandsübersicht
Der Funktionsblock ist zustandslos und führt die Konvertierung bei jedem `REQ`-Ereignis neu aus.

## Anwendungsszenarien
- Datenkommunikation zwischen Systemen mit unterschiedlicher Wortbreite.
- Explizite Typumwandlung in Steuerungsanwendungen, wo eine 64-Bit-Zahl auf eine 16-Bit-Zahl reduziert werden muss.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_DINT_TO_WORD` oder `F_INT_TO_WORD` führen ähnliche Konvertierungen durch, jedoch mit anderen Ausgangsdatentypen.
- `F_LINT_TO_WORD` ist spezifisch für die Konvertierung von 64-Bit zu 16-Bit und bietet keine zusätzliche Funktionalität wie Überlaufprüfung.

## Fazit
Der `F_LINT_TO_WORD` Funktionsblock ist ein einfaches, aber effektives Werkzeug zur Konvertierung von LINT- zu WORD-Daten. Er ist besonders nützlich in Szenarien, wo eine Reduzierung der Datenbreite erforderlich ist, ohne dass zusätzliche Überprüfungen notwendig sind.