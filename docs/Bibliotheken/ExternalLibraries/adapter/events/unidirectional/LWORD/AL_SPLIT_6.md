# AL_SPLIT_6


![AL_SPLIT_6](./AL_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AL_SPLIT_6** dient dazu, einen einzelnen unidirektionalen AL‑Adapter‑Eingang (Socket) auf sechs identische AL‑Adapter‑Ausgänge (Plugs) aufzuteilen. Er ermöglicht eine einfache Signalverteilung innerhalb einer 4diac‑Applikation, ohne dass zusätzliche Logik oder eine Zustandsmaschine erforderlich ist.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden.

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden.

### **Daten-Eingänge**

Keine Daten-Eingänge vorhanden.

### **Daten-Ausgänge**

Keine Daten-Ausgänge vorhanden.

### **Adapter**

| Richtung | Bezeichner | Typ                           | Beschreibung                                      |
|----------|------------|-------------------------------|---------------------------------------------------|
| In       | IN         | adapter::types::unidirectional::AL | Unidirektionaler AL‑Adapter als Eingangssignal.   |
| Out      | OUT1       | adapter::types::unidirectional::AL | Erster Ausgangskanal (identisch zu IN).          |
| Out      | OUT2       | adapter::types::unidirectional::AL | Zweiter Ausgangskanal.                           |
| Out      | OUT3       | adapter::types::unidirectional::AL | Dritter Ausgangskanal.                           |
| Out      | OUT4       | adapter::types::unidirectional::AL | Vierter Ausgangskanal.                           |
| Out      | OUT5       | adapter::types::unidirectional::AL | Fünfter Ausgangskanal.                           |
| Out      | OUT6       | adapter::types::unidirectional::AL | Sechster Ausgangskanal.                          |

## Funktionsweise

Der Baustein besitzt keinerlei interne Logik oder Zustandsmaschine. Er leitet das am Socket **IN** ankommende AL‑Signal unverändert an alle sechs Plugs **OUT1** … **OUT6** weiter. Jede Änderung oder jedes Ereignis am Eingang wird somit simultan auf alle Ausgänge übertragen. Der FB arbeitet rein strukturell als Verteiler (Splitter) und benötigt keine Aktivierung durch Ereignisse.

## Technische Besonderheiten

- **Generischer FB:** Der Baustein nutzt das Attribut `eclipse4diac::core::GenericClassName` mit dem Wert `GEN_AL_SPLIT`. Dadurch kann er in 4diac IDE als generischer Typ behandelt werden und erlaubt eine saubere Typsystem‑Integration.
- **Keine Daten‑/Ereignisschnittstelle:** Die Aufteilung erfolgt ausschließlich über die Adapter‑Schnittstelle. Es werden keine zusätzlichen Daten‑ oder Ereignisports benötigt.
- **Keine Laufzeitabhängigkeiten:** Da keine Algorithmen oder Zustände existieren, ist der Baustein ressourcenschonend und benötigt keine spezifische Initialisierung.

## Zustandsübersicht

Der FB besitzt keine Zustandsmaschine (kein ECC) und daher keinen definierten Zustandsautomaten. Das Verhalten ist vollständig durch die Schnittstellenstruktur und die reine Weiterleitung des Adaptersignals bestimmt.

## Anwendungsszenarien

- **Signalverteilung in der Landtechnik oder Automatisierung:** Ein zentraler AL‑Adapter (z. B. ein Steuerbefehl) soll an mehrere nachgelagerte Komponenten gleichzeitig gesendet werden.
- **Tests und Simulationen:** Ein Testsignal kann parallel an verschiedene Module verteilt werden, um das Systemverhalten zu überprüfen.
- **Redundante Pfade:** Der gleiche AL‑Adapter kann über mehrere Kanäle zu unterschiedlichen Verarbeitungseinheiten geführt werden.

## Vergleich mit ähnlichen Bausteinen

- **AL_SPLIT_2, AL_SPLIT_4** … **AL_SPLIT_N**: Diese Bausteine unterscheiden sich lediglich in der Anzahl der Ausgangskanäle. Die Funktionsweise ist identisch – eine einfache 1:N‑Aufteilung.
- **Andere Split‑Bausteine mit Ereignissen oder Daten:** Im Unterschied zu diesen besitzt **AL_SPLIT_6** keine Daten‑ oder Ereignisschnittstellen, sondern arbeitet rein über Adapter. Das vereinfacht die Konfiguration, schränkt aber die Typvielfalt ein.

## Fazit

Der **AL_SPLIT_6** ist ein kompakter und effizienter Funktionsblock zur Vervielfachung eines unidirektionalen AL‑Adapter‑Signals. Durch seinen generischen Charakter und die einfache Struktur eignet er sich hervorragend für alle Anwendungen, bei denen ein Eingangssignal auf mehrere Ausgänge verteilt werden muss, ohne zusätzliche Logik oder Ereignissteuerung.