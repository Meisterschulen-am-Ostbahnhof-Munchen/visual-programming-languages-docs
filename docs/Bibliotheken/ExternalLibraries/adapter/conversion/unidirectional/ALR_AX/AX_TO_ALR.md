# AX_TO_ALR


![AX_TO_ALR](./AX_TO_ALR.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AX_TO_ALR** dient zur Umwandlung eines BOOL‑Adapter-Signals (AX) in ein LREAL‑Adapter-Signal (ALR). Er setzt intern die IEC‑61131‑Standardfunktion `F_SEL` (Selection) ein, um aus einem booleschen Eingang einen diskreten LREAL‑Wert zu generieren. Der Baustein ist als Composite FB realisiert und eignet sich für die einfache, adapterbasierte Konvertierung von digitalen Zuständen in numerische Werte.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `AX_IN.E1` | EVENT | Ereignis vom angeschlossenen AX‑Adapter; löst die Verarbeitung aus. |

### **Ereignis-Ausgänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `ALR_OUT.E1` | EVENT | Bestätigungsereignis, nachdem der konvertierte Wert am ALR‑Adapter ausgegeben wurde. |

### **Daten-Eingänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `AX_IN.D1` | BOOL | Boolescher Wert, der in einen LREAL‑Wert umgesetzt werden soll. |

### **Daten-Ausgänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `ALR_OUT.D1` | LREAL | Ergebnis der Konvertierung: 0.0 bei `FALSE`, 1.0 bei `TRUE`. |

### **Adapter**

| Richtung | Bezeichnung | Typ | Beschreibung |
|----------|-------------|-----|--------------|
| Socket (Eingang) | `AX_IN` | `adapter::types::unidirectional::AX` | Nimmt ein BOOL‑Signal über den unidirektionalen AX‑Adapter entgegen. |
| Plug (Ausgang) | `ALR_OUT` | `adapter::types::unidirectional::ALR` | Stellt das konvertierte LREAL‑Signal über den unidirektionalen ALR‑Adapter bereit. |

## Funktionsweise

Der FB arbeitet nach folgendem Schema:

1. Ein eingehendes Ereignis an `AX_IN.E1` triggert die interne Verarbeitung.
2. Der boolesche Wert von `AX_IN.D1` wird an den Gate‑Eingang (G) der eingebetteten `F_SEL`‑Funktion übergeben.
3. `F_SEL` wählt – je nach booleschem Wert – einen der beiden Konstantenwerte aus:
   - `FALSE` (G = 0) → Ausgabe von **0.0** (LREAL#0.0)
   - `TRUE` (G = 1) → Ausgabe von **1.0** (LREAL#1.0)
4. Das Ergebnis wird an `ALR_OUT.D1` weitergeleitet und gleichzeitig das Bestätigungsereignis `ALR_OUT.E1` ausgegeben.

Die Konvertierung erfolgt ereignisgesteuert: Jedes ankommende Ereignis bewirkt genau eine Umwandlung des aktuellen BOOL‑Werts.

## Technische Besonderheiten

- **Adapter‑Schnittstelle**: Der FB verwendet ausschließlich unidirektionale Adapter (Socket/Plug), wodurch er sich nahtlos in adapterbasierte Architekturen einfügt.
- **Interner Einsatz von F_SEL**: Die IEC‑61131‑Standardfunktion garantiert ein deterministisches und portables Verhalten.
- **Feste Schwellwerte**: Die Ausgangswerte sind auf `0.0` und `1.0` festgelegt. Eine Anpassung erfordert eine Modifikation des inneren Netzwerks.
- **Paketierung**: Der FB ist im Paket `adapter::conversion::unidirectional` abgelegt.
- **Lizenz**: Der Baustein ist unter der Eclipse Public License 2.0 verfügbar.

## Zustandsübersicht

Da es sich um einen Composite FB ohne eigenen Ablaufzustand handelt, ergibt sich die Zustandslogik aus der Ereignis‑ und Datenverarbeitung des enthaltenen `F_SEL`‑Bausteins. Es existieren zwei stabile Zustände:

- **Warten auf Ereignis**: Kein Ereignis an `AX_IN.E1` – keine Ausgabe.
- **Verarbeitung aktiv**: Ein Ereignis wird verarbeitet: der boolesche Wert wird gelesen, in einen LREAL‑Wert umgewandelt und am Ausgang bereitgestellt; anschließend wird das Bestätigungsereignis gesendet.

## Anwendungsszenarien

- **Digital‑Analog‑Umsetzung**: Ein digitaler Sensor (z. B. Schalter, Grenztaster) liefert einen BOOL‑Wert, der in der Steuerung als LREAL‑Signal (0.0/1.0) weiterverarbeitet werden soll.
- **Adapter‑Integration**: Einbinden in bestehende Systeme, die bereits unidirektionale AX‑ und ALR‑Adapter verwenden – z. B. in der Landtechnik oder der industriellen Automatisierung.
- **Skalierung von Zuständen**: Vereinfachte Umwandlung von Ein‑/Aus‑Signalen in numerische Größen für Berechnungen oder Visualisierungen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eingangstyp | Ausgangstyp | Besonderheit |
|----------|-------------|-------------|--------------|
| `AX_TO_ALR` | BOOL (Adapter) | LREAL (Adapter) | Adapter‑basiert, feste Werte 0.0 / 1.0 |
| `BOOL_TO_REAL` | BOOL (direkt) | REAL (direkt) | Konventioneller IEC‑Baustein, Werte frei konfigurierbar |
| `SEL` / `F_SEL` | BOOL + 2x ANY | ANY | Allgemeine Auswahl ohne Adapter, Werte parameterisierbar |

Gegenüber direkten Funktionsbausteinen bietet `AX_TO_ALR` den Vorteil der sauberen Adapter‑Kapselung und der einfachen Wiederverwendung in adapterorientierten Projekten.

## Fazit

Der FB `AX_TO_ALR` stellt eine kompakte und zuverlässige Lösung zur Umwandlung eines booleschen Adaptersignals in einen LREAL‑Adapterwert dar. Durch den Einsatz der IEC‑Normfunktion `F_SEL` ist das Verhalten deterministisch und portabel. Er eignet sich besonders für Anwendungen, die eine saubere Trennung von digitalen und analogen Signalpfaden über Adapter erfordern.