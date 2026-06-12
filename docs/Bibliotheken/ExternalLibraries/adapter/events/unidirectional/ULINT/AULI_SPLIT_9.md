# AULI_SPLIT_9


![AULI_SPLIT_9](./AULI_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AULI_SPLIT_9** dient als Verteiler für den unidirektionalen AULI‑Adapter. Er nimmt einen eingehenden AULI‑Datensatz über den Socket **IN** entgegen und leitet diesen unverändert an alle neun Ausgangs‑Adapter (**OUT1** bis **OUT9**) weiter. Der Baustein ist als generischer Splitter konzipiert und eignet sich für Anwendungen, in denen ein AULI‑Signal auf mehrere Verbraucher aufgeteilt werden muss.

## Schnittstellenstruktur

### Ereignis-Eingänge

Keine Ereignis-Eingänge vorhanden.  
Die Weiterleitung erfolgt rein datengetrieben.

### Ereignis-Ausgänge

Keine Ereignis-Ausgänge vorhanden.  
Der Baustein erzeugt keine Steuerereignisse.

### Daten-Eingänge

Keine Daten-Eingänge vorhanden.  
Der gesamte Datenaustausch erfolgt über den Adapter **IN**.

### Daten-Ausgänge

Keine Daten-Ausgänge vorhanden.  
Die Ausgabe der Daten erfolgt ausschließlich über die Adapter **OUT1** bis **OUT9**.

### Adapter

| Typ | Richtung | Name | Beschreibung |
|-----|----------|------|--------------|
| Socket | Eingang | **IN** | Unidirektionaler AULI‑Adapter – empfängt den zu verteilenden Datensatz. |
| Plug | Ausgang | **OUT1** … **OUT9** | Neun unidirektionale AULI‑Adapter – geben den identischen Eingangsdatensatz aus. |

## Funktionsweise

Der Baustein arbeitet als reine 1:9‑Verteilerstufe. Sobald ein Datensatz am Socket **IN** anliegt, wird dieser Datensatz unverändert auf alle neun Plugs **OUT1** bis **OUT9** kopiert. Da keine ereignisgesteuerten Aktivierungen oder Verarbeitungsschritte existieren, erfolgt die Weitergabe implizit durch die Laufzeitumgebung, sobald sich der Eingangsdatensatz ändert. Der Baustein besitzt keinerlei interne Logik oder Zustandsspeicher.

## Technische Besonderheiten

- **Generischer Aufbau**: Der Baustein ist unter dem generischen Klassennamen `GEN_AULI_SPLIT` registriert und kann je nach Konfiguration der Laufzeitumgebung angepasst werden.
- **Unidirektionaler Datenfluss**: Alle beteiligten Adapter sind vom Typ `adapter::types::unidirectional::AULI`, was eine klare Datenflussrichtung vorgibt – vom Socket IN zu den Plugs. Rückwirkungen sind nicht vorgesehen.
- **Keine Zustandshaltung**: Der Baustein ist zustandslos und benötigt keine Initialisierung oder spezielle Steuerung.

## Zustandsübersicht

Der Baustein besitzt keinen expliziten Zustandsautomaten. Er befindet sich stets im aktiven Durchleitungsmodus. Einziger „Zustand“ ist die Identität des Eingangsdatensatzes, der durchgereicht wird.

## Anwendungsszenarien

- **Vervielfachung eines Steuer‑/Messsignals** in der Automatisierungstechnik, z. B. in der Agrar‑ oder Landtechnik (Herkunft des Bausteins deutet auf entsprechende Umgebungen hin).
- **Aufteilung eines AULI‑basierten Protokoll‑Kanals** auf mehrere parallele Empfänger, ohne dass eine aktive Kopie oder Signalverstärkung nötig ist.
- **Einfache Sternverteilung** innerhalb einer 4diac‑Applikation, wenn mehrere nachfolgende FBs denselben AULI‑Datensatz benötigen.

## Vergleich mit ähnlichen Bausteinen

- **AULI_SPLIT_4 / AULI_SPLIT_8**: Diese Varianten unterscheiden sich lediglich in der Anzahl der Ausgangskanäle. Der hier beschriebene Baustein bietet mit 9 Ausgängen eine besonders hohe Verteilungsdichte.
- **Generische Splitter‑FBs für andere Adaptertypen**: Prinzipiell existieren analoge Splitter für z. B. `AULI`-Adapter mit geringerer Ausgangszahl. Allen gemeinsam ist die zustandslose 1:n‑Vervielfältigung.

## Fazit

Der **AULI_SPLIT_9** ist ein einfacher, aber effektiver Verteilerbaustein für den unidirektionalen AULI‑Adapter. Dank seiner generischen Natur und der vollständigen Signaldurchleitung ohne Latenz oder Verarbeitungsverzögerung eignet er sich ideal für Szenarien, in denen ein einzelner Datensatz an viele Empfänger gestreut werden muss. Die fehlende Ereignissteuerung und der reine Adapter‑Ansatz machen ihn besonders leichtgewichtig und performant.