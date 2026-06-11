# ALI_TO_AL


![ALI_TO_AL](./ALI_TO_AL.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALI_TO_AL** ist ein Composite-Baustein, der einen **ALI-Adapter** (Datentyp LINT) in einen **AL-Adapter** (Datentyp LWORD) umwandelt. Er dient als Schnittstellenkonverter zwischen unterschiedlichen Adaptertypen und ermöglicht die nahtlose Datenweitergabe in 4diac- bzw. IEC-61499-Systemen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **Keine direkten Ereigniseingänge**  
  Ereignisse werden ausschließlich über den Socket-Adapter **ALI_IN** empfangen.

### **Ereignis-Ausgänge**
- **Keine direkten Ereignisausgänge**  
  Ausgangsereignisse werden ausschließlich über den Plug-Adapter **AL_OUT** gesendet.

### **Daten-Eingänge**
- **Keine direkten Dateneingänge**  
  Eingangsdaten (LINT) werden über den Socket-Adapter **ALI_IN** (Datenpunkt D1) bereitgestellt.

### **Daten-Ausgänge**
- **Keine direkten Datenausgänge**  
  Ausgangsdaten (LWORD) werden über den Plug-Adapter **AL_OUT** (Datenpunkt D1) abgegeben.

### **Adapter**

| Adapter | Richtung | Typ | Beschreibung |
|---------|----------|-----|--------------|
| **ALI_IN** | Socket | `adapter::types::unidirectional::ALI` | Empfängt einen LINT-Wert sowie ein Ereignis. |
| **AL_OUT** | Plug | `adapter::types::unidirectional::AL` | Sendet einen LWORD-Wert sowie ein Ereignis. |

## Funktionsweise

Der Baustein arbeitet intern mit einem einzelnen Konvertierungs-FB `F_LINT_TO_LWORD`. Sobald am Socket-Adapter **ALI_IN** ein Ereignis (E1) eintrifft, wird dieses an den internen Konverter (`REQ`-Eingang) weitergeleitet. Gleichzeitig wird der vom Adapter bereitgestellte LINT-Wert (D1) an den `IN`-Eingang des Konverters übergeben.

Der Konverter wandelt den LINT-Wert in einen LWORD-Wert um und signalisiert mit seinem `CNF`-Ausgang die Fertigstellung. Dieses Ereignis wird an den Plug-Adapter **AL_OUT** (E1) gesendet, zusammen mit dem konvertierten LWORD-Wert (OUT) auf dem Datenkanal D1.

## Technische Besonderheiten

- **Composite-FB**: Die eigentliche Typumwandlung erfolgt durch den eingebetteten Baustein `F_LINT_TO_LWORD` aus der IEC-61131-Standardbibliothek.
- **Unidirektionale Adapter**: Der Daten- und Ereignisfluss ist von ALI_IN zu AL_OUT festgelegt. Eine Rückwärtskommunikation ist nicht vorgesehen.
- **Keine Eigenzustände**: Der Baustein besitzt keinen eigenen Ablaufzustand (kein ECC), sondern leitet Ereignisse und Daten direkt weiter.

## Zustandsübersicht

Der Funktionsblock verfügt über keine internen Zustände. Er reagiert streng ereignisgesteuert: Jedes eingehende Ereignis am Socket **ALI_IN** löst genau eine Konvertierung und eine Ausgabe am Plug **AL_OUT** aus.

## Anwendungsszenarien

- **Adapterbrücke**: Einsatz in Systemen, die einen ALI-Adapter (LINT) verwenden, aber eine AL-Schnittstelle (LWORD) bereitstellen müssen.
- **Datenkonvertierung**: Umwandlung von LINT-Werten (z. B. lange Zählerstände) in LWORD-Werte (z. B. Bitmasken oder Speicheradressen) innerhalb einer Adapterkette.
- **Kompatibilität**: Nachrüstung älterer Komponenten, die LINT erwarten, in eine Umgebung, die LWORD über AL-Adapter nutzt.

## Vergleich mit ähnlichen Bausteinen

- **AL_TO_ALI**: Führt die umgekehrte Konvertierung von LWORD nach LINT durch.
- **F_LINT_TO_LWORD**: Reiner Konvertierungs-FB ohne Adaptereinbindung; direkter Datenaustausch ohne Kapselung.
- **Andere Adapterkonverter** (z. B. AL_TO_AL): Gleicher Adaptertyp, keine Typumwandlung.

Der ALI_TO_AL-Baustein hebt sich durch seine einfache Plug-and-Play-Fähigkeit innerhalb eines Adapter-basierten Designs hervor, da er die gesamte Konvertierungslogik und Ereignissteuerung in einem Baustein kapselt.

## Fazit

Der Composite-FB **ALI_TO_AL** ermöglicht eine saubere und standardkonforme Umwandlung von LINT- auf LWORD-Daten über unidirektionale Adapter. Er ist ideal für den Einsatz in modularen Automatisierungssystemen, die unterschiedliche Adapterdatentypen integrieren müssen. Durch die Nutzung der bewährten IEC-61131-Konvertierungsfunktion ist eine zuverlässige und performante Ausführung gewährleistet.