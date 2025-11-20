# F_MID

<img width="1158" height="232" alt="F_MID" src="https://github.com/user-attachments/assets/0f4a4667-023e-4ada-8ea0-2df3b494c7db" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `F_MID` dient zur Extraktion einer Teilzeichenkette aus einer gegebenen Zeichenkette. Dabei wird eine bestimmte Anzahl von Zeichen ab einer definierten Startposition extrahiert. Der FB ist Teil der Standard-Charakter- und String-Funktionen gemäß IEC 61131-3.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ**: Service-Anfrage zur Ausführung der Extraktion. Wird mit den Daten-Eingängen `IN`, `L` und `P` verknüpft.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung der erfolgreichen Ausführung der Anfrage. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- **IN**: Die Eingabezeichenkette, aus der die Teilzeichenkette extrahiert werden soll (Typ: `ANY_STRING`).
- **L**: Die Länge der zu extrahierenden Teilzeichenkette (Typ: `ANY_INT`).
- **P**: Die Startposition, ab der die Extraktion beginnen soll (Typ: `ANY_INT`).

### **Daten-Ausgänge**
- **OUT**: Die extrahierte Teilzeichenkette (Typ: `ANY_STRING`).

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock `F_MID` extrahiert eine Teilzeichenkette aus der Eingabezeichenkette `IN`. Die Extraktion beginnt an der Position `P` und umfasst `L` Zeichen. Das Ergebnis wird über den Ausgang `OUT` ausgegeben, sobald der Ereignisausgang `CNF` ausgelöst wird.

## Technische Besonderheiten
- Der FB unterstützt beliebige String-Typen (`ANY_STRING`) und Integer-Typen (`ANY_INT`).
- Die Startposition `P` und die Länge `L` müssen gültige Werte innerhalb der Länge der Eingabezeichenkette sein, um korrekte Ergebnisse zu gewährleisten.

## Zustandsübersicht
1. **Initialisierung**: Der FB wartet auf eine Anfrage über `REQ`.
2. **Verarbeitung**: Bei Empfang von `REQ` werden die Eingabedaten verarbeitet und die Teilzeichenkette extrahiert.
3. **Ausgabe**: Die extrahierte Teilzeichenkette wird über `OUT` ausgegeben und `CNF` wird ausgelöst.

## Anwendungsszenarien
- Extraktion von Teilzeichenketten aus längeren Texten oder Datenstrings.
- Verwendung in String-Verarbeitungsroutinen, z.B. zur Parsing von Datenformaten.

## Vergleich mit ähnlichen Bausteinen
- Ähnliche Funktionsblöcke wie `F_LEFT` oder `F_RIGHT` extrahieren Teilzeichenketten vom Anfang oder Ende einer Zeichenkette, während `F_MID` eine flexible Extraktion ab einer beliebigen Position ermöglicht.

## Fazit
Der `F_MID`-Funktionsblock bietet eine einfache und effiziente Möglichkeit, Teilzeichenketten aus einer gegebenen Zeichenkette zu extrahieren. Seine Flexibilität und Kompatibilität mit verschiedenen String- und Integer-Typen machen ihn zu einem nützlichen Werkzeug in der String-Verarbeitung.
