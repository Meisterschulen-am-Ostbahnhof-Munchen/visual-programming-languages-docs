# COGSOGRapidUpdate

![COGSOGRapidUpdate](https://github.com/user-attachments/assets/5a70a5f2-5ffd-44d5-95b9-3a9422b0504c)

* * * * * * * * * *

## Einleitung
Der **COGSOGRapidUpdate**-Funktionsbaustein ist ein NMEA 2000-konformes System zur Echtzeiterfassung von Kurs über Grund (COG) und Geschwindigkeit über Grund (SOG), entwickelt unter EPL-2.0 Lizenz.
Der Baustein ermöglicht die präzise Navigation für maritime und mobile Landanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Qualifier `QI`)

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung (mit Status)
- `IND`: Echtzeitdatenindikation
- `TIMEOUT`: Timeout-Ereignis

### **Daten-Eingänge**
- `QI` (BOOL): Qualifier für Initialisierung

### **Daten-Ausgänge**
| Parameter | Typ | Beschreibung | Genauigkeit | Einheit |
|-----------|-----|--------------|-------------|---------|
| `SID` | USINT | Sequenz-ID für Datenabgleich | - | - |
| `COGReference` | BYTE | Referenzrichtung (0=True North) | - | - |
| `CourseOverGround` | UINT | Kurs über Grund | 0.0001 rad | rad |
| `SpeedOverGround` | UINT | Geschwindigkeit über Grund | 0.01 m/s | m/s |

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit `QI`=TRUE startet Navigationssystem
   - `INITO` bestätigt Betriebsbereitschaft mit `QO` und `STATUS`

2. **Datenbereitstellung**:
   - `IND` liefert alle 100ms aktualisierte Navigationsdaten
   - Synchronisation über `SID` für Datenkonsistenz

3. **Fehlerbehandlung**:
   - `TIMEOUT` bei Signalverlust
   - Statusmeldungen im `STATUS`-Feld

## Technische Besonderheiten

✔ **NMEA 2000 konform** (PGN 129026)  
✔ **Hochpräzise Winkelmessung** (0.0057° Auflösung)  
✔ **Echtzeitfähig** mit 10Hz Update-Rate  
✔ **Mehrfachreferenzierung** (True/Magnetic North)  

## Anwendungsszenarien

- **Maritime Navigation**: Kursüberwachung
- **Landmaschinen**: Automatische Spurführung
- **Fahrzeugtelemetrie**: Geschwindigkeitsanalyse
- **Rettungssysteme**: Positionsverfolgung

## Datenkonvertierung

| Parameter | Umrechnung | Beispiel |
|-----------|------------|----------|
| `CourseOverGround` | ° = rad × (180/π) | 1 rad = 57.2958° |
| `SpeedOverGround` | km/h = m/s × 3.6 | 1 m/s = 3.6 km/h |

## Vergleich mit ähnlichen Systemen

| Feature | COGSOGRapidUpdate | Standard | Premium |
|---------|-------------------|----------|---------|
| Genauigkeit | ±0.0057° | ±0.1° | ±0.001° |
| Update-Rate | 10Hz | 1Hz | 20Hz |
| Referenzen | 2 | 1 | 3 |
| Normkonformität | NMEA 2000 | Proprietär | NMEA 2000+ |

## Fazit

Der COGSOGRapidUpdate-Baustein bietet präzise Navigationsdaten für mobile Systeme:

- **Echtzeitfähig**: Hochfrequente Datenaktualisierung
- **Maritim optimiert**: Speziell für Schifffahrt entwickelt
- **Flexibel**: Auch für Landanwendungen geeignet

Idealer Einsatz bei:
- Automatischen Navigationssystemen
- Geschwindigkeitsüberwachung
- Sicherheitskritischen Anwendungen
- Telemetriesystemen

*Entwickelt für präzise Kurs- und Geschwindigkeitserfassung*
