# AD_FIELDBUS_DWORD_TO_SIGNAL_SCALED


![AD_FIELDBUS_DWORD_TO_SIGNAL_SCALED](./AD_FIELDBUS_DWORD_TO_SIGNAL_SCALED.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AD_FIELDBUS_DWORD_TO_SIGNAL_SCALED` dient der Aufbereitung eines digitalen Feldbus-Signals (DWORD) zu einem skalierten analogen Ausgangswert. Er spiegelt den Eingangswert auf den Ausgang, sofern die Signalvalidität gegeben ist, und wendet dabei eine lineare Skalierung mit Offset an. Die gültige Signalzustandsinformation wird über einen flankengetriggerten Flip-Flop synchronisiert und als separates Ausgangssignal bereitgestellt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INIT | EInit | Initialisierungsanforderung für den gesamten Baustein (Weiterleitung an internen Kernbaustein) |

### **Ereignis-Ausgänge**

| Ereignis | Typ | Beschreibung |
|----------|-----|--------------|
| INITO | EInit | Initialisierungsbestätigung nach erfolgreicher Initialisierung |

### **Daten-Eingänge**

| Name | Datentyp | Initialwert | Beschreibung |
|------|----------|-------------|--------------|
| SCALE | LREAL | 1.0 | Skalierungsfaktor, mit dem der Eingangswert multipliziert wird |
| OFFSET | DINT | 0 | Ganzzahliger Offset, der nach der Skalierung addiert wird |

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Datenausgänge. Alle Ausgangsdaten werden über die Adapter-Schnittstellen bereitgestellt.

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| IN | AD (unidirektional) | Socket | Eingangsadapter für den DWORD-Wert (Feldbussignal) |
| OUT | ALR (unidirektional) | Plug | Ausgangsadapter für den skalierten Analogwert |
| VALID | AX (unidirektional) | Plug | Ausgangsadapter für die Signalvalidität (TRUE = gültig) |

## Funktionsweise

Der Baustein realisiert die Signalkette:

1. **Initialisierung**: Das Ereignis `INIT` wird direkt an den internen Kernbaustein `FIELDBUS_DWORD_TO_SIGNAL_SCALED` weitergeleitet. Nach Abschluss wird `INITO` ausgegeben.
2. **Datenverarbeitung**: Der am Socket `IN` anliegende DWORD-Wert wird bei jedem Datenereignis (E1) übernommen. Der Kernbaustein multipliziert den Wert mit `SCALE` (LREAL) und addiert den `OFFSET` (DINT). Das Ergebnis wird als LREAL auf den Plug `OUT` gegeben.
3. **Validitätssignal**: Der Kernbaustein gibt ein internes boolsches Validitätssignal aus, das angibt, ob der momentane Datenwert gültig ist. Dieses Signal wird über einen flankengetriggerten D-Flipflop (`E_D_FF`) synchronisiert und auf den Plug `VALID` ausgegeben. Der Flipflop taktet mit dem gleichen Ereignis (`CNF` des Kernbausteins), sodass die Validität zeitgleich mit dem Ausgangswert aktualisiert wird.

Die interne Verschaltung stellt sicher, dass der Validitätsstatus immer dem letzten verarbeiteten Datenwert entspricht.

## Technische Besonderheiten

- **Skalierungsreihenfolge**: Zuerst Multiplikation mit `SCALE` (LREAL), dann Addition von `OFFSET` (DINT). Dadurch kann der Offset auch in Einheiten des skalierten Bereichs angegeben werden.
- **Flankensynchronisation**: Das Validitätssignal wird über einen D-Flipflop flankengesteuert ausgegeben, sodass es keine metastabilen Zustände auf der Ausgangsseite gibt.
- **Initialwertvorgabe**: `SCALE` ist auf 1.0 vordefiniert, `OFFSET` auf 0. Im unskalierten Fall entspricht der Ausgang somit direkt dem Eingang.
- **Adapterstruktur**: Die Ein- und Ausgänge sind als Adapter realisiert, was eine typsichere Verbindung mit anderen Bausteinen aus derselben Adapterfamilie (AD, ALR, AX) ermöglicht.

## Zustandsübersicht

Der Baustein besitzt kein eigenes explizites Zustandsdiagramm (ECC). Die gesamte Zustandslogik liegt im internen Kernbaustein `FIELDBUS_DWORD_TO_SIGNAL_SCALED` und im flankengetriggerten D-Flipflop. Dieser speichert den letzten gültigen Validitätszustand. Bei jedem Verarbeitungsereignis wird der Flipflop getaktet und gibt den aktuellen Validitätswert aus.

## Anwendungsszenarien

- **Messwerterfassung über Feldbus**: Ein DWORD-Rohwert (z. B. von einem Analog-Digital-Wandler oder Encoder) wird mit physikalischen Faktoren (Skalierung) und Offset umgerechnet und als Analogwert an eine Steuerung übergeben.
- **Signalvalidierung mit Speicherung**: Wenn der Feldbus eine Gültigkeitsflagge (z. B. „Daten neu“) liefert, kann diese über die Validitätsadapterebene ausgewertet werden. Der Flipflop stellt sicher, dass das Gültigkeitssignal bis zur nächsten Aktualisierung stabil bleibt.
- **Parametrierbare Skalierung**: Durch externe Vorgabe von `SCALE` und `OFFSET` kann der gleiche Baustein für unterschiedliche Sensorbereiche verwendet werden, ohne den Baustein selbst zu ändern.

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem einfachen `MOVE`- oder `SCALE`-Baustein bietet dieser FB eine integrierte Validitätsbehandlung und eine saubere Trennung zwischen Daten- und Ereignisadaptern. Ähnliche Bausteine (z. B. `FIELD_DWORD_TO_ANALOG`) fehlen oft die separate Ausgabe der Signalvalidität oder die flankensynchrone Speicherung. Die hier verwendete Kombination aus Kernbaustein und D-Flipflop ist eine bewährte Lösung für sicherheitskritische Anwendungen, bei denen die Gültigkeit eines Datenwerts zuverlässig mitgeführt werden muss.

## Fazit

Der Funktionsblock `AD_FIELDBUS_DWORD_TO_SIGNAL_SCALED` ist ein robuster und parametrierbarer Baustein zur Umwandlung digitaler Feldbussignale in skalierte Analogwerte mit synchroner Validitätsausgabe. Dank der modularen Adapteranschlüsse und integrierten Flankensynchronisation eignet er sich besonders für industrielle Automatisierungssysteme, bei denen Datenkonsistenz und Signalqualität gleichermaßen wichtig sind.