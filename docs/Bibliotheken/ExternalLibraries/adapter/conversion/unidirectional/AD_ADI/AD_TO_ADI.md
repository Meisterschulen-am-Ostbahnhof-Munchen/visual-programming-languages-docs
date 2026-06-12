# AD_TO_ADI


![AD_TO_ADI](./AD_TO_ADI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AD_TO_ADI** ist ein Composite-Baustein zur Umwandlung eines DWORD-Adapters (AD) in einen DINT-Adapters (ADI). Er ermöglicht die nahtlose Integration von Komponenten unterschiedlicher Datentypen in einer IEC 61499-Applikation, ohne dass der Anwender die Konvertierungslogik selbst implementieren muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine direkten Ereignis-Eingänge. Die Ereignissteuerung erfolgt über den Socket-Adapter `AD_IN`.

### **Ereignis-Ausgänge**

Keine direkten Ereignis-Ausgänge. Die Ereignisausgabe erfolgt über den Plug-Adapter `ADI_OUT`.

### **Daten-Eingänge**

Keine direkten Daten-Eingänge. Die Datenübergabe erfolgt über den Socket-Adapter `AD_IN`.

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge. Die Datenweitergabe erfolgt über den Plug-Adapter `ADI_OUT`.

### **Adapter**

| Bezeichnung | Typ | Richtung | Kommentar |
|-------------|-----|----------|-----------|
| `AD_IN` | `adapter::types::unidirectional::AD` | Socket (Eingang) | DWORD Adapter Input – liefert ein DWORD-Datum und ein Ereignis |
| `ADI_OUT` | `adapter::types::unidirectional::ADI` | Plug (Ausgang) | DINT Adapter Output – liefert ein konvertiertes DINT-Datum und ein Ereignis |

## Funktionsweise

Der Baustein kapselt einen Aufruf der IEC‑61131‑3‑Konvertierungsfunktion `F_DWORD_TO_DINT`. Der Ablauf ist:

1. Ein Ereignis am Socket `AD_IN.E1` triggert den Konvertierungs-FB `Convert` (Ereignis `REQ`).
2. Gleichzeitig wird das DWORD-Datum `AD_IN.D1` an den Eingang `Convert.IN` übergeben.
3. Der Konvertierungs-FB wandelt den Wert in einen DINT um und signalisiert die Fertigstellung über das Ereignis `CNF`.
4. Dieses Ereignis wird an den Plug `ADI_OUT.E1` weitergeleitet, und der konvertierte DINT-Wert (`Convert.OUT`) wird an `ADI_OUT.D1` gelegt.

Dadurch verhält sich der Composite-FB aus Sicht der Applikation wie ein direkter Adapter-Konverter ohne Nebenwirkungen.

## Technische Besonderheiten

- **IEC‑61131‑3‑Kompatibilität** – Die Konvertierung erfolgt via der standardisierten Bibliotheksfunktion `F_DWORD_TO_DINT`, die für gängige SPS‑Systeme verfügbar ist.
- **Unidirektionale Adapter** – Sowohl der Eingangs- als auch der Ausgangsadapter sind unidirektional ausgelegt; Rückmeldungen oder Gegenrichtungsdaten werden nicht unterstützt.
- **Keine Zustandsinformationen** – Der Composite selbst besitzt keine internen Zustandsvariablen; jede Konvertierung ist atomar und zeitlich unabhängig.
- **Autonomie** – Der Baustein kann ohne manuelle Einbindung weiterer FB in einer Netzwerkkonfiguration verwendet werden.

## Zustandsübersicht

Der Composite-FB besitzt keinen eigenen Zustandsautomaten. Das Verhalten ergibt sich rein aus der sequenziellen Abarbeitung der internen Verbindungen:

- **Warten auf Ereignis** – keine Aktivität, solange kein Ereignis an `AD_IN.E1` anliegt.
- **Konvertierung** – nach Ereigniseingang erfolgt die einmalige Umwandlung und Ausgabe des Ergebnisses.
- **Abschluss** – der FB ist sofort wieder bereit für das nächste Ereignis.

## Anwendungsszenarien

- **Gateway zwischen Systemen unterschiedlicher Datenbreite** – z. B. Anbindung eines DWORD‑Sensorwertes an eine DINT‑basierte Steuerungslogik.
- **Adapter‑Brücke in IEC 61499-Architekturen** – wenn Komponenten über die standardisierten unidirektionalen Adapter (AD/ADI) kommunizieren müssen.
- **Kapselung von Plausibilitätsprüfungen** – der DWORD-Wert kann vor der Konvertierung in einer vorgelagerten Logik validiert werden, bevor er in den DINT-Bereich überführt wird.

## Vergleich mit ähnlichen Bausteinen

- **AD_TO_ADI** ist spezialisiert auf die Konvertierung von DWORD nach DINT und folgt einem strengen unidirektionalen Adapter-Profil.
- Ähnliche Bausteine wie `AD_TO_AI` (DWORD nach INT) oder `ADI_TO_AD` (Rückkonvertierung) existieren für andere Datentypen, teilen aber das gleiche Entwurfsmuster.
- Im Gegensatz zu einem generischen Konvertierungs-FB (z. B. `F_DWORD_TO_DINT` allein) bietet der Composite die direkte Adapter‑Einbindung, sodass der Anwender keine manuellen Adapter‑Schnittstellen erstellen muss.

## Fazit

Der Composite-FB **AD_TO_ADI** stellt eine einfache, robuste und standardkonforme Lösung zur Umwandlung von DWORD- in DINT‑Adapterdaten bereit. Er reduziert den Konfigurationsaufwand innerhalb von IEC‑61499‑Netzwerken und erhöht die Wiederverwendbarkeit von Bausteinen aus unterschiedlichen Quellen. Dank der rein funktionalen Umsetzung ohne Zustandsprobleme eignet er sich besonders für zeitkritische und sicherheitsgerichtete Anwendungen.