# AUI_D_FF_HYS


![AUI_D_FF_HYS](./AUI_D_FF_HYS.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein `AUI_D_FF_HYS` realisiert ein Daten-Latch (D-Flipflop) mit einer Hysteresefunktion. Er dient zum zuverlässigen Übernehmen eines analogen oder digitalen Werts, wobei kleine Schwankungen (Rauschen) durch ein einstellbares Hystereseband unterdrückt werden. Der Baustein ist für den Einsatz in der Automatisierungstechnik konzipiert und folgt der Norm IEC 61499-1 Annex A.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Kommentar                |
|----------|-------|--------------------------|
| INIT     | EInit | Setzt die Hysteresebreite |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Kommentar                |
|----------|-------|--------------------------|
| INITO    | EInit | Bestätigung der Initialisierung |

### **Daten-Eingänge**

| Daten        | Typ  | Kommentar                        |
|--------------|------|----------------------------------|
| HYSTERESIS   | UINT | Breite des Hysteresebandes       |

### **Daten-Ausgänge**

Keine dedizierten Datenausgänge; der latched Wert wird über den Adapter `Q` bereitgestellt.

### **Adapter**

| Name | Typ                                 | Richtung | Kommentar                |
|------|--------------------------------------|----------|--------------------------|
| I    | adapter::types::unidirectional::AUI  | Socket   | Wert zum Latchen         |
| Q    | adapter::types::unidirectional::AUI  | Plug     | Gelatchter Wert          |

Die Adapter `I` und `Q` vom Typ `AUI` (unidirektional) transportieren sowohl Daten (z.B. `D1`) als auch zugehörige Ereignisse (z.B. `E1`).

## Funktionsweise

Der Baustein enthält intern die Instanz `E_D_FF_ANY_HYS` (Typ `logiBUS::signalprocessing::hysteresis::E_D_FF_ANY_HYS`), die das eigentliche Latch mit Hysterese ausführt. Die Signalflüsse sind:

- Das Ereignis `I.E1` (vom Adapter `I`) wird direkt als Takt (`CLK`) an den inneren Baustein weitergegeben.
- Der Datenwert `I.D1` wird als `D`-Eingang an das interne Flipflop übergeben.
- Das Hystereseband wird über den Parameter `HYSTERESIS` gesetzt.
- Der Ausgang des internen Bausteins (`Q`) wird auf den Adapter `Q.D1` gelegt, das Ausgangsereignis (`EO`) auf `Q.E1`.
- Das Ereignis `INIT` wird sofort auf `INITO` durchgeschliffen (keine Verzögerung).

Die Hysterese bewirkt, dass der latched Wert nur dann auf den neuen Eingangswert springt, wenn sich dieser um mehr als die festgelegte Schwelle (`HYSTERESIS`) vom aktuell gespeicherten Wert unterscheidet. Dadurch werden Flankenrauschen und unstete Signalwechsel unterdrückt.

## Technische Besonderheiten

- Der Baustein ist ein reiner **Composite-Funktionsbaustein**, der die gesamte Logik an eine interne Instanz delegiert.
- Die Hysterese wird als vorzeichenloser Integer (`UINT`) übergeben.
- Die Adapter sind unidirektional ausgelegt – Daten und Ereignisse fließen nur in einer Richtung (Socket → Plug).
- Der Baustein enthält keine eigene Zustandsmaschine; der Zustand wird im inneren Flipflop gehalten.

## Zustandsübersicht

Da `AUI_D_FF_HYS` kein eigenes ECC (Execution Control Chart) besitzt, ergibt sich das Verhalten allein aus dem internen Baustein `E_D_FF_ANY_HYS`. Typischerweise besitzt ein D-Flipflop mit Hysterese zwei stabile Ausgangszustände, die durch den angelegten Takt und die Hysteresebedingung umgeschaltet werden. Eine detaillierte Zustandsbeschreibung ist der Dokumentation des internen Bausteins zu entnehmen.

## Anwendungsszenarien

- **Entprellung von Sensordaten**: Werte, die aus analogen oder digitalen Sensoren kommen, werden mit einer einstellbaren Hysterese stabilisiert.
- **Schwellwertschalter**: Der Baustein kann als Schmitt-Trigger verwendet werden, wenn ein Eingangswert nur oberhalb einer Ober- und unterhalb einer Unterschwelle (bestimmt durch Hysterese) seinen Ausgang wechselt.
- **Signalaufbereitung in der Prozessautomatisierung**: Rauschbehaftete Signale werden geglättet, bevor sie an nachfolgende Logikbausteine weitergegeben werden.

## Vergleich mit ähnlichen Bausteinen

- **E_D_FF**: Ein reines D-Flipflop ohne Hysterese. Es übernimmt den Eingangswert bei jeder Taktflanke, unabhängig von minimalen Schwankungen. `AUI_D_FF_HYS` bietet eine verbesserte Störsicherheit.
- **E_RS_BISTABLE**: Ein Set-Reset-Flipflop, das keine Hysterese besitzt und auf binäre Zustände beschränkt ist. `AUI_D_FF_HYS` arbeitet mit analogen/ganzzahligen Werten und ermöglicht eine dynamische Schwelle.
- **E_SPLIT_HYS**: Ein Baustein, der ein Signal mit einer festen Hysterese aufteilt. Im Gegensatz dazu kann die Hysterese in `AUI_D_FF_HYS` über den Eingang `HYSTERESIS` zur Laufzeit geändert werden.

## Fazit

Der `AUI_D_FF_HYS` ist ein nützlicher Baustein zur stabilen Latchung von Werten in Umgebungen mit Rauschen oder Signalinstabilitäten. Er vereint die Funktionalität eines D-Flipflops mit einer einstellbaren Hystereseschwelle und ist durch die Verwendung von Adaptern leicht in modulare IEC‑61499-Steuerungen integrierbar.