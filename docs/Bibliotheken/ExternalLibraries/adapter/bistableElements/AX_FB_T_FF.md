# AX_FB_T_FF


![AX_FB_T_FF](./AX_FB_T_FF.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AX_FB_T_FF** realisiert ein taktflankengesteuertes Toggle-Flipflop (T-FF).  
Er schaltet seinen Ausgangszustand bei jeder aktiven Taktflanke um und kann asynchron zurückgesetzt werden.  
Die Ein- und Ausgänge erfolgen ausschließlich über Adapter des Typs `AX`, die sowohl ein Ereignis als auch einen booleschen Datenwert übertragen.

## Schnittstellenstruktur

Der Baustein besitzt keine direkten Ereignis- oder Datenschnittstellen.  
Die gesamte Kommunikation erfolgt über **Adapter** (Plugs und Sockets).

### **Ereignis-Eingänge**
Keine (Ereignisse werden über die Adapter `CLK` und `RST` empfangen).

### **Ereignis-Ausgänge**
Keine (Ereignisse werden über den Adapter `Q1` gesendet).

### **Daten-Eingänge**
Keine (Daten werden über die Adapter `CLK` und `RST` empfangen).

### **Daten-Ausgänge**
Keine (Daten werden über den Adapter `Q1` gesendet).

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket** (Eingang) | `CLK` | `adapter::types::unidirectional::AX` | Taktsignal – bei jedem eingehenden Ereignis (E1) wird der Bool‑Wert (D1) als Taktpegel ausgewertet. |
| **Socket** (Eingang) | `RST` | `adapter::types::unidirectional::AX` | Reset – bei einem eingehenden Ereignis (E1) wird der Ausgang unabhängig vom Takt auf FALSE gesetzt (asynchroner Reset). |
| **Plug** (Ausgang) | `Q1` | `adapter::types::unidirectional::AX` | Ausgang – bei jedem Taktwechsel oder Reset wird ein Ereignis (E1) ausgelöst und der aktuelle Bool‑Wert (D1) gesendet. |

Die Adapter vom Typ `unidirectional::AX` besitzen intern:
- Ein Ereignis (E1)
- Ein Datum (D1) vom Typ `BOOL`

## Funktionsweise

Der Baustein arbeitet als **Toggle-Flipflop mit positiver Flankenerkennung**.  
Er besitzt einen internen Speicher `EDGE`, der den letzten Taktpegel speichert.

**Algorithmus (im Zustand REQ):**

1. Wenn ein Reset-Ereignis an `RST.E1` eintrifft:
   - Ausgang `Q1.D1` wird auf `FALSE` gesetzt.
   - Ausgangsereignis `Q1.E1` wird ausgelöst.

2. Andernfalls, wenn ein Takt-Ereignis an `CLK.E1` eintrifft:
   - Prüfen, ob der aktuelle Taktpegel `CLK.D1 = TRUE` und der vorherige Pegel `EDGE = FALSE` ist (d.h. positive Flanke).
   - Wenn ja: `Q1.D1` wird invertiert (`NOT Q1.D1`).
   - Unabhängig von der Flanke wird `EDGE := CLK.D1` gesetzt (Pegelmerker).
   - Ausgangsereignis `Q1.E1` wird ausgelöst.

3. Bleibt der Ausgang ohne Änderung, wenn `RST.E1` oder `CLK.E1` nicht eintreffen, wird kein Ereignis gesendet.

## Technische Besonderheiten

- **Adapter basierte Schnittstelle**: Der Baustein verwendet ausschließlich Adapter, was die modulare Kopplung mit anderen Bausteinen desselben Typs erleichtert.
- **Flankenerkennung**: Die interne Variable `EDGE` realisiert eine einfache positive Flankenerkennung. Ein Tastwechsel von 0→1 löst das Toggeln aus; ein konstanter High-Pegel löst nur einmal aus.
- **Asynchroner Reset**: Der Reset hat Vorrang vor der Taktflanke – er setzt den Ausgang sofort zurück, auch wenn gleichzeitig ein Takt-Ereignis ansteht.
- **Nur ein ECC-Zustand**: Der gesamte Ablauf spielt sich im Zustand `REQ` ab. Beide Transitionen (`CLK.E1` und `RST.E1`) führen zurück zu diesem Zustand.

## Zustandsübersicht

Der ECC besteht aus einem einzigen Zustand `REQ`.  
Jeder eingehende Ereignisimpuls (über `CLK.E1` oder `RST.E1`) führt zur Ausführung des Algorithmus `REQ` und einem sofortigen Ausgangsereignis auf `Q1.E1`.

| aktueller Zustand | eingehendes Ereignis | nächster Zustand | ausgeführte Aktion |
|-------------------|----------------------|------------------|--------------------|
| REQ               | `RST.E1`             | REQ              | RESET: Q1.D1 = FALSE |
| REQ               | `CLK.E1`             | REQ              | Toggle bei steigender Flanke und aktualisieren von EDGE |

Keine weiteren Zustände oder Verweilzeiten.

## Anwendungsszenarien

- **Taktgesteuerter Zustandswechsel**: Umschalten eines Ausgangs bei jeder steigenden Flanke eines Taktsignals (z.B. für Frequenzteiler oder Zähler).
- **Tastenentprellung**: Kombiniert mit einem Entprell-Baustein kann das Flipflop einen stabilen Zustandswechsel bei jedem Tastendruck erzeugen.
- **Signalumschaltung**: Ein- und Ausschalten eines Signals durch wiederholte Impulse.
- **Steuerung in Automatisierungssystemen**: Z.B. Wechsel zwischen zwei Betriebsmodi.

## Vergleich mit ähnlichen Bausteinen

- **Standard T-FF (z.B. `F_TRIG`/`R_TRIG`)**: Diese Bausteine detektieren nur Flanken, toggeln aber nicht den Ausgang. `AX_FB_T_FF` vereint Flankenerkennung und Toggle-Funktion.
- **SR-Flipflop (Set/Reset)**: Im Gegensatz zum SR-FF hat der T-FF nur einen Reset-Eingang und schaltet bei jedem Takt um, anstatt durch separate Set- und Reset-Signale gesteuert zu werden.
- **Adapterbasierte Varianten**: Andere T-FF in 4diac nutzen oft direkte Ein-/Ausgänge. Dieser Baustein ermöglicht eine lose Kopplung über Adapter, was die Wiederverwendbarkeit erhöht.

## Fazit

Der `AX_FB_T_FF` ist ein kompakter und flexibler Funktionsbaustein, der ein Toggle-Flipflop mit positiver Flankenerkennung und asynchronem Reset realisiert.  
Durch die reine Adapter-Schnittstelle lässt er sich besonders gut in modularen, adapterbasierten Entwürfen einsetzen, bei denen Daten- und Ereignisübertragung über einen einheitlichen Kanal erfolgen.  
Die einfache Logik und der minimale Zustandsautomat machen ihn zuverlässig und leicht verständlich.