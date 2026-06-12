# UDINT_AUDI_LE


![UDINT_AUDI_LE](./UDINT_AUDI_LE.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **UDINT_AUDI_LE** führt einen Vergleich zweier Werte durch und prüft, ob der erste Wert (IN1) kleiner oder gleich dem zweiten Wert (IN2) ist. Der zweite Wert wird über einen Adapter-Socket (Typ `AUDI`) bereitgestellt, während das Ergebnis (wahr/falsch) über einen Adapter-Plug (Typ `AX`) ausgegeben wird. Der Baustein ist speziell für die Verarbeitung von unsigned double integer (UDINT) – bzw. allgemein elementaren Datentypen – ausgelegt und eignet sich für den Einsatz in IEC 61131-3-Umgebungen.

* * * * * * * * * *
## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Service-Anfrage: Löst den Vergleich aus, sobald das Ereignis eintrifft. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `OUT.E1` | Bestätigung: Wird gesendet, sobald der Vergleich abgeschlossen ist und das Ergebnis am Datenausgang `OUT.D1` anliegt. |

### **Daten-Eingänge**

| Variable | Typ               | Beschreibung |
|----------|-------------------|--------------|
| `IN1`    | `ANY_ELEMENTARY`  | Erster Vergleichswert (standardmäßig z. B. UDINT). |

### **Daten-Ausgänge**

Der Baustein besitzt keine direkten Datenausgänge. Das Vergleichsergebnis wird über den Adapter-Plug `OUT` ausgegeben (siehe unten).

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | `IN2` | `adapter::types::unidirectional::AUDI` | Liefert den zweiten Vergleichswert (z. B. über einen Sensor oder einen anderen FB). |
| Plug (Ausgang)   | `OUT` | `adapter::types::unidirectional::AX`   | Gibt das Boolesche Ergebnis `True` aus, wenn `IN1 <= IN2` gilt. |

* * * * * * * * * *
## Funktionsweise

Der FB arbeitet ereignisgesteuert. Ein Vergleich wird ausgelöst durch:

- das externe Ereignis `REQ` oder
- ein eingehendes Ereignis vom Adapter-Socket `IN2` (über dessen Ereignisausgang).

Beide Ereignisse werden auf den internen Funktionsblock `F_LE` (less or equal) geführt. Diesem werden die Datenwerte übergeben:

- `IN1` wird auf den ersten Eingang des `F_LE` gelegt.
- Der Wert vom Adapter `IN2` (über dessen Datenausgang `IN2.D1`) wird auf den zweiten Eingang des `F_LE` gelegt.

Der interne Baustein `F_LE` führt den Vergleich durch und gibt das Ergebnis (`TRUE` oder `FALSE`) über seinen Ausgang `OUT` an den Adapter-Plug `OUT` weiter. Nach Abschluss wird das Ereignis `OUT.E1` ausgelöst.

Die Verwendung der Adapter ermöglicht eine modulare Anbindung: Der Socket `IN2` erwartet eine Datenquelle (z. B. einen analogen Eingang), der Plug `OUT` liefert das Ergebnis an nachfolgende Logik oder Aktoren.

* * * * * * * * * *
## Technische Besonderheiten

- **Datentyp:** Der Eingang `IN1` ist als `ANY_ELEMENTARY` deklariert, sodass der FB prinzipiell für alle elementaren Datentypen (z. B. INT, UDINT, REAL) geeignet ist – in der Benennung liegt der Schwerpunkt jedoch auf UDINT.
- **Adapter:** Die Kommunikation mit der Außenwelt erfolgt über standardisierte unidirektionale Adapter (`AUDI` und `AX`). Dies ermöglicht eine lose Kopplung und Wiederverwendbarkeit in unterschiedlichen Netzwerken.
- **Interne Implementierung:** Der Vergleich wird durch den eingebetteten Basisbaustein `F_LE` realisiert, der eine typische IEC‑61131‑3-Funktion darstellt.
- **Parallelauslösung:** Sowohl das externe Ereignis `REQ` als auch das Ereignis vom Socket `IN2` können den Vergleich starten; die Verarbeitung erfolgt deterministisch.
- **Copyright:** Der Baustein unterliegt der Eclipse Public License 2.0 und wurde ursprünglich an der TU Wien entwickelt.

* * * * * * * * * *
## Zustandsübersicht

Der FB besitzt keinen expliziten Zustandsautomaten. Er verhält sich wie eine reine Funktion: Auf jedes anliegende Ereignis (von `REQ` oder vom Socket) wird der Vergleich ausgeführt und anschließend das Bestätigungsereignis am Plug ausgegeben. Zwischen den Ereignissen bleibt der interne Zustand erhalten (z. B. Speicherung der letzten Werte ist nicht vorgesehen).

* * * * * * * * * *
## Anwendungsszenarien

- **Grenzwertüberwachung:** Vergleich eines Messwerts (z. B. Drehzahl, Druck) mit einem über einen Adapter vorgegebenen Schwellwert.  
- **Bereichsprüfung:** Kombination mit anderen Vergleichsbausteinen (z. B. `UDINT_AUDI_GE`) zur Überprüfung eines Wertebereichs.  
- **Steuerungslogik:** Auslösen einer Aktion, wenn eine Größe einen maximalen Wert nicht überschreitet.  
- **Datenaustausch in modularen Systemen:** Nutzung der Adapter‑Schnittstelle zur einfachen Kopplung mit Sensoren, Aktoren oder anderen Steuerungsbausteinen.

* * * * * * * * * *
## Vergleich mit ähnlichen Bausteinen

| Baustein         | Vergleichsoperation           | Adapter-Typen              |
|------------------|-------------------------------|----------------------------|
| `UDINT_AUDI_LE`  | Kleiner oder gleich (≤)       | Socket: AUDI – Plug: AX    |
| `UDINT_AUDI_LT`  | Kleiner (<)                   | identisch                  |
| `UDINT_AUDI_EQ`  | Gleich (=)                    | identisch                  |
| `UDINT_AUDI_GT`  | Größer (>)                    | identisch                  |
| `UDINT_AUDI_GE`  | Größer oder gleich (≥)        | identisch                  |

Die Bausteine unterscheiden sich lediglich in der Vergleichsoperation, sodass sie strukturell austauschbar sind. Die Adapter-Schnittstelle bleibt gleich, was eine einfache Parametrierung des Vergleichstyps ermöglicht.

* * * * * * * * * *
## Fazit

Der Funktionsblock `UDINT_AUDI_LE` realisiert eine IEC‑61131‑3‑konforme Kleiner‑oder‑gleich‑Vergleichsfunktion mit variabler Datenquelle über Adapter. Durch die Verwendung von unidirektionalen Adaptern und einem internen Basisbaustein ist er flexibel, erweiterbar und für den industriellen Einsatz in modularen Steuerungssystemen bestens geeignet. Die Unterstützung von `ANY_ELEMENTARY` erlaubt zudem den Einsatz mit verschiedenen Datentypen ohne Anpassung der Schnittstelle.