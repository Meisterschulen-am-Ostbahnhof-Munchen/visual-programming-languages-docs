# AB_TO_ADI


![AB_TO_ADI](./AB_TO_ADI.svg)

* * * * * * * * * * *
## Einleitung
Der Funktionsblock **AB_TO_ADI** ist ein zusammengesetzter Baustein (Composite FB), der einen eingehenden BYTE-Wert eines **AB**-Adapters in einen DINT-Wert umwandelt und diesen über einen **ADI**-Adapter ausgibt. Er dient als einfache, unidirektionale Konvertierungsschnittstelle zwischen diesen beiden Adaptertypen.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine – die Ereignissteuerung erfolgt ausschließlich über den eingehenden Adapter (`AB_IN`).

### **Ereignis-Ausgänge**
Keine – Ereignisse werden nur über den ausgehenden Adapter (`ADI_OUT`) weitergegeben.

### **Daten-Eingänge**
Keine – die Daten werden über den `AB_IN`-Adapter bereitgestellt.

### **Daten-Ausgänge**
Keine – die konvertierten Daten werden über den `ADI_OUT`-Adapter ausgegeben.

### **Adapter**

| Typ     | Name    | Richtung | Kommentar                        |
|---------|---------|----------|----------------------------------|
| Socket  | `AB_IN` | Eingang  | BYTE-Adapter (Eingang)           |
| Plug    | `ADI_OUT` | Ausgang  | DINT-Adapter (Ausgang)           |

## Funktionsweise
Der FB enthält intern einen einzelnen Konvertierungsbaustein `F_BYTE_TO_DINT` (aus der IEC‑61131‑Bibliothek). Das eingehende Ereignis `E1` des Adapters `AB_IN` triggert die Konvertierung des Datenwerts `D1` (BYTE). Der daraus resultierende DINT-Wert wird über `OUT` an den Datenausgang `D1` des Adapters `ADI_OUT` weitergeleitet. Nach Abschluss der Konvertierung wird das Ereignis `E1` des Ausgangsadapters ausgelöst.

Die Ansteuerung erfolgt rein datenflussgesteuert: Jedes Ereignis am Eingangsadapter bewirkt eine einmalige Umwandlung und Weiterleitung.

## Technische Besonderheiten
- **Zusammengesetzter Baustein** – Keine eigene Zustandslogik, sondern alleinige Nutzung des internen FBs `F_BYTE_TO_DINT`.
- **Adapter-basiert** – Die Schnittstellen sind als Adapter definiert, was eine hohe Wiederverwendbarkeit und Austauschbarkeit mit anderen Bausteinen ermöglicht.
- **Lizenz** – Der Baustein ist unter der **Eclipse Public License 2.0** veröffentlicht.
- **Paket** – Der FB ist im Paket `adapter::conversion::unidirectional` organisiert.

## Zustandsübersicht
Der Baustein besitzt keinen eigenen Zustandsautomaten. Die Funktionalität ergibt sich allein aus der inneren Verschaltung des Konvertierungsbausteins. Die Verarbeitung ist strikt ereignisgesteuert und kombinatorisch.

## Anwendungsszenarien
- Umwandlung von BYTE-basierten Sensordaten (z. B. digitale Statuswerte) in ganzzahlige DINT‑Werte für weiterverarbeitende Steuerungslogiken.
- Anbindung von Komponenten, die den **AB**-Adapter verwenden, an Systeme, die den **ADI**-Adapter erwarten.
- Einsatz in Adapter‑basierten Kommunikationsarchitekturen, wo eine einheitliche Datenrepräsentation hergestellt werden muss.

## Vergleich mit ähnlichen Bausteinen
- **AB_TO_AI** – Konvertiert BYTE nach INT (16‑Bit‑Ganzzahl).
- **AB_TO_AREAL** – Konvertiert BYTE nach REAL.
- **AB_TO_ADI** – Spezifisch für BYTE nach DINT (32‑Bit‑Ganzzahl).

Alle diese Bausteine folgen dem gleichen Prinzip: Ein‑ und Ausgang sind als unidirektionale Adapter definiert, die intern eine Standard‑Konvertierungsfunktion nutzen.

## Fazit
Der FB `AB_TO_ADI` stellt eine minimalistische und zuverlässige Lösung zur Umwandlung von BYTE‑ in DINT‑Daten dar. Seine Adapter‑Schnittstellen ermöglichen eine nahtlose Integration in modulare Steuerungssysteme, ohne dass die zugrundeliegende Konvertierungslogik neu implementiert werden muss. Er ist besonders geeignet für Anwendungen, die auf klare Trennung von Kommunikationsprotokollen und Datenformaten Wert legen.