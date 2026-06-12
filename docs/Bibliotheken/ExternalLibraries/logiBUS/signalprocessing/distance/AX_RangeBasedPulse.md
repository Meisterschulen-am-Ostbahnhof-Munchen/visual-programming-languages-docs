# AX_RangeBasedPulse


![AX_RangeBasedPulse](./AX_RangeBasedPulse.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock generiert einen Puls auf einem AX-Adapter basierend auf einer zurückgelegten Distanz (Adapter-Version). Er ist unter der Eclipse Public License 2.0 lizenziert und für den Einsatz in der Signalverarbeitung von Distanzdaten konzipiert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- `DIST_IN.E1`: Ereignis vom Distanz-Adapter, das die Aktualisierung des Distanzwerts signalisiert.

### **Ereignis-Ausgänge**

- `OUT.E1`: Ereignis auf dem Ausgangs-Adapter, das bei einer Zustandsänderung des Pulsausgangs gesendet wird.

### **Daten-Eingänge**

- `DIST_HIGH` (UDINT): Distanz in mm, die zurückgelegt werden muss, um den HIGH-Puls zu erzeugen (Initialwert: 5000).
- `DIST_LOW` (UDINT): Distanz in mm, die zurückgelegt werden muss, um den LOW-Puls zu erzeugen (Initialwert: 5000).
- `DIST_IN.D1` (UDINT): Aktuelle Distanz vom Eingangs-Adapter (über das Ereignis aktualisiert).

### **Daten-Ausgänge**

- `OUT.D1` (BOOL): Pulsausgang – wechselt zwischen TRUE (HIGH) und FALSE (LOW) abhängig von der akkumulierten Distanz.

### **Adapter**

- **DIST_IN (Socket):** Adapter vom Typ `adapter::types::unidirectional::AUDI`. Stellt einen unidirektionalen Distanzwert (`D1`) sowie ein zugehöriges Ereignis (`E1`) bereit.
- **OUT (Plug):** Adapter vom Typ `adapter::types::unidirectional::AX`. Stellt einen unidirektionalen Bool-Wert (`D1`) und ein Ereignis (`E1`) zur Verfügung.

## Funktionsweise

Der Funktionsblock arbeitet nach einem Hystereseprinzip mit zwei Schwellwerten:

1. **Initialisierung:** Beim ersten Durchlauf (`FirstRun = TRUE`) wird die aktuelle Distanz als Startwert `LastDist` gespeichert, der Ausgang `OUT.D1` auf FALSE gesetzt und `FirstRun` zurückgesetzt.
2. **Zustandsprüfung:** Bei jedem eingehenden Ereignis über `DIST_IN.E1` führt der Block den `CHECK`-Algorithmus aus:
   - Wenn der aktuelle Ausgang LOW (FALSE) ist und die neue Distanz `DIST_IN.D1` den Wert `LastDist + DIST_LOW` erreicht oder überschreitet, wird `OUT.D1` auf TRUE gesetzt und `LastDist` auf den aktuellen Distanzwert aktualisiert.
   - Wenn der Ausgang HIGH (TRUE) ist und die neue Distanz den Wert `LastDist + DIST_HIGH` erreicht oder überschreitet, wird `OUT.D1` auf FALSE gesetzt und `LastDist` aktualisiert.
3. **Ausgabe:** Bei einer Zustandsänderung von `OUT.D1` wird das Ereignis `OUT.E1` gesendet und der neue Zustand in `LastState` für die nächste Prüfung gespeichert.

## Technische Besonderheiten

- **Adapter-basierte Kommunikation:** Die Verwendung von Plugs und Sockets (`AX`, `AUDI`) ermöglicht eine modulare und flexible Verschaltung in der 4diac-IDE.
- **Asymmetrische Pulsbreiten:** Die getrennten Parameter `DIST_HIGH` und `DIST_LOW` erlauben unterschiedliche Distanzen für HIGH- und LOW-Phasen.
- **Initialisierungslogik:** Ein interner `FirstRun`-Flag sorgt dafür, dass die erste Messung korrekt als Startpunkt gesetzt wird.
- **Paketkontext:** Der FB ist für das Paket `logiBUS::signalprocessing::distance` vorgesehen.

## Zustandsübersicht

Das ECC (Execution Control Chart) besteht aus vier Zuständen:

- **START:** Wartezustand nach Initialisierung oder nach einer Verarbeitung.
- **INIT:** Führt den `INIT`-Algorithmus aus (Setzen der Startwerte). Wird nur beim ersten Durchlauf (`FirstRun = TRUE`) betreten.
- **CHECK:** Führt den `CHECK`-Algorithmus zur Distanzprüfung aus und ändert ggf. den Ausgang.
- **EMIT:** Führt den `SAVE`-Algorithmus aus (speichert den aktuellen Ausgangszustand) und sendet das Ereignis `OUT.E1`.

**Übergänge:**
- `START → INIT`: Wenn `DIST_IN.E1` eintrifft und `FirstRun = TRUE`.
- `START → CHECK`: Wenn `DIST_IN.E1` eintrifft und `FirstRun = FALSE`.
- `INIT → CHECK`: Sofort nach `INIT` (Bedingung 1).
- `CHECK → EMIT`: Wenn sich `OUT.D1` gegenüber `LastState` geändert hat.
- `CHECK → START`: Wenn keine Änderung eintritt (`OUT.D1 = LastState`).
- `EMIT → START`: Sofort nach `EMIT` (Bedingung 1).

## Anwendungsszenarien

- **Wegimpulsgeber in der Landtechnik:** Erzeugen von Impulsen nach jeder definierten Wegstrecke (z. B. alle 5 m ein HIGH-Impuls, dann nach weiteren 5 m ein LOW-Impuls) für Steuerungs- oder Zählaufgaben.
- **Distanzbasierte Schaltfunktionen:** Auslösen von Aktionen in Fördersystemen, fahrerlosen Transportsystemen oder automatischen Maschinen nach bestimmten zurückgelegten Strecken.
- **Pulsweitenmodulation über Strecke:** Durch unterschiedliche Werte für `DIST_HIGH` und `DIST_LOW` lassen sich variable Pulsbreiten realisieren, z. B. 10 m HIGH und 2 m LOW.

## Vergleich mit ähnlichen Bausteinen

- **Tonbasierte Pulsgeneratoren (z. B. `E_CYCLE`):** Erzeugen Pulse zeitabhängig, während `AX_RangeBasedPulse` wegabhängig arbeitet – für Anwendungen ohne feste Zeitbasis.
- **Einfache Flankendetektoren:** Erkennen Signalwechsel, jedoch ohne Hysterese und ohne Akkumulation einer Distanz.
- **Andere Distanz-Adapter-Bausteine:** Es existieren Bausteine, die Distanzwerte aggregieren, aber dieser FB kombiniert Ereignisverarbeitung mit Schwellwertlogik und asymmetrischer Konfiguration.

## Fazit

Der `AX_RangeBasedPulse`-Funktionsblock bietet eine robuste und flexible Lösung zur distanzbasierten Pulsgenerierung. Durch die Adapter-Schnittstelle, die getrennt konfigurierbaren Distanzschwellen und die Hystereselogik eignet er sich hervorragend für den modularen Einsatz in industriellen Steuerungssystemen, insbesondere in der Landtechnik und Automatisierung. Die Implementierung als BasicFB gewährleistet dabei ein deterministisches und nachvollziehbares Verhalten.