# AUI_UDINT_AX_SEL


![AUI_UDINT_AX_SEL](./AUI_UDINT_AX_SEL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUI_UDINT_AX_SEL** führt eine binäre Auswahl („binary selection“) zwischen zwei Eingangswerten durch. Er ist als Komposition eines internen IEC‑61131‑Bausteins `F_SEL` und eines unidirektionalen Adapters `AX` realisiert. Der über den Adapter bereitgestellte Selektor entscheidet, welcher der beiden Daten-Eingänge an den Ausgang weitergegeben wird. Der FB eignet sich für einfache Umschaltlogiken, bei denen die Wahl zwischen zwei Signalen von einem externen (z. B. per Adapter eingekoppelten) Kriterium abhängt.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `EI0`    | Event    | Setzt den Wert von `IN0` und löst eine Auswahl aus. |
| `EI1`    | Event    | Setzt den Wert von `IN1` und löst eine Auswahl aus. |

### **Ereignis-Ausgänge**

| Ereignis | Datentyp | Kommentar |
|----------|----------|-----------|
| `CNF`    | Event    | Bestätigung der erfolgreichen Auswahl und Aktualisierung von `OUT`. |

### **Daten-Eingänge**

| Variable | Datentyp        | Kommentar |
|----------|-----------------|-----------|
| `IN0`    | `UINT`          | Auswählbarer Eingangswert (erste Alternative). |
| `IN1`    | `ANY_ELEMENTARY`| Auswählbarer Eingangswert (zweite Alternative). |

*Hinweis:* `IN1` ist als beliebiger elementarer Datentyp (`ANY_ELEMENTARY`) deklariert. Die tatsächliche Kompatibilität mit dem Ausgangstyp `UINT` hängt vom verwendeten Elementartyp ab (implizite oder explizite Konvertierung ist je nach Zielsystem erforderlich).

### **Daten-Ausgänge**

| Variable | Datentyp | Kommentar |
|----------|----------|-----------|
| `OUT`    | `UINT`   | Der ausgewählte Eingangswert (entweder `IN0` oder `IN1`). |

### **Adapter**

| Adapter | Typ                                     | Kommentar |
|---------|-----------------------------------------|-----------|
| `G`     | `adapter::types::unidirectional::AX`    | Liefert das Auswahlkriterium (z. B. ein Bool‑Signal oder einen numerischen Wert). |

## Funktionsweise
Der Baustein kapselt den IEC‑61131‑Funktionsblock `F_SEL` (binäre Auswahl). Die Auswahl erfolgt synchron zu den Ereignissen `EI0` oder `EI1`:

1. Wird eines der Ereignisse `EI0` oder `EI1` ausgelöst, so wird gleichzeitig der zugehörige Daten-Eingang aktualisiert und das Ereignis `REQ` des internen `F_SEL` ausgelöst.
2. Der interne `F_SEL` prüft das über den Adapter `G` bereitgestellte Signal `G.D1`:
   - Ist `G.D1 = 0` (bzw. logisch falsch), wird der Wert von `IN0` an `OUT` weitergegeben.
   - Ist `G.D1 ≠ 0` (bzw. logisch wahr), wird der Wert von `IN1` an `OUT` weitergegeben.
3. Nach Abschluss der Auswahl bestätigt `F_SEL` mit dem Ereignis `CNF`, welches als Ausgangsereignis des Gesamtbausteins weitergeleitet wird.

Der Adapter `G` wird als unidirektionaler Socket an die Applikation angebunden und liefert das Selektionssignal kontinuierlich.

## Technische Besonderheiten
- Der FB ist als **Komposition** realisiert (internes FBNetzwerk), daher kann das Verhalten nicht auf ECC‑Ebene angepasst werden.
- Der Typ des Eingangs `IN1` ist als `ANY_ELEMENTARY` deklariert – dies ermöglicht grundsätzlich die Verwendung verschiedener elementarer Datentypen, erfordert aber typsichere Verdrahtung auf Applikationsebene.
- Der Ausgang `OUT` ist fest als `UINT` deklariert. Sollte `IN1` einen anderen elementaren Typ besitzen, muss entweder eine implizite Konvertierung im Zielsystem erfolgen oder eine explizite Anpassung vorgenommen werden.
- Der Baustein erfordert einen angeschlossenen Adapter vom Typ `AX`. Fehlt dieser, ist der interne `F_SEL` nicht korrekt verdrahtet und das Verhalten undefiniert.

## Zustandsübersicht
Der FB besitzt keinen expliziten Zustandsautomaten. Sein Verhalten ist rein durch das interne `F_SEL` definiert:

- Warten auf ein Ereignis (`EI0` oder `EI1`).
- Bei Eintreffen eines Ereignisses: Einlesen der zugehörigen Daten und des Selektorsignals vom Adapter.
- Ausgabe des Signals über `CNF` und Aktualisierung von `OUT`.

Es gibt keine internen Zustände, die über die Reaktionszeit eines Ereignisses hinaus bestehen bleiben.

## Anwendungsszenarien
- **Umschaltung zwischen zwei Sensordaten** in der Landtechnik / Agrartechnik, abhängig von einem Betriebsmodus (z. B. Drehzahl vs. Drehmoment).
- **Signal-Redundanz**: Auswahl zwischen einem primären und einem Backup-Signal, gesteuert durch einen Fehlerstatus (z. B. über Adapter).
- **Parametrierbare Konstanten**: Ein Parameter (z. B. `IN0`) wird durch einen über den Adapter gewählten Wert (z. B. `IN1`) ersetzt.

## Vergleich mit ähnlichen Bausteinen
- **EtherNet/IP & PROFINET‑Bausteine**: Oft als Funktionsbaustein oder Baustein mit Zustandsautomaten realisiert. `AUI_UDINT_AX_SEL` ist dagegen komponentenbasiert und nutzt den standardisierten IEC‑61131‑FB `F_SEL`.
- **`SEL` (Standard‑IEC‑61499‑Baustein)**: Meist als ECC‑Variante verfügbar. Der hier beschriebene FB bietet durch den Adapter eine entkoppelte Einspeisung des Selektors, was die Wiederverwendung in unterschiedlichen Kontexten vereinfacht.
- **Eigene Auswahl‑Bausteine**: Können mehrere Kanäle oder andere Datentypen unterstützen. `AUI_UDINT_AX_SEL` ist auf zwei Eingänge und den Ausgangstyp `UINT` spezialisiert.

## Fazit
Der Funktionsblock `AUI_UDINT_AX_SEL` stellt eine einfache, adaptergesteuerte binäre Auswahl dar. Er eignet sich besonders für Anwendungen, bei denen ein Selektionssignal extern (z. B. über einen Sensor oder Busadapter) bereitgestellt wird. Dank der Kapselung des bewährten `F_SEL` aus IEC‑61131 ist das Auswahlverhalten deterministisch und zuverlässig. Einschränkungen hinsichtlich der Datentypkompatibilität von `IN1` sind bei der Verdrahtung zu beachten. Insgesamt ein nützlicher, klar strukturierter Basisbaustein für Umschaltlogiken in IEC‑61499‑Anwendungen.