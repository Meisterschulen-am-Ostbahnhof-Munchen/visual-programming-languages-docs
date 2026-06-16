# ATM_MUX_4


![ATM_MUX_4](./ATM_MUX_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ATM_MUX_4` ist ein generischer Multiplexer, der einen von vier ATM‑Adapter-Eingängen auf einen Ausgangsadapter schaltet. Die Auswahl erfolgt über einen Index `K`. Der Baustein ist für den Einsatz in der Agrarsteuerung (nach IEC 61499) konzipiert und kann über den `GenericClassName` anwendungsspezifisch umbenannt werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ   | Kommentar             |
|------|-------|-----------------------|
| REQ  | Event | Set Index K (Eingang auswählen) |

Der Ereigniseingang `REQ` löst die Multiplexer-Funktion aus. Er ist mit der Dateneingangsvariable `K` verknüpft.

### **Ereignis-Ausgänge**

| Name | Typ   | Kommentar                        |
|------|-------|----------------------------------|
| CNF  | Event | Confirmation of Set Index K      |

Nach erfolgreicher Umschaltung des Ausgangs auf den durch `K` bestimmten Eingang wird das Ereignis `CNF` ausgegeben.

### **Daten-Eingänge**

| Name | Typ  | Kommentar |
|------|------|-----------|
| K    | UINT | index     |

Mit diesem ganzzahligen Wert wird festgelegt, welcher der vier ATM‑Adapter-Eingänge auf den Ausgang durchgeschaltet wird. Gültige Werte: 0, 1, 2, 3.

### **Daten-Ausgänge**
Der Baustein besitzt keine eigenen Datenausgänge. Die Datenweitergabe erfolgt ausschließlich über die Adapter.

### **Adapter**

| Name | Typ                                     | Kommentar                                   |
|------|-----------------------------------------|---------------------------------------------|
| IN1  | `adapter::types::unidirectional::ATM`   | Input value 1 (K = 0)                       |
| IN2  | `adapter::types::unidirectional::ATM`   | Input value 2 (K = 1)                       |
| IN3  | `adapter::types::unidirectional::ATM`   | Input value 3 (K = 2)                       |
| IN4  | `adapter::types::unidirectional::ATM`   | Input value 4 (K = 3)                       |
| OUT  | `adapter::types::unidirectional::ATM`   | IN1 for K=0, IN2 for K=1, IN3 for K=2, IN4 for K=3 |

**Anmerkung:** Die Bezeichnung „IN“ im Ausgangskommentar bezieht sich auf die Quell-Adapter – der Ausgang leitet den Datenstrom des entsprechenden Eingangs weiter.

## Funktionsweise
1. Zum Zeitpunkt des Ereignisses `REQ` wird der aktuell an `K` anliegende Wert (0…3) ausgelesen.
2. Der Baustein verbindet den Ausgangsadapter `OUT` mit dem Eingangsadapter, der dem Index entspricht:
   - `K = 0` → `IN1`
   - `K = 1` → `IN2`
   - `K = 2` → `IN3`
   - `K = 3` → `IN4`
3. Nach erfolgter Verbindung wird das Bestätigungsereignis `CNF` gesendet.

Die Adapter sind als unidirektionale ATM‑Schnittstellen typisiert. Der Multiplexer arbeitet rein ereignisgesteuert – eine Änderung von `K` ohne `REQ` wird nicht berücksichtigt.

## Technische Besonderheiten
- **Generischer Baustein** – Über das Attribut `eclipse4diac::core::GenericClassName` kann der Funktionsblock in der IDE (z. B. Eclipse 4diac) mit einem beliebigen Namen versehen werden, z. B. `GEN_ATM_MUX`. Dies erleichtert die Wiederverwendung in verschiedenen Projekten.
- Kein eigenes Zustandsdiagramm erforderlich – die Logik ist auf die reine Umschaltung reduziert.
- Die Adapter sind vom Typ `unidirectional::ATM`, d. h. Daten fließen nur in eine Richtung (vom Eingang zum Ausgang).

## Zustandsübersicht
Der `ATM_MUX_4` besitzt keine explizit modellierte Zustandsmaschine. Das Verhalten beschränkt sich auf:
- **Warten auf REQ**: Der Ausgang ist mit dem zuletzt gesetzten Eingang verbunden.
- **Ausführung bei REQ**: Der Ausgang wird auf den durch `K` bestimmten Eingang umgeschaltet und `CNF` wird ausgegeben.

Eine fehlerhafte Indexangabe (Werte außerhalb 0…3) wird nicht behandelt – der Baustein ist auf korrekte Eingaben angewiesen.

## Anwendungsszenarien
- **Agrarsteuerung**: Umschalten zwischen verschiedenen ATM‑Datenquellen (z. B. Sensoren, Aktoren) in Steuerungssystemen nach IEC 61499.
- **Datenstrom‑Selektion**: Auswahl eines von vier ATM‑Signalen zur Weiterverarbeitung in einer übergeordneten Logik.
- **Test‑ und Simulationsumgebungen**: Erzeugen gezielter Verbindungen zwischen virtuellen Komponenten.

## Vergleich mit ähnlichen Bausteinen
- **Standard‑MUX‑Bausteine (z. B. MUX2, MUX4)** arbeiten meist mit elementaren Datentypen (INT, BOOL). Der `ATM_MUX_4` ist speziell für den Adapter‑Typ „ATM“ ausgelegt, was eine direkte, protokollgetreue Weiterleitung ohne Datenkonvertierung erlaubt.
- **Adapter‑basierte Multiplexer** sind seltener als Daten‑Multiplexer. Der vorliegende Baustein kapselt die gesamte Umschaltlogik innerhalb eines Funktionsblocks, was die Netzübersichtlichkeit erhöht.

## Fazit
Der `ATM_MUX_4` ist ein kompakter, generischer Funktionsblock zur Auswahl eines von vier ATM‑Adapter-Eingängen. Er eignet sich besonders für ereignisgesteuerte Applikationen in der Agrarsteuerung, bei denen unidirektionale ATM‑Datenströme umgeschaltet werden müssen. Die Möglichkeit der generischen Umbenennung und die klare ereignisbasierte Schnittstelle machen ihn vielseitig einsetzbar.