# AB2_BYTE_TO_B

<img width="1224" height="196" alt="image" src="https://github.com/user-attachments/assets/d26afea7-42a5-4d51-b83f-a5b1dff4166d" />

* * * * * * * * * *
## Einleitung
Der Funktionsblock AB2_BYTE_TO_B ist ein Composite-Funktionsblock, der der Konvertierung zwischen BYTE-Datentypen und dem AB2-Adapter dient. Er fungiert als bidirektionaler Konverter und ermöglicht die Kommunikation zwischen Systemkomponenten mit unterschiedlichen Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Request to Adapter): Startet die Konvertierung und Datenübertragung zum Adapter

### **Ereignis-Ausgänge**
- **CNF** (Confirmation from Adapter): Signalisiert den erfolgreichen Abschluss der Konvertierung und Datenübernahme vom Adapter

### **Daten-Eingänge**
- **OUT** (BYTE): Ausgabedaten, die zum Adapter übertragen werden sollen

### **Daten-Ausgänge**
- **IN** (BYTE): Eingabedaten, die vom Adapter empfangen wurden

### **Adapter**
- **AB2_OUT** (adapter::types::bidirectional::AB2): Bidirektionaler Adapter für die Datenkonvertierung

## Funktionsweise
Der Funktionsblock empfängt über das REQ-Ereignis eine Konvertierungsanfrage und leitet die anliegenden BYTE-Daten (OUT) an den AB2-Adapter weiter. Der Adapter führt die eigentliche Konvertierung durch und sendet bei erfolgreichem Abschluss ein CNF-Ereignis zurück, zusammen mit den konvertierten BYTE-Daten (IN).

## Technische Besonderheiten
- Composite-Funktionsblock mit integriertem Adapter
- Bidirektionale Datenübertragung
- Verwendet BYTE als primären Datentyp
- Positionierte Schnittstellen für optimierte Darstellung in der Entwicklungsumgebung

## Zustandsübergänge
1. **Idle-Zustand**: Wartet auf REQ-Ereignis
2. **Verarbeitungszustand**: Bei REQ werden Daten an AB2_OUT weitergeleitet
3. **Bestätigungszustand**: Bei Rückmeldung vom Adapter wird CNF ausgelöst

## Anwendungsszenarien
- Integration von BYTE-basierten Komponenten in AB2-kompatible Systeme
- Protokollkonvertierung in verteilten Automatisierungssystemen
- Bidirektionale Datenaustausch-Schnittstellen
- Adapter-basierte Systemintegration

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Konvertierungsblöcken bietet AB2_BYTE_TO_B eine bidirektionale Funktionalität mit Adapter-Integration. Während einfache Konverter typischerweise nur in eine Richtung arbeiten, ermöglicht dieser Block die Kommunikation in beide Richtungen über standardisierte Adapterschnittstellen.

## Fazit
AB2_BYTE_TO_B ist ein spezialisierter Composite-Funktionsblock, der eine zuverlässige bidirektionale Konvertierung zwischen BYTE-Daten und dem AB2-Adapter-Standard bereitstellt. Seine strukturierte Schnittstelle und klare Ereignissteuerung machen ihn ideal für den Einsatz in komplexen Automatisierungssystemen mit standardisierten Kommunikationsprotokollen.
