# AUDI_MUX_5


![AUDI_MUX_5](./AUDI_MUX_5.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AUDI_MUX_5** ist ein generischer Multiplexer, der es ermöglicht, abhängig von einem Indexwert (K) einen von fünf gleichartigen Eingängen (IN1 bis IN5) auf einen Ausgang (OUT) durchzuschalten. Der Baustein wurde für die Verwendung mit dem Adaptertyp `adapter::types::unidirectional::AUDI` konzipiert und ist Bestandteil der HR Agrartechnik GmbH Bibliothek. Die Auswahl des aktiven Eingangs wird über das Ereignis REQ angestoßen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **REQ** – Setzt den Index K und triggert die Durchschaltung des entsprechenden Eingangs auf den Ausgang.

### **Ereignis-Ausgänge**
- **CNF** – Bestätigt die erfolgreiche Verarbeitung des REQ-Ereignisses.

### **Daten-Eingänge**
- **K** (Datentyp: UINT) – Index, der festlegt, welcher der fünf Eingänge (IN1…IN5) auf OUT gelegt wird. Gültige Werte: 0‑4.

### **Daten-Ausgänge**
Keine.

### **Adapter**
- **OUT** (Plug, Typ: `adapter::types::unidirectional::AUDI`) – Ausgangsadapter, der den aktuell ausgewählten Eingangswert bereitstellt.
- **IN1** (Socket, Typ: `adapter::types::unidirectional::AUDI`) – Erster Eingang (Index K=0).
- **IN2** (Socket, Typ: `adapter::types::unidirectional::AUDI`) – Zweiter Eingang (Index K=1).
- **IN3** (Socket, Typ: `adapter::types::unidirectional::AUDI`) – Dritter Eingang (Index K=2).
- **IN4** (Socket, Typ: `adapter::types::unidirectional::AUDI`) – Vierter Eingang (Index K=3).
- **IN5** (Socket, Typ: `adapter::types::unidirectional::AUDI`) – Fünfter Eingang (Index K=4).

## Funktionsweise
Der Baustein arbeitet als **1‑aus‑5‑Multiplexer**. Sobald am Ereigniseingang REQ ein Signal anliegt, wird der aktuelle Wert des Daten-Eingangs K ausgelesen. Anschließend wird der Adapterausgang **OUT** mit dem Inhalt des Adapters verbunden, der dem Index K entspricht:
- K = 0 → IN1
- K = 1 → IN2
- K = 2 → IN3
- K = 3 → IN4
- K = 4 → IN5

Nach erfolgreicher Umschaltung wird das Ereignis **CNF** ausgegeben. Der Baustein ist generisch ausgelegt und kann daher mit beliebigen AUDI-Adaptertypen arbeiten, solange die Schnittstellen unidirektional sind.

## Technische Besonderheiten
- **Generischer Typ** – Der FB ist als `generic FB` deklariert und kann durch einen konkreten Klassennamen (`GEN_AUDI_MUX`) instanziiert werden.
- **Adapterbasiert** – Sowohl Ein- als auch Ausgänge werden über Adapter realisiert, was eine modulare und typensichere Verbindung ermöglicht.
- **Indexabdeckung** – Der Index K ist als `UINT` definiert; es wird erwartet, dass die aufrufende Logik nur Werte im Bereich 0‑4 übergibt. Ein ungültiger Index (≥5) führt zu undefiniertem Verhalten.

## Zustandsübersicht
Der Baustein besitzt keine expliziten Zustände im Sinne einer Zustandsmaschine. Er verharrt im Ruhezustand, bis ein REQ-Ereignis eintrifft. Nach der Verarbeitung wird sofort CNF gesendet und der Baustein kehrt in den Wartezustand zurück.

## Anwendungsszenarien
- **Signalumschaltung** – Auswahl eines von fünf analogen oder digitalen Messwerten (z. B. Temperaturfühler, Drucksensoren) für die weitere Verarbeitung.
- **Modenumschaltung** – Wechsel zwischen unterschiedlichen Betriebsmodi einer Maschine, die über Adapter angeschlossen sind.
- **Test- und Diagnosefunktionen** – Gezieltes Einspielen von Testsignalen auf einen gemeinsamen Ausgang.

## Vergleich mit ähnlichen Bausteinen
Ähnliche Funktionalität bieten Standard‑MUX‑Bausteine (z. B. `MUX` oder `SEL`), die oft mit einfachen Datentypen (BOOL, INT, REAL) arbeiten. Der **AUDI_MUX_5** hebt sich durch die Verwendung von Adaptern ab, die komplexe, strukturierte Daten oder ganze Signalpfade in einem einzigen Verbindungspunkt bündeln. Dadurch eignet er sich besonders für den Einsatz in objektorientierten oder adapterbasierten Architekturen.

## Fazit
Der **AUDI_MUX_5** ist ein kompakter, generischer Multiplexer für fünf Adaptereingänge. Er ermöglicht eine saubere, typengeprüfte Umschaltung von Signalen in der Automatisierungstechnik und lässt sich aufgrund seiner generischen Natur flexibel in verschiedene Steuerungsumgebungen integrieren. Seine einfache Handhabung und klare Schnittstelle machen ihn zu einem nützlichen Werkzeug für die Signalauswahl in 4diac‑Projekten.