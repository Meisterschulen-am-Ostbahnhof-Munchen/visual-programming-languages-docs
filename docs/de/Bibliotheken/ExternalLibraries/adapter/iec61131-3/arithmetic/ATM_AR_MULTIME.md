# ATM_AR_MULTIME

![ATM_AR_MULTIME](./ATM_AR_MULTIME.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ATM_AR_MULTIME** multipliziert einen Zeitwert (Typ TIME) mit einem numerischen Wert – die vollständig adapterbasierte Variante von [AR_MULTIME](AR_MULTIME.md). Anders als bei AR_MULTIME wird auch der Zeitwert (IN1) über einen Adapter (Typ `ATM`) statt über einen festen Dateneingang eingespeist. Der Baustein ist gemäß IEC 61131-3 als standard arithmetic function klassifiziert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine – der Baustein besitzt keine klassischen Ereigniseingänge, die Auslösung erfolgt ausschließlich über die Adapter-Sockets.

### **Ereignis-Ausgänge**

Keine expliziten Ereignisausgänge in der Interface-Liste. Das Ergebnis wird über den Adapter-Ausgang **OUT** bereitgestellt, welcher ein Ereignis (E1) sendet, sobald die Berechnung abgeschlossen ist.

### **Daten-Eingänge**

Keine direkten Daten-Eingänge.

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge. Das Multiplikationsergebnis wird über den Adapter-Ausgang **OUT** als Datenwert (D1) ausgegeben.

### **Adapter**

- **IN1** (Adapter, Typ `adapter::types::unidirectional::ATM`): Erster Funktionsinput – der zu multiplizierende Zeitwert.
- **IN2** (Adapter, Typ `adapter::types::unidirectional::AR`): Zweiter Funktionsinput – der numerische Multiplikator.
- **OUT** (Adapter, Typ `adapter::types::unidirectional::ATM`): Ausgang für das multiplizierte Ergebnis (TIME).

## Funktionsweise

Der Funktionsblock kapselt die Funktionalität des internen Bausteins **F_MULTIME** (Typ `iec61131::arithmetic::F_MULTIME`). Ein Ereignis an **IN1.E1** oder **IN2.E1** löst die Multiplikation aus: Der interne FB multipliziert **IN1.D1** (TIME) mit **IN2.D1** (numerischer Wert) und gibt das Ergebnis auf **OUT.D1** aus. Anschließend wird ein Ereignis an **OUT.E1** gesendet.

## Technische Besonderheiten

- **Vollständig adapterbasiert:** Im Gegensatz zu `AR_MULTIME`, das IN1 als klassischen Dateneingang erwartet, sind bei `ATM_AR_MULTIME` beide Operanden als Adapter-Sockets ausgeführt (IN1 vom Typ `ATM`, IN2 vom Typ `AR`).
- **Standardkonformität:** Der Baustein erfüllt die Anforderungen der IEC 61131-3 (Klassifikation: standard arithmetic function).
- **Interne Kapselung:** Die eigentliche Berechnung erfolgt durch den wiederverwendbaren Baustein F_MULTIME.

## Zustandsübersicht

Der Baustein besitzt keine explizite Zustandsmaschine. Die ereignisgesteuerte Abarbeitung erfolgt deterministisch: Warten auf ein Ereignis an IN1.E1 oder IN2.E1, Ausführen der Multiplikation, Senden des Ergebnisses.

## Anwendungsszenarien

- Skalierung von Zeitwerten, bei denen sowohl der Zeitwert als auch der Faktor bereits als Adapterverbindungen aus vorgeschalteten Bausteinen vorliegen.
- Modulare Netzwerke, in denen konsequent auf Adapter statt klassischer Datenverdrahtung gesetzt wird.

## Vergleich mit ähnlichen Bausteinen

- **AR_MULTIME:** Die gemischte Variante mit IN1 als klassischem Dateneingang statt Adapter-Socket.
- **ATM_AR_DIVTIME:** Dividiert statt zu multiplizieren, ansonsten strukturell identisch.

## Fazit

`ATM_AR_MULTIME` bietet eine konsequent adapterbasierte Multiplikation von Zeitwerten mit numerischen Faktoren und eignet sich besonders für Netzwerke, die durchgängig auf Adapterverbindungen aufbauen.
