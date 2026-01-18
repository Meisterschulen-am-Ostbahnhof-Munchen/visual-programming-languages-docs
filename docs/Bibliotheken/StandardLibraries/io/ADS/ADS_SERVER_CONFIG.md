# ADS_SERVER_CONFIG

```{index} single: ADS_SERVER_CONFIG
```

<img width="1348" height="238" alt="image" src="https://github.com/user-attachments/assets/3b924f75-67ac-48e2-9abf-411c3f4906fd" />

* * * * * * * * * *

## Einleitung
Der ADS_SERVER_CONFIG Funktionsblock dient zur Konfiguration von ADS-Server-Verbindungen in 4diac-Systemen. Er ermöglicht die Initialisierung und Parametrisierung von Verbindungseinstellungen für ADS-Kommunikation, die in nachgelagerten IO-Funktionsblöcken verwendet werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service-Initialisierungsereignis - Startet die Konfiguration des ADS-Servers

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - Signalisiert den erfolgreichen Abschluss der Konfiguration

### **Daten-Eingänge**
- **QI** (BOOL): Ereigniseingangsqualifizierer - Aktiviert/deaktiviert die Initialisierung
- **FRIENDLY_NAME** (WSTRING): Benutzerfreundlicher Servername für Verwendung in IO-Funktionsblöcken
- **SERVER_ADS_ADDRESS** (WSTRING): ADS-Adresse des Servers
- **ADS_PORT** (UINT): ADS-Port des Servers
- **SERVER_IPV4_OR_HOSTNAME** (WSTRING): IPv4-Adresse oder Hostname des ADS-Servers

### **Daten-Ausgänge**
- **QO** (BOOL): Ereignisausgangsqualifizierer - Zeigt den Status der Initialisierung an
- **STATUS** (WSTRING): Service-Statusinformationen

### **Adapter**
Keine Adapter-Schnittstellen vorhanden.

## Funktionsweise
Der Funktionsblock wird durch das INIT-Ereignis aktiviert und verarbeitet die bereitgestellten Konfigurationsparameter. Bei erfolgreicher Verarbeitung gibt er das INITO-Ereignis aus und stellt die konfigurierten Parameter für nachgelagerte ADS-IO-Funktionsblöcke bereit. Der STATUS-Ausgang liefert detaillierte Informationen über den Konfigurationsprozess.

## Technische Besonderheiten
- Verwendet WSTRING-Datentypen für internationale Zeichenunterstützung
- Unterstützt sowohl IPv4-Adressen als auch Hostnamen für maximale Flexibilität
- Separate Parameter für ADS-Adresse und Netzwerkadresse ermöglichen komplexe Netzwerkkonfigurationen
- Port-Konfiguration als UINT für numerische Port-Spezifikation

## Zustandsübersicht
1. **Inaktiv**: Wartet auf INIT-Ereignis
2. **Konfiguration**: Verarbeitet Eingangsparameter
3. **Aktiv**: Konfiguration erfolgreich abgeschlossen, Parameter stehen zur Verfügung
4. **Fehler**: Konfiguration fehlgeschlagen, STATUS enthält Fehlerinformationen

## Anwendungsszenarien
- Initiale Systemkonfiguration in ADS-basierten Automatisierungssystemen
- Zentrale Verwaltung von ADS-Server-Verbindungsparametern
- Dynamische Rekonfiguration von Netzwerkeinstellungen
- Integration in größere IO-Management-Systeme

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einfachen ADS-IO-Blöcken bietet ADS_SERVER_CONFIG eine zentrale Konfigurationsmöglichkeit für mehrere nachgelagerte Blöcke. Er separiert die Konfigurationslogik von der eigentlichen Datenkommunikation und ermöglicht so wiederverwendbare Server-Einstellungen.

## Fazit
ADS_SERVER_CONFIG ist ein essentieller Baustein für strukturierte ADS-Kommunikation in 4diac-Systemen. Durch die zentrale Konfigurationsverwaltung vereinfacht er die Wartung und Änderung von Netzwerkeinstellungen und fördert konsistente Verbindungsparameter über verschiedene IO-Funktionsblöcke hinweg.
