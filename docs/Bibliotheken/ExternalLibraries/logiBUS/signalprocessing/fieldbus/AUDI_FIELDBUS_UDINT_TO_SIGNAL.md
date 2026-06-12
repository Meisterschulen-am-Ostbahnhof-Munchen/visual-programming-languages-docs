# AUDI_FIELDBUS_UDINT_TO_SIGNAL


![AUDI_FIELDBUS_UDINT_TO_SIGNAL](./AUDI_FIELDBUS_UDINT_TO_SIGNAL.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUDI_FIELDBUS_UDINT_TO_SIGNAL` spiegelt einen eingehenden `UDINT`-Wert (über den `IN`-Adapter) auf den `OUT`-Adapter, sofern das anliegende Signal als gültig erkannt wurde. Zusätzlich wird das Gültigkeitssignal über den `VALID`-Adapter ausgegeben. Der Baustein dient als Filter, der nur valide Datenpakete durchlässt und deren Status synchronisiert bereitstellt.

## Schnittstellenstruktur

Der Baustein besitzt keine direkten Ein-/Ausgangs-Ereignisse oder Daten, sondern arbeitet ausschließlich über **Adapter**, die sowohl Ereignisse als auch Daten transportieren.

### **Ereignis-Eingänge**

- **`IN.E1`** (über den `IN`-Adapter) – Startet die Verarbeitung des eingehenden Signals.

### **Ereignis-Ausgänge**

- **`OUT.E1`** (über den `OUT`-Adapter) – Wird ausgelöst, nachdem der `IN`-Wert aufbereitet und an `OUT.D1` weitergegeben wurde.
- **`VALID.E1`** (über den `VALID`-Adapter) – Wird ausgelöst, sobald die Gültigkeit des Signals aktualisiert wurde (siehe Funktionsweise).

### **Daten-Eingänge**

- **`IN.D1`** (über den `IN`-Adapter) – Der eingehende `UDINT`-Wert (z. B. aus einem Feldbus).

### **Daten-Ausgänge**

- **`OUT.D1`** (über den `OUT`-Adapter) – Der gefilterte `UDINT`-Wert (identisch mit `IN.D1`, wenn gültig).
- **`VALID.D1`** (über den `VALID`-Adapter) – Boolescher Wert, der `TRUE` signalisiert, sofern das anliegende Signal gültig ist.

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `IN` | `adapter::types::unidirectional::AUDI` | Socket | Signal-Eingang (liest Daten und Ereignisse) |
| `OUT` | `adapter::types::unidirectional::AUDI` | Plug | Gefilterter Signal-Ausgang |
| `VALID` | `adapter::types::unidirectional::AX` | Plug | Gültigkeitsanzeige (Ausgang für Bool & Ereignis) |

## Funktionsweise

Der Baustein enthält zwei interne Funktionsblöcke:

1. **`FIELDBUS_UDINT_TO_SIGNAL`** – Wandelt den eingehenden `UDINT`-Wert in ein Signal um und bestimmt dessen Gültigkeit.
2. **`E_D_FF`** – Ein flankengesteuertes D‑Flipflop, das das Gültigkeitssignal synchronisiert.

Der Ablauf:
- Ein Ereignis auf `IN.E1` triggert den Verarbeitungsblock `FIELDBUS_UDINT_TO_SIGNAL` (Eingang `REQ`).
- Dieser block liest `IN.D1` und gibt nach Abschluss auf `CNF` ein Ereignis aus.
- Das Ereignis `CNF` wird an drei Stellen weitergeleitet:
  - An `OUT.E1` → der Ausgangswert (`FIELDBUS_UDINT_TO_SIGNAL.OUT`) wird an `OUT.D1` gegeben.
  - An den Takteingang `CLK` des Flipflops (`E_D_FF`).
- Gleichzeitig wird der Gültigkeitsstatus (`FIELDBUS_UDINT_TO_SIGNAL.VALID`) auf den Dateneingang `D` des Flipflops gelegt.
- Mit der steigenden Flanke von `CLK` übernimmt das Flipflop den Wert von `D` nach `Q` und gibt auf `EO` ein Ereignis aus.
- Der Flipflop-Ausgang `Q` speist `VALID.D1`, und das Ereignis `EO` löst `VALID.E1` aus.

Somit wird das Gültigkeitssignal erst nach Abschluss der Signalverarbeitung aktualisiert und ausgegeben.

## Technische Besonderheiten

- **Synchronisation der Gültigkeit:** Durch das D‑Flipflop wird sichergestellt, dass der Gültigkeitstatus erst im nächsten Takt nach der Datenverarbeitung zur Verfügung steht – dies vermeidet inkonsistente Zustände.
- **Adapterbasierte Schnittstelle:** Alle Daten und Ereignisse werden über standardisierte unidirektionale Adapter ausgetauscht, was die Wiederverwendung in hierarchischen Projekten erleichtert.
- **Lizenzhinweis:** Der Baustein unterliegt der **Eclipse Public License 2.0** und enthält einen Copyright‑Vermerk (HR Agrartechnik GmbH).

## Zustandsübersicht

Der FB besitzt keinen eigenen Zustandsautomaten; das Verhalten wird durch das interne D‑Flipflop bestimmt. Dieses kennt zwei Zustände:

| Zustand | Q (Ausgang) | Bedeutung |
|---------|-------------|-----------|
| 0 | `FALSE` | Signal derzeit ungültig |
| 1 | `TRUE`  | Signal gültig |

Der Zustandswechsel erfolgt bei jeder steigenden Taktflanke (`CLK`) auf den aktuellen Wert von `D`. Ein Zurücksetzen (Reset) ist nicht vorgesehen – bei ungültigem Signal bleibt Q auf dem letzten bekannten gültigen Wert, bis ein neuer Takt mit `D = FALSE` eintrifft.

## Anwendungsszenarien

- **Feldbus‑Signalaufbereitung:** Ein Sensor liefert über einen Feldbus (z. B. CANopen, PROFIBUS) einen `UDINT`‑Wert samt Gültigkeitsflag. Der Baustein filtert ungültige Werte aus und stellt nur valide Daten der Steuerung zur Verfügung.
- **Datenvalidierung in sicherheitskritischen Umgebungen:** Wenn eine übergeordnete Anwendung nur verarbeitete, gültige Messwerte erhalten soll, kann dieser Baustein zwischen Bus und Logik geschaltet werden.
- **Synchronisation mehrerer paralleler Signale:** Das separate Gültigkeitssignal kann genutzt werden, um nachgeschaltete Bausteine zu takten oder Alarme auszulösen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Merkmal |
|----------|---------|
| `FIELDBUS_UDINT_TO_SIGNAL` allein | Gibt das Signal sofort ungültig weiter – ohne Synchronisation der Gültigkeit. |
| `AUDI_FIELDBUS_UDINT_TO_SIGNAL` (dieser FB) | **Zusätzliche Synchronisation** des Gültigkeitssignals über ein D‑Flipflop, sodass `VALID` erst mit dem nächsten Takt aktualisiert wird. |
| Andere Validierungs‑Bausteine | Oft ohne dynamische Synchronisation; dieser Baustein eignet sich besonders für zyklische Bus‑Systeme, bei denen Daten und Gültigkeit zeitlich versetzt ankommen können. |

## Fazit

`AUDI_FIELDBUS_UDINT_TO_SIGNAL` ist ein spezialisierter Filterbaustein für Feldbus‑Signale, der eingehende `UDINT`‑Werte nur bei Gültigkeit an den Ausgang weiterleitet und den Status über einen synchronisierten Pfad ausgibt. Die Verwendung eines internen Flipflops vermeidet inkonsistente Zustände und eignet sich ideal für den Einsatz in zeitkritischen Automatisierungsumgebungen. Durch die adapterbasierte Schnittstelle ist er leicht in größere 4diac‑Projekte integrierbar.