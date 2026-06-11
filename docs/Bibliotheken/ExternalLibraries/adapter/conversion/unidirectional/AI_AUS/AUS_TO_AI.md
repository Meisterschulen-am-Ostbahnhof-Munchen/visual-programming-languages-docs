# AUS_TO_AI


![AUS_TO_AI](./AUS_TO_AI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock `AUS_TO_AI` ist ein Composite-Baustein, der einen Adapter des Typs `AUS` (USINT-basiert) in einen Adapter des Typs `AI` (INT-basiert) umwandelt. Er dient als unidirektionale Schnittstelle zwischen Systemteilen, die unterschiedliche Datentypen für analoge Eingänge verwenden. Der Baustein kapselt die Konvertierungslogik und erleichtert die Integration von Komponenten, die auf `USINT`-Adaptern basieren, in Umgebungen, die `INT`-Adapter erwarten.

## Schnittstellenstruktur

Der FB besitzt **keine direkten Ereignis- oder Dateneingänge bzw. -ausgänge**. Die gesamte Signalkommunikation erfolgt über die beiden eingebauten Adapter:

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
| `AUS_IN` | Socket | `adapter::types::unidirectional::AUS` | USINT-basierter Adaptereingang (Quelle des zu konvertierenden Werts) |
| `AI_OUT` | Plug | `adapter::types::unidirectional::AI` | INT-basierter Adapterausgang (Ziel des konvertierten Werts) |

Der Socket `AUS_IN` empfängt ein Ereignissignal und einen USINT-Datenwert. Der Plug `AI_OUT` gibt nach erfolgter Konvertierung ein Ereignissignal und den dazugehörigen INT-Wert aus.

## Funktionsweise

Der Baustein arbeitet rein kombinatorisch auf Basis einer internen Instanz des IEC‑61131‑Funktionsbausteins `F_USINT_TO_INT`. Die Ablaufsteuerung wird über die Ereignisverbindungen der Adapter realisiert:

1. **Ereignis E1 am AUS_IN-Adapter** wird auf den **REQ-Eingang** des Konvertierungsbausteins `Convert` geleitet.
2. Der Konvertierungsbaustein führt die Wandlung des an seinem **IN**-Eingang anliegenden USINT-Werts in einen INT-Wert durch und signalisiert die Fertigstellung mit dem Ereignis **CNF**.
3. Das **CNF**-Ereignis wird an den **E1-Eingang des AI_OUT-Adapter**s weitergegeben, gleichzeitig wird der konvertierte INT-Wert an den **D1-Datenausgang** des AI_OUT-Adapter gelegt.

Somit entsteht eine kausale Kette: Ein eingehendes Ereignis am AUS_IN-Adapter löst die Umwandlung aus und führt zur Ausgabe eines entsprechenden Ereignisses und des konvertierten Datenwerts am AI_OUT-Adapter.

## Technische Besonderheiten

- **Reine Adapterkopplung** – Der Baustein besitzt keine eigenen Ein‑/Ausgangsvariablen, sondern definiert nur Adapter-Schnittstellen (Socket/Plug). Dies folgt dem Konzept der adapterbasierten Kommunikation in IEC 61499.
- **Unidirektionale Konvertierung** – Die Richtung ist festgelegt: von USINT nach INT. Eine Rückwärtskonvertierung ist nicht vorgesehen.
- **Nutzung eines Standard‑IEC‑61131‑Bausteins** – Die eigentliche Typkonvertierung erfolgt durch den etablierten FB `F_USINT_TO_INT`, der bereits in vielen Laufzeitumgebungen verfügbar ist.
- **Kein interner Zustand** – Der Composite-Baustein ist zustandslos; die Konvertierung wird bei jedem eingehenden Ereignis neu ausgelöst.

## Zustandsübersicht

Da der FB keine eigene Zustandsmaschine besitzt, existieren nur die impliziten Zustände des eingebetteten `F_USINT_TO_INT`. In der Praxis verhält sich der Baustein wie eine **kombinatorische Funktion**: Nach dem Eingang eines Ereignisses steht das Ausgangssignal zum nächsten Ausführungszyklus zur Verfügung. Ein definierter Fehlerzustand liegt nicht vor – die Konvertierung erfolgt gemäß der Spezifikation des IEC‑Bausteins.

## Anwendungsszenarien

- **Migration von USINT-basierter Hardware auf INT-basierte Steuerungen** – Ein System, das ursprünglich mit 8‑Bit‑Werten (USINT) arbeitet, kann über diesen Adapter an Komponenten angebunden werden, die 16‑Bit‑Analogwerte (INT) erwarten.
- **Kopplung unterschiedlicher Subsysteme** – In einer modularen Anlage nutzt ein Sensoradapter USINT, während die übergeordnete Steuerungseinheit INT‑Schnittstellen bereitstellt.
- **Prototypen und Testumgebungen** – Schnelle Integration von Komponenten mit abweichenden Datentypen ohne separate Konvertierungslogik in der Anwendungsebene.

## Vergleich mit ähnlichen Bausteinen

- **Direkte Konvertierungsbausteine** – FBs wie `F_USINT_TO_INT` oder `F_INT_TO_USINT` bieten die reine Typumwandlung, erfordern aber eine manuelle Verkabelung von Ereignissen und Daten. `AUS_TO_AI` kapselt dies in einem Adapter‑to‑Adapter‑Konzept, wodurch die Integration in adapterbasierte Architekturen vereinfacht wird.
- **Andere Adapter‑Converter** – Denkbar sind symmetrische Bausteine wie `AI_TO_AUS` (INT nach USINT) oder bidirektionale Varianten. `AUS_TO_AI` ist spezifisch für die unidirektionale Umwandlung von `AUS` nach `AI` ausgelegt.

## Fazit

Der Composite-Baustein `AUS_TO_AI` bietet eine saubere, adapterbasierte Lösung zur Konvertierung eines USINT-Werts in einen INT-Wert. Durch die Verkapselung des Standard‑Bausteins `F_USINT_TO_INT` und die klare Ereignis‑/Datenflusssteuerung eignet er sich hervorragend für die Integration heterogener Komponenten in IEC‑61499‑Systemen. Der Baustein ist wartungsarm, zustandslos und folgt den etablierten Konventionen der Adapter‑Schnittstellen.