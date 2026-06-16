# AUS_D_FF_TMIN


![AUS_D_FF_TMIN](./AUS_D_FF_TMIN.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUS_D_FF_TMIN** realisiert ein taktgesteuertes D‑Latch (Data Flip‑Flop) mit einer minimalen Wartezeit zwischen zwei aufeinanderfolgenden Ausgabe‑Ereignissen (Minimum inter‑disposal Time between EO). Er eignet sich besonders für Anwendungen, bei denen ein eingehender Wert (über einen Adapter‑Socket) übernommen und erst nach Ablauf einer einstellbaren Mindestzeit wieder ausgegeben werden darf. Die Initialisierung erfolgt über den Standard‑Ereigniseingang **INIT**.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar | Mit Variable |
|------|-----|-----------|--------------|
| INIT | EInit | Init Request | Tmin |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| INITO | EInit | Init Confirmation |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| HYSTERESIS | ANY_NUM | Hysterese‑Band (derzeit nicht im internen Netzwerk verbunden) |
| Tmin | TIME | Minimale Zeitspanne zwischen zwei EO‑Ereignissen |

### **Daten-Ausgänge**
Keine direkten Daten‑Ausgänge – die Ausgabedaten werden ausschließlich über den **Adapter‑Plug Q** bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Kommentar |
|----------|------|-----|-----------|
| Socket | I | adapter::types::unidirectional::AUS | Wert, der übernommen werden soll (enthält Ereignis E1 und Daten D1) |
| Plug | Q | adapter::types::unidirectional::AUS | Gelatchter Ausgabewert (enthält Ereignis E1 und Daten D1) |

## Funktionsweise
Der Baustein enthält intern einen vorgefertigten FB **E_D_FF_ANY_TMIN** (aus der Bibliothek `iec61499::events`). Dieser übernimmt bei jedem eingehenden Ereignis auf dem Clock‑Eingang den momentanen Datenwert und gibt ihn am Ausgang weiter – jedoch nur, wenn die seit dem letzten Ausgabe‑Ereignis vergangene Zeit mindestens **Tmin** beträgt.  

- Beim **INIT**‑Ereignis wird der Parameter *Tmin* an den internen FB übergeben.  
- Ein Ereignis auf **I.E1** (Adapter‑Socket) wirkt als Takt für den internen Flip‑Flop.  
- Der gelatchte Datenwert erscheint auf **Q.D1** (Adapter‑Plug) und wird gleichzeitig mit einem Ereignis auf **Q.E1** quittiert – sofern die Zeitbedingung erfüllt ist.  
- Der Parameter **HYSTERESIS** ist zwar deklariert, wird im aktuellen Netzwerk aber nicht verwendet. Er kann für zukünftige Erweiterungen oder für manuelle Verdrahtung genutzt werden.

## Technische Besonderheiten
- **Mindestzeit zwischen Ausgaben**: Die Ausgabe des gelatchten Werts wird erst dann freigegeben, wenn die seit dem letzten **EO** vergangene Zeit ≥ *Tmin* ist. Dies verhindert eine zu hohe Ereignisrate am Ausgang.  
- **Adapter‑Schnittstelle**: Ein‑ und Ausgang sind als unidirektionale Adapter vom Typ **AUS** realisiert, sodass der Baustein leicht in bestehende Adapter‑basierte Architekturen eingefügt werden kann.  
- **Hysterese‑Parameter**: Obwohl nicht direkt verdrahtet, steht der Eingang *HYSTERESIS* zur Verfügung – beispielsweise zur Realisierung eines Schmitt‑Trigger‑ähnlichen Verhaltens bei späteren Versionen.

## Zustandsübersicht
Der interne FB **E_D_FF_ANY_TMIN** besitzt einen Speicher für den zuletzt übernommenen Datenwert. Dieser Zustand wird bei jedem Clock‑Ereignis (I.E1) aktualisiert. Eine explizite Zustandsmaschine ist auf der oberen Ebene nicht vorhanden; das Verhalten ergibt sich aus der Logik des unterlagerten Flip‑Flops.

## Anwendungsszenarien
- **Sensorwert‑Entprellung**: Ein‑ und Ausschaltschwellen mit minimaler Wiederholrate.  
- **Datenpuffer mit Ausgabebegrenzung**: Verhindert das Überschwemmen nachgeschalteter Verbraucher mit zu vielen Aktualisierungen.  
- **Zeitgesteuerte Latch‑Funktion**: Übernahme eines Wertes nur dann, wenn die letzte Ausgabe länger als *Tmin* zurückliegt.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaften |
|----------|---------------|
| **E_D_FF** (einfaches D‑Flip‑Flop) | Übernimmt Wert sofort bei jedem Takt, keine Zeitsteuerung. |
| **AUS_D_FF_TMIN** | Wie **E_D_FF**, aber mit zusätzlicher Mindestzeit zwischen den Ausgabeereignissen. |
| **R_TRIG / F_TRIG** | Erkennen Flanken, speichern aber keinen Datenwert. |

Der **AUS_D_FF_TMIN** eignet sich daher speziell für zeitkritische Anwendungen, bei denen eine minimale Abtast‑ oder Aktualisierungsrate eingehalten werden muss.

## Fazit
Der **AUS_D_FF_TMIN** ist ein nützlicher Erweiterungsbaustein für das D‑Flip‑Flop um eine zeitliche Entkopplung der Ausgabe. Dank der Adapter‑Schnittstelle und der einfachen Konfiguration über **Tmin** lässt er sich flexibel in IEC‑61499‑Systeme integrieren. Der vorhandene, aber ungenutzte **HYSTERESIS**‑Eingang bietet Potenzial für künftige Funktionserweiterungen.