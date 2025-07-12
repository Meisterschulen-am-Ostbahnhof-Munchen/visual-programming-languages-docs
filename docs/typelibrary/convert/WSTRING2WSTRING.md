# WSTRING2WSTRING

<img width="1246" height="182" alt="WSTRING2WSTRING" src="https://github.com/user-attachments/assets/32a9935b-212b-4488-bfb7-9aa23dcc1aa5" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `WSTRING2WSTRING` dient der einfachen Übertragung eines WSTRING-Wertes vom Eingang zum Ausgang. Es handelt sich um einen grundlegenden Baustein ohne zusätzliche Verarbeitungslogik, der primär zur Weiterleitung von WSTRING-Daten in Automatisierungsanwendungen eingesetzt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Startet die Ausführung des Funktionsblocks und überträgt den Wert von `IN` zu `OUT`.

### **Ereignis-Ausgänge**
- `CNF`: Signalisiert den Abschluss der Ausführung und gibt den aktualisierten Wert von `OUT` aus.

### **Daten-Eingänge**
- `IN` (WSTRING): Der Eingangswert, der zum Ausgang weitergeleitet wird.

### **Daten-Ausgänge**
- `OUT` (WSTRING): Der Ausgangswert, der mit dem Wert von `IN` überschrieben wird.

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock kopiert bei jedem Empfang eines `REQ`-Ereignisses den Wert des Eingangs `IN` direkt auf den Ausgang `OUT` und bestätigt die Ausführung mit einem `CNF`-Ereignis. Es findet keine zusätzliche Verarbeitung oder Transformation der Daten statt.

## Technische Besonderheiten
- Der Block ist für den Umgang mit WSTRING-Daten optimiert.
- Keine zusätzliche Logik oder Fehlerbehandlung vorhanden.

## Zustandsübersicht
Der Funktionsblock besitzt keinen internen Zustand. Jede Ausführung ist unabhängig von vorherigen Aufrufen.

## Anwendungsszenarien
- Weiterleitung von WSTRING-Daten zwischen verschiedenen Funktionsblöcken.
- Einfache Datenübertragung in Automatisierungsanwendungen.
- Als Platzhalter oder Testkomponente in größeren Systemen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu komplexeren Konvertierungsblöcken bietet `WSTRING2WSTRING` keine Datenumwandlung oder -verarbeitung.
- Ähnlich einfache Blöcke für andere Datentypen (z.B. `INT2INT`) folgen demselben Prinzip.

## Fazit
Der `WSTRING2WSTRING`-Funktionsblock ist ein einfaches, aber nützliches Werkzeug zur direkten Weiterleitung von WSTRING-Daten in 4diac-IDE-Anwendungen. Seine Einfachheit macht ihn zu einer zuverlässigen Komponente für grundlegende Datenübertragungsaufgaben.
