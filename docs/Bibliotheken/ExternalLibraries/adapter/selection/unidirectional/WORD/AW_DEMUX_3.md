# AW_DEMUX_3


![AW_DEMUX_3](./AW_DEMUX_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AW_DEMUX_3** ist ein generischer Demultiplexer für den unidirektionalen Adaptertyp `AW`. Er verteilt einen eingehenden Datenwert, der über den Socket‑Adapter `IN` bereitgestellt wird, abhängig von einem ganzzahligen Index `K` auf einen von drei Ausgangsadaptern (`OUT1`, `OUT2`, `OUT3`). Der Baustein wird über das Ereignis `REQ` gesteuert und quittiert die Verteilung mit `CNF`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Set Index K; löst die Verteilung aus. |

Der Ereigniseingang `REQ` triggert die Demultiplex‑Operation. Der aktuelle Wert des Daten‑Eingangs `K` bestimmt, an welchen Ausgangsadapter der eingehende Wert weitergeleitet wird.

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Confirmation of Set Index K. |

Nach erfolgreicher Verteilung wird das Ereignis `CNF` ausgegeben. Es signalisiert, dass der Datenwert auf dem gewählten Ausgang anliegt.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `K` | UINT | index (1‑basiert, erwarteter Wertebereich 1…3) |

Der Eingang `K` legt fest, welcher der drei Ausgänge (`OUT1`, `OUT2`, `OUT3`) bedient wird. Werte außerhalb des Bereichs 1 – 3 werden ignoriert oder führen zu keiner Weiterleitung (abhängig von der konkreten Implementierung).

### **Daten-Ausgänge**

Der Baustein besitzt keine expliziten Daten‑Ausgänge. Alle Ausgangsdaten werden über die Adapter‑Schnittstellen bereitgestellt.

### **Adapter**

| Typ | Name | Richtung | Kommentar |
|-----|------|----------|-----------|
| `adapter::types::unidirectional::AW` | `IN` | Socket | Eingangswert, der demultiplext werden soll |
| `adapter::types::unidirectional::AW` | `OUT1` | Plug | 1. Ausgang |
| `adapter::types::unidirectional::AW` | `OUT2` | Plug | 2. Ausgang |
| `adapter::types::unidirectional::AW` | `OUT3` | Plug | 3. Ausgang |

Alle Adapter sind vom gleichen unidirektionalen Typ `AW`. Der Socket `IN` empfängt den zu verteilenden Datenwert. Die drei Plugs `OUT1`…`OUT3` stellen die jeweiligen Ausgänge dar.

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis am Eingang `REQ`.
2. Beim Eintreffen von `REQ` wird der aktuelle Wert des Daten‑Eingangs `K` ausgelesen.
3. Abhängig von `K` (Werte 1, 2 oder 3) wird der über den Socket `IN` anliegende Datenwert auf den entsprechenden Plug (`OUT1`, `OUT2` oder `OUT3`) durchgeschaltet. Alle anderen Ausgänge bleiben unverändert oder werden in einen definierten Ruhezustand versetzt (abhängig von der Adapter‑Definition).
4. Nach erfolgter Weiterleitung wird das Ereignis `CNF` ausgegeben, um den erfolgreichen Abschluss zu bestätigen.

Da der Adaptertyp `AW` unidirektional ist, erfolgt die Datenübertragung nur vom Socket zu den Plugs; eine Rückmeldung von den Verbrauchern ist nicht vorgesehen.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Baustein (`GenericClassName = 'GEN_AW_DEMUX'`) deklariert. Dies ermöglicht eine spätere Instanziierung oder Anpassung an unterschiedliche Ausgangszahlen, obwohl die vorliegende Version fest drei Ausgänge besitzt.
- **Unidirektionale Kommunikation**: Der verwendete Adapter `adapter::types::unidirectional::AW` erlaubt nur einen Datenfluss vom Sender (Socket) zum Empfänger (Plug). Eine Rückkopplung oder Quittierung von den angeschlossenen Verbrauchern ist nicht enthalten.
- **Kein interner Zustandsautomat**: Die Funktionalität ist rein ereignisgesteuert und verwendet keinen expliziten Zustandsautomaten (ECC). Der FB reagiert sofort bei jedem `REQ`‑Ereignis mit der Verteilung.
- **Indexprüfung**: Der Eingang `K` ist vom Typ `UINT`. Es wird erwartet, dass nur die Werte 1, 2 oder 3 verwendet werden. Abweichende Werte sollten durch die aufrufende Applikation ausgeschlossen werden.

## Zustandsübersicht

Der Baustein **AW_DEMUX_3** besitzt keinen modellierten internen Zustandsautomaten. Sein Verhalten ist deterministisch und rein transaktionsbasiert:  
- Im Ruhezustand wartet er auf `REQ`.  
- Bei `REQ` wird die Verteilung ausgeführt, und es wird sofort `CNF` ausgegeben.  
- Danach kehrt er in den Ruhezustand zurück.

Es gibt keine Halte‑, Fehler‑ oder Sonderzustände.

## Anwendungsszenarien

- **Signalverteilung in der Automatisierung**: Ein analoger oder digitaler Messwert (z. B. Temperatur, Druck) aus einer Sensoreinheit soll je nach Betriebsmodus an unterschiedliche Aktuatoren oder Steuerungsblöcke weitergeleitet werden.
- **Kanalumschaltung**: In einer Kommunikationskette wird ein eingehendes Datensignal durch einen Index auf einen von drei nachgeschalteten Verarbeitungspfaden geschaltet.
- **Test- und Simulationsumgebungen**: Der Baustein kann verwendet werden, um einen generischen Datenstrom auf verschiedene Testmodule zu verteilen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Beschreibung | Unterschied zu AW_DEMUX_3 |
|----------|--------------|---------------------------|
| **AW_MUX_3** | Multiplexer – fasst drei Eingänge zu einem Ausgang zusammen | Umgekehrte Datenrichtung: DEMUX verteilt, MUX vereint |
| **AW_DEMUX_2** | Demultiplexer mit zwei Ausgängen | Geringere Anzahl von Ausgängen |
| **E_DEMUX** (Ereignis‑Demux) | Verteilt Ereignisse statt Datenwerte | AW_DEMUX_3 verteilt Daten über Adapter, nicht Ereignisse |
| **GEN_DEMUX** (generischer, nicht adapter‑spezifisch) | Allgemeiner Demultiplexer mit Adapter‑generischer Schnittstelle | AW_DEMUX_3 ist spezifisch auf den Typ `AW` ausgelegt |

Der größte Unterschied zu reinen Daten‑ oder Ereignis‑Demultiplexern ist die Verwendung des Adapter‑Typs `AW`, der eine standardisierte, unidirektionale Datenübertragung in der 4diac‑IDE kapselt.

## Fazit

Der **AW_DEMUX_3** ist ein kompakter, generischer Demultiplexer für den Adapter‑Typ `AW`. Mit einem Ereignis gesteuert, verteilt er auf Basis eines Indexes Eingangsdaten auf drei Ausgänge. Seine einfache, transaktionsorientierte Funktionsweise ohne Zustandsautomaten macht ihn zu einem verlässlichen Baustein für die gezielte Signalweiterleitung in industriellen Steuerungs‑ und Automatisierungslösungen. Der generische Charakter ermöglicht zudem eine flexible Wiederverwendung in unterschiedlichen Projekten.