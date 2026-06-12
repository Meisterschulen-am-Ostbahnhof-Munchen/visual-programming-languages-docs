# AULI_FB_CTU


![AULI_FB_CTU](./AULI_FB_CTU.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_FB_CTU** realisiert einen Aufwärtszähler (Up Counter) auf Basis des Datentyps ULINT (unsigned long integer). Er ist als IEC 61499-konformer Baustein mit einer **AULI-Adapter-Schnittstelle** ausgelegt. Der Zähler verwendet intern einen standardisierten IEC 61131-3-CTU-Baustein (`FB_CTU_ULINT`) und stellt dessen Funktionalität über Adapterports zur Verfügung. Die Ereignisauslösung erfolgt bei jedem Update – unabhängig von einer Wertänderung.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine eigenständigen Ereignis-Eingänge. Ereignisse werden ausschließlich über die **AX‑Adapter** der Sockets (CU, R, PV) empfangen.

### **Ereignis-Ausgänge**
| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF | Event | Bestätigung der Ausführung (Execution Confirmation) – wird bei jeder Aktualisierung des Zählers ausgelöst |

### **Daten-Eingänge**
Keine direkten Daten-Eingänge. Die benötigten Daten (CU‑Impuls, Reset‑Signal, Preset‑Wert) werden über die **AULI‑bzw. AX‑Adapter** der Sockets bereitgestellt.

### **Daten-Ausgänge**
Keine direkten Daten-Ausgänge. Die Ergebniswerte (aktueller Zählerstand CV und Schwellwert‑Status Q) werden über die **AULI‑bzw. AX‑Adapter** der Plugs ausgegeben.

### **Adapter**
| Richtung | Adapter‑Name | Typ | Kommentar |
|----------|--------------|-----|-----------|
| **Socket (Eingang)** | CU | `adapter::types::unidirectional::AX` | Count‑Up‑Impuls (Ereignis + Daten) |
| **Socket (Eingang)** | R  | `adapter::types::unidirectional::AX` | Reset‑Impuls (Ereignis + Daten) |
| **Socket (Eingang)** | PV | `adapter::types::unidirectional::AULI` | Preset‑Wert (Vergleichswert für Q‑Ausgang) |
| **Plug (Ausgang)** | Q  | `adapter::types::unidirectional::AX` | Zählerstand ≥ Preset? (Bool‑Status) |
| **Plug (Ausgang)** | CV | `adapter::types::unidirectional::AULI` | Aktueller Zählerstand (ULINT) |

## Funktionsweise
Der Baustein kapselt einen IEC 61131-3-konformen CTU‑Zähler (`FB_CTU_ULINT`). Über die **Socket‑Adapter** werden sowohl Ereignisse als auch Daten empfangen:
- **CU‑Aktualisierung**: Ein positiver Flanke an CU löst einen Zählschritt aus (CV = CV + 1).
- **R‑Aktualisierung**: Ein Reset setzt den Zählerstand zurück (CV = 0).
- **PV‑Aktualisierung**: Der Preset‑Wert wird übernommen; bei jedem Zählschritt wird CV mit PV verglichen.

Das Ereignis an einem Socket wird intern auf den `REQ`‑Eingang des eingebetteten CTU‑Bausteins geführt. Nach der Verarbeitung wird das `CNF`‑Ereignis des CTU‑Blocks an alle drei Ausgänge weitergeleitet:
- **Q‑Plug**: Gibt das Status‑Ereignis (Q.E1) aus – wird **bei jedem Update** gesendet, unabhängig davon, ob sich der boolsche Wert geändert hat.
- **CV‑Plug**: Gibt das Ereignis (CV.E1) aus – ebenfalls **bei jedem Update**.
- **CNF‑Ereignis**: Wird als äußeres Ereignis bereitgestellt.

Die Datenflüsse sind analog: Die Daten der Sockets (CU.D1, R.D1, PV.D1) werden an die entsprechenden Daten‑Eingänge des internen Zählers übergeben. Die Ausgabedaten (Q.D1, CV.D1) werden über die Plugs ausgegeben.

## Technische Besonderheiten
- **Immer‑Aktualisierung**: Der Baustein löst die Ausgangsereignisse (Q.E1, CV.E1, CNF) bei **jedem** eingehenden Ereignis (CU, R, PV) aus – auch wenn sich der Zählerstand oder der Q‑Wert nicht ändert.
- **Filterempfehlung**: Soll nur bei tatsächlicher Wertänderung getriggert werden, wird der Einsatz eines **AX_D_FF**‑Bausteins als Vorfilter empfohlen (siehe Kommentar in der Identifikation).
- **Datenbreite**: Der Zähler arbeitet mit dem Datentyp ULINT (64‑Bit unsigned integer), geeignet für große Zählbereiche.
- **Adapter‑Schnittstelle**: Alle Ein‑ und Ausgaben erfolgen über genormte Adapter (`AX` für boolesche/ereignisbasierte, `AULI` für ULINT‑Werte). Dies erleichtert den modularen Aufbau und die Wiederverwendung in Adapter‑basierten Projekten.
- **Keine Zustandsmaschine auf oberster Ebene**: Der Baustein ist rein transaktionsbasiert: Jedes eingehende Ereignis führt zu einer sofortigen Verarbeitung.

## Zustandsübersicht
Der FB besitzt keinen eigenen Zustandsautomaten. Der interne `FB_CTU_ULINT` kann folgende Zustände durchlaufen (vereinfacht):
- **Idle**: Warten auf ein Ereignis.
- **Zählen (Increment)**: Bei CU‑Ereignis wird der interne Zähler erhöht.
- **Reset**: Bei R‑Ereignis wird der Zähler auf 0 gesetzt.
- **Preset‑Update**: Bei PV‑Ereignis wird der Vergleichswert aktualisiert.

Nach jeder Verarbeitung werden die Ausgänge aktualisiert und das CNF‑Ereignis gesendet.

## Anwendungsszenarien
- **Hochfrequente Impulszählung**: Erfassung von Zählimpulsen (z. B. Encoder, Taktsignale) mit 64‑Bit‑Auflösung.
- **Schwellwertüberwachung**: Zählen von Produkten oder Ereignissen bis zu einem einstellbaren Grenzwert (PV); bei Erreichen wird der Q‑Ausgang aktiv.
- **Reset‑gesteuerte Batch‑Zählung**: Nach einem R‑Impuls beginnt der Zähler von Null; die aktuelle Anzahl wird über CV ausgegeben.
- **Adapter‑basierte Automatisierungsmodule**: Einfache Integration in Systeme, die auf AX/AULI‑Adapter setzen (z. B. standardisierte E/A‑Module).

## Vergleich mit ähnlichen Bausteinen
- **Standard‑CTU (IEC 61131‑3)**: Bietet in der Regel separate Ereignis‑ und Datenports. Der `AULI_FB_CTU` kapselt diese in Adaptern, was die Verkabelung auf Bus‑Ebene verschlankt.
- **CTU mit Change‑Detection**: Manche Zähler‑Bausteine feuern Ausgangsereignisse nur bei Wertänderung. Der vorliegende FB löst bei jedem Update aus – dadurch entsteht ein deterministisches Verhalten (Ereignis pro Eingangsereignis), erfordert aber ggf. nachgeschaltete Filter.
- **CTU als Basic‑FB**: Andere Implementierungen nutzen einen eigenen Zustandsautomaten; dieser FB delegiert die Logik an einen eingebetteten Block und bleibt dadurch schlank.

## Fazit
Der **AULI_FB_CTU** bietet eine IEC 61499‑kompatible, adapterbasierte Aufwärtszähler‑Funktion mit ULINT‑Datenbreite. Seine Stärken liegen in der modularen Schnittstelle und der zuverlässigen Ereignisauslösung bei jedem Update. Für Anwendungen, die eine reine Änderungsdetektion benötigen, ist ein externer Filterbaustein (AX_D_FF) empfehlenswert. Insgesamt eignet sich der Baustein für vielfältige Zählszenarien in der industriellen Automatisierung, besonders in Adapter‑orientierten Architekturen.