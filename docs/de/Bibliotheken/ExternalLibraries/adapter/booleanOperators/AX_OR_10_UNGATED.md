# AX_OR_10_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AX_OR_10`](AX_OR_10.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

* * * * * * * * * *

## Einleitung

Der AX_OR_10_UNGATED ist ein generischer Funktionsblock zur Berechnung der logischen ODER-Verknüpfung von 10 Eingängen.

![AX_OR_10_UNGATED](AX_OR_10_UNGATED.svg)

## Schnittstellenstruktur

### **Adapter**

**Eingangsadapter:**

- **IN1** bis **IN10** (adapter::types::unidirectional::AX)

**Ausgangsadapter:**

- **OUT** (adapter::types::unidirectional::AX)

## Funktionsweise

Der Funktionsblock führt eine logische ODER-Verknüpfung der 10 Eingangssignale durch.

## Technische Besonderheiten

- Generischer Funktionsblock mit spezifischem Klassennamen 'GEN_AX_OR'
- Verwendet unidirektionale Adapter.

## Zustandsübersicht

Kombinatorischer Logikbaustein ohne Zustände.

## Anwendungsszenarien

Logische Verknüpfungen mit vielen Eingängen.

## ⚖️ Vergleich mit ähnlichen Bausteinen

- **AX_OR_2...9**: Varianten mit weniger Eingängen.

- **[`AX_OR_10`](AX_OR_10.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Adapter-basierter ODER-Baustein mit 10 Eingängen.
