# AUDI_LE


![AUDI_LE](./AUDI_LE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUDI_LE** realisiert einen Vergleich zweier Werte auf „kleiner oder gleich“ (less or equal). Er ist als Composite-FB auf Basis des standardisierten Vergleichsbausteins `F_LE` aus der IEC-61131-Klassifikation aufgebaut. Die Kommunikation mit der Umgebung erfolgt ausschließlich über Adapter-Schnittstellen, sodass der Baustein modular in ereignisgesteuerte Abläufe eingebunden werden kann.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `IN1.E1`    | EVENT    | Ereignis-Eingang des Adapters IN1 – löst die Verarbeitung des ersten Wertes aus. |
| `IN2.E1`    | EVENT    | Ereignis-Eingang des Adapters IN2 – löst die Verarbeitung des zweiten Wertes aus. |

*Hinweis: Beide Ereignisse müssen eingehen, damit ein Vergleich stattfindet (logische UND-Verknüpfung im internen Netzwerk).*

### **Ereignis-Ausgänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `OUT.E1`    | EVENT    | Ereignis-Ausgang des Adapters OUT – wird aktiviert, sobald das Vergleichsergebnis bereitsteht. |

### **Daten-Eingänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `IN1.D1`    | ANY      | Erster zu vergleichender Wert (über Adapter IN1). |
| `IN2.D1`    | ANY      | Zweiter zu vergleichender Wert (über Adapter IN2). |

### **Daten-Ausgänge**

| Bezeichnung | Datentyp | Beschreibung |
|-------------|----------|--------------|
| `OUT.D1`    | BOOL     | Vergleichsergebnis: `TRUE`, wenn `IN1 ≤ IN2`; sonst `FALSE`. |

### **Adapter**

| Name | Typ | Richtung | Beschreibung |
|------|-----|----------|--------------|
| `IN1` | `adapter::types::unidirectional::AUDI` | Socket (Eingang) | Aufnahme des ersten Wertes (Ereignis + Daten). |
| `IN2` | `adapter::types::unidirectional::AUDI` | Socket (Eingang) | Aufnahme des zweiten Wertes (Ereignis + Daten). |
| `OUT` | `adapter::types::unidirectional::AX` | Plug (Ausgang) | Ausgabe des Vergleichsergebnisses (Ereignis + Daten). |

## Funktionsweise

1. Der FB erwartet an beiden Eingangsadaptern (`IN1` und `IN2`) je ein Ereignis und einen Datenwert.
2. Intern werden die beiden Ereignisse (über eine implizite UND-Bedingung im Netzwerk) zusammengeführt und der eingebettete Baustein `F_LE` mit den Datenwerten gestartet.
3. `F_LE` führt den Vergleich `IN1 ≤ IN2` durch und legt das Ergebnis (Boolescher Wert) an seinem Datenausgang an.
4. Sobald das Ergebnis vorliegt, wird das Ereignis am Ausgangsadapter `OUT` ausgelöst und der Ergebniswert über `OUT.D1` bereitgestellt.

## Technische Besonderheiten

- **Adapterbasierte Schnittstellen:** Der FB besitzt keine klassischen Einzel-Ports, sondern verwendet standardisierte unidirektionale Adapter. Dies erleichtert die Wiederverwendung und die Integration in komplexe Kommunikationsstrukturen.
- **Composite-Aufbau:** Die gesamte Logik wird über einen internen FB (`F_LE`) realisiert. Dadurch ist der Baustein leicht nachvollziehbar und erweiterbar.
- **Ereignissynchronisation:** Beide Eingangsereignisse müssen eintreffen, bevor die Verarbeitung startet. Dies gewährleistet, dass stets aktuelle Wertepaare verglichen werden.

## Zustandsübersicht

Der FB besitzt keinen eigenen gerichteten Zustandsautomaten, da er rein kombinatorisch arbeitet. Der interne `F_LE` ist ebenfalls zustandslos. Die einzige relevante Logik ist die UND-Verknüpfung der Ereignisse – nach Erhalt beider Ereignisse wird einmalig das Ergebnis ausgegeben.

## Anwendungsszenarien

- **Grenzwertüberwachung:** Prüfen, ob ein Messwert einen Schwellwert nicht überschreitet.
- **Freigabelogik:** Aktivieren einer Aktion nur dann, wenn die aktuelle Anforderung kleiner oder gleich einer maximalen Zulassung ist.
- **Vergleichsketten:** Kombination mehrerer `AUDI_LE`-Bausteine, um komplexe Bedingungen (z. B. `x ≤ y ≤ z`) zu realisieren.

## Vergleich mit ähnlichen Bausteinen

| FB | Funktion | Unterschied zu AUDI_LE |
|----|----------|------------------------|
| `AUDI_LT` | Kleiner als (`<`) | Nicht inklusive Gleichheit. |
| `AUDI_EQ` | Gleichheit (`=`) | Prüft nur auf exakte Übereinstimmung. |
| `AUDI_GE` | Größer oder gleich (`≥`) | Umgekehrte Vergleichsrichtung. |
| `AUDI_AND` | Logisches UND | Arbeitet mit Booleschen Werten, nicht mit numerischen Vergleichen. |

## Fazit

`AUDI_LE` ist ein spezialisierter Vergleichsbaustein, der dank seiner Adapter-Schnittstellen besonders gut in modulare, ereignisgesteuerte Automatisierungslösungen passt. Er bietet eine klare, standardisierte Logik für die „kleiner oder gleich“-Bedingung und lässt sich durch die Composite-Struktur leicht in eigene Applikationen einbinden.