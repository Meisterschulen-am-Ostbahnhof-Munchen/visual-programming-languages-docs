# CbVtStatus

```{index} single: CbVtStatus
```

![CbVtStatus](https://user-images.githubusercontent.com/116869307/214146846-2d9f0694-b5f4-4e70-aae0-dc64540eb356.png)

* * * * * * * * * *

## Einleitung
Der **CbVtStatus** ist ein standardisierter Callback-Baustein für Virtual-Terminal-Seitenwechsel, entwickelt unter EPL-2.0 Lizenz. Die Version 1.0 unterstützt ISO 11783-6 (ISOBUS) in landwirtschaftlichen Steuersystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- `INIT`: Initialisierungsanforderung

### **Ereignis-Ausgänge**
- `INITO`: Initialisierungsbestätigung (mit STATUS)
- `IND`: Seitenwechsel-Indikation (mit Seiteninfo)

### **Daten-Ausgänge**
- `STATUS` (STRING): Betriebsstatus
- `u8Instance` (USINT): Client-Instanzkennung
- `qWsActive` (BOOL): Arbeitsmengen-Status
- `wPage` (UINT): Aktuelle Seiten-ID

## Funktionsweise

1. **Initialisierung**:
   - `INIT`-Ereignis startet Setup
   - `INITO` bestätigt mit STATUS

2. **Seitenwechsel**:
   - `IND` wird bei Maskenwechsel ausgelöst
   - Liefert: Seiten-ID, Aktivstatus, Instanznummer

3. **Betrieb**:
   - Echtzeit-Überwachung des VT-Zustands
   - Multi-ECU-fähige Architektur

## Technische Besonderheiten

✔ **ISO 11783-6 konform**
✔ **Deterministisches** Verhalten
✔ **Multi-ECU Unterstützung**
✔ **Plug-in-fähige** Architektur

## Unterstützte Betriebsmodi

| Modus         | Beschreibung                     |
|---------------|----------------------------------|
| Einzelgerät   | Standardbetrieb mit u8Instance=0 |
| Multi-ECU     | Parallele Instanzen (1-255)      |
| Diagnose      | STATUS-Meldungen für Service     |

## Anwendungsszenarien

- **Traktorsteuerungen**: Bedienmasken-Überwachung
- **Erntemaschinen**: Arbeitsdaten-Anzeige
- **Diagnosetools**: VT-Zustandsmonitoring
- **Multi-Display-Systeme**: Synchronisation

## Vergleich mit ähnlichen Bausteinen

| Feature        | CbVtStatus | VtPageManager | VtEventLogger |
|---------------|------------|---------------|---------------|
| Seitenwechsel | ✔          | ✔             | ✖             |
| Multi-ECU     | ✔          | ✖             | ✖             |
| STATUS-Rückmeldung | ✔     | ✖             | ✔             |

## Fehlerbehandlung

- Ungültige Seiten-ID:
  - STATUS = "ERR_INVALID_PAGE"
  - wPage = 0xFFFF
- Initialisierungsfehler:
  - STATUS = "ERR_INIT_FAILED"
  - System im Safe-State

## Fazit

Der CbVtStatus-Baustein ist essentiell für ISOBUS-konforme Agrarsysteme:

- Robustes Seitenwechsel-Management
- Volle ISO-11783-6-Kompatibilität
- Bewährte Architektur in Serieprodukten

Besonders wertvoll für Hersteller von:
- Traktorsteuergeräten
- Erntemaschinen-Kontrollsystemen
- ISOBUS-Diagnosegeräten

Die standardisierte Implementierung ermöglicht zuverlässigen Betrieb in heterogenen Systemumgebungen.




















