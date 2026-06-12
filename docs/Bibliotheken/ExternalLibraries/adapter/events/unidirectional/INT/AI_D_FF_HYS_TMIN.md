# AI_D_FF_HYS_TMIN


![AI_D_FF_HYS_TMIN](./AI_D_FF_HYS_TMIN.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AI_D_FF_HYS_TMIN** realisiert ein Data-Latch (D-Flipflop) mit einem Hystereseband und einer Mindestzeit zwischen aufeinanderfolgenden Ereignisausgängen. Er dient als robuste Signalverarbeitungskomponente, die Störungen und schnelle Flankenwechsel unterdrückt und nur stabile Zustandsänderungen weitergibt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| INIT     | EInit | Initialisierungsanforderung (setzt Hystereseband und Tmin) |

### **Ereignis-Ausgänge**
| Ereignis | Typ | Kommentar |
|----------|-----|-----------|
| INITO    | EInit | Initialisierungsbestätigung |

### **Daten-Eingänge**
| Variable     | Typ   | Kommentar |
|--------------|-------|-----------|
| HYSTERESIS   | INT   | Hystereseband (Wert in derselben Einheit wie das Eingangssignal) |
| Tmin         | TIME  | Mindestzeit zwischen zwei Ereignisausgängen (E1 am Q-Adapter) |

### **Daten-Ausgänge**
Der Baustein besitzt keine eigenen Datenausgänge. Der latched Wert wird über den Ausgangsadapter **Q** bereitgestellt.

### **Adapter**
| Adapter | Typ | Kommentar |
|---------|-----|-----------|
| **I**   | adapter::types::unidirectional::AI | Eingangsadapter: liefert das zu verarbeitende Signal (über Ereignis E1 und Daten D1) |
| **Q**   | adapter::types::unidirectional::AI | Ausgangsadapter: gibt den latched Wert aus (über Ereignis E1 und Daten D1) |

## Funktionsweise
Der Baustein verwendet intern das Unterprogramm **E_D_FF_ANY_HYS_TMIN** aus der Bibliothek *logiBUS::signalprocessing::hysteresis*. Die Funktionsweise im Überblick:

1. **Initialisierung**  
   Über den Ereigniseingang **INIT** werden die Parameter `HYSTERESIS` und `Tmin` übernommen. Nach erfolgreicher Initialisierung wird **INITO** gesendet.

2. **Signalverarbeitung**  
   - Ein neuer Wert wird über den Adapter **I** (Ereignis **E1** mit zugehörigem Datenwert **D1**) empfangen.
   - Der Baustein vergleicht den neuen Wert mit dem aktuell gespeicherten (latched) Wert unter Berücksichtigung des Hysteresebandes:  
     - Eine Änderung wird nur dann übernommen, wenn die Differenz zwischen neuem Wert und altem Wert größer als `HYSTERESIS` ist.
   - Zusätzlich muss die seit dem letzten Ereignisausgang verstrichene Zeit mindestens `Tmin` betragen. Erst wenn beide Bedingungen erfüllt sind, wird der neue Wert übernommen und über den Adapter **Q** (Ereignis **E1** und Daten **D1**) ausgegeben.

3. **Ausgang**  
   Der aktuell gültige latched Wert wird über den **Q**-Adapter bereitgestellt. Bei jeder gültigen Zustandsänderung wird ein Ereignis an **Q.E1** gesendet.

## Technische Besonderheiten
- **Hysterese** – Unterdrückt Rauschen und schnelle Schwankungen, indem eine Änderung nur dann akzeptiert wird, wenn sie das Hystereseband überschreitet.
- **Mindestzeit zwischen Ereignissen (Tmin)** – Verhindert zu häufige Ausgaben (z. B. durch hochfrequente Signale oder Prellen). Ereignisse werden erst nach Ablauf von `Tmin` seit dem letzten Ereignis freigegeben.
- **Adapterbasierte Schnittstelle** – Die Ein- und Ausgabe erfolgt über Unidirectional-Adapters, was eine flexible Kopplung mit anderen Komponenten erlaubt.

## Zustandsübersicht
Der Baustein besitzt keine expliziten benannten Zustände. Das interne Flipflop arbeitet als bistabiles Element mit zwei stabilen Zuständen (hoch/niedrig oder dem letzten gültigen Wert). Die Zustandsübergänge werden durch die Hysterese- und Zeitbedingungen kontrolliert.

## Anwendungsszenarien
- **Entprellung von Sensorwerten** – Glättung analoger oder digitaler Eingangssignale (z. B. Temperatur, Druck, Füllstand) bei Schwellwertüberschreitungen.
- **Filterung von Rauschspitzen** – Vermeidung von Fehlauslösungen durch kurzzeitige Störungen.
- **Zeitgesteuerte Signalüberwachung** – Wenn Änderungen nur in bestimmten Zeitabständen gemeldet werden sollen (z. B. für Logging oder Aktualisierungsraten).
- **Schnittstellenentkopplung** – Verwendung als stabilisierte Zwischenstufe zwischen einem schnellen Signalgeber und einer trägen Aktorik.

## Vergleich mit ähnlichen Bausteinen
| Baustein | Wesentlicher Unterschied |
|----------|--------------------------|
| **E_D_FF** (einfaches D-Flipflop) | Kein Hystereseband, keine Mindestzeit – übernimmt jede Änderung sofort. |
| **AI_D_FF_HYS** (ohne Tmin) | Enthält Hysterese, jedoch keine zeitliche Begrenzung der Ausgabe. |
| **AI_D_FF_TMIN** (ohne Hysterese) | Enthält nur die Mindestzeit, aber keine Hysterese. |
| **AI_D_FF_HYS_TMIN** (dieser) | Kombiniert beide Filter: Hysterese und zeitliche Begrenzung. |

## Fazit
Der **AI_D_FF_HYS_TMIN** ist ein vielseitiger Funktionsblock zur robusten Signalaufbereitung. Seine Kombination aus Hysterese und Mindestintervall macht ihn ideal für Anwendungen, die sowohl störungssichere als auch zeitlich kontrollierte Zustandsänderungen erfordern. Die adapterbasierte Anbindung erleichtert die Integration in modulare Automatisierungssysteme.