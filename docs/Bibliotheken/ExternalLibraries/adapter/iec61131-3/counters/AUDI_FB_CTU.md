# AUDI_FB_CTU


![AUDI_FB_CTU](./AUDI_FB_CTU.svg)

* * * * * * * * * *
## Einleitung
Der **AUDI_FB_CTU** ist ein Aufwärtszähler (Up Counter) für den Datentyp **UDINT** (32‑Bit vorzeichenlos), der über standardisierte **AUDI‑Adapter** angebunden wird. Der Baustein kapselt die IEC 61131‑Zählfunktion in einer adapterbasierten Architektur und erlaubt das Triggern von Zählimpulsen, Reset‑ und Preset‑Operationen über Adapter‑Events. Jeder zählrelevante Vorgang (Zählimpuls, Reset, Setzen des Presetwerts) löst zwingend einen Ausgangs‑Event aus – unabhängig davon, ob sich der Zählerstand oder der Ausgangswert ändert. Soll eine reine Änderungsauslösung (on‑change) realisiert werden, muss ein nachgeschalteter AX_D_FF‑Baustein verwendet werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der Baustein besitzt keine klassischen Event‑Eingänge (EventInputs). Stattdessen werden die auslösenden Ereignisse **über die Adapter‑Sockets** hereingeführt:
* **CU.E1** – Ereignis vom *Count up*‑Adapter: ein ansteigender Impuls erhöht den Zählerstand um 1.
* **R.E1** – Ereignis vom *Reset*‑Adapter: setzt den Zählerstand auf 0 zurück.
* **PV.E1** – Ereignis vom *Preset value*‑Adapter: übernimmt den aktuell am Preset‑Eingang anliegenden Wert als neuen Vorwahlwert (wirkt sofort, ohne den Zähler zu ändern).

Alle drei Ereignisse werden intern auf den **REQ**‑Event des eingebetteten IEC‑Funktionsblocks `FB_CTU_UDINT` gemultiplext. Das bedeutet, dass jeder dieser externen Impulse eine Verarbeitung anstößt.

### **Ereignis-Ausgänge**
* **CNF** – Bestätigungs‑Event (EventOutput): wird nach jeder Verarbeitung eines eingehenden Ereignisses ausgegeben. Ist mit den Ausgangsadaptern mitverbunden, sodass die angeschlossenen Komponenten über eine erfolgte Zähloperation informiert werden.

Zusätzlich werden folgende **Adapter‑Events** ausgelöst (über interne Verdrahtung):
* **Q.E1** – Event des *Output*‑Adapters (Typ AX): signalisiert die Verfügbarkeit eines neuen Ausgangswerts Q.
* **CV.E1** – Event des *Count value*‑Adapters (Typ AUDI): signalisiert die Verfügbarkeit eines neuen Zählerstands CV.

Diese Adapter‑Events feuern **gleichzeitig mit CNF**, d. h. bei jedem zählrelevanten Ereignis werden alle drei Ausgangs‑Events gleichzeitig aktiviert.

### **Daten-Eingänge**
Auch die Daten werden **über die Adapter‑Sockets** bereitgestellt:
* **CU.D1** (UDINT, über Adapter CU) – Zählimpuls: Nur der Wert 0 oder 1 wird ausgewertet; ein positiver Flankenwechsel (0→1) führt zu einer Erhöhung. (Der Adapter liefert das Ereignis selbst, zusätzlich kann der Datenwert z. B. als flankenbewertetes Signal genutzt werden.)
* **R.D1** (UDINT, über Adapter R) – Reset‑Signal: Ein Wert ≠0 setzt den Zähler zurück.
* **PV.D1** (UDINT, über Adapter PV) – Preset‑Wert: Der hier anliegende Wert wird beim Eintreffen des PV.E1‑Ereignisses als neue Vorwahl übernommen. (Der Datenwert wird also nur bei einem expliziten PV‑Ereignis eingelesen.)

### **Daten-Ausgänge**
* **Q.D1** (BOOL, über Adapter Q) – Ausgangssignal: `TRUE`, wenn der aktuelle Zählerstand **≥ PV** ist (Pre‑set Output).
* **CV.D1** (UDINT, über Adapter CV) – Aktueller Zählerstand (Count Value).

### **Adapter**
| Adapter-Typ | Richtung | Name | Kurzbeschreibung |
|-------------|----------|------|------------------|
| `AX` (unidirectional) | Socket (Eingang) | CU | Liefert das Zählimpuls‑Ereignis und einen flankenbewerteten Datenwert. |
| `AX` (unidirectional) | Socket (Eingang) | R | Liefert das Reset‑Ereignis und den Resetschalter. |
| `AUDI` (unidirectional) | Socket (Eingang) | PV | Liefert das Preset‑Ereignis und den Preset‑Zahlenwert. |
| `AX` (unidirectional) | Plug (Ausgang) | Q | Stellt das Ausgangsbinary (Q) als Ereignis und Datenwert bereit. |
| `AUDI` (unidirectional) | Plug (Ausgang) | CV | Stellt den aktuellen Zählerstand als Ereignis und Datenwert bereit. |

