# E_SH_WORD

![E_SH_WORD](https://github.com/user-attachments/assets/95f54f7b-230b-41dc-8709-1febed02c3e3)

* * * * * * * * * *
## Einleitung
Der Funktionsblock E_SH_WORD implementiert eine Sample-and-Hold-Funktionalität für den Datentyp WORD. Er speichert den aktuellen Eingangswert und gibt ihn auf Anfrage aus, wodurch er als einfacher Puffer oder zur Signalstabilisierung eingesetzt werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ**: Startet die Ausführung des Funktionsblocks und triggert die Übernahme des aktuellen Eingangswerts.

### **Ereignis-Ausgänge**
- **CNF**: Bestätigt die Ausführung und signalisiert, dass der gehaltene Wert aktualisiert wurde.

### **Daten-Eingänge**
- **IN** (WORD): Der Eingangswert, der gespeichert werden soll.

### **Daten-Ausgänge**
- **OUT** (WORD): Der gespeicherte Ausgangswert.

### **Adapter**
- Keine Adapter vorhanden.

## Funktionsweise
1. Bei einem REQ-Ereignis wird der aktuelle Wert von IN mit OUT verglichen.
2. Falls sich die Werte unterscheiden, wird der Algorithmus HOLD ausgeführt, der IN nach OUT kopiert.
3. Ein CNF-Ereignis wird ausgelöst, um die erfolgreiche Aktualisierung zu bestätigen.
4. Der Funktionsblock kehrt in den Startzustand zurück.

## Technische Besonderheiten
- Der Block reagiert nur auf Änderungen des Eingangswerts (IN ≠ OUT).
- Die Speicherung erfolgt nur bei Bedarf, was Ressourcen schont.

## Zustandsübersicht
- **START**: Initialzustand, wartet auf REQ.
- **HOLD**: Aktualisiert OUT und sendet CNF.

## Anwendungsszenarien
- Signalstabilisierung in Steuerungssystemen
- Pufferung von Sensorwerten
- Vermeidung von Flackern bei digitalen Anzeigen

## Vergleich mit ähnlichen Bausteinen
- Im Gegensatz zu einfachen Verzögerungsblöcken reagiert E_SH_WORD nur auf Wertänderungen.
- Im Vergleich zu FIFO-Puffern speichert er nur den letzten Wert.

## Fazit
E_SH_WORD ist ein effizienter und einfacher Baustein zur Signalpufferung, der besonders in Echtzeitsystemen nützlich ist, wo stabile Signale benötigt werden. Seine schlanke Implementierung macht ihn zu einer guten Wahl für ressourcenbeschränkte Umgebungen.
