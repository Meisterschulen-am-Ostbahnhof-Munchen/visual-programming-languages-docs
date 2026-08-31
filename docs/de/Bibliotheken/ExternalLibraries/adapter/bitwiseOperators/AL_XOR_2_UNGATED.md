# AL_XOR_2_UNGATED

> ℹ️ **UNGATED-Variante:** Dieser Baustein ist die ungegatete Version von [`AL_XOR_2`](AL_XOR_2.md). Er unterdrückt **keine** unveränderten Wiederholungen – jedes neu berechnete Ergebnis wird bedingungslos weitergegeben, auch ohne Wertänderung. Das ist wichtig für Verbraucher, die eine periodische Kadenz unabhängig von Wertänderung brauchen (z. B. Ableitungs-/Frequenzberechnungen, die sonst nicht gegen Null abklingen). Alle Angaben zu Änderungserkennung/Change-Gating weiter unten auf dieser Seite gelten **nicht** für diesen Baustein.

![AL_XOR_2_UNGATED](./AL_XOR_2_UNGATED.svg)

* * * * * * * * * *

## Einleitung

Der **AL_XOR_2_UNGATED** ist ein generischer Funktionsblock zur bitweisen XOR (exklusives ODER)-Verknüpfung von 2 Eingangswerten vom Typ `LWORD` (64-Bit-Bitmuster (Langwort)). Im Gegensatz zur booleschen Verknüpfung einzelner Wahrheitswerte (wie bei den `AX_XOR`-Bausteinen) wird hier jedes einzelne Bit des Datenworts unabhängig verknüpft.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine Ereignis-Eingänge vorhanden

### **Ereignis-Ausgänge**

Keine Ereignis-Ausgänge vorhanden

### **Daten-Eingänge**

Keine direkten Daten-Eingänge vorhanden

### **Daten-Ausgänge**

Keine direkten Daten-Ausgänge vorhanden

### **Adapter**

**Eingangsadapter:**

- **IN1**: XOR (exklusives ODER)-Eingang 1 (Typ: adapter::types::unidirectional::AL)
- **IN2**: XOR (exklusives ODER)-Eingang 2 (Typ: adapter::types::unidirectional::AL)

**Ausgangsadapter:**

- **OUT**: XOR (exklusives ODER)-Ergebnis (Typ: adapter::types::unidirectional::AL)

## Funktionsweise

Sobald an einem der 2 Eingangsadapter (`IN1` … `IN2`) ein Ereignis eintrifft, verknüpft der Baustein die Bitmuster aller 2 Eingänge bitweise mit **XOR (exklusives ODER)** und schreibt das Ergebnis auf den Ausgangsadapter `OUT`. Als Startwert der Verknüpfung dient das neutrale Element (alle Bits gelöscht / 0 (Nullelement der XOR-Verknüpfung)), sodass bei nur einem tatsächlich angeschlossenen Eingang dessen Wert unverändert durchgereicht wird.

Nur wenn sich das neu berechnete Ergebnis vom aktuell auf `OUT` gehaltenen Wert unterscheidet, wird `OUT` neu beschrieben und dessen Adapter-Event gesendet (siehe „Änderungserkennung" unten).

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_AL_XOR`) definiert und deckt über den GenericClassName-Mechanismus alle Aritäten (2 bis 8 Eingänge) derselben Grundlogik ab.
- **Bitweise Verknüpfung**: Anders als bei den booleschen `AX_XOR`-Bausteinen wird hier jedes Bit des `LWORD`-Datenworts einzeln verknüpft, nicht nur ein einzelner Wahrheitswert.
- **Unidirektionale Adapter**: Alle Adapter sind vom Typ `unidirectional::AL` – die Daten fließen nur vom Socket zum Plug.
- **Normkonformität**: Der Baustein implementiert die Verknüpfung gemäß IEC 61499-2 / IEC 61131-3.

## Zustandsübersicht

Da es sich um einen kombinatorischen Logikbaustein handelt, besitzt der AL_XOR_2_UNGATED keine internen Zustände. Die Ausgabe wird bei jedem eingehenden Ereignis direkt aus den aktuellen Eingangswerten neu berechnet.

## Anwendungsszenarien

- **Bitmasken-Verknüpfung**: Kombinieren mehrerer Statusregister oder Flag-Bytes vom Typ `LWORD` zu einem Gesamtergebnis.
- **Signalaggregation**: Zusammenführen mehrerer `LWORD`-Datenquellen (z. B. aus verschiedenen Modulen) über eine gemeinsame XOR (exklusives ODER)-Verknüpfung.
- **Diagnose- und Statusauswertung**: Prüfen von Bitmustern auf gemeinsame oder unterschiedliche gesetzte Bits.

## ⚖️ Vergleich mit ähnlichen Bausteinen

Im Gegensatz zu `AX_XOR_2`, der einzelne boolesche Wahrheitswerte verknüpft, arbeitet `AL_XOR_2_UNGATED` auf dem vollständigen Bitmuster eines `LWORD`-Werts. Verglichen mit dem Standard-Baustein [XOR_2](../../../StandardLibraries/iec61131-3/bitwiseOperators/XOR_2.md) verwendet `AL_XOR_2_UNGATED` Adapter-basierte Schnittstellen anstelle direkter Daten-/Ereignisein-/ausgänge, was eine flexiblere Integration in Adapter-basierte Systemarchitekturen ermöglicht.

- **[`AL_XOR_2`](AL_XOR_2.md)**: Die gegatete Variante – aktualisiert den Ausgang nur bei tatsächlicher Wertänderung.

## Änderungserkennung

Dieser Baustein führt **keine** Änderungserkennung durch. Jedes neu berechnete Ergebnis wird bedingungslos auf den Ausgang geschrieben und das zugehörige Adapter-Event gesendet, unabhängig davon, ob sich der Wert gegenüber dem vorherigen Durchlauf geändert hat.

## Fazit

Der **AL_XOR_2_UNGATED** bietet eine zuverlässige, generische Implementierung der bitweisen XOR (exklusives ODER)-Funktion für `LWORD`-Werte mit Adapter-basierten Schnittstellen. Seine generische Natur macht ihn vielseitig einsetzbar in Automatisierungsprojekten, die nach IEC 61499-Standard entwickelt werden und mehrere Bitmuster desselben Datentyps kombinieren müssen.
