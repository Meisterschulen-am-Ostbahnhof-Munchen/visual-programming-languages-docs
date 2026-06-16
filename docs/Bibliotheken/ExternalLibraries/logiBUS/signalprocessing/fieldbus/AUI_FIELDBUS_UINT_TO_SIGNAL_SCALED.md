# AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED


![AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED](./AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED dient der skalieren Übertragung eines eingehenden UINT-Wertes (Feldbus-Signal) auf einen analogen REAL-Ausgang. Er arbeitet nur dann, wenn das eingehende Signal als gültig markiert ist (VALID-Signal). Eine zusätzliche Initialisierungsschnittstelle erlaubt das Zurücksetzen der internen Logik. Der Baustein ist als Composite ausgeführt und kombiniert einen skalierenden Unterbaustein mit einem D-Flipflop zur Gültigkeitsspeicherung.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| INIT | EInit | Initialisierungsanforderung |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| INITO | EInit | Initialisierungsbestätigung |

### **Daten-Eingänge**

| Name | Typ | Initialwert | Kommentar |
|------|-----|-------------|-----------|
| SCALE | REAL | REAL#1.0 | Skalierungsfaktor |
| OFFSET | DINT | DINT#0 | Offset nach der Skalierung |

### **Daten-Ausgänge**
*(Keine direkten Datenausgänge – Ausgaben erfolgen über Adapter)*

### **Adapter**

| Typ | Name | Richtung | Kommentar |
|-----|------|----------|-----------|
| adapter::types::unidirectional::AUI | IN | Socket | UINT-Eingang (Feldbus-Signal) |
| adapter::types::unidirectional::AR | OUT | Plug | Skalierter REAL-Ausgang |
| adapter::types::unidirectional::AX | VALID | Plug | Gültigkeitssignal (TRUE = gültig) |

## Funktionsweise
Der Baustein besteht intern aus zwei Sub-FBs: dem skalierenden Kernbaustein `logiBUS::signalprocessing::fieldbus::FIELDBUS_UINT_TO_SIGNAL_SCALED` und einem D-Flipflop `E_D_FF`.

Die Initialisierung erfolgt über den Ereignis-Eingang INIT, der direkt an den internen Kernbaustein weitergeleitet wird. Die Bestätigung INITO wird nach erfolgreicher Initialisierung zurückgegeben.

Die eigentliche Signalverarbeitung wird durch ein eingehendes Ereignis (E1) des IN-Adapters ausgelöst. Dieses Ereignis triggert den Kernbaustein, der den über IN.D1 anliegenden UINT-Wert wie folgt verarbeitet:
- **Skalierung**: `Wert_skaliert = (REAL)IN_D1 * SCALE`
- **Offset**: `Wert_skaliert = Wert_skaliert + OFFSET`

Das Ergebnis (REAL) wird als OUT.D1 ausgegeben und gleichzeitig ein Ereignis OUT.E1 erzeugt. Parallel wird das vom Kernbaustein berechnete VALID-Signal (TRUE = gültig, FALSE = ungültig) an den D-Eingang des D-Flipflops gelegt. Das gleiche Ereignis CNF des Kernbausteins dient als Takt für das Flipflop. Dadurch wird der Gültigkeitszustand übernommen und am Q-Ausgang dauerhaft bis zum nächsten Takt gehalten. Der finale Gültigkeitswert wird über den VALID-Adapter (D1) und dessen Ereignis E1 ausgegeben.

Damit wird das VALID-Signal erst nach Abschluss der Skalierung aktualisiert und bleibt solange stabil, bis ein neuer Wert am Eingang eintrifft.

## Technische Besonderheiten
- **Composite-Architektur**: Der FB ist komplett aus Sub-FBs aufgebaut, was eine einfache Anpassung und Wiederverwendung ermöglicht.
- **Gültigkeitsspeicherung**: Ein D-Flipflop speichert das Gültigkeitssignal zwischen den Verarbeitungszyklen. So kann der Ausgang auch dann einen definierten Zustand anzeigen, wenn keine neuen Daten anliegen.
- **Skalierung und Offset**: Die Skalierung erfolgt mit einem REAL-Faktor und einem DINT-Offset. Dies erlaubt eine flexible Anpassung an physikalische Einheiten (z. B. Umrechnung von Digitalwerten in Druck oder Temperatur).
- **Adapterbasierte Ein-/Ausgabe**: Alle Signale werden über standardisierte 61499-Adapter (AUI, AR, AX) ausgetauscht, was die Integration in modulare Feldbussysteme erleichtert.

## Zustandsübersicht
Der Funktionsblock selbst besitzt keinen eigenen Zustandsautomaten. Der interne Zustand wird durch das D-Flipflop repräsentiert:
- **Zustand Q = FALSE**: Letzter verarbeiteter Wert war ungültig oder noch kein Wert eingetroffen.
- **Zustand Q = TRUE**: Der letzte verarbeitete Wert war gültig und liegt skaliert am OUT-Ausgang an.

Der Zustandswechsel erfolgt mit jedem neuen Ereignis auf dem IN-Adapter (E1), wenn der Kernbaustein ein neues VALID-Signal liefert.

## Anwendungsszenarien
- **Landwirtschaftliche Sensorik**: Übertragung skalierter Messwerte (z. B. Füllstand, Druck) von Feldbussensoren mit Gültigkeitsflag.
- **Datenvorverarbeitung**: Anpassung von Rohwerten aus Digitalwandlern (z. B. 0–10 V → REAL-Werte) mit automatischer Gültigkeitsprüfung.
- **Qualitätssicherung**: Nur Werte, die als gültig markiert sind, werden an nachfolgende Steuerlogiken weitergegeben.

## Vergleich mit ähnlichen Bausteinen
- **AUI_FIELDBUS_UINT_TO_SIGNAL** (ohne Gültigkeitsflag): Gibt immer einen skalierten Wert aus, unabhängig von der Signalqualität.
- **AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED** (Core): Liefert bereits eine skalierte Ausgabe mit Gültigkeitsflag, jedoch ohne Speicherung. Der vorliegende Composite ergänzt diese Speicherung und erlaubt eine stabilere Ausgabe zwischen den Ereignissen.
- **Adapterbasierte Filter**: Andere Bausteine nutzen ähnliche Prinzipien, aber mit spezifischen Gültigkeitsbedingungen (z. B. Zeitfilter).

## Fazit
Der AUI_FIELDBUS_UINT_TO_SIGNAL_SCALED bietet eine zuverlässige und flexible Lösung zur skalierten Übertragung von UINT-Feldbussignalen mit expliziter Gültigkeitskennzeichnung. Die Kombination aus Skalierung, Offset und gespeichertem Gültigkeitssignal macht ihn besonders geeignet für sicherheitskritische oder qualitätsüberwachte Anwendungen in der Automatisierungstechnik.