# F_PHYS_LREAL_TO_RAW


![F_PHYS_LREAL_TO_RAW](./F_PHYS_LREAL_TO_RAW.svg)

*Bild nicht verfügbar*

* * * * * * * * * *

## Einleitung

Der Funktionsblock F_PHYS_LREAL_TO_RAW dient der Umrechnung eines physikalischen Messwerts im Datentyp LREAL in einen ISOBUS-konformen Rohwert als UDINT. Dabei werden Sättigungsgrenzen eingehalten und Über- bzw. Unterlaufzustände als boolsche Ausgänge signalisiert. Die Konvertierung folgt der ISOBUS‑Formel:  
**Anzeigewert = (Rohwert + Offset) · Skalierung**  
**Rohwert = UDINT( DINT( physikalischer Wert / Skalierung ) – Offset )**  

Der Baustein eignet sich für Applikationen, die physikalische Größen in das ISOBUS‑Protokoll einbinden müssen, insbesondere in der Land- und Nutzfahrzeugtechnik.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung | Mitgeführte Variablen |
|----------|--------------|-----------------------|
| `REQ`    | Startet die Umrechnung | `lrPhys`, `stObj`     |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung | Mitgeführte Variablen |
|----------|--------------|-----------------------|
| `CNF`    | Bestätigt die abgeschlossene Umrechnung | `xOver`, `xUnder`     |

### **Daten-Eingänge**

| Name    | Typ                                                      | Initialwert | Beschreibung                                      |
|---------|----------------------------------------------------------|-------------|---------------------------------------------------|
| `lrPhys`| `LREAL`                                                  | –           | Physikalischer Eingangswert (z. B. Temperatur, Druck) |
| `stObj` | `logiBUS::utils::conversion::phys::NumericObjectPool_S`  | `(u16ObjId := 65535, r32Scale := 1.0, i32Offset := 0, u8Decimals := 0)` | Datenstruktur mit Skalier- und Offsetparametern   |

### **Daten-Ausgänge**

| Name     | Typ    | Beschreibung                                 |
|----------|--------|----------------------------------------------|
| *(kein Name)*  | `UDINT` | Berechneter ISOBUS‑Rohwert (0 … 4294967295) |
| `xOver`  | `BOOL` | `TRUE`, wenn der Eingang die obere Grenze überschreitet (Überlauf) |
| `xUnder` | `BOOL` | `TRUE`, wenn der Eingang die untere Grenze unterschreitet (Unterlauf) |

### **Adapter**

Der Funktionsblock verwendet keine Adapter.

## Funktionsweise

Der FB führt folgende Schritte aus:

1. **Berechnung der Grenzen:**  
   - Untere Grenze: `i32Offset * r32Scale`  
   - Obere Grenze: `(i32Offset + 4294967295) * r32Scale`

2. **Vergleich und Sättigung:**  
   - Ist `lrPhys > obere Grenze` → Rohwert = **UDINT#4294967295**, `xOver = TRUE`.  
   - Ist `lrPhys < untere Grenze` → Rohwert = **0**, `xUnder = TRUE`.  
   - Andernfalls → Rohwert = `DINT_TO_UDINT( LREAL_TO_DINT( lrPhys / r32Scale ) - i32Offset )`, keine Über-/Unterlaufmeldung.

3. **Ausgabe:** Der berechnete Rohwert wird am unbenannten `UDINT`-Ausgang bereitgestellt und das Ereignis `CNF` ausgelöst.

## Technische Besonderheiten

- **ISOBUS‑Konformität:** Die Umrechnung folgt exakt der ISOBUS‑Spezifikation (ISO 11783).  
- **Sättigungsverhalten:** Kritische Bereiche werden durch die Über-/Unterlaufausgänge `xOver` und `xUnder` abgebildet, sodass Folgefunktionen (z. B. Alarmierung) reagieren können.  
- **Skalierungseinheit:** Der Skalierungsfaktor `r32Scale` ist vom Typ `REAL` und wird direkt in die Berechnung einbezogen.  
- **Integer‑Umwandlung:** Die Konvertierung von LREAL über DINT zu UDINT erfolgt mit der in IEC 61499 üblichen Rundung (Abschneiden der Dezimalstellen).  
- **Keine Zustandsautomaten:** Der FB arbeitet rein funktional ohne interne Zustandsmaschine.

## Zustandsübersicht

Der Funktionsblock besitzt keine explizite Zustandsmaschine. Die Berechnung wird durch das Ereignis `REQ` angestoßen; nach einem Zyklus wird das Ergebnis am Datenausgang bereitgestellt und das Ereignis `CNF` gesendet. Die Ausführungszeit ist deterministisch und hängt nur von der Laufzeitumgebung ab.

## Anwendungsszenarien

- **Landwirtschaftliche Steuergeräte:** Umwandlung von Sensorwerten (z. B. Drehmoment, Druck) in ISOBUS‑Rohdaten für die Übertragung an Terminals oder Aktoren.  
- **Diagnose und Überwachung:** Erkennung von Messbereichsüberschreitungen durch `xOver`/`xUnder` zur Auslösung von Warnungen.  
- **Datenlogging:** Aufbereitung physikalischer Messwerte für die Archivierung im ISOBUS‑Format.  

## Vergleich mit ähnlichen Bausteinen

Typische Alternativen sind selbstgeschriebene Rechenfunktionen oder generische Konvertierungsbausteine.  
Der F_PHYS_LREAL_TO_RAW bietet folgende Vorteile:  
- **Vorgegebene Parametrierung** über die Struktur `NumericObjectPool_S` (ObjID, Skalierung, Offset, Dezimalstellen).  
- **Integrierte Sättigung** und Grenzwertüberwachung.  
- **Wiederverwendbar** in allen logiBUS‑Projekten.  

Nachteile gegenüber einer maßgeschneiderten Lösung sind die Bindung an die ISOBUS‑Formel und die festgelegte Datenstruktur.

## Fazit

Der Funktionsblock F_PHYS_LREAL_TO_RAW ist eine kompakte, normkonforme Lösung zur Umrechnung physikalischer Messwerte in das ISOBUS‑Rohdatenformat. Seine Sättigungslogik und die Überwachungsausgänge machen ihn robust und sicher für den Einsatz in industriellen und landwirtschaftlichen Steuerungssystemen. Die Verwendung vordefinierter Strukturparameter erleichtert die Integration und reduziert die Fehleranfälligkeit bei der Parametrierung.