# VP1

![VP1](https://github.com/user-attachments/assets/f91c494e-2e9f-4f90-a4f9-bb124842671d)

* * * * * * * * * *

## Einleitung
Der **VP1**-Funktionsbaustein (Vehicle Position 1) ist ein ISO 11783-7-konformes System zur präzisen GPS-Positionsbestimmung, entwickelt unter EPL-2.0 Lizenz.
Der Baustein ermöglicht die hochgenaue Erfassung von Längen- und Breitengraden für mobile Arbeitsmaschinen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung (mit Qualifier `QI`)

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung (mit Status)
- `IND`: Positionsdatenindikation
- `TIMEOUT`: Timeout-Ereignis

### **Daten-Eingänge**
- `QI` (BOOL): Qualifier für Initialisierung

### **Daten-Ausgänge**
| Parameter | Typ | SPN | Größe | Offset | Beschreibung |
|-----------|-----|-----|-------|--------|--------------|
| `QO` | BOOL | - | 1 Bit | - | Ereignisqualifier |
| `STATUS` | STRING | - | - | - | Systemstatusmeldung |
| `Latitude` | REAL | 584 | 4 Byte | -210° | Breitengrad (WGS84) |
| `Longitude` | REAL | 585 | 4 Byte | -210° | Längengrad (WGS84) |

## Funktionsweise

1. **Initialisierung**:
   - `INIT` mit `QI`=TRUE startet GPS-Empfänger
   - `INITO` bestätigt Betriebsbereitschaft mit `QO` und `STATUS`

2. **Positionsbestimmung**:
   - `IND` liefert kontinuierlich aktualisierte Koordinaten
   - Standard-Update-Rate: 5Hz für Echtzeitanwendungen
   - Koordinaten im WGS84-Format

3. **Fehlerbehandlung**:
   - `TIMEOUT` bei GPS-Signalverlust
   - Statusmeldungen im `STATUS`-Feld

## Technische Besonderheiten

✔ **ISO 11783-7 konform** (PGN 65267)  
✔ **Hochpräzise Positionsbestimmung** mit REAL-Datentyp  
✔ **Globale Abdeckung** (WGS84-Referenzsystem)  
✔ **Robuste Signalverarbeitung** mit Fehlerkorrektur  

## Positionsdatenformat

| Parameter | Beispielwert | Bedeutung |
|-----------|--------------|-----------|
| `Latitude` | 48.135125 | 48°13'5.125"N |
| `Longitude` | 11.581981 | 11°58'19.81"E |

## Anwendungsszenarien

- **Präzisionslandwirtschaft**: Automatische Spurführung
- **Flottenmanagement**: Echtzeit-Ortung
- **Geofencing**: Sicherheitszonenüberwachung
- **Arbeitsdokumentation**: Feldkartierung

## Genauigkeitsmerkmale

| Bedingung | Typische Genauigkeit |
|-----------|----------------------|
| Freifeld (RTK) | ±2 cm |
| Standard-GPS | ±2 m |
| Urbaner Raum | ±5 m |

## Vergleich mit ähnlichen Systemen

| Feature | VP1 | Standard-GPS | Premium-Navi |
|---------|-----|-------------|--------------|
| Genauigkeit | ±0.000001° | ±0.0001° | ±0.00001° |
| Update-Rate | 5Hz | 1Hz | 10Hz |
| Datentyp | REAL (32-bit) | INT (16-bit) | DOUBLE (64-bit) |
| ISO-Konformität | Voll | Teilweise | Voll |

## Fazit

Der VP1-Baustein bietet hochpräzise Positionsdaten für mobile Arbeitsmaschinen:

- **Präzision**: Submeter-genaue Positionsbestimmung
- **Zuverlässigkeit**: Robuste GPS-Signalverarbeitung
- **Flexibilität**: Weltweiter Einsatz möglich

Idealer Einsatz bei:
- Automatischen Lenksystemen
- Präzisionslandwirtschaft
- Flottenmanagementsystemen
- Sicherheitskritischen Anwendungen

*Entwickelt für hochpräzise Fahrzeugortung und -navigation*
