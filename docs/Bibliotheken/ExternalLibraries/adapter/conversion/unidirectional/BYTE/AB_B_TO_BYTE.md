# AB_B_TO_BYTE

```{index} single: AB_B_TO_BYTE
```

<img width="1243" height="236" alt="image" src="https://github.com/user-attachments/assets/e8004a47-56e9-447b-a228-03b20792af4a" />

* * * * * * * * * *

## Einleitung
Der Funktionsblock AB_B_TO_BYTE ist ein Composite-Funktionsblock, der der Konvertierung von AB-Daten in das BYTE-Format dient. Er fungiert als Adapter-Konverter und ermöglicht die nahtlose Integration von AB-Datenquellen in Systeme, die BYTE-Daten erwarten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge vorhanden - Ereignisse werden über den Adapter empfangen.

### **Ereignis-Ausgänge**
- **CNF** (Confirmation): Bestätigungsereignis, das vom Adapter empfangen wird

### **Daten-Eingänge**
Keine direkten Daten-Eingänge vorhanden - Daten werden über den Adapter empfangen.

### **Daten-Ausgänge**
- **IN** (BYTE): Eingangsdaten, die vom Adapter konvertiert wurden

### **Adapter**
- **AB_IN**: Adapter-Eingang vom Typ `adapter::types::unidirectional::AB` für den Empfang von AB-Daten

## Funktionsweise
Der Funktionsblock empfängt AB-Daten über den Adapter-Eingang AB_IN und konvertiert diese in das BYTE-Format. Bei Empfang von Daten über den Adapter wird automatisch das Bestätigungsereignis CNF ausgelöst und die konvertierten Daten am Ausgang IN bereitgestellt.

## Technische Besonderheiten
- Implementiert als Composite-FB mit interner Netzwerkstruktur
- Verwendet unidirektionale Adapter-Kommunikation
- Automatische Ereignisweiterleitung vom Adapter zum CNF-Ausgang
- Direkte Datenweiterleitung vom Adapter zum IN-Ausgang

## Zustandsübersicht
Der Funktionsblock arbeitet zustandslos und reagiert sofort auf eingehende Adapter-Ereignisse. Bei jedem E1-Ereignis vom Adapter wird das CNF-Ereignis ausgelöst und die aktuellen D1-Daten des Adapters an IN ausgegeben.

## Anwendungsszenarien
- Integration von AB-basierten Sensoren oder Aktoren in BYTE-orientierte Steuerungssysteme
- Protokollkonvertierung in industriellen Automatisierungsanlagen
- Adapter-basierte Datenumwandlung in verteilten Steuerungssystemen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen Konvertierungsbausteinen bietet AB_B_TO_BYTE den Vorteil der Adapter-Integration, was eine standardisierte und typsichere Schnittstelle ermöglicht. Andere Konvertierungsbausteine arbeiten typischerweise mit direkten Ein-/Ausgängen statt mit Adaptern.

## Fazit
AB_B_TO_BYTE stellt eine elegante Lösung für die Konvertierung von AB- zu BYTE-Daten mittels Adapter-Schnittstellen dar. Die Composite-Implementierung gewährleistet eine robuste und zuverlässige Datenumwandlung, die besonders in komplexen Automatisierungssystemen mit standardisierten Kommunikationsschnittstellen vorteilhaft ist.
