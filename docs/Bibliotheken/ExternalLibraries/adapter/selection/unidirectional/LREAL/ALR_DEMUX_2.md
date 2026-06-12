# ALR_DEMUX_2


![ALR_DEMUX_2](./ALR_DEMUX_2.svg)

* * * * * * * * * *
## Einleitung
Der ALR_DEMUX_2 ist ein generischer Demultiplexer-Baustein für ALR-Daten. Er leitet einen eingehenden ALR-Wert, der über den Socket IN bereitgestellt wird, basierend auf einem Index K an einen der beiden Ausgangsadapter OUT1 oder OUT2 weiter. Das Umschalten erfolgt durch das Ereignis REQ.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
- **REQ** : Löst die Weiterleitung aus. Der Index K wird ausgewertet.

### **Ereignis-Ausgänge**
- **CNF** : Bestätigt die erfolgreiche Verarbeitung des REQ-Ereignisses.

### **Daten-Eingänge**
- **K** (UINT) : Index, der angibt, an welchen Ausgang der Wert weitergeleitet werden soll (z. B. 0 für OUT1, 1 für OUT2).

### **Daten-Ausgänge**
Keine direkten Datenausgänge. Die Ausgabe erfolgt über die Adapter OUT1 und OUT2.

### **Adapter**
- **IN** (Socket, Typ: `adapter::types::unidirectional::ALR`) : Eingangsadapter für den zu demultiplexenden ALR-Wert.
- **OUT1** (Plug, Typ: `adapter::types::unidirectional::ALR`) : Erster Ausgangsadapter.
- **OUT2** (Plug, Typ: `adapter::types::unidirectional::ALR`) : Zweiter Ausgangsadapter.

## Funktionsweise
Der Baustein arbeitet ereignisgesteuert. Bei einem REQ-Ereignis wird der aktuelle Wert des Eingangs K gelesen. Abhängig von K wird der IN‑Adapater mit OUT1 (z. B. bei K=0) oder mit OUT2 (bei K=1) verbunden. Anschließend wird das CNF-Ereignis ausgegeben. Der Baustein ist zustandslos; jede Anforderung führt zu einer sofortigen Neuverbindung.

## Technische Besonderheiten
- Der Baustein ist als generischer Funktionsblock deklariert (GenericClassName "GEN_ALR_DEMUX"), was eine flexible Wiederverwendung in verschiedenen Kontexten ermöglicht.
- Er verwendet den benutzerdefinierten Adaptertyp `adapter::types::unidirectional::ALR`.
- Der Baustein wird unter der Eclipse Public License 2.0 bereitgestellt (SPDX‑Lizenzidentifikator: EPL‑2.0).
- Es sind keine internen Zustände oder Algorithmen in der XML definiert; die Logik wird durch die 4diac‑IDE oder das Laufzeitsystem implementiert.

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine. Die Funktionalität lässt sich als einfacher Schalter ohne Gedächtnis beschreiben. Nachdem ein REQ verarbeitet wurde, bleibt die Verbindung bis zur nächsten Anforderung bestehen.

## Anwendungsszenarien
- Aufteilung eines ALR-Datenstroms auf zwei verschiedene Verarbeitungspfade in einer Automatisierungsanwendung.
- Umschalten zwischen zwei Sensoren oder Aktoren, die über das ALR-Protokoll kommunizieren.
- Test- und Diagnosezwecke, um einen Datenpfad temporär umzuleiten.

## Vergleich mit ähnlichen Bausteinen
- **ALR_DEMUX_2** ist spezifisch für ALR-Daten. Ein allgemeiner Demultiplexer (z. B. mit ANY‑Datentyp) wäre flexibler, aber nicht auf ALR optimiert.
- Ein Multiplexer (ALR_MUX) würde die umgekehrte Funktion ausführen: mehrere Eingänge auf einen Ausgang zusammenführen.
- Der Baustein ähnelt einem 1‑zu‑2‑Demultiplexer in der Digitaltechnik, jedoch auf Adapterebene.

## Fazit
Der ALR_DEMUX_2 ist ein nützlicher, einfacher Demultiplexer für ALR‑Daten. Seine klare Schnittstelle und die ereignisgesteuerte Arbeitsweise machen ihn gut geeignet für Anwendungen, die eine gezielte Weiterschaltung von ALR‑Verbindungen erfordern. Durch die generische Deklaration ist eine problemlose Integration in bestehende 4diac‑Projekte möglich.