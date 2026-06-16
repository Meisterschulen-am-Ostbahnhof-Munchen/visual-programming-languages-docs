# AIWS_DEMUX_2


![AIWS_DEMUX_2](./AIWS_DEMUX_2.svg)

* * * * * * * * * *
## Einleitung
Der **AIWS_DEMUX_2** ist ein generischer Demultiplexer-Funktionsblock für das AIWS-Protokoll. Er leitet einen eingehenden AIWS-Datenstrom an einen von zwei Ausgängen weiter, gesteuert durch einen Index. Der Baustein ist ereignisgesteuert und arbeitet unidirektional.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Setzt den Index K und startet die Weiterleitung |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigt die Verarbeitung des Index |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index, der den Zielausgang bestimmt (z. B. 0 → OUT1, 1 → OUT2) |

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Typ | Name | Richtung | Kommentar |
|-----|------|----------|-----------|
| AIWS (unidirectional) | IN | Socket (Eingang) | Eingangsdatenstrom, der demultiplext werden soll |
| AIWS (unidirectional) | OUT1 | Plug (Ausgang) | Erster Zielausgang |
| AIWS (unidirectional) | OUT2 | Plug (Ausgang) | Zweiter Zielausgang |

## Funktionsweise
Der Baustein wartet auf ein **REQ**-Ereignis. Beim Eintreffen wird der Wert des Daten-Eingangs **K** ausgewertet:
- Ist `K = 0`, werden die aktuellen Daten des **IN**-Adapters an den **OUT1**-Adapter weitergegeben.
- Ist `K = 1`, werden die Daten an **OUT2** weitergegeben.
- Für andere Werte von K (falls vorhanden) bleibt die Ausgabe unverändert (oder es wird ein Fehlerzustand angenommen – je nach Implementierung).

Nach erfolgreicher Weiterleitung wird das Ereignis **CNF** ausgegeben. Der Baustein arbeitet streng sequenziell und blockiert während der Verarbeitung keine weiteren REQ-Ereignisse.

## Technische Besonderheiten
- **Generischer Typ**: Der FB ist als generischer Funktionsblock deklariert (`GenericClassName = 'GEN_AIWS_DEMUX'`), sodass er für verschiedene Ausgangsanzahlen parametriert werden kann. Die konkrete Ausprägung `AIWS_DEMUX_2` besitzt zwei Ausgänge.
- **Adapter-basiert**: Die Schnittstellen sind über Adapter vom Typ `adapter::types::unidirectional::AIWS` realisiert, was eine saubere Trennung von Steuerungs- und Datenfluss ermöglicht.
- **Ereignisgesteuerte Verarbeitung**: Die Demultiplexing-Operation wird nur durch das REQ-Ereignis ausgelöst; ohne Ereignis bleiben alle Ausgänge unverändert.
- **Keine Daten-Ausgänge**: Die Ausgabe erfolgt ausschließlich über die Adapter-Plugs; es gibt keine separaten Daten-Variablen.

## Zustandsübersicht
Der FB besitzt eine einfache Zustandslogik (im ECC nicht explizit dargestellt, aber implizit):
- **IDLE**: Warten auf ein REQ-Ereignis.
- **PROCESS**: Auswerten von K und Weiterleiten der Daten an den entsprechenden OUT-Adapter.
- **DONE**: Senden des CNF-Ereignisses und Rückkehr in den IDLE-Zustand.

Fehlerzustände (z. B. ungültiger Index) können in der Implementierung optional durch ein Fehler-Ereignis abgebildet werden, sind aber im vorliegenden Interface nicht definiert.

## Anwendungsszenarien
- **Sensorwerte-Verteilung**: Ein analoger Sensor (z. B. AIWS-konformer Temperaturfühler) liefert Daten, die je nach Index an verschiedene Aktoren oder Steuerungen weitergeleitet werden.
- **Kanalselektion**: In einer Steuerung können zwei verschiedene Regelungspfade bedient werden, z. B. für Heizung und Kühlung.
- **Umschaltung zwischen Betriebsarten**: Der Index K kann aus einem übergeordneten Zustandsautomaten kommen und die Daten an den gerade aktiven Teilprozess senden.

## Vergleich mit ähnlichen Bausteinen
- **AIWS_DEMUX_N**: Generalisierte Variante mit N Ausgängen – dieser FB ist eine spezielle Ausprägung mit zwei Ausgängen.
- **Standard-DEMUX (z. B. für ANY-Datentypen)**: Nutzen oft Daten-Eingänge und -Ausgänge statt Adapter; der Adapter-Ansatz kapselt das Protokoll und erleichtert die Wiederverwendung.
- **AIWS-Splitter**: Im Gegensatz zu einem Splitter (der Daten an alle Ausgänge gleichzeitig sendet) wählt der Demultiplexer gezielt einen Pfad aus.

## Fazit
Der **AIWS_DEMUX_2** ist ein kompakter, ereignisgesteuerter Demultiplexer für AIWS-Protokolldaten. Er eignet sich hervorragend für Anwendungen, bei denen ein Datenstrom bedarfsgerecht an eines von zwei Zielen weitergeleitet werden muss. Die generische Basis erlaubt eine einfache Erweiterung auf mehr Kanäle, ohne das Interface grundlegend ändern zu müssen.