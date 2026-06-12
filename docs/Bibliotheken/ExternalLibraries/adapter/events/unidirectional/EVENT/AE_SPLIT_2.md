# AE_SPLIT_2


![AE_SPLIT_2](./AE_SPLIT_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AE_SPLIT_2** dient als generischer Verteiler für ein eingehendes Adapter-Ereignis (AE). Er empfängt ein unidirektionales Ereignis über den Socket `IN` und leitet es ohne Verzögerung oder Veränderung an die beiden Ausgangs-Plugs `OUT1` und `OUT2` weiter. Der Baustein wird als generischer FB (GenericClassName: `'GEN_AE_SPLIT'`) implementiert, sodass er theoretisch für verschiedene Adaptertypen verwendbar ist – vorausgesetzt, sie entsprechen dem unidirektionalen AE-Protokoll.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine. Der FB besitzt keine klassischen Ereigniseingänge. Die Ereignisweiterleitung erfolgt ausschließlich über den Adapter-Socket.

### **Ereignis-Ausgänge**

Keine. Die Ereignisweitergabe geschieht über die Adapter-Plugs.

### **Daten-Eingänge**

Keine.

### **Daten-Ausgänge**

Keine.

### **Adapter**

| Rolle | Name | Typ | Beschreibung |
|-------|------|-----|--------------|
| Socket (Eingang) | `IN` | `adapter::types::unidirectional::AE` | Empfängt ein unidirektionales Ereignis, das auf beide Ausgänge verteilt wird. |
| Plug (Ausgang 1) | `OUT1` | `adapter::types::unidirectional::AE` | Erster Ausgang für das duplizierte Ereignis. |
| Plug (Ausgang 2) | `OUT2` | `adapter::types::unidirectional::AE` | Zweiter Ausgang für das duplizierte Ereignis. |

## Funktionsweise

Sobald am Adapter-Socket `IN` ein Ereignis eintrifft, wird es **sofort und parallel** an beide Ausgangs-Plugs `OUT1` und `OUT2` weitergeleitet. Der Baustein führt keinerlei Logik, Filterung oder Verzögerung durch – er fungiert als reiner Splitter auf Adapterebene. Die Verteilung erfolgt ereignisgetreu: Jedes einzelne eingehende Ereignis erscheint an beiden Ausgängen.

## Technische Besonderheiten

- **Generischer Typ**: Der FB ist als generischer Baustein deklariert (`GenericClassName = 'GEN_AE_SPLIT'`). Dies erlaubt eine Anpassung an andere, vom Benutzer definierte Adaptertypen, solange sie die unidirektionale Ereignisschnittstelle nutzen. In der vorliegenden Konfiguration ist der konkrete Typ `adapter::types::unidirectional::AE` hinterlegt.
- **Keine Zustände / Algorithmen**: Da keinerlei Logik oder Speicherverhalten implementiert ist, besitzt der FB keinen ECC (Execution Control Chart) und keine internen Zustände.
- **Latenz**: Die Weiterleitung erfolgt verzögerungsfrei innerhalb eines Ausführungszyklus.

## Zustandsübersicht

Der FB besitzt **keinen Zustandsautomaten**. Das Verhalten ist rein kombinatorisch: Jedes eingehende Adapter-Ereignis wird sofort dupliziert und an beiden Ausgängen ausgegeben.

## Anwendungsszenarien

- **Ereignisverteilung**: Ein Sensor oder eine Steuerung liefert ein Ereignis (z. B. „Start“ oder „Alarm“), das von zwei unabhängigen Subsystemen verarbeitet werden muss.
- **Parallelschaltung**: Aufteilung eines Signals zur gleichzeitigen Ansteuerung zweier Aktoren oder zur parallelen Datenaufnahme.
- **Prototyping**: Temporäre Verzweigung eines Ereignisstroms während der Entwicklungs- und Testphase.

## Vergleich mit ähnlichen Bausteinen

- **AE_SPLIT_1**: Ein Splitter mit nur einem Ausgang (d. h. reine Durchleitung) – meist überflüssig.
- **E_SPLIT_2**: Klassischer Ereignis-Splitter für standardmäßige Ereigniseingänge/-ausgänge. Im Gegensatz zu `AE_SPLIT_2` arbeitet dieser auf der Ereignisebene ohne Adapter-Kopplung.
- **AE_ROUTER**: Ein adapterbasierter Verteiler, der Ereignisse gezielt an bestimmte Ausgänge weiterleiten kann (z. B. basierend auf Datenwerten). `AE_SPLIT_2` ist simpler und verteilt immer an alle Ausgänge.

## Fazit

Der **AE_SPLIT_2** ist ein minimaler, aber nützlicher Funktionsblock zur einfachen Verteilung von Adapter-Ereignissen. Seine generische Natur macht ihn flexibel einsetzbar, während die fehlende Logik für geringe Latenz und hohe Zuverlässigkeit sorgt. Er eignet sich ideal für alle Szenarien, in denen ein Ereignis an mehrere Empfänger weitergegeben werden muss.