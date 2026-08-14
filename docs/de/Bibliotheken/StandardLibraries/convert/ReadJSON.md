# ReadJSON

![ReadJSON](ReadJSON.svg)

* * * * * * * * * *
## Einleitung

Der `ReadJSON`-Funktionsblock extrahiert den Wert eines benannten Felds aus einem JSON-String. Er dient als einfacher, ereignisgesteuerter JSON-Decoder für Anwendungsfälle, in denen ein einzelnes Feld aus einer JSON-Struktur ausgelesen werden soll, ohne die gesamte Struktur in dedizierte IEC-61131-3-Datentypen abbilden zu müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst das Auslesen aus, trägt `JSONIn` und `FieldName`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `Value`.

### **Daten-Eingänge**

- **JSONIn** (STRING): Der zu durchsuchende JSON-String.
- **FieldName** (STRING): Der Name des zu extrahierenden Felds.

### **Daten-Ausgänge**

- **Value** (ANY): Der extrahierte Feldwert, generisch typisiert.

## Funktionsweise

Bei Eintreffen von `REQ` durchsucht der Baustein `JSONIn` nach dem Feld `FieldName` und gibt dessen Wert über `Value` aus. Da `Value` vom Typ `ANY` ist, kann der extrahierte Wert je nach JSON-Inhalt als Zahl, Zeichenkette oder boolescher Wert interpretiert werden. Anschließend wird `CNF` ausgelöst.

## Technische Besonderheiten

- **ANY-Rückgabetyp**: `Value` passt sich generisch an den tatsächlichen JSON-Feldtyp an, muss aber beim Anschluss an eine konkret typisierte Variable mit deren Typ kompatibel sein.
- **Einzelfeld-Extraktion**: Der Baustein liest genau ein benanntes Feld pro Aufruf; verschachtelte oder mehrere Felder erfordern mehrere `ReadJSON`-Aufrufe oder -Instanzen.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Extraktion und zu `CNF`.

## Anwendungsszenarien

- **Konfigurationsauslesen**: Ein per Netzwerk oder Datei empfangener JSON-Konfigurationsstring soll ausgewertet werden, ohne eine vollständige STRUCT-Definition anzulegen.
- **Kommunikation mit REST-/Web-Schnittstellen**: Antworten von HTTP-APIs, die JSON liefern, können feldweise ausgelesen werden.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **[ToJSON](ToJSON.md)**: die Gegenrichtung — fügt ein Feld zu einem JSON-String hinzu bzw. erstellt einen neuen.
- **`GET_STRUCT_VALUE`**: liest ein Feld aus einer IEC-61131-3-STRUCT statt aus einem JSON-String.

## Fazit

`ReadJSON` liefert einen einfachen, feldweisen JSON-Decoder für 4diac-Anwendungen, die mit JSON-basierten Konfigurationen oder Web-Schnittstellen kommunizieren, ohne dafür eine vollständige Struktur-Typdefinition zu benötigen.
