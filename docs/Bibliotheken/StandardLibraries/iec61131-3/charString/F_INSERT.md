# F_INSERT

```{index} single: F_INSERT
```

<img width="1330" height="232" alt="F_INSERT" src="https://github.com/user-attachments/assets/a4d23188-0238-4c4c-a6b8-f51a6a493b1c" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_INSERT` dient zur Manipulation von Zeichenketten. Er fügt eine Zeichenkette (`IN2`) in eine andere Zeichenkette (`IN1`) an einer bestimmten Position (`P`) ein. Der Block ist Teil der Standard-Charakter- und String-Funktionen gemäß IEC 61131-3.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Dienst-Anfrage. Löst die Ausführung des Funktionsblocks aus. Wird mit den Daten-Eingängen `IN1`, `IN2` und `P` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung der angeforderten Dienstleistung. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN1` (`ANY_STRING`): Die erste Eingabezeichenkette, in die `IN2` eingefügt wird.
- `IN2` (`ANY_STRING`): Die zweite Eingabezeichenkette, die in `IN1` eingefügt wird.
- `P` (`ANY_INT`): Die Position in `IN1`, an der `IN2` eingefügt werden soll.

### **Daten-Ausgänge**
- `OUT` (`ANY_STRING`): Die resultierende Zeichenkette nach dem Einfügevorgang.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird die Zeichenkette `IN2` in die Zeichenkette `IN1` an der durch `P` definierten Position eingefügt. Das Ergebnis dieser Operation wird über den Daten-Ausgang `OUT` ausgegeben und das Ereignis `CNF` wird ausgelöst, um die erfolgreiche Bearbeitung zu signalisieren.

## Technische Besonderheiten
- Unterstützt alle String-Typen (`ANY_STRING`), was eine flexible Verwendung ermöglicht.
- Die Position `P` kann jeder ganzzahlige Wert sein (`ANY_INT`), muss jedoch innerhalb der Länge von `IN1` liegen, um ein definiertes Verhalten zu gewährleisten.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Operation wird bei jedem `REQ`-Ereignis neu ausgeführt.

## Anwendungsszenarien
- Textverarbeitung in Automatisierungsanwendungen.
- Dynamische Erstellung von Log-Nachrichten oder Benachrichtigungen.
- Manipulation von Datenstrings vor der Weiterverarbeitung oder Ausgabe.

## Vergleich mit ähnlichen Bausteinen
- Ähnlich zu `F_CONCAT`, das jedoch zwei Strings nur aneinanderhängt, ohne eine spezifische Einfügeposition zu berücksichtigen.
- Im Gegensatz zu `F_MID`, das Teile eines Strings extrahiert, fügt `F_INSERT` einen String in einen anderen ein.

## Fazit
`F_INSERT` ist ein nützlicher Funktionsblock für Anwendungen, die eine präzise Manipulation von Zeichenketten erfordern. Seine einfache, aber effektive Funktionalität macht ihn zu einem wertvollen Werkzeug in der Automatisierungstechnik.
