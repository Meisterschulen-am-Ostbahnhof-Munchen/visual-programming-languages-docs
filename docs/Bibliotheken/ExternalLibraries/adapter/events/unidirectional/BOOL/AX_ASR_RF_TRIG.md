# AX_ASR_RF_TRIG


![AX_ASR_RF_TRIG](./AX_ASR_RF_TRIG.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_ASR_RF_TRIG** dient der bidirektionalen Flankenerkennung (steigende und fallende) eines booleschen Eingangssignals. Er ist als Adapter-basierte Hüllkurve des IEC‑61499‑Standardbausteins `E_RF_TRIG` konzipiert. Über zwei unidirektionale Adapter wird das zu überwachende Signal eingelesen und das Ergebnis als Setz‑/Rücksetz‑Ausgang bereitgestellt.

## Schnittstellenstruktur

Der FB besitzt **keine direkten** Ereignis- oder Datenein-/ausgänge. Die gesamte Kommunikation erfolgt über zwei Adapter.

### Ereignis-Eingänge

- **keine**

### Ereignis-Ausgänge

- **keine**

### Daten-Eingänge

- **keine**

### Daten-Ausgänge

- **keine**

### Adapter

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| **QI**  | `adapter::types::unidirectional::AX` | Socket | Eingangsadapter – liefert den zu überwachenden Booleschen Wert (über Kanal `D1`) sowie ein Ereignis (`E1`) zur Verarbeitung. |
| **Q**   | `adapter::types::unidirectional::ASR` | Plug   | Ausgangsadapter – signalisiert über die Ereignisse `SET` (steigende Flanke) und `RESET` (fallende Flanke) den erkannten Flankenzustand. |

## Funktionsweise

1. Ein am Socket **QI** eingehendes Ereignis (über `QI.E1`) überträgt zeitgleich den booleschen Wert `QI.D1` an den internen `E_RF_TRIG`-Baustein.
2. Der integrierte `E_RF_TRIG` erkennt eine **steigende Flanke** (Übergang von FALSE auf TRUE) und eine **fallende Flanke** (Übergang von TRUE auf FALSE).
3. Bei einer steigenden Flanke erzeugt der interne FB das Ereignis `ER`, welches über den Plug **Q** als `Q.SET` ausgegeben wird.
4. Bei einer fallenden Flanke erzeugt der interne FB das Ereignis `EF`, welches als `Q.RESET` ausgegeben wird.

Somit wird das Eingangssignal in ein Setz‑/Rücksetz‑Signal umgesetzt, ohne dass der Anwender sich mit der internen Ereignisverarbeitung befassen muss.

## Technische Besonderheiten

- **Reine Adapter‑Schnittstelle:** Der FB besitzt keine direkten Eingänge/Ausgänge im FB‑Typ‑Interface, was eine lose Kopplung und Wiederverwendbarkeit in verschiedenen Adapternetzwerken ermöglicht.
- **Nutzung des Standardbausteins `E_RF_TRIG`:** Die Flankenerkennung basiert auf der bewährten IEC‑61499‑Implementierung, die sowohl steigende als auch fallende Flanken zuverlässig detektiert.
- **Keine Zustandsspeicherung außerhalb des internen FB:** Die gesamte Logik wird durch den eingebetteten `E_RF_TRIG` realisiert; der äußere Baustein dient ausschließlich als Kapselung und Adapteranpassung.

## Zustandsübersicht

Der FB besitzt **keine eigene explizite Zustandsmaschine**. Der interne `E_RF_TRIG` arbeitet nach folgender impliziter Zustandslogik:

| letzter Wert | aktueller Wert | ausgelöstes Ereignis |
|--------------|----------------|----------------------|
| FALSE        | TRUE           | steigende Flanke (SET) |
| TRUE         | FALSE          | fallende Flanke (RESET) |
| sonst        | –              | kein Ereignis        |

Die Zustandsspeicherung erfolgt ausschließlich innerhalb des internen FB.

## Anwendungsszenarien

- **Tastendruck‑Erkennung:** Überwachung eines Tastersignals; `SET` beim Drücken, `RESET` beim Loslassen.
- **Signalflanken‑Auswertung in Steuerungen:** Detektion von Grenzwertüberschreitungen oder Impulsanfängen/-enden.
- **Adapterbasierte Sensor‑Integration:** Einbinden von Sensoren mit booleschem Ausgang in ein Adapter‑Netzwerk, z. B. über die AX/ASR‑Adapterfamilie.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Flankenerkennung | Ausgangssignal | Schnittstelle |
|----------|------------------|----------------|---------------|
| `E_RF_TRIG` | steigend + fallend | separate Ereignisausgänge | direkte Events |
| `E_TRIG` | nur steigend | ein Ereignis | direkte Events |
| `E_F_TRIG` | nur fallend | ein Ereignis | direkte Events |
| **AX_ASR_RF_TRIG** | steigend + fallend | Setz‑/Rücksetz‑Ereignisse über Adapter | reine Adapter |

Der vorliegende FB bietet im Gegensatz zu den reinen Event‑Bausteinen eine Adapter‑Schnittstelle, die eine einfachere Verbindung in hierarchischen oder typisierten Adapternetzen ermöglicht.

## Fazit

Der `AX_ASR_RF_TRIG` ist ein kompakter, auf Adapterbasis gekapselter Flankendetektor für boolesche Signale. Er vereinfacht die Verwendung des Standardbausteins `E_RF_TRIG` in adapterbasierten Architekturen und setzt die erkannten Flanken direkt in ein Setz‑/Rücksetz‑Signal um. Durch die lose Kopplung eignet er sich besonders für modulare, wiederverwendbare Steuerungsanwendungen.