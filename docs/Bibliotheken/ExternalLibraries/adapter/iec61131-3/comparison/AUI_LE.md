# AUI_LE


![AUI_LE](./AUI_LE.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AUI_LE** führt einen Vergleich zweier analoger Eingangswerte auf „kleiner oder gleich“ (less or equal) durch. Er ist als Composite-Baustein realisiert, der intern den IEC‑61131‑3 Baustein `F_LE` verwendet. Das Ergebnis (ein BOOL‑Wert) wird über einen Ausgangsadapter bereitgestellt. Der FB eignet sich für ereignisgesteuerte Grenzwertüberwachungen in Automatisierungssystemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **IN1.E1** (über Adapter IN1) – Ereignis, das den Vergleich auslöst, sobald der erste Eingangswert bereitsteht.
- **IN2.E1** (über Adapter IN2) – Ereignis, das den Vergleich auslöst, sobald der zweite Eingangswert bereitsteht.

### **Ereignis-Ausgänge**
- **OUT.E1** (über Adapter OUT) – Ereignis, das nach erfolgreichem Vergleich ausgegeben wird und signalisiert, dass das Ergebnis gültig ist.

### **Daten-Eingänge**
- **IN1.D1** (über Adapter IN1) – Erster Eingangswert (analog, Typ gemäß Adapter `AUI`).
- **IN2.D1** (über Adapter IN2) – Zweiter Eingangswert (analog, Typ gemäß Adapter `AUI`).

### **Daten-Ausgänge**
- **OUT.D1** (über Adapter OUT) – Ergebnis des Vergleichs (BOOL): `TRUE`, wenn IN1 ≤ IN2, sonst `FALSE`.

### **Adapter**
- **IN1** – Socket (Typ: `adapter::types::unidirectional::AUI`) für den ersten Analogwert.
- **IN2** – Socket (Typ: `adapter::types::unidirectional::AUI`) für den zweiten Analogwert.
- **OUT** – Plug (Typ: `adapter::types::unidirectional::AX`) für das Vergleichsergebnis.

## Funktionsweise
Der Baustein enthält ein internes Netzwerk mit einem `F_LE`-Baustein. Die Ereignisse der beiden Eingangsadapter (`IN1.E1` und `IN2.E1`) sind mit dem `REQ`-Eingang des `F_LE` verbunden. Jedes eintreffende Ereignis (egal an welchem Eingang) startet den Vergleich der aktuellen Datenwerte `IN1.D1` und `IN2.D1`. Der interne `F_LE` berechnet `(IN1 ≤ IN2)` und legt das Ergebnis auf seinem Ausgang `OUT` ab. Dieses wird über den Adapter `OUT.D1` ausgegeben und gleichzeitig ein Ereignis über `OUT.E1` gesendet.

## Technische Besonderheiten
- **Adapterbasierte Schnittstelle**: Die Ein- und Ausgänge sind als unidirektionale Adapter realisiert, was eine flexible Kopplung mit anderen Bausteinen ermöglicht.
- **Ereignissteuerung**: Der Vergleich wird durch jedes anliegende Ereignis an einem der beiden Eingänge ausgelöst – es muss nicht zwingend ein gleichzeitiges Ereignis an beiden Eingängen vorliegen.
- **Interner Standardbaustein**: Die Vergleichslogik nutzt den geprüften IEC‑61131‑3 Baustein `F_LE`.
- **Lizenz**: Der Baustein steht unter der Eclipse Public License 2.0 (EPL‑2.0), Copyright (c) 2013 TU Wien ACIN.

## Zustandsübersicht
Der Baustein besitzt keine explizite Zustandsmaschine. Er arbeitet ereignisgesteuert und seine Ausgabe ist das direkte Ergebnis des internen kombinatorischen Vergleichs. Nach der Ereignisbearbeitung liegt das Ergebnis bis zum nächsten Ereignis stabil an.

## Anwendungsszenarien
- **Grenzwertüberwachung**: Prüfen, ob ein Messwert (z. B. Temperatur, Druck) einen eingestellten Schwellwert nicht überschreitet.
- **Steuerungslogik**: Auslösen einer Aktion, wenn zwei analoge Signale in einer festgelegten Relation stehen (z. B. Füllstand ≤ Maximalfüllstand).
- **Sicherheitsfunktionen**: Vergleich von redundanten Sensorwerten auf „kleiner gleich“ zur Fehlererkennung.

## Vergleich mit ähnlichen Bausteinen
- **AUI_LT**: Führt den Vergleich „kleiner“ (strict less) durch.
- **AUI_EQ**: Prüft auf Gleichheit der beiden Werte.
- **AUI_GT**: Prüft auf „größer“.
- **AUI_GE**: Prüft auf „größer oder gleich“.  
Alle diese Bausteine besitzen die gleiche Adapterschnittstelle (AUI für Eingänge, AX für Ausgang) und unterscheiden sich nur in der Vergleichsoperation.

## Fazit
Der Baustein `AUI_LE` bietet eine einfache und zuverlässige Möglichkeit, analoge Signale auf „kleiner oder gleich“ zu prüfen. Dank der adapterbasierten Schnittstelle und der ereignisgesteuerten Ausführung lässt er sich nahtlos in Automatisierungsprojekte integrieren, die standardisierte Vergleichsfunktionen benötigen.