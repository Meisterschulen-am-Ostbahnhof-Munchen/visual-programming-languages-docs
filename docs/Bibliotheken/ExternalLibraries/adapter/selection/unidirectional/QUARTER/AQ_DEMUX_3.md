# AQ_DEMUX_3


![AQ_DEMUX_3](./AQ_DEMUX_3.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AQ_DEMUX_3** realisiert einen generischen Demultiplexer für analoge Signale (AQ – Analog Quantity). Er leitet das an seinem Eingangs‑Adapter anliegende Signal auf einen von drei Ausgangs‑Adaptern weiter. Die Auswahl des aktiven Ausgangs erfolgt über den Indexparameter K, der mit einem Ereignis am Eingang **REQ** gesetzt wird. Der Baustein ist als **generischer FB** (Generic FB) ausgelegt und kann in IEC 61499‑basierten Steuerungssystemen für die flexible Signalverteilung eingesetzt werden.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Beschreibung |
|------|--------------|
| `REQ` | Ereignis zum Setzen des Index K. Der neu übergebene Wert von K bestimmt, welcher Ausgang nach der Verarbeitung aktiv ist. |

### **Ereignis-Ausgänge**

| Name | Beschreibung |
|------|--------------|
| `CNF` | Bestätigungsereignis, nachdem der Index K erfolgreich übernommen wurde. Erst nach diesem Ereignis ist der neue Ausgang für die Weiterleitung des Eingangssignals bereit. |

### **Daten-Eingänge**

| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `K`   | `UINT`   | Index des auszuwählenden Ausgangs (1‑basiert). Erlaubte Werte: 1, 2, 3. Werte außerhalb dieses Bereichs führen zu undefiniertem Verhalten (kein Ausgang aktiv). |

### **Daten-Ausgänge**

Keine eigenständigen Datenausgänge. Die Ausgangsdaten werden über die Adapter‑Ausgänge bereitgestellt.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Sockets** (Eingang) | `IN` | `adapter::types::unidirectional::AQ` | Adapter‑Eingang, der das zu demultiplexende analoge Signal bereitstellt. |
| **Plugs** (Ausgänge) | `OUT1`, `OUT2`, `OUT3` | `adapter::types::unidirectional::AQ` | Drei unidirektionale Adapter‑Ausgänge. Nur der durch `K` ausgewählte Ausgang gibt das Signal des Eingangsadapter weiter; die anderen bleiben inaktiv. |

## Funktionsweise

1. Der Baustein wartet auf ein Ereignis am Eingang `REQ`.  
2. Mit dem Ereignis wird der aktuelle Wert des Daten‑Eingangs `K` gelesen.  
3. Abhängig vom Wert `K` (1, 2 oder 3) wird der entsprechende Ausgangs‑Adapter (`OUT1`, `OUT2` oder `OUT3`) aktiviert und das am Adapter‑Eingang `IN` anliegende Signal dorthin weitergeleitet.  
4. Nachdem die Umschaltung erfolgt ist, wird das Bestätigungsereignis `CNF` ausgegeben.  

Der Baustein verhält sich wie ein 1‑zu‑3‑Demultiplexer: Das Eingangssignal wird immer nur an einen der drei Ausgänge geroutet. Die anderen beiden Ausgänge liefern keinen gültigen Wert (üblicherweise 0 oder undefiniert).

## Technische Besonderheiten

- **Generischer Baustein:** Der FB ist als Typ mit dem generischen Klassennamen `'GEN_AQ_DEMUX'` deklariert. Dadurch kann er in verschiedenen Ausprägungen (z.B. mit mehr Ausgängen) durch Metadaten‑Anpassung genutzt werden.  
- **Adaptive Adapter‑Schnittstelle:** Die Verwendung des Typs `adapter::types::unidirectional::AQ` ermöglicht eine lose Kopplung der Signalquellen und -senken. Die genaue AQ‑Datenstruktur kann in der konkreten Implementierung variieren.  
- **Ereignisgesteuerte Umschaltung:** Die Änderung des Ausgangs erfolgt ausschließlich über das `REQ`-Ereignis. Ohne erneutes Ereignis bleibt der aktuelle Ausgang bestehen.  
- **Keine zyklische Aktualisierung:** Das Eingangssignal wird nicht autonom weitergeleitet; eine Aktualisierung der Ausgangsdaten erfolgt nur nach einem `REQ`-Ereignis.

## Zustandsübersicht

Der FB besitzt keinen explizit in der XML definierten Zustandsautomaten, da er ereignisgesteuert arbeitet. Das interne Verhalten lässt sich wie folgt beschreiben:

- **Idle** → Warten auf `REQ`  
- **Processing** → Auswertung von `K` und Umschalten des aktiven Ausgangs  
- **Done** → Ausgabe von `CNF`, Rückkehr zu Idle  

Nach einem gültigen `REQ` wird der Zustand **Processing** durchlaufen, danach sofort wieder **Idle**.

## Anwendungsszenarien

- **Aufteilung eines analogen Sensorsignals** an verschiedene Aktoren oder nachgelagerte Regelungsblöcke.  
- **Umschaltung zwischen mehreren Verbrauchern** (z.B. je nach Betriebsart oder Produktrezept).  
- **Test‑ und Diagnoseumgebungen**, in denen ein Signal wahlweise auf unterschiedliche Analysepfade gelenkt werden muss.  
- **Redundante Signalverteilung**, bei der nur ein aktiver Pfad gleichzeitig genutzt wird.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Funktion | Unterschied |
|----------|----------|-------------|
| `AQ_DEMUX_3` | Analog‑Demultiplexer mit 3 Ausgängen | Speziell für AQ‑Adapter, generisch erweiterbar. |
| `AQ_MUX_3` | Analog‑Multiplexer (3 Eingänge → 1 Ausgang) | Umgekehrte Richtung: mehrere Quellen auf einen Ausgang. |
| `E_DEMUX` | Ereignis‑Demultiplexer | Verteilt Ereignisse, nicht Daten‑Adapter; arbeitet mit boolescher Auswahl. |
| `SAMPLE_3` | Beispiel‑Demux mit konkreten Datentypen | Kein generischer Adapter‑Ansatz, daher weniger flexibel. |

Der vorliegende Baustein zeichnet sich durch die lose Adapter‑Kopplung und die generische Auslegung aus.

## Fazit

Der **AQ_DEMUX_3** ist ein nützlicher, generischer IEC 61499‑Funktionsbaustein zur verteilten Signalweitergabe auf Basis von AQ‑Adaptern. Mit seiner ereignisgesteuerten Indexumschaltung eignet er sich für flexible Routing‑Aufgaben in der Automatisierungstechnik. Die klare Schnittstelle und die Möglichkeit der generischen Erweiterung machen ihn zu einer guten Wahl, wenn mehrere analoge Signale zeitlich getrennt an verschiedene Empfänger geleitet werden müssen.