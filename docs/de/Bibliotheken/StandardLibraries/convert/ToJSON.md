# ToJSON

![ToJSON](ToJSON.svg)

* * * * * * * * * *
## Einleitung

Der `ToJSON`-Funktionsblock fügt ein benanntes Feld mit einem Wert zu einem JSON-String hinzu. Ist `JSONIn` leer, wird ein neues JSON-Objekt mit genau diesem einen Feld erstellt — durch mehrfaches Verketten mehrerer `ToJSON`-Aufrufe (`JSONOut` des einen als `JSONIn` des nächsten) lässt sich so schrittweise ein vollständiges JSON-Objekt aufbauen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst das Hinzufügen aus, trägt `JSONIn`, `Value` und `FieldName`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `JSONOut`.

### **Daten-Eingänge**

- **JSONIn** (STRING): Der bestehende JSON-String, dem ein Feld hinzugefügt wird (bei leerem String wird ein neues Objekt erstellt).
- **Value** (ANY): Der zu speichernde Wert, generisch typisiert.
- **FieldName** (STRING): Der Schlüssel (Feldname), unter dem `Value` gespeichert wird.

### **Daten-Ausgänge**

- **JSONOut** (STRING): Der aktualisierte JSON-String mit dem neu hinzugefügten Feld.

## Funktionsweise

Bei Eintreffen von `REQ` prüft der Baustein `JSONIn`: Ist der String leer, wird ein neues JSON-Objekt `{"FieldName": Value}` erzeugt; andernfalls wird das Feld `FieldName` mit `Value` in das bestehende Objekt eingefügt (bzw. ein vorhandenes Feld gleichen Namens überschrieben). Das Ergebnis wird über `JSONOut` ausgegeben, anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **ANY-Eingabetyp**: `Value` akzeptiert generisch Zahlen, Zeichenketten und boolesche Werte, die entsprechend in den JSON-Datentyp übersetzt werden.
- **Verkettbar**: Da `JSONOut` denselben Typ wie `JSONIn` hat, lassen sich mehrere `ToJSON`-Instanzen hintereinanderschalten, um ein JSON-Objekt mit mehreren Feldern Schritt für Schritt aufzubauen.
- **Leerer `JSONIn` erzeugt neues Objekt**: Kein separater "Create"-Baustein nötig — der erste Aufruf einer Verkettung kann direkt mit leerem `JSONIn` beginnen.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Feld-Einfügung und zu `CNF`.

## Anwendungsszenarien

- **Aufbau von JSON-Nutzlasten**: Für den Versand an eine REST-API oder ein MQTT-Topic wird schrittweise ein JSON-Objekt aus mehreren Prozesswerten zusammengesetzt.
- **Protokollierung**: Strukturierte Log-Einträge im JSON-Format, bei denen einzelne Felder aus verschiedenen Programmteilen ergänzt werden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[ReadJSON](ReadJSON.md)**: die Gegenrichtung — extrahiert ein Feld aus einem JSON-String.
- **`SET_STRUCT_VALUE`**: setzt ein Feld in einer IEC-61131-3-STRUCT statt in einem JSON-String.

## Fazit

`ToJSON` ermöglicht den schrittweisen, verkettbaren Aufbau von JSON-Strings aus einzelnen Feld/Wert-Paaren und eignet sich für die Erstellung von JSON-Nutzlasten in 4diac-Anwendungen, ohne eine vollständige Struktur-Typdefinition zu benötigen.
