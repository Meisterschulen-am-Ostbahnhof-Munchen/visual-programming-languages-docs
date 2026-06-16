# ALR_DEMUX_3


![ALR_DEMUX_3](./ALR_DEMUX_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsbaustein `ALR_DEMUX_3` ist ein generischer Demultiplexer für ALR-Adapterschnittstellen (unidirektional). Er leitet den am Socket `IN` anliegenden ALR-Datenstrom auf einen von drei Ausgangs-Adaptern (`OUT1`, `OUT2`, `OUT3`) weiter. Die Auswahl des Zielausgangs erfolgt über den Index `K`. Der Baustein eignet sich für den Einsatz in Anwendungen, bei denen ein Signalweg dynamisch auf verschiedene nachgelagerte Komponenten geschaltet werden muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `REQ` | Event | Setze den Index `K` und löse die Weiterleitung aus |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `CNF` | Event | Bestätigung der erfolgten Umschaltung/Weiterleitung |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| `K` | UINT | Index des Zielausgangs (1..3) |

### **Daten-Ausgänge**
*Keine Daten-Ausgänge vorhanden.* Die eigentliche Datenübertragung erfolgt über die Adapter.

### **Adapter**

| Name | Typ | Richtung | Kommentar |
|------|-----|----------|-----------|
| `IN` | ALR (unidirectional) | Socket | Eingangsadapter (Datenquelle) |
| `OUT1` | ALR (unidirectional) | Plug | Erster Ausgangskanal |
| `OUT2` | ALR (unidirectional) | Plug | Zweiter Ausgangskanal |
| `OUT3` | ALR (unidirectional) | Plug | Dritter Ausgangskanal |

## Funktionsweise
Der Baustein arbeitet nach dem Demultiplex-Prinzip. Bei einem Ereignis am Eingang `REQ` wird der am Socket `IN` anliegende ALR-Wert übernommen und an den durch den Index `K` (ganzzahliger Wert 1–3) bestimmten Ausgangsadapter (`OUT1`, `OUT2` oder `OUT3`) weitergereicht. Anschließend wird das Ereignis `CNF` gesendet, um den erfolgreichen Abschluss zu signalisieren. Liegt der Index außerhalb des gültigen Bereichs (z. B. 0 oder >3), wird die Anfrage möglicherweise ignoriert oder ein undefinierter Zustand erreicht – abhängig von der konkreten Implementierung.

## Technische Besonderheiten
- **Generische Ausführung**: Der Baustein ist als instanziierbarer generischer Funktionsbaustein (`GEN_ALR_DEMUX`) deklariert, d. h., er kann in verschiedenen Kontexten mit unterschiedlichen ALR-Typen verwendet werden, sofern diese das gleiche Adapter-Interface besitzen.
- **Unidirektionale Adapter**: Sowohl Eingang als auch Ausgänge nutzen den unidirektionalen ALR-Adaptertyp. Eine Rückmeldung vom Ausgang zum Eingang ist nicht möglich.
- **Keine Zustandsmaschine**: Laut der bereitgestellten XML-Definition besitzt der Baustein keine explizite ECC (Execution Control Chart). Das Verhalten ist rein ereignisgesteuert und auf den Moment der `REQ`-Bearbeitung beschränkt.

## Zustandsübersicht
Der `ALR_DEMUX_3` verfügt über keine explizite Zustandsmaschine. Er befindet sich stets in einem grundlegenden Bereitschaftszustand. Bei Eintreffen von `REQ` führt er sofort die Demultiplex-Operation aus und signalisiert den Abschluss mit `CNF`. Es gibt keine inneren Zustände wie „Warten“ oder „Beschäftigt“.

## Anwendungsszenarien
- **Ressourcenumschaltung**: Mehrere Sensoren oder Aktoren teilen sich eine Datenquelle, die je nach Kontext auf unterschiedliche Einheiten geschaltet werden muss (z. B. in der Automatisierungstechnik für die Ansteuerung mehrerer identischer Verbraucher).
- **Test- und Diagnoseaufbauten**: Ein ALR-Signal wird nacheinander an verschiedene Prüfstellen geleitet, ohne die Verkabelung physisch ändern zu müssen.
- **Redundanzschaltungen**: Ein primäres Signal wird bei Bedarf auf eine von drei redundanten Einheiten umgeleitet.

## Vergleich mit ähnlichen Bausteinen
Im Vergleich zu einem klassischen, datenorientierten Demultiplexer (z. B. `F_MUX/DEMUX`), der mit skalaren Datentypen (INT, REAL usw.) arbeitet, ist der `ALR_DEMUX_3` speziell für die strukturierte Adapter-Kommunikation ausgelegt. Während ein Daten-Demux nur einzelne Werte weiterleitet, überträgt dieser Baustein eine gesamte ALR-Verbindung einschließlich aller darin enthaltener Datenfelder. Er ist weniger flexibel bezüglich der Anzahl der Ausgänge (fest auf drei), bietet aber eine saubere Trennung auf Adapter-Ebene.

## Fazit
Der `ALR_DEMUX_3` ist ein spezialisierter, generischer Baustein für die unidirektionale Verteilung von ALR-Adapterverbindungen. Er ermöglicht eine flexible und dynamische Signalweiterleitung in Automatisierungssystemen und erweitert das Spektrum industrieller Demultiplexer um die Komponente der adapterbasierten Kommunikation. Seine einfache Ereignislogik und die festgelegte Anzahl von drei Ausgängen machen ihn für praxisnahe Szenarien gleichermaßen leistungsfähig und einfach zu handhaben.