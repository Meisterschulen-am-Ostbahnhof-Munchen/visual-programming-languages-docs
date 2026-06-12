# UDINT_AUI_GT


![UDINT_AUI_GT](./UDINT_AUI_GT.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **UDINT_AUI_GT** realisiert einen Vergleichsbaustein vom Typ „größer als“ (greater than). Er vergleicht einen direkt übergebenen Eingangswert (`IN1`) mit einem zweiten Wert, der über einen Adapter (`IN2`) bereitgestellt wird. Das Ergebnis des Vergleichs wird über einen Ausgangsadapter (`OUT`) ausgegeben. Der Baustein ist als standard comparison function nach IEC 61131-3 klassifiziert.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `REQ` | Event | Dient als Service Request zur Auslösung des Vergleichs. Der Daten-Eingang `IN1` ist mit diesem Ereignis verknüpft. |

### **Ereignis-Ausgänge**

Keine expliziten Ereignis-Ausgänge vorhanden. Ereignisse werden über den Adapter `OUT` ausgegeben.

### **Daten-Eingänge**

| Name | Typ | Beschreibung |
|------|-----|--------------|
| `IN1` | ANY_ELEMENTARY | Erster Wert des Vergleichs (beliebiger elementarer Datentyp). |

### **Daten-Ausgänge**

Keine expliziten Daten-Ausgänge vorhanden. Daten werden über den Adapter `OUT` ausgegeben.

### **Adapter**

| Name | Richtung | Typ | Beschreibung |
|------|----------|-----|--------------|
| `IN2` | Socket (Eingang) | `adapter::types::unidirectional::AUI` | Liefert den zweiten Vergleichswert. Der Adapter stellt einen Ereignis-Ausgang `E1` und einen Daten-Ausgang `D1` bereit. Ein neuer Wert am Adapter löst intern den Vergleich aus. |
| `OUT` | Plug (Ausgang) | `adapter::types::unidirectional::AX` | Gibt das Vergleichsergebnis aus. Der Adapter besitzt einen Ereignis-Eingang `E1` und einen Daten-Eingang `D1`, die vom Baustein angesteuert werden. |

## Funktionsweise

Der Baustein führt einen „größer als“-Vergleich zwischen zwei Werten durch:

- Der erste Wert wird über den Daten-Eingang `IN1` bereitgestellt.
- Der zweite Wert wird dynamisch über den Socket-Adapter `IN2` (dessen Datenausgang `D1`) empfangen.
- Der Vergleich wird entweder durch ein Ereignis am Eingang `REQ` oder durch ein eintreffendes Ereignis am Adapter `IN2` (über `IN2.E1`) ausgelöst.
- Intern wird der IEC 61131-3-Funktionsblock `F_GT` (aus der Bibliothek `iec61131::comparison`) verwendet.
- Das Ergebnis (wahr/falsch) wird über den Plug-Adapter `OUT` ausgegeben: Der Datenausgang des internen `F_GT.OUT` wird auf `OUT.D1` gelegt, und das Abschlussereignis `F_GT.CNF` triggert `OUT.E1`.

## Technische Besonderheiten

- **Generischer Datentyp:** `IN1` ist vom Typ `ANY_ELEMENTARY`, sodass der Baustein mit verschiedenen elementaren Datentypen (z. B. INT, REAL, TIME) arbeiten kann.
- **Adapterbasierte Schnittstelle:** Die Verwendung von Adaptern für den zweiten Eingangswert und das Ergebnis ermöglicht eine flexible Einbindung in verschiedene Umgebungen und Protokolle.
- **Interne Wiederverwendung:** Der Baustein delegiert den eigentlichen Vergleich an den standardisierten `F_GT`-Baustein, was Konsistenz und Wartbarkeit erhöht.
- **Auslöseereignisse:** Der Vergleich kann sowohl über den `REQ`-Eingang als auch über ein Ereignis vom Adapter `IN2` gestartet werden – dies erlaubt reaktive Logiken.

## Zustandsübersicht

Der Baustein besitzt keinen eigenen Zustandsautomaten (ECC). Sein Verhalten wird vollständig durch die interne Verknüpfung mit dem Funktionsblock `F_GT` bestimmt. Eine Ausführung erfolgt immer dann, wenn eines der Eingangsereignisse (`REQ` oder `IN2.E1`) eintrifft. Nach Abschluss des Vergleichs wird das Ergebnis über den Ausgangsadapter mit einem Ereignis signalisiert.

## Anwendungsszenarien

- **Schwellwertüberwachung:** Vergleich eines Messwerts (`IN1`) mit einem Grenzwert, der über einen Adapter aus einer übergeordneten Steuerung bezogen wird.
- **Dynamische Vergleichslogik:** Wenn der zweite Vergleichswert nicht statisch, sondern aus einem anderen Baustein oder einer Datenquelle stammt, eignet sich die Adapter-Schnittstelle ideal.
- **Standardisierte Vergleichsfunktionen:** Einsatz in IEC 61131-3-Umgebungen, in denen ein Funktionsblock mit definierten Schnittstellen für „größer als“ benötigt wird.

## Vergleich mit ähnlichen Bausteinen

Einfache Vergleichsbausteine (z. B. `GT` mit zwei direkten Dateneingängen) bieten eine geringere Komplexität, erlauben aber keine dynamische Veränderung der zweiten Vergleichsgröße zur Laufzeit. Der `UDINT_AUI_GT` ist speziell für den Einsatz in adapterbasierten Architekturen konzipiert, bei denen die zweite Größe über einen unidirektionalen Socket geliefert wird. Der Ausgangsadapter `AX` erlaubt zudem eine einheitliche Weiterverarbeitung des Ergebnisses unabhängig vom restlichen System.

## Fazit

Der `UDINT_AUI_GT` ist ein spezialisierter Vergleichsbaustein, der die Stärken adapterbasierter Schnittstellen mit der Robustheit standardisierter IEC 61131-3-Funktionen verbindet. Seine flexible Triggermöglichkeit und der generische Eingangstyp machen ihn zu einem vielseitigen Werkzeug für Vergleichsaufgaben in komplexen Automatisierungslösungen.