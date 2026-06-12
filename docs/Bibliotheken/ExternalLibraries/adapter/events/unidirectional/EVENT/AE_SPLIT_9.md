# AE_SPLIT_9


![AE_SPLIT_9](./AE_SPLIT_9.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock AE_SPLIT_9 dient dazu, ein eingehendes unidirektionales Adapter-Event (AE) auf neun identische Ausgänge aufzuteilen. Er ist als generischer Baustein implementiert und ermöglicht die Verteilung von Ereignissen an mehrere nachgeschaltete Funktionsblöcke.

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
- **IN** (Socket): Unidirektionaler AE-Adapter (Eingang)
- **OUT1 … OUT9** (Plugs): Unidirektionale AE-Adapter (Ausgänge)

## Funktionsweise
Der Baustein empfängt über den Socket "IN" ein Adapter-Event. Jedes eintreffende Ereignis wird unverzögert und ohne weitere Logik auf alle neun Plug-Ausgänge (OUT1 bis OUT9) dupliziert. Somit verhält sich der FB wie ein 1:9-Splitter für AE-Signale.

## Technische Besonderheiten
- Der Baustein ist als generischer FB (GenericClassName = 'GEN_AE_SPLIT') implementiert, was eine flexible Wiederverwendung in unterschiedlichen Kontexten ermöglicht.
- Es werden keine Daten verarbeitet; ausschließlich das Adapter-Interface wird durchgeschliffen.
- Die Ausgänge sind voneinander unabhängig; ein Fehler an einem Ausgang beeinflusst die anderen nicht.

## Zustandsübersicht
Der FB besitzt keinen internen Zustand. Er arbeitet rein kombinatorisch: Ein Ereignis am Eingang führt sofort zu Ereignissen an allen Ausgängen.

## Anwendungsszenarien
- Verteilung eines Sensor-Ereignisses an mehrere Steuerungslogiken.
- Broadcast eines Alarms an verschiedene Überwachungseinheiten.
- Aufteilung eines Triggersignals für parallele Verarbeitungspfade.

## Vergleich mit ähnlichen Bausteinen
- AE_SPLIT_2, AE_SPLIT_4: gleiche Funktionalität mit weniger Ausgängen.
- Im Unterschied zu Daten-Splittern (z.B. SPLIT_INT) werden hier ausschließlich Ereignisse (ohne Daten) vervielfältigt.

## Fazit
AE_SPLIT_9 ist ein einfacher, aber nützlicher Baustein zur Ereignisverteilung in IEC 61499-Systemen. Seine generische Natur und die klare 1:9-Aufteilung machen ihn ideal für Anwendungen, die eine breite Streuung von Adapter-Events erfordern.