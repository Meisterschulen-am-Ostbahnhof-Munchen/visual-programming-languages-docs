# AD_D_FF


![AD_D_FF](./AD_D_FF.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AD_D_FF** realisiert ein **Data-Latch (D‑Flipflop)**. Er übernimmt einen Datenwert bei einem eingehenden Ereignis und hält diesen Wert bis zur nächsten Übernahme bereit. Die Schnittstelle ist ausschließlich über standardisierte **Adapter** definiert, was eine flexible Verkabelung in komplexen Automatisierungssystemen ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine direkten Ereignis-Eingänge. Der FB verwendet ausschließlich den **Eingangsadapter `I`**, der über seinen internen Ereigniskanal das Taktsignal liefert.

### **Ereignis-Ausgänge**
Keine direkten Ereignis-Ausgänge. Der FB verwendet ausschließlich den **Ausgangsadapter `Q`**, der über seinen internen Ereigniskanal signalisiert, dass ein neuer Datenwert bereitsteht.

### **Daten-Eingänge**
Keine direkten Daten-Eingänge. Der zu latchende Wert wird über den **Datenkanal des Eingangsadapters `I`** bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Der latched Wert wird über den **Datenkanal des Ausgangsadapters `Q`** zur Verfügung gestellt.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `I` (Socket) | Eingang | `adapter::types::unidirectional::AD` | Liefert das Taktsignal (E1) und den zu speichernden Datenwert (D1). |
| `Q` (Plug) | Ausgang | `adapter::types::unidirectional::AD` | Gibt nach dem Taktereignis den gespeicherten Datenwert aus (E1 als Bestätigung, D1 als Daten). |

Die Adapter vom Typ `unidirectional::AD` definieren je einen Ereigniskanal (`E1`) und einen Datenkanal (`D1`). Die genauen Datentypen sind durch die Adapterdefinition festgelegt (üblicherweise `ANY`).

## Funktionsweise

Der FB verwendet intern den elementaren Baustein `E_D_FF_ANY` (aus der IEC‑61499‑Standardbibliothek). Dessen Verhalten:

1. **Bei jedem Ereignis am Takteingang (CLK)** wird der aktuelle Datenwert am Eingang `D` an den Ausgang `Q` übernommen. Die Übernahme erfolgt flankengetriggert (steigende Flanke des Ereignisses).
2. Der Ausgang `Q` bleibt so lange unverändert, bis ein neues Taktereignis eintrifft.

Die Verschaltung im FBNetzwerk:
- Das Ereignis `I.E1` wird mit `CLK` verbunden.
- Das Datum `I.D1` wird mit `D` verbunden.
- Der Ereignisausgang `EO` des internen Bausteins wird an `Q.E1` weitergeleitet.
- Der Datenausgang `Q` des internen Bausteins wird an `Q.D1` weitergeleitet.

Somit wird bei jedem Ereignis am Eingangsadapter der anliegende Datenwert übernommen und sofort über den Ausgangsadapter ausgegeben. Der Wert bleibt bis zum nächsten Ereignis erhalten.

## Technische Besonderheiten

- **Reine Adapter-Schnittstelle:** Der FB besitzt keine klassischen Event-/Data-Ports, sondern kommuniziert ausschließlich über Adapter. Dies ermöglicht die Verwendung in Systemen mit standardisierten Verbindungen (z. B. über bestimmte Feldbus‑Adapterprofile).
- **Typtransparenz:** Da die Adapter generisch (`ANY`) sind, kann der FB mit verschiedenen Datentypen arbeiten – vorausgesetzt, sowohl der Eingangs- als auch der Ausgangsadapter verwenden denselben Datentyp.
- **Kein interner Zustandsautomat:** Der FB realisiert das Flipflop‑Verhalten durch die reine Daten‑/Ereignisverdrahtung des internen `E_D_FF_ANY`. Ein eigener Zustandsautomat ist nicht vorhanden.

## Zustandsübersicht

Der FB besitzt keinen expliziten Zustandsautomaten. Der interne Baustein `E_D_FF_ANY` hält intern den gespeicherten Wert (Zustand). Der FB ist jedoch aus Sicht der Ereignisverarbeitung zustandslos: Jedes Ereignis am Eingang löst sofort eine Ausgabe aus.

## Anwendungsszenarien

- **Puffern von Signalen:** Ein Datenwert soll bei einem bestimmten Ereignis „eingefroren“ und für nachfolgende Verarbeitungsschritte bereitgestellt werden.
- **Synchronisation asynchroner Daten:** Werte aus einem unsynchronisierten Kontext werden mittels eines Taktereignisses in den getakteten Bereich übernommen.
- **Standardisierte Datenkopplung:** In Architekturen, die auf Adapter‑Schnittstellen setzen (z. B. in der Landmaschinentechnik), kann der FB als universelle Latch‑Komponente eingesetzt werden.

## Vergleich mit ähnlichen Bausteinen

- **RS‑Flipflop (AD_RS_FF):** Speichert zwei Zustände (Set/Reset) und benötigt zwei Ereignis‑/Datenkanäle. Der AD_D_FF arbeitet mit nur einem Taktsignal und einem Datum – einfacher und deterministischer.
- **E_D_FF_ANY (direkt):** Bietet die gleiche Funktionalität, jedoch mit klassischen Event‑/Data‑Ports anstelle von Adaptern. Der AD_D_FF kapselt diese Logik in eine Adapter‑Schnittstelle, was die Wiederverwendung in adapterbasierten Umgebungen erleichtert.
- **Toggle‑FF (AD_T_FF)** oder **JK‑FF:** Komplexere Flipflops mit mehreren Eingängen; der AD_D_FF ist die einfachste Form eines datengesteuerten Speichers.

## Fazit

Der **AD_D_FF** ist ein schlanker, adapterbasierter D‑Flipflop‑Baustein für die 4diac‑IDE. Er übernimmt bei jedem Taktereignis einen Datenwert und gibt ihn aus. Durch die reinen Adapter‑Schnittstellen fügt er sich nahtlos in Architekturen ein, die auf standardisierte Verbindungen setzen. Seine einfache Funktionalität macht ihn zur idealen Wahl für Aufgaben der Datenpufferung und -synchronisation ohne zusätzliche Logik.