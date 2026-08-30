# F_FROM_BIG_ENDIAN

![F_FROM_BIG_ENDIAN](F_FROM_BIG_ENDIAN.svg)

* * * * * * * * * *

## Einleitung

Der `F_FROM_BIG_ENDIAN` konvertiert einen Wert aus der Big-Endian (höchstwertiges Byte zuerst)-Byte-Reihenfolge. Er gehört zur Familie der Endian-Konvertierungsfunktionen, die für den plattformübergreifenden Austausch binärer Daten (z. B. über Netzwerkprotokolle oder mit Fremdsystemen) benötigt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- **REQ**: Löst die Konvertierung aus, trägt `IN`.

### **Ereignis-Ausgänge**

- **CNF**: Bestätigt den Abschluss, trägt `OUT`.

### **Daten-Eingänge**

- **IN** (ANY): Der zu konvertierende Wert, beliebiger Datentyp.

### **Daten-Ausgänge**

- **OUT** (ANY): Der konvertierte Wert, gleicher Datentyp wie `IN`.

## Funktionsweise

Bei Eintreffen von `REQ` interpretiert die Bytefolge von `IN` als Big-Endian (höchstwertiges Byte zuerst)-kodierten Wert und wandelt sie in die native Byte-Reihenfolge der Zielplattform um. Das Ergebnis wird über `OUT` ausgegeben, anschließend wird `CNF` ausgelöst. Die Bitbreite des Datentyps bleibt dabei unverändert — es wird ausschließlich die Byte-Reihenfolge angepasst.

## Technische Besonderheiten

- **Generischer `ANY`-Datentyp**: `IN`/`OUT` passen sich an den zur Übersetzungszeit angeschlossenen konkreten Datentyp an; die Byte-Anzahl ergibt sich aus dessen Größe.
- **Reine Byte-Reihenfolge, keine Wertinterpretation**: Der Baustein ändert nur die Anordnung der Bytes, nicht deren Bedeutung oder Vorzeichen.

## Zustandsübersicht

Zustandslos: jedes `REQ` führt unmittelbar zur Konvertierung und zu `CNF`.

## Anwendungsszenarien

- **Netzwerkkommunikation**: Viele Netzwerkprotokolle (z. B. TCP/IP-Header) verwenden Big-Endian ("Network Byte Order"); `F_FROM_BIG_ENDIAN` stellt die korrekte Byte-Reihenfolge beim Senden/Empfangen sicher.
- **Interoperabilität mit Fremdsystemen**: Austausch von Binärdaten mit Systemen, die eine andere native Byte-Reihenfolge verwenden als die Zielplattform.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **`F_FROM_LITTLE_ENDIAN`**: dieselbe Konvertierungsrichtung (aus), aber für die jeweils andere Byte-Reihenfolge.
- **`F_TO_BIG_ENDIAN`**: die Gegenrichtung für dieselbe Byte-Reihenfolge.

## Fazit

`F_FROM_BIG_ENDIAN` liefert eine einfache, generisch typisierte Byte-Reihenfolgen-Konvertierung und ist ein wichtiger Baustein für die korrekte Interoperabilität mit Netzwerkprotokollen und Fremdsystemen unterschiedlicher Endianness.
