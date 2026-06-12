# AS_D_FF_HYS_TMIN


![AS_D_FF_HYS_TMIN](./AS_D_FF_HYS_TMIN.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsbaustein **AS_D_FF_HYS_TMIN** realisiert ein datengetriggertes Flipflop (D-Flipflop) mit Hysterese und einer minimalen Zeitverzögerung zwischen aufeinanderfolgenden Ereignissen. Er dient zur stabilen, entprellten Signalweitergabe in zeitkritischen Steuerungsabläufen. Der Baustein nutzt Adapter zur unidirektionalen Kommunikation, wobei ein Eingangssignal über den Socket **I** empfangen und das latchende Ausgangssignal über den Plug **Q** bereitgestellt wird.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name  | Typ   | Kommentar                                   |
|-------|-------|---------------------------------------------|
| INIT  | EInit | Initialisierungsanfrage; setzt Hysterese und Mindestzeit |

### **Ereignis-Ausgänge**
| Name  | Typ   | Kommentar                                   |
|-------|-------|---------------------------------------------|
| INITO | EInit | Bestätigung der abgeschlossenen Initialisierung |

### **Daten-Eingänge**
| Name       | Typ  | Kommentar                                        |
|------------|------|--------------------------------------------------|
| HYSTERESIS | SINT | Hysterese-Band (ganzzahliger Wert, z. B. 8 Bit) |
| Tmin       | TIME | Minimale Zeit zwischen zwei Ereignissen (z. B. für Entprellung) |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – das Ausgangssignal wird über den Adapter **Q** bereitgestellt.

### **Adapter**
| Typ | Bezeichnung | Richtung | Kommentar                             |
|-----|-------------|----------|---------------------------------------|
| AS  | I (Socket)  | Eingang  | Unidirektionaler Adapter für das zu latchnde Signal (z. B. Daten‑ + Ereignisleitung) |
| AS  | Q (Plug)    | Ausgang  | Unidirektionaler Adapter für das latchende Ausgangssignal |

## Funktionsweise
Der Baustein arbeitet intern mit einem vordefinierten Funktionsbaustein **E_D_FF_ANY_HYS_TMIN**. Beim Ereignis **INIT** werden die Parameter **HYSTERESIS** und **Tmin** übernommen. Das eingehende Ereignis (über den Adapter **I**, Leitung **E1**) triggert den Flipflop‑Clock, während der zugehörige Datenwert (über **I.D1**) übernommen wird. Der Ausgang **Q.D1** wird nur dann aktualisiert, wenn  
- der neue Datenwert um mindestens die **Hysterese** vom aktuell gespeicherten Wert abweicht, und  
- seit dem letzten Ereignis mindestens die Zeit **Tmin** vergangen ist.  

Das Ausgangsereignis (über **Q.E1**) signalisiert eine gültige Aktualisierung. Der Baustein unterdrückt somit Rauschen und verhindert zu schnelle Flankenwechsel.

## Technische Besonderheiten
- **Adapterbasierte Ein‑/Ausgabe** – Die Signalübertragung über die Adapter **I** und **Q** ermöglicht eine einfache Integration in komplexe Adapter‑Netzwerke und erhöht die Wiederverwendbarkeit.
- **Hysterese** – Vermeidet Oszillationen bei schwankenden oder verrauschten Eingangssignalen, indem nur signifikante Änderungen übernommen werden.
- **Minimale Ereigniszeit (Tmin)** – Erzwingt eine Mindestpause zwischen zwei Triggerungen; dient als zusätzlicher Entprellmechanismus.
- **Interne Nutzung eines bewährten Flipflop‑Bausteins** – Die Implementierung delegiert die Kernlogik an **E_D_FF_ANY_HYS_TMIN**, der für generische Datentypen ausgelegt ist.

## Zustandsübersicht
Der Baustein kennt keine expliziten, extern sichtbaren Zustände. Intern führt das Flipflop einen gespeicherten Wert (letzter gültiger Ausgang), der nur bei Erfüllung der Hysterese‑ und Zeitbedingungen aktualisiert wird. Nach der Initialisierung (INIT/INITO) ist der gespeicherte Wert undefiniert, bis das erste gültige Signal eintrifft.

## Anwendungsszenarien
- **Entprellung von Sensorsignalen** – z. B. Endschalter oder Näherungssensoren mit mechanischem Prellen.
- **Frequenzbegrenzung** – Verhindern zu schneller Schaltvorgänge in nachgeschalteten Aktoren oder Kommunikationsschnittstellen.
- **Hysteresebasierte Schwellwerterkennung** – z. B. Temperatur‑ oder Druckregelung mit Rücksetzband.
- **Signalweitergabe in zeitkritischen, störungsbehafteten Umgebungen** (z. B. Landmaschinen‑Steuerungen).

## Vergleich mit ähnlichen Bausteinen
- **Einfaches D-Flipflop (z. B. E_D_FF)** – ohne Hysterese oder Zeitverzögerung; übernimmt jeden Takt ohne Filterung.
- **Schmitt‑Trigger‑Baustein** – ebenfalls mit Hysterese, jedoch meist ohne asynchrone Ereignissteuerung und ohne einstellbare Mindestzeit.
- **Verzögerungsbaustein (z. B. E_DELAY)** – verzögert nur das Signal, hat aber keine Hysterese oder Latch‑Funktion.

**AS_D_FF_HYS_TMIN** vereint Latch‑Funktion, Hysterese und Zeitsteuerung in einem Baustein und ist daher speziell für robuste, zeitgesteuerte Signalverarbeitung optimiert.

## Fazit
Der **AS_D_FF_HYS_TMIN** ist ein spezialisierter Funktionsbaustein für industrielle Steuerungen, die eine zuverlässige, rauschunempfindliche Signalweitergabe mit einstellbarer Totzeit erfordern. Die Kombination aus D‑Flipflop, Hysterese und Minimalzeit macht ihn zu einem wertvollen Werkzeug für Automatisierungslösungen, insbesondere in Umgebungen mit hohen Störeinflüssen oder engen zeitlichen Anforderungen.