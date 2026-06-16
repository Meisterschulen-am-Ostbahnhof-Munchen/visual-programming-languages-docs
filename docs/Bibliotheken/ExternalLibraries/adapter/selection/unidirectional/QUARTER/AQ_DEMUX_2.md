# AQ_DEMUX_2


![AQ_DEMUX_2](./AQ_DEMUX_2.svg)

* * * * * * * * * *
## Einleitung
Der **AQ_DEMUX_2** ist ein generischer Funktionsbaustein, der als Demultiplexer für analoge Werte (AQ – Analog Quantity) fungiert. Er verteilt einen eingehenden AQ-Wert auf einen von zwei möglichen Ausgangsadaptern, gesteuert durch einen Index. Der Baustein ist als generischer FB (Generic FB) ausgelegt und ermöglicht eine flexible Wiederverwendung in verschiedenen Anwendungskontexten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Auslöser zum Setzen des Index K und Weiterleitung des Werts. Verbunden mit dem Daten-Eingang K. |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Bestätigung, dass der Index K gesetzt und der Wert weitergeleitet wurde. |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index zur Auswahl des Ausgangs (1 → OUT1, 2 → OUT2). |

### **Daten-Ausgänge**
Der Baustein besitzt keine direkten Daten-Ausgänge. Die Ausgaben erfolgen über die Adapter-Schnittstellen.

### **Adapter**

| Typ | Richtung | Name | Kommentar |
|-----|----------|------|-----------|
| adapter::types::unidirectional::AQ | Eingang (Socket) | IN | Eingangswert, der demultiplext werden soll. |
| adapter::types::unidirectional::AQ | Ausgang (Plug) | OUT1 | Erster Ausgangskanal (Index 1). |
| adapter::types::unidirectional::AQ | Ausgang (Plug) | OUT2 | Zweiter Ausgangskanal (Index 2). |

## Funktionsweise
Beim Eintreffen eines **REQ**-Ereignisses wird der Wert des Daten-Eingangs **K** ausgewertet:
- Ist **K = 1**, so wird der aktuelle Wert des Adapter-Sockets **IN** auf den Adapter-Plug **OUT1** weitergeleitet.
- Ist **K = 2**, erfolgt die Weiterleitung auf **OUT2**.
- Für andere Werte von **K** bleibt der Baustein inaktiv oder der Wert wird ignoriert (je nach Implementierung). Anschließend wird das **CNF**-Ereignis ausgegeben, um den erfolgreichen Abschluss zu signalisieren.

Die Weiterleitung erfolgt ereignisgesteuert und ohne interne Zwischenspeicherung – der Wert wird direkt vom Eingangsadapter auf den ausgewählten Ausgangsadapter kopiert.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als Generic FB definiert (`GEN_AQ_DEMUX`), sodass er für unterschiedliche analoge Datentypen instanziiert werden kann, solange die Adapter-Schnittstelle das Protokoll `unidirectional::AQ` unterstützt.
- **Adapterbasierte Kommunikation**: Anstelle klassischer Datenports werden Adapter verwendet. Dies ermöglicht eine lose Kopplung und den Austausch komplexer Datenstrukturen zwischen Bausteinen.
- **Einfache Indexsteuerung**: Der Index **K** ist vom Typ `UINT` und legt fest, welcher Ausgang aktiv wird. Die Beschränkung auf zwei Ausgänge ist fest verdrahtet („_2“ im Namen).
- **Keine Datenkopplung am CNF-Ereignis**: Das Bestätigungsereignis CNF hat keine verbundenen Daten – es dient lediglich zur Synchronisation.

## Zustandsübersicht
Der Baustein besitzt keinen expliziten Zustandsautomaten. Die interne Logik lässt sich als einfache Folge beschreiben:
1. **Warten auf REQ** (Idle-Zustand)
2. **Auswerten von K** und **Weiterleiten des IN-Werts** an den entsprechenden Plug
3. **Senden von CNF** und Rückkehr in den Idle-Zustand

Ein wiederholtes REQ-Ereignis führt jedes Mal eine neue Weiterleitung durch, unabhängig vom vorherigen Index.

## Anwendungsszenarien
- **Verteilen eines analogen Sollwerts** auf verschiedene Aktoren (z. B. Ventile, Antriebe) in einer Fertigungsanlage.
- **Steuerung von zwei parallelen Prozesszweigen** mit einem gemeinsamen Messwert, der je nach Index an unterschiedliche Regelkreise weitergegeben wird.
- **Umschaltung zwischen zwei Betriebsarten** in einer adaptiven Steuerung, bei der ein analoger Eingang auf zwei verschiedene Ausgänge geschaltet wird.

## Vergleich mit ähnlichen Bausteinen
- **AQ_MUX**: Der Multiplexer-Gegenstück – er wählt einen von mehreren analogen Eingängen aus und gibt ihn an einen einzigen Ausgang weiter.
- **DATA_DEMUX**: Ein allgemeiner Daten-Demultiplexer, der jedoch oft mit primitiven Datentypen (z. B. INT, REAL) arbeitet und keine Adapter verwendet.
- **AQ_DEMUX_N**: Eine erweiterte Version mit mehr als zwei Ausgängen. Der AQ_DEMUX_2 stellt die einfachste Realisierung dar.

Gegenüber einem reinen Daten-Demultiplexer bietet der AQ_DEMUX_2 Vorteile durch die Adapter-Schnittstelle, die eine standardisierte Übertragung analoger Werte mit optionalen Zusatzinformationen (z. B. Einheit, Status) ermöglicht.

## Fazit
Der **AQ_DEMUX_2** ist ein spezialisierter, aber flexibler Funktionsbaustein zur Verteilung analoger Werte auf zwei Ausgänge. Sein generischer Charakter und die Adapter-basierte Kommunikation machen ihn zu einem wertvollen Element in der Automatisierungstechnik, insbesondere in Szenarien mit ereignisgesteuerter Kanalauswahl. Die einfache Schnittstelle und die klare Trennung von Ereignis- und Datenlogik erleichtern die Integration in komplexe Steuerungsprojekte.