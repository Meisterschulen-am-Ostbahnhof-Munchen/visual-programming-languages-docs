# NumericValue_PHYSA


![NumericValue_PHYSA](./NumericValue_PHYSA.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **NumericValue_PHYSA** ist ein Eingangs-Service-Interface-Funktionsblock (SIFB) nach ISO 11783-6. Seine Aufgabe besteht darin, einen physikalischen REAL-Wert über einen AR-Adapter (Adapter Typ *unidirectional::AR*) bereitzustellen. Intern kapselt er den Baustein `NumericValue_PHYS` und dessen gesamte Logik zur Umrechnung und Bereitstellung des Wertes.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| INIT | EInit | Initialisiert den Baustein (mit Parametern und Objekt-Pool) |
| REQ  | Event | Löst die Ausgabe des aktuellen physikalischen Wertes aus |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| INITO | EInit | Bestätigung der erfolgreichen Initialisierung |

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| QI    | BOOL   | Eingangsqualifizierer (aktiviert/steuert die Verarbeitung) |
| PARAMS| STRING | Parameter für den Dienst (z. B. Konfigurationsstring) |
| stObj | *NumericObjectPool_S* | Objekt-Pool-Eigenschaften: Objekt-ID (UINT16), Skalierung, Offset, Dezimalstellen |

### **Daten-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| QO    | BOOL   | Ausgangsqualifizierer (zeigt erfolgreiche Verarbeitung an) |
| STATUS| STRING | Statusmeldung (OK oder Fehlertext) |

### **Adapter**

| Name | Typ | Beschreibung |
|------|-----|-------------|
| rPhys | *adapter::types::unidirectional::AR* | Adapter-Schnittstelle zur Ausgabe des physikalischen REAL-Wertes (Ereigniskanal `E1` und Datenkanal `D1`) |

## Funktionsweise

Der Baustein ist als reiner Wrapper um den internen FB `NumericValue_PHYS` realisiert. Sämtliche Ein- und Ausgänge werden eins‑zu‑eins auf den inneren Baustein durchverbunden:

- Die Ereignisse `INIT` und `REQ` werden direkt an `NumericValue_PHYS` weitergeleitet.
- Das Initialisierungs‑Bestätigungsereignis `INITO` des inneren FB wird nach außen geführt.
- Das Ausgangsereignis `IND` von `NumericValue_PHYS` wird mit dem Ereigniseingang `rPhys.E1` des Adapters verbunden, sodass der Adapter bei jeder neuen Wertberechnung ein Ereignis erhält.
- Die Daten‑Eingänge (`QI`, `PARAMS`, `stObj`) werden an den inneren FB verdrahtet.
- Die Daten‑Ausgänge (`QO`, `STATUS`) kommen direkt vom inneren FB.
- Der physikalische REAL‑Wert aus `NumericValue_PHYS.rPhys` wird auf den Datenkanal `rPhys.D1` des Adapter-Plugs gelegt.

Damit ist der FB ein reiner Konnektor, der die Funktionalität von `NumericValue_PHYS` um eine standardisierte Adapter‑Schnittstelle ergänzt, ohne selbst zusätzliche Logik zu implementieren.

## Technische Besonderheiten

- **Eingesetzte Datentypen:** Die physikalischen Eigenschaften des Messwerts (Skalierung, Offset, Dezimalstellen) werden über den strukturierten Typ `logiBUS::utils::conversion::phys::NumericObjectPool_S` definiert.
- **Adapter‑Kopplung:** Der AR‑Adapter (unidirektional) ermöglicht eine lose Kopplung an nachfolgende Bausteine, die den physikalischen Wert konsumieren.
- **Typ‑Hash:** Der Baustein trägt ein Attribut `eclipse4diac::core::TypeHash` zur Identifikation der exakten Version.
- **Keine interne Zustandsmaschine:** Der FB delegiert alle Zustandslogik an den gekapselten Baustein.

## Zustandsübersicht

Da der FB keine eigene Zustandsmaschine besitzt, ergibt sich der Zustand vollständig aus dem inneren `NumericValue_PHYS`:

1. **Initialisierungsphase:** Nach dem Ereignis `INIT` wird der FB konfiguriert. Erst nach `INITO` ist er betriebsbereit.
2. **Betriebsphase:** Mit jedem `REQ` wird der aktuelle physikalische Wert berechnet und über den Adapter ausgegeben.
3. **Fehlerzustand:** Bei fehlerhafter Initialisierung oder ungültigen Parametern wird `STATUS` mit einem entsprechenden Text belegt und `QO` auf FALSE gesetzt.

## Anwendungsszenarien

- **ISOBUS‑Steuergeräte:** Der FB eignet sich ideal, um Sensordaten (z. B. Drehzahl, Druck, Temperatur) in ein standardisiertes Adapter‑Interface zu wandeln, wie es in landwirtschaftlichen Maschinen gemäß ISO 11783‑6 gefordert wird.
- **Messwerterfassung mit Skalierung:** Über die Parameter‑Struktur können Rohwerte mit individuellem Offset und Skalierungsfaktor in physikalische Einheiten umgerechnet werden.
- **Modulare Systeme:** Durch die Adapter‑Schnittstelle können mehrere Ausgabebausteine einfach an verschiedene Konsumenten (z. B. Visualisierung, Logik) angeschlossen werden.

## Vergleich mit ähnlichen Bausteinen

- **NumericValue_PHYS** (ohne „A“‑Suffix): Der reine Funktionsblock ohne Adapter‑Schnittstelle. Er stellt den physikalischen Wert nur als Datenausgang (`rPhys`) bereit. Der vorliegende FB fügt den Adapter‑Plug hinzu, um die Kopplung über einen standardisierten Kanal zu ermöglichen.
- **NumericValue_RAW / NumericValue_SCALED** (hypothetisch): Diese Bausteine würden Roh- bzw. skalierte Werte ohne Bezug zu einem Objekt‑Pool liefern. `NumericValue_PHYSA` hingegen nutzt die Struktur `NumericObjectPool_S` mit expliziten Umrechnungsparametern.

## Fazit

Der Funktionsblock `NumericValue_PHYSA` bietet eine saubere, adapter‑basierte Schnittstelle zur Ausgabe physikalischer REAL‑Werte. Durch die Kapselung der gesamten Umrechnungslogik in `NumericValue_PHYS` bleibt er schlank und wartbar. Sein Einsatz empfiehlt sich überall dort, wo nach ISO 11783‑6 konforme, physikalische Messwerte in einem modularen Automatisierungssystem bereitgestellt werden müssen.