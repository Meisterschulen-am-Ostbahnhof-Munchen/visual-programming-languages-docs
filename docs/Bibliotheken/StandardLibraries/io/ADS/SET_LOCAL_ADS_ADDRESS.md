# SET_LOCAL_ADS_ADDRESS

```{index} single: SET_LOCAL_ADS_ADDRESS
```

<img width="1327" height="235" alt="image" src="https://github.com/user-attachments/assets/79166574-02f4-4798-bfa1-22a3911fc8a1" />

* * * * * * * * * *

## 🎧 Podcast

* [Unlock Simultaneous Connectivity: Your Guide to Dual Wi-Fi for Uninterrupted Local Device Control](https://podcasters.spotify.com/pod/show/ms-muc-lama/episodes/Unlock-Simultaneous-Connectivity-Your-Guide-to-Dual-Wi-Fi-for-Uninterrupted-Local-Device-Control-e3756vt)

## Einleitung
Der SET_LOCAL_ADS_ADDRESS Funktionsblock ist ein Service Interface Function Block zur Konfiguration der lokalen ADS-Adresse. ADS (Automation Device Specification) ist ein Kommunikationsprotokoll, das häufig in der Automatisierungstechnik verwendet wird. Dieser Baustein ermöglicht die dynamische Einstellung der lokalen ADS-Adresse während der Laufzeit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **INIT**: Service Initialisierung - Startet den Konfigurationsprozess für die lokale ADS-Adresse

### **Ereignis-Ausgänge**
- **INITO**: Initialisierungsbestätigung - Signalisiert den Abschluss des Konfigurationsvorgangs

### **Daten-Eingänge**
- **QI** (BOOL): Event Input Qualifier - Aktiviert/deaktiviert den Initialisierungsvorgang
- **PARAMS** (STRING): Lokale ADS-Adresse, die gesetzt werden soll

### **Daten-Ausgänge**
- **QO** (BOOL): Event Output Qualifier - Bestätigt den erfolgreichen Abschluss der Operation
- **STATUS** (WSTRING): Service Status - Enthält Statusinformationen über den durchgeführten Vorgang
- **LOCAL_ADS_ADDRESS** (STRING): Resultierende ADS-Adresse - Die tatsächlich gesetzte ADS-Adresse

## Funktionsweise
Der Funktionsblock wird durch das INIT-Ereignis aktiviert. Bei Aktivierung liest er den PARAMS-Eingang, der die gewünschte lokale ADS-Adresse im STRING-Format enthält. Der Baustein konfiguriert daraufhin die lokale ADS-Schnittstelle mit der angegebenen Adresse. Nach Abschluss des Vorgangs wird das INITO-Ereignis ausgelöst und die resultierende ADS-Adresse sowie Statusinformationen an den Ausgängen bereitgestellt.

## Technische Besonderheiten
- Verwendet STRING-Datentyp für die ADS-Adressen
- Bietet umfangreiche Statusinformationen im WSTRING-Format
- Unterstützt dynamische Adresskonfiguration zur Laufzeit
- Implementiert ein standardisiertes Initialisierungsprotokoll

## Zustandsübergänge
1. **Initialzustand**: Wartet auf INIT-Ereignis
2. **Konfigurationszustand**: Verarbeitet die ADS-Adressen-Parameter
3. **Abschlusszustand**: Sendet INITO-Ereignis mit Ergebnisdaten

## Anwendungsszenarien
- Dynamische Konfiguration von ADS-Geräten in verteilten Automatisierungssystemen
- Adressierung von ADS-Komponenten in flexiblen Produktionsanlagen
- Integration in Systeme mit variablen Netzwerkkonfigurationen
- Wartung und Inbetriebnahme von ADS-basierten Steuerungen

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu statischen ADS-Konfigurationsbausteinen ermöglicht SET_LOCAL_ADS_ADDRESS eine dynamische Adressverwaltung während der Laufzeit. Der Baustein bietet zudem detaillierte Statusrückmeldungen, was die Fehlerdiagnose erleichtert.

## Fazit
Der SET_LOCAL_ADS_ADDRESS Funktionsblock stellt eine flexible Lösung für die dynamische Konfiguration von ADS-Adressen in IEC 61499-basierten Steuerungssystemen dar. Durch seine klare Schnittstellendefinition und umfassende Statusrückmeldung eignet er sich besonders für Anwendungen, die eine flexible Netzwerkkonfiguration erfordern.