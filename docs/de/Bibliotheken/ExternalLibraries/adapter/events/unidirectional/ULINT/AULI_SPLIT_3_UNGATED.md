# AULI_SPLIT_3_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AULI_SPLIT_3`](AULI_SPLIT_3.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AULI_SPLIT_3_UNGATED](./AULI_SPLIT_3_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AULI_SPLIT_3_UNGATED** dient der Verteilung eines einzelnen AULI-Adaptersignals auf drei identische Ausgänge. Er fungiert als einfacher Splitter für unidirektionale AULI-Verbindungen und ermöglicht den Broadcast eines Signals an mehrere nachfolgende Komponenten. Der Baustein ist generisch ausgelegt und kann für verschiedene AULI-Typen instantiiert werden.

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

| Name | Typ | Beschreibung |
| ------ | ----- | -------------- |
| IN | AULI (unidirectional) | Eingangsadapter – empfängt das zu verteilende Signal. |
| OUT1 | AULI (unidirectional) | Erster Ausgangsadapter. |
| OUT2 | AULI (unidirectional) | Zweiter Ausgangsadapter. |
| OUT3 | AULI (unidirectional) | Dritter Ausgangsadapter. |

## Funktionsweise

Der Baustein leitet jede am Eingangsadapter **IN** ankommende AULI-Information (sowohl Ereignisse als auch zugehörige Daten) direkt und ohne Verzögerung an alle drei Ausgangsadapter **OUT1**, **OUT2** und **OUT3** weiter. Es findet keine Filterung, Transformation oder Pufferung statt. Die Ausgänge sind identisch und arbeiten parallel, sodass das Eingangssignal gleichzeitig an drei unabhängige Empfänger gesendet wird.

## Technische Besonderheiten

- **Generischer Typ:** Der FB ist als generischer Baustein deklariert (GenericClassName `'GEN_AULI_SPLIT'`). Er kann mit verschiedenen konkreten AULI-Adaptertypen verwendet werden, sofern diese dem unidirektionalen AULI-Interface entsprechen.
- **Latenz:** Durch die reine Weiterleitung ohne interne Logik ist die Latenz minimal und beschränkt sich auf die Durchlaufzeit des Laufzeitsystems.
- **Copyright:** Der Baustein unterliegt dem Eclipse Public License 2.0 (SPDX-License-Identifier: EPL-2.0).

## Zustandsübersicht

Der Baustein besitzt keinen internen Zustandsautomaten. Die Funktionalität ist rein kombinatorisch und kontinuierlich aktiv – sobald ein Signal am Eingang anliegt, wird es an alle Ausgänge weitergegeben.

## Anwendungsszenarien

- **Signalverteilung:** Ein AULI-Signal (z. B. Steuerbefehle, Messwerte) soll an mehrere unabhängige Aktoren oder Subsysteme gesendet werden.
- **Test- und Simulationsaufbauten:** Ein Testsignal wird aufgezeichnet oder von einer Quelle gesendet und parallel an mehrere Überwachungs- oder Analyseblöcke verteilt.
- **Redundante Verarbeitung:** Derselbe Eingangswert wird von mehreren parallel arbeitenden Logiken gleichzeitig benötigt.

## Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu einem **AULI_MERGE** (der mehrere Eingänge auf einen Ausgang zusammenführt) oder einem **AULI_SELECT** (der wahlweise einen von mehreren Eingängen durchschaltet), bietet **AULI_SPLIT_3_UNGATED** eine reine Fan-out-Funktion. Es gibt keinen Entscheidungsmechanismus, keine Priorisierung und keine Datenmodifikation. Ähnliche Splitter mit anderer Ausgangsanzahl (z. B. SPLIT_2) unterscheiden sich lediglich in der Anzahl der Ausgänge.

- **[`AULI_SPLIT_3`](AULI_SPLIT_3.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

**AULI_SPLIT_3_UNGATED** ist ein einfacher, aber essenzieller Baustein zur Vervielfachung unidirektionaler AULI-Signale. Durch die generische Auslegung und die verzögerungsfreie Weiterleitung eignet er sich besonders für Broadcast-Szenarien in der Automatisierungstechnik, wo ein Signal gleichzeitig an mehrere Verbraucher übergeben werden muss.
