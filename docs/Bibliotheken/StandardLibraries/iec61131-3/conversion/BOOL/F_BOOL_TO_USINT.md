# F_BOOL_TO_USINT

```{index} single: F_BOOL_TO_USINT
```

<img width="1450" height="212" alt="F_BOOL_TO_USINT" src="https://github.com/user-attachments/assets/72e9600a-837a-49a8-b423-6f5380816310" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_BOOL_TO_USINT` dient der Konvertierung eines booleschen Wertes (`BOOL`) in einen vorzeichenlosen 8-Bit-Integer (`USINT`). Diese Konvertierung ist nützlich, wenn boolesche Werte in numerischen Operationen oder für die Kommunikation mit Systemen verwendet werden müssen, die keine booleschen Werte direkt unterstützen.

![F_BOOL_TO_USINT](F_BOOL_TO_USINT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Ereigniseingang ist mit dem Dateneingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ereignisausgang ist mit dem Datenausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der boolesche Eingangswert (`BOOL`), der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT**: Der konvertierte vorzeichenlose 8-Bit-Integer (`USINT`).

### **Adapter**
Dieser Funktionsblock verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, indem er den booleschen Wert `IN` in einen numerischen Wert umwandelt:
- `FALSE` wird zu `0` konvertiert.
- `TRUE` wird zu `1` konvertiert.

Die Konvertierung wird durch das Ereignis `REQ` ausgelöst und das Ergebnis wird über den Ausgang `OUT` ausgegeben, begleitet von dem Bestätigungsereignis `CNF`.

## Technische Besonderheiten
- Der Funktionsblock ist ein einfacher Funktionsblock (`SimpleFB`) und führt die Konvertierung in einem einzigen Algorithmus aus.
- Die Konvertierung erfolgt direkt und ohne Verzögerung, sobald das `REQ`-Ereignis eintrifft.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Konvertierung erfolgt unmittelbar bei Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Umwandlung von booleschen Schaltzuständen in numerische Werte für die Verarbeitung in mathematischen Operationen.
- Kommunikation mit Systemen oder Geräten, die boolesche Werte nicht direkt unterstützen, aber numerische Werte verarbeiten können.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsfunktionsblöcken wie `F_BOOL_TO_INT` oder `F_BOOL_TO_UINT` ist `F_BOOL_TO_USINT` spezifisch für die Konvertierung in einen vorzeichenlosen 8-Bit-Integer optimiert.
- Ähnliche Funktionsblöcke können größere oder vorzeichenbehaftete Integer-Typen verwenden, was je nach Anwendungsfall mehr oder weniger geeignet sein kann.

## Fazit
Der `F_BOOL_TO_USINT`-Funktionsblock ist ein einfaches und effizientes Werkzeug zur Konvertierung von booleschen Werten in vorzeichenlose 8-Bit-Integer. Seine direkte und verzögerungsfreie Funktionsweise macht ihn ideal für Echtzeitanwendungen, bei denen schnelle und zuverlässige Konvertierungen erforderlich sind.