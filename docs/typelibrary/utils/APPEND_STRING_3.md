# APPEND_STRING_3

![APPEND_STRING_3](https://github.com/user-attachments/assets/5b8f89b4-0436-4ec9-bf1b-e33feea39fdd)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `APPEND_STRING_3` dient zur Verkettung von drei Eingabewerten zu einem einzigen String. Die Eingabewerte können von beliebigem Datentyp (`ANY`) sein und werden automatisch in Strings konvertiert. Der Block ist besonders nützlich, wenn verschiedene Datentypen zu einer lesbaren Ausgabe kombiniert werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dienst-Anforderung. Löst die Verkettung der Eingabewerte aus. Wird mit den Daten-Eingängen `IN_1`, `IN_2` und `IN_3` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der Dienstausführung. Wird nach erfolgreicher Verkettung ausgelöst und liefert den verketteten String über den Daten-Ausgang `OUT`.

### **Daten-Eingänge**
- **IN_1**: Erster Eingabewert (beliebiger Datentyp, wird zu String konvertiert).
- **IN_2**: Zweiter Eingabewert (beliebiger Datentyp, wird zu String konvertiert).
- **IN_3**: Dritter Eingabewert (beliebiger Datentyp, wird zu String konvertiert).

### **Daten-Ausgänge**
- **OUT**: Verketteter Ausgabe-String, bestehend aus den konvertierten Werten von `IN_1`, `IN_2` und `IN_3`.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
1. Bei Empfang des Ereignisses `REQ` werden die Werte der Daten-Eingänge `IN_1`, `IN_2` und `IN_3` gelesen.
2. Die Werte werden automatisch in Strings konvertiert.
3. Die Strings werden in der Reihenfolge `IN_1` + `IN_2` + `IN_3` verkettet.
4. Das Ergebnis wird über den Daten-Ausgang `OUT` ausgegeben und das Ereignis `CNF` signalisiert.

## Technische Besonderheiten
- Unterstützt beliebige Datentypen (`ANY`) für die Eingabewerte.
- Automatische Konvertierung der Eingabewerte in Strings.
- Einfache und direkte Verkettung ohne zusätzliche Formatierung.

## Zustandsübersicht
- **Idle**: Wartet auf das Ereignis `REQ`.
- **Processing**: Verarbeitet die Eingabewerte und führt die Verkettung durch.
- **Done**: Signalisiert `CNF` mit dem Ergebnis.

## Anwendungsszenarien
- Erstellung von Log-Meldungen aus verschiedenen Datentypen.
- Kombination von Sensorwerten oder Statusinformationen zu einer lesbaren Ausgabe.
- Generierung von benutzerdefinierten Nachrichten oder Befehlen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `CONCAT_STRING` (nur zwei Eingänge) bietet `APPEND_STRING_3` drei Eingänge für mehr Flexibilität.
- Ähnlich zu `FORMAT_STRING`, jedoch ohne zusätzliche Formatierungsoptionen.

## Fazit
Der `APPEND_STRING_3`-Block ist ein einfacher und effizienter Baustein zur Verkettung von drei Werten unterschiedlicher Datentypen. Durch die automatische Konvertierung und direkte Verkettung eignet er sich ideal für schnelle String-Operationen in Steuerungsanwendungen.
