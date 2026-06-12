# ADI_D_FF


![ADI_D_FF](./ADI_D_FF.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `ADI_D_FF` realisiert ein Daten-Latch (D‑Flipflop) auf Basis von Adaptern. Er dient dazu, einen Booleschen Wert bei Eintreffen eines Ereignisses zu speichern und auszugeben. Der Baustein kapselt den industriellen Standard‑FB `E_D_FF_ANY` und kommuniziert ausschließlich über die unidirektionalen Adapter `ADI`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine separaten Ereignis–Eingänge. Die Ereignissteuerung erfolgt ausschließlich über den Adapter `I`.

### **Ereignis-Ausgänge**

Der FB besitzt keine separaten Ereignis–Ausgänge. Die Ereignisausgabe erfolgt ausschließlich über den Adapter `Q`.

### **Daten-Eingänge**

Der FB besitzt keine separaten Daten–Eingänge. Die Datenaufnahme erfolgt über den Adapter `I`.

### **Daten-Ausgänge**

Der FB besitzt keine separaten Daten–Ausgänge. Die Datenausgabe erfolgt über den Adapter `Q`.

### **Adapter**

| Typ | Bezeichnung | Richtung | Beschreibung |
|-----|-------------|----------|--------------|
| `adapter::types::unidirectional::ADI` | `I` | Eingang (Socket) | Liefert das Taktsignal (`E1`) und den zu latchnden Datenwert (`D1`). |
| `adapter::types::unidirectional::ADI` | `Q` | Ausgang (Plug)  | Gibt den gespeicherten Datenwert (`D1`) und ein Bestätigungsereignis (`E1`) aus. |

## Funktionsweise

Der `ADI_D_FF` arbeitet nach dem Prinzip eines flankengesteuerten D‑Flipflops. Jedes am Adapter `I` eintreffende Ereignis `E1` wird als Takt (CLK) interpretiert. Bei jedem Takt wird der aktuelle Datenwert `D1` vom Eingang übernommen, intern gespeichert und am Adapter `Q` sowohl als neuer Datenwert (`D1`) als auch als Bestätigungsereignis (`E1`) ausgegeben.

Im Inneren wird der standardisierte IEC‑61499‑Baustein `E_D_FF_ANY` verwendet, der exakt diese Funktion bereitstellt. Die Adapter dienen als einheitliche, wiederverwendbare Schnittstellen für Ereignisse und Daten.

## Technische Besonderheiten

- Der gesamte Daten- und Ereignisaustausch erfolgt über Adapter vom Typ `ADI` (unidirektionale Ereignis- und Datenübertragung). Dadurch ist der FB leicht in adapterbasierte Architekturen integrierbar.
- Es ist kein eigenständiger Zustandsautomat implementiert; die gesamte Logik wird durch den internen FB `E_D_FF_ANY` realisiert.
- Die Implementierung folgt dem Standard IEC 61499-1 (Annex A) und nutzt die Eclipse 4diac-IDE.

## Zustandsübersicht

Der FB besitzt keine expliziten Zustände im Sinne einer Zustandsmaschine. Das Verhalten entspricht einem einfachen Flipflop:

- Bei jedem Takt (Ereignis an `I.E1`) wird der aktuelle Wert von `I.D1` übernommen und an `Q.D1` weitergegeben.
- Der gespeicherte Wert bleibt bis zum nächsten Takt konstant.
- Der Ausgang `Q.E1` signalisiert die Übernahme eines neuen Wertes.

## Anwendungsszenarien

- **Synchronisation:** Festhalten eines asynchron eintreffenden Booleschen Signals zu einem definierten Taktzeitpunkt.
- **Zwischenspeicher (Latch):** Halten eines Datenwertes zur Weiterverarbeitung in nachfolgenden FB‑Netzwerken.
- **Puffern:** Entkopplung von Ereignis- und Datenquellen von der weiteren Verarbeitung (z. B. bei zeitkritischen Abläufen).

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschiede |
|----------|----------|--------------|
| `ADI_SR_FF` | Set‑Reset‑Flipflop | Speichert aufgrund von Setzen/Rücksetzen, nicht taktgesteuert. |
| `ADI_T_FF` | T‑Flipflop | Schaltet den Zustand bei jedem Takt um (Toggle). |
| `ADI_D_FF` | D‑Flipflop | Speichert den anliegenden Datenwert bei Taktflanke (wie hier beschrieben). |

## Fazit

Der `ADI_D_FF` ist ein kompakter, adapterbasierter D‑Flipflop‑Baustein für die 4diac‑IDE. Er bietet eine saubere Trennung von Takt und Datum und ist ideal für den Einsatz in ereignisgesteuerten Automatisierungslösungen geeignet. Die Kapselung durch Adapter erhöht die Wiederverwendbarkeit und vereinfacht die Integration in bestehende Projekte.