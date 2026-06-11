# IA_FHS


![IA_FHS](./IA_FHS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **IA_FHS** dient als ISOBUS-Adapter für den Front Hitch Status (FHS) gemäß ISO 11783-7 (PGN 65094). Er kapselt die interne Verarbeitung des Bausteins `I_FHS` und stellt die gewonnenen Mess- und Statuswerte über standardisierte unidirektionale Adapterausgänge zur Verfügung. Die Initialisierung erfolgt über das Ereignis `INIT`; nach erfolgreichem Abschluss werden die Daten über die Adapterschnittstellen bereitgestellt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ    | mit Variablen | Beschreibung                    |
|----------|--------|---------------|---------------------------------|
| `INIT`   | EInit  | `QI`          | Service-Initialisierung         |

### **Ereignis-Ausgänge**

| Ereignis | Typ    | mit Variablen      | Beschreibung                      |
|----------|--------|--------------------|-----------------------------------|
| `INITO`  | EInit  | `QO`, `STATUS`     | Initialisierungsbestätigung       |

### **Daten-Eingänge**

| Variable | Typ    | Beschreibung                  |
|----------|--------|-------------------------------|
| `QI`     | BOOL   | Ereignis-Eingangs-Qualifier   |

### **Daten-Ausgänge**

| Variable | Typ    | Beschreibung                |
|----------|--------|-----------------------------|
| `QO`     | BOOL   | Ausgangs-Qualifier          |
| `STATUS` | STRING | Statusmeldung (z. B. „OK“)  |

### **Adapter**

| Adapter   | Typ                         | Beschreibung                                 |
|-----------|-----------------------------|----------------------------------------------|
| `POSITION`| `adapter::types::unidirectional::AUS` | Front-Hitch-Position (analog, unsigniert)   |
| `FORCE`   | `adapter::types::unidirectional::AUS` | Front-Nominal-Lower-Link-Force (analog)     |
| `DRAFT`   | `adapter::types::unidirectional::AUI` | Front-Draft (analog, ganzzahlig unsigniert) |
| `TIMEOUT` | `adapter::types::unidirectional::AX`  | Timeout-Status des ISOBUS-Empfangs          |

## Funktionsweise

Der Baustein enthält intern eine Instanz `I_CORE` vom Typ `isobus::tecu::I_FHS`. Beim Eintreffen des Initialisierungsereignisses `INIT` wird der Kern mit dem Qualifier `QI` aktiviert. Nach erfolgreicher Initialisierung löst dieser das Ereignis `INITO` aus, setzt `QO = TRUE` und gibt den Status auf `STATUS` aus. Gleichzeitig generiert der Kern das Ereignis `IND`, das über die internen Ereignisverbindungen an die Adapter `POSITION`, `FORCE` und `DRAFT` weitergeleitet wird. Die zugehörigen Datenwerte (`FRONT_HITCH_POSITION`, `FRONT_HITCH_NOMINAL_LOWER_LINK_FORCE`, `FRONT_HITCH_DRAFT`) werden dabei über die entsprechenden Datenverbindungen an die Adapterausgänge übertragen. Ein etwaiger Timeout-Zustand des ISOBUS-Empfangs wird über das Adapter‑Ereignis `TIMEOUT.E1` und den Datenwert `Q_timeout` gemeldet.

## Technische Besonderheiten

- **Standardkonformität**: Der Baustein erfüllt die Anforderungen der ISO 11783-7 für die **PGN 65094** (Front Hitch Status).
- **Adapter‑Schnittstellen**: Alle Sensorwerte werden über unidirektionale Adapter ausgegeben, die eine flexible und entkoppelte Weiterverarbeitung in der 4diac‑IDE ermöglichen.
- **Initialisierungssequenz**: Die Initialisierung muss explizit über das Ereignis `INIT` angestoßen werden; der Baustein arbeitet erst nach erfolgreichem Abschluss korrekt.
- **Timeout‑Überwachung**: Der Adapter `TIMEOUT` signalisiert, ob der ISOBUS‑Datenempfang innerhalb der erwarteten Zeit erfolgt. Dies dient der Fehlererkennung in der Feldbuskommunikation.

## Zustandsübersicht

Der Baustein besitzt keinen eigenen sichtbaren Zustandsautomaten. Die interne Ablaufsteuerung erfolgt über den Kernbaustein `I_FHS`. Grob lassen sich zwei Phasen unterscheiden:

- **Vor Initialisierung**: Der Baustein ist inaktiv. Die Ereignis‑Ausgänge und Adapter liefern keine Daten.
- **Nach Initialisierung (INIT erfolgreich)**:  
  - `INITO` wird ausgelöst, `QO = TRUE`.  
  - Die Adapter `POSITION`, `FORCE`, `DRAFT` werden zyklisch oder ereignisgesteuert mit aktuellen Messwerten versorgt.  
  - Der Adapter `TIMEOUT` meldet den aktuellen Timeout‑Status.

Tritt während des Betriebs ein Fehler auf (z. B. Verbindungsabbruch), wird dies über den Timeout‑Adapter oder den Status‑Ausgang signalisiert.

## Anwendungsszenarien

- **Traktorsteuerung**: Erfassung der Front-Hubwerksposition und der Belastung des Unterlenkers zur Regelung von Arbeitsgeräten (z. B. Frontlader, Fronthubwerk).
- **ISOBUS‑Diagnose**: Überwachung des ISOBUS‑Datenstroms auf Timeouts und Plausibilität der Kraft‑ und Positionswerte.
- **Datenaufzeichnung**: Bereitstellung von Position, Kraft und Zugkraft für Telemetrie‑ oder Protokollierungsanwendungen.

## Vergleich mit ähnlichen Bausteinen

- **IA_RHS** (Rear Hitch Status): Analoger Adapter für den Heckkraftheber. Die Adressierung und PGN‑Nummer unterscheiden sich (z. B. PGN 65096). Während `IA_FHS` die Front‑Daten liefert, fokussiert `IA_RHS` auf den hinteren Bereich.
- **Direkter I_FHS‑Baustein**: Ohne Adapter‑Wrapper müsste der Anwender den Kernbaustein `I_FHS` selbst einbinden und die erforderlichen Daten‑ und Ereignisverbindungen manuell setzen. Der Adapter‑Baustein vereinfacht die Handhabung durch standardisierte, vorgefertigte Schnittstellen.

## Fazit

Der Funktionsblock **IA_FHS** bietet einen fertig konfektionierten ISOBUS‑Adapter für den Front‑Hitch‑Status. Dank der internen Kapselung des `I_FHS`‑Kerns und der Ausgabe über unidirektionale Adapter kann der Anwender die Werte für Position, Kraft und Zugkraft schnell und zuverlässig in eigene Steuerungs‑ oder Überwachungsanwendungen einbinden. Die integrierte Timeout‑Überwachung erhöht die Betriebssicherheit der ISOBUS‑Kommunikation.