# FIELDBUS_WORD_TO_SIGNAL_SCALED


![FIELDBUS_WORD_TO_SIGNAL_SCALED](./FIELDBUS_WORD_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **FIELDBUS_WORD_TO_SIGNAL_SCALED** dient dazu, einen digitalen Feldbus-Rohwert (16‑Bit WORD) in einen skalierten physikalischen Signalwert (REAL) umzurechnen. Dabei wird nur dann ein gültiger Ausgang geliefert, wenn der eingehende Wert als gültiges Signal erkannt wird. Der Baustein prüft die Gültigkeit anhand einer vordefinierten Konstanten (`VALID_SIGNAL_W`) und kann unsichere oder „nicht verfügbare“ Werte zuverlässig unterdrücken.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|-------------|
| `INIT`   | Initialisierungsanfrage; setzt die Skalierungsfaktoren (`SCALE`, `OFFSET`). |
| `REQ`    | Normale Verarbeitungsanfrage; wertet den aktuellen Eingang `IN` aus. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|-------------|
| `INITO`  | Bestätigung der Initialisierung. |
| `CNF`    | Bestätigung der Verarbeitung; signalisiert, dass die Ausgänge `OUT` und `VALID` aktualisiert wurden. |

### **Daten-Eingänge**

| Name    | Datentyp | Vorgabewert     | Beschreibung |
|---------|----------|-----------------|-------------|
| `IN`    | WORD     | `NOT_AVAILABLE_WM` | Rohwert vom Feldbus (z. B. 0…65535). Die Konstante `NOT_AVAILABLE_WM` kennzeichnet einen ungültigen Startwert. |
| `SCALE` | REAL     | `1.0`           | Skalierungsfaktor (wird mit dem eingelesenen Wert multipliziert). |
| `OFFSET`| DINT     | `0`             | Ganzzahliger Offset, der nach der Skalierung addiert wird (als REAL konvertiert). |

### **Daten-Ausgänge**

| Name    | Datentyp | Vorgabewert | Beschreibung |
|---------|----------|-------------|-------------|
| `OUT`   | REAL     | `0.0`       | Skalierter Signalwert. Nur gültig, wenn `VALID = TRUE`. |
| `VALID` | BOOL     | `FALSE`     | Gültigkeitsflag – `TRUE`, wenn der eingehende Rohwert als gültiges Signal erkannt wurde. |

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Der Baustein arbeitet zustandsgesteuert:

1. **INIT‑Zustand**:  
   Nach dem Eintreten des `INIT`-Ereignisses wird der Initialisierungsalgorithmus (leer) ausgeführt und das Ereignis `INITO` ausgegeben. Die Skalierungsfaktoren werden dabei an den Eingängen `SCALE` und `OFFSET` übernommen (die Werte liegen bereits an den Eingängen an).

2. **REQ‑Zustand** (Hauptlogik):  
   Bei jedem `REQ`-Ereignis wird folgender Algorithmus durchlaufen:
   - Der eingehende `IN` (WORD) wird zunächst in `UINT` konvertiert.
   - Liegt dieser Wert **kleiner oder gleich** dem in der globalen Konstanten `VALID_SIGNAL_W` definierten Grenzwert (ebenfalls als WORD/UINT), gilt das Signal als **gültig**.
   - Bei Gültigkeit:  
     `OUT = UINT_TO_REAL(IN) * SCALE + DINT_TO_REAL(OFFSET)`  
     `VALID = TRUE`
   - Bei Ungültigkeit:  
     `OUT = 0.0`  
     `VALID = FALSE`
   - Anschließend wird das `CNF`-Ereignis ausgelöst, das die aktualisierten Ausgänge `OUT` und `VALID` begleitet.

Der Vergleichswert `VALID_SIGNAL_W` sowie der Standard‑Eingangswert `NOT_AVAILABLE_WM` sind als Konstanten im Namespace `eclipse4diac::signalprocessing::FIELDBUS_SIGNAL` importiert.

## Technische Besonderheiten
- **Verwendung von externen Konstanten**: Die Gültigkeitsschwelle (`VALID_SIGNAL_W`) und der „Nicht verfügbar“‑Marker (`NOT_AVAILABLE_WM`) werden aus einer globalen Bibliothek bezogen. Dies ermöglicht eine konsistente Signaldefinition über mehrere FB‑Instanzen hinweg.
- **Skalierung mit REAL und DINT**: Der Offset ist als `DINT` definiert, wird aber durch `DINT_TO_REAL` in eine Gleitkommazahl gewandelt. Dies kann bei großen Werten zu geringfügigen Rundungsfehlern führen, ist in der Praxis aber meist vernachlässigbar.
- **Gültigkeitslogik**: Anders als bei einfachen „Word‑to‑Real“‑Wandlern wird der Wert nur dann ausgegeben, wenn er innerhalb des definierten gültigen Bereichs liegt. Dadurch werden Fehlinterpretationen von Störungen oder ungültigen Telegrammen vermieden.
- **Initialverhalten**: Die Eingänge `IN` haben als Vorgabewert `NOT_AVAILABLE_WM`, sodass der FB nach einem Reset oder bei fehlender Kommunikation sofort „ungültig“ meldet, bis ein gültiger Wert ankommt.

## Zustandsübersicht

| Zustand | Inhalt | Aktion | Ausgangsereignis |
|---------|--------|--------|-----------------|
| `INIT`  | Initialisierung (leerer Algorithmus) | – | `INITO` |
| `REQ`   | Signalverarbeitung | Berechnung von `OUT` und `VALID` | `CNF` |

Der FB kennt keine weiteren Zustände; nach jedem Ereignis kehrt er in den entsprechenden Startzustand zurück. Es gibt keine explizite Fehlerbehandlung oder Timeouts.

## Anwendungsszenarien
- **Landtechnik / Agrarsteuerungen**: Ein Feldbus-Gerät (z. B. ISOBUS) liefert Rohwerte für Sensoren (Drehzahl, Temperatur, Druck). Der FB skaliert diese auf physikalische Einheiten und erkennt ungültige Messbereiche.
- **Industrielle Automatisierung**: Bei Profibus/IO‑Link‑Anbindung können Wort‑Codes in prozessrelevante Größen umgerechnet werden – z. B. 0…1000 → 0,0…10,0 V.
- **Diagnose‑ und Sicherheitsfunktionen**: Durch die Gültigkeitsprüfung lassen sich Signalverluste oder Bereichsüberschreitungen einfach erkennen und eine Fehlerreaktion einleiten.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Unterschiede |
|----------|-------------|
| **FIELDBUS_WORD_TO_SIGNAL** (ohne Skalierung) | Bildet den Rohwert 1:1 ab, ohne Multiplikation/Addition. |
| **WORD_TO_REAL** (Standard‑IEC‑Baustein) | Reine Typumwandlung ohne Gültigkeitsprüfung und Skalierung. |
| **SCALING_FB** | Meist mit separatem Gültigkeits- und Skalierungszweig; dieser FB vereint beides in einem Schritt. |

Die Stärke von `FIELDBUS_WORD_TO_SIGNAL_SCALED` liegt in der **Kombination aus Gültigkeitsprüfung, Skalierung und Offset** in einem einzigen, überschaubaren FB.

## Fazit
Der Funktionsblock bietet eine kompakte und robuste Lösung zur Aufbereitung von Feldbus‑Rohdaten. Er integriert die typische Aufgabenkette „Prüfen → Skalieren → Offsieten“ und sorgt durch die feste Gültigkeitsschwelle für eine klare Trennung zwischen normalen Messwerten und Fehlersignalen. Durch die Verwendung externer Konstanten bleibt er flexibel anpassbar, ohne die innere Logik zu verkomplizieren. Ideal für sicherheitskritische oder diagnostische Anwendungen in der Automatisierungstechnik.