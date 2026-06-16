# AUDI_UDINT_AX_SEL


![AUDI_UDINT_AX_SEL](./AUDI_UDINT_AX_SEL.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock `AUDI_UDINT_AX_SEL` realisiert eine binäre Auswahl (binary selection) zwischen zwei Eingangswerten. Er wählt entweder den Wert von `IN0` oder `IN1` auf den Ausgang `OUT` aus, gesteuert durch einen angeschlossenen Adapter vom Typ `AX`. Die Auswahl wird einmalig durch ein Ereignis des Adapters ausgelöst. Zusätzliche Ereignisse erlauben das Aktualisieren der Eingänge.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `EI0` | Event | Setzt den Eingang `IN0` (Wert wird mit dem Daten-Eingang `IN0` verknüpft) |
| `EI1` | Event | Setzt den Eingang `IN1` (Wert wird mit dem Daten-Eingang `IN1` verknüpft) |

### **Ereignis-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `CNF` | Event | Bestätigung der durchgeführten Auswahl (wird nach erfolgreicher Selektion gesendet) |

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `IN0` | UDINT | Erster auswählbarer Eingangswert (unsignierte 32‑Bit‑Ganzzahl) |
| `IN1` | ANY_ELEMENTARY | Zweiter auswählbarer Eingangswert (beliebiger elementarer Datentyp) |

### **Daten-Ausgänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `OUT` | UDINT | Ergebnis der binären Auswahl (der gewählte Wert, als UDINT) |

### **Adapter**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `G` | adapter::types::unidirectional::AX | Steuerungsadapter: liefert das Auswahlkriterium (Daten `G.D1`) und das Triggersignal (`G.E1`) für die Selektion |

## Funktionsweise
Der Baustein arbeitet in zwei Schritten:
1. **Aktualisierung der Eingänge:** Über die Ereignisse `EI0` und `EI1` können die Werte von `IN0` bzw. `IN1` im internen Kontext gespeichert werden. Diese Ereignisse sind nicht direkt mit der eigentlichen Auswahl verbunden, sondern dienen der zeitlichen Trennung von Datenerfassung und Auswahl.
2. **Selektion:** Ein Ereignis auf `G.E1` (vom Adapter `G`) triggert den internen Funktionsbaustein `F_SEL` (Typ `iec61131::selection::F_SEL`). Der Adapter-Datenwert `G.D1` (vom Typ `AX`) bestimmt, welcher Eingang auf den Ausgang gelegt wird:
   - Bei `G.D1 = FALSE` (0) wird `IN0` auf `OUT` übernommen.
   - Bei `G.D1 = TRUE` (1) wird `IN1` auf `OUT` übernommen.
   Nach erfolgreicher Auswahl wird das Ereignis `CNF` gesendet.

Der Daten‑Ausgang `OUT` ist stets vom Typ `UDINT`. Der Eingang `IN1` erlaubt beliebige elementare Datentypen, die bei der Selektion implizit in `UDINT` konvertiert werden. Falls dies nicht möglich ist, kann der Baustein einen Fehler erzeugen (je nach Laufzeitumgebung).

## Technische Besonderheiten
- **ANY_ELEMENTARY‑Unterstützung:** Der zweite Eingang `IN1` kann Werte unterschiedlicher elementarer Typen (z. B. SINT, INT, REAL, BOOL) annehmen. Die Konvertierung nach UDINT erfolgt automatisch.
- **Adapter‑basierte Steuerung:** Die Auswahl wird nicht durch einen diskreten Daten‑Eingang, sondern über einen Adapter realisiert – dies ermöglicht eine saubere Kapselung des Selektorsignals (z. B. von einem Sensor oder einer Steuerlogik).
- **Ereignisgesteuerte Aktualisierung:** Die Eingänge `IN0` und `IN1` werden nur bei Bedarf über die Ereignisse `EI0`/`EI1` übernommen, was die Kommunikation über Feldbusse optimieren kann.

## Zustandsübersicht
Der Baustein enthält keine explizite Zustandsmaschine. Die Funktionalität ist rein ereignisgesteuert:
- Nach dem Setzen von `IN0` oder `IN1` (über `EI0`/`EI1`) wartet der Baustein auf das Triggersignal des Adapters `G.E1`.
- Mit Eintreffen von `G.E1` wird sofort `F_SEL` ausgeführt und `CNF` ausgegeben.
- Zwischen den Schritten ist der Baustein in einem passiven Ruhezustand.

## Anwendungsszenarien
- **Auswahl zwischen zwei Messwerten:** Ein Sensor liefert über den Adapter `G` das Auswahlkriterium (z. B. Schwellwertüberschreitung). `IN0` könnte einen Minimal‑, `IN1` einen Maximalwert repräsentieren.
- **Umschaltung von Parameter-Sets:** Über `EI0` und `EI1` werden zwei verschiedene Konfigurationswerte geladen. Ein externer Regler aktiviert über `G` die passende Konfiguration.
- **Redundante Signale:** Zwei redundante Quellen (z. B. Geschwindigkeitssensoren) liefern die Werte, und ein Signal entscheidet, welche Quelle verwendet wird.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaften |
|----------|---------------|
| `MUX` (IEC 61131) | Mehrere Eingänge, Index-Auswahl; benötigt einen Index-Eingang als skalaren Wert. |
| `SEL` (IEC 61131) | Binäre Auswahl mit einem BOOL-Eingang. |
| `AUDI_UDINT_AX_SEL` | Adapter‑gesteuerte binäre Auswahl mit getrennter Aktualisierung der Eingänge, speziell für UDINT‑Ausgang und Unterstützung von ANY_ELEMENTARY. |

Im Vergleich zu den IEC‑Standardbausteinen bietet dieser FB eine entkoppelte Kommunikation über Adapter und extrahierte Ereignisse für die Datenerfassung – vorteilhaft in modularen, ereignisbasierten Systemen.

## Fazit
Der Funktionsblock `AUDI_UDINT_AX_SEL` stellt eine flexible, adaptergesteuerte binäre Auswahl dar. Er eignet sich besonders für Anwendungen, bei denen das Selektorsignal von einem externen Gerät (z. B. einem Profinet‑Adapter) stammt und die Eingangswerte asynchron aktualisiert werden müssen. Die Unterstützung von `ANY_ELEMENTARY` am zweiten Eingang erhöht die Wiederverwendbarkeit, während der einheitliche `UDINT`‑Ausgang die Weiterverarbeitung vereinfacht.