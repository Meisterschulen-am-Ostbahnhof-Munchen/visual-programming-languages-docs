# E_D_FF_ANY_HYS_TMIN

![E_D_FF_ANY_HYS_TMIN](./E_D_FF_ANY_HYS_TMIN.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **E_D_FF_ANY_HYS_TMIN** ist ein D‑Flip-Flop (Data Latch) mit Hysterese, das zusätzlich eine minimale Verweilzeit („Minimum inter‑disposal Time“) zwischen aufeinanderfolgenden Ausgangsereignissen erzwingt. Er dient der stabilen Übernahme eines analogen oder diskreten Werts unter gleichzeitiger Unterdrückung von schnellem Rauschen und zu häufigen Zustandswechseln.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Beschreibung                                         |
|----------|-------|------------------------------------------------------|
| `INIT`   | EInit | Init‑Anforderung; Parameter `Tmin` wird übergeben    |
| `CLK`    | Event | Taktsignal; übernimmt den aktuellen Wert von `D` und wendet die Hysterese an |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Beschreibung                                              |
|----------|-------|-----------------------------------------------------------|
| `INITO`  | EInit | Bestätigung der Initialisierung                           |
| `EO`     | Event | Wird ausgegeben, wenn sich der Ausgang `Q` ändert **und** die Mindestzeit `Tmin` seit dem letzten `EO` abgelaufen ist |

### **Daten-Eingänge**

| Name         | Typ      | Beschreibung                                           |
|--------------|----------|--------------------------------------------------------|
| `D`          | ANY_NUM  | Wert, der bei `CLK` übernommen werden soll             |
| `HYSTERESIS` | ANY_NUM  | Hystereseband: Änderungen kleiner als dieser Betrag werden ignoriert |
| `Tmin`       | TIME     | Minimale Zeit zwischen zwei aufeinanderfolgenden `EO`‑Ereignissen |

### **Daten-Ausgänge**

| Name | Typ      | Beschreibung                                        |
|------|----------|-----------------------------------------------------|
| `Q`  | ANY_NUM  | Ausgangswert – der zuletzt gültige, gelatchte Wert  |

### **Adapter**

Keine.

## Funktionsweise

Der Baustein setzt sich intern aus zwei Funktionsblöcken zusammen:

1. **`E_D_FF_ANY_HYS`** – Ein D‑Flip‑Flop mit Hysterese: Bei einem `CLK`‑Ereignis wird der aktuelle Wert von `D` mit dem gespeicherten Wert verglichen. Nur wenn die Differenz den Betrag von `HYSTERESIS` überschreitet, wird der Ausgang `Q` auf den neuen Wert gesetzt und ein internes Ereignis an den nachfolgenden Block gesendet.
2. **`E_TMIN`** – Ein Timer, der sicherstellt, dass zwischen zwei `EO`‑Ereignissen mindestens die Zeit `Tmin` vergangen ist.

Ablauf:

- `INIT` initialisiert den Timer von `E_TMIN` mit dem Parameter `Tmin`.
- Ein `CLK` triggert das Hysterese‑Flip‑Flop.
- Wenn das Flip‑Flop eine Zustandsänderung erkennt, erzeugt es ein internes Ereignis (`E_D_FF_ANY_HYS.EO`).
- Dieses Ereignis wird an `E_TMIN.EI` weitergeleitet. `E_TMIN` prüft, ob seit dem letzten ausgegebenen `EO` die geforderte Mindestzeit `Tmin` verstrichen ist. Ist dies der Fall, wird `EO` am Ausgang gesetzt, andernfalls wird das Ereignis verworfen.
- Der Ausgangswert `Q` wird direkt vom Flip‑Flop an den Datenausgang durchgeschliffen.

## Technische Besonderheiten

- **Generischer Datentyp** `ANY_NUM`: Der Baustein kann mit verschiedenen numerischen Datentypen (INT, REAL, LREAL, …) arbeiten.
- **Hysterese** unterdrückt kleine Schwankungen (z. B. Sensorrauschen) und verhindert ungewolltes Oszillieren.
- **Minimale Ereignisabstand `Tmin`** begrenzt die maximale Ausgangsfrequenz und schützt nachfolgende Verarbeitungsschritte vor Überlastung.
- **Keine Zustandsmaschine sichtbar**: Die Funktionalität wird vollständig durch den inneren Netzwerkaufbau aus den Blöcken `E_D_FF_ANY_HYS` und `E_TMIN` realisiert.

## Zustandsübersicht

Da der Baustein intern aus zwei Unterblöcken besteht, ist kein eigenes Zustandsdiagramm im XML definiert. Die wesentlichen Verhaltensweisen sind:

- Initialisiert (`INIT` → `INITO`)
- Takten (`CLK`) → Übernahme von `D` mit Hysterese
- Veränderung von `Q` löst Timer‑Prüfung aus
- Timer erlaubt oder blockiert die Ausgabe von `EO`

## Anwendungsszenarien

- **Signalaufbereitung** für langsame Messgrößen (z. B. Temperatur, Füllstand), bei denen kleine Schwankungen ignoriert werden sollen und eine Mindestaktualisierungsrate eingehalten werden muss.
- **Entprellung** von digitalen oder analogen Schaltkontakten, die nur verzögert weitergegeben werden dürfen.
- **Regelungstechnik** mit begrenzter Stellfrequenz, um Aktoren zu schonen.
- **Datenvorverarbeitung** in IoT‑Edge-Geräten, die nicht jedes kleine Ereignis senden sollen.

## Vergleich mit ähnlichen Bausteinen

| Baustein                       | Hysterese | Min. Ereignisabstand | Einsatzgebiet                        |
|--------------------------------|-----------|----------------------|--------------------------------------|
| `E_D_FF` (einfach)             | Nein      | Nein                 | Reine Datenübernahme ohne Filterung  |
| `E_D_FF_ANY_HYS`               | Ja        | Nein                 | Hysterese, aber keine Frequenzbegrenzung |
| `E_D_FF_ANY_HYS_TMIN` (dieser) | Ja        | Ja                   | Komplette Filterung mit Rausch- und Frequenzbegrenzung |

## Fazit

Der `E_D_FF_ANY_HYS_TMIN` kombiniert zwei bewährte Mechanismen – Hysterese und minimale Ereignisverzögerung – in einem einzigen Funktionsblock. Dadurch eignet er sich besonders für raue Umgebungen, in denen Messwerte stabilisiert und die Kommunikationslast reduziert werden muss. Seine generische Datentypschnittstelle macht ihn flexibel einsetzbar.
