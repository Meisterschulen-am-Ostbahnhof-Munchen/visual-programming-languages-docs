# AUI_SPLIT_5


![AUI_SPLIT_5](./AUI_SPLIT_5.svg)

* * * * * * * * * *

## Einleitung
Der Funktionsblock **AUI_SPLIT_5** ist ein generischer Baustein zur Aufteilung eines eingehenden AUI-Adapters („Automation Unit Interface“) auf fünf separate, gleichartige AUI-Ausgänge. Er realisiert eine 1:5-Verteilung in unidirektionaler Datenrichtung. Entwickelt für den Einsatz in der Automatisierungstechnik, ermöglicht er die redundante oder verteilte Weiterleitung von AUI-Signalen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**
Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**
Keine Daten-Eingänge vorhanden. Die Signale werden ausschließlich über die Adapter-Schnittstellen transportiert.

### **Daten-Ausgänge**
Keine Daten-Ausgänge vorhanden.

### **Adapter**
Der Baustein verfügt über sechs Adapter-Schnittstellen vom Typ `adapter::types::unidirectional::AUI`:

- **IN** (Socket) – Eingangsadapter für das zu verteilende AUI-Signal.
- **OUT1** bis **OUT5** (Plugs) – Fünf Ausgangsadapter, die das eingehende Signal spiegeln.

Sämtliche Adapter sind unidirektional ausgelegt und übertragen Daten sowie optional zugehörige Ereignisse gemäß der AUI-Spezifikation.

## Funktionsweise
Der FB fungiert als reiner Splitter ohne Logik oder Pufferung. Ein am Socket **IN** anliegendes AUI-Signal wird parallel und unverändert auf alle fünf Plugs **OUT1** bis **OUT5** kopiert. Die Weiterleitung erfolgt instantan, d.h. ohne Verzögerung durch interne Verarbeitung. Die einzelnen Ausgänge sind galvanisch oder logisch nicht entkoppelt – eine Änderung am Eingang wirkt sich sofort auf alle Ausgänge aus.

## Technische Besonderheiten
- **Generischer Typ**: Der FB ist als generischer Baustein deklariert (Attribut `eclipse4diac::core::GenericClassName` = `'GEN_AUI_SPLIT'`). Dies ermöglicht eine spätere Typanpassung oder Instanziierung mit einem konkreten AUI-Typ.
- **Keine Zustandshaltung**: Da keine Ereignisse oder Daten existieren, die auf Änderungen reagieren, ist der FB zustandslos. Eine Zustandsmaschine ist nicht erforderlich.
- **Volle Bandbreite**: Die Ausgänge liefern das Eingangssignal ohne Einschränkung – alle Daten- und Ereigniskanäle des AUI-Adapters werden 1:1 kopiert.

## Zustandsübersicht
Der Baustein besitzt keine eigenen Zustände oder Zustandsautomaten. Er verhält sich wie eine passive Verdrahtung. Eine Zustandsübersicht ist daher nicht anwendbar.

## Anwendungsszenarien
- **Signalverteilung**: Aufteilung eines zentralen AUI-Datenstroms auf mehrere parallele Verbraucher (z.B. Anzeigen, Überwachungseinheiten, Steuerungen).
- **Test- und Diagnoseaufbauten**: Verwendung in Prüfständen, um ein Signal simultan an mehrere Messgeräte oder Logging-Systeme zu legen.
- **Redundanz**: Bereitstellung identischer Signale für Failover-Systeme, wenn die AUI-Kommunikation unidirektional ist.
- **Bus-Kopplung**: Einsatz als passiver Splitter in AUI-basierten Linien- oder Sternstrukturen.

## Vergleich mit ähnlichen Bausteinen
- **AUI_SPLIT_2 / AUI_SPLIT_3 / AUI_SPLIT_4**: Analoge Bausteine mit weniger Ausgängen; Skalierung nur durch Auswahl des passenden Split-Typs.
- **AUI_MERGE (z.B. AUI_MERGE_5)**: Führt mehrere AUI-Eingänge zu einem Ausgang zusammen – gegensätzliche Funktion.
- **Reine Event-Splitter (E_SPLIT)**: Teilen nur Ereignisse, aber keine Datenadapter. Der AUI_SPLIT_5 hingegen verteilt komplette Adapter-Schnittstellen.

## Fazit
Der **AUI_SPLIT_5** ist ein einfacher, aber essenzieller Baustein zur Vervielfältigung von AUI-Signalen. Seine generische Auslegung und die vollständige Durchleitung des Adapters machen ihn flexibel einsetzbar. Für Anwendungen, die eine unidirektionale 1:5-Verteilung bei gleichzeitiger Minimierung von Latenz erfordern, stellt er eine optimale Lösung dar.