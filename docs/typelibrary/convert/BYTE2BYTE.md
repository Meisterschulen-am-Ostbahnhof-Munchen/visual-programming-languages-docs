# BYTE2BYTE

<img width="1171" height="182" alt="BYTE2BYTE" src="https://github.com/user-attachments/assets/753ab5bd-f2b6-4358-82d6-724a75feb8da" />

* * * * * * * * * *
## Einleitung
Der BYTE2BYTE Funktionsblock dient zur direkten Übertragung eines Byte-Wertes vom Eingang zum Ausgang. Es handelt sich um einen einfachen Konverter, der bei Anforderung den Eingabewert unverändert an den Ausgang weiterleitet.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Löst die Ausführung des Funktionsblocks aus. Der Eingabewert IN wird mit diesem Ereignis verarbeitet.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die erfolgreiche Ausführung des Funktionsblocks. Das Ereignis wird zusammen mit dem Ausgabewert OUT ausgelöst.

### **Daten-Eingänge**
- **IN** (BYTE): Der Eingabewert, der unverändert an den Ausgang weitergeleitet wird.

### **Daten-Ausgänge**
- **OUT** (BYTE): Der Ausgabewert, der dem Eingabewert IN entspricht.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
Der Funktionsblock kopiert bei Empfang des REQ-Ereignisses den Wert des Daten-Eingangs IN unverändert auf den Daten-Ausgang OUT. Anschließend wird das CNF-Ereignis ausgelöst, um die erfolgreiche Ausführung zu bestätigen.

## Technische Besonderheiten
- Einfache, direkte Wertübertragung ohne Transformation oder Bearbeitung.
- Keine Zustandsverwaltung erforderlich, da es sich um einen statischen Funktionsblock handelt.

## Zustandsübersicht
Der Funktionsblock besitzt keine internen Zustände. Die Ausführung erfolgt unmittelbar bei Empfang des REQ-Ereignisses.

## Anwendungsszenarien
- Weiterleitung von Byte-Werten zwischen verschiedenen Komponenten eines Systems.
- Als Platzhalter oder Testkomponente in frühen Entwicklungsphasen.
- In Kombination mit anderen Funktionsblöcken zur Datenweiterleitung.

## Vergleich mit ähnlichen Bausteinen
- Ähnlich wie andere Konverter-Funktionsblöcke (z.B. INT2INT), jedoch spezialisiert auf den BYTE-Datentyp.
- Einfacher als komplexe Konverter, die zusätzliche Transformationen oder Berechnungen durchführen.

## Fazit
Der BYTE2BYTE Funktionsblock bietet eine einfache und effiziente Möglichkeit, Byte-Werte zwischen verschiedenen Teilen eines Systems weiterzuleiten. Seine Einfachheit macht ihn zu einem nützlichen Baustein in vielen Anwendungen, insbesondere dort, wo keine Datenmanipulation erforderlich ist.
