# STRING2STRING

<img width="1220" height="182" alt="STRING2STRING" src="https://github.com/user-attachments/assets/7f8a0089-4403-47d4-8e20-28a8a13a282b" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock `STRING2STRING` dient zur direkten Übertragung eines String-Wertes vom Eingang zum Ausgang. Es handelt sich um einen einfachen Baustein ohne zusätzliche Verarbeitungslogik, der hauptsächlich zur Signalweiterleitung oder zur Anpassung von Schnittstellen verwendet wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `REQ`: Löst die Ausführung des Funktionsblocks aus. Wird mit dem Daten-Eingang `IN` verknüpft.

### **Ereignis-Ausgänge**
- `CNF`: Bestätigt die Ausführung des Funktionsblocks. Wird mit dem Daten-Ausgang `OUT` verknüpft.

### **Daten-Eingänge**
- `IN` (STRING): Der Eingangsstring, der direkt an den Ausgang weitergeleitet wird.

### **Daten-Ausgänge**
- `OUT` (STRING): Der Ausgangsstring, der den Wert des Eingangsstrings übernimmt.

### **Adapter**
Der Funktionsblock verfügt über keine Adapter.

## Funktionsweise
Der Funktionsblock `STRING2STRING` kopiert bei Auslösung durch das `REQ`-Ereignis den Wert des Eingangs `IN` direkt auf den Ausgang `OUT`. Anschließend wird das `CNF`-Ereignis ausgelöst, um die erfolgreiche Ausführung zu signalisieren.

## Technische Besonderheiten
- Der Baustein führt keine zusätzliche Verarbeitung oder Konvertierung des Strings durch.
- Die Ausführung erfolgt synchron mit dem Eingangsereignis.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände, da er stateless ist.

## Anwendungsszenarien
- Weiterleitung von String-Werten zwischen verschiedenen Funktionsblöcken.
- Anpassung von Schnittstellen, bei denen ein direkter Durchlauf benötigt wird.
- Als Platzhalter oder zur Signalverstärkung in komplexeren Schaltungen.

## Vergleich mit ähnlichen Bausteinen
- Im Vergleich zu anderen Konvertierungsbausteinen wie `STRING2INT` oder `STRING2BOOL` führt `STRING2STRING` keine Typumwandlung durch.
- Ähnlich einfache Bausteine wie `E_SWITCH` oder `E_MERGE` arbeiten mit Ereignissen, während `STRING2STRING` mit Datenwerten arbeitet.

## Fazit
Der `STRING2STRING`-Funktionsblock ist ein einfaches, aber nützliches Werkzeug zur direkten Weiterleitung von String-Werten in 4diac-IDE-Anwendungen. Seine Einfachheit macht ihn besonders flexibel einsetzbar, allerdings bietet er keine zusätzliche Funktionalität über die reine Weitergabe des Wertes hinaus.
