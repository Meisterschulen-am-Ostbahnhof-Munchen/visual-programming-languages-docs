# AX_FB_TP_LTIME


![AX_FB_TP_LTIME](./AX_FB_TP_LTIME.svg)

* * * * * * * * * *
## Einleitung
Der **AX_FB_TP_LTIME** ist ein standardisierter Puls-Timer-Funktionsblock (Timer-Pulse) gemäß IEC 61131-3, erweitert um einen uni-direktionalen **AX-Adapter**. Er wird in der 4diac-IDE verwendet, um zeitlich begrenzte Impulse zu erzeugen und die Ausgangssignale über einen Adapter an die Anwendung zu übergeben. Das Verhalten entspricht einem **TP**-Timer, der bei einem steigenden Flanke am Eingang den Ausgang für eine vorgegebene Zeit auf TRUE setzt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Normaler Ausführungsanforderung (nicht-triggernd) |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Ausführungsbestätigung |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| PT   | LTIME | Pulszeit (Impulsdauer) |

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| ET   | LTIME | Verstrichene Zeit (Elapsed Time) |

### **Adapter**
- **Stecker (Plugs):**  
  - **Q**: Ausgangsadapter vom Typ `adapter::types::unidirectional::AX`.  
    Über diesen Adapter wird das boolesche Ausgangssignal `Q.D1` sowie das Ereignis `Q.E1` an die Anwendung weitergegeben.

- **Buchse (Sockets):**  
  - **IN**: Eingangsadapter vom Typ `adapter::types::unidirectional::AX`.  
    Über diesen Adapter empfängt der Baustein das Start-Ereignis (über `IN.E1`) und ggf. ein boolesches Signal (über `IN.D1`), das intern als Freigabe oder Zusatzbedingung genutzt wird (hier nicht direkt mit der Timerlogik verbunden, sondern zu einem internen Standard-Timer geführt).

## Funktionsweise
Der Baustein besteht intern aus zwei Komponenten:
1. **FB_TP_LTIME** – ein reiner Puls-Timer (IEC 61131‑3 TP) mit Zeitbasis LTIME.
2. **E_D_FF** – ein flankengesteuertes D‑Flipflop (E‑D‑FF gemäß IEC 61499), das den Q‑Ausgang des Timers zwischenspeichert.

**Ablauf:**
- Ein Ereignis über den Adaptereingang `IN.E1` oder den Standard‑Eventeingang `REQ` startet den Timer `FB_TP_LTIME` (die Ereignisse sind intern zusammengeführt – beide lösen denselben Start aus).
- Der Timer zählt die verstrichene Zeit `ET` hoch und setzt seinen internen boolschen Ausgang `Q` auf TRUE, sobald `PT` erreicht ist. Nach Ablauf der Pulszeit wird `Q` wieder FALSE und ein `CNF`-Ereignis ausgegeben.
- Das `CNF`-Ereignis taktet das D‑Flipflop `E_D_FF`, welches den aktuellen Zustand von `Q` (also TRUE während der Pulsdauer, FALSE danach) übernimmt und am Ausgang `Q.D1` des Adapters bereitstellt.
- Gleichzeitig wird das `CNF`-Ereignis auch direkt an den Ausgang `CNF` des Gesamtbausteins weitergeleitet, sodass die Anwendung über das Ende des Impulses informiert wird.
- Der Ausgang `ET` gibt die aktuell verstrichene Zeit an und ist direkt mit dem Ausgang des internen Timers verbunden.

## Technische Besonderheiten
- **Adapter‑Schnittstelle:** Der FB kapselt die Timerlogik in eine Adapter‑Schnittstelle, sodass er in modularen, adapterbasierten Architekturen einfach eingebunden werden kann.
- **D‑Flipflop zur Signalhaltung:** Der Q‑Ausgang des Timers wird über ein Flipflop synchron zum `CNF`-Ereignis übernommen, um Glitches oder asynchrone Änderungen zu vermeiden.
- **Doppelter Ereignispfad:** Der Start des Timers kann sowohl über den Adapter (`IN.E1`) als auch über den Standard‑Eventeingang `REQ` erfolgen – beide sind intern verbunden, was eine flexible Ansteuerung erlaubt.
- **LTIME‑Unterstützung:** Die Pulszeit wird als `LTIME` (Long Time, 64‑Bit Nanosekunden) verarbeitet, was eine extrem hohe Zeitauflösung und große Zeitbereiche ermöglicht.

## Zustandsübersicht
Da der Funktionsblock aus zwei Teilen besteht, ergibt sich folgendes Zustandsverhalten für den Gesamtbaustein:

| Zustand | Beschreibung |
|---------|--------------|
| **IDLE** | Kein Impuls aktiv. Der Adapterausgang `Q.D1` ist FALSE. |
| **TIMING** | Ein Puls läuft – der interne Timer zählt hoch. `ET` steigt, `Q.D1` ist TRUE (sobald das Flipflop beim Start oder nach dem ersten CNF getaktet wurde). |
| **DONE** | Der Puls ist abgeschlossen. `CNF` wurde ausgegeben, `ET` ist gleich `PT`, `Q.D1` wird mit dem nächsten `CNF` auf FALSE gesetzt. Bei einem neuen `REQ` oder `IN.E1` beginnt der Zyklus von vorn. |

## Anwendungsszenarien
- **Impulsausgabe mit definierter Länge:** Steuerung von Aktoren (z. B. Ventile, Lampen), die für eine bestimmte Zeit eingeschaltet werden sollen.
- **Adapter‑basierte Subsysteme:** Einbinden des Timers in eine modulare Automatisierungslösung, bei der Ein‑ und Ausgänge über Adapter (AX‑Protokoll) kommunizieren.
- **Zeitmessung mit hoher Auflösung:** Nutzung von `LTIME` für präzise Zeitsteuerungen im Mikro‑ oder Nanosekundenbereich.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Typ | Besonderheit |
|----------|-----|--------------|
| **FB_TP_LTIME** (Standard) | TP‑Timer | Kein Adapter, nur Standard‑Events und Signale. |
| **AX_FB_TP_LTIME** (dieser FB) | TP‑Timer mit AX‑Adapter | Ermöglicht Einbindung in adapterbasierte Architekturen, enthält D‑Flipflop zur Signalstabilisierung. |
| **FB_TON_LTIME** | Einschaltverzögerung | Verzögert das Einschalten eines Ausgangs. |
| **FB_TOF_LTIME** | Ausschaltverzögerung | Verzögert das Ausschalten eines Ausgangs. |

Der vorliegende Baustein kombiniert die Timerfunktion eines TP mit der Flexibilität eines Adapters.

## Fazit
Der **AX_FB_TP_LTIME** ist ein robuster und präziser Puls‑Timer für die 4diac‑IDE, der durch die Adapter‑Schnittstelle und die Verwendung von `LTIME` besonders geeignet für hochauflösende, modulare Automatisierungslösungen ist. Die interne Flipflop‑Struktur sorgt für saubere Signalübergaben, und die doppelte Ereignisbeschaltung bietet Flexibilität in der Ansteuerung.