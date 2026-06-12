# AUI_EQ


![AUI_EQ](./AUI_EQ.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock AUI_EQ führt einen Gleichheitsvergleich zwischen zwei analogen Werten durch. Er ist als standard comparison function nach IEC 61131-3 klassifiziert und nutzt Adapter für die typsichere Kommunikation mit der Umgebung. Das Ergebnis wird als boolescher Wert ausgegeben, der genau dann `true` ist, wenn beide Eingangswerte gleich sind.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **IN1.E1** – Auslöser für den Vergleich (wird gesendet, wenn der erste Wert aktualisiert wird).
- **IN2.E1** – Alternativer Auslöser für den Vergleich (wird gesendet, wenn der zweite Wert aktualisiert wird).

Beide Ereignisse sind mit demselben internen Verarbeitungsereignis verbunden; der Vergleich wird bei Eintreffen eines der beiden Ereignisse angestoßen.

### **Ereignis-Ausgänge**
- **OUT.E1** – Bestätigung, dass der Vergleich abgeschlossen ist und das Ergebnis am Datenausgang anliegt.

### **Daten-Eingänge**
- **IN1.D1** – Erster zu vergleichender analoger Wert.
- **IN2.D1** – Zweiter zu vergleichender analoger Wert.

### **Daten-Ausgänge**
- **OUT.D1** – Ergebnis des Vergleichs: `true`, wenn `IN1.D1 == IN2.D1`, sonst `false`.

### **Adapter**
- **IN1** (Socket) – Adapter vom Typ `adapter::types::unidirectional::AUI`, kapselt den ersten Eingangswert und das zugehörige Ereignis.
- **IN2** (Socket) – Adapter vom Typ `adapter::types::unidirectional::AUI`, kapselt den zweiten Eingangswert und das zugehörige Ereignis.
- **OUT** (Plug) – Adapter vom Typ `adapter::types::unidirectional::AX`, kapselt das Ergebnis und das Ausgangsereignis.

Die Adapter ermöglichen eine lose Kopplung zwischen dem Baustein und seiner Umgebung und vereinfachen die Wiederverwendung in verschiedenen Anwendungen.

## Funktionsweise

AUI_EQ delegiert die eigentliche Vergleichslogik an den internen Funktionsblock `F_EQ` (Typ `iec61131::comparison::F_EQ`). Sobald an einem der Eingangsadapter (IN1 oder IN2) ein Ereignis eintrifft, wird die Berechnung gestartet. Der interne `F_EQ` vergleicht die beiden übergebenen Werte und liefert das boolesche Ergebnis. Nach Abschluss der Berechnung wird das Ergebnis über den Ausgangsadapter OUT ausgegeben und ein entsprechendes Ereignis gesendet.

Der Baustein ist ereignisgesteuert – er reagiert auf Eingangsereignisse und benötigt keinen eigenen zyklischen Aufruf.

## Technische Besonderheiten

- Der Funktionsblock verwendet ausschließlich Adapter für die Kommunikation, was eine hohe Flexibilität bei der Anbindung an verschiedene Datenquellen und -senken bietet.
- Intern basiert er auf dem Standard-Baustein `F_EQ` aus der IEC 61131‑Bibliothek, der eine robuste und getestete Vergleichsfunktion bereitstellt.
- Die Eingangsereignisse sind logisch ODER-verknüpft: Jedes der beiden Ereignisse löst eine Neuberechnung aus. Dies vereinfacht die Ansteuerung, da nur das aktuell aktualisierte Signal gesendet werden muss.
- Der Baustein ist in mehreren Versionen weiterentwickelt worden und wurde zuletzt 2025 aktualisiert.

## Zustandsübersicht

AUI_EQ besitzt keinen expliziten Zustandsautomaten. Sein Verhalten wird vollständig durch die Ereignisverarbeitung des internen `F_EQ` bestimmt. Nach dem Eintreffen eines Ereignisses durchläuft der Baustein eine Berechnung und sendet das Ergebnis – es gibt keine wartenden oder blockierenden Zustände.

## Anwendungsszenarien

- **Überwachung von Gleichheit**: Prüfen, ob zwei Sensormesswerte (z. B. Temperatur, Druck) denselben Wert aufweisen.
- **Alarmierung**: Auslösen eines Alarms, wenn zwei redundante Messungen voneinander abweichen (logische Negation des Ausgangs).
- **Steuerung**: Schalten von Aktoren, wenn ein Sollwert mit einem Istwert übereinstimmt.
- **Plausibilitätsprüfung**: Vergleichen von Analogwerten aus unterschiedlichen Quellen zur Fehlererkennung.

## Vergleich mit ähnlichen Bausteinen

Neben `AUI_EQ` existieren in der IEC 61131‑Bibliothek weitere Vergleichsbausteine wie `AUI_GT` (größer), `AUI_LT` (kleiner) und `AUI_NE` (ungleich). Diese teilen sich die gleiche Adapter‑Schnittstelle, unterscheiden sich jedoch in der Vergleichsoperation. `AUI_EQ` ist speziell für den Gleichheitstest optimiert und bietet keine anderen Vergleichslogiken. Für umfassendere Vergleiche (z B. größer oder gleich) sind Kombinationen mit logischen Bausteinen erforderlich.

## Fazit

Der Funktionsblock AUI_EQ realisiert eine einfache und zuverlässige Gleichheitsprüfung für analoge Werte. Die Verwendung von Adaptern macht ihn äußerst anpassungsfähig für verschiedene Automatisierungsumgebungen. Seine ereignisgesteuerte Arbeitsweise und die interne Nutzung eines standardisierten Vergleichsbausteins gewährleisten eine konsistente und performante Ausführung. AUI_EQ ist damit ein grundlegender Baustein für Überwachungs- und Steuerungsaufgaben, bei denen Wertegleichheit festgestellt werden muss.