## Funktionsweise
Der **AUDI_FB_CTU** delegiert seine gesamte Zähllogik an den inneren IEC‑Baustein `FB_CTU_UDINT`. Bei jedem eingehenden Ereignis (CU.E1, R.E1 oder PV.E1) wird dessen **REQ**‑Eingang aktiviert. Der innere Zähler führt dann die folgende Logik aus:
1. **Reset zuerst**: Falls **R** ≠ 0, wird der Zähler auf 0 gesetzt.
2. **Zählimpuls**: Falls **CU** ≠ 0 und ein positiver Flankenübergang seit dem letzten Aufruf vorliegt, wird CV um 1 erhöht.
3. **Preset‑Übernahme**: Falls **PV.E1** ausgelöst wurde, wird der an PV anliegende Wert als neuer Schwellwert (PV) gespeichert.
4. **Vergleich**: Ist CV ≥ PV (gespeicherter Presetwert), wird **Q** = TRUE, sonst FALSE.

Nach der Verarbeitung werden die Ereignisse **CNF**, **Q.E1** und **CV.E1** gleichzeitig ausgegeben, unabhängig davon, ob sich Q oder CV geändert haben.

## Technische Besonderheiten
* **Adapterbasierung**: Sämtliche Ein‑ und Ausgänge sind als standardisierte unidirektionale Adapter (`AX` für Binär-, `AUDI` für Zahlenwerte) realisiert. Dies ermöglicht eine flexible Verschaltung in adapterorientierten Architekturen.
* **Multiplexing der Ereignisse**: Die drei Eingangsereignisse (CU, R, PV) werden auf einen gemeinsamen REQ gemultiplext. Dies vereinfacht die interne Verdrahtung, bedeutet aber, dass auch ein Reset‑ oder Presetvorgang den Ausgangs‑Event auslöst.
* **Keine on‑change‑Filterung**: Wie im Header‑Kommentar beschrieben, feuert der Baustein **immer** bei jeder Verarbeitung. Für eine reine Änderungsauslösung muss ein AX_D_FF nachgeschaltet werden (z. B. auf Q und CV).
* **Datenbreite**: Alle Zähler‑ und Vorwahlwerte sind als **UDINT** (32‑Bit vorzeichenlos) ausgeführt.
* **Zustandshaltung**: Der innere Zähler speichert den aktuellen Zählerstand und die Preset‑Schwelle über mehrere Aufrufe hinweg.

## Zustandsübersicht
Der Baustein verfügt über **keinen eigenen Zustandsautomaten** (ECC). Die Zustandslogik liegt vollständig im eingebetteten IEC‑Funktionsblock `FB_CTU_UDINT`. Dessen wesentliche Zustände sind:
* **Idle**: Warten auf ein Ereignis (CU.E1, R.E1 oder PV.E1).
* **Processing** (während des internen Durchlaufs): Auswerten der Eingangsdaten (CU, R, PV), Aktualisieren des Zählers und der Ausgänge Q und CV.
* **Emitting**: Ausgabe der Ereignisse CNF, Q.E1, CV.E1.

Ein expliziter Fehlerzustand ist nicht vorgesehen.

## Anwendungsszenarien
* **Ereigniszählung in adapterbasierten Automatisierungssystemen** – z. B. Zählen von Werkstücken auf einem Förderband, wobei der Sensor über einen AX‑Adapter angebunden ist.
* **Zeit- oder Impulszähler mit Reset** – Der Reset‑Adapter kann z. B. von einem manuellen Taster kommen.
* **Erreichen einer Schwellwertmarke** – Der PV‑Eingang erlaubt eine dynamische Grenzwertvorgabe; sobald der Zählerstand diesen Wert erreicht oder überschreitet, wird Q aktiv.
* **Integration in Modulsysteme** – Durch die standardisierten Adapter (AUDI, AX) lässt sich der Baustein leicht in bestehende adapterbasierte Bibliotheken einfügen.

## Vergleich mit ähnlichen Bausteinen
* **Gegensatz zu klassischen IEC‑CTU‑Bausteinen** (z. B. `CTU_UDINT` ohne Adapter): Diese haben direkte Event‑ und Daten‑Eingänge, benötigen aber keine Adapter‑Wrapper. Der AUDI_FB_CTU bietet den Vorteil einer adaptereinheitlichen Schnittstelle, erfordert aber ein spezifisches Adapter‑Mapping.
* **Gegensatz zu CTU‑Bausteinen mit On‑Change‑Auslösung**: Bausteine, die nur bei tatsächlichen Wertänderungen feuern, vermeiden unnötige Ereignisfluten. Der AUDI_FB_CTU feuert immer, was durch den Zusatz eines AX_D_FF kompensiert werden kann.
* **Vergleich zum AUDI_FB_CTD** (Abwärtszähler): Der interne IEC‑Baustein wäre dann `FB_CTD_UDINT`; Schnittstellen und Verhalten sind analog, nur Zählrichtung und Bedingung für Q unterscheiden sich (Q aktiv bei CV ≤ 0).

## Fazit
Der **AUDI_FB_CTU** stellt einen robusten, adapterbasierten Aufwärtszähler dar, der sich nahtlos in adapterorientierte Automatisierungslösungen integrieren lässt. Durch die Kapselung eines standardisierten IEC‑Zählers und die Verwendung von AUDI/AX‑Adaptern wird eine hohe Interoperabilität erreicht. Die Eigenschaft, bei jedem Ereignis zu feuern, ist für viele Anwendungen akzeptabel oder kann durch eine nachgeschaltete Filterung korrigiert werden. Der Baustein eignet sich besonders für modulare, erweiterbare Steuerungsarchitekturen, die auf Adapterprotokollen basieren.