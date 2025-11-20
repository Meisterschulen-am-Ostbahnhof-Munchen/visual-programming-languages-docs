# F_LEN

<img width="1366" height="211" alt="F_LEN" src="https://github.com/user-attachments/assets/ca04179e-54ed-4419-aee6-51c03a2829a8" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_LEN` dient zur Bestimmung der Länge eines Eingabe-Strings. Er ist Teil der Standard-Bibliothek für Zeichen- und String-Funktionen gemäß IEC 61131-3.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Service-Anfrage. Wird dieses Ereignis ausgelöst, beginnt die Berechnung der String-Länge.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigung der Service-Anfrage. Wird ausgelöst, sobald die Berechnung abgeschlossen ist.

### **Daten-Eingänge**
- `IN` (ANY_STRING): Der Eingabe-String, dessen Länge bestimmt werden soll.

### **Daten-Ausgänge**
- `OUT` (ANY_INT): Die Länge des Eingabe-Strings.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock `F_LEN` berechnet die Länge des übergebenen Strings (`IN`) und gibt das Ergebnis als Integer (`OUT`) aus. Die Berechnung wird durch das Ereignis `REQ` gestartet und durch `CNF` bestätigt.

## Technische Besonderheiten
- Unterstützt alle String-Typen (`ANY_STRING`).
- Gibt die Länge als beliebigen Integer-Typ (`ANY_INT`) zurück.

## Zustandsübersicht
1. **Idle-Zustand**: Wartet auf das `REQ`-Ereignis.
2. **Berechnungszustand**: Berechnet die Länge des Strings.
3. **Bestätigungszustand**: Sendet das `CNF`-Ereignis mit der berechneten Länge.

## Anwendungsszenarien
- Überprüfung der Länge von Benutzereingaben.
- Validierung von String-Daten vor der weiteren Verarbeitung.
- Logging und Debugging von String-Operationen.

## Vergleich mit ähnlichen Bausteinen
- Ähnlich zu `LEN` in anderen Programmiersprachen, jedoch als standardisierter Funktionsblock in IEC 61131-3.
- Im Gegensatz zu `F_MID` oder `F_LEFT`, die Teile eines Strings extrahieren, liefert `F_LEN` nur die Länge.

## Fazit
Der `F_LEN`-Funktionsblock ist ein einfaches, aber essentielles Werkzeug zur String-Verarbeitung in IEC 61131-3-Umgebungen. Seine klare Schnittstelle und einfache Funktionsweise machen ihn zu einem zuverlässigen Baustein für diverse Anwendungen.
