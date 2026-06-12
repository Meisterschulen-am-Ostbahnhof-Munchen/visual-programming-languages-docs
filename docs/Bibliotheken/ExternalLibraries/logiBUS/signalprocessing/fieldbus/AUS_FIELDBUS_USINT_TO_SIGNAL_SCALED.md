# AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED


![AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED](./AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED spiegelt einen eingehenden Feldbussignalwert (USINT) auf den Ausgang, sofern das Signal als gültig erkannt wird. Dabei wird der Eingangswert mit einem konfigurierbaren Skalierungsfaktor multipliziert und ein Offset addiert. Der FB ist als Composite-Baustein realisiert und besteht aus einem Sub-FB für die Skalierung sowie einem flankengesteuerten D-Flipflop zur Synchronisation des Gültigkeitssignals. Er wird typischerweise in der Feldbus-Signalverarbeitung eingesetzt, um rohe USINT-Werte in physikalische Größen umzurechnen und die Datenvalidität weiterzuleiten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **INIT** (EInit): Initialisierungsanforderung. Wird durchgereicht an das interne Sub-FB.

### **Ereignis-Ausgänge**
- **INITO** (EInit): Initialisierungsbestätigung. Wird vom internen Sub-FB übernommen.

### **Daten-Eingänge**
- **SCALE** (REAL): Skalierungsfaktor, der auf den Eingangswert multipliziert wird. Standardwert: 1.0.
- **OFFSET** (DINT): Offsetwert, der nach der Multiplikation zum skalierten Wert addiert wird. Standardwert: 0.

### **Daten-Ausgänge**
Keine direkten Datenausgänge – die Ausgabe erfolgt ausschließlich über die Adapter.

### **Adapter**
- **IN** (Socket, Typ `adapter::types::unidirectional::AUS`): Eingangsadapter für das Rohsignal. Liefert die USINT-Daten über `D1` und ein Ereignis über `E1`.
- **OUT** (Plug, Typ `adapter::types::unidirectional::AR`): Ausgangsadapter für das skalierte Signal. Stellt den skalierten Wert über `D1` und ein Ereignis über `E1` bereit.
- **VALID** (Plug, Typ `adapter::types::unidirectional::AX`): Ausgangsadapter für das Gültigkeitssignal. Gibt einen booleschen Wert (TRUE = gültig) über `D1` und ein Ereignis über `E1` aus.

## Funktionsweise
1. **Initialisierung**: Das Ereignis `INIT` wird direkt an das interne Sub-FB `FIELDBUS_USINT_TO_SIGNAL_SCALED` weitergeleitet. Dessen `INITO` wird an den äußeren `INITO`-Ausgang durchgereicht.
2. **Datenverarbeitung**: Sobald ein Ereignis am `IN.E1` eintrifft, triggert es die Ausführung des internen Sub-FBs über dessen `REQ`-Eingang. Das Sub-FB verarbeitet den aktuellen Wert von `IN.D1` (USINT) unter Anwendung von `SCALE` und `OFFSET` und berechnet einen skalierten Ausgabewert (REAL) sowie ein Gültigkeitsflag (BOOL).
3. **Ergebnisausgabe**: Nach der Berechnung erzeugt das Sub-FB ein `CNF`-Ereignis. Dieses triggert:
   - Die Ausgabe des skalierten Werts über `OUT.D1` und das Ereignis `OUT.E1`.
   - Den Takteingang (`CLK`) des D-Flipflops `E_D_FF`.
4. **Gültigkeitssignal**: Das Gültigkeitsflag des Sub-FBs wird auf den Dateneingang (`D`) des Flipflops gelegt. Mit jedem Taktereignis übernimmt das Flipflop den aktuellen `D`-Wert auf seinen Ausgang `Q`. Das Ereignis `E_D_FF.EO` triggert anschließend die Ausgabe des Gültigkeitssignals über `VALID.D1` und `VALID.E1`.
5. **Zusammenspiel**: Dadurch wird sichergestellt, dass das Gültigkeitssignal erst nach Abschluss der Skalierung und streng getaktet mit dem ausgegebenen skalierten Wert aktualisiert wird.

## Technische Besonderheiten
- **Composite-Struktur**: Der FB besteht aus einem spezialisierten Sub-FB (`FIELDBUS_USINT_TO_SIGNAL_SCALED`) zur Skalierung und einem standardisierten D-Flipflop (`E_D_FF`) aus der IEC 61499-Ereignisbibliothek.
- **Verborgene Verbindungen**: Einige interne Verbindungen (z. B. für `INIT`, `SCALE`, `OFFSET`) sind als unsichtbar (`Visible="false"`) markiert, um die Übersichtlichkeit in der grafischen Darstellung zu erhöhen.
- **Datentypen**: Der Eingangswert ist als USINT (0…255) angenommen, der Ausgang wird durch die Skalierung zu REAL. Der Offset ist als DINT deklariert.
- **Flankengesteuerte Synchronisation**: Das D-Flipflop sorgt für eine entprellte Weitergabe des Gültigkeitssignals, sodass es nur bei einem neuen Verarbeitungszyklus aktualisiert wird.

## Zustandsübersicht
Der FB besitzt keine eigenen expliziten Zustände. Die Zustandslogik ergibt sich aus den Sub-Komponenten:
- **Sub-FB `FIELDBUS_USINT_TO_SIGNAL_SCALED`**: Führt eine ablauforientierte Berechnung ohne Zustandsspeicher durch; es reagiert auf jedes `REQ`-Ereignis mit einem `CNF`.
- **D-Flipflop `E_D_FF`**: Besitzt zwei Zustände (Q = 0 oder 1). Bei jedem positiven Takt (CLK) wird Q = D gesetzt. Der Zustand bleibt bis zum nächsten Takt erhalten.

## Anwendungsszenarien
- **Feldbus-Sensorauswertung**: Ein Sensor liefert über Feldbus einen USINT-Wert (z. B. 0–100 % Füllstand oder 0–255 Druckwerte). Der FB skaliert diesen Wert in eine physikalische Größe (z. B. Meter, bar) und gibt ihn zusammen mit einem Gültigkeitsflag aus.
- **Signalaufbereitung in der Agrartechnik**: In landwirtschaftlichen Maschinen werden oft skalierte Signale benötigt, bei denen die Gültigkeit der Daten (z. B. nach einer Kommunikationsstörung) explizit ausgewiesen werden muss.
- **Initialisierungskaskaden**: Der durchgereichte `INIT`-Ausgang ermöglicht die Initialisierung nachgeschalteter Bausteine, die ebenfalls auf dieses Signal angewiesen sind.

## Vergleich mit ähnlichen Bausteinen
- **`AUS_FIELDBUS_USINT_TO_SIGNAL`** (ohne Skalierung): Bietet lediglich eine direkte Durchleitung des USINT-Werts ohne Skalierung und Offset.
- **`AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED` mit separatem Valid-Toggle**: Ein alternativer Aufbau könnte das Gültigkeitssignal asynchron (ohne Flipflop) weiterleiten, was aber zu möglichen Zittereffekten führen kann.
- **`AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED` mit integrierter Zustandsmaschine**: Statt eines Flipflops könnte eine eigene Zustandslogik das Gültigkeitssignal verwalten; der vorliegende Baustein nutzt jedoch bewährte Standardkomponenten.

## Fazit
Der Funktionsblock `AUS_FIELDBUS_USINT_TO_SIGNAL_SCALED` bietet eine robuste und wartbare Lösung zur Skalierung von USINT-Feldbussignalen und zur zuverlässigen Weiterleitung des Gültigkeitsstatus. Durch die Composite-Struktur und die Verwendung eines D-Flipflops wird eine saubere zeitliche Trennung zwischen Datenberechnung und Ausgabe erreicht. Er ist besonders in Systemen mit Zyklus-basierter Datenverarbeitung und expliziter Signalgültigkeit nützlich.