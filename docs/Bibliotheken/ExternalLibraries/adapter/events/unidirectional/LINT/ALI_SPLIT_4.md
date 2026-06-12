# ALI_SPLIT_4


![ALI_SPLIT_4](./ALI_SPLIT_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **ALI_SPLIT_4** dient dazu, einen einzelnen ALI-Adapter-Eingang (Typ: `adapter::types::unidirectional::ALI`) auf vier separate ALI-Adapter-Ausgänge zu verteilen. Er ist als generischer Baustein (generic FB) ausgelegt und ermöglicht eine unidirektionale Signalweitergabe von einer Quelle an bis zu vier Senken.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Richtung | Name   | Typ                              | Beschreibung                                       |
|----------|--------|----------------------------------|----------------------------------------------------|
| Socket   | IN     | adapter::types::unidirectional::ALI | Einheitlicher ALI-Eingang (Quelle)                |
| Plug     | OUT1   | adapter::types::unidirectional::ALI | Erster ALI-Ausgang (Ziel)                         |
| Plug     | OUT2   | adapter::types::unidirectional::ALI | Zweiter ALI-Ausgang (Ziel)                        |
| Plug     | OUT3   | adapter::types::unidirectional::ALI | Dritter ALI-Ausgang (Ziel)                        |
| Plug     | OUT4   | adapter::types::unidirectional::ALI | Vierter ALI-Ausgang (Ziel)                        |

## Funktionsweise

Der Baustein empfängt über den Socket **IN** eine ALI-Adapterverbindung und leitet die eingehenden Signale unverändert an alle vier Plugs **OUT1** bis **OUT4** weiter. Es findet keine Datenverarbeitung, Filterung oder logische Verknüpfung statt – die Verteilung erfolgt rein passiv. Durch die generische Implementierung kann der Baustein in verschiedenen Kontexten eingesetzt werden, in denen ein ALI-Signal mehrfach benötigt wird.

## Technische Besonderheiten

- Der FB ist als generischer Baustein (`GEN_ALI_SPLIT`) deklariert, was eine flexible Typanpassung in der Entwicklungsumgebung 4diac IDE ermöglicht.
- Es werden keinerlei Ereignisse oder Datenpunkte benötigt – die gesamte Kommunikation erfolgt ausschließlich über die Adapter-Schnittstellen.
- Der Baustein ist unidirektional ausgelegt: eine Rückkopplung von den Ausgängen zum Eingang ist nicht vorgesehen.
- Die Attribute `GenericClassName` und `TypeHash` dienen der eindeutigen Identifikation und Versionierung des generischen Typs.

## Zustandsübersicht

Der Baustein besitzt keine eigenen Zustände oder Steuerlogik. Das Verhalten ist deterministisch und besteht ausschließlich in der Weiterleitung des Adaptersignals. Daher entfällt eine separate Zustandsmaschine.

## Anwendungsszenarien

- **Signalverteilung**: Ein zentraler ALI-Datenstrom (z. B. von einem Sensor oder Steuergerät) soll parallel an mehrere nachgelagerte Komponenten gesendet werden.
- **Prototyping**: In frühen Entwicklungsphasen kann der Baustein verwendet werden, um ein Signal schnell auf mehrere Testeinheiten zu verteilen.
- **Redundanz**: Mehrere identische Ausgänge ermöglichen den Anschluss von Backup-Systemen oder separaten Überwachungseinheiten.

## Vergleich mit ähnlichen Bausteinen

- **ALI_SPLIT_2**: Verteilt das Eingangssignal auf zwei statt vier Ausgänge. Der ALI_SPLIT_4 bietet die doppelte Anzahl an Ausgangskanälen.
- **ALI_MERGE**: Führt mehrere ALI-Eingänge zu einem Ausgang zusammen – die inverse Funktion zum Split.
- **ALI_SELECT**: Wählt basierend auf einem Steuersignal einen von mehreren Eingängen aus und leitet ihn an einen Ausgang weiter (keine Parallelverteilung).

## Fazit

Der **ALI_SPLIT_4** ist ein einfacher, aber nützlicher Funktionsbaustein zur passiven Verteilung eines unidirektionalen ALI-Signals auf vier identische Ausgänge. Durch die generische Bauweise und das Fehlen von Ereignis- oder Datenlogik eignet er sich besonders für schnelle Signalvervielfachungen in der Automatisierungstechnik, ohne zusätzliche Rechenlast zu verursachen.