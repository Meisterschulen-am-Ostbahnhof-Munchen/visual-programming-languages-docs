# F_STRING_AS_UDINT

```{index} single: F_STRING_AS_UDINT
```

<img width="1478" height="220" alt="F_STRING_AS_UDINT" src="https://github.com/user-attachments/assets/703603e7-5595-4570-8772-7efeb1ea4785" />

* * * * * * * * * *
## 📺 Video

* [Zusätzlich: Uebung_083: Aufwärts/Abwärts zählen: E_CTUD_UDINT Datentyp UDINT; mit Anzeige am VT.](https://www.youtube.com/watch?v=oTPDtsw5eAw)

## Einleitung
Der Funktionsblock `F_STRING_AS_UDINT` dient der Konvertierung eines `STRING`-Wertes in einen `UDINT`-Wert (unsigned double integer). Er ist Teil des Pakets `iec61131::conversion` und ermöglicht die einfache Umwandlung von Zeichenketten in numerische Werte.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Startet die Konvertierung. Der Eingang ist mit dem Daten-Eingang `IN` verbunden.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert den Abschluss der Konvertierung. Der Ausgang ist mit dem Daten-Ausgang `OUT` verbunden.

### **Daten-Eingänge**
- **IN**: Der Eingang erwartet einen `STRING`-Wert, der in einen `UDINT`-Wert umgewandelt werden soll.

### **Daten-Ausgänge**
- **OUT**: Der Ausgang liefert den konvertierten `UDINT`-Wert.

### **Adapter**
Der FB verwendet keine Adapter.

## Funktionsweise
Der Funktionsblock führt die Konvertierung mithilfe der eingebauten Funktion `STRING_AS_UDINT` durch. Bei Auslösung des Ereignisses `REQ` wird der `STRING`-Wert am Eingang `IN` in einen `UDINT`-Wert umgewandelt und am Ausgang `OUT` ausgegeben. Anschließend wird das Ereignis `CNF` ausgelöst, um den erfolgreichen Abschluss der Konvertierung zu signalisieren.

## Technische Besonderheiten
- Die Konvertierung erfolgt direkt und ohne zusätzliche Parameter.
- Der FB ist für einfache Umwandlungen optimiert und unterstützt keine komplexen Formatierungen oder Fehlerbehandlungen.

## Zustandsübersicht
1. **Idle**: Wartet auf das Ereignis `REQ`.
2. **Konvertierung**: Führt die Umwandlung durch und gibt das Ergebnis aus.
3. **Bestätigung**: Löst das Ereignis `CNF` aus und kehrt in den Idle-Zustand zurück.

## Anwendungsszenarien
- Umwandlung von Benutzereingaben oder Kommunikationsdaten in numerische Werte.
- Integration in Systeme, die numerische Verarbeitung erfordern, aber Zeichenketten als Eingabe erhalten.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu generischen Konvertierungs-FBs bietet `F_STRING_AS_UDINT` eine spezialisierte und effiziente Lösung für die Umwandlung von `STRING` zu `UDINT`.
- Andere FBs könnten zusätzliche Funktionen wie Fehlerbehandlung oder Formatierung bieten, sind jedoch komplexer in der Handhabung.

## Fazit
Der `F_STRING_AS_UDINT`-Funktionsblock ist eine einfache und effiziente Lösung für die Konvertierung von Zeichenketten in numerische Werte. Er eignet sich besonders für Anwendungen, bei denen eine schnelle und direkte Umwandlung benötigt wird.