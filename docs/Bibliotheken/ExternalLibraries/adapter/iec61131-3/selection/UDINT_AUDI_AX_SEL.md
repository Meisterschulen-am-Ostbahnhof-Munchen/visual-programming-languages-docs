# UDINT_AUDI_AX_SEL


![UDINT_AUDI_AX_SEL](./UDINT_AUDI_AX_SEL.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **UDINT_AUDI_AX_SEL** realisiert eine binäre Auswahl zwischen zwei Eingangswerten. Die Selektion erfolgt über einen Adapter (Typ `AX`), der ein externes Steuersignal bereitstellt. Je nach Zustand des Adapters wird entweder der Wert am Eingang `IN0` oder `IN1` an den Ausgang `OUT` weitergegeben.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis     | Kommentar                 | Mit Daten          |
|------------- |---------------------------|--------------------|
| `EI0`        | Set IN0                   | `IN0`              |
| `EI1`        | Set IN1                   | `IN1`              |

### **Ereignis-Ausgänge**

| Ereignis     | Kommentar                                 |
|------------- |-------------------------------------------|
| `CNF`        | Bestätigung der angeforderten Operation   |

### **Daten-Eingänge**

| Variable | Typ              | Kommentar                     |
|----------|------------------|-------------------------------|
| `IN0`    | `ANY_ELEMENTARY` | Erster auswählbarer Eingang   |
| `IN1`    | `UDINT`          | Zweiter auswählbarer Eingang  |

### **Daten-Ausgänge**

| Variable | Typ     | Kommentar                 |
|----------|---------|---------------------------|
| `OUT`    | `UDINT` | Ausgewählter Eingangswert |

### **Adapter**

| Adapter | Typ                                      | Kommentar          |
|---------|------------------------------------------|--------------------|
| `G`     | `adapter::types::unidirectional::AX`     | Selektionssteuerung |

Der Adapter `G` liefert das Ereignis `E1` und den Datenwert `D1`, der als Selektionssignal dient.
- Bei Zustand **0** des Selektionssignals wird `IN0` übernommen.
- Bei Zustand **1** (oder ungleich 0) wird `IN1` übernommen.

## Funktionsweise
Der Baustein besitzt zwei Eingangsereignisse `EI0` und `EI1`, die jeweils die Daten `IN0` bzw. `IN1` setzen – jedoch nicht direkt zur Auswahl führen. Die eigentliche Selektion wird durch ein externes Ereignis ausgelöst, das über den Adapter `G` an den internen Funktionsblock `F_SEL` (Typ `iec61131::selection::F_SEL`) übergeben wird.

Wenn der Adapter sein Ereignis `E1` sendet, wird der `F_SEL`-Baustein gesteuert. Die Auswahl erfolgt anhand des vom Adapter übermittelten Datenwerts `D1`:
- **D1 = 0** → Ausgang `OUT` erhält den Wert von `IN0`.
- **D1 ≠ 0** → Ausgang `OUT` erhält den Wert von `IN1`.

Anschließend wird das Ereignis `CNF` ausgegeben, um die erfolgreiche Verarbeitung zu bestätigen.

## Technische Besonderheiten
- Der Eingang `IN0` ist als `ANY_ELEMENTARY` deklariert, d. h. er kann Werte unterschiedlicher elementarer Typen annehmen. Der Ausgang `OUT` ist jedoch fest als `UDINT` definiert – eine implizite Typkonvertierung (z. B. von INT, DINT, REAL) findet bei der Übergabe an `F_SEL` statt.
- Der Baustein nutzt intern einen vordefinierten `F_SEL`-Funktionsblock (aus der IEC-61131-Bibliothek), der die eigentliche binäre Auswahl durchführt.
- Die Ereignisse `EI0` und `EI1` dienen lediglich der Aktualisierung der entsprechenden Datenwerte; die Auswahl wird erst durch das Adapter-Ereignis angestoßen.

## Zustandsübersicht
Der Funktionsblock besitzt keine explizite Zustandsmaschine. Die Verarbeitung erfolgt ereignisgesteuert:
1. **Empfang von `EI0` oder `EI1`** → Setzen des jeweiligen Datenwerts (kein Ausgangsereignis).
2. **Empfang des Adapter-Ereignisses `G.E1`** → Auswahl durchführen und `CNF` senden.

Die interne Logik ist rein kombinatorisch nach dem Trigger durch das Adapter-Ereignis.

## Anwendungsszenarien
- Umschaltung zwischen zwei Sensormesswerten (z. B. unterschiedlicher Messbereiche) in Abhängigkeit eines Betriebsmodus.
- Auswahl eines Parametersatzes (IN0 = Standardwert, IN1 = Ersatzwert) gesteuert durch eine externe Bedingung.
- Flexibles Routing von Signalen in einer Automatisierungsanwendung mit minimaler Konfiguration.

## Vergleich mit ähnlichen Bausteinen

| Baustein            | Eigenschaft                                                                 |
|---------------------|-----------------------------------------------------------------------------|
| `UDINT_AUDI_AX_SEL` | Binäre Auswahl, externes Selektionssignal über Adapter, zwei Eingänge + Konvertierung von ANY_ELEMENTARY zu UDINT. |
| `F_SEL`             | Reine IEC-61131 binäre Auswahl ohne Adapter (Steuersignal als dritter Eingang). |
| `MUX`               | Auswahl aus mehr als zwei Kanälen, i. d. R. mit Indexeingang.              |

Der vorliegende Baustein erweitert `F_SEL` um eine adapterbasierte Ansteuerung und eine flexiblere Typisierung des ersten Eingangs.

## Fazit
Der **UDINT_AUDI_AX_SEL** ist ein spezialisierter Auswahlbaustein für Anwendungen, bei denen das Selektionssignal über einen Adapter von außen bereitgestellt werden muss. Die Kombination aus einem universellen `ANY_ELEMENTARY`-Eingang und einem festen `UDINT`-Ausgang macht ihn vielseitig einsetzbar, erfordert jedoch eine korrekte Typverträglichkeit. Durch die Wiederverwendung des bewährten `F_SEL`-Blocks bleibt die Funktionslogik robust und vorhersagbar.