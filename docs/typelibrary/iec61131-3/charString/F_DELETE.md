# F_DELETE

<img width="1068" height="196" alt="F_DELETE" src="https://github.com/user-attachments/assets/bf84dd90-6f79-4860-924b-8bfa70fcafcc" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_DELETE` dient zur Manipulation von Zeichenketten. Er entfernt eine bestimmte Anzahl von Zeichen (`L`) aus einer Eingabezeichenkette (`IN`), beginnend an einer definierten Position (`P`). Das Ergebnis wird als neue Zeichenkette (`OUT`) ausgegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Verarbeitung des Funktionsblocks. Die zugehörigen Daten sind `IN`, `L` und `P`.

### **Ereignis-Ausgänge**
- **CNF**: Signalisiert die erfolgreiche Verarbeitung und liefert das Ergebnis `OUT`.

### **Daten-Eingänge**
- **IN**: Die Eingabezeichenkette, aus der Zeichen entfernt werden sollen (Typ: `ANY_STRING`).
- **L**: Die Anzahl der zu entfernenden Zeichen (Typ: `ANY_INT`).
- **P**: Die Startposition, ab der Zeichen entfernt werden sollen (Typ: `ANY_INT`).

### **Daten-Ausgänge**
- **OUT**: Die resultierende Zeichenkette nach dem Entfernen der Zeichen (Typ: `ANY_STRING`).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
1. Der Funktionsblock wird durch das Ereignis `REQ` aktiviert.
2. Aus der Zeichenkette `IN` werden `L` Zeichen beginnend an Position `P` entfernt.
3. Das Ergebnis wird in `OUT` gespeichert und das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten
- Der Funktionsblock unterstützt verschiedene String-Typen (`ANY_STRING`), was eine flexible Verwendung ermöglicht.
- Die Position `P` und die Länge `L` müssen gültige Werte innerhalb der Länge von `IN` sein, um korrekte Ergebnisse zu gewährleisten.

## Zustandsübersicht
1. **Idle**: Wartet auf das Ereignis `REQ`.
2. **Processing**: Verarbeitet die Eingabedaten und entfernt die Zeichen.
3. **Completed**: Gibt das Ergebnis aus und signalisiert `CNF`.

## Anwendungsszenarien
- Bereinigung von Benutzereingaben.
- Verarbeitung von Protokoll- oder Log-Daten.
- Manipulation von Textdaten in automatisierten Prozessen.

## Vergleich mit ähnlichen Bausteinen
- **F_INSERT**: Fügt Zeichen an einer bestimmten Position ein.
- **F_REPLACE**: Ersetzt Zeichen in einer Zeichenkette.
- **F_SUBSTRING**: Extrahiert einen Teilstring aus einer Zeichenkette.

## Fazit
Der `F_DELETE` Funktionsblock ist ein nützliches Werkzeug zur Bearbeitung von Zeichenketten in der 4diac-IDE. Durch seine einfache und flexible Schnittstelle kann er in verschiedenen Anwendungen eingesetzt werden, um Zeichen aus Strings zu entfernen.
