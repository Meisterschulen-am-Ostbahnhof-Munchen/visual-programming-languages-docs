# AUDI_UDINT_GE


![AUDI_UDINT_GE](./AUDI_UDINT_GE.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AUDI_UDINT_GE** führt einen größer-oder-gleich-Vergleich (≥) zwischen zwei Werten des Typs UDINT durch. Er kapselt die Vergleichslogik in einer adapterbasierten Schnittstelle, die eine typsichere und ereignisgesteuerte Kommunikation mit der Umgebung ermöglicht.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ   | Kommentar        |
|------|-------|------------------|
| REQ  | Event | Service Request  |

### **Ereignis-Ausgänge**

Keine direkten Ereignisausgänge. Das Ergebnis wird über den Ausgangsadapter `OUT` als Ereignis signalisiert.

### **Daten-Eingänge**

| Name | Typ    | Kommentar        |
|------|--------|------------------|
| IN2  | UDINT  | Eingabewert 2    |

### **Daten-Ausgänge**

Keine direkten Datenausgänge. Der Ergebniswert (BOOL) wird über den Ausgangsadapter `OUT` bereitgestellt.

### **Adapter**

| Name | Typ           | Richtung       | Kommentar                        |
|------|---------------|----------------|----------------------------------|
| IN1  | AUDI (Socket) | Eingang        | Eingabewert 1 (über D1 und E1)   |
| OUT  | AX   (Plug)   | Ausgang        | Ergebnis: Wert 1 ≥ Wert 2 (D1), Ereignis (E1) |

## Funktionsweise

Der Baustein arbeitet ereignisgesteuert. Ein Vergleich wird ausgelöst durch:
- ein Ereignis am Eingang `REQ` oder
- ein Ereignis am Adaptereingang `IN1.E1`.

Intern wird der Standard-Funktionsblock `F_GE` (IEC 61131‑3) für den Datentyp UDINT verwendet. Die Eingabedaten stammen von:
- `IN1.D1` → erster Operand,
- `IN2` → zweiter Operand.

Der Vergleich `IN1.D1 ≥ IN2` liefert ein BOOL-Ergebnis, das über den Ausgangsadapter `OUT` als Datenwert `OUT.D1` ausgegeben wird. Gleichzeitig wird ein Ereignis auf `OUT.E1` erzeugt, das die Verfügbarkeit des Ergebnisses signalisiert.

## Technische Besonderheiten

- **Adapterbasierte Schnittstelle:** Anstelle von direkten Ein-/Ausgängen werden Adapter (`AUDI`, `AX`) verwendet. Dies ermöglicht eine modulare und typsichere Verkabelung in größeren Netzwerken.
- **Wiederverwendung von Standardbausteinen:** Der interne Vergleich wird durch einen zertifizierten IEC‑61131‑3‑Baustein (`F_GE`) realisiert, was Korrektheit und Portabilität sicherstellt.
- **Kein interner Zustand:** Die Funktion ist rein kombinatorisch; nach jedem Ereignis wird das Ergebnis sofort neu berechnet.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Er verhält sich wie ein reiner Funktionsblock ohne Gedächtnis. Jedes Eingangsereignis führt zur sofortigen Auswertung und Ausgabe.

## Anwendungsszenarien

- **Schwellwertüberwachung:** Prüfen, ob ein Messwert (über `IN1`) einen eingestellten Grenzwert (`IN2`) erreicht oder überschreitet.
- **Freigabelogik:** Auslösen einer Aktion, wenn eine Zählvariable (z. B. Stückzahl) mindestens einen Sollwert erreicht.
- **Sequenzsteuerungen:** Verknüpfung von Zeit- oder Zählwerten mit Vergleichsbedingungen in einer Adapter-basierten Steuerungsarchitektur.

## Vergleich mit ähnlichen Bausteinen

- **`AUDI_UDINT_GT`**: Führt einen „größer als“-Vergleich (>) durch, bei Gleichheit liefert er `FALSE`.
- **`AUDI_UDINT_EQ`**: Prüft auf Gleichheit (=).
- **`F_GE` (direkt)**: Bietet die gleiche Logik, jedoch ohne Adapter-Schnittstelle. Der `AUDI_UDINT_GE` erleichtert die Einbindung in adapterbasierte Komponentenmodelle.

## Fazit

Der Funktionsblock `AUDI_UDINT_GE` ist ein spezialisierter Vergleichsbaustein für UDINT-Werte, der die Vorteile der Adaptertechnik mit bewährter IEC‑61131‑3‑Logik kombiniert. Er eignet sich besonders für modulare, ereignisgesteuerte Steuerungsanwendungen, in denen typsichere und flexible Schnittstellen gefordert sind.