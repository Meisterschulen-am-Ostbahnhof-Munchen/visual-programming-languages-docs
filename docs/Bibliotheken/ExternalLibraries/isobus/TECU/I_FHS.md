# I_FHS

```{index} single: I_FHS
```

![I_FHS](https://github.com/user-attachments/assets/b03b0b7f-5254-4cc4-b25a-ec6da0840286)

* * * * * * * * * *

## Einleitung
Der **I_FHS** ist ein standardkonformer Funktionsbaustein für Front-Anbaugerätestatusinformationen nach ISO 11783-7 (PGN 65094).
Entwickelt unter EPL-2.0 Lizenz,ermöglicht er die Überwachung und Steuerung von Front-Anbaugeräten in modernen Agrarsystemen.

![I_FHS](I_FHS.svg)

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung
- `IND`: Statusindikation
- `TIMEOUT`: Timeout-Ereignis

### **Daten-Eingänge**
- `QI` (BOOL): Initialisierungsqualifier

### **Daten-Ausgänge**
- `QO` (BOOL): Statusqualifier
- `STATUS` (STRING): Betriebsstatus
- `timestamp_*` (DINT): Zeitstempel
- `Q_timeout` (BOOL): Timeout-Indikator

## Parameter (SPN-Details)

| Parameter | SPN  | Typ   | Länge | Skalierung | Wertebereich | Beschreibung |
|-----------|------|-------|-------|------------|--------------|--------------|
| `FRONT_HITCH_POSITION` | 1872 | USINT | 8 bit | 0.4 %/bit | 0-100% | Aktuelle Position des Front-Anbaugeräts |
| `FRONT_HITCH_WORK_INDICATION` | 1876 | BYTE | 2 bit | 4 Zustände | 0-3 | Arbeitsstatusindikator |
| `FRONT_HITCH_POS_LIMIT_STATUS` | 5150 | BYTE | 3 bit | 8 Zustände | 0-7 | Positionslimit-Status |
| `FRONT_HITCH_NOMINAL_LOWER_LINK_FORCE` | 1880 | USINT | 8 bit | 0.8 %/bit | -100% bis +100% | Normale Unterlenkerkraft |
| `FRONT_HITCH_DRAFT` | 1878 | UINT | 16 bit | 10 N/bit | -320 kN bis +320 kN | Zugkraft am Front-Anbaugerät |
| `FRONT_HITCH_EXIT_REASON_CODE` | 5816 | BYTE | 6 bit | 64 Zustände | 0-63 | Grundcode für Systemabbruch |

## Funktionsweise

1. **Initialisierung**:
   - Aktivierung durch `INIT`-Ereignis
   - Bestätigung via `INITO` mit Statusinformation

2. **Datenaktualisierung**:
   - Automatische Statusmeldungen via `IND`-Ereignis
   - Enthält alle relevanten Front-Anbaugeräteparameter

3. **Fehlerbehandlung**:
   - Timeout-Erkennung via `TIMEOUT`-Ereignis
   - Detaillierte Statuscodes im `STATUS`-Feld

## Technische Besonderheiten

✔ **ISO 11783-7 konform** (PGN 65094)
✔ **Echtzeitfähige** Statusüberwachung
✔ **Umfassende Parameter** für Front-Anbaugeräte
✔ **Integrierte Fehlerdiagnose**

## Anwendungsszenarien

- **Frontladersteuerung**: Präzise Positionsregelung
- **Kraftmessung**: Echtzeit-Überwachung der Zugkräfte
- **Sicherheitssysteme**: Erkennung von Grenzwertüberschreitungen
- **Diagnose**: Systematische Fehleranalyse

## Vergleich mit ähnlichen Bausteinen

| Feature        | I_FHS | Standard Hitch Control | Advanced Hitch Manager |
|---------------|-------|------------------------|------------------------|
| ISO-Standard  | ✔     | ✖                      | ✖                      |
| Front-Anbau   | ✔     | ✖                      | ✔                      |
| Kraftmessung  | ✔     | ✔                      | ✔                      |
| Diagnosecodes | ✔     | ✖                      | ✔                      |




## Zugehörige Übungen

* [Uebung_079](../../../../training1/Ventilsteuerung/4diacIDE-workspace/test_B/Uebungen_doc/Uebung_079.md)

## Fazit

Der I_FHS-Baustein bietet umfassende Front-Anbaugerätesteuerung:

- **Standardkonform**: Volle ISO 11783-7 Kompatibilität
- **Präzise**: Hochauflösende Messparameter
- **Zuverlässig**: Integrierte Fehlererkennung

Essential für:
- Moderne Frontlader-Systeme
- Präzisionslandwirtschaft
- Sicherheitskritische Anwendungen