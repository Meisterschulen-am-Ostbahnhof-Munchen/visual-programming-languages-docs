# AD_SPLIT_6_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AD_SPLIT_6`](AD_SPLIT_6.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AD_SPLIT_6_UNGATED](./AD_SPLIT_6_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock **AD_SPLIT_6_UNGATED** dient der Verteilung eines eingehenden Adapters vom Typ `adapter::types::unidirectional::AD` auf sechs separate Ausgangsadapter desselben Typs. Er ist als generischer Baustein konzipiert, der eine einfache 1:6-Aufteilung ohne zusätzliche Logik oder Zustandsverwaltung realisiert.

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
| ----- | ------ | ---------- | -------------- |
| `adapter::types::unidirectional::AD` | IN | Socket | Eingangsadapter, der auf die sechs Ausgänge verteilt wird. |
| `adapter::types::unidirectional::AD` | OUT1 | Plug | Erster Ausgangsadapter (identisch zu IN). |
| `adapter::types::unidirectional::AD` | OUT2 | Plug | Zweiter Ausgangsadapter. |
| `adapter::types::unidirectional::AD` | OUT3 | Plug | Dritter Ausgangsadapter. |
| `adapter::types::unidirectional::AD` | OUT4 | Plug | Vierter Ausgangsadapter. |
| `adapter::types::unidirectional::AD` | OUT5 | Plug | Fünfter Ausgangsadapter. |
| `adapter::types::unidirectional::AD` | OUT6 | Plug | Sechster Ausgangsadapter. |

## Funktionsweise

Der Baustein leitet den über den Socket **IN** empfangenen Adapter unverändert an alle sechs Plugs (**OUT1** bis **OUT6**) weiter. Es findet keine Datenmanipulation, Filterung oder Verzögerung statt. Der Adapter wird als Referenz oder durch direkte Kopplung (abhängig von der Laufzeitumgebung) auf die Ausgänge multipliziert. Somit erhalten alle angeschlossenen nachfolgenden Funktionsbausteine denselben Adapter-Inhalt.

## Technische Besonderheiten

- **Generischer Baustein**: Das Attribut `eclipse4diac::core::GenericClassName` ist auf `'GEN_AD_SPLIT'` gesetzt, was die Wiederverwendung in verschiedenen Typkonfigurationen ermöglicht.
- **Keine Ereignisse oder Daten**: Der Baustein arbeitet ausschließlich über Adapter-Schnittstellen; Ereignisse oder direkte Datenverbindungen werden nicht benötigt.
- **Einfache Topologie**: Die 1:6-Verteilung ist fest verdrahtet und kann nicht dynamisch angepasst werden.

## Zustandsübersicht

Der Funktionsblock besitzt keine internen Zustände oder Zustandsautomaten. Er verhält sich passiv und gibt den Eingangswert permanent an alle Ausgänge weiter. Es gibt keine zeitlichen Bedingungen oder Wechsel zwischen Modi.

## Anwendungsszenarien

- **Signalverteilung** in Steuerungsanwendungen, bei denen eine AD-Adapter-Schnittstelle an mehrere nachfolgende Bausteine verteilt werden muss.
- **Test- und Simulationsaufbauten**, um einen Datenstrom parallel zu überwachen und zu verarbeiten.
- **Bus-ähnliche Architekturen**, bei denen mehrere Verbraucher identische Adapterinformationen erhalten sollen.

## Vergleich mit ähnlichen Bausteinen

Andere Splitt-Bausteine wie `AD_SPLIT_2`, `AD_SPLIT_4` oder `AD_SPLIT_8` unterscheiden sich lediglich in der Anzahl der Ausgänge. `AD_SPLIT_6_UNGATED` bietet mit sechs Ausgängen einen Mittelweg zwischen den varianten. Es existieren auch Bausteine mit zusätzlicher Logik (z.B. bedingte Verteilung), die jedoch hier nicht vorliegt.

- **[`AD_SPLIT_6`](AD_SPLIT_6.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

`AD_SPLIT_6_UNGATED` ist ein einfacher, aber nützlicher generischer Funktionsblock zur 1:6-Verteilung eines AD-Adapters. Seine klare Schnittstelle und das Fehlen von Zustandslogik machen ihn leicht verständlich und effizient für die Verteilungsaufgaben in IEC 61499-basierten Anwendungen.

---

### 🌐 Passende Themen-Unterseiten auf ms-muc-docs.de

- [🌐 Eclipse 4diac IDE & Farb-Referenz auf ms-muc-docs.de](https://www.ms-muc-docs.de/iec-61499/eclipse-4diac/)
