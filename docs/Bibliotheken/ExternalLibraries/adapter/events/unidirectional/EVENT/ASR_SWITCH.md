# ASR_SWITCH


![ASR_SWITCH](./ASR_SWITCH.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ASR_SWITCH** dient als Demultiplexer für **ASR-Ereignisse** (SET/RESET). Er leitet die über den Adapter-Socket `EI` empfangenen Ereignisse wahlweise an den Adapter-Plug `EO0` oder `EO1` weiter – abhängig vom booleschen Wert des Eingangs `G`. Dadurch lassen sich zwei verschiedene Signalpfade in einer Automatisierungsanwendung umschalten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datenverbund | Beschreibung |
|----------|--------------|--------------|
| `EIG`    | `G`          | Setzt den Schaltwert `G` auf den am Eingang `G` anliegenden Booleschen Wert. |

### **Ereignis-Ausgänge**

Der Baustein besitzt keine eigenständigen Ereignisausgänge. Die Ausgabe erfolgt ausschließlich über die **Adapterplugs**.

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| `G`      | `BOOL`| Schalterposition: `FALSE` → Ereignisse werden an `EO0` weitergeleitet, `TRUE` → an `EO1`. |

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Adapter | Richtung | Typ                       | Beschreibung |
|---------|----------|---------------------------|--------------|
| `EI`    | Socket   | `adapter::types::unidirectional::ASR` | Empfang der hereinlaufenden ASR‑Ereignisse (SET/RESET). |
| `EO0`   | Plug     | `adapter::types::unidirectional::ASR` | Ausgang für den Fall `G = FALSE`. |
| `EO1`   | Plug     | `adapter::types::unidirectional::ASR` | Ausgang für den Fall `G = TRUE`. |

## Funktionsweise

Der **ASR_SWITCH** wird durch ein eingehendes Ereignis vom Adapter-Socket `EI` oder durch das Ereignis `EIG` aktiviert. Die Verarbeitung erfolgt in der **Ereignisgesteuerten Ablaufsteuerung (ECC)**:

1. **Schalten von G:**  
   Trifft das Ereignis `EIG` ein, wird der Wert von `G` übernommen. Der Baustein bleibt im Startzustand `START` und wartet auf die nächsten Ereignisse.

2. **Weiterleitung von `EI.SET`:**  
   - `EI.SET` und `G = FALSE`: Übergang in den Zustand `G0_SET`, dort wird `EO0.SET` ausgegeben.  
   - `EI.SET` und `G = TRUE` : Übergang in den Zustand `G1_SET`, dort wird `EO1.SET` ausgegeben.

3. **Weiterleitung von `EI.RESET`:**  
   - `EI.RESET` und `G = FALSE`: Übergang in den Zustand `G0_RESET`, dort wird `EO0.RESET` ausgegeben.  
   - `EI.RESET` und `G = TRUE` : Übergang in den Zustand `G1_RESET`, dort wird `EO1.RESET` ausgegeben.

4. **Rückkehr:**  
   Nach Ausgabe der Aktion springt die ECC sofort (Bedingung = `1`) zurück in den Startzustand `START`, um das nächste Ereignis zu verarbeiten.

## Technische Besonderheiten

- Der Baustein arbeitet ausschließlich mit dem **unidirektionalen Adapter-Typ `ASR`**, das heißt, er kann sowohl SET- als auch RESET-Ereignisse über denselben Adapter transportieren.
- Die Umschaltung erfolgt **ereignisgetriggert** über `EIG` (nicht zyklisch).
- Es werden keine Datenausgänge benötigt – die gesamte Signalisierung erfolgt über die Adapterplugs.
- Durch das sofortige Zurücksetzen in den Startzustand ist der Baustein **deterministisch und schnell** wiedereintrittsbereit.

## Zustandsübersicht

Die folgende Tabelle fasst die ECC-Zustände und die ausgeführten Aktionen zusammen:

| Zustand       | Beschreibung                                 | Aktion(en)        |
|---------------|----------------------------------------------|-------------------|
| `START`       | Warten auf Ereignisse                        | –                 |
| `G0_SET`      | `EI.SET` bei `G = FALSE`                    | Ausgabe `EO0.SET` |
| `G1_SET`      | `EI.SET` bei `G = TRUE`                     | Ausgabe `EO1.SET` |
| `G0_RESET`    | `EI.RESET` bei `G = FALSE`                  | Ausgabe `EO0.RESET` |
| `G1_RESET`    | `EI.RESET` bei `G = TRUE`                   | Ausgabe `EO1.RESET` |

Alle Zustände (außer `START`) kehren mit einer unbedingten Transition (`1`) zurück zu `START`.

## Anwendungsszenarien

- **Steuerung zweier paralleler Prozesspfade:** Je nach Stellung eines Schalters werden SET/RESET-Signale auf unterschiedliche Anlagenteile verteilt.
- **Betriebsartenumschaltung:** Beispielsweise zwischen Automatik- und Handbetrieb – eine logische Größe `G` entscheidet, welche Ereignisse auf welche Logik wirken.
- **Testumgebungen:** Ein Testrahmen kann durch Umschalten von `G` die gleichen Ereignisse an unterschiedliche Testobjekte senden.

## Vergleich mit ähnlichen Bausteinen

- **`SELECT`-Baustein:** Ein klassischer Multiplexer/Demultiplexer arbeitet meist mit Daten, nicht mit Ereignissen. Der **ASR_SWITCH** spezialisiert sich auf ASR-Ereignisweiterleitung.
- **`F_TRIG` / `R_TRIG` / `SR`:** Diese Bausteine setzen oder rücksetzen eine Speicherfunktion, leiten aber keine Ereignisse weiter. Der **ASR_SWITCH** erzeugt selbst keine Zustände, sondern kanalisiert nur vorhandene Ereignisse.
- **Adapterbasierte Lösungen:** In der 4diac-IDE ist die Verwendung von Adaptern typisch für modulare Kommunikation – der **ASR_SWITCH** ist ein Paradebeispiel für die flexible Kopplung von Funktionsbausteinen.

## Fazit

Der **ASR_SWITCH** ist ein einfacher, aber effektiver Funktionsbaustein zur demultiplexierenden Verteilung von SET/RESET-Ereignissen. Durch die Adapter-Schnittstelle lässt er sich nahtlos in ereignisbasierte Automatisierungslösungen integrieren. Seine klare Zustandslogik und minimale Schnittstelle machen ihn zu einem zuverlässigen Baustein für die Umschaltung zwischen zwei Signalpfaden.