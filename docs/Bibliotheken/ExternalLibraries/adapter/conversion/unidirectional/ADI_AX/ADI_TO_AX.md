# ADI_TO_AX


![ADI_TO_AX](./ADI_TO_AX.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ADI_TO_AX** ist ein Composite-Baustein, der eine einfache Signalumsetzung zwischen zwei Adaptertypen realisiert. Er wandelt einen über den **ADI_IN**-Socket empfangenen DINT-Wert (Typ: *adapter::types::unidirectional::ADI*) in einen BOOL-Wert um und gibt diesen über den **AX_OUT**-Plug (Typ: *adapter::types::unidirectional::AX*) aus. Die Umwandlung erfolgt durch einen Vergleich des empfangenen DINT-Werts mit dem konstanten Wert 0. Ist der Wert ungleich 0, wird der BOOL-Ausgang auf TRUE gesetzt; bei Gleichheit auf FALSE. Der Baustein eignet sich vor allem für die Anbindung von digitalen Signalquellen, die als Ganzzahlen codiert sind, an boolesche Schnittstellen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Beschreibung |
|---|---|
| *(keine expliziten Ereignis-Eingänge)* | Der FB nutzt ausschließlich die über den ADI_IN-Adapter angebundenen Ereignisse. Tatsächlich wird das Ereignis `E1` des ADI_IN-Adapters intern auf den Funktionsbaustein `F_NE` weitergeleitet. |

### **Ereignis-Ausgänge**
| Name | Beschreibung |
|---|---|
| *(keine expliziten Ereignis-Ausgänge)* | Der Ausgang erfolgt über den AX_OUT-Adapter; das Ereignis `E1` des AX_OUT-Adapters wird nach erfolgreicher Verarbeitung des `F_NE`-Aufrufs gesendet. |

### **Daten-Eingänge**
| Name | Typ | Beschreibung |
|---|---|---|
| *(über ADI_IN-Adapter)* | `DINT` | Der über den Adapter-Socket angebundene DINT-Wert (z. B. Messwert oder Statuscode) wird als Eingang `D1` des ADI_IN-Adapters empfangen. |

### **Daten-Ausgänge**
| Name | Typ | Beschreibung |
|---|---|---|
| *(über AX_OUT-Adapter)* | `BOOL` | Der Ausgangswert wird als `D1` des AX_OUT-Adapters bereitgestellt. TRUE, wenn der empfangene DINT-Wert ungleich 0 ist; sonst FALSE. |

### **Adapter**
| Adapter | Name | Richtung | Typ | Beschreibung |
|---|---|---|---|---|
| Socket | ADI_IN | Eingang | `adapter::types::unidirectional::ADI` | Nimmt einen DINT-Wert (mit zugehörigem Ereignis) entgegen. |
| Plug | AX_OUT | Ausgang | `adapter::types::unidirectional::AX` | Gibt den resultierenden BOOL-Wert (mit zugehörigem Ereignis) weiter. |

## Funktionsweise

Der Baustein besteht intern aus einem einzigen Funktionsbaustein **F_NE** des Typs `iec61131::comparison::F_NE`. Dieser implementiert die IEC-61131-Funktion „Ungleich“ (NE – Not Equal). Das Verhalten:

1. Ein eingehendes Ereignis **E1** des ADI_IN-Adapters wird an den **REQ**-Eingang des **F_NE** weitergeleitet.
2. Der Datenwert **D1** des ADI_IN-Adapters wird an den **IN1**-Eingang des **F_NE** gelegt. Der zweite Vergleichswert **IN2** ist fest auf den Wert `DINT#0` eingestellt.
3. Der **F_NE** vergleicht `IN1 != IN2`. Das Ergebnis (BOOL) wird am Ausgang **OUT** ausgegeben.
4. Nach Beendigung der Verarbeitung signalisiert **F_NE.CNF** die Fertigstellung. Dieses Ereignis wird an den **E1**-Eingang des AX_OUT-Adapters gesendet, wodurch der Ausgangswert (ebenfalls das **OUT**-Signal) an **D1** des AX_OUT-Adapters weitergegeben wird.

Damit realisiert der FB eine einfache „Schwellwertlogik“: Jeder von Null verschiedene DINT-Wert wird als logisch „Wahr“ interpretiert. Der Baustein arbeit dabei strikt ereignisgesteuert – jedes eingehende Ereignis löst genau eine Vergleiche- und Ausgabeaktion aus.

## Technische Besonderheiten

- **Adapter-Kopplung:** Der FB ist als Composite-Baustein konzipiert, der zwei unidirektionale Adapter miteinander verbindet. Er kann daher nahtlos in eine Adapter-basierte Kommunikationsarchitektur eingebunden werden.
- **Keine eigenen Zustände:** Da der FB keinerlei interne Zustandsvariablen oder Timer besitzt, ist sein Verhalten rein kombinatorisch und deterministisch.
- **Direkte Impedanz:** Der verwendete Baustein `F_NE` aus der IEC-61131-Bibliothek ist hochperformant und benötigt keine dynamische Speicherverwaltung.
- **Typsicherheit:** Die Konstante `DINT#0` wird explizit als DINT deklariert, sodass keine impliziten Typkonvertierungen auftreten.
- **Lizenzhinweis:** Der Baustein unterliegt der Eclipse Public License 2.0 (EPL-2.0), Copyright 2026 HR Agrartechnik GmbH.

## Zustandsübersicht

Der FB besitzt keine eigenen Zustände, da er vollständig auf dem internen funktionalen Block **F_NE** aufbaut. Das Verhalten ist daher ohne Verzögerungen oder Speicherung auskommend. Der Ablauf ist:

- **Warten auf Ereignis:** Inaktiv, bis ein Ereignis über den ADI_IN-Adapter eintrifft.
- **Verarbeitung:** Nach Ereigniseingang wird der Vergleich ausgeführt; der Ausgang aktualisiert sich sofort. Nach dem Vergleich wird das Ausgangsereignis gesendet.

## Anwendungsszenarien

- **Digitalisierung von analogen Werten:** In der Automatisierung werden häufig DINT-Werte (z. B. Zählerstände, Fehlercodes) als boolesche Signale interpretiert. Der FB eignet sich zur Umwandlung von „ungleich Null“-Bedingungen in binäre Signale.
- **Adapter-Brückenbildung:** Wenn eine Komponente nur einen ADI-Adapter bereitstellt, die nachgeschaltete Logik aber nur AX-Adapter akzeptiert, kann dieser FB als verlustfreier Konverter eingesetzt werden.
- **Einfache Schaltschwellen:** Mit minimalem Aufwand lässt sich feststellen, ob ein Wert von Null abweicht – nützlich z. B. für Überwachung von Zählimpulsen oder Grenzwertverletzungen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Typ | Funktion |
|---|---|---|
| **ADI_TO_AX** (dieser FB) | Composite | DINT ≠ 0 → BOOL |
| `BOOL_TO_DINT` (Standard-Bibliothek) | Funktion | Direkte Konvertierung von BOOL zu DINT (z. B. TRUE → 1) |
| `F_NE` (IEC 61131) | Funktion | Allgemeiner Ungleich-Vergleich beliebiger Datentypen |
| **Eigener Adapter-Konverter** | – | Kann einfach durch andere Vergleichsfunktionen (F_EQ, F_GT, etc.) erweitert werden |

Im Vergleich zu einer reinen BOOL-zu-DINT-Konvertierung bietet **ADI_TO_AX** den Vorteil, dass der DINT-Wert exakt beibehalten wird (z. B. 42 → TRUE), während eine boolesche Konvertierung nur zwischen TRUE/FALSE und 1/0 unterscheiden kann.

## Fazit

Der Funktionsblock **ADI_TO_AX** ist ein schlanker und robuster Adapter-Konverter für unidirektionale Schnittstellen. Er nutzt den bewährten IEC-61131-Vergleichsbaustein `F_NE` und setzt damit eine einfache, aber nützliche Logik um: „Jeder Wert ungleich Null ist wahr.“ Der FB eignet sich besonders für den Einsatz in modularen Automatisierungssystemen, bei denen unterschiedliche Adapter-Standards aufeinander abgestimmt werden müssen. Dank der Composite-Struktur kann er leicht in eigene Netzwerke integriert und bei Bedarf erweitert werden.