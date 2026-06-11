# AUI_TO_ALI


![AUI_TO_ALI](./AUI_TO_ALI.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsblock AUI_TO_ALI ist ein Composite FB, der einen AUI-Adapter (UINT) in einen ALI-Adapter (LINT) umwandelt. Er nutzt intern den IEC 61131-Baustein F_UINT_TO_LINT zur Konvertierung.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- **AUI_IN.E1** (Ereignis über Socket AUI_IN): Startet die Konvertierung, wenn ein Ereignis am Socket anliegt (über den AUI-Adapter).

### **Ereignis-Ausgänge**
- **ALI_OUT.E1** (Ereignis über Plug ALI_OUT): Wird nach abgeschlossener Konvertierung ausgegeben (über den ALI-Adapter).

### **Daten-Eingänge**
- **AUI_IN.D1** (Daten über Socket AUI_IN): UINT-Wert, der in einen LINT-Wert konvertiert werden soll.

### **Daten-Ausgänge**
- **ALI_OUT.D1** (Daten über Plug ALI_OUT): Konvertierter LINT-Wert.

### **Adapter**
- **Socket AUI_IN** (Typ: adapter::types::unidirectional::AUI): Empfängt UINT-Daten und zugehöriges Ereignis.
- **Plug ALI_OUT** (Typ: adapter::types::unidirectional::ALI): Sendet konvertierte LINT-Daten und zugehöriges Ereignis.

## Funktionsweise

Der FB wartet auf ein Ereignis am Eingangsadapter AUI_IN (E1). Sobald dieses eintrifft, wird der anliegende UINT-Wert (D1) an den internen Konvertierungsbaustein F_UINT_TO_LINT weitergeleitet. Die Konvertierung erfolgt gemäß IEC 61131-Standard, wobei der UINT-Wert ohne Vorzeichen in einen LINT-Wert (64-Bit-Ganzzahl mit Vorzeichen) umgewandelt wird. Nach Abschluss der Konvertierung wird das Ausgangsereignis am ALI_OUT-Adapter (E1) ausgelöst und der konvertierte LINT-Wert an ALI_OUT.D1 übergeben.

## Technische Besonderheiten

- Der FB ist als Composite-Typ realisiert und kapselt die Konvertierungslogik in einem wiederverwendbaren Adapter-Interface.
- Verwendet den standardisierten Baustein F_UINT_TO_LINT aus der IEC 61131-Bibliothek.
- Lizenz: Eclipse Public License 2.0 (EPL-2.0).
- Entwickelt von HR Agrartechnik GmbH (Version 1.0, 2026-02-17).

## Zustandsübersicht

Der FB besitzt keine eigene Zustandsmaschine, da er als Composite passiv die Zustände des internen Bausteins abbildet. Der interne F_UINT_TO_LINT arbeitet nach einem einfachen Schema: Warten auf das REQ-Ereignis, Verarbeitung der Konvertierung, Auslösen des CNF-Ereignisses.

## Anwendungsszenarien

- Integration von einem System, das UINT-Werte über einen AUI-Adapter liefert, in ein System, das LINT-Werte über einen ALI-Adapter erwartet.
- Datenbrücke zwischen unterschiedlichen Adapter-Typen in einer verteilten Steuerung.
- Erweiterung von 4diac-Anwendungen, wenn eine Typkonvertierung zwischen UINT und LINT benötigt wird.

## Vergleich mit ähnlichen Bausteinen

Es existieren analoge Adapter-Konvertierungsbausteine für andere Datentypen (z. B. UINT_TO_DINT, UINT_TO_REAL usw.). Der AUI_TO_ALI ist speziell für die Kombination der unidirektionalen Adapter AUI und ALI ausgelegt und ermöglicht eine einheitliche Adapter-Schnittstelle ohne zusätzliche manuelle Konvertierung.

## Fazit

Der Composite FB AUI_TO_ALI bietet eine einfache und zuverlässige Möglichkeit, UINT-Daten über AUI-Adapter in LINT-Daten über ALI-Adapter zu konvertieren. Er ist gut gekapselt, nutzt Standardbausteine und kann leicht in 4diac-Projekte integriert werden.