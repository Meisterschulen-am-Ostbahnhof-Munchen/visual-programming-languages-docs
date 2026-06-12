# AI_DEMUX_5


![AI_DEMUX_5](./AI_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AI_DEMUX_5** ist ein generischer Analog-Eingangs-Demultiplexer für die 4diac-IDE. Er verteilt einen über einen Adapter eingehenden AI-Wert (Analog Input) auf einen von fünf Ausgangsadaptern, gesteuert durch einen ganzzahligen Index K. Der FB ist als unidirektionaler Adapter-Baustein realisiert und ermöglicht die flexible Weiterleitung von analogen Signalen in Steuerungsanwendungen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K |

Der Ereigniseingang **REQ** löst die Demultiplex-Funktion aus. Mit diesem Ereignis wird der Index K übernommen und die Weiterleitung des aktuellen Eingangswerts an den entsprechenden Ausgang angestoßen.

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Confirmation of Set Index K |

Das Ereignis **CNF** wird nach erfolgreicher Verteilung des Wertes ausgegeben und bestätigt die Ausführung des REQ-Ereignisses.

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | index |

Der Daten-Eingang **K** bestimmt den Zielausgang (1..5), an den der vom IN-Adapter stammende Wert weitergeleitet wird. Werte außerhalb dieses Bereichs werden typischerweise ignoriert oder führen zu einer Fehlerbehandlung (nicht näher spezifiziert).

### **Daten-Ausgänge**

Es sind keine direkten Datenausgänge vorhanden. Die Ausgabe erfolgt ausschließlich über die Adapter-Schnittstellen.

### **Adapter**

| Rolle | Name | Typ | Kommentar |
|-------|------|-----|-----------|
| Socket | IN | adapter::types::unidirectional::AI | Input Value to demultiplex |
| Plug  | OUT1 | adapter::types::unidirectional::AI | – |
| Plug  | OUT2 | adapter::types::unidirectional::AI | – |
| Plug  | OUT3 | adapter::types::unidirectional::AI | – |
| Plug  | OUT4 | adapter::types::unidirectional::AI | – |
| Plug  | OUT5 | adapter::types::unidirectional::AI | – |

Der **IN**-Socket nimmt den zu verteilenden Analogwert entgegen. Die fünf Plugs **OUT1** bis **OUT5** stellen die möglichen Zielausgänge dar, über die der Wert ausgegeben wird.

## Funktionsweise

Bei jedem REQ-Ereignis wird der aktuelle Wert des Index K ausgelesen. Der am IN-Adapter anliegende AI-Wert wird dann unverändert an den durch K bezeichneten OUT-Plug weitergegeben (z. B. K=1 → OUT1, K=2 → OUT2, usw.). Die übrigen vier Ausgänge bleiben unverändert oder werden auf einen definierten Grundzustand (z. B. Nullwert) gesetzt – dies ist abhängig von der konkreten Implementierung des generischen FB. Nach Abschluss der Weiterleitung wird das CNF-Ereignis ausgelöst. Die Funktion ist rein kombinatorisch; es gibt keine internen Speicher oder Zustände.

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist als generischer Typ (`eclipse4diac::core::GenericClassName = 'GEN_AI_DEMUX'`) deklariert, was eine einfache Parametrierung oder Wiederverwendung in verschiedenen Projekten ermöglicht.
- **Unidirektionale Adapter:** Die Schnittstellen IN und OUT1..OUT5 sind als unidirektionale AI-Adapter ausgeführt, d. h. sie erlauben Datenfluss nur in eine Richtung (vom Socket zum Plug). Dies vereinfacht die Verdrahtung in hierarchischen Strukturen.
- **Keine Datenausgänge:** Der FB verzichtet auf klassische Datenausgänge und nutzt ausschließlich Adapter für die Wertübergabe, was eine modulare Kapselung der analogen Signale fördert.

## Zustandsübersicht

Der Funktionsblock besitzt keinen internen Zustandsautomaten. Die Demultiplex-Funktion wird bei jedem REQ-Ereignis direkt ausgeführt. Es gibt keine Abhängigkeiten von vorherigen Aufrufen, außer dass der Index K zum Zeitpunkt des REQ gültig sein muss.

## Anwendungsszenarien

- **Signalrouting in der Automatisierung:** Ein analoger Sensorwert (z. B. Temperatur, Druck) soll abhängig von einer Auswahl (z. B. Produkttyp) an verschiedene weitere Funktionsblöcke zur Verarbeitung oder Protokollierung weitergeleitet werden.
- **Mehrkanal-Messsysteme:** Verteilung eines einkommenden AI-Werts auf unterschiedliche Pfade (z. B. Regelung, Überwachung, Archivierung) ohne mehrfache Verkabelung.
- **Test- und Simulationsumgebungen:** Umschalten zwischen verschiedenen Simulationsdatenquellen durch Ändern des Index K.

## Vergleich mit ähnlichen Bausteinen

Ein **MUX** (Multiplexer) führt die umgekehrte Funktion aus – mehrere Eingänge werden auf einen Ausgang geschaltet. Der **AI_DEMUX_5** ist ein Demultiplexer mit fest fünf Ausgängen. Im Gegensatz zu einem generischen, parametrierbaren DEMUX (z. B. mit variabler Anzahl an Ausgängen) ist die Anzahl hier auf fünf festgelegt, was eine klare Schnittstelle für typische Anwendungen mit bis zu fünf Zielen bietet. Gegenüber einem manuellen, kaskadierten Aufbau mit mehreren 1-zu-2-Demultiplexern reduziert dieser FB die Komplexität und erhöht die Übersichtlichkeit.

## Fazit

Der **AI_DEMUX_5** ist ein kompakter, generischer Demultiplexer für analoge Eingangssignale in der 4diac-IDE. Mit seiner einfachen Ereignissteuerung, dem Index-K-Eingang und der Adapter-basierten Schnittstelle eignet er sich ideal für das Routing von AI-Werten in modularen Steuerungsanwendungen. Die feste Anzahl von fünf Ausgängen deckt viele praktische Anforderungen ab, während die generische Implementierung eine flexible Wiederverwendung ermöglicht.