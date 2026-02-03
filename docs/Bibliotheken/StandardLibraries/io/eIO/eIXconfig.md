# eIXconfig

```{index} single: eIXconfig
```

<img width="1406" height="219" alt="image" src="https://github.com/user-attachments/assets/0d14f01f-7aa9-4cd7-93a2-74a47d4f4646" />

* * * * * * * * * *

## Einleitung
Der eIXconfig Funktionsblock dient als Service Interface Function Block zur Konfiguration von eIO-Instanzen. Er ermöglicht die Einstellung von Trigger-Eigenschaften für Ein- und Ausgänge und stellt eine Verbindung zu eIO-Instanzen über einen Adapter bereit.

![eIXconfig](eIXconfig.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **CONF**: Konfigurationsanforderung - löst die Konfiguration der eIO-Instanz aus

### **Ereignis-Ausgänge**
- **CNF**: Bestätigung des angeforderten Services - signalisiert den Abschluss der Konfiguration

### **Daten-Eingänge**
- **FE** (BOOL): Falling Edge Trigger Enable - aktiviert die Flankenauslösung bei fallender Flanke
- **RE** (BOOL): Rising Edge Trigger Enable - aktiviert die Flankenauslösung bei steigender Flanke

### **Daten-Ausgänge**
- **STATUS** (WSTRING): Service Status - liefert Statusinformationen über den Konfigurationsvorgang

### **Adapter**
- **eIX**: Verbindung zur eIO-Instanz - stellt die Kommunikation mit der eIO-Hardware her

## Funktionsweise
Der eIXconfig Block empfängt über das CONF-Ereignis eine Konfigurationsanforderung. Zusammen mit den Daten-Eingängen FE und RE werden die Trigger-Einstellungen für die eIO-Instanz konfiguriert. Nach erfolgreicher Konfiguration wird das CNF-Ereignis mit dem entsprechenden STATUS ausgegeben. Die tatsächliche Kommunikation mit der Hardware erfolgt über den eIX-Adapter.

## Technische Besonderheiten
- Verwendet WSTRING für Statusausgaben, was umfangreiche Statusinformationen ermöglicht
- Unterstützt separate Konfiguration von steigender und fallender Flankenerkennung
- Implementiert als Service Interface Function Block gemäß IEC 61499-2 Standard

## Zustandsübergänge
1. **Initialisierungszustand**: Block wartet auf CONF-Ereignis
2. **Konfigurationszustand**: Verarbeitung der Trigger-Einstellungen und Übertragung an eIO-Instanz
3. **Bestätigungszustand**: Ausgabe von CNF mit Statusinformation

## Anwendungsszenarien
- Konfiguration von eIO-Hardwarekomponenten in industriellen Steuerungssystemen
- Einstellung von Trigger-Eigenschaften für digitale Eingänge
- Integration in größere Automatisierungssysteme mit eIO-Komponenten

## ⚖️ Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen IO-Konfigurationsblöcken bietet eIXconfig spezifische eIO-Integration und erweiterte Trigger-Konfigurationsmöglichkeiten. Die Verwendung eines Adapters ermöglicht eine saubere Trennung zwischen Funktionalität und Hardwarekommunikation.

## Fazit
Der eIXconfig Funktionsblock stellt eine spezialisierte Lösung für die Konfiguration von eIO-Instanzen dar. Durch die klare Trennung von Konfigurationslogik und Hardwarekommunikation sowie die flexible Trigger-Einstellung eignet er sich ideal für anspruchsvolle industrielle Anwendungen.