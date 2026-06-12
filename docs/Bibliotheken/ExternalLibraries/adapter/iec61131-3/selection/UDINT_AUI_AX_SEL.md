# UDINT_AUI_AX_SEL


![UDINT_AUI_AX_SEL](./UDINT_AUI_AX_SEL.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **UDINT_AUI_AX_SEL** realisiert eine binäre Auswahl zwischen zwei Eingangswerten. Die Auswahl wird über einen Adapter vom Typ `AX` gesteuert, der typischerweise eine Achsenposition oder einen digitalen Zustand liefert. Der Baustein dient zur flexiblen Umschaltung von Signalquellen in Automatisierungslösungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| `EI0` | Setzt den Wert von `IN0` |
| `EI1` | Setzt den Wert von `IN1` |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| `CNF` | Bestätigung des abgeschlossenen Auswahlvorgangs |

### **Daten-Eingänge**

| Variable | Typ | Kommentar |
|----------|-----|-----------|
| `IN0` | ANY_ELEMENTARY | Erster auswählbarer Eingangswert |
| `IN1` | UINT | Zweiter auswählbarer Eingangswert (fester Typ) |

### **Daten-Ausgänge**

| Variable | Typ | Kommentar |
|----------|-----|-----------|
| `OUT` | UINT | Ausgewählter Wert (entspricht `IN0` oder `IN1`) |

### **Adapter**

| Adapter | Typ | Kommentar |
|---------|-----|-----------|
| `G` | `adapter::types::unidirectional::AX` | Liefert das binäre Auswahlsignal (0/1) |

## Funktionsweise

Der FB arbeitet ereignisgesteuert:

1. Bei einem Ereignis an `EI0` wird der aktuelle Wert von `IN0` intern übernommen.
2. Bei einem Ereignis an `EI1` wird der aktuelle Wert von `IN1` intern übernommen.
3. Über den Adapter `G` wird permanent das Auswahlsignal `G.D1` bezogen. Wenn `G.D1 = FALSE`, wird der Wert von `IN0` an den Ausgang `OUT` weitergeleitet; bei `G.D1 = TRUE` wird der Wert von `IN1` ausgegeben.
4. Nach erfolgreicher internen Verarbeitung wird ein Ereignis am Ausgang `CNF` gesendet, um die Auswahl zu bestätigen.

Die eigentliche Auswahllogik wird durch einen internen `F_SEL`-Baustein (IEC 61131) realisiert, der die beiden zwischengespeicherten Werte anhand des Auswahlsignals `G.D1` steuert.

## Technische Besonderheiten

- **Flexibler Eingang `IN0`**: Der erste Eingang ist als `ANY_ELEMENTARY` deklariert, sodass er verschiedene elementare Datentypen akzeptieren kann. Der zweite Eingang und der Ausgang sind auf `UINT` festgelegt – eine Typanpassung muss außerhalb erfolgen.
- **Adapterbasierte Ansteuerung**: Die Auswahl erfolgt nicht über einen direkten boolschen Eingang, sondern über den Adapter `AX`. Dies ermöglicht eine lose Kopplung an physikalische oder logische Achsensignale.
- **Ereignisgesteuerte Aktualisierung**: Die Werte von `IN0` und `IN1` werden nur durch explizite Ereignisse übernommen, nicht zyklisch. Dadurch wird die Auswahl deterministisch gesteuert.
- **Interne Verwendung von `F_SEL`**: Der Baustein nutzt den bewährten IEC‑61131‑Baustein `selection::F_SEL` für die Kernlogik.

## Zustandsübersicht

Der Funktionsblock besitzt keinen expliziten Zustandsautomaten. Die Ablaufsteuerung erfolgt rein ereignisorientiert über die Event-Eingänge und den internen `F_SEL`. Die Werte der Eingänge werden bei den entsprechenden Events gelatcht und dann kontinuierlich gemäß dem Auswahlsignal durchgeschaltet.

## Anwendungsszenarien

- **Achsenabhängige Signalauswahl**: In einer Werkzeugmaschine kann über die Achsposition (bereitgestellt durch den `AX`-Adapter) zwischen zwei Messsignalquellen umgeschaltet werden.
- **Redundante Sensorauswahl**: Bei zwei Sensoren, die unterschiedliche Werte liefern (z. B. ein analoger und ein digitaler), wählt der FB den aktiven Wert basierend auf einem Betriebsmodus-Signal.
- **Parametrierbare Betriebsarten**: Ein Adapter liefert einen Schaltbefehl (0/1) und ermöglicht so die Auswahl zwischen zwei vordefinierten Sollwerten.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu einem einfachen IEC‑61131‑`SEL`-Baustein, der direkt einen boolschen Eingang `G` besitzt, kapselt `UDINT_AUI_AX_SEL` die Auswahl hinter einem Adapter. Dadurch wird die Logik von der Signalquelle entkoppelt und die Wiederverwendbarkeit erhöht. Der Baustein bietet zudem eine explizite Ereignissteuerung für die Übernahme der Eingangswerte, während ein Standard‑`SEL` die Werte üblicherweise zyklisch abtastet.

## Fazit

Der Funktionsblock **UDINT_AUI_AX_SEL** ist ein flexibler binärer Selektor, der sich durch seine adapterbasierte Steuerung und ereignisgesteuerte Aktualisierung auszeichnet. Er eignet sich besonders für Anwendungen, in denen die Auswahl von Signalquellen von einer externen Achsen- oder Zustandsinformation abhängt und eine deterministische, nicht‑zyklische Verarbeitung erforderlich ist.