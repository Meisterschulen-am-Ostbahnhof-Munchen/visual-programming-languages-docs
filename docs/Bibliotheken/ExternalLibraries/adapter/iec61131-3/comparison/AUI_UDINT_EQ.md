# AUI_UDINT_EQ


![AUI_UDINT_EQ](./AUI_UDINT_EQ.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUI_UDINT_EQ** realisiert einen Gleichheitsvergleich zwischen zwei Werten. Der erste Operand wird über einen Adaptereingang (IN1) vom Typ `AUI` bereitgestellt, der zweite über den Dateneingang `IN2` als `UDINT`. Das Vergleichsergebnis wird als boolescher Wert über einen Adapterausgang (OUT) vom Typ `AX` ausgegeben. Der Baustein ist für den Einsatz in IEC 61499-Systemen konzipiert und basiert auf dem Standardvergleichsbaustein `F_EQ`.

## Schnittstellenstruktur
### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ | Event | Service Request – löst den Vergleich aus. |
| (über Adapter IN1.E1) | Event | Ereignis vom Adaptereingang – löst ebenfalls den Vergleich aus. |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| OUT.E1 | Event | Bestätigungsereignis am Adapterausgang, signalisiert Abschluss des Vergleichs. |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| IN2 | UDINT | Zweiter Operand (unsigned double integer). |
| (über Adapter IN1.D1) | (implizit) | Erster Operand, typabhängig (via AUI-Adapter). |

### **Daten-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| OUT.D1 | BOOL | Vergleichsergebnis: TRUE, wenn die Werte gleich sind, sonst FALSE. |

### **Adapter**

| Typ | Richtung | Name | Kommentar |
|-----|----------|------|-----------|
| `adapter::types::unidirectional::AUI` | Socket (Eingang) | IN1 | Stellt den ersten Operanden als Wert (D1) und ein Ereignis (E1) zur Verfügung. |
| `adapter::types::unidirectional::AX` | Plug (Ausgang) | OUT | Gibt das Vergleichsergebnis als booleschen Wert (D1) sowie ein Bestätigungsereignis (E1) aus. |

## Funktionsweise
Der FB wird entweder durch ein Ereignis am Eingang `REQ` oder durch ein Ereignis vom Adapter `IN1.E1` aktiviert. Beide Ereignisse führen zur Ausführung des internen Bausteins `F_EQ`, der die Werte von `IN1.D1` (erster Operand) und `IN2` (zweiter Operand) auf Gleichheit prüft. Das Ergebnis wird als BOOL über `OUT.D1` ausgegeben. Gleichzeitig wird ein Ereignis an `OUT.E1` gesendet, um den Abschluss des Vergleichs zu signalisieren.

## Technische Besonderheiten
- **Doppelte Trigger-Möglichkeit:** Der FB kann sowohl über den separaten Ereigniseingang `REQ` als auch über das mit dem Adapter eingehende Ereignis `IN1.E1` aktiviert werden. Dies ermöglicht eine flexible Integration: Entweder zyklisch getaktet oder direkt durch die ankommende AUI-Nachricht.
- **Interne Nutzung des Standardbausteins `F_EQ`:** Die eigentliche Vergleichslogik wird durch den IEC 61131-Baustein `F_EQ` realisiert. Dies gewährleistet Standardkonformität und Wiederverwendbarkeit.
- **Adapterbasierte Ein-/Ausgabe:** Über die Adapter `AUI` und `AX` wird eine typisierte, modulare Verbindung in 4diac-Architekturen ermöglicht.

## Zustandsübersicht
Der FB besitzt keinen eigenen ECC, sondern delegiert die Ausführung an den internen `F_EQ`. Das Verhalten ist rein ereignisgesteuert:

- Bei Eintreffen eines Ereignisses (REQ oder IN1.E1) wird einmalig der Vergleich durchgeführt.
- Nach Abschluss wird das Ergebnis über OUT ausgegeben.
- Es gibt keine internen Zustände oder sequenziellen Abläufe.

## Anwendungsszenarien
- **Überwachung eines Prozesswerts:** Vergleiche einen gemessenen Wert (z. B. Drehzahl, Temperatur) der über einen AUI-Adapter geliefert wird, mit einem festen Schwellwert (als UDINT) und melde Gleichheit.
- **Trigger-gesteuerte Prüfung:** In zyklischen Steuerungsaufgaben kann der Vergleich über das REQ-Event getaktet werden, unabhängig von eingehenden AUI-Nachrichten.
- **Verknüpfung mit adapterbasierten Komponenten:** Der FB lässt sich einfach in bestehende 4diac-Netzwerke einfügen, die AUI- und AX-Adapter verwenden.

## Vergleich mit ähnlichen Bausteinen
- **CMP_EQ (Standard-Vergleich):** Einfacher Gleichheitsvergleich zweier Datenwerte ohne Adapter. `AUI_UDINT_EQ` bietet dagegen eine adaptergestützte Schnittstelle, die eine lose Kopplung mit anderen IEC 61499-Komponenten erlaubt.
- **AUI_UDINT_GT, AUI_UDINT_LT:** Analoge Bausteine für Größer/Kleiner-Vergleiche mit identischer Adapterstruktur. `AUI_UDINT_EQ` fokussiert speziell auf die Gleichheitsprüfung.
- **Direkte Nutzung von `F_EQ`:** Der Baustein kapselt den `F_EQ` und erweitert ihn um adapterspezifische Ereignissteuerung.

## Fazit
Der `AUI_UDINT_EQ` ist ein kompakter und flexibler Funktionsblock für Gleichheitsvergleiche in IEC 61499-Umgebungen. Die Kombination aus adapterbasiertem Zugriff auf den ersten Operanden und einem direkten Dateneingang für den zweiten Operanden, zusammen mit der doppelten Trigger-Möglichkeit, macht ihn vielseitig einsetzbar. Die Nutzung des Standardbausteins `F_EQ` gewährleistet dabei eine robuste und standardkonforme Funktionalität.