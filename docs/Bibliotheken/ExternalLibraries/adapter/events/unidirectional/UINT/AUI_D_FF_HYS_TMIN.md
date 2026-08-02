# AUI_D_FF_HYS_TMIN

![AUI_D_FF_HYS_TMIN](./AUI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *
## Einleitung

Der Baustein **AUI_D_FF_HYS_TMIN** ist ein Datenspeicher (D‑Flip‑Flop) mit einstellbarer Hysterese und einer minimalen Zwischenereigniszeit (`Tmin`). Er wird über Adapter‑Schnittstellen (Socket `I` und Plug `Q`) mit anderen Bausteinen verbunden. Der interne Kern entspricht dem FB `E_D_FF_ANY_HYS_TMIN` aus der Bibliothek `logiBUS::signalprocessing::hysteresis`. Die Initialisierung legt die Parameter fest, danach wird bei jedem eingehenden Ereignis am Eingang `I.E1` der aktuelle Wert von `I.D1` übernommen, gefiltert und über `Q.D1` ausgegeben.

## Schnittstellenstruktur

### **Ereignis‑Eingänge**

| Name  | Typ    | Kommentar                            |
|-------|--------|--------------------------------------|
| INIT  | EInit  | Initialisierungsanforderung          |

### **Ereignis‑Ausgänge**

| Name   | Typ    | Kommentar                      |
|--------|--------|---------------------------------|
| INITO  | EInit  | Initialisierungsbestätigung     |

### **Daten‑Eingänge**

| Name       | Typ   | Kommentar                                  |
|------------|-------|--------------------------------------------|
| HYSTERESIS | UINT  | Hysterese‑Band                             |
| Tmin       | TIME  | Minimale Zwischenankunftszeit der EI‑Ereignisse |

### **Daten‑Ausgänge**

Keine eigenständigen Datenausgänge – der ausgegebene Wert wird über den Adapter `Q` übertragen.

### **Adapter**

| Typ                                                   | Bezeichnung | Kommentar           |
|-------------------------------------------------------|-------------|---------------------|
| `adapter::types::unidirectional::AUI` (Socket)         | I           | Zu speichernder Wert |
| `adapter::types::unidirectional::AUI` (Plug)          | Q           | Gespeicherter Wert   |

Der Adapter `AUI` ist ein unidirektionaler Typ, der ein Ereignis und einen Datenwert bündelt (`E1` und `D1`).

## Funktionsweise

1. **Initialisierung**  
   Beim Ereignis `INIT` werden die Parameter `HYSTERESIS` (als UINT) und `Tmin` (als TIME) an den internen Baustein übergeben. Nach erfolgreicher Initialisierung wird `INITO` ausgelöst.

2. **Betrieb**  
   Der interne FB `E_D_FF_ANY_HYS_TMIN` arbeitet als getaktetes D‑Flip‑Flop mit Hysterese und Zeitbegrenzung:

   - Ein Ereignis an `I.E1` (Clock) übernimmt den momentanen Datenwert von `I.D1`.
   - Der übernommene Wert wird nur dann als gültiger Ausgang `Q.D1` weitergegeben, wenn der Abstand zum letzten gültigen Ereignis größer oder gleich `Tmin` ist.
   - Zusätzlich wird der Wert mit einer Hysterese (band `HYSTERESIS`) geglättet: Kleine Änderungen unterhalb der Hystereseschwelle werden unterdrückt.
   - Der Ausgang wird über das Ereignis `Q.E1` signalisiert.

3. **Ergebnis**  
   Der Ausgangsadapter `Q` liefert den zuletzt angenommenen, gefilterten Wert.

## Technische Besonderheiten

- **Hysterese** in Verbindung mit einer **Mindestzeit zwischen zwei Ereignissen** verhindert sowohl Rauschen als auch zu schnelle Zustandswechsel.
- Der Baustein ist als **Adapter‑Wrapper** aufgebaut – er nutzt standardisierte unidirektionale AUI‑Adapter für Ein‑ und Ausgabe.
- Die Implementierung delegiert die gesamte Logik an den FB `E_D_FF_ANY_HYS_TMIN`, der universell für beliebige Datentypen ausgelegt ist. Hier wird er im Kontext des AUI‑Adapters verwendet.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten internen Zustandsautomaten. Das Verhalten wird durch den internen FB abgebildet:

- **Idle:** Wartet auf nächstes Ereignis an `I.E1`.
- **Sampling:** Bei Eintreffen von `I.E1` wird der Datenwert erfasst.
- **Filterung:** Prüfung gegen Hysterese und Tmin.
- **Ausgabe:** Bei Erfolg wird `Q.E1` ausgelöst und der neue Wert auf `Q.D1` gelegt.

## Anwendungsszenarien

- **Sensor‑Wert‑Erfassung** in der Landtechnik (siehe Copyright HR Agrartechnik GmbH): Verarbeitung von Analog‑ oder Digitalsignalen mit Entprellung und Mindestabtastrate.
- **Steuerungskomponenten** in Automatisierungssystemen, bei denen Rauschen unterdrückt und eine Mindestpulsdauer gefordert wird.
- **Datenlogik** in verteilten Systemen, die auf asynchrone Ereignisse mit Stabilitätsanforderungen reagieren müssen.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft |
|----------|-------------|
| `E_D_FF` | Einfaches D‑Flip‑Flop ohne Hysterese oder Zeitbegrenzung |
| `E_D_FF_HYS` | D‑Flip‑Flop mit Hysterese, aber ohne `Tmin` |
| `E_D_FF_HYS_TMIN` (dieser FB) | Kombiniert Hysterese *und* minimale Zwischenzeit → robuster gegen Rauschen und Burst‑Ereignisse |

## Fazit

Der `AUI_D_FF_HYS_TMIN` bietet eine kompakte und zuverlässige Lösung zur signalverarbeitenden Datenerfassung, die durch Hysterese und Zeitbegrenzung unerwünschte Störimpulse unterdrückt. Die Adapter‑Schnittstelle erleichtert die Integration in bestehende 4diac‑Projekte mittels standardisierter unidirektionaler AUI‑Verbindungen.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de
* [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
