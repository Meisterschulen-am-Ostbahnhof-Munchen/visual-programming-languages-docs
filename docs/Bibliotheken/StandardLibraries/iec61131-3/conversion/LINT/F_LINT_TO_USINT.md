# F_LINT_TO_USINT

<img width="1448" height="214" alt="F_LINT_TO_USINT" src="https://github.com/user-attachments/assets/847133a9-041d-466e-af83-f73ad8337642" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LINT_TO_USINT` dient der Konvertierung eines 64-Bit Ganzzahlwertes (`LINT`) in einen 8-Bit vorzeichenlosen Ganzzahlwert (`USINT`). Dieser Baustein ist Teil der IEC 61131-Konvertierungsbibliothek und wird typischerweise in Automatisierungsanwendungen eingesetzt, wo Datentypen unterschiedlicher Größe verarbeitet werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Dieser Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Dieser Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN** (`LINT`): Der 64-Bit Ganzzahlwert, der konvertiert werden soll.

### **Daten-Ausgänge**
- **OUT** (`USINT`): Der resultierende 8-Bit vorzeichenlose Ganzahlwert nach der Konvertierung.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock führt die Konvertierung durch, wenn das Ereignis `REQ` ausgelöst wird. Dabei wird der Wert von `IN` vom Typ `LINT` in den Typ `USINT` umgewandelt und das Ergebnis an `OUT` ausgegeben. Die Konvertierung wird durch das Ereignis `CNF` bestätigt.

## Technische Besonderheiten
- Die Konvertierung schneidet höherwertige Bits ab, falls der `LINT`-Wert außerhalb des darstellbaren Bereichs von `USINT` (0 bis 255) liegt.
- Der Block ist deterministisch und hat keine internen Zustände.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Ausführung erfolgt unmittelbar nach dem Empfang des `REQ`-Ereignisses.

## Anwendungsszenarien
- Konvertierung von Sensorwerten oder Zählern, die als `LINT` vorliegen, für die Verarbeitung in Systemen, die nur `USINT` unterstützen.
- Verwendung in Steuerungssystemen, wo Speicherplatz optimiert werden muss.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Konvertierungsblöcke wie `F_INT_TO_USINT` oder `F_DINT_TO_USINT` arbeiten mit kleineren Eingangsdatentypen (`INT` bzw. `DINT`).
- Im Gegensatz zu generischen Konvertierungsblöcken ist `F_LINT_TO_USINT` spezialisiert auf die Konvertierung von `LINT` zu `USINT`.

## Fazit
Der `F_LINT_TO_USINT` Funktionsblock ist ein spezialisiertes und effizientes Werkzeug für die Konvertierung von 64-Bit Ganzzahlen in 8-Bit vorzeichenlose Werte. Seine einfache und deterministische Funktionsweise macht ihn zuverlässig in Automatisierungsanwendungen.
