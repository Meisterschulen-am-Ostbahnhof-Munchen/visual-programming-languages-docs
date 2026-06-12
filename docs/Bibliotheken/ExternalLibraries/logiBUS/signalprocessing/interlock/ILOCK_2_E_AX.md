# ILOCK_2_E_AX


![ILOCK_2_E_AX](./ILOCK_2_E_AX.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ILOCK_2_E_AX** stellt zwei bistabile Ausgänge mit gegenseitiger Verriegelung (Interlock) sowie einer Toggle-Funktion bereit. Er wird über Ereignisse gesteuert und gibt seine Zustände über zwei Adapter (Typ `AX`) aus. Der Baustein eignet sich für Anwendungen, bei denen zwei sich gegenseitig ausschließende Signale benötigt werden, z. B. für die Ansteuerung von Weichen, Ventilen oder Motoren.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name   | Beschreibung                                   |
|--------|-----------------------------------------------|
| `SET1` | Setzt Ausgang `OUT1` auf TRUE und `OUT2` auf FALSE |
| `CLK1` | Toggelt den Zustand von `OUT1`, sofern nicht bereits getoggelt |
| `SET2` | Setzt Ausgang `OUT2` auf TRUE und `OUT1` auf FALSE |
| `CLK2` | Toggelt den Zustand von `OUT2`, sofern nicht bereits getoggelt |
| `R`    | Setzt beide Ausgänge auf FALSE (Reset)        |

### **Ereignis-Ausgänge**
Der Funktionsblock besitzt keine eigenen Ereignis-Ausgänge. Die Ausgangssignale werden ausschließlich über die **Adapter** (siehe unten) übertragen.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Die aktuellen Zustände der Flip-Flops sind über die **Adapter** (siehe unten) abrufbar.

### **Adapter**

| Name   | Typ  | Beschreibung                                      |
|--------|------|--------------------------------------------------|
| `OUT1` | `AX` | Stellt den Zustand des ersten Flip-Flops bereit (Datenausgang `D1`) und quittiert Änderungen über Ereignisausgang `E1` |
| `OUT2` | `AX` | Stellt den Zustand des zweiten Flip-Flops bereit (Datenausgang `D1`) und quittiert Änderungen über Ereignisausgang `E1` |

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert. Ein eingehendes Ereignis löst eine Zustandsänderung aus, die sofort an den entsprechenden Adaptern ausgegeben wird.

- **SET1**: Setzt `OUT1.D1 = TRUE` und `OUT2.D1 = FALSE`. Die internen Flankenspeicher (`EDGE1`, `EDGE2`) werden zurückgesetzt.
- **SET2**: Setzt `OUT1.D1 = FALSE` und `OUT2.D1 = TRUE`. Flankenspeicher werden zurückgesetzt.
- **CLK1**: Toggelt `OUT1.D1` (wenn nicht bereits durch ein vorheriges `CLK1`-Ereignis getoggelt) und setzt `OUT2.D1 = FALSE`. Der Flankenspeicher `EDGE1` verhindert wiederholtes Toggeln beim selben Ereignis.
- **CLK2**: Toggelt `OUT2.D1` (Flankenspeicher `EDGE2`) und setzt `OUT1.D1 = FALSE`.
- **R**: Setzt beide Ausgänge auf FALSE und löscht die internen Flankenspeicher.

Die Verriegelung sorgt dafür, dass immer nur einer der beiden Ausgänge den Wert TRUE annehmen kann. Beim Toggeln eines Ausgangs wird der andere stets auf FALSE gesetzt.

## Technische Besonderheiten
- Der Baustein verwendet **Adapter** (Typ `AX`) als Ausgänge. Dies ermöglicht eine flexible Verbindung mit anderen Bausteinen, die denselben Adapter unterstützen.
- Eine **interne Flankenerkennung** (Variablen `EDGE1`, `EDGE2`) verhindert mehrfaches Toggeln bei einem einzelnen Ereignis. Erst nach einem Reset oder einem expliziten Setzen wird der Flankenspeicher zurückgesetzt, sodass ein erneutes Toggeln möglich ist.
- Alle Algorithmen werden **atomar** in den Zuständen des ECC ausgeführt; der Baustein gibt nach jeder Aktion ein Ereignis über die Adapter aus (`OUT1.E1` bzw. `OUT2.E1`).
- Die Initialzustände aller Ausgänge sind **FALSE**.

## Zustandsübersicht
Der Ablaufsteuerung (ECC) liegen folgende Zustände zugrunde:

- **STOP** – Wartezustand (initial)
- **SET1** – Setzt Kanal 1
- **SET2** – Setzt Kanal 2
- **TOGGLE1** – Toggelt Kanal 1, deaktiviert Kanal 2
- **TOGGLE2** – Toggelt Kanal 2, deaktiviert Kanal 1
- **RESET** – Setzt beide Kanäle zurück

Die Übergänge zwischen den Zuständen erfolgen durch die empfangenen Ereignisse (`SET1`, `SET2`, `CLK1`, `CLK2`, `R`) und kehren nach Ausführung der Aktionen automatisch in den Zustand `STOP` zurück (Übergangsbedingung `1`).

## Anwendungsszenarien
- **Wechselweiser Betrieb** von zwei Verbrauchern, z. B. Vorschub-/Rücklaufventile, bei denen nie beide gleichzeitig aktiv sein dürfen.
- **Taktgesteuerte Umschaltung** zwischen zwei Zuständen (z. B. Richtungswechsel eines Förderbands) mittels der Toggle-Eingänge.
- **Zentrale Reset-Funktion** für eine Gruppe von bistabilen Aktoren über den `R`-Eingang.

## Vergleich mit ähnlichen Bausteinen
Gegenüber einem einfachen Set-Reset-Flipflop (z. B. `E_SR`) bietet **ILOCK_2_E_AX** zwei Ausgänge mit integrierter Verriegelung und einer Toggle-Funktion. Während `E_SR` nur einen einzelnen Ausgang umschaltet, kann dieser Baustein zwei gekoppelte Signale steuern. Die Verwendung von Adaptern anstelle von direkten Datenports erlaubt eine standardisierte und wiederverwendbare Kopplung mit anderen Bausteinen.

## Fazit
Der Funktionsblock **ILOCK_2_E_AX** ist ein kompakter, ereignisgesteuerter Baustein zur Realisierung von verriegelten, bistabilen Ausgängen mit optionaler Toggle-Funktion. Durch die Adapter-basierte Schnittstelle und die klare Trennung von Setzen, Toggeln und Zurücksetzen eignet er sich besonders für sicherheitskritische oder logisch verknüpfte Steuerungsaufgaben in der Automatisierungstechnik.