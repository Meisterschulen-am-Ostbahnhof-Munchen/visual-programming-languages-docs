# AL_SPLIT_4


![AL_SPLIT_4](./AL_SPLIT_4.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AL_SPLIT_4** ist ein generischer Baustein, der einen einzelnen Adapter-Eingang (Socket) vom Typ `adapter::types::unidirectional::AL` auf vier separate Ausgänge (Plugs) desselben Typs aufteilt. Er dient dazu, einen eingehenden Adapter-Datenstrom auf mehrere parallele Verbraucher zu verteilen, ohne dass die Daten selbst verändert werden.

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

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AL` | **IN** | Socket (Eingang) | Eingehender Adapter-Datenstrom, der auf alle Ausgänge verteilt wird. |
| `adapter::types::unidirectional::AL` | **OUT1** | Plug (Ausgang) | Erster Ausgang – erhält eine identische Kopie des Eingangsdatenstroms. |
| `adapter::types::unidirectional::AL` | **OUT2** | Plug (Ausgang) | Zweiter Ausgang – erhält eine identische Kopie des Eingangsdatenstroms. |
| `adapter::types::unidirectional::AL` | **OUT3** | Plug (Ausgang) | Dritter Ausgang – erhält eine identische Kopie des Eingangsdatenstroms. |
| `adapter::types::unidirectional::AL` | **OUT4** | Plug (Ausgang) | Vierter Ausgang – erhält eine identische Kopie des Eingangsdatenstroms. |

## Funktionsweise

Der Baustein ist ein reiner Signalverteiler. Er besitzt eine interne Logik, die – sobald der Adapter-Eingang **IN** mit einer Datenquelle verbunden ist – die eingehenden Datenpakete (Events und Daten) unmittelbar und unverändert an alle vier Ausgangsadapter **OUT1** bis **OUT4** weiterleitet. Es findet keine Pufferung, Verzögerung oder logische Verarbeitung statt. Jeder Ausgang erhält exakt dieselben Informationen wie der Eingang.

## Technische Besonderheiten

- **Generischer Baustein:** Die Klasse `GEN_AL_SPLIT` ist im Attribut `eclipse4diac::core::GenericClassName` definiert, was bedeutet, dass der Baustein als Vorlage für verschiedene Ausprägungen des Adaptertyps `AL` wiederverwendet werden kann.
- **Keine Zustände oder Zeitsteuerung:** Da der FB ausschließlich leitungsbasiert arbeitet und keinerlei Verarbeitungslogik besitzt, existieren keine internen Zustände oder nebenläufige Ausführungssequenzen.
- **Adapter-Typ:** Der verwendete Adapter `adapter::types::unidirectional::AL` ist ein standardisierter, unidirektionaler Adapter aus der Bibliothek `adapter::types::unidirectional`. Seine genaue Schnittstelle (enthaltene Events und Daten) wird durch die Adapterdefinition vorgegeben und nicht durch den Split-Baustein selbst beeinflusst.

## Zustandsübersicht

Der Baustein besitzt keinen Zustandsautomaten. Er arbeitet statisch und verteilt das Eingangssignal permanent auf alle Ausgänge.

## Anwendungsszenarien

- **Verteilen eines Steuerungssignals** an mehrere parallele Aktoreinheiten, z. B. in der Agrartechnik (wie im Copyright-Hinweis der HR Agrartechnik GmbH angedeutet).
- **Aufteilen einer Messdatenquelle** auf mehrere Analyse- oder Logging-Module.
- **Testen und Debugging:** Ein Original-Adaptersignal kann auf mehrere Ausgänge geführt werden, um es gleichzeitig an verschiedene Test-Instanzen zu senden.

## Vergleich mit ähnlichen Bausteinen

- **AL_SPLIT_2** – teilt ein AL-Signal auf zwei Ausgänge auf (weniger Ausgänge, geringere Fan-out-Kapazität).
- **AL_MERGE** – führt mehrere AL-Eingänge zu einem Ausgang zusammen (umgekehrte Funktion).
- **Ereignisbasierte Split-Bausteine (z. B. SPLIT_EVENT)** – teilen nur Ereignisse auf, ohne die assoziierten Datenadapter zu duplizieren.

Im Gegensatz zu diesen Bausteinen arbeitet `AL_SPLIT_4` ausschließlich auf Adapterebene und kopiert vollständige Adapter-Kommunikationsströme.

## Fazit

Der Funktionsblock **AL_SPLIT_4** ist ein einfacher, effizienter Signalfächer für den Adaptertyp `AL`. Er eignet sich ideal für alle Anwendungen, in denen ein einzelner Adapterdatenstrom an mehrere Verbraucher weitergegeben werden muss, ohne zusätzliche Logik oder Verzögerungen. Seine generische Natur erlaubt den Einsatz in unterschiedlichen Kontexten der Automatisierungstechnik, insbesondere in der Landmaschinensteuerung, wie vom Hersteller vorgesehen.