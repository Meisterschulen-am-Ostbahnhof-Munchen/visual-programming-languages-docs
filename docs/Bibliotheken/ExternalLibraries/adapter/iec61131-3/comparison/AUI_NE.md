# AUI_NE


![AUI_NE](./AUI_NE.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `AUI_NE` realisiert einen Ungleich-Vergleich (not equal) für zwei Eingangswerte. Er ist als Composite-FB (zusammengesetzter Baustein) aus dem IEC-61131-3-Vergleichsbaustein `F_NE` aufgebaut. Die Kommunikation mit der Umgebung erfolgt über standardisierte Adapter-Schnittstellen (`AUI` für die Eingänge, `AX` für den Ausgang). Dadurch lässt er sich in adapterbasierte Architekturen der 4diac-IDE nahtlos integrieren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Der FB besitzt keine direkten Ereignis-Eingänge. Ereignisse werden über die **Socket-Adapter** `IN1` und `IN2` empfangen:

| Adapter | Ereignis | Beschreibung |
|---------|----------|--------------|
| `IN1`   | Ereignis über Adapter-Eingang E1 | Startet den Vergleich, wenn der Wert an `IN1` bereitsteht. |
| `IN2`   | Ereignis über Adapter-Eingang E1 | Startet den Vergleich, wenn der Wert an `IN2` bereitsteht. |

Beide Ereignisse führen zur Aktivierung des internen `F_NE`-Bausteins.

### **Ereignis-Ausgänge**

Der FB besitzt keine direkten Ereignis-Ausgänge. Das Ergebnis wird über den **Plug-Adapter** `OUT` ausgegeben:

| Adapter | Ereignis | Beschreibung |
|---------|----------|--------------|
| `OUT`   | Ereignis über Adapter-Ausgang E1 | Zeigt an, dass der Vergleich abgeschlossen ist und der Ergebniswert gültig ist. |

### **Daten-Eingänge**

Daten werden ebenfalls über die Socket-Adapter bereitgestellt:

| Adapter | Datenpunkt | Typ | Beschreibung |
|---------|------------|-----|--------------|
| `IN1`   | D1         | ANY (über AUI) | Erster Vergleichswert |
| `IN2`   | D2         | ANY (über AUI) | Zweiter Vergleichswert |

Die genauen Datentypen werden durch die verwendete Adapter-Instanz (`adapter::types::unidirectional::AUI`) festgelegt.

### **Daten-Ausgänge**

Der Ergebniswert wird über den Plug-Adapter ausgegeben:

| Adapter | Datenpunkt | Typ | Beschreibung |
|---------|------------|-----|--------------|
| `OUT`   | D1         | BOOL (über AX) | `TRUE`, wenn IN1 ≠ IN2; `FALSE` sonst. |

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| `IN1`   | Socket   | `adapter::types::unidirectional::AUI` | Aufnehmender Adapter für den ersten Eingangswert. |
| `IN2`   | Socket   | `adapter::types::unidirectional::AUI` | Aufnehmender Adapter für den zweiten Eingangswert. |
| `OUT`   | Plug     | `adapter::types::unidirectional::AX`   | Ausgebender Adapter für das Vergleichsergebnis. |

## Funktionsweise

Bei jedem eingehenden Ereignis über `IN1.E1` oder `IN2.E1` wird der interne Baustein `F_NE` (IEC 61131-3: `NOT EQUAL`) getriggert. `F_NE` vergleicht die Werte an den Datenpunkten `IN1.D1` und `IN2.D2`. Das Ergebnis (BOOL) wird an den Ausgangsadapter `OUT.D1` weitergeleitet und gleichzeitig ein Ereignis an `OUT.E1` gesendet, um den Ergebnisabruf zu signalisieren.

Der FB arbeitet **ereignisgesteuert** – ein Vergleich wird nur dann neu berechnet, wenn mindestens einer der beiden Eingangsadapter ein Ereignis empfängt. Dadurch wird unnötige Rechenlast vermieden.

## Technische Besonderheiten

- **Adapter-Kapselung**: Die gesamte Ein-/Ausgabe erfolgt über standardisierte Adapter, wodurch der FB in komplexe Adapter-Netzwerke eingebunden werden kann.
- **Wiederverwendung**: Intern wird der bewährte IEC-61131-3-Baustein `F_NE` genutzt, der einen effizienten, typunabhängigen Ungleich-Vergleich implementiert.
- **Unidirektionale Adapter**: Die verwendeten Adapter (`AUI`, `AX`) sind unidirektional – sie unterstützen jeweils nur eine Daten- und Ereignisrichtung, was die Klarheit der Datenflüsse erhöht.
- **Keine Zustandsspeicherung**: Der FB ist zustandslos; jedes Ereignis führt zu einer Neuberechnung.

## Zustandsübersicht

Der FB `AUI_NE` selbst besitzt keinen eigenen Zustandsautomaten. Das Verhalten wird vollständig durch den internen `F_NE`-Baustein bestimmt, der einen einfachen funktionalen Ablauf ohne Zustände realisiert. Die Ereignissteuerung (Eingang → Berechnung → Ausgang) ist strikt kausal.

## Anwendungsszenarien

- **Abweichungsüberwachung**: Prüfen, ob zwei Messwerte (z. B. Temperatur, Druck) voneinander abweichen.
- **Schwellwertverletzung**: Kombination mit anderen Bausteinen, um Ungleichheit als Teil einer Plausibilitätsprüfung zu nutzen.
- **Datenvalidierung**: Erkennen, ob zwei redundante Signale unterschiedliche Werte liefern (Vergleich von Kopien).
- **Ereignisgesteuerte Vergleiche**: Einbettung in Applikationen, die nur bei Änderung eines der Eingänge einen Vergleich benötigen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Vergleichsfunktion | Besonderheit |
|----------|---------------------|--------------|
| `AUI_EQ` | Gleichheit (equal) | Ergebnis `TRUE` bei gleichen Werten |
| `AUI_NE` | Ungleichheit (not equal) | Ergebnis `TRUE` bei unterschiedlichen Werten |
| `AUI_GT` | Größer (greater than) | Ergebnis `TRUE` wenn IN1 > IN2 |
| `AUI_LT` | Kleiner (less than) | Ergebnis `TRUE` wenn IN1 < IN2 |

Alle genannten Bausteine teilen sich die gleiche Adapter-Schnittstelle und lassen sich daher leicht austauschen oder kombinieren.

## Fazit

Der `AUI_NE` ist ein einfacher, aber zuverlässiger Funktionsblock für den Ungleich-Vergleich zweier Werte innerhalb einer adapterbasierten 4diac-Umgebung. Seine Stärken liegen in der sauberen Kapselung durch Adapter, der ereignisgesteuerten Ausführung und der hohen Wiederverwendbarkeit dank des zugrundeliegenden IEC-61131-3-Bausteins. Er eignet sich besonders für modulare, erweiterbare Automatisierungslösungen.