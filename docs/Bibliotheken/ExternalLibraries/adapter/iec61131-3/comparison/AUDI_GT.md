# AUDI_GT


![AUDI_GT](./AUDI_GT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AUDI_GT realisiert einen Vergleich zweier Werte auf „Größer als“ (greater than). Er ist als IEC 61131-3 konformer Vergleichsbaustein konzipiert und verwendet ein Adapter-basiertes Interface, um die Werte und Ereignisse zu übertragen. Der Baustein ist Teil der Bibliothek iec61131::comparison.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **IN1.E1** – Ereigniseingang für den ersten Wert (über Adapter IN1)
- **IN2.E1** – Ereigniseingang für den zweiten Wert (über Adapter IN2)
Beide Ereignisse werden auf den internen REQ-Eingang des Bausteins F_GT verbunden.

### **Ereignis-Ausgänge**
- **OUT.E1** – Ereignisausgang, der nach Abschluss des Vergleichs aktiviert wird (über Adapter OUT). Das Ergebnis liegt dann am Datenausgang an.

### **Daten-Eingänge**
- **IN1.D1** – Erster Eingangswert (über Adapter IN1, Typ abhängig vom Adapter AUDI)
- **IN2.D1** – Zweiter Eingangswert (über Adapter IN2, Typ abhängig vom Adapter AUDI)

### **Daten-Ausgänge**
- **OUT.D1** – Ergebnis des Vergleichs: TRUE, wenn IN1 > IN2, sonst FALSE (über Adapter OUT, Typ abhängig vom Adapter AX)

### **Adapter**
- **Socket IN1** (Typ: `adapter::types::unidirectional::AUDI`) – Verbindung für den ersten zu vergleichenden Wert.
- **Socket IN2** (Typ: `adapter::types::unidirectional::AUDI`) – Verbindung für den zweiten zu vergleichenden Wert.
- **Plug OUT** (Typ: `adapter::types::unidirectional::AX`) – Ausgabe des Vergleichsergebnisses.

Die verwendeten Adapter sind unidirektional und stellen je einen Ereignis- und einen Datenport bereit.

## Funktionsweise

Der Baustein AUDI_GT kapselt den elementaren Vergleichsbaustein F_GT aus der IEC 61131-3 Bibliothek. Die Eingangsadapter IN1 und IN2 liefern je einen Wert (D1) sowie ein Startsignal (E1). Beide Ereignisse werden auf den REQ-Eingang des F_GT verbunden, sodass der Vergleich ausgelöst wird, sobald mindestens einer der Ereignisse eintritt. Intern führt F_GT den Vergleich der beiden Werte durch. Das Ergebnis (BOOL) wird über den Ausgangsadapter OUT bereitgestellt, wobei gleichzeitig ein Ereignis (E1) generiert wird.

## Technische Besonderheiten

- Der Baustein verwendet **Adapter** anstelle von direkten Ein-/Ausgangs-Ports, was eine flexible Kapselung und Wiederverwendung der Schnittstellen ermöglicht.
- Die Ereignisse beider Eingänge werden auf denselben REQ-Eingang des internen F_GT zusammengeführt. Dies bedeutet, dass der Baustein bei jedem eintreffenden Ereignis an IN1 oder IN2 den Vergleich neu durchführt.
- Der Baustein gibt das Ergebnis als BOOL-Wert aus (TRUE/FALSE). Die genauen Datentypen der Adapter (AUDI, AX) sind anwendungsspezifisch und können je nach Kontext variieren.
- Der Baustein ist als Teil der Bibliothek `iec61131::comparison` gekennzeichnet und folgt dem IEC 61131-3 Standard.

## Zustandsübersicht

Der Baustein AUDI_GT besitzt keinen eigenen Zustandsautomaten. Die gesamte Logik wird durch den internen F_GT realisiert, der einen einfachen kombinatorischen Vergleich ausführt. Es gibt keine internen Zustände oder Speicherverhalten; das Ergebnis wird bei jeder Aktivierung neu berechnet.

## Anwendungsszenarien

- **Prozessüberwachung**: Vergleich von Messwerten (z.B. Temperatur, Druck) mit einem Schwellwert. Wenn Wert1 > Wert2, wird ein Alarm ausgelöst.
- **Logische Entscheidungen**: In Automatisierungsabläufen, z.B. Sortierlogik oder Prioritätssteuerungen.
- **Sicherheitsfunktionen**: Überprüfung, ob ein aktueller Wert einen Grenzwert überschreitet.
- **Adapter-basierte Systeme**: Überall dort, wo modulare, wiederverwendbare Schnittstellen über Adapter gewünscht sind.

## Vergleich mit ähnlichen Bausteinen

- **GT (Greater Than)**: Einfache Vergleicher wie `F_GT` (IEC 61131-3) haben direkte Eingänge. `AUDI_GT` erweitert dies auf eine adapterbasierte Schnittstelle, was die Integration in heterogene Systeme erleichtert.
- **GE (Greater or Equal)**, **LT (Less Than)**, **EQ (Equal)**: Analoge Bausteine für andere Vergleichsoperationen. Der vorliegende Baustein unterstützt nur „Größer als“.
- **Vergleichskaskaden**: Mehrere AUDI_GT können zu komplexeren Ausdrücken verknüpft werden, indem Ausgänge an Eingänge weiterer Bausteine geschaltet werden.

## Fazit

Der AUDI_GT ist ein dedizierter Vergleichsbaustein für die „Größer als“-Funktion mit adaptern basierten Ein- und Ausgängen. Er bietet eine standardisierte, modulare Schnittstelle gemäß IEC 61131-3 und eignet sich besonders für den Einsatz in verteilten Automatisierungssystemen, die eine lose Kopplung der Komponenten erfordern. Dank der Adaptertechnologie kann der Baustein flexibel in verschiedene Kontexte eingebettet werden.