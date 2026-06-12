# AUDI_UDINT_NE


![AUDI_UDINT_NE](./AUDI_UDINT_NE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUDI_UDINT_NE** realisiert einen Ungleich-Vergleich (not equal) zwischen einem über einen Adapter bereitgestellten Wert (Typ UDINT) und einem zweiten direkten Daten-Eingang. Er ist Bestandteil der IEC 61131-3 Vergleichsfunktionen und kapselt die Vergleichslogik in einer adressierbaren Komponente mit Ereignissteuerung. Der Baustein eignet sich besonders für den Einsatz in industriellen Steuerungssystemen, in denen Werte unterschiedlicher Quellen auf Ungleichheit geprüft werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Dient als Service Request zur Anforderung des Vergleichs. Mitverarbeitet wird der Daten-Eingang `IN2`. |

### **Ereignis-Ausgänge**

Es sind keine separaten Ereignis-Ausgänge vorhanden. Das Ergebnis des Vergleichs sowie die zugehörige Ausgangsbestätigung werden über den **Adapter-Ausgang `OUT`** bereitgestellt (Ereignis `E1` des Adapters).

### **Daten-Eingänge**

| Name | Typ   | Kommentar |
|------|-------|-----------|
| IN2  | UDINT | Zweiter Vergleichswert. |

### **Daten-Ausgänge**

Es sind keine direkten Daten-Ausgänge vorhanden. Das Vergleichsergebnis (Boolescher Wert) wird über den **Adapter-Ausgang `OUT`** (Datenpunkt `D1`) ausgegeben.

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| IN1  | `adapter::types::unidirectional::AUDI` | Socket (Eingang) | Liefert den ersten Vergleichswert als Typ UDINT sowie das Start-Ereignis für die Verarbeitung. |
| OUT  | `adapter::types::unidirectional::AX` | Plug (Ausgang) | Gibt das Ergebnis der Ungleich-Prüfung (Boolesch) und das Bestätigungs-Ereignis aus. |

## Funktionsweise

Der Funktionsblock vergleicht die beiden 32‑Bit‑Ganzzahlwerte (UDINT) auf Ungleichheit. Der erste Wert wird über den **Adapter-Eingang `IN1`** (Datenpunkt `D1`) bereitgestellt, der zweite über den **Daten-Eingang `IN2`**. Der Vergleich wird durch ein Ereignis an einem der beiden Eingänge angestoßen:

- Trifft das **Ereignis `REQ`** ein, wird `IN2` mit dem aktuellen Wert von `IN1.D1` verglichen.
- Trifft ein **Ereignis über den Adapter `IN1.E1`** ein, wird ebenfalls der Vergleich ausgelöst, wobei der über den Adapter übertragene Datenwert `IN1.D1` mit dem zuletzt an `IN2` anliegenden Wert verglichen wird.

Intern wird der Vergleich durch den eingebetteten Funktionsblock `F_NE` (Typ `iec61131::comparison::F_NE`) durchgeführt. Das Ergebnis (`true` bei Ungleichheit) wird über den **Adapter-Ausgang `OUT.D1`** ausgegeben und gleichzeitig das Ereignis `OUT.E1` gesendet.

## Technische Besonderheiten

- **Adapterbasierte Kommunikation:** Die Daten- und Ereignisverbindungen sind in standardisierten Adaptern (`AUDI`, `AX`) gekapselt. Dies vereinfacht die Wiederverwendung und den modularen Aufbau von Funktionsbaustein‑Netzwerken.
- **Doppelte Auslösemöglichkeit:** Der Vergleich kann sowohl über den direkten Ereignis-Eingang `REQ` als auch über das Ereignis des Adapter-Eingangs `IN1` gestartet werden. Dies ermöglicht flexible Steuerungsarchitekturen.
- **Paketorientierte Typisierung:** Der Baustein ist im Paket `iec61131::comparison` abgelegt und folgt der IEC 61131‑3‑Klassifikation für Vergleichsfunktionen.
- **Keine eigene Zustandslogik:** Die gesamte Vergleichslogik wird an den internen Funktionsblock `F_NE` delegiert; der Baustein selbst besitzt keinen eigenen ECloch‑Zustandsautomaten.

## Zustandsübersicht

Der Funktionsblock verfügt über **keine** explizite Zustandsmaschine. Die Verarbeitung erfolgt ereignisgesteuert:

1. Ereignis an `REQ` oder `IN1.E1` → intern wird `F_NE` aufgerufen.
2. Nach Abschluss des Vergleichs wird das Ereignis `OUT.E1` erzeugt und das Ergebnis an `OUT.D1` ausgegeben.

Zwischen den Ereignissen verhält sich der Baustein passiv und hält keine Zustandsinformationen vor.

## Anwendungsszenarien

- **Grenzwertüberwachung:** Prüfung, ob ein Messwert (über Adapter) von einem Sollwert abweicht.
- **Zustandsabfragen:** Feststellen, ob sich zwei Sensorwerte (z. B. Drehzahlen oder Zählerstände) unterscheiden.
- **Fehlererkennung:** Erkennen eines nicht erwarteten Eingangspegels durch Vergleich mit einem Referenzwert.
- **Modulare Steuerungslogik:** Einbindung in größere Funktionsbaustein‑Netzwerke, in denen Daten über Adapter ausgetauscht werden.

## Vergleich mit ähnlichen Bausteinen

- **`AUDI_UDINT_EQ` (Equal):** Führt einen Gleich-Vergleich durch. Logische Umkehrung des `NE`‑Bausteins.
- **`AUDI_INT_NE`, `AUDI_DINT_NE`:** Analoge Bausteine für die Datentypen `INT` bzw. `DINT`. Die Schnittstellenstruktur ist identisch, lediglich der Datenpfad ist an den jeweiligen Typ angepasst.
- **`F_NE` (direkter Vergleichsbaustein):** Bietet den selben Vergleich ohne Adapter‑Kapselung. Der `AUDI_UDINT_NE` fügt die Adapter‑Ein‑/Ausgänge hinzu und vereinfacht so die Verdrahtung in gerichteten Datenflüssen.

## Fazit

Der **AUDI_UDINT_NE** ist ein spezialisierter Vergleichsbaustein für die Ungleich-Prüfung von 32‑Bit‑Werten (UDINT) in einem adapterbasierten, ereignisgesteuerten Umfeld. Durch die Kapselung der Ereignis- und Datenpfade in standardisierten Adaptern wird die Integration in komplexe Automatisierungslösungen erleichtert. Der Baustein bietet eine saubere, funktionale Schnittstelle und ist aufgrund seiner Einfachheit und Klarheit ein verlässliches Werkzeug für Vergleiche in IEC 61131‑3‑Umgebungen.