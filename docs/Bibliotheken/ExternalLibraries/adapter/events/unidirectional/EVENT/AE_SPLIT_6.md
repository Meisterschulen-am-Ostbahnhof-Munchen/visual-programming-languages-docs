# AE_SPLIT_6


![AE_SPLIT_6](./AE_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AE_SPLIT_6** verteilt einen eingehenden AE‑Adapter (Typ `adapter::types::unidirectional::AE`) auf sechs identische Ausgänge. Es handelt sich um einen generischen Baustein, der für verschiedene AE‑Typen wiederverwendet werden kann. Der Name leitet sich von der 1:6‑Aufteilung ab: Ein Eingang wird auf sechs Ausgänge gesplittet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| **Socket (Eingang)** | IN | `adapter::types::unidirectional::AE` | Eingehender AE‑Adapter, dessen Signal auf alle Ausgänge vervielfältigt wird. |
| **Plug (Ausgang)** | OUT1 | `adapter::types::unidirectional::AE` | Erster Ausgang, identische Kopie des Eingangssignals. |
| **Plug (Ausgang)** | OUT2 | `adapter::types::unidirectional::AE` | Zweiter Ausgang, identische Kopie des Eingangssignals. |
| **Plug (Ausgang)** | OUT3 | `adapter::types::unidirectional::AE` | Dritter Ausgang, identische Kopie des Eingangssignals. |
| **Plug (Ausgang)** | OUT4 | `adapter::types::unidirectional::AE` | Vierter Ausgang, identische Kopie des Eingangssignals. |
| **Plug (Ausgang)** | OUT5 | `adapter::types::unidirectional::AE` | Fünfter Ausgang, identische Kopie des Eingangssignals. |
| **Plug (Ausgang)** | OUT6 | `adapter::types::unidirectional::AE` | Sechster Ausgang, identische Kopie des Eingangssignals. |

## Funktionsweise
Der Baustein leitet das am Socket **IN** anliegende Adaptersignal unverändert an alle sechs Plugs (**OUT1** … **OUT6**) weiter. Es findet keinerlei logische Verarbeitung, Filterung oder Verzögerung statt – die Verteilung erfolgt passiv und verzögerungsfrei. Somit verhält sich der FB wie ein reiner 1:6‑Splitter für den unidirektionalen Adaptertyp `AE`.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist mit dem Attribut `eclipse4diac::core::GenericClassName` als `'GEN_AE_SPLIT'` gekennzeichnet. Dadurch kann er in verschiedenen Projekten mit unterschiedlichen, aber strukturgleichen AE‑Adaptertypen verwendet werden – erst zur Projektlaufzeit wird der konkrete Typ festgelegt.
- **Unidirektionalität**: Alle Adapter sind als unidirektional deklariert, d.h. die Daten‑/Ereignisübertragung erfolgt nur vom Eingang (Socket) zu den Ausgängen (Plugs). Rückwirkungen sind nicht vorgesehen.
- **Keine Zustandslogik**: Der Baustein besitzt keine internen Zustände, keine Ereignisse und keine Daten‑Ein‑/Ausgänge. Er ist vollständig durch seine Adapterschnittstellen definiert.

## Zustandsübersicht
Der FB **AE_SPLIT_6** ist ein rein kombinatorischer Baustein ohne Zustandsautomat. Es gibt keine internen Schritte, Transitionen oder Aktionen – die Verteilung erfolgt direkt und permanent.

## Anwendungsszenarien
- **Signalverteilung**: Mehrere nachfolgende Funktionsblöcke sollen das gleiche AE‑Signal empfangen, z.B. um parallele Berechnungen oder parallele Ausgabe zu starten.
- **Bus‑Struktur**: In einer Steuerungsarchitektur, in der ein Ereignis an mehrere Komponenten (Aktoren, Anzeigen, Logger) gesendet werden muss, ohne die Quelle zu belasten.
- **Adapternetzwerke**: Wenn ein AE‑Adapter von einem Sender bereitgestellt wird und mehrere Empfänger unabhängig voneinander darauf zugreifen sollen.

## Vergleich mit ähnlichen Bausteinen
- **E_SPLIT‑Bausteine**: Diese teilen ein Ereignissignal (z.B. in **E_SPLIT** oder **E_F_SPLIT**) auf mehrere Ereignisausgänge auf. Der **AE_SPLIT_6** hingegen arbeitet auf Adapterebene und verteilt den gesamten Adapterverbund, der sowohl Ereignisse als auch Daten enthalten kann – je nach konkreter Adapterinstanziierung.
- **AE_SPLIT_2 / AE_SPLIT_4**: Varianten mit zwei oder vier Ausgängen. Der **AE_SPLIT_6** bietet die maximale Anzahl von sechs Ausgängen in dieser Familie.
- **MUX/DEMUX‑Bausteine**: Diese selektieren oder kombinieren Signale. Der **AE_SPLIT_6** hingegen vervielfältigt das Signal ohne Auswahl.

## Fazit
Der **AE_SPLIT_6** ist ein einfacher, aber nützlicher generischer Funktionsblock zur 1:6‑Verteilung eines unidirektionalen AE‑Adapters. Durch seine generische Auslegung kann er in unterschiedlichsten Automatisierungs‑ und Steuerungsumgebungen eingesetzt werden, in denen ein Signal mehrfach benötigt wird. Er arbeitet ohne Verzögerung und ohne eigene Logik, was ihn besonders effizient und zuverlässig macht.