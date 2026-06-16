# AX_ASR_RF_TRIG_X


![AX_ASR_RF_TRIG_X](./AX_ASR_RF_TRIG_X.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AX_ASR_RF_TRIG_X** dient der Erkennung von steigenden und fallenden Flanken eines booleschen Signals. Er bildet die erkannten Flanken auf ein Set/Reset-Ausgangssignal ab, wobei eine gekreuzte Zuordnung („crossed mapping“) verwendet wird: Die steigende Flanke löst einen Reset-Vorgang aus, die fallende Flanke einen Set-Vorgang. Der Baustein ist als reiner Adapterbaustein realisiert und nutzt intern den Standard-Funktionsblock `E_RF_TRIG`.

## Schnittstellenstruktur
Der FB besitzt keine direkten Ereignis- oder Dateneingänge/-ausgänge auf der Schnittstellenebene. Die gesamte Kommunikation erfolgt über zwei spezifizierte Adapter.

### **Ereignis-Eingänge**
Keine (Ereignissteuerung erfolgt über den Adapter **QI**)

### **Ereignis-Ausgänge**
Keine (Ereignisausgabe erfolgt über den Adapter **Q**)

### **Daten-Eingänge**
Keine (Dateneingabe erfolgt über den Adapter **QI**)

### **Daten-Ausgänge**
Keine (Datenausgabe erfolgt über den Adapter **Q**)

### **Adapter**

| Adapter | Typ | Richtung | Beschreibung |
|---------|-----|----------|--------------|
| **QI** | `adapter::types::unidirectional::AX` | Socket | Nimmt das auf Flanken zu prüfende boolesche Signal entgegen. Enthält das Ereignis `E1` (Auslöser) und das Datenwort `D1` (Wert). |
| **Q** | `adapter::types::unidirectional::ASR` | Plug | Gibt die Set/Reset-Ausgangssignale aus. Über die Ereignisse `SET` (fallende Flanke) und `RESET` (steigende Flanke) werden die entsprechenden Aktionen signalisiert. |

## Funktionsweise
Im FBNetzwerk des Bausteins wird eine Instanz des Standard-FBs `E_RF_TRIG` verwendet. Die Verbindungen sind wie folgt konfiguriert:

- Der Ereigniseingang `QI.E1` löst die Flankenerkennung aus und ist mit `E_RF_TRIG.EI` verbunden.
- Der Datenwert `QI.D1` wird an `E_RF_TRIG.QI` weitergeleitet.
- Das Ausgangsereignis `E_RF_TRIG.EF` (fallende Flanke) wird auf den Adapterausgang `Q.SET` gelegt.
- Das Ausgangsereignis `E_RF_TRIG.ER` (steigende Flanke) wird auf den Adapterausgang `Q.RESET` gelegt.

Durch diese Verschaltung ergibt sich das gewünschte „Crossed Mapping“:
- **Steigende Flanke** am Eingangswert → **RESET**-Impuls am Ausgang.
- **Fallende Flanke** am Eingangswert → **SET**-Impuls am Ausgang.

## Technische Besonderheiten
- Der Baustein ist vollständig als Adapter-FB realisiert, d. h. er besitzt keine eigenen Ereignis-/Datenschnittstellen, sondern kommuniziert ausschließlich über die definierten Adapter **QI** und **Q**.
- Die inverse Zuordnung der Flanken (Rising → Reset, Falling → Set) ist eine Besonderheit gegenüber der Standardverwendung von `E_RF_TRIG`.
- Die Implementierung folgt der Spezifikation IEC 61499-1 und verwendet die Bibliothek `adapter::events::unidirectional`.

## Zustandsübersicht
Der Baustein besitzt keinen eigenen Zustandsautomaten. Die interne Flankenerkennung erfolgt durch den integrierten FB `E_RF_TRIG`, dessen Zustandslogik (warten auf Flanke) für die Funktionalität verantwortlich ist.

## Anwendungsszenarien
- **Umgekehrte Set/Reset-Logik**: In Steuerungen, bei denen ein aktiver HIGH-Zustand durch eine steigende Flanke zurückgesetzt und durch eine fallende Flanke gesetzt werden soll.
- **Schnittstellenanpassung**: Wenn ein System Flankensignale in genau dieser Zuordnung erwartet (z. B. bei speziellen Aktorsteuerungen).
- **Vereinfachung von Adapter-Verkettungen**: Durch die Kapselung der inversen Logik in einem eigenen FB wird die Netzwerkstruktur übersichtlicher.

## Vergleich mit ähnlichen Bausteinen
- **`E_RF_TRIG`** (IEC 61499 Standard): Liefert steigende Flanke auf `ER` und fallende Flanke auf `EF`. `AX_ASR_RF_TRIG_X` invertiert diese Zuordnung.
- **`E_RS_TRIG`**: Erkennt nur steigende Flanken. Der vorliegende Baustein erkennt beide Flanken und ordnet sie unterschiedlichen Ausgängen zu.
- **`AX_ASR_TRIG_X`**: Mögliche alternative Varianten mit anderer Mapping-Logik unterscheiden sich in der Flanken-Ausgangs-Zuordnung.

## Fazit
Der Funktionsblock `AX_ASR_RF_TRIG_X` bietet eine spezialisierte Flankenerkennung mit invertierter Ausgangszuordnung. Durch die Verwendung von Adaptern fügt er sich nahtlos in eine ad-hoc basierte 61499-Kommunikation ein und ermöglicht eine klare, wiederverwendbare Kapselung dieser Logik. Er eignet sich besonders für Szenarien, in denen die Standardzuordnung von `E_RF_TRIG` nicht dem gewünschten Verhalten entspricht.