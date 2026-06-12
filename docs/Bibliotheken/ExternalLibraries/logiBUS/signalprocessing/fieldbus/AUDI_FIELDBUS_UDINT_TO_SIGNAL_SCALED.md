# AUDI_FIELDBUS_UDINT_TO_SIGNAL_SCALED


![AUDI_FIELDBUS_UDINT_TO_SIGNAL_SCALED](./AUDI_FIELDBUS_UDINT_TO_SIGNAL_SCALED.svg)

*Bild des Funktionsblocks: nicht verfügbar*

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUDI_FIELDBUS_UDINT_TO_SIGNAL_SCALED** dient dazu, einen empfangenen UDINT-Wert (unsigned 32‑Bit Integer) aus einem Feldbusprotokoll in ein skaliertes Signal umzuwandeln und nur dann an den Ausgang weiterzuleiten, wenn das Eingangssignal als gültig markiert ist. Er stellt eine kombinierte Lösung aus Skalierung und Signalgültigkeitsprüfung dar und wird vor allem in der Automatisierungstechnik für LogiBUS-Anwendungen eingesetzt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name  | Typ    | Kommentar                     |
|-------|--------|-------------------------------|
| INIT  | EInit  | Initialisierungsanforderung   |

### **Ereignis-Ausgänge**

| Name  | Typ    | Kommentar                     |
|-------|--------|-------------------------------|
| INITO | EInit  | Initialisierungsbestätigung   |

### **Daten-Eingänge**

| Name   | Typ   | Kommentar                          | Initialwert      |
|--------|-------|------------------------------------|------------------|
| SCALE  | LREAL | Skalierungsfaktor                  | LREAL#1.0        |
| OFFSET | DINT  | Offset, der nach der Skalierung addiert wird | DINT#0           |

### **Daten-Ausgänge**

Keine separaten Datenausgänge – die skalierten Daten werden über den Adapterausgang `OUT` bereitgestellt.

### **Adapter**

| Name  | Typ              | Richtung | Kommentar                     |
|-------|------------------|----------|-------------------------------|
| IN    | unidirectional::AUDI | Eingang  | Feldbus-UDINT-Eingangssignal  |
| OUT   | unidirectional::ALR  | Ausgang  | Skaliertes Signal (falls gültig) |
| VALID | unidirectional::AX   | Ausgang  | Gültigkeitsflag (TRUE = gültig) |

## Funktionsweise

Der FB arbeitet intern als zusammengesetzter Baustein (Composite). Er besteht aus einem Unter-FB `FIELDBUS_UDINT_TO_SIGNAL_SCALED` (der die eigentliche Skalierung vornimmt) und einem flankengetriggerten D‑Flipflop `E_D_FF`.

- Über den Adapter `IN` wird ein UDINT-Wert (über `IN.D1`) und ein Ereignis (`IN.E1`) empfangen.
- Der eingehende Wert wird an den internen FB `FIELDBUS_UDINT_TO_SIGNAL_SCALED` weitergeleitet, der den Wert mit `SCALE` multipliziert und anschließend `OFFSET` addiert. Das Ergebnis steht am Ausgang `OUT.D1` zur Verfügung.
- Gleichzeitig wird vom internen FB ein Gültigkeitssignal (`VALID`) erzeugt, das angibt, ob der empfangene Rohwert als gültig erachtet wird.
- Dieses Gültigkeitssignal wird dem D‑Flipflop an seinem Dateneingang (`D`) zugeführt. Die steigende Flanke des Verarbeitungsereignisses (`CNF`) taktet das Flipflop (`CLK`).
- Am Ausgang `Q` des Flipflops liegt das verzögerungsfreie, synchronisierte Gültigkeitssignal an, das über den Adapter `VALID.D1` ausgegeben wird.
- Das Ereignis `OUT.E1` wird zeitgleich mit der Aktualisierung der Ausgabedaten ausgelöst, sodass nachgeschaltete Bausteine die neuen Werte abholen können.

## Technische Besonderheiten

- Der FB ist als **Composite-FB** realisiert, d.h. seine Funktionalität wird durch ein internes Netzwerk aus anderen Bausteinen abgebildet. Dies erlaubt eine klare Trennung von Skalierung und Gültigkeitslogik.
- Die Initialisierung erfolgt über das `INIT`-Ereignis, das an den internen FB weitergeleitet wird. Nach erfolgreicher Initialisierung wird `INITO` ausgegeben.
- Der Skalierungsfaktor `SCALE` und der `OFFSET` werden bei der Initialisierung gesetzt und können zur Laufzeit nicht geändert werden, da sie nicht über separate Ereignisse aktualisiert werden.
- Die Verwendung eines D‑Flipflops sorgt dafür, dass der Gültigkeitsstatus stabil bleibt, bis der nächste gültige Datenwert verarbeitet wird.
- Der Baustein ist für die Verwendung im LogiBUS‑Umfeld konzipiert (Package `logiBUS::signalprocessing::fieldbus`).

## Zustandsübersicht

Der FB besitzt keine expliziten Zustände im Sinne einer Zustandsmaschine. Seine interne Logik wird rein datenflussgesteuert über die Ereigniskette ausgeführt:

1. **Initialisierungsphase**: Nach Empfang von `INIT` wird der interne Baustein initialisiert und `INITO` gesendet.
2. **Datenverarbeitungsphase**: Ein eingehendes `IN.E1` löst die Skalierung und Gültigkeitsprüfung aus. Nach Abschluss werden `OUT.E1` und die Ausgabedaten aktualisiert.

## Anwendungsszenarien

- **Skalierung von Feldbussignalen**: Wenn ein Feldbus einen UDINT‑Wert liefert (z.B. einen Sensorzählerstand), der in eine physikalische Einheit umgerechnet werden muss, z.B. Skalierung und Offset.
- **Gültigkeitsprüfung**: Nur gültige Messwerte sollen an die Steuerung weitergegeben werden. Das Flag `VALID` kann z.B. von einem übergeordneten Sicherheitsbaustein ausgewertet werden.
- **Kopplung von LogiBUS‑ und IEC‑61499‑Systemen**: Der FB dient als Brücke zwischen dem LogiBUS‑Protokoll und standardisierten Funktionsbausteinen.

## Vergleich mit ähnlichen Bausteinen

- **FIELDBUS_UDINT_TO_SIGNAL_SCALED** (nackter Skalierbaustein): Dieser Baustein führt nur die Skalierung durch, ohne die Gültigkeitsprüfung und ohne die Speicherlogik. Der vorliegende Composite-FB erweitert ihn um die Zustandsverwaltung des Gültigkeitsflags.
- **Standard IEC 61499 Skalierbausteine** (z.B. `SCALE`): Meist als einfache Arithmetik‑Bausteine realisiert, fehlt oft die Integration einer Gültigkeitslogik und die Anbindung an Feldbus‑Adapter.

## Fazit

Der Funktionsblock `AUDI_FIELDBUS_UDINT_TO_SIGNAL_SCALED` bietet eine kompakte, wiederverwendbare Lösung zur skalierenden Signalverarbeitung mit integrierter Gültigkeitsprüfung in LogiBUS‑Umgebungen. Er kombiniert Skalierung, Offset und eine flankengetriggerte Gültigkeitssperre, sodass am Ausgang nur gültige und korrekt skalierte Werte anliegen. Dank der Composite‑Struktur ist er leicht erweiterbar und gut in bestehende IEC‑61499‑Projekte integrierbar.