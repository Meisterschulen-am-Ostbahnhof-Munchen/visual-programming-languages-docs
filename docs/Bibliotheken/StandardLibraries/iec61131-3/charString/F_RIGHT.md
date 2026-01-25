# F_RIGHT

```{index} single: F_RIGHT
```

<img width="1390" height="208" alt="F_RIGHT" src="https://github.com/user-attachments/assets/d39c7fe1-3c16-4c26-90c3-b78236b98380" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_RIGHT` ist ein Standard-Baustein für die Verarbeitung von Zeichenketten (Strings) nach der Norm IEC 61131-3. Er extrahiert die rechten `L` Zeichen aus der Eingabezeichenkette `IN` und gibt diese als Ergebnis `OUT` aus. Dieser Baustein ist besonders nützlich in Anwendungen, bei denen Teile von Zeichenketten verarbeitet oder analysiert werden müssen.

![F_RIGHT](F_RIGHT.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Dienst-Anforderung. Löst die Extraktion der rechten `L` Zeichen aus. Wird mit den Daten `IN` und `L` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der angeforderten Dienstleistung. Wird mit dem Ergebnis `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Eingabezeichenkette, aus der die rechten Zeichen extrahiert werden sollen. Der Datentyp ist `ANY_STRING`.
- **L**: Anzahl der Zeichen, die von rechts aus der Eingabezeichenkette extrahiert werden sollen. Der Datentyp ist `ANY_INT`.

### **Daten-Ausgänge**
- **OUT**: Ergebniszeichenkette, die die extrahierten Zeichen enthält. Der Datentyp ist `ANY_STRING`.

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Bei Auslösung des Ereignisses `REQ` wird die Eingabezeichenkette `IN` verarbeitet. Der Funktionsblock extrahiert die rechten `L` Zeichen aus `IN` und gibt das Ergebnis über den Ausgang `OUT` aus. Das Ereignis `CNF` signalisiert die erfolgreiche Verarbeitung und stellt das Ergebnis bereit.

## Technische Besonderheiten
- Unterstützt verschiedene String-Typen (`ANY_STRING`), was eine flexible Verwendung ermöglicht.
- Die Position `L` kann mit verschiedenen Integer-Typen (`ANY_INT`) angegeben werden.
- Der Baustein ist Teil des Pakets `iec61131::charString`.

## Zustandsübersicht
Der Funktionsblock hat keine internen Zustände. Die Verarbeitung erfolgt unmittelbar bei Auslösung des `REQ`-Ereignisses.

## Anwendungsszenarien
- Extraktion von Dateierweiterungen aus Dateinamen.
- Verarbeitung von festen Längenformaten, bei denen relevante Informationen am Ende der Zeichenkette stehen.
- Allgemeine Stringmanipulation in Steuerungs- und Automatisierungsanwendungen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu `F_LEFT`, der die linken Zeichen einer Zeichenkette extrahiert, bietet `F_RIGHT` die umgekehrte Funktionalität.
- Andere String-Funktionsblöcke wie `F_MID` ermöglichen die Extraktion von Teilzeichenketten aus der Mitte einer Zeichenkette, während `F_RIGHT` speziell auf die rechten Zeichen fokussiert ist.

## Fazit
Der Funktionsblock `F_RIGHT` ist ein einfacher und effektiver Baustein für die Extraktion von Zeichen vom Ende einer Zeichenkette. Seine Flexibilität in Bezug auf die unterstützten Datentypen macht ihn zu einem vielseitigen Werkzeug in der Stringverarbeitung.