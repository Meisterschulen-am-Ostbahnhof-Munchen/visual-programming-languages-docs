# AULI_SPLIT_3


![AULI_SPLIT_3](./AULI_SPLIT_3.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AULI_SPLIT_3** dient der Verteilung eines einzelnen AULI-Adaptersignals auf drei identische Ausgänge. Er fungiert als einfacher Splitter für unidirektionale AULI-Verbindungen und ermöglicht den Broadcast eines Signals an mehrere nachfolgende Komponenten. Der Baustein ist generisch ausgelegt und kann für verschiedene AULI-Typen instantiiert werden.

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
|------|-----|--------------|
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
Im Gegensatz zu einem **AULI_MERGE** (der mehrere Eingänge auf einen Ausgang zusammenführt) oder einem **AULI_SELECT** (der wahlweise einen von mehreren Eingängen durchschaltet), bietet **AULI_SPLIT_3** eine reine Fan-out-Funktion. Es gibt keinen Entscheidungsmechanismus, keine Priorisierung und keine Datenmodifikation. Ähnliche Splitter mit anderer Ausgangsanzahl (z. B. SPLIT_2) unterscheiden sich lediglich in der Anzahl der Ausgänge.

## Fazit
**AULI_SPLIT_3** ist ein einfacher, aber essenzieller Baustein zur Vervielfachung unidirektionaler AULI-Signale. Durch die generische Auslegung und die verzögerungsfreie Weiterleitung eignet er sich besonders für Broadcast-Szenarien in der Automatisierungstechnik, wo ein Signal gleichzeitig an mehrere Verbraucher übergeben werden muss.