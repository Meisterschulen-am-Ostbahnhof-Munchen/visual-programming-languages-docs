# AB_SPLIT_8

![AB_SPLIT_8](./AB_SPLIT_8.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AB_SPLIT_8** dient der Vervielfachung eines eingehenden Adaptersignals vom Typ `AB` auf acht gleichartige Ausgänge. Er fungiert als passiver Verteiler (Splitter) für den unidirektionalen Datenaustausch über die standardisierte Schnittstelle `adapter::types::unidirectional::AB`. Der Baustein ist als generischer Funktionblock ausgelegt und wird typischerweise in der Automatisierungstechnik eingesetzt, um ein AB-Signal parallel an mehrere nachfolgende Komponenten weiterzuleiten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine vorhanden. Der FB besitzt keine ereignisgesteuerten Eingänge; die Datenweitergabe erfolgt rein über die Adapterschnittstelle.

### **Ereignis-Ausgänge**

Keine vorhanden. Es werden keine Ereignisse explizit ausgegeben.

### **Daten-Eingänge**

Keine direkten Daten-Eingänge. Alle eingehenden Informationen werden über den Socket-Adapter transportiert.

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge. Ausgehende Informationen werden über die Plug-Adapter bereitgestellt.

### **Adapter**

| Name  | Typ                                   | Richtung | Beschreibung                                   |
|-------|---------------------------------------|----------|------------------------------------------------|
| `IN`  | `adapter::types::unidirectional::AB`  | Socket   | Eingangsadapter, der das zu verteilende Signal empfängt. |
| `OUT1` | `adapter::types::unidirectional::AB`  | Plug     | Erster Ausgangsadapter (identisch zum Eingangssignal). |
| `OUT2` | `adapter::types::unidirectional::AB`  | Plug     | Zweiter Ausgangsadapter.                       |
| `OUT3` | `adapter::types::unidirectional::AB`  | Plug     | Dritter Ausgangsadapter.                       |
| `OUT4` | `adapter::types::unidirectional::AB`  | Plug     | Vierter Ausgangsadapter.                       |
| `OUT5` | `adapter::types::unidirectional::AB`  | Plug     | Fünfter Ausgangsadapter.                       |
| `OUT6` | `adapter::types::unidirectional::AB`  | Plug     | Sechster Ausgangsadapter.                      |
| `OUT7` | `adapter::types::unidirectional::AB`  | Plug     | Siebter Ausgangsadapter.                       |
| `OUT8` | `adapter::types::unidirectional::AB`  | Plug     | Achter Ausgangsadapter.                        |

## Funktionsweise

Der **AB_SPLIT_8** arbeitet als reiner Signalverteiler ohne interne Logik oder Zustandsautomat. Das über den Socket `IN` ankommende AB-Signal wird identisch und zeitgleich an alle acht Plug-Ausgänge `OUT1` bis `OUT8` weitergeleitet. Eine Pufferung oder Verzögerung findet nicht statt. Der Baustein ist vollständig passiv – er reagiert ausschließlich auf Datenänderungen des angeschlossenen Adapters und gibt diese unverändert weiter.

Die Verteilung erfolgt unabhängig von der internen Struktur des AB-Adapters (z. B. enthaltene Daten- und Ereignisverbindungen). Der FB selbst besitzt keinen eigenen Ausführungszustand und benötigt keine sequenzielle Steuerung.

## Technische Besonderheiten

- **Generischer Typ**: Der FB ist als generischer Baustein deklariert (`GenericClassName = 'GEN_AB_SPLIT'`), was eine flexible Verwendung in verschiedenen Projekten ermöglicht.
- **Keine Zustandsmaschine**: Es existiert kein ECC (Execution Control Chart); der FB ist vollständig datenflussgesteuert.
- **Adaptertyp**: Der verwendete Adapter `adapter::types::unidirectional::AB` ist standardisiert und ermöglicht eine einheitliche Schnittstelle.
- **Lizenz**: Der Baustein steht unter der **Eclipse Public License 2.0 (EPL-2.0)** und ist für die **4diac IDE** konzipiert.

## Zustandsübersicht

Der **AB_SPLIT_8** besitzt keine internen Zustände oder Zustandsautomaten. Die Signalweitergabe erfolgt ohne Verzögerung und ohne Abhängigkeit von einer sequenziellen Logik.

## Anwendungsszenarien

- **Verteilen eines einzigen AB-Sensorsignals** an mehrere Aktoren oder Steuerungen.
- **Parallelschaltung von Überwachungseinheiten** in der Landtechnik (z. B. Verteilen eines Acknowledge-Signals).
- **Erweiterung von Schaltschrankverkabelungen** durch softwarebasierte Signalvervielfachung.
- **Testumgebungen**, in denen ein AB-Signal gleichzeitig an mehrere Analyse-FBs gesendet werden soll.

## Vergleich mit ähnlichen Bausteinen

- **`AB_SPLIT_2`, `AB_SPLIT_4`**: Diese Bausteine verteilen das Signal auf zwei bzw. vier Ausgänge. Der `AB_SPLIT_8` bietet die maximale Anzahl von acht Ausgängen in einem FB.
- **`DATA_SPLIT`**: Verteilt beliebige Datentypen (z. B. `INT`, `BOOL`). Der `AB_SPLIT_8` ist auf den Adaptertyp `AB` spezialisiert und behält die vollständige Adapterstruktur bei.
- **`EC_SPLIT`**: Ein Ereignis-Splitter, der nur Ereignisse vervielfacht, aber keine Daten. Im Gegensatz dazu arbeitet `AB_SPLIT_8` auf Adapterebene inklusive aller darin enthaltenen Daten und Ereignisse.

- **[`AB_SPLIT_8_UNGATED`](AB_SPLIT_8_UNGATED.md)**: Ungegatete Variante – aktualisiert den Ausgang bei jedem Durchlauf, auch ohne Wertänderung.

## Änderungserkennung

Jeder Ausgangs-Plug wird unabhängig aktualisiert: Der eingehende Wert wird nur dann auf einen Ausgang geschrieben und dessen Adapter-Event gesendet, wenn er sich vom aktuellen Wert dieses Ausgangs unterscheidet. Bereits synchrone Ausgänge bleiben still, während ein gerade erst verbundener (oder nicht mehr synchroner) Ausgang weiterhin die nötige Aktualisierung erhält.

## Fazit

Der **AB_SPLIT_8** ist ein einfacher, aber effektiver Funktionsblock zur Vervielfachung eines unidirektionalen AB-Adaptersignals. Durch seine generische Ausführung und die passive Arbeitsweise eignet er sich ideal für die Parallelisierung von Steuerungs- und Überwachungssignalen in der Automatisierungstechnik. Die fehlende Zustandslogik sorgt für geringe Laufzeitkomplexität und hohe Zuverlässigkeit. Der Baustein ist eine sinnvolle Ergänzung für jede 4diac-Bibliothek, die auf Adapterkommunikation setzt.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
- [🌐 Gesamtwiderstand in Reihen- & Parallelschaltung auf ms-muc-docs.de](https://www.ms-muc-docs.de/elektrotechnik/elektrik/widerstand/widerstand-theorie/gesamtwiderstand-reihen-parallelschaltung/)
