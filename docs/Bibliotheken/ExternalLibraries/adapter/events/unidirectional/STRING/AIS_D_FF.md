# AIS_D_FF


![AIS_D_FF](./AIS_D_FF.svg)

* * * * * * * * * *

## Einleitung

Der Baustein `AIS_D_FF` realisiert ein taktflankengesteuertes D‑Flipflop (Data Latch). Er dient dazu, einen Datenwert bei einem eingehenden Taktereignis zu speichern und auszugeben. Die Kommunikation erfolgt ausschließlich über AIS‑Adapter (unidirectional), sodass der Baustein in adapterbasierte Komponentenarchitekturen eingebunden werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge. Das Taktsignal wird über den Socket-Adapter **I** (Ereignisport `E1`) bereitgestellt.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge. Das Ausgangsereignis wird über den Plug-Adapter **Q** (Ereignisport `E1`) gesendet.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge. Der zu übernehmende Datenwert wird über den Socket-Adapter **I** (Datenport `D1`) empfangen.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Der gespeicherte Wert wird über den Plug-Adapter **Q** (Datenport `D1`) ausgegeben.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| **I**   | `adapter::types::unidirectional::AIS` | Socket | Eingangsadapter: Taktsignal (Ereignis `E1`) und Dateneingang (Daten `D1`) |
| **Q**   | `adapter::types::unidirectional::AIS` | Plug   | Ausgangsadapter: Bestätigungsereignis (Ereignis `E1`) und gespeicherter Datenwert (Daten `D1`) |

## Funktionsweise

Der Baustein kapselt den IEC‑61499‑Standardbaustein `E_D_FF_ANY`. Bei einer positiven Flanke des Taktsignals (Ereignis `I.E1`) wird der aktuelle Wert von `I.D1` übernommen und intern im Flipflop gespeichert. Anschließend wird ein Ereignis am Ausgang `Q.E1` ausgelöst und der gespeicherte Wert am Port `Q.D1` bereitgestellt. Der Ausgangswert bleibt solange erhalten, bis das nächste Taktereignis eintrifft.

## Technische Besonderheiten

- **Reine Adapter‑Schnittstelle**: Der Baustein besitzt keine direkten Event‑ oder Datenports, sondern verwendet ausschließlich AIS‑Adapter. Dies ermöglicht eine flexible Kopplung mit anderen adapterbasierten Komponenten.
- **Generischer Datentyp**: Der interne `E_D_FF_ANY`‑Baustein unterstützt beliebige Datentypen. Die Datenbreite und der Typ werden durch die verwendete Adapter‑Implementierung bestimmt.
- **Ereignisgesteuerte Datenweitergabe**: Eine Aktualisierung des Ausgangs erfolgt nur bei einem eingehenden Taktereignis. Ohne Taktereignis bleibt der Ausgang unverändert.

## Zustandsübersicht

Da der Baustein das Verhalten eines D‑Flipflops implementiert, können zwei Zustände unterschieden werden:

| Zustand | Beschreibung |
|---------|--------------|
| **Ruhezustand** | Der gespeicherte Wert bleibt konstant. Es wird kein Ausgangsereignis erzeugt. |
| **Übernahme** | Bei Eintreffen eines Taktereignisses wird der aktuelle Eingangswert übernommen, der Ausgang wird aktualisiert und ein Ausgangsereignis gesendet. |

Das Flipflop ist flankengesteuert (steigende Flanke) und nicht pegelgesteuert.

## Anwendungsszenarien

- **Datenpuffer in Adapter‑Netzwerken**: Zwischenspeichern von Werten, die nur bei bestimmten Ereignissen gültig sind (z. B. Taktsignale von Sensoren).
- **Synchronisation**: Abgleich von Daten zwischen Komponenten, die über asynchrone Ereignisse kommunizieren.
- **Register in Steuerungsanwendungen**: Aufbau von Schieberegistern oder einfachen Speicherzellen in IEC‑61499‑Systemen, die AIS‑Adapter verwenden.

## Vergleich mit ähnlichen Bausteinen

- **`E_D_FF_ANY`** – Das direkte Funktionsblock‑Äquivalent mit standardmäßigen Event‑ und Datenports. `AIS_D_FF` kapselt diesen Baustein in eine adapterbasierte Schnittstelle.
- **SR‑Flipflop** – Speichert einen binären Zustand über Set‑ und Reset‑Eingänge, während `AIS_D_FF` einen beliebigen Datenwert über ein Taktsignal speichert.
- **Latch (pegelgesteuert)** – Ein Latch übernimmt den Eingangswert, solange das Taktsignal aktiv ist; `AIS_D_FF` reagiert dagegen nur auf eine Flanke und ist damit unempfindlicher gegen Rauschen und Glitches.

## Fazit

`AIS_D_FF` ist ein nützlicher Baustein, um ein flankengesteuertes D‑Flipflop in adapterbasierten Architekturen einzusetzen. Durch die Kapselung des bewährten `E_D_FF_ANY`‑Funktionsblocks bietet er zuverlässige Speicherfunktionalität und lässt sich nahtlos in bestehende AIS‑Kommunikationsstrukturen integrieren.