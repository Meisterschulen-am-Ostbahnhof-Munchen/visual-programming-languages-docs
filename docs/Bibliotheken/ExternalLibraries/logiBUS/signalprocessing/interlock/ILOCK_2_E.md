# ILOCK_2_E


![ILOCK_2_E](./ILOCK_2_E.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ILOCK_2_E** ist ein ereignisgesteuerter bistabiler und Toggle-Baustein mit dualer Verriegelung (Interlock). Er dient zur Steuerung von zwei sich gegenseitig ausschließenden Ausgängen (OUT1, OUT2). Neben expliziten Setz- und Rücksetzfunktionen bietet der Block eine flankengesteuerte Toggle-Funktion, die ein einmaliges Umschalten pro Aktivierung ermöglicht. Der Baustein eignet sich besonders für Steuerungslogiken, bei denen niemals beide Ausgänge gleichzeitig TRUE sein dürfen und ein wiederholter Toggle-Befehl erst nach erneuter Freigabe (z. B. durch ein Setzen des anderen Kanals oder Reset) wirksam wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Kommentar |
|----------|-----------|
| `SET1`   | Setzt OUT1 auf TRUE und OUT2 auf FALSE. |
| `CLK1`   | Toggelt OUT1 (bei erstmaliger Aktivierung nach einem Set/Reset) und setzt OUT2 auf FALSE. |
| `SET2`   | Setzt OUT2 auf TRUE und OUT1 auf FALSE. |
| `CLK2`   | Toggelt OUT2 und setzt OUT1 auf FALSE. |
| `R`      | Rücksetzen (Reset) beider Ausgänge auf FALSE. |

### **Ereignis-Ausgänge**

| Ereignis | Kommentar |
|----------|-----------|
| `EO`     | Wird nach jeder Ausgangsänderung (SET, TOGGLE oder RESET) ausgelöst. Trägt die aktuellen Werte von OUT1 und OUT2. |

### **Daten-Eingänge**

Keine (der Baustein ist rein ereignisgesteuert).

### **Daten-Ausgänge**

| Ausgang | Typ   | Kommentar |
|---------|-------|-----------|
| `OUT1`  | BOOL  | Erster Ausgang (bistabiler Wert). |
| `OUT2`  | BOOL  | Zweiter Ausgang (bistabiler Wert). |

### **Adapter**

Keine.

## Funktionsweise

Der FB besitzt sechs Zustände: den initialen Ruhezustand **STOP** sowie fünf Aktionszustände (**SET1**, **SET2**, **TOGGLE1**, **TOGGLE2**, **RESET**). Bei Eintreffen eines Ereignisses wird sofort in den entsprechenden Zustand gewechselt, der zugehörige Algorithmus ausgeführt und anschließend das Ereignis `EO` ausgegeben. Danach kehrt der Baustein unverzüglich in den Zustand **STOP** zurück (Bedingung `1` auf allen Transitionen).

Die interne Logik sorgt für eine **duale Verriegelung**: Beim Setzen eines Ausgangs wird der andere zwangsweise auf FALSE gesetzt. Auch beim Togglen eines Ausgangs wird der andere Ausgang zurückgesetzt.

Die **Toggle-Funktion** ist flankengesteuert: Die internen Variablen `EDGE1` und `EDGE2` speichern, ob bereits ein Toggle auf dem entsprechenden Kanal ausgeführt wurde. Nur bei `EDGE = FALSE` (d. h. nach einem Reset oder einem Set des anderen Kanals) wird der Toggle tatsächlich ausgeführt und das Flag auf TRUE gesetzt. Wiederholte CLK-Ereignisse ohne zwischenzeitliches Setzen/Rücksetzen des eigenen oder des anderen Kanals werden ignoriert.

## Technische Besonderheiten

- **Kantenerkennung für Toggle** – Die internen Flags `EDGE1`/`EDGE2` verhindern mehrfaches Togglen bei derselben Freigabe.
- **Immer exklusive Ausgänge** – Jeder Algorithmus stellt sicher, dass nie beide Ausgänge gleichzeitig TRUE sind.
- **Keine Daten-Eingänge** – Die gesamte Steuerung erfolgt ausschließlich über Ereignisse, was eine einfache Integration in ereignisbasierte Automatisierungssysteme ermöglicht.
- **Robustes Reset-Verhalten** – Ein Reset setzt sowohl die Ausgänge als auch die internen Kantenflags zurück, sodass die Toggle-Funktion wieder bereit ist.

## Zustandsübersicht

| Zustand     | Beschreibung                | Auslöser | Algorithmus-Effekt (vereinfacht)                        | Ausgang |
|-------------|-----------------------------|----------|---------------------------------------------------------|---------|
| `STOP`      | Initial, wartet auf Ereignis | -        | –                                                       | –       |
| `SET1`      | Setze Ausgang 1             | `SET1`   | OUT1=TRUE, OUT2=FALSE, EDGE1=FALSE, EDGE2=FALSE        | `EO`    |
| `SET2`      | Setze Ausgang 2             | `SET2`   | OUT1=FALSE, OUT2=TRUE, EDGE1=FALSE, EDGE2=FALSE        | `EO`    |
| `TOGGLE1`   | Toggle Ausgang 1            | `CLK1`   | Wenn EDGE1=FALSE: OUT1 = NOT OUT1; OUT2=FALSE; EDGE1=TRUE; EDGE2=FALSE | `EO` |
| `TOGGLE2`   | Toggle Ausgang 2            | `CLK2`   | OUT1=FALSE; wenn EDGE2=FALSE: OUT2 = NOT OUT2; EDGE1=FALSE; EDGE2=TRUE | `EO` |
| `RESET`     | Reset aller Ausgänge        | `R`      | OUT1=FALSE, OUT2=FALSE, EDGE1=FALSE, EDGE2=FALSE       | `EO`    |

Alle Aktionszustände wechseln nach Ausführung des Algorithmus sofort zurück zu `STOP`.

## Anwendungsszenarien

- **Richtungssteuerung** (z. B. Motor links/rechts) – nie beide Richtungen gleichzeitig aktiv.
- **Pumpensteuerung mit Priorität** – zwei Pumpen, wobei immer nur eine laufen darf.
- **Modusumschaltung mit einmaligem Toggle** – z. B. „Start/Stop“-Verhalten, bei dem ein wiederholter Toggle-Befehl erst nach einem Reset oder einer anderen Aktion wirksam wird.
- **Verriegelte Schaltzustände in Sicherheitssteuerungen** – garantierte Exklusivität der Ausgänge.

## Vergleich mit ähnlichen Bausteinen

| Baustein      | Eigenschaften                                                                 |
|---------------|-------------------------------------------------------------------------------|
| `E_SR`        | Einfacher Set‑/Reset‑Flipflop, kein Toggle, keine duale Verriegelung.         |
| `SR-Flipflop` (zwei Ausgänge) | Oft nur kombinatorisch oder ohne Kantenerkennung.                               |
| `ILOCK_2_E`   | Bietet beides: **Setzen** (exklusiv) und **flankengesteuertes Toggle** mit automatischer Verriegelung. Ideal für erweiterte Anforderungen. |

## Fazit

Der Funktionsblock `ILOCK_2_E` ist ein leistungsfähiger Baustein für Anwendungen mit zwei sich gegenseitig ausschließenden Zuständen. Die Kombination aus explizitem Setzen, flankengesteuertem Toggle und robustem Reset-Verhalten macht ihn besonders geeignet für Steuerungslogiken, die eine klare Trennung der Ausgänge und eine definierte Reaktion auf wiederholte Befehle erfordern. Die Integration in ereignisbasierte Automatisierungssysteme (z. B. IEC 61499) erfolgt durch die rein ereignisgesteuerte Schnittstelle und den einheitlichen Ausgang `EO`.