# IA_PosDeltaHighPrecRapidUpd


![IA_PosDeltaHighPrecRapidUpd](./IA_PosDeltaHighPrecRapidUpd.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `IA_PosDeltaHighPrecRapidUpd` ist ein ISOBUS-Adapterbaustein für hochpräzise, schnell aktualisierte Positionsdeltas gemäß dem NMEA 2000 Standard (PGN 129027). Er kapselt den internen Kernbaustein `I_PosDeltaHighPrecRapidUpd` und stellt dessen Ausgangsdaten über Adapterschnittstellen zur Verfügung. Dadurch können Positionsänderungen (Zeit-, Breiten- und Längengraddeltas) sowie ein Timeout-Status nahtlos in Automatisierungssysteme eingebunden werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Beschreibung                                            |
|----------|-------|---------------------------------------------------------|
| `INIT`   | EInit | Initialisierung des Bausteins; wird mit `QI` verwendet. |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Beschreibung                                    |
|----------|-------|-------------------------------------------------|
| `INITO`  | EInit | Bestätigung der Initialisierung; liefert `QO` und `STATUS`. |

### **Daten-Eingänge**

| Name | Typ    | Beschreibung                |
|------|--------|-----------------------------|
| `QI` | `BOOL` | Qualifikator für INIT-Ereignis. |

### **Daten-Ausgänge**

| Name     | Typ      | Beschreibung                      |
|----------|----------|-----------------------------------|
| `QO`     | `BOOL`   | Ausgangsqualifikator (Initialisierung erfolgreich?). |
| `STATUS` | `STRING` | Statusmeldung zur Initialisierung. |

### **Adapter**

| Adapterbezeichnung | Typ (Adapter)                    | Beschreibung                            |
|--------------------|----------------------------------|-----------------------------------------|
| `TIME_DELTA`       | `adapter::types::unidirectional::AUI` | Liefert das Zeitdelta (unsigned integer). |
| `LAT_DELTA`        | `adapter::types::unidirectional::AI`  | Liefert das Breitengraddelta (signed integer). |
| `LON_DELTA`        | `adapter::types::unidirectional::AI`  | Liefert das Längengraddelta (signed integer). |
| `TIMEOUT`          | `adapter::types::unidirectional::AX`  | Zeigt an, ob ein Timeout aufgetreten ist (Bool). |

## Funktionsweise

Der Baustein arbeitet als **Wrapper** um den internen FB `I_PosDeltaHighPrecRapidUpd`. Bei einem `INIT`-Ereignis mit gesetztem `QI` wird der Kern initialisiert. Nach erfolgreicher Initialisierung meldet sich der Kern mit `INITO` und liefert `QO = TRUE` sowie einen passenden Status. Sobald neue Positionsdaten eintreffen, erzeugt der Kern das Ereignis `IND` (intern, nicht direkt sichtbar), das die Daten an die drei Delta-Adapter weitergibt. Gleichzeitig wird bei Timeout das Ereignis `TIMEOUT` ausgelöst und der entsprechende Adapter aktualisiert.

Die internen Datenverbindungen stellen sicher, dass die Werte von `TimeDelta`, `LatitudeDelta`, `LongitudeDelta` und `Q_timeout` auf die entsprechenden Adapterdatenport `D1` übertragen werden.

## Technische Besonderheiten

- **Standardkonformität**: Der Baustein realisiert den NMEA 2000 PGN 129027 – „Position Delta, High Precision Rapid Update“.
- **Adapterbasiert**: Die Ausgangsdaten werden über flexible, unidirektionale Adapter bereitgestellt, sodass sie direkt mit anderen Bausteinen eines 4diac-Systems verbunden werden können.
- **Hohe Präzision & Aktualisierungsrate**: Optimiert für Anwendungen, die genaue und schnelle Positionsänderungen benötigen (z. B. in der Landwirtschaft oder Fahrzeugnavigation).
- **Initialisierung mit Status**: Der Baustein liefert eine explizite Initialisierungsbestätigung (QO, STATUS) und kann so in sicherheitskritische Abläufe eingebunden werden.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten endlichen Automaten (ECC) in der XML-Definition. Sein Verhalten wird vollständig durch den internen Kern-FB `I_PosDeltaHighPrecRapidUpd` gesteuert:

1. **Initialisierung abwarten**: Nach Systemstart liegt `QI = FALSE` an; `INIT` wird nicht ausgelöst.
2. **Initialisierung starten**: Bei `INIT`-Ereignis mit `QI = TRUE` wird der Kern aktiviert.
3. **Initialisierung bestätigt**: Der Kern meldet `INITO` mit `QO = TRUE` und positivem Status; anschließend beginnt die Datenbereitstellung.
4. **Datenaktualisierung**: Bei jedem neuen Positionsdelta werden die Adapter automatisch mit den aktuellen Werten versorgt.
5. **Timeout**: Falls keine gültigen Daten mehr empfangen werden, setzt der Kern `Q_timeout = TRUE` und löst das `TIMEOUT`-Ereignis aus.

## Anwendungsszenarien

- **Präzisionslandwirtschaft**: Überwachung von Positionsänderungen eines Traktors oder einer Landmaschine in Echtzeit (z. B. für Lenksysteme oder Applikationskarten).
- **Fahrzeugnavigation**: Verarbeitung von hochgenauen GNSS-Deltas in autonomen Fahrzeugen.
- **ISOBUS‑Integration**: Anbindung an bestehende ISOBUS‑Steuergeräte, die auf PGN 129027 basieren.
- **Sicherheitsüberwachung**: Erkennung von Datenausfällen durch den Timeout‑Adapter.

## Vergleich mit ähnlichen Bausteinen

Ähnliche ISOBUS‑Adapter-Bausteine (z. B. `IA_PosSpeed` oder `IA_TimeDate`) kapseln ebenfalls spezifische PGNs und stellen deren Daten über Adapter bereit. Der `IA_PosDeltaHighPrecRapidUpd` unterscheidet sich durch:

- Spezialisierung auf **Positionsdeltas** (nicht absolute Positionen)
- Unterstützung von **Zeit-, Breiten- und Längengraddelta** sowie separatem **Timeout**-Signal
- Ausrichtung auf hohe **Präzision** und schnelle **Aktualisierungsraten**

Andere Bausteine liefern oft nur eine einzelne Messgröße oder haben keine Timeout-Überwachung.

## Fazit

Der `IA_PosDeltaHighPrecRapidUpd` ist ein spezialisierter ISOBUS-Adapter für hochpräzise Positionsänderungen gemäß NMEA 2000 PGN 129027. Er bietet eine standardkonforme, adapterbasierte Schnittstelle, die sich nahtlos in 4diac-Systeme einfügt. Dank der integrierten Timeout-Erkennung und der expliziten Initialisierungsbestätigung eignet er sich besonders für sicherheitsrelevante Automatisierungslösungen in der Landwirtschaft und Fahrzeugtechnik.