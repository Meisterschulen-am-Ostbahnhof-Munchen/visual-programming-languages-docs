# ILOCK_T_FF_SR_AX


![ILOCK_T_FF_SR_AX](./ILOCK_T_FF_SR_AX.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ILOCK_T_FF_SR_AX** ist ein zusammengesetzter Baustein (Composite FB) für ein verriegelbares Toggle-Flipflop mit Set-Reset-Funktionalität und einer AE2-Adapter-Schnittstelle. Er ermöglicht das gezielte Setzen, Rücksetzen und Takten eines Ausgangssignals unter Berücksichtigung von Verriegelungszuständen, die über bidirektionale Adapter eingelesen und ausgegeben werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| S    | Event | Setzt den Ausgang Q (sofern nicht verriegelt) |
| R    | Event | Setzt den Ausgang Q zurück |
| CLK  | Event | Takt-Eingang zum Umschalten (Toggle) des Ausgangs |

### **Ereignis-Ausgänge**

Der Baustein besitzt keine expliziten Ereignis-Ausgänge. Die Ausgabe erfolgt über Adapter.

### **Daten-Eingänge**

Es sind keine direkten Dateneingänge vorhanden. Die Verriegelungsinformationen werden über die Adapter `ILOCK_IN` und `ILOCK_OUT` ausgetauscht.

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| Q    | Adapter AX (unidirektional) | Ausgangssignal des internen SR-Flipflops |

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket   | ILOCK_IN | AE2 (bidirektional) | Empfängt Verriegelungssignale von externen Bausteinen |
| Plug     | ILOCK_OUT | AE2 (bidirektional) | Sendet Verriegelungssignale an externe Bausteine |
| Plug     | Q         | AX  (unidirektional) | Gibt den aktuellen Zustand des Flipflops aus |

## Funktionsweise

Der Baustein realisiert ein SR-Flipflop mit Toggle-Funktion und Verriegelungsmechanismus.

- **Setzen (S)**: Ein Ereignis an `S` bewirkt über eine Zusammenführung (E_MERGE_2) ein Setzen des internen SR-Flipflops `E_SR`. Der Ausgang Q wird auf `true` gesetzt, sofern keine verriegelnde Rücksetzung von `ILOCK_IN` oder `ILOCK_OUT` vorliegt.
- **Rücksetzen (R)**: Ein Ereignis an `R` setzt den Ausgang Q auf `false`. Zusätzlich können sowohl der Eingangsadapter `ILOCK_IN` als auch der Ausgangsadapter `ILOCK_OUT` ebenfalls ein Rücksetzen auslösen – dies dient der Verriegelung (Interlock).
- **Toggle (CLK)**: Bei jedem Takt-Ereignis an `CLK` wird der aktuelle Zustand von Q ausgewertet. Über einen Schalter (E_SWITCH) wird:
  - Bei Q = `false` ein Setz-Impuls erzeugt (Q → `true`).
  - Bei Q = `true` ein Rücksetz-Impuls erzeugt (Q → `false`).
  Somit wird der Ausgang bei jedem CLK-Ereignis umgeschaltet, sofern keine Verriegelung dies unterbindet.

Die Verriegelung erfolgt über das bidirektionale AE2-Protokoll: Die Signale von `ILOCK_IN` und `ILOCK_OUT` werden gegenseitig durchgeschliffen und können sowohl das interne Flipflop rücksetzen als auch untereinander ausgetauscht werden. Dadurch lässt sich eine sichere Sperre (z. B. gegenseitiger Ausschluss) realisieren.

## Technische Besonderheiten

- **Composite-Architektur**: Der FB besteht aus den eingebetteten Funktionen `E_SR`, `E_SWITCH` und `E_MERGE_2`, die logisch verknüpft sind.
- **Bidirektionale Verriegelung**: Die Adapter `ILOCK_IN` und `ILOCK_OUT` sind vom Typ AE2, der einen bidirektionalen Austausch von Ereignissen und Daten ermöglicht. Dies erlaubt eine verschränkte Verriegelung mit anderen Bausteinen.
- **Toggle nur bei Zustandsänderung**: Der Toggle-Mechanismus wertet den Ausgang Q aus, sodass nur dann ein Umschalten erfolgt, wenn das Flipflop nicht bereits durch S oder R gesetzt wurde.
- **Keine direkten Dateneingänge**: Die Steuerung erfolgt ausschließlich über Ereignisse und Adapter, was die Integration in ereignisgesteuerte Systeme erleichtert.

## Zustandsübersicht

Der interne Zustand des Flipflops kann die Werte `false` (0) oder `true` (1) annehmen. Die möglichen Übergänge:

| Aktuell | Ereignis | Neuer Zustand | Bedingungen |
|---------|----------|---------------|-------------|
| 0       | S        | 1             | Keine Verriegelung durch ILOCK |
| 0       | R        | 0             | – |
| 0       | CLK      | 1             | Keine Verriegelung |
| 0       | ILOCK_IN/ILOCK_OUT | 0 | – |
| 1       | S        | 1             | – |
| 1       | R        | 0             | Keine Verriegelung (Vorrang von R) |
| 1       | CLK      | 0             | Keine Verriegelung |
| 1       | ILOCK_IN/ILOCK_OUT | 0 | – |

## Anwendungsszenarien

- **Maschinensteuerung**: Schalten eines Ausgangs (z. B. Ventil oder Motor) im Takt, wobei eine übergeordnete Sicherheitssteuerung den Ausgang bei Gefahr sperren kann.
- **Gegenseitige Verriegelung (Interlock)**: Mehrere Bausteine des Typs `ILOCK_T_FF_SR_AX` können über die bidirektionalen Adapter so verschaltet werden, dass immer nur einer seiner Ausgang gesetzt hat (z. B. bei Weichen- oder Antriebssteuerung).
- **Taktgesteuerte Signalgenerierung**: Erzeugen eines periodischen Rechtecksignals durch Anlegen eines Takts an `CLK`, wobei Setzen und Rücksetzen extern eingreifen können.

## Vergleich mit ähnlichen Bausteinen

- **Einfaches SR-Flipflop**: Besitzt keine Toggle-Funktion und keine Adapter für Verriegelung.
- **TcFF (Toggle-Flipflop)**: Erlaubt nur das Umschalten bei einem Taktereignis, hat aber keine getrennten Set-/Reset-Eingänge und keine Verriegelungsschnittstelle.
- **Standard-Interlock-Bausteine**: Oft auf binäre Signale beschränkt, während `ILOCK_T_FF_SR_AX` die Kombination aus Toggle, SR und bidirektionaler Verriegelung in einem Baustein vereint.

## Fazit

Der Funktionsblock `ILOCK_T_FF_SR_AX` bietet eine flexible und sichere Möglichkeit, einen Ausgang zu steuern, der sowohl getaktet umschalten als auch über separate Set-/Reset-Eingänge sowie über eine erweiterbare Verriegelungsschnittstelle beeinflusst werden kann. Durch die Kombination von SR-Flipflop und Toggle-Logik eignet er sich besonders für sicherheitskritische Anwendungen in der Automatisierungstechnik.