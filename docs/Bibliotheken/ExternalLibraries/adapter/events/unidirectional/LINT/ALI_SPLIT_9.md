# ALI_SPLIT_9


![ALI_SPLIT_9](./ALI_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung
Der **ALI_SPLIT_9** ist ein generischer Funktionsbaustein (FB) innerhalb der 4diac-IDE, der dazu dient, ein eingehendes **ALI**-Adapter-Signal (unidirektional) auf bis zu neun separate Ausgangsadapter aufzuteilen. Der Baustein ist als generischer Typ („Generic FB“) realisiert und wird üblicherweise über die Typ-Parameter `eclipse4diac::core::GenericClassName` und `eclipse4diac::core::TypeHash` individualisiert. Ziel ist die flexible Signalverteilung ohne zusätzliche Logik, rein auf Adapterebene.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine

### **Ereignis-Ausgänge**
Keine

### **Daten-Eingänge**
Keine

### **Daten-Ausgänge**
Keine

### **Adapter**

| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | IN | `ALI` (unidirektional) | Einspeisung des zu verteilenden ALI-Signals |
| Plug (Ausgang 1) | OUT1 | `ALI` (unidirektional) | Erster Ausgang – identische Kopie des Eingangssignals |
| Plug (Ausgang 2) | OUT2 | `ALI` (unidirektional) | Zweiter Ausgang |
| Plug (Ausgang 3) | OUT3 | `ALI` (unidirektional) | Dritter Ausgang |
| Plug (Ausgang 4) | OUT4 | `ALI` (unidirektional) | Vierter Ausgang |
| Plug (Ausgang 5) | OUT5 | `ALI` (unidirektional) | Fünfter Ausgang |
| Plug (Ausgang 6) | OUT6 | `ALI` (unidirektional) | Sechster Ausgang |
| Plug (Ausgang 7) | OUT7 | `ALI` (unidirektional) | Siebter Ausgang |
| Plug (Ausgang 8) | OUT8 | `ALI` (unidirektional) | Achter Ausgang |
| Plug (Ausgang 9) | OUT9 | `ALI` (unidirektional) | Neunter Ausgang |

## Funktionsweise
Der Baustein arbeitet passiv als reiner **Signalverteiler**. Das am Socket **IN** anliegende ALI-Adapterprotokoll wird unverändert auf alle neun Plug-Ausgänge **OUT1…OUT9** dupliziert. Es findet keinerlei Datenverarbeitung, Ereignisgenerierung oder Filterung statt. Jeder Ausgang bietet eine identische logische und zeitliche Kopie des eingehenden Signals.

Die interne Implementierung erfolgt über die generischen Typmechanismen der 4diac-IDE (`GenericClassName` und `TypeHash`), sodass der Baustein zur Laufzeit spezifisch an die Anforderungen des Projekts angepasst werden kann.

## Technische Besonderheiten
- **Generischer Baustein**: Der FB ist als `GEN_ALI_SPLIT` deklariert (laut Attribut `eclipse4diac::core::GenericClassName`). Konkrete Instanzen erhalten eine eindeutige Typkennung über `TypeHash`.
- **Keine Ereignisse oder Daten**: Die Schnittstelle besteht ausschließlich aus Adaptern; es gibt keine Ereignis-Ein-/Ausgänge oder Data-Ein-/Ausgänge.
- **Unidirektionale ALI-Adapter**: Alle verwendeten Adapter sind vom Typ `adapter::types::unidirectional::ALI`, d. h. die Kommunikation erfolgt in einer Richtung (Eingang → Ausgänge). Rückwirkung von den Ausgängen auf den Eingang ist nicht vorgesehen.
- **Einfache Topologie**: Der Baustein realisiert eine 1:9-Sternverteilung ohne zusätzliche Puffer oder Synchronisierung.

## Zustandsübersicht
Der Baustein besitzt keinen eigenen Zustandsautomaten. Sein Verhalten ist rein durch die Adapter-Schnittstellen bestimmt: Solange der Socket **IN** ein Signal liefert, sind alle neun Plugs aktiv. Sobald **IN** inaktiv wird (kein Signal), liefern auch alle Ausgänge kein Signal.

## Anwendungsszenarien
- **Verteilen eines ALI-Bus-Signals** an mehrere nachgeschaltete Subsysteme (z. B. Sensordaten an mehrere Steuergeräte).
- **Aufteilung eines Master-Signals** für Redundanz oder Parallelverarbeitung in der Anlagensteuerung.
- **Test- und Debugging-Umgebungen**: Ein ALI-Signal kann gleichzeitig an ein Analysegerät und an mehrere Zielsysteme weitergeleitet werden.
- **Generische Schnittstellenerweiterung**: Wenn ein System nur einen ALI-Ausgang besitzt, aber mehrere Verbraucher bedient werden müssen.

## Vergleich mit ähnlichen Bausteinen
- **ALI_SPLIT_2 / ALI_SPLIT_4 / ALI_SPLIT_8**: Varianten mit 2, 4 oder 8 Ausgängen. Der hier beschriebene Baustein bietet die maximale Aufteilung auf 9 Kanäle.
- **ALI_MERGE** (hypothetisch): Fasst mehrere ALI-Eingänge zu einem Ausgang zusammen – gegenteilige Funktion.
- **Ereignisbasierte Splitter**: Andere Bausteine nutzen Ereignisse zur Steuerung des Signalflusses; dieser Adapter-Splitter arbeitet signalgetrieben ohne Ereignislogik.

## Fazit
Der **ALI_SPLIT_9** ist ein spezialisierter, generischer Adapter-FB, der in der industriellen Automatisierung mit 4diac-IDE die einfache und zuverlässige Verteilung eines unidirektionalen ALI-Signals auf bis zu neun separate Empfänger ermöglicht. Durch seine reine Adapterschnittstelle ist er besonders ressourcenschonend und eignet sich ideal für sternförmige Vernetzungstopologien in IEC 61499-basierten Systemen. Der generische Charakter erlaubt eine flexible Anpassung an spezifische Typanforderungen ohne Änderung der Bausteinstruktur.