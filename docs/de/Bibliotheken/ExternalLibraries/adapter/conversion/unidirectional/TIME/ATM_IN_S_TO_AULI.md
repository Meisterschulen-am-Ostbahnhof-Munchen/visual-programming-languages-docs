# ATM_IN_S_TO_AULI

![ATM_IN_S_TO_AULI](ATM_IN_S_TO_AULI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **ATM_IN_S_TO_AULI** ist ein Composite-Baustein, der einen `TIME`-Wert (übertragen über den [ATM](../../../types/unidirectional/TIME/ATM.md)-Adapter) in Sekunden auf einen `ULINT`-Wert (64-Bit-Ganzzahl (vorzeichenlos)) umrechnet und über den [AULI](../../../types/unidirectional/ULINT/AULI.md)-Adapter ausgibt. Er gehört zur Blockfamilie `ATM_IN_<EINHEIT>_TO_<ZIELTYP>`, die dieselbe Umrechnung für alle vier Zeiteinheiten (MS, NS, S, US) und alle fünf Zielganzzahl-/Gleitkommatypen bereitstellt.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

- Keine direkt sichtbaren Ereignis-Eingänge. Die Ereignissteuerung erfolgt indirekt über den Adapter **IN** (Ereignis E1).

### **Ereignis-Ausgänge**

- Keine direkt sichtbaren Ereignis-Ausgänge. Die Ereignissignalisierung erfolgt indirekt über den Adapter **OUT** (Ereignis E1).

### **Daten-Eingänge**

- Keine direkt sichtbaren Daten-Eingänge. Der Eingabewert wird über den Adapter **IN** (Datenpunkt D1 vom Typ `TIME`) bereitgestellt.

### **Daten-Ausgänge**

- Keine direkt sichtbaren Daten-Ausgänge. Der Ausgabewert wird über den Adapter **OUT** (Datenpunkt D1 vom Typ `ULINT`) bereitgestellt.

### **Adapter**

| Adapter | Rolle | Typ | Beschreibung |
|---------|-------|-----|--------------|
| IN | Socket | adapter::types::unidirectional::ATM | Unidirektionaler `TIME`-Adapter als Eingangsschnittstelle. |
| OUT | Plug | adapter::types::unidirectional::AULI | Unidirektionaler `ULINT`-Adapter als Ausgangsschnittstelle, Wert von `IN` in Sekunden ausgedrückt. |

## Funktionsweise

Der Baustein enthält intern einen einzelnen Funktionsbaustein `F_TIME_IN_S_TO_ULINT` aus der IEC-61131-3-Standardbibliothek. Die Ablaufsteuerung erfolgt rein ereignisgesteuert:

1. Ein Ereignis am Eingangsadapter **IN.E1** triggert den Eingang **REQ** des internen Umrechnungsbausteins.
2. Der Datenwert **IN.D1** (`TIME`) wird an den Eingang **IN** von `F_TIME_IN_S_TO_ULINT` übergeben.
3. `F_TIME_IN_S_TO_ULINT` rechnet den Zeitwert in eine Sekunden-Zahl vom Typ `ULINT` um und signalisiert dies über seinen Ausgang **CNF**.
4. Dieses Ereignis wird an den Ausgangsadapter **OUT.E1** weitergeleitet.
5. Gleichzeitig wird der umgerechnete Wert (Ausgang **OUT** von `F_TIME_IN_S_TO_ULINT`) an den Datenpunkt **OUT.D1** übergeben.

Der gesamte Vorgang erfolgt synchron und ohne Zwischenspeicherung – jede erfolgreiche Umrechnung löst sofort ein Ausgangsereignis aus.

## Technische Besonderheiten

- **Einheitenumrechnung nach IEC 61131-3**: Der interne Baustein `F_TIME_IN_S_TO_ULINT` interpretiert den intern in Nanosekunden gehaltenen `TIME`-Wert als Zahl in Sekunden und liefert das Ergebnis als `ULINT` (64-Bit-Ganzzahl (vorzeichenlos)).
- **Unidirektionale Adapter**: Sowohl der Eingangs- als auch der Ausgangsadapter sind unidirektional ausgelegt. Eine Rückwärtskommunikation ist nicht vorgesehen.
- **Composite-Struktur ohne eigene Logik**: Der Baustein besteht ausschließlich aus einer Daten- und einer Ereignisverbindung zum internen Umrechnungsbaustein; es gibt kein eigenes ECC.
- **Leerer TypeHash**: Wie bei allen generierten Konvertierungs-Composites in diesem Paket ist `eclipse4diac::core::TypeHash` leer (`''`).

## Zustandsübersicht

Der Baustein besitzt keine eigene Zustandsmaschine. Der Ablauf lässt sich als einfacher Schritt beschreiben:

| Schritt | Aktion |
| --------- | -------- |
| 1 | Warten auf Ereignis an **IN.E1** |
| 2 | Umrechnung des Datenwerts von `TIME` (Sekunden) nach `ULINT` über `F_TIME_IN_S_TO_ULINT` |
| 3 | Ausgabe des umgerechneten Werts an **OUT.D1** und Ereignis an **OUT.E1** |
| 4 | Rückkehr zu Schritt 1 |

## Anwendungsszenarien

- **Anzeige/Weiterverarbeitung von Zeitdauern**: Eine über einen `ATM`-Adapter transportierte Zeitdauer (z. B. eine Zykluszeit oder Verzögerung) soll als Zahl in Sekunden an einen Adapter-Socket vom Typ `AULI` weitergegeben werden, etwa zur Anzeige auf einem Panel oder zur Weiterverarbeitung in einer Berechnung.
- **Schnittstellenanpassung**: In Netzwerken, die konsequent auf Adapterverbindungen statt klassischer Datenverdrahtung setzen, ermöglicht der Baustein die nahtlose Umwandlung eines Zeit- in einen Zahlenadapter.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **Gleiche Einheit, andere Zieltypen**: [ATM_IN_S_TO_ADI](ATM_IN_S_TO_ADI.md), [ATM_IN_S_TO_ALI](ATM_IN_S_TO_ALI.md), [ATM_IN_S_TO_ALR](ATM_IN_S_TO_ALR.md), [ATM_IN_S_TO_AUDI](ATM_IN_S_TO_AUDI.md)
- **Gleicher Zieltyp, andere Einheiten**: [ATM_IN_MS_TO_AULI](ATM_IN_MS_TO_AULI.md), [ATM_IN_NS_TO_AULI](ATM_IN_NS_TO_AULI.md), [ATM_IN_US_TO_AULI](ATM_IN_US_TO_AULI.md)
- **[ATM_TIME_TO_TM](ATM_TIME_TO_TM.md) / [ATM_TM_TO_TIME](ATM_TM_TO_TIME.md)**: reine Adapter-↔-Variablen-Durchreichung ohne Einheitenumrechnung, im Gegensatz zur numerischen Umrechnung von `ATM_IN_S_TO_AULI`.

## Fazit

`ATM_IN_S_TO_AULI` liefert eine standardkonforme, vollständig adapterbasierte Umrechnung eines `TIME`-Werts in Sekunden auf einen `ULINT`-Wert und fügt sich damit nahtlos in Netzwerke ein, die konsequent auf Adapterverbindungen statt klassischer Datenverdrahtung setzen.
