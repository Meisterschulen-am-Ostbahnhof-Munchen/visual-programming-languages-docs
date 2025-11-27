# AX2_X_TO_BOOL

<img width="1186" height="196" alt="image" src="https://github.com/user-attachments/assets/f72801f7-3cc1-4935-9f9d-8c58011e6876" />

* * * * * * * * * *

## Einleitung
Der Funktionsblock AX2_X_TO_BOOL ist ein Composite-Funktionsblock zur Konvertierung von AX2-Daten in BOOL-Werte. Er dient als bidirektionaler Adapter für die Datentypumwandlung zwischen verschiedenen Schnittstellen in Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** (Request to Adapter): Startet die Konvertierungsanfrage an den Adapter

### **Ereignis-Ausgänge**
- **CNF** (Confirmation from Adapter): Bestätigt den Abschluss der Konvertierung vom Adapter

### **Daten-Eingänge**
- **OUT** (BOOL): Ausgabedaten für die Übergabe an den Adapter

### **Daten-Ausgänge**
- **IN** (BOOL): Eingabedaten vom Adapter nach erfolgter Konvertierung

### **Adapter**
- **AX2_IN** (adapter::types::bidirectional::AX2): Bidirektionaler AX2-Adapter für die Datentypkonvertierung

## Funktionsweise
Der Funktionsblock empfängt über das REQ-Ereignis eine Konvertierungsanfrage und leitet diese an den AX2-Adapter weiter. Der Adapter führt die Umwandlung der AX2-Daten in BOOL-Werte durch. Nach erfolgreicher Konvertierung wird das CNF-Ereignis mit den konvertierten Daten am IN-Ausgang ausgegeben. Gleichzeitig können BOOL-Daten über den OUT-Eingang an den Adapter zurückgegeben werden.

## Technische Besonderheiten
- Bidirektionale Datenübertragung zwischen AX2- und BOOL-Datentypen
- Composite-Funktionsblock mit integriertem Adapter
- Automatische Ereignisweiterleitung zwischen Schnittstellen
- Positionierte Elemente für optimierte Darstellung in der Entwicklungsumgebung

## Zustandsübergänge
1. **Wartezustand**: Keine aktive Konvertierung
2. **Aktiver Zustand**: Bei REQ-Ereignis - Daten werden an Adapter weitergeleitet
3. **Bestätigungszustand**: Bei Abschluss der Konvertierung - CNF-Ereignis wird ausgelöst

## Anwendungsszenarien
- Integration von AX2-Sensordaten in BOOL-basierte Steuerungssysteme
- Datentypkonvertierung in gemischten Automatisierungsumgebungen
- Bidirektionale Kommunikation zwischen verschiedenen Protokollen
- Adapterlösungen für bestehende Systeme mit unterschiedlichen Datentypen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Konvertierungsblöcken bietet AX2_X_TO_BOOL eine bidirektionale Funktionalität mit integriertem Adapter-Interface. Während einfache Konverter typischerweise nur in eine Richtung arbeiten, ermöglicht dieser Block den Datenaustausch in beide Richtungen.

## Fazit
Der AX2_X_TO_BOOL Funktionsblock stellt eine robuste Lösung für die bidirektionale Konvertierung zwischen AX2- und BOOL-Datentypen dar. Durch die integrierte Adapter-Architektur und die klare Ereignissteuerung eignet er sich besonders für komplexe Automatisierungsanwendungen mit gemischten Datentypumgebungen.
