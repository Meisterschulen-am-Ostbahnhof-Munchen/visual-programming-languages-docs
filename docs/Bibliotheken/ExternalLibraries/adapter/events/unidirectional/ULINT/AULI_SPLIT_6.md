# AULI_SPLIT_6


![AULI_SPLIT_6](./AULI_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **AULI_SPLIT_6** dient dazu, einen einzelnen AULI-Adapter-Eingang (unidirektional) auf sechs identische AULI-Ausgänge zu verteilen. Er stellt eine generische Lösung dar, um ein AULI-Signal an mehrere nachfolgende Bausteine weiterzuleiten, ohne die Signalintegrität zu beeinträchtigen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| IN | Socket (Eingang) | adapter::types::unidirectional::AULI | Empfängt das zu verteilende AULI-Signal. |
| OUT1 | Plug (Ausgang) | adapter::types::unidirectional::AULI | Erster identischer Ausgang des verteilten Signals. |
| OUT2 | Plug (Ausgang) | adapter::types::unidirectional::AULI | Zweiter identischer Ausgang. |
| OUT3 | Plug (Ausgang) | adapter::types::unidirectional::AULI | Dritter identischer Ausgang. |
| OUT4 | Plug (Ausgang) | adapter::types::unidirectional::AULI | Vierter identischer Ausgang. |
| OUT5 | Plug (Ausgang) | adapter::types::unidirectional::AULI | Fünfter identischer Ausgang. |
| OUT6 | Plug (Ausgang) | adapter::types::unidirectional::AULI | Sechster identischer Ausgang. |

## Funktionsweise

Der Baustein arbeitet als reine Signalverteilung (Splitter). Ein an **IN** anliegendes AULI-Signal wird ohne Verzögerung oder Datenverlust auf alle sechs Ausgangs-Adapter (**OUT1** bis **OUT6**) dupliziert. Es findet keine aktive Verarbeitung oder Filterung statt – die Datenübertragung erfolgt ausschließlich über die unidirektionalen AULI-Adapter.

Da keine Ereignisse oder Daten-Ein-/Ausgänge vorhanden sind, basiert die Kommunikation vollständig auf der Adapter-Schnittstelle. Der Baustein ist ereignisfrei und wird allein durch die Verbindung der Adapter aktiv.

## Technische Besonderheiten

- **Generischer Typ:** Der Baustein ist als generischer Funktionsbaustein (`GEN_AULI_SPLIT`) implementiert, sodass er für verschiedene AULI-Varianten wiederverwendet werden kann.
- **Unidirektionale Adapter:** Die verwendeten Adapter sind als unidirektionale Schnittstellen deklariert – sie unterstützen nur eine Datenflussrichtung (vom Socket zu den Plugs).
- **Keine Daten- oder Ereignisverarbeitung:** Der Baustein enthält keine internen Algorithmen oder Zustände; er fungiert ausschließlich als passiver Splitter.
- **Einfache Skalierung:** Durch die feste Anzahl von sechs Ausgängen ist der Baustein für typische Anwendungen in der Landtechnik (z. B. HR Agrartechnik) optimiert.

## Zustandsübersicht

Da der Baustein keine Ereignissteuerung besitzt und keine internen Zustände verwaltet, existiert kein Zustandsautomat. Der Baustein ist rein kombinatorisch und gibt die Eingangssignale unverändert an alle Ausgänge weiter.

## Anwendungsszenarien

- **Verteilen eines Sensorsignals:** In landwirtschaftlichen Steuerungssystemen kann ein einzelner AULI-Sensor (z. B. für Erntegutfluss) an mehrere nachgelagerte Auswertemodule angeschlossen werden.
- **Parallelisierung von Aktorsteuerungen:** Ein Steuerbefehl (z. B. für Hydraulikventile) soll gleichzeitig an sechs identische Aktoren weitergeleitet werden.
- **Redundanzaufbau:** Bei sicherheitskritischen Anwendungen kann das gleiche Signal mehrfach an redundante Steuereinheiten geführt werden.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Anzahl Ausgänge | Besonderheit |
|----------|------------------|--------------|
| AULI_SPLIT_6 | 6 | Fester Splitter für AULI-Adapter |
| AULI_SPLIT_2 | 2 | Kleinere Variante für zwei Ausgänge |
| AULI_SPLIT_4 | 4 | Mittlere Variante für vier Ausgänge |

Der **AULI_SPLIT_6** bietet im Vergleich zu kleineren Splittern eine höhere Anzahl an Ausgängen, was den Verdrahtungsaufwand in komplexen Systemen reduziert und gleichzeitig eine saubere Signalstruktur erhält.

## Fazit

Der **AULI_SPLIT_6** ist ein einfacher, aber effektiver Funktionsbaustein zur Verteilung eines AULI-Adaptersignals auf sechs parallele Ausgänge. Dank seiner generischen Implementierung und der reinen Adapter-Schnittstelle lässt er sich leicht in IEC‑61499‑Anwendungen der Landtechnik und Automatisierungstechnik integrieren. Er eignet sich besonders für Szenarien, in denen ein Signal mehrfach benötigt wird, ohne zusätzliche Logik oder Zustandsverwaltung.