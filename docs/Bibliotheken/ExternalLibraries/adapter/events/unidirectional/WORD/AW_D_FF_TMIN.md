# AW_D_FF_TMIN

(Bild des Funktionsblocks – in der XML nicht enthalten, daher kein Bild)


![AW_D_FF_TMIN](./AW_D_FF_TMIN.svg)

* * * * * * * * * *

## Einleitung

Der **AW_D_FF_TMIN** ist ein komponierter IEC 61499‑Funktionsblock (Typ eines Daten‑Latch‑Flipflops), der einen eingehenden Datenwert auf einem Adapter empfängt, bei einem Ereignis übernimmt und auf einem Ausgangsadapter mit einer minimalen Verzögerungszeit zwischen zwei aufeinanderfolgenden Ausgabeereignissen weitergibt. Er dient als zuverlässiger Zwischenspeicher, der die Ausgabe‑Ereignisse auf eine durch den Parameter `Tmin` definierte Mindestzeit streckt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Typ   | Kommentar |
|----------|-------|-----------|
| `INIT`   | EInit | Initialisierungsanforderung; legt die minimale Inter‑Event‑Zeit `Tmin` fest. |

### **Ereignis-Ausgänge**

| Ereignis | Typ   | Kommentar |
|----------|-------|-----------|
| `INITO`  | EInit | Bestätigung der erfolgreichen Initialisierung. |

### **Daten-Eingänge**

| Daten | Typ   | Kommentar |
|-------|-------|-----------|
| `Tmin` | TIME | Minimale Zeit (z. B. `T#100ms`), die zwischen zwei aufeinanderfolgenden Ausgabeereignissen (`Q.E1`) mindestens vergehen muss. |

### **Daten-Ausgänge**

Der FB besitzt keine direkten Datenausgänge; der latchende Wert wird über den Adapter `Q` bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| `Socket` | `I`  | `adapter::types::unidirectional::AW` | Wert, der gelatcht werden soll (Eingangsadapter). Enthält die Ereignis‑ und Datenschnittstellen `I.E1` und `I.D1`. |
| `Plug`   | `Q`  | `adapter::types::unidirectional::AW` | Latched Wert (Ausgangsadapter). Enthält die Ereignis‑ und Datenschnittstellen `Q.E1` und `Q.D1`. |

## Funktionsweise

Der **AW_D_FF_TMIN** kapselt den IEC‑61499‑Standardfunktionsblock `E_D_FF_ANY_TMIN`. Die Arbeitsweise ist wie folgt:

1. **Initialisierung**  
   Über den Ereigniseingang `INIT` wird der Parameter `Tmin` an den inneren FB übergeben. Nach erfolgreicher Initialisierung wird `INITO` ausgegeben.

2. **Daten‑Latching**  
   Trifft am Adapter‑Eingang `I.E1` ein Ereignis ein, wird der gleichzeitig an `I.D1` anliegende Datenwert übernommen (flankengesteuertes D‑Flipflop).

3. **Ausgabe mit Mindestzeit**  
   Der gelatchte Wert wird am Adapter‑Ausgang `Q.D1` ausgegeben. Gleichzeitig wird ein Ereignis auf `Q.E1` erzeugt – jedoch nur, wenn seit dem letzten Ereignis auf `Q.E1` mindestens die Zeit `Tmin` vergangen ist. Dadurch wird sichergestellt, dass die Ausgangsereignisse nicht schneller als durch `Tmin` erlaubt aufeinander folgen.

4. **Weitere Zyklen**  
   Jedes neue Ereignis auf `I.E1` wiederholt das Latching und die zeitgesteuerte Ausgabe.

## Technische Besonderheiten

- Der Funktionsblock ist nach IEC 61499‑1 Annex A spezifiziert und verwendet die Adapter‑Typdefinition `adapter::types::unidirectional::AW`.
- Die Implementierung basiert auf dem reproduzierbaren Baustein `E_D_FF_ANY_TMIN`, der die eigentliche Latch‑ und Timing‑Logik bereitstellt.
- Die minimale Inter‑Event‑Zeit `Tmin` wird zur Laufzeit über `INIT` gesetzt und kann nicht während des Betriebs geändert werden.
- Der Baustein ist unter der Eclipse Public License 2.0 (EPL‑2.0) veröffentlicht, Version 1.0 (2026‑05‑15, HR Agrartechnik GmbH).

## Zustandsübersicht

Der interne FB `E_D_FF_ANY_TMIN` besitzt einen impliziten Zustandsautomaten:

- **Initialisierungszustand**: Nach `INIT` wird die Konfiguration übernommen; bei Erfolg wird `INITO` gesendet.
- **Betriebszustand**: Nach der Initialisierung wartet der FB auf Ereignisse an `I.E1`. Bei jedem Ereignis wird der Datenwert gelatcht, die Timer‑Überwachung gestartet und die Ausgabe nur dann freigegeben, wenn die Mindestzeit `Tmin` seit dem letzten Ausgangsereignis abgelaufen ist.
- **Warte‑Zustand**: Falls ein Ausgangsereignis noch nicht freigegeben werden darf (weil die Zeit seit dem letzten Ereignis kleiner als `Tmin` ist), wird der gelatchte Wert zurückgehalten, bis die geforderte Verzögerung abgelaufen ist. Erst dann wird `Q.E1` ausgelöst.

## Anwendungsszenarien

- **Signalentprellung**: Verhindert, dass mechanische oder kommunikationsbedingte Preller in schneller Folge auf einen nachgeschalteten Prozess wirken.
- **Taktsteuerung mit Mindestpulsdauer**: Sicherstellung, dass nachfolgende Bausteine eine Mindestzeit zwischen zwei Verarbeitungsschritten erhalten.
- **Synchronisation von Datenströmen**: Puffert einen Datenwert und gibt ihn mit einer definierten Mindestverzögerung weiter, um Jitter zu glätten.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft | Unterschied |
|----------|-------------|-------------|
| `E_D_FF` | Einfaches D‑Flipflop ohne Zeitbegrenzung | Fehlende Kontrolle über die maximale Ausgabefrequenz. |
| `SR_FF` | Set‑Reset‑Flipflop | Keine flankengesteuerte Datenübernahme. |
| `E_D_FF_ANY_TMIN` (direkt) | Wie AW_D_FF_TMIN, aber reiner Ereignis‑/Daten‑FB | Besitzt kein Adapter‑Interface; die Variante mit Adapter erhöht die Austauschbarkeit und Kapselung in steckbaren Komponenten. |

## Fazit

Der **AW_D_FF_TMIN** ist ein wartungsfreundlicher, adapterbasierter D‑Latch‑Baustein, der die Übernahme eines Datenwerts mit einer konfigurierbaren Mindestzeit zwischen Ausgabeereignissen kombiniert. Durch die Verwendung eines standardisierten Adapter‑Typs kann er leicht in hierarchische Module eingebunden werden und bietet eine robuste Lösung für zeitkritische Signalketten in IEC‑61499‑Systemen.