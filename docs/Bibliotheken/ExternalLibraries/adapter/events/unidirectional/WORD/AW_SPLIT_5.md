# AW_SPLIT_5


![AW_SPLIT_5](./AW_SPLIT_5.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AW_SPLIT_5** dient dazu, einen eingehenden AW‑Adapter („Aktor/Wege“) auf fünf separate, identische AW‑Ausgänge zu verteilen. Er ist als generischer Baustein ausgelegt und kann in Steuerungsarchitekturen eingesetzt werden, in denen ein einzelnes Signal oder eine Datenverbindung auf mehrere parallele Pfade aufgeteilt werden muss.

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
* **IN** (Socket) – Typ: `adapter::types::unidirectional::AW`  
  Eingangsschnittstelle für den ursprünglichen AW‑Datenstrom.
* **OUT1** bis **OUT5** (Plugs) – Typ: `adapter::types::unidirectional::AW`  
  Fünf parallele Ausgangsschnittstellen, die jeweils das gleiche Signal wie am Eingang bereitstellen.

## Funktionsweise
Der FB leitet den eingehenden AW‑Adapter passiv auf alle fünf Ausgänge weiter. Eine aktive Logik oder Zustandsmaschine ist nicht vorhanden – die Verteilung erfolgt strukturell durch die Verdrahtung im FB‑Inneren. Änderungen am Eingang werden unverzögert an allen Ausgängen sichtbar.

## Technische Besonderheiten
* **Generischer Baustein** – Der FB ist als generischer Typ (`GEN_AW_SPLIT`) deklariert und kann in unterschiedlichen Kontexten wiederverwendet werden.
* **Keine Ereignissteuerung** – Die Signalweitergabe erfolgt kontinuierlich ohne ereignisgesteuerte Aktivierung.
* **Unidirektionale Adapter** – Der verwendete Adaptertyp `AW` ist unidirektional, d. h. die Daten fließen nur vom Eingang zu den Ausgängen. Eine Rückmeldung von den Ausgängen ist nicht vorgesehen.

## Zustandsübersicht
Der FB besitzt keine interne Zustandsmaschine (ECC). Es gibt keine definierten Zustände oder Zustandsübergänge – die Funktionalität ist rein datenflussorientiert.

## Anwendungsszenarien
* **Verteilen eines Sensorsignals** an mehrere nachgelagerte Steuerungseinheiten.
* **Parallele Ansteuerung** mehrerer Aktoren, die denselben Sollwert oder dasselbe Kommando erhalten sollen.
* **Testaufbauten** – Ein Signal aufzeichnen oder gleichzeitig an verschiedene Simulations‑ und Analysekomponenten weiterleiten.

## Vergleich mit ähnlichen Bausteinen
* **AW_SPLIT_N** – Ein weiterer generischer Split‑FB, der auf eine variable Anzahl von Ausgängen erweiterbar ist. `AW_SPLIT_5` ist eine spezialisierte Variante mit fest fünf Ausgängen.
* **Reine Daten‑Splitter** – Diese arbeiten auf Datentypen wie `INT` oder `BOOL` und nutzen andere Schnittstellentypen. `AW_SPLIT_5` ist speziell für den AW‑Adapter konzipiert.

## Fazit
Der `AW_SPLIT_5` ist ein einfacher, aber nützlicher Baustein zur Aufteilung eines AW‑Adapter‑Signals auf fünf parallele Pfade. Durch seinen generischen Aufbau kann er flexibel in unterschiedlichen Steuerungsprojekten der 4diac‑IDE eingesetzt werden. Die fehlende Ereignis- und Daten‑Schnittstelle reduziert die Komplexität auf das Wesentliche – die reine Signalvervielfältigung.