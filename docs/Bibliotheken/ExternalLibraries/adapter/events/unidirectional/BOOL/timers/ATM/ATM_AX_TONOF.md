# ATM_AX_TONOF


![ATM_AX_TONOF](./ATM_AX_TONOF.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ATM_AX_TONOF** realisiert einen kombinierten Ein-/Ausschaltverzögerungs-Timer. Er ist als Standard-Timerbaustein nach IEC 61499 ausgelegt und nutzt ausschließlich Adapter-Schnittstellen zur Kommunikation. Dadurch kann er flexibel in unterschiedliche Kommunikationsstrukturen eingebunden werden. Der Baustein verarbeitet ein boolesches Eingangssignal und gibt das verzögerte Signal aus – sowohl die Einschaltverzögerung (ON-Delay) als auch die Ausschaltverzögerung (OFF-Delay) werden über eigene Adapter konfiguriert.

## Schnittstellenstruktur

### Ereignis-Eingänge

| Name | Typ    | Beschreibung                                                 |
|------|--------|--------------------------------------------------------------|
| R    | Event  | Setzt den Timer zurück. Beide laufenden Verzögerungen werden abgebrochen und der Ausgang Q wird sofort auf FALSE gesetzt. |

### Ereignis-Ausgänge

Der Funktionsblock besitzt keine eigenständigen Ereignis-Ausgänge. Das Ausgangsereignis wird über den Ausgangsadapter **Q** bereitgestellt (siehe Adapter).

### Daten-Eingänge

Der FB verfügt über keine direkten Dateneingänge. Alle notwendigen Daten (boolescher Eingang und Verzögerungszeiten) werden über die Adapter-Schnittstellen eingelesen.

### Daten-Ausgänge

Auch für Datenausgänge existieren keine eigenen Anschlüsse. Der aktuelle Ausgangszustand (BOOL) wird über den Ausgangsadapter **Q** ausgegeben.

### Adapter

| Name   | Richtung | Typ              | Beschreibung                                                                                         |
|--------|----------|------------------|------------------------------------------------------------------------------------------------------|
| IN     | Socket   | AX (unidirektional) | Eingangsadapter, der über sein Ereignis E1 die Ausführung anstößt und über sein Datum D1 den booleschen Eingangswert liefert. |
| PT_ON  | Socket   | ATM (unidirektional) | Adapter für die Einschaltverzögerungszeit (TIME). Der Wert wird über D1 bereitgestellt.          |
| PT_OFF | Socket   | ATM (unidirektional) | Adapter für die Ausschaltverzögerungszeit (TIME). Der Wert wird über D1 bereitgestellt.          |
| Q      | Plug     | AX (unidirektional) | Ausgangsadapter. Das Ereignis E1 signalisiert die Aktualisierung des Ausgangswertes, das Datum D1 enthält den booleschen Zustand von Q (TRUE oder FALSE). |

## Funktionsweise

Der FB arbeitet nach folgendem Ablauf:

- Wenn das Eingangssignal **IN** von FALSE auf TRUE wechselt, startet der Timer die Einschaltverzögerung mit der Zeit **PT_ON**. Nach Ablauf dieser Zeit wird der Ausgang **Q** auf TRUE gesetzt.
- Wenn **IN** von TRUE auf FALSE wechselt, startet der Timer die Ausschaltverzögerung mit der Zeit **PT_OFF**. Nach Ablauf dieser Zeit wird **Q** auf FALSE gesetzt.
- Ein Ereignis am Reset-Eingang **R** stoppt beide laufenden Timer sofort und setzt **Q** auf FALSE, unabhängig vom aktuellen Zustand von **IN**.

Die interne Implementierung nutzt den standardisierten Baustein **E_TONOF** der IEC 61499-Bibliothek. Dies gewährleistet ein definiertes, robustes Zeitverhalten.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle**: Alle Ein- und Ausgaben erfolgen über Adapter (AX, ATM) anstatt über diskrete Ereignis- und Datenports. Dies erleichtert die Integration in modulare Systeme und erlaubt eine saubere Trennung von Kommunikation und Logik.
- **Standardkonformität**: Der FB ist als Standard-Timer nach IEC 61499 klassifiziert und kann in beliebigen 4diac-IDE Projekten verwendet werden.
- **Reset-Funktion**: Der separate Reset-Eingang ermöglicht ein sofortiges Zurücksetzen ohne Abhängigkeit vom aktuellen Timer-Zustand.
- **Wiederverwendbare Adaptertypen**: Die Adapter AX und ATM werden in der Anwendung mehrfach verwendet, sodass keine zusätzlichen Typdefinitionen erforderlich sind.

## Zustandsübersicht

Der interne Timer **E_TONOF** durchläuft folgende Zustände:

1. **IDLE**: Keine Verzögerung aktiv. Ausgang Q = Zustand von IN (sofern nach vorheriger Verzögerung aktualisiert).
2. **START_ON**: Nach positiver Flanke von IN – Timer für PT_ON läuft.
3. **START_OFF**: Nach negativer Flanke von IN – Timer für PT_OFF läuft.
4. **RESET**: Wird durch das Ereignis R ausgelöst, unterbricht jeden aktiven Timer und kehrt in den IDLE-Zustand mit Q = FALSE zurück.

## Anwendungsszenarien

- **Verzögerte Ein- und Ausschaltung von Aktoren**: Beispielsweise zur Vermeidung von Prellern oder zur zeitlichen Staffelung von Schaltvorgängen.
- **Motorschutz**: Einschaltverzögerung verhindert häufiges Ein-/Ausschalten, Ausschaltverzögerung ermöglicht definierten Nachlauf.
- **Türsteuerung**: ON-Delay für zeitverzögertes Schließen nach Freigabe, OFF-Delay für automatisches Öffnen nach Ablauf einer Wartezeit.
- **HMI-Filterung**: Unterdrückung kurzer, unerwünschter Signalwechsel durch einstellbare Totzeiten.

## Vergleich mit ähnlichen Bausteinen

- **E_TON (TON)**: Realisiert nur eine Einschaltverzögerung; der Ausgang wird nach Ablauf der Verzögerung auf TRUE gesetzt und bleibt TRUE, solange IN=TRUE ist.
- **E_TOF (TOF)**: Realisiert nur eine Ausschaltverzögerung; der Ausgang wird sofort bei IN=TRUE auf TRUE gesetzt und fällt nach Ablauf der Verzögerung nach IN=FALSE wieder auf FALSE.
- **E_TONOF**: Kombiniert beide Verzögerungen in einem Baustein. Der **ATM_AX_TONOF** erweitert dieses Konzept um eine Adapter-Schnittstelle, sodass die Anbindung an andere Adapter-basierte Komponenten erleichtert wird. Er bietet denselben Funktionsumfang, jedoch mit erhöhter Flexibilität in der Systemintegration.

## Fazit

Der **ATM_AX_TONOF** ist ein leistungsfähiger Timer-Funktionsblock für verzögerte Ein-/Ausschaltvorgänge. Durch seine Adapter-basierte Schnittstelle passt er sich nahtlos in modulare Automatisierungslösungen ein und bleibt dennoch vollständig kompatibel zum IEC 61499-Standard. Die Kombination von ON-Delay und OFF-Delay in einem Baustein reduziert den Verdrahtungsaufwand und vereinfacht die Applikationserstellung. Dank des separaten Reset-Eingangs und der stabilen internen Implementierung eignet er sich für vielfältige industrielle Anwendungen.