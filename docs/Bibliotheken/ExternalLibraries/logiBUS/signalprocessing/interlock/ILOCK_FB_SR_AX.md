# ILOCK_FB_SR_AX


![ILOCK_FB_SR_AX](./ILOCK_FB_SR_AX.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **ILOCK_FB_SR_AX** realisiert ein set-dominantes (Set-vorrangiges) bistabiles Flipflop (RS-Latch) mit Interlock-Funktion. Er ist für den Einsatz in Sicherheits- und Verriegelungsketten (Interlock) konzipiert, bei denen ein Set-Signal über mehrere Stufen propagiert und rückgekoppelt werden kann. Die Schnittstelle besteht aus zwei unidirektionalen AX-Adaptern (SET1, RESET) und einem AX2-Bidirektionaladapterpaar (ILOCK_IN / ILOCK_OUT) sowie einem Ausgangsadapter Q1. Der Baustein arbeitet ereignisgesteuert und führt bei jedem eingehenden Ereignis eine Neuberechnung der Ausgangswerte durch.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Datenherkunft | Beschreibung |
|----------|---------------|--------------|
| `SET1.E1` | Socket SET1 | Setzt den Ausgang Q1 (set-dominant) |
| `RESET.E1` | Socket RESET | Setzt den Ausgang Q1 zurück (nur wirksam, wenn SET1 = 0) |
| `ILOCK_IN.EO1` | Socket ILOCK_IN | Empfängt das Propagationsereignis von der übergeordneten Interlock-Stufe |
| `ILOCK_OUT.EI1` | Plug ILOCK_OUT | Empfängt ein Ereignis von der untergeordneten Interlock-Stufe (z. B. Bestätigung) |

### **Ereignis-Ausgänge**

| Ereignis | Datenherkunft | Beschreibung |
|----------|---------------|--------------|
| `Q1.E1` | Plug Q1 | Ausgangsereignis nach jeder Aktualisierung von Q1 |
| `ILOCK_IN.EI1` | Socket ILOCK_IN | Sendet Propagationsereignis an die übergeordnete Stufe |
| `ILOCK_OUT.EO1` | Plug ILOCK_OUT | Sendet Propagationsereignis an die untergeordnete Stufe |

### **Daten-Eingänge**

| Daten | Typ | Beschreibung |
|-------|-----|--------------|
| `SET1.D1` | BOOL | Set-Eingang (dominant) |
| `RESET.D1` | BOOL | Reset-Eingang (aktiv, wenn SET1=0) |
| `ILOCK_IN.DO1` | BOOL | Daten von der übergeordneten Interlock-Stufe (Propagationssignal) |
| `ILOCK_OUT.DI1` | BOOL | Daten von der untergeordneten Interlock-Stufe (Rückkopplung) |

### **Daten-Ausgänge**

| Daten | Typ | Beschreibung |
|-------|-----|--------------|
| `Q1.D1` | BOOL | Ausgang des Latches (gesetzt durch Set oder Interlock) |
| `ILOCK_IN.DI1` | BOOL | Propagiertes Set-Signal an die übergeordnete Stufe |
| `ILOCK_OUT.DO1` | BOOL | Propagiertes Set-Signal an die untergeordnete Stufe |

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| `Q1` | AX (unidirectional) | Plug | Ausgang des Latches |
| `ILOCK_OUT` | AX2 (bidirectional) | Plug | Interlock-Schnittstelle zur untergeordneten Stufe |
| `SET1` | AX (unidirectional) | Socket | Set-Eingang |
| `RESET` | AX (unidirectional) | Socket | Reset-Eingang |
| `ILOCK_IN` | AX2 (bidirectional) | Socket | Interlock-Schnittstelle zur übergeordneten Stufe |

## Funktionsweise
Der FB implementiert einen Algorithmus, der bei jedem eingehenden Ereignis die folgenden Berechnungen durchführt:

1. **Q1.D1 (Latch-Ausgang):**  
   `Q1.D1 := SET1.D1 OR ILOCK_IN.DO1 OR ILOCK_OUT.DI1 OR ((NOT RESET.D1) AND Q1.D1)`  
   - Der Ausgang wird gesetzt, wenn **SET1.D1**, **ILOCK_IN.DO1** (von oben) oder **ILOCK_OUT.DI1** (von unten) den Wert `TRUE` haben.  
   - Ist kein Set-Signal aktiv und **RESET.D1 = FALSE**, bleibt der aktuelle Wert von Q1 erhalten (Speicherverhalten).  
   - Set ist dominant: Ein aktives Set überschreibt einen Reset.

2. **ILOCK_IN.DI1 (Propagation nach oben):**  
   `ILOCK_IN.DI1 := SET1.D1 OR ILOCK_OUT.DI1`  
   - Das Set-Signal wird nach oben weitergegeben, wenn entweder der eigene Set-Eingang oder das Signal der unteren Stufe aktiv ist.

3. **ILOCK_OUT.DO1 (Propagation nach unten):**  
   `ILOCK_OUT.DO1 := SET1.D1 OR ILOCK_IN.DO1`  
   - Das Set-Signal wird nach unten weitergegeben, wenn entweder der eigene Set-Eingang oder das Signal der oberen Stufe aktiv ist.

Nach jeder Berechnung werden die Ereignisausgänge `Q1.E1`, `ILOCK_IN.EI1` und `ILOCK_OUT.EO1` aktiviert.

## Technische Besonderheiten
- **Interlock-Kaskade:** Der FB kann in einer Kette von mehreren identischen Bausteinen verwendet werden. Über die AX2-Adapter (ILOCK) wird ein Set-Signal sowohl nach oben als auch nach unten propagiert. Dies ermöglicht eine wechselseitige Verriegelung (Interlock) über mehrere Stufen.
- **Bidirektionale Kommunikation:** Der AX2-Adapter erlaubt sowohl das Senden als auch das Empfangen von Ereignissen und Daten in beide Richtungen, sodass eine Rückkopplung von untergeordneten Stufen möglich ist.
- **Set-Dominanz:** Ein aktiver Set-Eingang setzt den Ausgang sofort und blockiert einen Reset. Dieser Baustein ist daher ein **SR-Flipflop mit Vorrang des Set-Signals**.
- **Reine Ereignissteuerung:** Der FB hat keinen zyklischen Ablauf; jede Änderung wird nur durch ein entsprechendes Ereignis ausgelöst.

## Zustandsübersicht
Der FB besitzt einen einzigen internen Zustand **REQ**, in dem er sich immer befindet. Auf jedes eingehende Ereignis (SET1.E1, RESET.E1, ILOCK_IN.EO1, ILOCK_OUT.EI1) wird der Algorithmus ausgeführt und anschließend wieder in den Zustand REQ zurückgekehrt. Es gibt keine weiteren Zustände; der FB ist im Wesentlichen zustandslos (kombinatorisch mit Speicher durch Rückkopplung von Q1.D1).

## Anwendungsszenarien
- **Sicherheitsverriegelung in der Agrartechnik:** Kaskadierung mehrerer ILOCK_FB_SR_AX, um eine durchgängige Verriegelungskette (z. B. für Maschinenachsen) zu realisieren. Ein Set-Signal von einer beliebigen Stelle blockiert alle nachfolgenden Stufen.
- **Produktionsanlagen mit Freigabeketten:** Setzen und Rücksetzen von Freigabesignalen in einer hierarchischen Steuerung, wobei höhere Stufen niedrigere dominieren.
- **Redundante Steuerungssysteme:** Nutzung der Interlock-Funktion zur gegenseitigen Überwachung und Verriegelung mehrerer Steuerungskanäle.

## Vergleich mit ähnlichen Bausteinen
- **Standard RS-Flipflop (SR):** Ein einfacher SR-Baustein besitzt keinen Interlock-Mechanismus und keine bidirektionale Datenpropagation. Er kann nur lokal gesetzt oder zurückgesetzt werden.
- **ILOCK_FB_SR_AX** erweitert das klassische RS-Flipflop um eine Kaskadierungsfähigkeit über die AX2-Schnittstellen. Die Dominanz des Set-Signals und die Propagation in beide Richtungen machen ihn besonders für Sicherheitsketten geeignet.
- **Monostabile Bausteine:** Im Gegensatz zu monostabilen Funktionen behält dieser FB seinen Zustand bis zum nächsten Reset oder Set bei (bistabil).

## Fazit
Der ILOCK_FB_SR_AX ist ein spezialisierter Funktionsblock für den Aufbau von Interlock-Ketten mit set-dominanter Latch-Funktion. Durch die Kombination von unidirektionalen Set/Reset-Eingängen und bidirektionalen Interlock-Adaptern eignet er sich hervorragend für sicherheitsgerichtete Anwendungen, bei denen eine Kaskadierung und gegenseitige Verriegelung mehrerer Stufen erforderlich ist. Seine einfache, ereignisgesteuerte Logik ermöglicht eine effiziente und deterministische Verarbeitung in der Automatisierungstechnik.