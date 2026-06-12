# ILOCK_T_FF_AX


![ILOCK_T_FF_AX](./ILOCK_T_FF_AX.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock `ILOCK_T_FF_AX` ist ein zusammengesetzter (Composite) Baustein, der einen verriegelbaren Toggle-Flip-Flop (engl. lockable toggle flip-flop) realisiert. Er verfügt über eine AE2-Adapter-Schnittstelle zur Anbindung an eine übergeordnete Verriegelungslogik und gibt den aktuellen Schaltzustand über einen unidirektionalen AX-Adapter aus. Der Baustein ist für den Einsatz in sicherheitsgerichteten oder verriegelten Steuerungsanwendungen konzipiert, bei denen das Umschalten eines Ausgangs durch externe Bedingungen beeinflusst werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ    | Beschreibung                                  |
|----------|--------|-----------------------------------------------|
| `CLK`    | Event  | Taktsignal, das einen Zustandswechsel (Toggle) auslöst. |

### **Ereignis-Ausgänge**

Der Baustein besitzt keine eigenen Ereignisausgänge. Ereignisse werden über die Adapter-Schnittstellen weitergegeben.

### **Daten-Eingänge**

Keine direkten Dateneingänge.

### **Daten-Ausgänge**

Keine direkten Datenausgänge. Der aktuelle Zustand wird über den AX-Adapter bereitgestellt.

### **Adapter**

| Adapter      | Typ                                                 | Richtung     | Beschreibung                                                                 |
|--------------|------------------------------------------------------|--------------|-------------------------------------------------------------------------------|
| `Q`          | `adapter::types::unidirectional::AX`                | Plug/Output  | Unidirektionaler Ausgangsadapter, der den aktuellen Zustand (boolescher Wert) als Datum liefert und ein Ereignis bei Zustandsänderung ausgibt. |
| `ILOCK_IN`   | `adapter::types::bidirectional::AE2`                | Socket       | Bidirektionaler Adapter (Eingang) zur Aufnahme von Verriegelungssignalen.     |
| `ILOCK_OUT`  | `adapter::types::bidirectional::AE2`                | Plug         | Bidirektionaler Adapter (Ausgang) zur Weitergabe von Verriegelungsereignissen an die übergeordnete Logik. |

Die AE2-Adapter besitzen je zwei Ereignispaare (`EI1/EO1`, `EI2/EO2`) und zwei zugehörige Datenports. In diesem Baustein werden nur die ersten Ports (`EI1/EO1`) genutzt.

## Funktionsweise

Der interne Aufbau besteht aus zwei IEC 61499-Standardbausteinen: `E_SR` (Set-Reset-Flip-Flop) und `E_SWITCH` (Ereignisweiche). Das Toggle-Verhalten wird wie folgt realisiert:

1. Ein ankommendes `CLK`-Ereignis wird der Ereignisweiche `E_SWITCH` zugeführt.
2. Der Schalteingang `G` der Weiche ist mit dem Ausgang `Q` des SR-Flip-Flops verbunden.
   - Ist `G = false`, wird das Ereignis an den Ausgang `EO0` (Set-Pfad) weitergeleitet.
   - Ist `G = true`, wird das Ereignis an den Ausgang `EO1` (Reset-Pfad) weitergeleitet.
3. Der Set-Pfad (`EO0`) setzt den SR-Flip-Flop (`E_SR.S`) und erzeugt gleichzeitig ein Ereignis auf `ILOCK_OUT.EO1` sowie `ILOCK_IN.EI1`, um die Verriegelung über die Adapter zu informieren.
4. Der Reset-Pfad (`EO1`) setzt den SR-Flip-Flop zurück (`E_SR.R`). Dieser Reset kann auch extern über `ILOCK_IN.EO1` oder `ILOCK_OUT.EI1` ausgelöst werden, wodurch ein **verriegelter Reset** möglich ist.
5. Der Ausgang des SR-Flip-Flops (`E_SR.Q`) wird auf den AX-Adapter `Q.D1` geschrieben und bei jedem Zustandswechsel wird das Ereignis `Q.E1` ausgelöst.
6. Zusätzlich werden Ereignisse zwischen `ILOCK_IN` und `ILOCK_OUT` in beide Richtungen durchgeschleift, um eine Kommunikation mit benachbarten Bausteinen im selben Verriegelungsverbund zu ermöglichen.

Der Baustein realisiert somit einen flankengetriggerten Toggle-Flip-Flop, der durch externe Verriegelungssignale (über die AE2-Adapter) zurückgesetzt werden kann.

## Technische Besonderheiten

- **Composite-Implementierung:** Der Baustein ist als Netzwerk aus Standard-FBs (`E_SR` und `E_SWITCH`) aufgebaut und kann daher leicht angepasst oder in andere Projekte eingebunden werden.
- **Bidirektionale Verriegelungsschnittstelle:** Die AE2-Adapter erlauben sowohl den Empfang als auch die Weitergabe von Verriegelungsereignissen, was eine modulare Kaskadierung mehrerer Bausteine ermöglicht.
- **Unidirektionaler AX-Ausgang:** Der Zustand wird als sauberes boolesches Signal mit Ereignisbereitstellung ausgegeben; kein zusätzlicher Datenkonvertierungsaufwand auf der Empfängerseite.
- **Verwendung nur der ersten AE2-Ports:** Die zweiten Ports der AE2-Adapter bleiben ungenutzt und können bei Bedarf in einer abgeleiteten Variante ergänzt werden.

## Zustandsübersicht

Der interne Zustand des Flip-Flops ist binär:

| Zustand | Beschreibung                                                        |
|---------|----------------------------------------------------------------------|
| `0` (false) | Ausgang `Q` ist inaktiv. Bei nächstem `CLK` wird der Baustein setzen. |
| `1` (true)  | Ausgang `Q` ist aktiv. Bei nächstem `CLK` wird der Baustein zurücksetzen. |

Die Zustandsübergänge erfolgen ausschließlich bei einem `CLK`-Ereignis (Toggle) oder bei einem Verriegelungs-Reset über `ILOCK_IN.EO1` bzw. `ILOCK_OUT.EI1`. Ein gleichzeitiges Setzen und Rücksetzen wird durch die Logik des SR-Flip-Flops aufgelöst (Reset hat Priorität, sofern beide Ereignisse eintreffen).

## Anwendungsszenarien

- **Verriegelte Ausgangssteuerung:** In Maschinensteuerungen, bei denen ein Ausgang nur unter bestimmten Sicherheitsbedingungen umgeschaltet werden darf. Die Verriegelungssignale (z. B. von Not-Aus-Kreisen oder Lichtgittern) werden über `ILOCK_IN` eingelesen und unterdrücken den Toggle.
- **Kaskadierte Verriegelungsketten:** Mehrere `ILOCK_T_FF_AX`-Bausteine können über die AE2-Adapter miteinander verbunden werden, um eine abgestufte Verriegelungshierarchie aufzubauen.
- **Taktsynchrone Schaltzustandsverwaltung:** Der Baustein eignet sich für Anwendungen, die einen getakteten Zustandswechsel benötigen, z. B. in Schrittketten oder sequentiellen Ablaufsteuerungen.

## Vergleich mit ähnlichen Bausteinen

- **Standard Toggle-FF (z. B. eigener IEC‑61499-Baustein `E_TOGGLE`):** Ein einfacher Toggle-Flip-Flop hat keine externe Verriegelungsschnittstelle und kann nicht durch externe Bedingungen zurückgesetzt werden. `ILOCK_T_FF_AX` erweitert dieses Grundprinzip um die bidirektionale AE2-Kommunikation.
- **Set-Reset-Flip-Flop (z. B. `E_SR`):** Ein SR-FF hat separate Set- und Reset-Eingänge, aber keinen Toggle-Mechanismus. Der vorliegende Baustein kombiniert Toggle- und SR-Verhalten mit einer Verriegelungslogik.
- **Bausteine mit AX-Ausgang:** Der AX-Adapter ist ein gebräuchlicher Standard für unidirektionale boolesche Ausgänge. Andere Bausteine verwenden oft separate Datenports, während hier eine gekapselte Adapterschnittstelle genutzt wird.

## Fazit

`ILOCK_T_FF_AX` bietet eine kompakte, standardkonforme Lösung für einen verriegelbaren Toggle-Flip-Flop in der IEC‑61499‑Umgebung. Durch die Verwendung von AE2-Adapter-Schnittstellen lässt er sich nahtlos in moderne, modulare Automatisierungsarchitekturen integrieren. Der Composite-Aufbau erleichtert die Wartung und Anpassung, während die klare Trennung von Ereignis- und Datenflüssen die Fehlersuche vereinfacht. Der Baustein ist speziell für sicherheitsgerichtete oder verriegelungsabhängige Schaltaufgaben optimiert und bietet eine solide Grundlage für die Entwicklung komplexerer Steuerungslogiken.