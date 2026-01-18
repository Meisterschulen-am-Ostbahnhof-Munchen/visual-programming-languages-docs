# F_UDINT_AS_STRING

```{index} single: F_UDINT_AS_STRING
```

<img width="1481" height="212" alt="F_UDINT_AS_STRING" src="https://github.com/user-attachments/assets/a7240c03-594a-4f72-a90f-85145981374e" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_UDINT_AS_STRING` dient der Konvertierung eines vorzeichenlosen 32-Bit-Integer-Werts (UDINT) in einen String (STRING). Dieser Baustein ist besonders nützlich, wenn numerische Werte für die Anzeige oder Protokollierung in eine lesbare Textform umgewandelt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Der vorzeichenlose 32-Bit-Integer-Wert (UDINT), der in einen String umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der resultierende String (STRING) nach der Konvertierung.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird der Algorithmus ausgeführt, der den Wert des Eingangs `IN` in einen String umwandelt und das Ergebnis an `OUT` ausgibt. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Operation zu signalisieren.

## Technische Besonderheiten
- Der Funktionsblock verwendet die Funktion `UDINT_AS_STRING` zur Konvertierung.
- Die Implementierung erfolgt in Structured Text (ST).

## Zustandsübersicht
1. **Initialisierung**: Der Funktionsblock ist bereit und wartet auf das `REQ`-Ereignis.
2. **Konvertierung**: Bei Empfang von `REQ` wird der Wert von `IN` konvertiert und an `OUT` ausgegeben.
3. **Bestätigung**: Das `CNF`-Ereignis wird ausgelöst, um den Abschluss der Konvertierung zu signalisieren.

## Anwendungsszenarien
- Anzeige von numerischen Werten in Benutzeroberflächen.
- Protokollierung von Messwerten in Textdateien oder Datenbanken.
- Vorbereitung von Daten für die Kommunikation über Textprotokolle (z.B. HTTP, MQTT).

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungsbausteinen bietet `F_UDINT_AS_STRING` eine spezialisierte Lösung für die Umwandlung von UDINT zu STRING.
- Andere Bausteine könnten zusätzliche Parameter wie Formatierung oder Längenbegrenzung unterstützen, was hier nicht der Fall ist.

## Fazit
Der `F_UDINT_AS_STRING` Funktionsblock ist ein einfacher und effizienter Baustein für die Konvertierung von vorzeichenlosen 32-Bit-Integern in Strings. Seine klare Schnittstelle und einfache Funktionsweise machen ihn ideal für grundlegende Konvertierungsaufgaben in Automatisierungsprojekten.